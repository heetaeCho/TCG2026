#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "scantag.cpp"

#include "stream.h"



using namespace YAML;



class ScanTagHandleTest_163 : public ::testing::Test {

protected:

    std::istringstream input;

    Stream stream;

    bool canBeHandle;



    ScanTagHandleTest_163() : stream(input) {}

};



TEST_F(ScanTagHandleTest_163, NormalOperationValidHandle_163) {

    input.str("!handle");

    EXPECT_EQ(ScanTagHandle(stream, canBeHandle), "!handle");

    EXPECT_TRUE(canBeHandle);

}



TEST_F(ScanTagHandleTest_163, NormalOperationValidTag_163) {

    input.str("tag!");

    EXPECT_EQ(ScanTagHandle(stream, canBeHandle), "tag!");

    EXPECT_FALSE(canBeHandle);

}



TEST_F(ScanTagHandleTest_163, BoundaryConditionEmptyInput_163) {

    input.str("");

    EXPECT_EQ(ScanTagHandle(stream, canBeHandle), "");

    EXPECT_TRUE(canBeHandle);

}



TEST_F(ScanTagHandleTest_163, ExceptionalOperationInvalidCharacterInHandle_163) {

    input.str("handle!invalid");

    EXPECT_THROW({

        ScanTagHandle(stream, canBeHandle);

    }, ParserException);

}



TEST_F(ScanTagHandleTest_163, BoundaryConditionSingleExclamationMark_163) {

    input.str("!");

    EXPECT_EQ(ScanTagHandle(stream, canBeHandle), "!");

    EXPECT_FALSE(canBeHandle);

}



TEST_F(ScanTagHandleTest_163, NormalOperationValidWordFollowedByExclamationMark_163) {

    input.str("word!");

    EXPECT_EQ(ScanTagHandle(stream, canBeHandle), "word!");

    EXPECT_FALSE(canBeHandle);

}



TEST_F(ScanTagHandleTest_163, ExceptionalOperationInvalidCharacterInWord_163) {

    input.str("inva lid!");

    EXPECT_THROW({

        ScanTagHandle(stream, canBeHandle);

    }, ParserException);

}
