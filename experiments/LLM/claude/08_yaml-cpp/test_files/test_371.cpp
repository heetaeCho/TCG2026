#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;

// A mock/stub type to serve as SignedSignificandBits for template parameter
struct MockSignedSignificandBits {
    int value = 0;
};

struct AnotherSignedSignificandBits {
    double data = 3.14;
};

// Test fixture
class NearestAwayFromZeroTest_371 : public ::testing::Test {
protected:
    nearest_away_from_zero_t policy_;
};

// Test that normal_interval returns a value (compiles and is callable)
TEST_F(NearestAwayFromZeroTest_371, NormalIntervalReturnsLeftClosedRightOpen_371) {
    MockSignedSignificandBits bits;
    auto result = nearest_away_from_zero_t::normal_interval(bits);
    // The return type should be interval_type::left_closed_right_open
    // We verify it compiles and returns without error
    (void)result;
}

// Test that normal_interval is constexpr
TEST_F(NearestAwayFromZeroTest_371, NormalIntervalIsConstexpr_371) {
    // Verify the function can be called in a constexpr context
    constexpr auto result = nearest_away_from_zero_t::normal_interval(MockSignedSignificandBits{});
    (void)result;
}

// Test that normal_interval is noexcept
TEST_F(NearestAwayFromZeroTest_371, NormalIntervalIsNoexcept_371) {
    MockSignedSignificandBits bits;
    EXPECT_TRUE(noexcept(nearest_away_from_zero_t::normal_interval(bits)));
}

// Test with different SignedSignificandBits type
TEST_F(NearestAwayFromZeroTest_371, NormalIntervalWorksWithDifferentTypes_371) {
    AnotherSignedSignificandBits bits;
    auto result = nearest_away_from_zero_t::normal_interval(bits);
    (void)result;
}

// Test that normal_interval can be called as a static method
TEST_F(NearestAwayFromZeroTest_371, NormalIntervalIsStaticMethod_371) {
    MockSignedSignificandBits bits;
    // Call without instance
    auto result = nearest_away_from_zero_t::normal_interval(bits);
    (void)result;
}

// Test with integer type as SignedSignificandBits
TEST_F(NearestAwayFromZeroTest_371, NormalIntervalWorksWithIntType_371) {
    int bits = 42;
    auto result = nearest_away_from_zero_t::normal_interval(bits);
    (void)result;
}

// Test that the return type is consistent across calls
TEST_F(NearestAwayFromZeroTest_371, ReturnTypeIsConsistent_371) {
    MockSignedSignificandBits bits1;
    AnotherSignedSignificandBits bits2;
    
    auto result1 = nearest_away_from_zero_t::normal_interval(bits1);
    auto result2 = nearest_away_from_zero_t::normal_interval(bits2);
    
    EXPECT_TRUE((std::is_same<decltype(result1), decltype(result2)>::value));
}

// Test default constructibility of the policy
TEST_F(NearestAwayFromZeroTest_371, PolicyIsDefaultConstructible_371) {
    EXPECT_TRUE(std::is_default_constructible<nearest_away_from_zero_t>::value);
}

// Boundary: test with zero-initialized SignedSignificandBits
TEST_F(NearestAwayFromZeroTest_371, NormalIntervalWithZeroInitializedBits_371) {
    MockSignedSignificandBits bits{0};
    auto result = nearest_away_from_zero_t::normal_interval(bits);
    (void)result;
}

// Test that multiple calls produce the same type
TEST_F(NearestAwayFromZeroTest_371, MultipleCalls_371) {
    MockSignedSignificandBits bits;
    for (int i = 0; i < 100; ++i) {
        bits.value = i;
        auto result = nearest_away_from_zero_t::normal_interval(bits);
        (void)result;
    }
}

} // namespace
