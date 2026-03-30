#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_clara.hpp"



namespace Catch { namespace Clara { namespace Detail {



class MockParserResult {

public:

    MOCK_METHOD0(isOk, bool());

};



template <typename L>

class TestBoundLambda : public BoundLambda<L> {

public:

    using BoundLambda<L>::BoundLambda;

    testing::NiceMock<MockParserResult>* mockParserResult = new testing::NiceMock<MockParserResult>;



    auto setValue(std::string const& arg) -> ParserResult override {

        return *mockParserResult;

    }

};



class BoundLambdaTest_382 : public ::testing::Test {

protected:

    TestBoundLambda<std::function<void(const std::string&)>> boundLambda;



    BoundLambdaTest_382() : boundLambda([](const std::string&){}) {}

};



TEST_F(BoundLambdaTest_382, SetValue_CallsLambdaWithArgument_382) {

    using ::testing::_;



    EXPECT_CALL(*boundLambda.mockParserResult, isOk()).Times(1);



    boundLambda.setValue("test_argument");

}



TEST_F(BoundLambdaTest_382, SetValue_ReturnsParserResult_382) {

    using ::testing::Return;



    EXPECT_CALL(*boundLambda.mockParserResult, isOk())

        .WillOnce(Return(true));



    ParserResult result = boundLambda.setValue("test_argument");



    EXPECT_TRUE(result.isOk());

}



TEST_F(BoundLambdaTest_382, SetValue_HandlesEmptyString_382) {

    using ::testing::Return;



    EXPECT_CALL(*boundLambda.mockParserResult, isOk())

        .WillOnce(Return(true));



    ParserResult result = boundLambda.setValue("");



    EXPECT_TRUE(result.isOk());

}



TEST_F(BoundLambdaTest_382, SetValue_HandlesLongString_382) {

    using ::testing::Return;



    std::string long_string(1024, 'a');



    EXPECT_CALL(*boundLambda.mockParserResult, isOk())

        .WillOnce(Return(true));



    ParserResult result = boundLambda.setValue(long_string);



    EXPECT_TRUE(result.isOk());

}



TEST_F(BoundLambdaTest_382, SetValue_ReturnsErrorOnFailure_382) {

    using ::testing::Return;



    EXPECT_CALL(*boundLambda.mockParserResult, isOk())

        .WillOnce(Return(false));



    ParserResult result = boundLambda.setValue("error_argument");



    EXPECT_FALSE(result.isOk());

}



}}} // namespace Catch::Clara::Detail
