#ifndef CPPUTIL_RANGE_H
#define CPPUTIL_RANGE_H

#include <stdexcept>

namespace cpputil {

// Left close right open range.
// Example:
// ```c++
//   auto print_range = [](Range range) {
//     for (int x : range)
//       cout << x << " ";
//     cout << endl;
//   };
//   print_range({0, 4});
//   print_range({0, -1});
//   print_range({0, 4, 2});
//   print_range({5, 0, -2});
// ```
// Above code will print:
// ```
// 0 1 2 3 
// 
// 0 2 
// 5 3 1 
// ```
class Range {
 public:
  // Throws runtime_error if `step ` is 0
  Range(int start, int end, int step = 1)
      : start_(start),
        end_(end),
        step_(step),
        iter_begin_{start_, step_},
        iter_end_{roundedEnd(), step_} {}

  struct Iterator {
    int index;
    const int step;

    int operator*() const noexcept { return index; }

    bool operator!=(const Iterator& rhs) const noexcept {
      return index != rhs.index;
    }

    Iterator& operator++() noexcept {
      index += step;
      return *this;
    }

    Iterator operator++(int) noexcept {
      auto temp = *this;
      index += step;
      return temp;
    }
  };

  Iterator begin() const noexcept { return iter_begin_; }
  Iterator end() const noexcept { return iter_end_; }

 private:
  const int start_;
  const int end_;
  const int step_;

  const Iterator iter_begin_;
  const Iterator iter_end_;

  // returns a new end that satisfies (result - start_) % step_ == 0
  int roundedEnd() const {
    if (step_ == 0) throw std::runtime_error("step must be non-zero");

    // empty range
    if ((step_ > 0 && start_ >= end_) || (step_ < 0 && start_ <= end_))
      return start_;

    const bool increase = (step_ > 0);
    const int size = (increase ? (end_ - start_) : (start_ - end_));
    const int step = (increase ? step_ : -step_);

    const int last_step = size % step;
    if (last_step == 0) {
      return end_;
    } else {
      int padding = step - last_step;
      return (increase ? (end_ + padding) : (end_ - padding));
    }
  }
};

}  // namespace cpputil

#endif  // CPPUTIL_RANGE_H
