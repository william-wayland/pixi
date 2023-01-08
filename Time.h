#pragma once

#include <cmath>
#include <chrono>
#include <functional>

#include "Macro.h"

using namespace std::literals::chrono_literals;

/**
 * Base std::chrono type that TimeDuration extends.
 */
using TimeDuration_Base_Duration = std::chrono::duration<int64_t, std::nano>;

/**
 * It extends TimeDuration_Base_Duration which is a nanosecond count as a signed 64bit integer.
 * TimeDuration can be implicitly constructed from 64bit int (in nanoseconds), a double (in
 * seconds) or any std::chrono::duration type. It can also be implicitly converted to a 64bit
 * integer (in nanoseconds)
 */
struct TimeDuration : public TimeDuration_Base_Duration
{
    /**
     * Default constructor. Creates a duration of 0 nanoseconds.
     */
    constexpr TimeDuration()
        : TimeDuration_Base_Duration(0)
    {}

    /**
     * Create a TimeDuration from an integer
     *
     * @param nanoseconds the time duration in nanoseconds.
     */
    constexpr TimeDuration(int64_t nanoseconds)
        : TimeDuration_Base_Duration(nanoseconds)
    {}

    /**
     * Create a TimeDuration from a std::chrono::duration type
     *
     * @param d the duration. Will be converted to integer nanosecond representation.
     */
    template <typename Rep, typename Period>
    constexpr TimeDuration(const duration<Rep, Period>& d)
        : TimeDuration_Base_Duration(std::chrono::duration_cast<TimeDuration_Base_Duration>(d))
    {}

    COPY_MOVE_CONSTRUCTORS(TimeDuration, default, default)

    ~TimeDuration() = default;

    /**
     * Implcit conversion from TimeDuration to int64 (as nanoseconds)
     */
    constexpr operator int64_t() const {
        return count();
    }

    /**
     * Get duration in nanoseconds
     */
    constexpr int64_t Nanoseconds() const {
        return count();
    }

    /**
     * Get duration in microseconds
     */
    constexpr int64_t Microseconds() const {
        return std::chrono::duration_cast<std::chrono::duration<int64_t, std::micro>>(*this).count();
    }

    /**
     * Get duration in milliseconds
     */
    constexpr int64_t Milliseconds() const {
        return std::chrono::duration_cast<std::chrono::duration<int64_t, std::milli>>(*this).count();
    }

    /**
     * Get duration in seconds
     */
    constexpr double Seconds() const {
        return std::chrono::duration_cast<std::chrono::duration<double>>(*this).count();
    }

    /**
     * Get a Time Duration from seconds
     */
    template<typename T>
    static TimeDuration FromSeconds(T seconds) {
        return std::chrono::duration<T>(seconds);
    }

    std::string ToString() {

        double s = Seconds();
        double ms = (s - static_cast<int>(s)) * 1000;
        double us = (ms - static_cast<int>(ms)) * 1000;
        double ns = (us - static_cast<int>(us)) * 1000;

        std::stringstream ss;
        ss << static_cast<int>(s) << "s "
            << static_cast<int>(ms) << "ms "
            << static_cast<int>(us) << "us "
            << static_cast<int>(ns) << "ns";
        return ss.str();
    }
};

// From MSVC when targetting C++20, time point is a little strict with durations, it'll check the following
// specialization. We need to trick std::chrono, but we know it's a duration so it's probably safe.
namespace std {
    namespace chrono {
        template <>
        constexpr bool _Is_duration_v<TimeDuration> = true;
    }
}

/**
 * Base std::chrono type that Timestamp extends.
 */
using Timestamp_Base_Timepoint = std::chrono::time_point<std::chrono::system_clock, TimeDuration>;

/**
 * Timestamp represents a datetime value (as nanosec since epoch).
 * 
 * It extends Timestamp_Base_Timepoint which is a system_clock time_point with integer nanosecond
 * representation.
 * Timestamp can be implicitly constructed from 64bit int (nanoseconds since epoch) or any
 * std::chrono::time_point that uses std::chrono::system_clock. It can also be implicitly converted
 * to a 64bit integer (nanoseconds since epoch)
 */
struct Timestamp : public Timestamp_Base_Timepoint
{
    /**
     * Default constructor. Creates a Timestamp at epoch.
     */
    constexpr Timestamp()
        : Timestamp_Base_Timepoint()
    {}

    /**
     * Create a Timestamp from an integer
     *
     * @param nanoseconds time since epoch in nanoseconds.
     */
    constexpr Timestamp(int64_t nanoseconds)
        : Timestamp_Base_Timepoint(nanoseconds)
    {}

    /**
     * Create a Timestamp from a std::chrono::time_point. Note that the timepoint must use
     * std::chrono::system_clock.
     *
     * @param t the time_point
     */
    template <typename Duration>
    constexpr Timestamp(const std::chrono::time_point<clock, Duration>& t)
        : Timestamp_Base_Timepoint(std::chrono::time_point_cast<TimeDuration_Base_Duration>(t))
    {}

    COPY_MOVE_CONSTRUCTORS(Timestamp, default, default)

    ~Timestamp() = default;

    /**
     * Implcit conversion from Timestamp to int64 (nanoseconds since epoch)
     */
    constexpr operator int64_t() const {
        return time_since_epoch().count();
    }

    /**
     * Get a Timestamp at the current time.
     */
    static Timestamp Now() {
        return Timestamp(clock::now());
    }
};

template<>
struct std::hash<Timestamp> {
    std::size_t operator()(const Timestamp& timestamp) const noexcept {
        return std::hash<int64_t>{}(timestamp);
    };
};