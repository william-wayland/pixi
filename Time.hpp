#pragma once

#include <chrono>
#include <cmath>
#include <functional>

using namespace std::literals::chrono_literals;

using TimeDuration_Base_Duration = std::chrono::duration<int64_t, std::nano>;

struct TimeDuration : public TimeDuration_Base_Duration {

  constexpr TimeDuration() : TimeDuration_Base_Duration(0) {}

  constexpr TimeDuration(int64_t nanoseconds)
      : TimeDuration_Base_Duration(nanoseconds) {}

  template <typename Rep, typename Period>
  constexpr TimeDuration(const duration<Rep, Period> &d)
      : TimeDuration_Base_Duration(
            std::chrono::duration_cast<TimeDuration_Base_Duration>(d)) {}

  TimeDuration(const TimeDuration &) = default;
  TimeDuration &operator=(const TimeDuration &) = default;
  TimeDuration(TimeDuration &&) = default;
  TimeDuration &operator=(TimeDuration &&) = default;

  ~TimeDuration() = default;

  constexpr operator int64_t() const { return count(); }

  constexpr int64_t Nanoseconds() const { return count(); }

  constexpr int64_t Microseconds() const {
    return std::chrono::duration_cast<
               std::chrono::duration<int64_t, std::micro>>(*this)
        .count();
  }

  constexpr int64_t Milliseconds() const {
    return std::chrono::duration_cast<
               std::chrono::duration<int64_t, std::milli>>(*this)
        .count();
  }
  constexpr double Seconds() const {
    return std::chrono::duration_cast<std::chrono::duration<double>>(*this)
        .count();
  }

  template <typename T> static TimeDuration FromSeconds(T seconds) {
    return std::chrono::duration<T>(seconds);
  }
};

// From MSVC when targetting C++20, time point is a little strict with
// durations, it'll check the following specialization. We need to trick
// std::chrono, but we know it's a duration so it's probably safe.
namespace std {
namespace chrono {
template <> constexpr bool _Is_duration_v<TimeDuration> = true;
}
} // namespace std

using Timestamp_Base_Timepoint =
    std::chrono::time_point<std::chrono::system_clock, TimeDuration>;

struct Timestamp : public Timestamp_Base_Timepoint {

  constexpr Timestamp() : Timestamp_Base_Timepoint() {}

  constexpr Timestamp(int64_t nanoseconds)
      : Timestamp_Base_Timepoint(nanoseconds) {}

  template <typename Duration>
  constexpr Timestamp(const std::chrono::time_point<clock, Duration> &t)
      : Timestamp_Base_Timepoint(
            std::chrono::time_point_cast<TimeDuration_Base_Duration>(t)) {}

  Timestamp(const Timestamp &) = default;
  Timestamp &operator=(const Timestamp &) = default;
  Timestamp(Timestamp &&) = default;
  Timestamp &operator=(Timestamp &&) = default;

  ~Timestamp() = default;

  constexpr operator int64_t() const { return time_since_epoch().count(); }
  static Timestamp Now() { return Timestamp(clock::now()); }
};
