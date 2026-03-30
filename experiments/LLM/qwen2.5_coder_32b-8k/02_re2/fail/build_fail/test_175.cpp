#include <gtest/gtest.h>

#include "TestProjects/re2/util/pcre.h"



namespace re2 {

    class PCRE_Options;

}



using namespace re2;



class PCREOptionsTest_175 : public ::testing::Test {

protected:

    PCRE_Options options_;

};



TEST_F(PCREOptionsTest_175, DefaultConstructorInitializesOptionToNone_175) {

    EXPECT_EQ(options_.option(), PCRE::None);

}



TEST_F(PCREOptionsTest_175, SetOptionUpdatesOptionValue_175) {

    options_.set_option(PCRE::IgnoreCase);

    EXPECT_EQ(options_.option(), PCRE::IgnoreCase);

}



TEST_F(PCREOptionsTest_175, DefaultConstructorInitializesMatchLimitToZero_175) {

    EXPECT_EQ(options_.match_limit(), 0);

}



TEST_F(PCREOptionsTest_175, SetMatchLimitUpdatesMatchLimitValue_175) {

    options_.set_match_limit(1000);

    EXPECT_EQ(options_.match_limit(), 1000);

}



TEST_F(PCREOptionsTest_175, DefaultConstructorInitializesStackLimitToZero_175) {

    EXPECT_EQ(options_.stack_limit(), 0);

}



TEST_F(PCREOptionsTest_175, SetStackLimitUpdatesStackLimitValue_175) {

    options_.set_stack_limit(2000);

    EXPECT_EQ(options_.stack_limit(), 2000);

}



TEST_F(PCREOptionsTest_175, DefaultConstructorInitializesReportErrorsToTrue_175) {

    EXPECT_TRUE(options_.report_errors());

}



TEST_F(PCREOptionsTest_175, SetReportErrorsUpdatesReportErrorsValue_175) {

    options_.set_report_errors(false);

    EXPECT_FALSE(options_.report_errors());

}
