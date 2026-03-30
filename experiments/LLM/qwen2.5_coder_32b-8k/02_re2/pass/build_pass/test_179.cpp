#include <gtest/gtest.h>

#include "pcre.h"



using namespace re2;



class PCRE_OptionsTest_179 : public ::testing::Test {

protected:

    PCRE_Options options;

};



TEST_F(PCRE_OptionsTest_179, StackLimitDefault_179) {

    EXPECT_EQ(options.stack_limit(), 0);

}



TEST_F(PCRE_OptionsTest_179, SetStackLimitAndGet_179) {

    int new_stack_limit = 1024;

    options.set_stack_limit(new_stack_limit);

    EXPECT_EQ(options.stack_limit(), new_stack_limit);

}



TEST_F(PCRE_OptionsTest_179, MatchLimitDefault_179) {

    EXPECT_EQ(options.match_limit(), 0);

}



TEST_F(PCRE_OptionsTest_179, SetMatchLimitAndGet_179) {

    int new_match_limit = 500;

    options.set_match_limit(new_match_limit);

    EXPECT_EQ(options.match_limit(), new_match_limit);

}



TEST_F(PCRE_OptionsTest_179, ReportErrorsDefault_179) {

    EXPECT_TRUE(options.report_errors());

}



TEST_F(PCRE_OptionsTest_179, SetReportErrorsAndGet_179) {

    options.set_report_errors(false);

    EXPECT_FALSE(options.report_errors());

}
