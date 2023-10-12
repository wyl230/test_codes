#pragma once
// https://stackoverflow.com/questions/75771792/asio-co-await-multiple-outsourced-async-tasks//
// #define BOOST_ASIO_ENABLE_HANDLER_TRACKING 1 #define BOOST_ASIO_STANDALONE 1
// #define BOOST_ASIO_HAS_CO_AWAIT      1
// #define BOOST_ASIO_HAS_STD_COROUTINE 1

#include <boost/asio.hpp>
#include <boost/asio/experimental/awaitable_operators.hpp>
#include <iomanip>
#include <iostream>
namespace asio = boost::asio;
using namespace std::chrono_literals;

namespace multi_task {
auto my_async(auto executor, auto task, auto &&token) {
  return async_initiate<decltype(token), void(std::error_code e)>(
      [executor](auto handler, auto task) {
        asio::post( //
            executor, [h = std::move(handler), t = std::move(task)]() mutable {
              t();
              std::move(h)(std::error_code{});
            });
      },
      std::forward<decltype(token)>(token), std::move(task));
}

static std::atomic_int thread_counter = 0;

thread_local int const t_id = thread_counter++;
static auto const now = std::chrono::steady_clock::now;
static auto const start = now();

static void trace(auto const &...args) {
  static std::mutex mx;

  std::lock_guard lk(mx);
  std::cout << std::setw(10) << (now() - start) / 1ms << "ms t_id:" << t_id
            << " ";
  (std::cout << ... << args) << std::endl;
}

inline int test() {
  trace("start program");

  asio::thread_pool pool(4);
  asio::io_context io_service{};

  auto guard = make_work_guard(io_service);

  std::thread thrd = std::thread{[&io_service]() {
    trace("start io_service loop");
    io_service.run();
    trace("end io_service loop");
  }};

  asio::steady_timer main_timer{io_service,
                                asio::steady_timer::time_point::max()};

  asio::cancellation_signal cancel;

  auto make_task = [&](std::string name,
                       auto cost) { // generates expensive tasks
    return [=] {
      trace(name, " begin ", cost / 1.s, "s work");
      std::this_thread::sleep_for(cost);
      trace(name, " end ", cost / 1.s, "s work");
    };
  };

  using asio::use_awaitable;
  using namespace asio::experimental::awaitable_operators;

  auto mainloop = [&]() -> asio::awaitable<void> {
    trace("run mainloop event");
    auto ex = pool.get_executor();
    auto aw1 = my_async(ex, make_task("aw1", 6s), use_awaitable);
    auto aw2 = my_async(ex, make_task("aw2", 2s), use_awaitable);
    // < possible medium expansive work here>
    auto aw3 = my_async(ex, make_task("aw3", 4s), use_awaitable);
    auto aw4 = my_async(
        ex,
        [&main_timer]() {
          std::this_thread::sleep_for(3s);
          trace("aw4 cancels main_timer");
          main_timer.expires_at(asio::steady_timer::time_point::min());
        },
        use_awaitable);

    asio::steady_timer local_timer(io_service, 5s);
    auto delay = local_timer.async_wait(use_awaitable);

    trace("before co_await");
    co_await (std::move(delay) && std::move(aw1) && std::move(aw2) &&
              std::move(aw3) && std::move(aw4));
    trace("after co_await");
  };

  trace(std::boolalpha, "main_timer.expiry() == max()? ",
        main_timer.expiry() == std::chrono::steady_clock::time_point::max());

  asio::co_spawn(io_service.get_executor(), mainloop(),
                 [&](std::exception_ptr e) {
                   if (e) {
                     try {
                       std::rethrow_exception(e);
                     } catch (const std::exception &e) {
                       trace("mainloop failed with: ", e.what());
                     } catch (...) {
                       trace("mainloop failed with unknown exception");
                     }
                   }

                   trace(std::boolalpha, "main_timer.expiry() == min()? ",
                         main_timer.expiry() ==
                             std::chrono::steady_clock::time_point::min());
                 });

  guard.reset();
  thrd.join();
  trace("bye");
  return 0;
}

} // namespace multi_task
