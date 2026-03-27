#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/re2/re2/regexp.h"



namespace re2 {



class RegexpStatusTest : public ::testing::Test {

protected:

    RegexpStatus status_;

};



TEST_F(RegexpStatusTest_137, DefaultConstructor_SetsCodeToSuccess_137) {

    EXPECT_EQ(status_.code(), kRegexpSuccess);

}



TEST_F(RegexpStatusTest_137, SetCode_ChangesStatusCode_137) {

    status_.set_code(kRegexpBadEscape);

    EXPECT_EQ(status_.code(), kRegexpBadEscape);

}



TEST_F(RegexpStatusTest_137, SetErrorArg_StoresErrorArgument_137) {

    absl::string_view error_arg = "Invalid character";

    status_.set_error_arg(error_arg);

    EXPECT_EQ(status_.error_arg(), error_arg);

}



TEST_F(RegexpStatusTest_137, Ok_ReturnsTrueForSuccessCode_137) {

    EXPECT_TRUE(status_.ok());

}



TEST_F(RegexpStatusTest_137, Ok_ReturnsFalseForErrorCode_137) {

    status_.set_code(kRegexpBadEscape);

    EXPECT_FALSE(status_.ok());

}



TEST_F(RegexpStatusTest_137, CodeText_ReturnsCorrectStringForSuccess_137) {

    EXPECT_EQ(status_.CodeText(kRegexpSuccess), "success");

}



TEST_F(RegexpStatusTest_137, CodeText_ReturnsCorrectStringForErrorCode_137) {

    EXPECT_EQ(status_.CodeText(kRegexpBadEscape), "invalid escape sequence");

}



TEST_F(RegexpStatusTest_137, Text_ReturnsSuccessMessageForSuccessCode_137) {

    EXPECT_EQ(status_.Text(), "success");

}



TEST_F(RegexpStatusTest_137, Text_ReturnsErrorMessageForErrorCode_137) {

    status_.set_code(kRegexpBadEscape);

    status_.set_error_arg("Invalid character 'x'");

    EXPECT_EQ(status_.Text(), "invalid escape sequence: Invalid character 'x'");

}



TEST_F(RegexpStatusTest_137, Copy_CopiesAllFields_137) {

    RegexpStatus original;

    original.set_code(kRegexpBadEscape);

    absl::string_view error_arg = "Invalid character";

    original.set_error_arg(error_arg);



    status_.Copy(original);

    EXPECT_EQ(status_.code(), kRegexpBadEscape);

    EXPECT_EQ(status_.error_arg(), error_arg);

}



}  // namespace re2
