#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_21 : public ::testing::Test {

protected:

    RE2::Options options;

};



TEST_F(RE2OptionsTest_21, DefaultLogErrorsValueIsTrue_21) {

    EXPECT_TRUE(options.log_errors());

}



TEST_F(RE2OptionsTest_21, SetLogErrorsChangesValueToFalse_21) {

    options.set_log_errors(false);

    EXPECT_FALSE(options.log_errors());

}



TEST_F(RE2OptionsTest_21, SetLogErrorsChangesValueToTrue_21) {

    options.set_log_errors(false);  // First set to false

    options.set_log_errors(true);

    EXPECT_TRUE(options.log_errors());

}



TEST_F(RE2OptionsTest_21, BoundaryConditionLogErrorsFalse_21) {

    options.set_log_errors(false);

    EXPECT_FALSE(options.log_errors());

}



TEST_F(RE2OptionsTest_21, BoundaryConditionLogErrorsTrue_21) {

    options.set_log_errors(true);

    EXPECT_TRUE(options.log_errors());

}
