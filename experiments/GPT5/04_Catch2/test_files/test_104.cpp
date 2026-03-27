// File: catch_tostring_convert_timepoint_test_104.cpp

#include <gtest/gtest.h>
#include <chrono>
#include <string>

// ---- Test doubles for the external collaborator ----
// We provide non-template overloads for specific duration types. These are
// visible to the header below and will be preferred over any template
// stringify, letting us observe parameters & control the return value.
namespace Catch { namespace Detail {

// Observability for seconds
inline bool g_called_seconds = false;
inline std::chrono::seconds g_last_seconds{0};
inline std::string stringify(std::chrono::seconds const& d) {
    g_called_seconds = true;
    g_last_seconds = d;
    // Return a controlled token so we can assert suffixing behavior
    return "S(" + std::to_string(d.count()) + ")";
}

// Observability for milliseconds
inline bool g_called_millis = false;
inline std::chrono::milliseconds g_last_millis{0};
inline std::string stringify(std::chrono::milliseconds const& d) {
    g_called_millis = true;
    g_last_millis = d;
    return "MS(" + std::to_string(d.count()) + ")";
}

}} // namespace Catch::Detail

// ---- Include the unit under test AFTER our stringify overloads ----
#include "Catch2/src/catch2/catch_tostring.hpp"

// ---- Test fixture (keeps names consistent and resets observers) ----
class CatchToStringTimePointTest_104 : public ::testing::Test {
protected:
    void SetUp() override {
        using namespace Catch::Detail;
        g_called_seconds = false;
        g_last_seconds = std::chrono::seconds{0};
        g_called_millis = false;
        g_last_millis = std::chrono::milliseconds{0};
    }
};

// ---- Tests ----

// Verifies that convert appends " since epoch" to the result of stringify
// and that stringify is invoked with the exact duration (seconds).
TEST_F(CatchToStringTimePointTest_104, AppendsSuffixAndCallsStringify_Seconds_104) {
    using sys = std::chrono::system_clock;
    std::chrono::time_point<sys, std::chrono::seconds> tp{std::chrono::seconds{42}};

    const std::string out = Catch::convert(tp);

    EXPECT_TRUE(Catch::Detail::g_called_seconds) << "stringify(seconds) should be called";
    EXPECT_EQ(Catch::Detail::g_last_seconds, std::chrono::seconds{42})
        << "stringify should receive the exact time_since_epoch() value";
    EXPECT_EQ(out, "S(42) since epoch") << "convert must append the fixed suffix";
}

// Boundary: epoch (zero) should still call stringify with zero duration and suffix correctly.
TEST_F(CatchToStringTimePointTest_104, HandlesEpochZero_Seconds_104) {
    using sys = std::chrono::system_clock;
    std::chrono::time_point<sys, std::chrono::seconds> tp{std::chrono::seconds{0}};

    const std::string out = Catch::convert(tp);

    EXPECT_TRUE(Catch::Detail::g_called_seconds);
    EXPECT_EQ(Catch::Detail::g_last_seconds, std::chrono::seconds{0});
    EXPECT_EQ(out, "S(0) since epoch");
}

// Boundary: negative duration (time before epoch) must be forwarded unchanged.
TEST_F(CatchToStringTimePointTest_104, ForwardsNegativeDuration_Seconds_104) {
    using sys = std::chrono::system_clock;
    std::chrono::time_point<sys, std::chrono::seconds> tp{std::chrono::seconds{-3}};

    const std::string out = Catch::convert(tp);

    EXPECT_TRUE(Catch::Detail::g_called_seconds);
    EXPECT_EQ(Catch::Detail::g_last_seconds, std::chrono::seconds{-3});
    EXPECT_EQ(out, "S(-3) since epoch");
}

// Type-variation: verify that convert calls the matching stringify overload
// for the provided Duration type (milliseconds here) and still appends the suffix.
TEST_F(CatchToStringTimePointTest_104, UsesMatchingDurationOverload_Milliseconds_104) {
    using sys = std::chrono::system_clock;
    std::chrono::time_point<sys, std::chrono::milliseconds> tp{std::chrono::milliseconds{1500}};

    const std::string out = Catch::convert(tp);

    EXPECT_TRUE(Catch::Detail::g_called_millis) << "stringify(milliseconds) should be called";
    EXPECT_EQ(Catch::Detail::g_last_millis, std::chrono::milliseconds{1500});
    EXPECT_EQ(out, "MS(1500) since epoch");
}
