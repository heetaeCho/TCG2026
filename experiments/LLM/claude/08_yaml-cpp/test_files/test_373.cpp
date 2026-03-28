#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::detail;

// A minimal mock/stub for SignedSignificandBits to use in template invocation
struct MockSignedSignificandBits {
    int value = 0;
};

struct AnotherSignedSignificandBits {
    double data = 3.14;
};

// Test fixture
class NearestAlwaysClosedTest_373 : public ::testing::Test {
protected:
    nearest_always_closed_t instance;
};

// Test that normal_interval returns a closed interval type for a basic type
TEST_F(NearestAlwaysClosedTest_373, NormalIntervalReturnsClosedInterval_373) {
    MockSignedSignificandBits bits;
    auto result = nearest_always_closed_t::normal_interval(bits);
    // The function should return an interval_type::closed default-constructed object.
    // We verify it compiles and is callable - the return type is interval_type::closed.
    (void)result;
    SUCCEED();
}

// Test that normal_interval is constexpr-capable
TEST_F(NearestAlwaysClosedTest_373, NormalIntervalIsConstexpr_373) {
    constexpr MockSignedSignificandBits bits{};
    constexpr auto result = nearest_always_closed_t::normal_interval(bits);
    (void)result;
    SUCCEED();
}

// Test that normal_interval is noexcept
TEST_F(NearestAlwaysClosedTest_373, NormalIntervalIsNoexcept_373) {
    MockSignedSignificandBits bits;
    static_assert(noexcept(nearest_always_closed_t::normal_interval(bits)),
                  "normal_interval should be noexcept");
    SUCCEED();
}

// Test with a different SignedSignificandBits type to ensure template works generically
TEST_F(NearestAlwaysClosedTest_373, NormalIntervalWorksWithDifferentType_373) {
    AnotherSignedSignificandBits bits;
    auto result = nearest_always_closed_t::normal_interval(bits);
    (void)result;
    SUCCEED();
}

// Test that normal_interval can be called with an integer type as SignedSignificandBits
TEST_F(NearestAlwaysClosedTest_373, NormalIntervalWorksWithIntType_373) {
    int bits = 42;
    auto result = nearest_always_closed_t::normal_interval(bits);
    (void)result;
    SUCCEED();
}

// Test that the function is static and can be called without an instance
TEST_F(NearestAlwaysClosedTest_373, NormalIntervalIsStatic_373) {
    MockSignedSignificandBits bits;
    // Call directly on the type, not on an instance
    auto result = nearest_always_closed_t::normal_interval(bits);
    (void)result;
    SUCCEED();
}

// Test that multiple calls return consistent results (default-constructed closed interval)
TEST_F(NearestAlwaysClosedTest_373, NormalIntervalConsistentAcrossCalls_373) {
    MockSignedSignificandBits bits1{0};
    MockSignedSignificandBits bits2{100};
    
    auto result1 = nearest_always_closed_t::normal_interval(bits1);
    auto result2 = nearest_always_closed_t::normal_interval(bits2);
    
    // Both should be the same type and default-constructed
    static_assert(std::is_same<decltype(result1), decltype(result2)>::value,
                  "Return types should be identical regardless of input");
    SUCCEED();
}

// Boundary: test with zero-initialized struct
TEST_F(NearestAlwaysClosedTest_373, NormalIntervalWithZeroInitializedInput_373) {
    MockSignedSignificandBits bits{};
    auto result = nearest_always_closed_t::normal_interval(bits);
    (void)result;
    SUCCEED();
}

} // namespace
