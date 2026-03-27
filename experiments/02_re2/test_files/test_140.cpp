#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"



namespace re2 {



class RegexpStatusTest : public ::testing::Test {

protected:

    RegexpStatus status;

};



TEST_F(RegexpStatusTest_140, DefaultConstructor_SetsCodeToSuccess_140) {

    EXPECT_EQ(status.code(), kRegexpSuccess);

}



TEST_F(RegexpStatusTest_140, DefaultConstructor_SetsErrorArgToEmpty_140) {

    EXPECT_TRUE(status.error_arg().empty());

}



TEST_F(RegexpStatusTest_140, SetCode_ChangesStatusCode_140) {

    status.set_code(kRegexpBadEscape);

    EXPECT_EQ(status.code(), kRegexpBadEscape);

}



TEST_F(RegexpStatusTest_140, SetErrorArg_ChangesErrorArgument_140) {

    status.set_error_arg("test error");

    EXPECT_EQ(status.error_arg(), "test error");

}



TEST_F(RegexpStatusTest_140, Ok_ReturnsTrueForSuccessCode_140) {

    EXPECT_TRUE(status.ok());

}



TEST_F(RegexpStatusTest_140, Ok_ReturnsFalseForErrorCode_140) {

    status.set_code(kRegexpBadEscape);

    EXPECT_FALSE(status.ok());

}



TEST_F(RegexpStatusTest_140, Text_ReturnsCodeTextForSuccess_140) {

    EXPECT_EQ(status.Text(), "success");

}



TEST_F(RegexpStatusTest_140, Text_ReturnsCodeTextForErrorCode_140) {

    status.set_code(kRegexpBadEscape);

    EXPECT_EQ(status.Text(), "invalid escape sequence: \\e");

}



TEST_F(RegexpStatusTest_140, Copy_CopiesStatusCodeAndErrorArg_140) {

    RegexpStatus other;

    other.set_code(kRegexpInternalError);

    other.set_error_arg("internal error");



    status.Copy(other);

    EXPECT_EQ(status.code(), kRegexpInternalError);

    EXPECT_EQ(status.error_arg(), "internal error");

}



}  // namespace re2
