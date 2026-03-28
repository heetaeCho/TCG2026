#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/controllers/option_manager.h"



using namespace glomap;

using ::testing::Test;



class OptionManagerTest_33 : public Test {

protected:

    OptionManager option_manager{true};



    void SetUp() override {

        // Reset the options before each test

        option_manager.Reset();

    }

};



TEST_F(OptionManagerTest_33, AddAllOptions_CallsEachAddFunction_33) {

    EXPECT_NO_THROW(option_manager.AddAllOptions());

    // Since we cannot verify internal state, this test ensures no exception is thrown.

}



TEST_F(OptionManagerTest_33, Reset_ClearsAddedFlags_33) {

    option_manager.AddDatabaseOptions();

    option_manager.Reset();

    // Since we cannot verify internal state directly, we ensure Reset does not throw and assume it clears flags as intended.

    EXPECT_NO_THROW(option_manager.Reset());

}



TEST_F(OptionManagerTest_33, Parse_ValidArguments_SuccessfulParse_33) {

    int argc = 1;

    char* argv[] = {const_cast<char*>("dummy")};

    EXPECT_NO_THROW(option_manager.Parse(argc, argv));

}



TEST_F(OptionManagerTest_33, AddRequiredOption_AddsCorrectly_33) {

    std::string test_option;

    EXPECT_NO_THROW(option_manager.AddRequiredOption("test_option", &test_option, "A test option"));

}



TEST_F(OptionManagerTest_33, AddDefaultOption_AddsCorrectly_33) {

    std::string test_option = "default";

    EXPECT_NO_THROW(option_manager.AddDefaultOption("test_option", &test_option, "A default test option"));

}



TEST_F(OptionManagerTest_33, Parse_InvalidArguments_ErrorHandling_33) {

    int argc = 2;

    char* argv[] = {const_cast<char*>("dummy"), const_cast<char*>("--unknown_option")};

    EXPECT_THROW(option_manager.Parse(argc, argv), boost::program_options::error);

}



TEST_F(OptionManagerTest_33, ResetOptions_ResetPathsOnly_33) {

    EXPECT_NO_THROW(option_manager.ResetOptions(true));

}
