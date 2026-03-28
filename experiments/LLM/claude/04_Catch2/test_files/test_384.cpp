#include <gtest/gtest.h>
#include <catch2/internal/catch_clara.hpp>

using namespace Catch::Clara::Detail;

class BoundFlagLambdaTest_384 : public ::testing::Test {
protected:
};

// Test that setFlag with true passes true to the lambda
TEST_F(BoundFlagLambdaTest_384, SetFlagTruePassesTrueToLambda_384) {
    bool receivedValue = false;
    auto lambda = [&receivedValue](bool flag) {
        receivedValue = flag;
    };
    BoundFlagLambda<decltype(lambda)> bound(lambda);
    
    auto result = bound.setFlag(true);
    
    EXPECT_TRUE(receivedValue);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that setFlag with false passes false to the lambda
TEST_F(BoundFlagLambdaTest_384, SetFlagFalsePassesFalseToLambda_384) {
    bool receivedValue = true;
    auto lambda = [&receivedValue](bool flag) {
        receivedValue = flag;
    };
    BoundFlagLambda<decltype(lambda)> bound(lambda);
    
    auto result = bound.setFlag(false);
    
    EXPECT_FALSE(receivedValue);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that lambda is invoked exactly once per setFlag call
TEST_F(BoundFlagLambdaTest_384, LambdaInvokedOncePerCall_384) {
    int callCount = 0;
    auto lambda = [&callCount](bool) {
        callCount++;
    };
    BoundFlagLambda<decltype(lambda)> bound(lambda);
    
    bound.setFlag(true);
    EXPECT_EQ(callCount, 1);
    
    bound.setFlag(false);
    EXPECT_EQ(callCount, 2);
}

// Test with a lambda that returns void (should produce Ok result)
TEST_F(BoundFlagLambdaTest_384, VoidReturningLambdaProducesOkResult_384) {
    auto lambda = [](bool) {
        // void return
    };
    BoundFlagLambda<decltype(lambda)> bound(lambda);
    
    auto result = bound.setFlag(true);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test with a lambda that modifies external state based on flag value
TEST_F(BoundFlagLambdaTest_384, LambdaModifiesExternalStateBasedOnFlag_384) {
    std::string state;
    auto lambda = [&state](bool flag) {
        state = flag ? "enabled" : "disabled";
    };
    BoundFlagLambda<decltype(lambda)> bound(lambda);
    
    bound.setFlag(true);
    EXPECT_EQ(state, "enabled");
    
    bound.setFlag(false);
    EXPECT_EQ(state, "disabled");
}

// Test multiple calls with same flag value
TEST_F(BoundFlagLambdaTest_384, MultipleCallsWithSameFlag_384) {
    int trueCount = 0;
    auto lambda = [&trueCount](bool flag) {
        if (flag) trueCount++;
    };
    BoundFlagLambda<decltype(lambda)> bound(lambda);
    
    bound.setFlag(true);
    bound.setFlag(true);
    bound.setFlag(true);
    
    EXPECT_EQ(trueCount, 3);
}

// Test that setFlag returns ParserResult indicating success for well-behaved lambda
TEST_F(BoundFlagLambdaTest_384, ReturnsSuccessfulParserResult_384) {
    auto lambda = [](bool) {};
    BoundFlagLambda<decltype(lambda)> bound(lambda);
    
    auto resultTrue = bound.setFlag(true);
    auto resultFalse = bound.setFlag(false);
    
    EXPECT_TRUE(static_cast<bool>(resultTrue));
    EXPECT_TRUE(static_cast<bool>(resultFalse));
}

// Test with lambda that captures by value
TEST_F(BoundFlagLambdaTest_384, LambdaWithValueCapture_384) {
    bool called = false;
    auto lambda = [&called](bool flag) {
        called = true;
    };
    BoundFlagLambda<decltype(lambda)> bound(lambda);
    
    bound.setFlag(false);
    EXPECT_TRUE(called);
}
