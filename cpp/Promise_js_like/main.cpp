#pragma once
#include "promise_resolver.hpp"
#include "promise_state.hpp"
#include "promise_status_machine.hpp"
#include "to_be_checked.hpp"
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <print.hpp>

int main(int argc, char *argv[]) { return 0; }

// void test1() {
//   MessageLoop *loop;
//
//   int value = 0;
//   Promise<int> p1;
//
//   auto p2 = p1.Then(
//       [&](Result<int> &&r) -> Result<std::string> {
//         if (r) {
//           value = r.PassResult();
//           return std::to_string(value);
//         } else {
//           return r.PassError();
//         }
//       },
//       loop->GetExecutor());
//
//   p1.Resolve(2023);
//
//   assert(value == 2023);
//   assert(std::is_same_v<decltype(p2), Promise<std::string>>);
//
//   std::string str;
//   p2.Then(
//       [&](Result<std::string> &&r) -> Result<void> {
//         if (r) {
//           str = r.PassResult();
//         } else {
//           return r.PassError();
//         }
//       },
//       loop->GetExecutor());
//
//   assert(str == "2023");
// }
