#pragma once

#include <tuple>

template <typename OStream, typename Tuple, size_t N> struct TuplePrinter {
  static void Print(OStream *os, const Tuple &t) {
    TuplePrinter<OStream, Tuple, N - 1>::Print(os, t);
    *os << std::get<N - 1>(t);
  }
};

template <typename OStream, typename Tuple>
struct TuplePrinter<OStream, Tuple, 0> {
  static void Print(OStream *os, const Tuple &t) {}
};

// Print elements from a tuple to a stream, in order.
// Typical use is to pack a bunch of existing values with
// std::forward_as_tuple() before passing it to this function.
template <typename OStream, typename... Args>
void PrintTuple(OStream *os, const std::tuple<Args &...> &tup) {
  TuplePrinter<OStream, std::tuple<Args &...>, sizeof...(Args)>::Print(os, tup);
}

template <typename Range, typename Separator> struct PrintVector {
  const Range &range_;
  const Separator &separator_;

  template <typename Os> // template to dodge inclusion of <ostream>
  friend Os &operator<<(Os &os, PrintVector l) {
    bool first = true;
    os << "[";
    for (const auto &element : l.range_) {
      if (first) {
        first = false;
      } else {
        os << l.separator_;
      }
      os << ToChars(element); // use ToChars to avoid locale dependence
    }
    os << "]";
    return os;
  }
};
template <typename Range, typename Separator>
PrintVector(const Range &, const Separator &) -> PrintVector<Range, Separator>;
