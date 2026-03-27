#include <gtest/gtest.h>

#include "pcre.h"



using namespace re2;



class PCRE_OptionsTest : public ::testing::Test {

protected:

    PCRE_Options options;

};



TEST_F(PCRE_OptionsTest_176, DefaultOptionIsNone_176) {

    EXPECT_EQ(options.option(), PCRE::None);

}



TEST_F(PCRE_OptionsTest_176, SetAndGetOption_176) {

    options.set_option(PCRE::UTF8);

    EXPECT_EQ(options.option(), PCRE::UTF8);

}



TEST_F(PCRE_OptionsTest_176, DefaultMatchLimitIsZero_176) {

    EXPECT_EQ(options.match_limit(), 0);

}



TEST_F(PCRE_OptionsTest_176, SetAndGetMatchLimit_176) {

    options.set_match_limit(1000);

    EXPECT_EQ(options.match_limit(), 1000);

}



TEST_F(PCRE_OptionsTest_176, DefaultStackLimitIsZero_176) {

    EXPECT_EQ(options.stack_limit(), 0);

}



TEST_F(PCRE_OptionsTest_176, SetAndGetStackLimit_176) {

    options.set_stack_limit(500);

    EXPECT_EQ(options.stack_limit(), 500);

}



TEST_F(PCRE_OptionsTest_176, DefaultReportErrorsIsTrue_176) {

    EXPECT_TRUE(options.report_errors());

}



TEST_F(PCRE_OptionsTest_176, SetAndGetReportErrors_176) {

    options.set_report_errors(false);

    EXPECT_FALSE(options.report_errors());

}
