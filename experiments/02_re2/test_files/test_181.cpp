#include <gtest/gtest.h>

#include "./TestProjects/re2/util/pcre.h"



using namespace re2;



class PCRE_OptionsTest_181 : public ::testing::Test {

protected:

    PCRE_Options options;

};



TEST_F(PCRE_OptionsTest_181, DefaultReportErrorsIsTrue_181) {

    EXPECT_TRUE(options.report_errors());

}



TEST_F(PCRE_OptionsTest_181, SetReportErrorsChangesValue_181) {

    options.set_report_errors(false);

    EXPECT_FALSE(options.report_errors());



    options.set_report_errors(true);

    EXPECT_TRUE(options.report_errors());

}



// Assuming match_limit and stack_limit have similar behavior to report_errors

TEST_F(PCRE_OptionsTest_181, DefaultMatchLimitIsZero_181) {

    EXPECT_EQ(options.match_limit(), 0);

}



TEST_F(PCRE_OptionsTest_181, SetMatchLimitChangesValue_181) {

    options.set_match_limit(100);

    EXPECT_EQ(options.match_limit(), 100);



    options.set_match_limit(50);

    EXPECT_EQ(options.match_limit(), 50);

}



TEST_F(PCRE_OptionsTest_181, DefaultStackLimitIsZero_181) {

    EXPECT_EQ(options.stack_limit(), 0);

}



TEST_F(PCRE_OptionsTest_181, SetStackLimitChangesValue_181) {

    options.set_stack_limit(200);

    EXPECT_EQ(options.stack_limit(), 200);



    options.set_stack_limit(100);

    EXPECT_EQ(options.stack_limit(), 100);

}



// Boundary conditions for match_limit and stack_limit

TEST_F(PCRE_OptionsTest_181, MatchLimitBoundaryConditions_181) {

    options.set_match_limit(-1);

    EXPECT_EQ(options.match_limit(), -1);



    options.set_match_limit(0);

    EXPECT_EQ(options.match_limit(), 0);



    options.set_match_limit(std::numeric_limits<int>::max());

    EXPECT_EQ(options.match_limit(), std::numeric_limits<int>::max());

}



TEST_F(PCRE_OptionsTest_181, StackLimitBoundaryConditions_181) {

    options.set_stack_limit(-1);

    EXPECT_EQ(options.stack_limit(), -1);



    options.set_stack_limit(0);

    EXPECT_EQ(options.stack_limit(), 0);



    options.set_stack_limit(std::numeric_limits<int>::max());

    EXPECT_EQ(options.stack_limit(), std::numeric_limits<int>::max());

}
