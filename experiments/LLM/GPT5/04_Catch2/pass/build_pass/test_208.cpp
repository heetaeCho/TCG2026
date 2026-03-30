// File: within_rel_factory_test_208.cpp
#include <gtest/gtest.h>
#include <type_traits>

// Assume the real project exposes this header;
// if your include path differs, adjust accordingly.
#include "catch2/matchers/catch_matchers_floating_point.hpp"

using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinRelMatcher;

class WithinRelFactoryTest_208 : public ::testing::Test {};

// Verifies that calling the float overload returns the documented matcher type.
TEST_F(WithinRelFactoryTest_208, ReturnsWithinRelMatcherType_208) {
    using T = decltype(WithinRel(1.0f, 0.1f));
    static_assert(std::is_same<T, WithinRelMatcher>::value,
                  "WithinRel(float, float) must return WithinRelMatcher");
    SUCCEED();
}

// Normal operation: constructing with typical values should not throw.
TEST_F(WithinRelFactoryTest_208, Construct_NoThrow_NormalInputs_208) {
    EXPECT_NO_THROW({
        auto m = WithinRel(123.45f, 0.01f);
        (void)m;
    });
}

// Boundary condition: eps == 0.0f should at least be constructible or surface an error via exceptions.
// We only assert construction does not unexpectedly throw at the factory level.
TEST_F(WithinRelFactoryTest_208, Construct_NoThrow_EpsZero_208) {
    EXPECT_NO_THROW({
        auto m = WithinRel(1.0f, 0.0f);
        (void)m;
    });
}

// Boundary/extreme values: targets at infinities and NaN should not cause construction-time crashes.
TEST_F(WithinRelFactoryTest_208, Construct_NoThrow_InfiniteAndNaNTargets_208) {
    const float inf = std::numeric_limits<float>::infinity();
    const float nan = std::numeric_limits<float>::quiet_NaN();

    EXPECT_NO_THROW({ auto m = WithinRel(inf, 0.1f); (void)m; });
    EXPECT_NO_THROW({ auto m = WithinRel(-inf, 0.1f); (void)m; });
    EXPECT_NO_THROW({ auto m = WithinRel(nan, 0.1f); (void)m; });
}

// API surface sanity: the returned matcher should be copyable and movable as a regular value type.
TEST_F(WithinRelFactoryTest_208, Matcher_CopyMoveSemantics_208) {
    auto m = WithinRel(10.0f, 0.05f);

    // Copy
    WithinRelMatcher copy(m);
    (void)copy;

    // Move
    WithinRelMatcher moved(std::move(m));
    (void)moved;

    SUCCEED();
}
