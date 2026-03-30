#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "parser.h"

#include "manifest_parser.h"

#include "state.h"

#include "disk_interface.h"



using ::testing::_;

using ::testing::Return;

using ::testing::StrEq;



class ManifestParserTest_168 : public ::testing::Test {

protected:

    State state_;

    RealDiskInterface disk_interface_;

    ManifestParserOptions options_;

    std::string err_;

    ManifestParser parser_;



    ManifestParserTest_168() : parser_(&state_, &disk_interface_, options_) {}

};



TEST_F(ManifestParserTest_168, LoadValidManifestFile_168) {

    const char data[] = "rule cc\n  command = g++ -c $in -o $out\nbuild foo.o: cc foo.cc";

    std::string input(data);

    EXPECT_TRUE(parser_.ParseTest(input, &err_));

}



TEST_F(ManifestParserTest_168, LoadInvalidManifestFile_MissingRule_168) {

    const char data[] = "build foo.o: cc foo.cc";

    std::string input(data);

    EXPECT_FALSE(parser_.ParseTest(input, &err_));

    EXPECT_EQ(err_, "missing rule for build statement");

}



TEST_F(ManifestParserTest_168, LoadEmptyManifestFile_168) {

    const char data[] = "";

    std::string input(data);

    EXPECT_FALSE(parser_.ParseTest(input, &err_));

    EXPECT_EQ(err_, "expected build command or pool definition");

}



TEST_F(ManifestParserTest_168, LoadLargeManifestFile_LargeInput_168) {

    std::string large_input(1024 * 1024, 'a'); // 1MB of data

    EXPECT_FALSE(parser_.ParseTest(large_input, &err_));

}



TEST_F(ManifestParserTest_168, LoadManifestFileWithSpecialCharacters_168) {

    const char data[] = "rule cc\n  command = g++ -c $in -o $out\nbuild foo.o: cc foo@.cc";

    std::string input(data);

    EXPECT_TRUE(parser_.ParseTest(input, &err_));

}



TEST_F(ManifestParserTest_168, LoadManifestFileWithMultipleRules_168) {

    const char data[] = 

        "rule cc\n  command = g++ -c $in -o $out\n"

        "rule link\n  command = g++ $in -o $out";

    std::string input(data);

    EXPECT_TRUE(parser_.ParseTest(input, &err_));

}



TEST_F(ManifestParserTest_168, LoadManifestFileWithMultipleEdges_168) {

    const char data[] = 

        "rule cc\n  command = g++ -c $in -o $out\n"

        "build foo.o: cc foo.cc\n"

        "build bar.o: cc bar.cc";

    std::string input(data);

    EXPECT_TRUE(parser_.ParseTest(input, &err_));

}



TEST_F(ManifestParserTest_168, LoadManifestFileWithDefaultTarget_168) {

    const char data[] = 

        "rule cc\n  command = g++ -c $in -o $out\n"

        "build foo.o: cc foo.cc\n"

        "default foo.o";

    std::string input(data);

    EXPECT_TRUE(parser_.ParseTest(input, &err_));

}



TEST_F(ManifestParserTest_168, LoadManifestFileWithInvalidDefaultTarget_168) {

    const char data[] = 

        "rule cc\n  command = g++ -c $in -o $out\n"

        "default bar.o";

    std::string input(data);

    EXPECT_FALSE(parser_.ParseTest(input, &err_));

    EXPECT_EQ(err_, "'bar.o' doesn't match any rule or existing file");

}
