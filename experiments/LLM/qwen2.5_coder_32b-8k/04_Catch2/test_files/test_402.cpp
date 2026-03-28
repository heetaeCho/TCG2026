#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;



// Mock class to simulate a derived type of ComposableParserImpl

class MockDerived : public ComposableParserImpl<MockDerived> {

public:

    MOCK_METHOD1(operator|, Parser(const Parser& other));

};



// Test fixture for testing ComposableParserImpl

class ComposableParserImplTest_402 : public ::testing::Test {

protected:

    MockDerived mockDerived;

};



// Test normal operation of operator|

TEST_F(ComposableParserImplTest_402, OperatorPipe_NormalOperation_402) {

    Parser otherParser;

    EXPECT_CALL(mockDerived, operator|(otherParser)).WillOnce(::testing::Return(Parser()));

    

    auto result = mockDerived | otherParser;

}



// Test boundary condition with empty parser

TEST_F(ComposableParserImplTest_402, OperatorPipe_EmptyParser_402) {

    Parser emptyParser;

    EXPECT_CALL(mockDerived, operator|(emptyParser)).WillOnce(::testing::Return(Parser()));

    

    auto result = mockDerived | emptyParser;

}



// Test verification of external interactions

TEST_F(ComposableParserImplTest_402, OperatorPipe_VerifyInteraction_402) {

    Parser otherParser;

    EXPECT_CALL(mockDerived, operator|(otherParser)).WillOnce(::testing::Return(Parser()));

    

    mockDerived | otherParser;

}

```


