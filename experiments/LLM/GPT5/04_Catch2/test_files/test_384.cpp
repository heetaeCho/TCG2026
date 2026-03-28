// File: tests/BoundFlagLambda_setFlag_384_test.cpp

#include <gtest/gtest.h>
#include <vector>
#include <cstddef>

// Include the header as provided in the prompt (adjust include path to your tree)
#include "Catch2/src/catch2/internal/catch_clara.hpp"

using Catch::Clara::Detail::BoundFlagLambda;

// Fixture kept minimal (no shared state required)
class BoundFlagLambdaTest_384 : public ::testing::Test {};

// [Normal] setFlag forwards `true` to a void-returning lambda and reports success
TEST_F(BoundFlagLambdaTest_384, CallsVoidLambdaWithTrue_384) {
    std::vector<bool> seen;
    auto lambda = [&](bool f) -> void { seen.push_back(f); };

    BoundFlagLambda<decltype(lambda)> bound(lambda);

    auto res = bound.setFlag(true);

    ASSERT_EQ(seen.size(), 1u);
    EXPECT_TRUE(seen[0]);           // external interaction verified
    EXPECT_TRUE(static_cast<bool>(res)); // observable success (no internals relied upon)
}

// [Normal] setFlag forwards `false` to a void-returning lambda and reports success
TEST_F(BoundFlagLambdaTest_384, CallsVoidLambdaWithFalse_384) {
    std::vector<bool> seen;
    auto lambda = [&](bool f) -> void { seen.push_back(f); };

    BoundFlagLambda<decltype(lambda)> bound(lambda);

    auto res = bound.setFlag(false);

    ASSERT_EQ(seen.size(), 1u);
    EXPECT_FALSE(seen[0]);          // external interaction verified
    EXPECT_TRUE(static_cast<bool>(res));
}

// [Boundary] Works across multiple invocations, preserving each flag value in order
TEST_F(BoundFlagLambdaTest_384, ForwardsFlagAcrossMultipleCalls_384) {
    std::vector<bool> seen;
    auto lambda = [&](bool f) -> void { seen.push_back(f); };

    BoundFlagLambda<decltype(lambda)> bound(lambda);

    EXPECT_TRUE(static_cast<bool>(bound.setFlag(true)));
    EXPECT_TRUE(static_cast<bool>(bound.setFlag(false)));
    EXPECT_TRUE(static_cast<bool>(bound.setFlag(true)));

    ASSERT_EQ(seen.size(), 3u);
    EXPECT_TRUE(seen[0]);
    EXPECT_FALSE(seen[1]);
    EXPECT_TRUE(seen[2]);
}

// [Interaction] Lambda is invoked exactly once per setFlag() call
TEST_F(BoundFlagLambdaTest_384, InvokesExactlyOncePerCall_384) {
    std::size_t callCount = 0;
    auto lambda = [&](bool) -> void { ++callCount; };

    BoundFlagLambda<decltype(lambda)> bound(lambda);

    EXPECT_TRUE(static_cast<bool>(bound.setFlag(true)));
    EXPECT_EQ(callCount, 1u);

    EXPECT_TRUE(static_cast<bool>(bound.setFlag(false)));
    EXPECT_EQ(callCount, 2u);
}

// [Observable Error Path] Bool-returning lambda: `false` maps to a non-success result,
// while `true` maps to success (relies only on ParserResult's boolean observability)
TEST_F(BoundFlagLambdaTest_384, PropagatesBoolReturnToParserResult_384) {
    // Lambda returning bool (no reliance on ParserResult internals)
    auto lambdaTrue  = [&](bool) -> bool { return true;  };
    auto lambdaFalse = [&](bool) -> bool { return false; };

    BoundFlagLambda<decltype(lambdaTrue)> boundTrue(lambdaTrue);
    BoundFlagLambda<decltype(lambdaFalse)> boundFalse(lambdaFalse);

    EXPECT_TRUE(static_cast<bool>(boundTrue.setFlag(true)));
    EXPECT_FALSE(static_cast<bool>(boundFalse.setFlag(true)));
}
