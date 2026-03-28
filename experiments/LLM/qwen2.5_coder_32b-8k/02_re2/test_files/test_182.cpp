#include <gtest/gtest.h>

#include "TestProjects/re2/util/pcre.h"



namespace {



class PCRE_OptionsTest_182 : public ::testing::Test {

protected:

    re2::PCRE_Options options_;

};



TEST_F(PCRE_OptionsTest_182, DefaultReportErrorsIsTrue_182) {

    EXPECT_TRUE(options_.report_errors());

}



TEST_F(PCRE_OptionsTest_182, SetReportErrorsToFalse_182) {

    options_.set_report_errors(false);

    EXPECT_FALSE(options_.report_errors());

}



TEST_F(PCRE_OptionsTest_182, SetReportErrorsToTrue_182) {

    options_.set_report_errors(true);

    EXPECT_TRUE(options_.report_errors());

}



}  // namespace
