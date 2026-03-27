#include <gtest/gtest.h>

#include "pcre.h"



using namespace re2;



class PCRE_OptionsTest_177 : public ::testing::Test {

protected:

    PCRE_Options options_;

};



TEST_F(PCRE_OptionsTest_177, DefaultConstructorInitializesMatchLimitToZero_177) {

    EXPECT_EQ(options_.match_limit(), 0);

}



TEST_F(PCRE_OptionsTest_177, SetMatchLimitUpdatesMatchLimitCorrectly_177) {

    options_.set_match_limit(500);

    EXPECT_EQ(options_.match_limit(), 500);

}



TEST_F(PCRE_OptionsTest_177, MatchLimitBoundaryConditionZero_177) {

    options_.set_match_limit(0);

    EXPECT_EQ(options_.match_limit(), 0);

}



TEST_F(PCRE_OptionsTest_177, MatchLimitBoundaryConditionNegativeValue_177) {

    options_.set_match_limit(-1);

    EXPECT_EQ(options_.match_limit(), -1); // Assuming the implementation allows negative values

}



// Assuming stack_limit and report_errors follow similar patterns as match_limit,

// we can create tests for them as well.



TEST_F(PCRE_OptionsTest_177, DefaultConstructorInitializesStackLimitToZero_177) {

    EXPECT_EQ(options_.stack_limit(), 0);

}



TEST_F(PCRE_OptionsTest_177, SetStackLimitUpdatesStackLimitCorrectly_177) {

    options_.set_stack_limit(1024);

    EXPECT_EQ(options_.stack_limit(), 1024);

}



TEST_F(PCRE_OptionsTest_177, StackLimitBoundaryConditionZero_177) {

    options_.set_stack_limit(0);

    EXPECT_EQ(options_.stack_limit(), 0);

}



TEST_F(PCRE_OptionsTest_177, StackLimitBoundaryConditionNegativeValue_177) {

    options_.set_stack_limit(-1);

    EXPECT_EQ(options_.stack_limit(), -1); // Assuming the implementation allows negative values

}



TEST_F(PCRE_OptionsTest_177, DefaultConstructorInitializesReportErrorsToTrue_177) {

    EXPECT_TRUE(options_.report_errors());

}



TEST_F(PCRE_OptionsTest_177, SetReportErrorsUpdatesReportErrorsCorrectly_177) {

    options_.set_report_errors(false);

    EXPECT_FALSE(options_.report_errors());



    options_.set_report_errors(true);

    EXPECT_TRUE(options_.report_errors());

}
