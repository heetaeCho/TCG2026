#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;



// Mock for LambdaInvoker to verify interactions with it.

template <typename ReturnType>

struct MockLambdaInvoker {

    MOCK_STATIC_METHOD1(invoke, ParserResult(typename UnaryLambdaTraits<L>::ReturnType));

};



// Test Fixture

class BoundFlagLambdaTest_384 : public ::testing::Test {

protected:

    struct DummyLambda {

        auto operator()(bool flag) -> bool { return flag; }

    };



    DummyLambda dummyLambda;

    BoundFlagLambda<DummyLambda> boundFlagLambda;



    BoundFlagLambdaTest_384() : boundFlagLambda(dummyLambda) {}

};



// Test normal operation

TEST_F(BoundFlagLambdaTest_384, SetFlag_ReturnsParserResult_384) {

    EXPECT_CALL(MockLambdaInvoker<bool>, invoke(testing::_)).Times(1);

    auto result = boundFlagLambda.setFlag(true);

    EXPECT_EQ(result, ParserResult{});

}



// Test boundary conditions

TEST_F(BoundFlagLambdaTest_384, SetFlag_False_ReturnsParserResult_384) {

    EXPECT_CALL(MockLambdaInvoker<bool>, invoke(testing::_)).Times(1);

    auto result = boundFlagLambda.setFlag(false);

    EXPECT_EQ(result, ParserResult{});

}



// Test external interactions

TEST_F(BoundFlagLambdaTest_384, SetFlag_CallsLambdaInvokerWithTrue_384) {

    EXPECT_CALL(MockLambdaInvoker<bool>, invoke(true)).Times(1);

    boundFlagLambda.setFlag(true);

}



TEST_F(BoundFlagLambdaTest_384, SetFlag_CallsLambdaInvokerWithFalse_384) {

    EXPECT_CALL(MockLambdaInvoker<bool>, invoke(false)).Times(1);

    boundFlagLambda.setFlag(false);

}

```


