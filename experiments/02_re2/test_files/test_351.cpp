#include <gtest/gtest.h>

#include "re2/regexp.h"



using namespace re2;



class RegexpStatusTest_351 : public ::testing::Test {

protected:

    RegexpStatus status;

};



TEST_F(RegexpStatusTest_351, DefaultConstructorInitializesToSuccess_351) {

    EXPECT_EQ(status.code(), kRegexpSuccess);

    EXPECT_TRUE(status.ok());

    EXPECT_EQ(status.Text(), "success");

}



TEST_F(RegexpStatusTest_351, SetCodeUpdatesCode_351) {

    status.set_code(kRegexpBadEscape);

    EXPECT_EQ(status.code(), kRegexpBadEscape);

    EXPECT_FALSE(status.ok());

}



TEST_F(RegexpStatusTest_351, SetErrorArgUpdatesErrorArgument_351) {

    status.set_error_arg("test error");

    EXPECT_EQ(status.error_arg(), "test error");

}



TEST_F(RegexpStatusTest_351, TextIncludesErrorCodeAndArgument_351) {

    status.set_code(kRegexpBadEscape);

    status.set_error_arg("test error");

    EXPECT_EQ(status.Text(), "bad escape: test error");

}



TEST_F(RegexpStatusTest_351, CopyFunctionCopiesValues_351) {

    RegexpStatus other;

    other.set_code(kRegexpCompileError);

    other.set_error_arg("compile failed");



    status.Copy(other);



    EXPECT_EQ(status.code(), kRegexpCompileError);

    EXPECT_EQ(status.error_arg(), "compile failed");

}



TEST_F(RegexpStatusTest_351, CodeTextReturnsCorrectStringForSuccess_351) {

    EXPECT_EQ(RegexpStatus::CodeText(kRegexpSuccess), "success");

}



TEST_F(RegexpStatusTest_351, CodeTextReturnsCorrectStringForBadEscape_351) {

    EXPECT_EQ(RegexpStatus::CodeText(kRegexpBadEscape), "bad escape");

}



TEST_F(RegexpStatusTest_351, CodeTextReturnsCorrectStringForCompileError_351) {

    EXPECT_EQ(RegexpStatus::CodeText(kRegexpCompileError), "compile error");

}
