#include <gtest/gtest.h>

#include "regexp.h"



using namespace re2;



class RegexpStatusTest_352 : public ::testing::Test {

protected:

    RegexpStatus status;

};



TEST_F(RegexpStatusTest_352, DefaultConstructorSetsSuccessCode_352) {

    EXPECT_EQ(status.code(), kRegexpSuccess);

}



TEST_F(RegexpStatusTest_352, CopyConstructorCopiesState_352) {

    RegexpStatus original;

    original.set_code(kRegexpBadEscape);

    original.set_error_arg("bad escape");



    RegexpStatus copy(original);



    EXPECT_EQ(copy.code(), kRegexpBadEscape);

    EXPECT_EQ(copy.error_arg(), "bad escape");

}



TEST_F(RegexpStatusTest_352, CopyMethodCopiesState_352) {

    RegexpStatus original;

    original.set_code(kRegexpBadEscape);

    original.set_error_arg("bad escape");



    status.Copy(original);



    EXPECT_EQ(status.code(), kRegexpBadEscape);

    EXPECT_EQ(status.error_arg(), "bad escape");

}



TEST_F(RegexpStatusTest_352, SetCodeSetsTheCode_352) {

    status.set_code(kRegexpInternalError);

    EXPECT_EQ(status.code(), kRegexpInternalError);

}



TEST_F(RegexpStatusTest_352, SetErrorArgSetsTheErrorArgument_352) {

    status.set_error_arg("invalid pattern");

    EXPECT_EQ(status.error_arg(), "invalid pattern");

}



TEST_F(RegexpStatusTest_352, OkReturnsTrueForSuccessCode_352) {

    status.set_code(kRegexpSuccess);

    EXPECT_TRUE(status.ok());

}



TEST_F(RegexpStatusTest_352, OkReturnsFalseForErrorCode_352) {

    status.set_code(kRegexpBadEscape);

    EXPECT_FALSE(status.ok());

}



TEST_F(RegexpStatusTest_352, TextReturnsDescriptionForSuccessCode_352) {

    status.set_code(kRegexpSuccess);

    EXPECT_EQ(status.Text(), "success");

}



TEST_F(RegexpStatusTest_352, TextReturnsDescriptionForErrorCode_352) {

    status.set_code(kRegexpBadEscape);

    status.set_error_arg("bad escape");

    EXPECT_EQ(status.Text(), "error parsing regexp: bad escape");

}
