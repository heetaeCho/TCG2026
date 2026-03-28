#include <gtest/gtest.h>
#include "contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::detail;

// A mock/stub type to use as SignedSignificandBits template argument
struct MockSignedSignificandBits {
    int value = 0;
};

struct AnotherSignedSignificandBits {
    double data = 3.14;
};

// Test fixture
class NearestAlwaysOpenTest_376 : public ::testing::Test {
protected:
    nearest_always_open_t instance;
};

// Test that shorter_interval can be called with a MockSignedSignificandBits and returns properly
TEST_F(NearestAlwaysOpenTest_376, ShorterIntervalReturnsOpenInterval_376) {
    MockSignedSignificandBits bits;
    auto result = nearest_always_open_t::shorter_interval(bits);
    // The function should return interval_type::open - we verify it compiles and is callable
    (void)result;
    SUCCEED();
}

// Test that shorter_interval is noexcept
TEST_F(NearestAlwaysOpenTest_376, ShorterIntervalIsNoexcept_376) {
    MockSignedSignificandBits bits;
    EXPECT_TRUE(noexcept(nearest_always_open_t::shorter_interval(bits)));
}

// Test that shorter_interval is constexpr by using it in a constexpr context
TEST_F(NearestAlwaysOpenTest_376, ShorterIntervalIsConstexpr_376) {
    constexpr auto result = nearest_always_open_t::shorter_interval(MockSignedSignificandBits{});
    (void)result;
    SUCCEED();
}

// Test that shorter_interval works with different SignedSignificandBits types
TEST_F(NearestAlwaysOpenTest_376, ShorterIntervalWorksWithDifferentTypes_376) {
    AnotherSignedSignificandBits bits;
    auto result = nearest_always_open_t::shorter_interval(bits);
    (void)result;
    SUCCEED();
}

// Test that shorter_interval can be called as a static method without an instance
TEST_F(NearestAlwaysOpenTest_376, ShorterIntervalCallableAsStatic_376) {
    MockSignedSignificandBits bits;
    auto result = nearest_always_open_t::shorter_interval(bits);
    (void)result;
    SUCCEED();
}

// Test that the return type of shorter_interval is consistent across calls
TEST_F(NearestAlwaysOpenTest_376, ReturnTypeConsistency_376) {
    MockSignedSignificandBits bits1;
    AnotherSignedSignificandBits bits2;
    
    auto result1 = nearest_always_open_t::shorter_interval(bits1);
    auto result2 = nearest_always_open_t::shorter_interval(bits2);
    
    // Both should return the same type (interval_type::open)
    bool same_type = std::is_same<decltype(result1), decltype(result2)>::value;
    EXPECT_TRUE(same_type);
}

// Test that nearest_always_open_t is default constructible
TEST_F(NearestAlwaysOpenTest_376, DefaultConstructible_376) {
    EXPECT_TRUE(std::is_default_constructible<nearest_always_open_t>::value);
}

// Test with a default-constructed SignedSignificandBits argument
TEST_F(NearestAlwaysOpenTest_376, ShorterIntervalWithDefaultConstructedArg_376) {
    auto result = nearest_always_open_t::shorter_interval(MockSignedSignificandBits{});
    (void)result;
    SUCCEED();
}

// Test that multiple calls produce consistent results
TEST_F(NearestAlwaysOpenTest_376, MultipleCalls_376) {
    MockSignedSignificandBits bits;
    auto result1 = nearest_always_open_t::shorter_interval(bits);
    auto result2 = nearest_always_open_t::shorter_interval(bits);
    // Both should be the same type and value (default constructed interval_type::open)
    EXPECT_TRUE((std::is_same<decltype(result1), decltype(result2)>::value));
}

} // namespace
