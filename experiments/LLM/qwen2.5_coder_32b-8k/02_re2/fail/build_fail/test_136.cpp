#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"



using namespace re2;



class RegexpStatusTest : public ::testing::Test {

protected:

    RegexpStatus status;

};



TEST_F(RegexpStatusTest_136, DefaultConstructorInitializesSuccessCode_136) {

    EXPECT_EQ(status.code(), kRegexpSuccess);

}



TEST_F(RegexpStatusTest_136, SetCodeUpdatesStatusCode_136) {

    status.set_code(kRegexpBadEscape);

    EXPECT_EQ(status.code(), kRegexpBadEscape);

}



TEST_F(RegexpStatusTest_136, SetErrorArgStoresArgument_136) {

    absl::string_view error_arg = "test_error";

    status.set_error_arg(error_arg);

    EXPECT_EQ(status.error_arg(), error_arg);

}



TEST_F(RegexpStatusTest_136, OkReturnsTrueForSuccessCode_136) {

    EXPECT_TRUE(status.ok());

}



TEST_F(RegexpStatusTest_136, OkReturnsFalseForErrorCode_136) {

    status.set_code(kRegexpBadEscape);

    EXPECT_FALSE(status.ok());

}



TEST_F(RegexpStatusTest_136, CodeTextReturnsCorrectStringForSuccessCode_136) {

    EXPECT_EQ(RegexpStatus::CodeText(kRegexpSuccess), "success");

}



TEST_F(RegexpStatusTest_136, CodeTextReturnsCorrectStringForErrorCode_136) {

    EXPECT_EQ(RegexpStatus::CodeText(kRegexpBadEscape), "invalid escape sequence");

}



TEST_F(RegexpStatusTest_136, TextReturnsEmptyForSuccessCode_136) {

    EXPECT_TRUE(status.Text().empty());

}



TEST_F(RegexpStatusTest_136, TextReturnsErrorStringForErrorCode_136) {

    status.set_code(kRegexpBadEscape);

    status.set_error_arg("test_error");

    EXPECT_EQ(status.Text(), "invalid escape sequence: test_error");

}



TEST_F(RegexpStatusTest_136, CopyUpdatesAllFields_136) {

    RegexpStatus source;

    source.set_code(kRegexpBadCharClass);

    source.set_error_arg("bad_char_class_error");

    std::string tmp = "temporary";

    source.set_tmp(&tmp);



    status.Copy(source);

    EXPECT_EQ(status.code(), kRegexpBadCharClass);

    EXPECT_EQ(status.error_arg(), "bad_char_class_error");

    EXPECT_EQ(status.tmp_, &tmp);

}
