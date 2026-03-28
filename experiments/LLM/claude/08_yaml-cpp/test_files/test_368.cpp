#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;

// A mock/stub for SignedSignificandBits to use as template parameter
struct MockSignedSignificandBits {
    // Minimal stub - we only need it as a parameter type
};

// Another type to test template generality
struct AnotherSignedSignificandBits {
    int value = 42;
};

// Test fixture
class NearestTowardZeroTest_368 : public ::testing::Test {
protected:
    nearest_toward_zero policy_;
};

// Test that normal_interval returns the correct interval type
TEST_F(NearestTowardZeroTest_368, NormalIntervalReturnsRightClosedLeftOpen_368) {
    MockSignedSignificandBits bits;
    auto result = nearest_toward_zero::normal_interval(bits);
    
    // Verify the return type is interval_type::right_closed_left_open
    static_assert(
        std::is_same<
            decltype(result),
            YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type::right_closed_left_open
        >::value,
        "normal_interval should return interval_type::right_closed_left_open"
    );
    
    // If we got here, the function returned successfully
    SUCCEED();
}

// Test that normal_interval is constexpr
TEST_F(NearestTowardZeroTest_368, NormalIntervalIsConstexpr_368) {
    // This should compile if normal_interval is truly constexpr
    constexpr auto result = nearest_toward_zero::normal_interval(MockSignedSignificandBits{});
    (void)result;
    SUCCEED();
}

// Test that normal_interval is noexcept
TEST_F(NearestTowardZeroTest_368, NormalIntervalIsNoexcept_368) {
    MockSignedSignificandBits bits;
    static_assert(
        noexcept(nearest_toward_zero::normal_interval(bits)),
        "normal_interval should be noexcept"
    );
    SUCCEED();
}

// Test with a different SignedSignificandBits type to verify template works generically
TEST_F(NearestTowardZeroTest_368, NormalIntervalWorksWithDifferentTypes_368) {
    AnotherSignedSignificandBits bits;
    auto result = nearest_toward_zero::normal_interval(bits);
    
    static_assert(
        std::is_same<
            decltype(result),
            YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type::right_closed_left_open
        >::value,
        "normal_interval should return right_closed_left_open for any SignedSignificandBits type"
    );
    SUCCEED();
}

// Test that normal_interval is a static member function (can be called without instance)
TEST_F(NearestTowardZeroTest_368, NormalIntervalIsStatic_368) {
    MockSignedSignificandBits bits;
    // Call as a static function (not on an instance)
    auto result = nearest_toward_zero::normal_interval(bits);
    (void)result;
    SUCCEED();
}

// Test that the return type is default constructible (right_closed_left_open is a struct)
TEST_F(NearestTowardZeroTest_368, ReturnTypeIsDefaultConstructible_368) {
    using ReturnType = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type::right_closed_left_open;
    static_assert(std::is_default_constructible<ReturnType>::value,
                  "right_closed_left_open should be default constructible");
    SUCCEED();
}

// Test that nearest_toward_zero is default constructible
TEST_F(NearestTowardZeroTest_368, PolicyIsDefaultConstructible_368) {
    static_assert(std::is_default_constructible<nearest_toward_zero>::value,
                  "nearest_toward_zero should be default constructible");
    nearest_toward_zero ntz;
    (void)ntz;
    SUCCEED();
}

// Test with an integer type as SignedSignificandBits (boundary: primitive type)
TEST_F(NearestTowardZeroTest_368, NormalIntervalWorksWithPrimitiveType_368) {
    int bits = 0;
    auto result = nearest_toward_zero::normal_interval(bits);
    static_assert(
        std::is_same<
            decltype(result),
            YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type::right_closed_left_open
        >::value,
        "normal_interval should work with primitive types too"
    );
    SUCCEED();
}

// Test that multiple calls return the same type (consistency)
TEST_F(NearestTowardZeroTest_368, MultipleCallsReturnSameType_368) {
    MockSignedSignificandBits bits1;
    AnotherSignedSignificandBits bits2;
    
    auto result1 = nearest_toward_zero::normal_interval(bits1);
    auto result2 = nearest_toward_zero::normal_interval(bits2);
    
    static_assert(std::is_same<decltype(result1), decltype(result2)>::value,
                  "All calls should return the same type regardless of input type");
    SUCCEED();
}

} // namespace
