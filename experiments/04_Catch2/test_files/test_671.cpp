#include <gtest/gtest.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara;



class ParserTest : public ::testing::Test {

protected:

    Parser parser;

};



TEST_F(ParserTest_671, ValidateReturnsOkWhenNoOptionsOrArgs_671) {

    auto result = parser.validate();

    EXPECT_TRUE(result);

}



TEST_F(ParserTest_671, ValidatePropagatesErrorFromOption_671) {

    bool dummyFlag = false;

    Opt option(dummyFlag);

    EXPECT_CALL(option, validate()).WillOnce(testing::Return(Detail::Result::logicError("test error")));

    

    parser | option;

    auto result = parser.validate();

    EXPECT_FALSE(result);

    EXPECT_EQ(result.errorMessage(), "test error");

}



TEST_F(ParserTest_671, ValidatePropagatesErrorFromArg_671) {

    bool dummyFlag = false;

    Opt option(dummyFlag);

    Arg arg(dummyFlag);

    EXPECT_CALL(arg, validate()).WillOnce(testing::Return(Detail::Result::runtimeError("test error")));

    

    parser | option | arg;

    auto result = parser.validate();

    EXPECT_FALSE(result);

    EXPECT_EQ(result.errorMessage(), "test error");

}



TEST_F(ParserTest_671, ValidateMultipleOptionsAndArgsAllValid_671) {

    bool dummyFlag1 = false;

    bool dummyFlag2 = false;

    Opt option1(dummyFlag1);

    Opt option2(dummyFlag2);

    Arg arg1(dummyFlag1);

    Arg arg2(dummyFlag2);



    EXPECT_CALL(option1, validate()).WillOnce(testing::Return(Detail::Result::ok()));

    EXPECT_CALL(option2, validate()).WillOnce(testing::Return(Detail::Result::ok()));

    EXPECT_CALL(arg1, validate()).WillOnce(testing::Return(Detail::Result::ok()));

    EXPECT_CALL(arg2, validate()).WillOnce(testing::Return(Detail::Result::ok()));



    parser | option1 | option2 | arg1 | arg2;

    auto result = parser.validate();

    EXPECT_TRUE(result);

}



TEST_F(ParserTest_671, ValidateMultipleOptionsAndArgsWithOneInvalid_671) {

    bool dummyFlag1 = false;

    bool dummyFlag2 = false;

    Opt option1(dummyFlag1);

    Opt option2(dummyFlag2);

    Arg arg1(dummyFlag1);

    Arg arg2(dummyFlag2);



    EXPECT_CALL(option1, validate()).WillOnce(testing::Return(Detail::Result::ok()));

    EXPECT_CALL(option2, validate()).WillOnce(testing::Return(Detail::Result::logicError("test error")));

    EXPECT_CALL(arg1, validate()).WillOnce(testing::Return(Detail::Result::ok()));

    EXPECT_CALL(arg2, validate()).WillOnce(testing::Return(Detail::Result::ok()));



    parser | option1 | option2 | arg1 | arg2;

    auto result = parser.validate();

    EXPECT_FALSE(result);

    EXPECT_EQ(result.errorMessage(), "test error");

}

```


