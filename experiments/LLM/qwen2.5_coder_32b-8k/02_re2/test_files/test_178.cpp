#include <gtest/gtest.h>

#include "TestProjects/re2/util/pcre.h"



using namespace re2;



class PCRE_OptionsTest_178 : public ::testing::Test {

protected:

    PCRE_Options options;

};



TEST_F(PCRE_OptionsTest_178, DefaultMatchLimitIsZero_178) {

    EXPECT_EQ(options.match_limit(), 0);

}



TEST_F(PCRE_OptionsTest_178, SetMatchLimitUpdatesValue_178) {

    options.set_match_limit(5000);

    EXPECT_EQ(options.match_limit(), 5000);

}



TEST_F(PCRE_OptionsTest_178, DefaultStackLimitIsZero_178) {

    EXPECT_EQ(options.stack_limit(), 0);

}



TEST_F(PCRE_OptionsTest_178, SetStackLimitUpdatesValue_178) {

    options.set_stack_limit(10000);

    EXPECT_EQ(options.stack_limit(), 10000);

}



TEST_F(PCRE_OptionsTest_178, DefaultReportErrorsIsTrue_178) {

    EXPECT_TRUE(options.report_errors());

}



TEST_F(PCRE_OptionsTest_178, SetReportErrorsUpdatesValue_178) {

    options.set_report_errors(false);

    EXPECT_FALSE(options.report_errors());

}



TEST_F(PCRE_OptionsTest_178, BoundaryMatchLimitNegativeValue_178) {

    options.set_match_limit(-1);

    EXPECT_EQ(options.match_limit(), -1);

}



TEST_F(PCRE_OptionsTest_178, BoundaryStackLimitNegativeValue_178) {

    options.set_stack_limit(-1);

    EXPECT_EQ(options.stack_limit(), -1);

}
