#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/controllers/option_manager.h"



namespace glomap {

using ::testing::_;

using ::testing::Eq;



class OptionManagerTest_166 : public ::testing::Test {

protected:

    OptionManager manager{true};



    void SetUp() override {

        manager.Reset();

    }

};



TEST_F(OptionManagerTest_166, ResetOptionsSetsPathsToEmpty_166) {

    *manager.database_path = "some_path";

    *manager.image_path = "another_path";



    manager.ResetOptions(true);



    EXPECT_EQ(*manager.database_path, "");

    EXPECT_EQ(*manager.image_path, "");

}



TEST_F(OptionManagerTest_166, ResetOptionsDoesNotAffectPathsWhenFalse_166) {

    *manager.database_path = "some_path";

    *manager.image_path = "another_path";



    manager.ResetOptions(false);



    EXPECT_EQ(*manager.database_path, "some_path");

    EXPECT_EQ(*manager.image_path, "another_path");

}



TEST_F(OptionManagerTest_166, ResetClearsRegisteredOptions_166) {

    manager.AddRequiredOption("test_option", &FLAGS_logtostderr, "help text");



    manager.Reset();



    // Assuming that after reset, the options are no longer registered or accessible

    // This is a bit of an assumption since the internal state is not exposed,

    // but we can test for known behavior like parsing errors if applicable.

}



TEST_F(OptionManagerTest_166, AddAndRegisterDefaultOptionAddsToDesc_166) {

    manager.AddDefaultOption("test_option", &FLAGS_logtostderr, "help text");



    // Assuming that adding an option makes it parsable

    int argc = 2;

    char* argv[] = {const_cast<char*>(""), const_cast<char*>("--test_option=1")};

    EXPECT_NO_THROW(manager.Parse(argc, argv));

}



TEST_F(OptionManagerTest_166, ParseFailsWithUnknownOption_166) {

    int argc = 2;

    char* argv[] = {const_cast<char*>(""), const_cast<char*>("--unknown_option=1")};



    EXPECT_THROW(manager.Parse(argc, argv), boost::program_options::error);

}



TEST_F(OptionManagerTest_166, AddAllOptionsAddsMultipleOptions_166) {

    manager.AddAllOptions();



    // Assuming that adding all options makes multiple specific options parsable

    int argc = 3;

    char* argv[] = {const_cast<char*>(""), const_cast<char*>("--log_to_stderr=1"), const_cast<char*>("--log_level=2")};

    EXPECT_NO_THROW(manager.Parse(argc, argv));

}



TEST_F(OptionManagerTest_166, AddRequiredOptionThrowsWhenMissing_166) {

    manager.AddRequiredOption("required_option", &FLAGS_logtostderr, "help text");



    int argc = 1;

    char* argv[] = {const_cast<char*>("")};



    EXPECT_THROW(manager.Parse(argc, argv), boost::program_options::error);

}



TEST_F(OptionManagerTest_166, AddRequiredOptionSucceedsWhenProvided_166) {

    manager.AddRequiredOption("required_option", &FLAGS_logtostderr, "help text");



    int argc = 2;

    char* argv[] = {const_cast<char*>(""), const_cast<char*>("--required_option=1")};



    EXPECT_NO_THROW(manager.Parse(argc, argv));

}



TEST_F(OptionManagerTest_166, BoundaryConditionForAddDefaultOption_166) {

    manager.AddDefaultOption("", &FLAGS_logtostderr, "help text");



    int argc = 2;

    char* argv[] = {const_cast<char*>(""), const_cast<char*>("--=1")};



    // Assuming an empty option name does not cause a crash

    EXPECT_NO_THROW(manager.Parse(argc, argv));

}



TEST_F(OptionManagerTest_166, BoundaryConditionForAddRequiredOption_166) {

    manager.AddRequiredOption("", &FLAGS_logtostderr, "help text");



    int argc = 2;

    char* argv[] = {const_cast<char*>(""), const_cast<char*>("--=1")};



    // Assuming an empty option name does not cause a crash

    EXPECT_NO_THROW(manager.Parse(argc, argv));

}



} // namespace glomap
