#include <gtest/gtest.h>

#include "TestProjects/glomap/glomap/controllers/option_manager.h"

#include <boost/program_options.hpp>



using namespace glomap;

using ::testing::_;

using ::testing::Eq;



class OptionManagerTest_49 : public ::testing::Test {

protected:

    OptionManager* option_manager;



    void SetUp() override {

        option_manager = new OptionManager(false);

    }



    void TearDown() override {

        delete option_manager;

    }

};



TEST_F(OptionManagerTest_49, ResetClearsOptions_49) {

    // Assuming some options were added before reset

    option_manager->AddDatabaseOptions();

    option_manager->Reset();



    EXPECT_EQ(option_manager->database_path, nullptr);

}



TEST_F(OptionManagerTest_49, ResetResetsDescPointer_49) {

    option_manager->AddDatabaseOptions();

    option_manager->Reset();



    EXPECT_NE(option_manager->desc_, nullptr); // desc_ should be re-initialized

}



TEST_F(OptionManagerTest_49, ResetClearsBoolOptionsVector_49) {

    bool test_bool = true;

    option_manager->AddRequiredOption("test_bool", &test_bool, "Test bool option");

    option_manager->Reset();



    EXPECT_EQ(option_manager->options_bool_.size(), 0);

}



TEST_F(OptionManagerTest_49, ResetClearsIntOptionsVector_49) {

    int test_int = 0;

    option_manager->AddRequiredOption("test_int", &test_int, "Test int option");

    option_manager->Reset();



    EXPECT_EQ(option_manager->options_int_.size(), 0);

}



TEST_F(OptionManagerTest_49, ResetClearsDoubleOptionsVector_49) {

    double test_double = 0.0;

    option_manager->AddRequiredOption("test_double", &test_double, "Test double option");

    option_manager->Reset();



    EXPECT_EQ(option_manager->options_double_.size(), 0);

}



TEST_F(OptionManagerTest_49, ResetClearsStringOptionsVector_49) {

    std::string test_string = "";

    option_manager->AddRequiredOption("test_string", &test_string, "Test string option");

    option_manager->Reset();



    EXPECT_EQ(option_manager->options_string_.size(), 0);

}



TEST_F(OptionManagerTest_49, ResetResetsAddedFlags_49) {

    option_manager->AddDatabaseOptions();

    option_manager->Reset();



    EXPECT_FALSE(option_manager->added_database_options_);

}
