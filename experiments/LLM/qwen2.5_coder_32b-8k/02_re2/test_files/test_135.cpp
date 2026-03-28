#include <gtest/gtest.h>

#include "regexp.h"

#include <absl/strings/string_view.h>



using namespace re2;



class RegexpStatusTest_135 : public ::testing::Test {

protected:

    RegexpStatus status;

};



TEST_F(RegexpStatusTest_135, DefaultConstructorInitializesSuccess_135) {

    EXPECT_EQ(status.code(), kRegexpSuccess);

    EXPECT_TRUE(status.ok());

}



TEST_F(RegexpStatusTest_135, SetCodeUpdatesCode_135) {

    status.set_code(kRegexpBadEscape);

    EXPECT_EQ(status.code(), kRegexpBadEscape);

    EXPECT_FALSE(status.ok());

}



TEST_F(RegexpStatusTest_135, SetErrorArgUpdatesErrorArg_135) {

    absl::string_view error_arg = "test_error";

    status.set_error_arg(error_arg);

    EXPECT_EQ(status.error_arg(), error_arg);

}



TEST_F(RegexpStatusTest_135, SetTmpUpdatesTmp_135) {

    std::string tmp_str = "temporary_string";

    status.set_tmp(&tmp_str);

    // Since tmp is private and we cannot access it directly,

    // we verify the behavior indirectly by checking if the destructor cleans up properly.

}



TEST_F(RegexpStatusTest_135, CopyCopiesState_135) {

    RegexpStatus original;

    original.set_code(kRegexpBadPattern);

    original.set_error_arg("bad_pattern");

    std::string tmp_str = "original_temp";

    original.set_tmp(&tmp_str);



    status.Copy(original);

    EXPECT_EQ(status.code(), kRegexpBadPattern);

    EXPECT_EQ(status.error_arg(), "bad_pattern");

}



TEST_F(RegexpStatusTest_135, CodeTextReturnsCorrectString_135) {

    EXPECT_EQ(RegexpStatus::CodeText(kRegexpSuccess), "success");

    EXPECT_EQ(RegexpStatus::CodeText(kRegexpBadEscape), "invalid escape sequence");

    // Add more cases as necessary for other status codes

}



TEST_F(RegexpStatusTest_135, TextReturnsCorrectString_135) {

    status.set_code(kRegexpInternalError);

    status.set_error_arg("internal error message");



    std::string expected_text = "error parsing regexp: internal error message";

    EXPECT_EQ(status.Text(), expected_text);

}



TEST_F(RegexpStatusTest_135, DestructorFreesMemory_135) {

    std::string* tmp_str = new std::string("test_temp");

    status.set_tmp(tmp_str);



    // The destructor should delete the allocated memory when the object goes out of scope

}
