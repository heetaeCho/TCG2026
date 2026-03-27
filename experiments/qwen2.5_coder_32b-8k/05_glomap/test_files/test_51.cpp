#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "option_manager.h"

#include <boost/program_options.hpp>



using namespace glomap;

namespace po = boost::program_options;



class OptionManagerTest_51 : public ::testing::Test {

protected:

    OptionManagerTest_51() : option_manager(true) {}



    void SetUp() override {

        // Setup the options description

        desc.add_options()

            ("help", "produce help message")

            ("database-path,d", po::value<std::string>(&database_path)->default_value("default_db"), "Database path")

            ("image-path,i", po::value<std::string>(&image_path)->default_value("default_img"), "Image path");

        option_manager.desc_ = std::make_shared<po::options_description>(desc);

    }



    OptionManager option_manager;

    po::options_description desc;

    std::string database_path;

    std::string image_path;

};



TEST_F(OptionManagerTest_51, ParseHelpFlag_51) {

    char* argv[] = {const_cast<char*>("program"), const_cast<char*>("--help")};

    int argc = 2;



    EXPECT_EXIT(option_manager.Parse(argc, argv), ::testing::ExitedWithCode(EXIT_SUCCESS),

                "The following options can be specified via command-line:");

}



TEST_F(OptionManagerTest_51, ParseValidArguments_51) {

    char* argv[] = {const_cast<char*>("program"), const_cast<char*>("--database-path"), const_cast<char*>("/path/to/db"),

                    const_cast<char*>("--image-path"), const_cast<char*>("/path/to/img")};

    int argc = 5;



    option_manager.Parse(argc, argv);



    EXPECT_EQ(database_path, "/path/to/db");

    EXPECT_EQ(image_path, "/path/to/img");

}



TEST_F(OptionManagerTest_51, ParseInvalidArguments_51) {

    char* argv[] = {const_cast<char*>("program"), const_cast<char*>("--unknown-option")};

    int argc = 2;



    EXPECT_EXIT(option_manager.Parse(argc, argv), ::testing::ExitedWithCode(EXIT_FAILURE),

                "Failed to parse options");

}



TEST_F(OptionManagerTest_51, ParseDefaultValues_51) {

    char* argv[] = {const_cast<char*>("program")};

    int argc = 1;



    option_manager.Parse(argc, argv);



    EXPECT_EQ(database_path, "default_db");

    EXPECT_EQ(image_path, "default_img");

}



TEST_F(OptionManagerTest_51, ParseMixedArguments_51) {

    char* argv[] = {const_cast<char*>("program"), const_cast<char*>("--database-path"), const_cast<char*>("/path/to/db")};

    int argc = 3;



    option_manager.Parse(argc, argv);



    EXPECT_EQ(database_path, "/path/to/db");

    EXPECT_EQ(image_path, "default_img");

}
