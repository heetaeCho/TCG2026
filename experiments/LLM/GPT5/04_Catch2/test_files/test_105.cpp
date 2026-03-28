// File: test_catch_tostring_timepoint_105.cpp

#include <gtest/gtest.h>
#include <chrono>
#include <ctime>
#include <string>

// Include the header under test
#include "catch2/catch_tostring.hpp"

namespace {

// Helper: build a UTC time_t from calendar fields without depending on local TZ.
// Uses timegm (POSIX) or _mkgmtime (Windows).
inline std::time_t MakeUTCTime(int year, int mon, int mday,
                               int hour, int min, int sec) {
    std::tm tm{};
    tm.tm_year = year - 1900; // years since 1900
    tm.tm_mon  = mon - 1;     // 0-11
    tm.tm_mday = mday;        // 1-31
    tm.tm_hour = hour;        // 0-23
    tm.tm_min  = min;         // 0-59
    tm.tm_sec  = sec;         // 0-60 (leap second)
    tm.tm_isdst = -1;         // let library determine

#if defined(_WIN32)
    return _mkgmtime(&tm);
#else
    return timegm(&tm);
#endif
}

using std::chrono::system_clock;

} // namespace

// --- Tests ---

// Normal operation: epoch 0 should format as ISO-8601 UTC.
TEST(CatchToStringTimepointTest_105, ConvertsEpoch_105) {
    system_clock::time_point tp = system_clock::from_time_t(0);
    std::string out = Catch::convert(tp);
    EXPECT_EQ(out, "1970-01-01T00:00:00Z");
}

// Boundary-ish/date correctness: leap day formatting in UTC.
TEST(CatchToStringTimepointTest_105, FormatsLeapDay_105) {
    const std::time_t t = MakeUTCTime(2000, 2, 29, 12, 34, 56);
    ASSERT_NE(t, static_cast<std::time_t>(-1)) << "MakeUTCTime failed to build UTC time";
    system_clock::time_point tp = system_clock::from_time_t(t);

    std::string out = Catch::convert(tp);
    EXPECT_EQ(out, "2000-02-29T12:34:56Z");
}

// General formatting guarantees: length and trailing 'Z' (UTC indicator).
TEST(CatchToStringTimepointTest_105, EmitsFixedLengthAndZSuffix_105) {
    const std::time_t t = MakeUTCTime(1999, 12, 31, 23, 59, 59);
    ASSERT_NE(t, static_cast<std::time_t>(-1));
    system_clock::time_point tp = system_clock::from_time_t(t);

    std::string out = Catch::convert(tp);
    // Expect "YYYY-MM-DDTHH:MM:SSZ" -> length 20 and ends with 'Z'
    EXPECT_EQ(out.size(), 20u);
    EXPECT_EQ(out.back(), 'Z');
}

// Exceptional/error case that is observable through the interface on MSVC:
// pre-1970 dates may fail in Microsoft libc and return a specific message.
#if defined(_MSC_VER)
TEST(CatchToStringTimepointTest_105, Pre1970OnMSVC_ReturnsErrorMessage_105) {
    const std::time_t t = MakeUTCTime(1960, 1, 1, 0, 0, 0);
    // Even if _mkgmtime returns -1 for some platforms, the class under test
    // treats the conversion as a black box; we only check the observable result.
    system_clock::time_point tp = system_clock::from_time_t(t);

    std::string out = Catch::convert(tp);
    EXPECT_EQ(out,
        "gmtime from provided timepoint has failed. This "
        "happens e.g. with pre-1970 dates using Microsoft libc");
}
#endif
