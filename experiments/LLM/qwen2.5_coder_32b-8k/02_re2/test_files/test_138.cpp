#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/re2/re2/regexp.h"



using namespace re2;



class RegexpStatusTest_138 : public ::testing::Test {

protected:

    RegexpStatus status_;

};



TEST_F(RegexpStatusTest_138, DefaultConstructorInitializesCodeToSuccess_138) {

    EXPECT_EQ(status_.code(), kRegexpSuccess);

}



TEST_F(RegexpStatusTest_138, DefaultConstructorInitializesErrorArgToEmpty_138) {

    EXPECT_EQ(status_.error_arg(), "");

}



TEST_F(RegexpStatusTest_138, DefaultConstructorInitializesTmpToNull_138) {

    EXPECT_EQ(status_.tmp_, nullptr);

}



TEST_F(RegexpStatusTest_138, SetCodeChangesStatusCode_138) {

    status_.set_code(kRegexpBadEscape);

    EXPECT_EQ(status_.code(), kRegexpBadEscape);

}



TEST_F(RegexpStatusTest_138, SetErrorArgChangesErrorArgument_138) {

    status_.set_error_arg("invalid escape");

    EXPECT_EQ(status_.error_arg(), "invalid escape");

}



TEST_F(RegexpStatusTest_138, SetTmpAssignsNewStringPointer_138) {

    std::string tmp = "temp";

    status_.set_tmp(&tmp);

    EXPECT_EQ(status_.tmp_, &tmp);

}



TEST_F(RegexpStatusTest_138, CopyCopiesCodeAndErrorArg_138) {

    RegexpStatus other;

    other.set_code(kRegexpBadEscape);

    other.set_error_arg("invalid escape");

    

    status_.Copy(other);

    EXPECT_EQ(status_.code(), kRegexpBadEscape);

    EXPECT_EQ(status_.error_arg(), "invalid escape");

}



TEST_F(RegexpStatusTest_138, CodeTextReturnsCorrectStringForSuccess_138) {

    EXPECT_EQ(RegexpStatus::CodeText(kRegexpSuccess), "success");

}



TEST_F(RegexpStatusTest_138, TextReturnsEmptyStringWhenOk_138) {

    status_.set_code(kRegexpSuccess);

    EXPECT_EQ(status_.Text(), "");

}



TEST_F(RegexpStatusTest_138, TextReturnsErrorStringWhenNotOk_138) {

    status_.set_code(kRegexpBadEscape);

    status_.set_error_arg("invalid escape");

    EXPECT_EQ(status_.Text(), "error parsing regexp: invalid escape");

}
