#include <gtest/gtest.h>

#include "re2/regexp.h"



namespace {



class RegexpStatusTest_139 : public ::testing::Test {

protected:

    re2::RegexpStatus status_;

};



TEST_F(RegexpStatusTest_139, DefaultConstructorSetsSuccessCode_139) {

    EXPECT_EQ(status_.code(), re2::kRegexpSuccess);

}



TEST_F(RegexpStatusTest_139, SetCodeUpdatesCode_139) {

    status_.set_code(re2::kRegexpBadEscape);

    EXPECT_EQ(status_.code(), re2::kRegexpBadEscape);

}



TEST_F(RegexpStatusTest_139, OkReturnsTrueForSuccessCode_139) {

    EXPECT_TRUE(status_.ok());

}



TEST_F(RegexpStatusTest_139, OkReturnsFalseForErrorCode_139) {

    status_.set_code(re2::kRegexpBadEscape);

    EXPECT_FALSE(status_.ok());

}



TEST_F(RegexpStatusTest_139, SetErrorArgUpdatesErrorArg_139) {

    absl::string_view error_arg = "test_error";

    status_.set_error_arg(error_arg);

    EXPECT_EQ(status_.error_arg(), error_arg);

}



TEST_F(RegexpStatusTest_139, CopySetsCodeAndErrorArg_139) {

    re2::RegexpStatus source;

    source.set_code(re2::kRegexpBadEscape);

    source.set_error_arg("test_copy");



    status_.Copy(source);



    EXPECT_EQ(status_.code(), source.code());

    EXPECT_EQ(status_.error_arg(), source.error_arg());

}



TEST_F(RegexpStatusTest_139, CodeTextReturnsValidString_139) {

    std::string code_text = re2::RegexpStatus::CodeText(re2::kRegexpBadEscape);

    EXPECT_FALSE(code_text.empty());

}



TEST_F(RegexpStatusTest_139, TextReturnsValidStringForSuccess_139) {

    std::string text = status_.Text();

    EXPECT_FALSE(text.empty());

}



TEST_F(RegexpStatusTest_139, TextIncludesErrorArgForErrorCode_139) {

    absl::string_view error_arg = "test_error";

    status_.set_code(re2::kRegexpBadEscape);

    status_.set_error_arg(error_arg);



    std::string text = status_.Text();

    EXPECT_NE(text.find(std::string(error_arg)), std::string::npos);

}



}  // namespace
