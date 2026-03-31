#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::detail;

// A minimal mock for SignedSignificandBits to use as template parameter
struct MockSignedSignificandBits {
    using carrier_uint = unsigned int;
    carrier_uint u;
};

// Test fixture
class NearestAlwaysClosedTest_374 : public ::testing::Test {
protected:
    nearest_always_closed_t instance;
};

// Test that shorter_interval returns an interval_type::closed instance
TEST_F(NearestAlwaysClosedTest_374, ShorterIntervalReturnsClosedInterval_374) {
    MockSignedSignificandBits bits{0};
    auto result = nearest_always_closed_t::shorter_interval(bits);
    // The function should return a default-constructed interval_type::closed.
    // We verify it compiles and returns the correct type.
    (void)result;
    // If we get here without error, the function returned successfully.
    SUCCEED();
}

// Test that shorter_interval is constexpr and noexcept
TEST_F(NearestAlwaysClosedTest_374, ShorterIntervalIsNoexcept_374) {
    MockSignedSignificandBits bits{0};
    EXPECT_TRUE(noexcept(nearest_always_closed_t::shorter_interval(bits)));
}

// Test with different values of SignedSignificandBits - result should be the same closed interval
TEST_F(NearestAlwaysClosedTest_374, ShorterIntervalIgnoresInputValue_374) {
    MockSignedSignificandBits bits1{0};
    MockSignedSignificandBits bits2{42};
    MockSignedSignificandBits bits3{0xFFFFFFFF};

    auto result1 = nearest_always_closed_t::shorter_interval(bits1);
    auto result2 = nearest_always_closed_t::shorter_interval(bits2);
    auto result3 = nearest_always_closed_t::shorter_interval(bits3);

    // All should return the same type (interval_type::closed)
    // Since the struct has no distinguishing members, we just verify they are the same type
    static_assert(std::is_same<decltype(result1), decltype(result2)>::value, "Types should match");
    static_assert(std::is_same<decltype(result2), decltype(result3)>::value, "Types should match");
    SUCCEED();
}

// Test that the function can be called as a static method without an instance
TEST_F(NearestAlwaysClosedTest_374, CanBeCalledStatically_374) {
    MockSignedSignificandBits bits{100};
    auto result = nearest_always_closed_t::shorter_interval(bits);
    (void)result;
    SUCCEED();
}

// Test constexpr evaluation
TEST_F(NearestAlwaysClosedTest_374, ConstexprEvaluation_374) {
    // Verify the function can be evaluated at compile time
    struct ConstexprBits {
        using carrier_uint = unsigned int;
        carrier_uint u = 0;
    };
    
    constexpr auto result = nearest_always_closed_t::shorter_interval(ConstexprBits{});
    (void)result;
    SUCCEED();
}

// Test that nearest_always_closed_t is default constructible
TEST_F(NearestAlwaysClosedTest_374, IsDefaultConstructible_374) {
    EXPECT_TRUE(std::is_default_constructible<nearest_always_closed_t>::value);
}

// Boundary: test with a struct that has maximum carrier_uint value
TEST_F(NearestAlwaysClosedTest_374, BoundaryMaxValue_374) {
    struct MaxBits {
        using carrier_uint = uint64_t;
        carrier_uint u = std::numeric_limits<uint64_t>::max();
    };
    
    auto result = nearest_always_closed_t::shorter_interval(MaxBits{});
    (void)result;
    SUCCEED();
}

// Boundary: test with a struct that has minimum carrier_uint value
TEST_F(NearestAlwaysClosedTest_374, BoundaryMinValue_374) {
    struct MinBits {
        using carrier_uint = uint64_t;
        carrier_uint u = 0;
    };
    
    auto result = nearest_always_closed_t::shorter_interval(MinBits{});
    (void)result;
    SUCCEED();
}

} // namespace
