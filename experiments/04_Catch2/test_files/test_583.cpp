#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_commandline.cpp"



using namespace Catch;

using namespace Clara;



class CommandLineParserTest_583 : public ::testing::Test {

protected:

    ConfigData config;

};



TEST_F(CommandLineParserTest_583, SetWarning_NoAssertions_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--warn=NoAssertions"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

    EXPECT_TRUE((config.warnings & WarnAbout::NoAssertions));

}



TEST_F(CommandLineParserTest_583, SetWarning_UnmatchedTestSpec_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--warn=UnmatchedTestSpec"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

    EXPECT_TRUE((config.warnings & WarnAbout::UnmatchedTestSpec));

}



TEST_F(CommandLineParserTest_583, SetWarning_Unrecognised_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--warn=Unknown"});

    EXPECT_EQ(result.type(), ParseResultType::NoMatch);

    EXPECT_TRUE(result.errorMessage().find("Unrecognised warning option") != std::string::npos);

}



TEST_F(CommandLineParserTest_583, LoadTestNamesFromFile_Success_583) {

    config.processName = "test";

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--input-file=./tests.txt"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(CommandLineParserTest_583, LoadTestNamesFromFile_FileNotFound_583) {

    config.processName = "test";

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--input-file=./nonexistentfile.txt"});

    EXPECT_EQ(result.type(), ParseResultType::NoMatch);

    EXPECT_TRUE(result.errorMessage().find("Unable to load input file") != std::string::npos);

}



TEST_F(CommandLineParserTest_583, SetTestOrder_Declared_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--order=decl"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

    EXPECT_EQ(config.runOrder, TestRunOrder::Declared);

}



TEST_F(CommandLineParserTest_583, SetTestOrder_Lexical_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--order=lex"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

    EXPECT_EQ(config.runOrder, TestRunOrder::LexicographicallySorted);

}



TEST_F(CommandLineParserTest_583, SetTestOrder_Randomized_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--order=rand"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

    EXPECT_EQ(config.runOrder, TestRunOrder::Randomized);

}



TEST_F(CommandLineParserTest_583, SetTestOrder_Unrecognised_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--order=unknown"});

    EXPECT_EQ(result.type(), ParseResultType::NoMatch);

    EXPECT_TRUE(result.errorMessage().find("Unrecognised ordering") != std::string::npos);

}



TEST_F(CommandLineParserTest_583, SetRngSeed_Time_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--rng-seed=time"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(CommandLineParserTest_583, SetRngSeed_RandomDevice_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--rng-seed=random-device"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(CommandLineParserTest_583, SetRngSeed_Number_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--rng-seed=1234"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(CommandLineParserTest_583, SetRngSeed_Invalid_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--rng-seed=invalid"});

    EXPECT_EQ(result.type(), ParseResultType::NoMatch);

    EXPECT_TRUE(result.errorMessage().find("Could not parse") != std::string::npos);

}



TEST_F(CommandLineParserTest_583, SetDefaultColourMode_Ansi_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--colour-mode=ansi"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(CommandLineParserTest_583, SetDefaultColourMode_Win32_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--colour-mode=win32"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(CommandLineParserTest_583, SetDefaultColourMode_None_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--colour-mode=none"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(CommandLineParserTest_583, SetDefaultColourMode_Default_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--colour-mode=default"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(CommandLineParserTest_583, SetDefaultColourMode_Unrecognised_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--colour-mode=unknown"});

    EXPECT_EQ(result.type(), ParseResultType::NoMatch);

    EXPECT_TRUE(result.errorMessage().find("Unrecognised colour mode") != std::string::npos);

}



TEST_F(CommandLineParserTest_583, SetWaitForKeypress_Never_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--wait-for-keypress=never"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(CommandLineParserTest_583, SetWaitForKeypress_Start_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--wait-for-keypress=start"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(CommandLineParserTest_583, SetWaitForKeypress_Exit_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--wait-for-keypress=exit"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(CommandLineParserTest_583, SetWaitForKeypress_Both_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--wait-for-keypress=both"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(CommandLineParserTest_583, SetWaitForKeypress_Unrecognised_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--wait-for-keypress=unknown"});

    EXPECT_EQ(result.type(), ParseResultType::NoMatch);

    EXPECT_TRUE(result.errorMessage().find("keypress argument must be one of") != std::string::npos);

}



TEST_F(CommandLineParserTest_583, SetVerbosity_Quiet_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--verbosity=quiet"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(CommandLineParserTest_583, SetVerbosity_Normal_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--verbosity=normal"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(CommandLineParserTest_583, SetVerbosity_High_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--verbosity=high"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(CommandLineParserTest_583, SetVerbosity_Unrecognised_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--verbosity=unknown"});

    EXPECT_EQ(result.type(), ParseResultType::NoMatch);

    EXPECT_TRUE(result.errorMessage().find("Unrecognised verbosity") != std::string::npos);

}



TEST_F(CommandLineParserTest_583, SetReporter_Default_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--reporter=console"});

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(CommandLineParserTest_583, SetReporter_Empty_583) {

    auto parser = makeCommandLineParser(config);

    auto result = parser.parse("test", {"--reporter="});

    EXPECT_EQ(result.type(), ParseResultType::NoMatch);

    EXPECT_TRUE(result.errorMessage().find("Unrecognised colour mode") != std::string::npos);

}



TEST_F(CommandLineParserTest_583, SetShardCount_Default_583) {

    auto parser = makeCommandLineParser(config);

    EXPECT_EQ(config.shardCount, 1);

}



TEST_F(CommandLineParserTest_583, SetShardIndex_Default_583) {

    auto parser = makeCommandLineParser(config);

    EXPECT_EQ(config.shardIndex, 0);

}
