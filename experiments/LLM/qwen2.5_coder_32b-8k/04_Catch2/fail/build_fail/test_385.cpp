#include <gtest/gtest.h>

#include "catch2/internal/catch_clara.hpp"

#include <string>



using namespace Catch::Clara;

using namespace Catch::Clara::Detail;



class ParserBaseTest_385 : public ::testing::Test {

protected:

    class MockParser : public ParserBase {

    public:

        MOCK_CONST_METHOD0(validate, Result());

        MOCK_CONST_METHOD1(parse, InternalParseResult(const std::string&, TokenStream));

        MOCK_CONST_METHOD0(cardinality, size_t());

    };



    std::unique_ptr<MockParser> mockParser;



    void SetUp() override {

        mockParser = std::make_unique<MockParser>();

    }

};



TEST_F(ParserBaseTest_385, ValidateReturnsOk_385) {

    EXPECT_CALL(*mockParser, validate()).WillOnce(::testing::Return(Result::ok()));

    auto result = mockParser->validate();

    EXPECT_TRUE(result);

}



TEST_F(ParserBaseTest_385, ValidateReturnsLogicError_385) {

    EXPECT_CALL(*mockParser, validate()).WillOnce(::testing::Return(BasicResult<void>::logicError("Logic Error")));

    auto result = mockParser->validate();

    EXPECT_FALSE(result);

    EXPECT_EQ(result.errorMessage(), "Logic Error");

}



TEST_F(ParserBaseTest_385, ValidateReturnsRuntimeError_385) {

    EXPECT_CALL(*mockParser, validate()).WillOnce(::testing::Return(BasicResult<void>::runtimeError("Runtime Error")));

    auto result = mockParser->validate();

    EXPECT_FALSE(result);

    EXPECT_EQ(result.errorMessage(), "Runtime Error");

}



TEST_F(ParserBaseTest_385, ParseWithExeNameAndTokensReturnsDefault_385) {

    TokenStream tokens;

    InternalParseResult expectedResult; // Assuming default constructed is expected

    EXPECT_CALL(*mockParser, parse(::testing::_, ::testing::_)).WillOnce(::testing::Return(expectedResult));

    auto result = mockParser->parse("exeName", tokens);

    EXPECT_EQ(result, expectedResult);

}



TEST_F(ParserBaseTest_385, ParseWithArgsReturnsDefault_385) {

    Args args;

    InternalParseResult expectedResult; // Assuming default constructed is expected

    EXPECT_CALL(*mockParser, parse(::testing::_)).WillOnce(::testing::Return(expectedResult));

    auto result = mockParser->parse(args);

    EXPECT_EQ(result, expectedResult);

}



TEST_F(ParserBaseTest_385, CardinalityReturnsZero_385) {

    EXPECT_CALL(*mockParser, cardinality()).WillOnce(::testing::Return(0));

    size_t card = mockParser->cardinality();

    EXPECT_EQ(card, 0);

}



TEST_F(ParserBaseTest_385, CardinalityReturnsNonZero_385) {

    EXPECT_CALL(*mockParser, cardinality()).WillOnce(::testing::Return(1));

    size_t card = mockParser->cardinality();

    EXPECT_NE(card, 0);

}
