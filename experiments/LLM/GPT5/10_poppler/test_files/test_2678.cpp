// pdfsig_getReadableTime_test_2678.cc
#include <gtest/gtest.h>

#include <clocale>
#include <cstdlib>
#include <ctime>
#include <regex>
#include <string>

#if defined(_WIN32)
#include <stdlib.h>
#endif

// If pdfsig.cc is a standalone tool, it may define `main`. Rename it to avoid
// collision with gtest's main.
#define main pdfsig_main_2678
#include "TestProjects/poppler/utils/pdfsig.cc"
#undef main

namespace {

// RAII helper to make std::localtime() deterministic for tests by forcing:
// - C locale (so %b is English-like month abbreviations)
// - UTC timezone (so timestamps map to stable date/time)
class ScopedLocaleAndTZ_2678 {
public:
    ScopedLocaleAndTZ_2678() {
        // Locale: prefer "C" which is always available.
        oldLocale_ = std::setlocale(LC_TIME, nullptr);
        if (oldLocale_) {
            savedLocale_ = oldLocale_;
        }
        std::setlocale(LC_TIME, "C");

        // Timezone: force UTC.
#if defined(_WIN32)
        // Save old TZ
        char *old = nullptr;
        size_t len = 0;
        if (_dupenv_s(&old, &len, "TZ") == 0 && old) {
            savedTZ_ = old;
            free(old);
            hadTZ_ = true;
        } else {
            hadTZ_ = false;
        }
        _putenv_s("TZ", "UTC");
        _tzset();
#else
        const char *old = std::getenv("TZ");
        if (old) {
            savedTZ_ = old;
            hadTZ_ = true;
        } else {
            hadTZ_ = false;
        }
        setenv("TZ", "UTC", 1);
        tzset();
#endif
    }

    ~ScopedLocaleAndTZ_2678() {
        // Restore locale
        if (!savedLocale_.empty()) {
            std::setlocale(LC_TIME, savedLocale_.c_str());
        }

        // Restore TZ
#if defined(_WIN32)
        if (hadTZ_) {
            _putenv_s("TZ", savedTZ_.c_str());
        } else {
            _putenv_s("TZ", "");
        }
        _tzset();
#else
        if (hadTZ_) {
            setenv("TZ", savedTZ_.c_str(), 1);
        } else {
            unsetenv("TZ");
        }
        tzset();
#endif
    }

private:
    const char *oldLocale_ = nullptr;
    std::string savedLocale_;
    std::string savedTZ_;
    bool hadTZ_ = false;
};

} // namespace

TEST(GetReadableTimeTest_2678, EpochInUTCFormatsAsExpected_2678) {
    ScopedLocaleAndTZ_2678 guard;

    const time_t t = static_cast<time_t>(0);
    const std::string s = getReadableTime(t);

    // With TZ=UTC and C locale: Jan 01 1970 00:00:00
    EXPECT_EQ(s, "Jan 01 1970 00:00:00");
}

TEST(GetReadableTimeTest_2678, KnownTimestampFormatsAsExpected_2678) {
    ScopedLocaleAndTZ_2678 guard;

    // 2021-01-01 00:00:00 UTC
    const time_t t = static_cast<time_t>(1609459200);
    const std::string s = getReadableTime(t);

    EXPECT_EQ(s, "Jan 01 2021 00:00:00");
}

TEST(GetReadableTimeTest_2678, LeapDayTimestampFormatsAsExpected_2678) {
    ScopedLocaleAndTZ_2678 guard;

    // 2020-02-29 12:34:56 UTC
    const time_t t = static_cast<time_t>(1582979696);
    const std::string s = getReadableTime(t);

    EXPECT_EQ(s, "Feb 29 2020 12:34:56");
}

TEST(GetReadableTimeTest_2678, OutputMatchesExpectedPattern_2678) {
    ScopedLocaleAndTZ_2678 guard;

    const time_t t = static_cast<time_t>(1672531199); // 2022-12-31 23:59:59 UTC
    const std::string s = getReadableTime(t);

    // Format: "%b %d %Y %H:%M:%S"
    // e.g., "Dec 31 2022 23:59:59"
    const std::regex pattern(R"(^[A-Z][a-z]{2} [0-9]{2} [0-9]{4} [0-9]{2}:[0-9]{2}:[0-9]{2}$)");
    EXPECT_TRUE(std::regex_match(s, pattern)) << "Actual: " << s;

    // Also verify exact expected value for this boundary-like time.
    EXPECT_EQ(s, "Dec 31 2022 23:59:59");
}