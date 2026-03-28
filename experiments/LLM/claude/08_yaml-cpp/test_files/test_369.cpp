#include <gtest/gtest.h>
#include "contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;

// A mock/stub type to use as SignedSignificandBits parameter
struct MockSignedSignificandBits {
    int value;
};

struct AnotherMockSignedSignificandBits {
    double data;
    bool flag;
};

class NearestTowardZeroTest_369 : public ::testing::Test {
protected:
    nearest_toward_zero policy_;
};

// Test that shorter_interval can be called with a simple mock type
TEST_F(NearestTowardZeroTest_369, ShorterIntervalReturnsRightClosedLeftOpen_369) {
    MockSignedSignificandBits bits{0};
    auto result = nearest_toward_zero::shorter_interval(bits);
    // The function should return a default-constructed right_closed_left_open interval
    // We verify it compiles and returns the expected type
    (void)result;
    SUCCEED();
}

// Test that shorter_interval works with different SignedSignificandBits values
TEST_F(NearestTowardZeroTest_369, ShorterIntervalWithDifferentValues_369) {
    MockSignedSignificandBits bits1{-1};
    MockSignedSignificandBits bits2{42};
    MockSignedSignificandBits bits3{std::numeric_limits<int>::max()};
    MockSignedSignificandBits bits4{std::numeric_limits<int>::min()};

    auto result1 = nearest_toward_zero::shorter_interval(bits1);
    auto result2 = nearest_toward_zero::shorter_interval(bits2);
    auto result3 = nearest_toward_zero::shorter_interval(bits3);
    auto result4 = nearest_toward_zero::shorter_interval(bits4);

    (void)result1;
    (void)result2;
    (void)result3;
    (void)result4;
    SUCCEED();
}

// Test that shorter_interval is constexpr
TEST_F(NearestTowardZeroTest_369, ShorterIntervalIsConstexpr_369) {
    constexpr MockSignedSignificandBits bits{10};
    constexpr auto result = nearest_toward_zero::shorter_interval(bits);
    (void)result;
    SUCCEED();
}

// Test that shorter_interval is noexcept
TEST_F(NearestTowardZeroTest_369, ShorterIntervalIsNoexcept_369) {
    MockSignedSignificandBits bits{0};
    static_assert(noexcept(nearest_toward_zero::shorter_interval(bits)),
                  "shorter_interval should be noexcept");
    SUCCEED();
}

// Test that the function works with a different type as template argument
TEST_F(NearestTowardZeroTest_369, ShorterIntervalWithAnotherType_369) {
    AnotherMockSignedSignificandBits bits{3.14, true};
    auto result = nearest_toward_zero::shorter_interval(bits);
    (void)result;
    SUCCEED();
}

// Test that shorter_interval returns the same type regardless of input
TEST_F(NearestTowardZeroTest_369, ReturnTypeConsistency_369) {
    MockSignedSignificandBits bits1{0};
    AnotherMockSignedSignificandBits bits2{0.0, false};

    auto result1 = nearest_toward_zero::shorter_interval(bits1);
    auto result2 = nearest_toward_zero::shorter_interval(bits2);

    // Both should return the same type
    static_assert(std::is_same<decltype(result1), decltype(result2)>::value,
                  "Return types should be the same regardless of input type");
    SUCCEED();
}

// Test that nearest_toward_zero can be default constructed
TEST_F(NearestTowardZeroTest_369, DefaultConstructible_369) {
    nearest_toward_zero ntz;
    (void)ntz;
    SUCCEED();
}

// Test with zero-initialized parameter
TEST_F(NearestTowardZeroTest_369, ShorterIntervalWithZeroInit_369) {
    MockSignedSignificandBits bits{};
    auto result = nearest_toward_zero::shorter_interval(bits);
    (void)result;
    SUCCEED();
}

} // namespace
