#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;

using namespace Catch::Clara;



// Mock lambda function for testing

struct MockLambda {

    MOCK_METHOD1(operator(), void(int));

};



TEST_F(InvokeTest_380, InvokeWithValidLambda_ReturnsMatched_380) {

    MockLambda mockLambda;

    EXPECT_CALL(mockLambda, operator()(42));



    auto result = invoke(mockLambda, 42);

    ASSERT_TRUE(result);

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(InvokeTest_380, InvokeWithNoOpLambda_ReturnsMatched_380) {

    auto noOpLambda = [](int){};

    auto result = invoke(noOpLambda, 42);

    ASSERT_TRUE(result);

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



// No exceptional or error cases are observable through the provided interface

// as the lambda is expected to not throw exceptions and the function always returns ParserResult::ok.

```


