// File: tests/MakeCommandLineParserTests_583.cpp
#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>

#include "catch2/internal/catch_commandline.cpp"      // makeCommandLineParser
#include "catch2/catch_config.hpp"                    // ConfigData
#include "catch2/internal/catch_clara.hpp"            // Clara::Detail::ParseResultType, TokenStream (via Clara)
#include "catch2/interfaces/catch_interfaces_config.hpp"

using Catch::ConfigData;
using Catch::Clara::Parser;
using Catch::Clara::ParseResultType;
namespace Detail = Catch::Clara::Detail;

// Small helper to run the parser with given argv-like vector.
// This uses only public interfaces of Parser & TokenStream.
static auto ParseArgs(Parser& p,
                      const std::string& exe,
                      const std::vector<std::string>& args) {
    return p.parse(exe, Detail::TokenStream{ args });
}

// ---------- Normal operation ----------

TEST(MakeCommandLineParserTest_583, WarnNoAssertions_SetsFlag_583) {
    ConfigData cfg{};
    auto cli = Catch::makeCommandLineParser(cfg);

    auto res = ParseArgs(cli, "exe", {"--warn", "NoAssertions"});
    ASSERT_TRUE(res) << "parse should succeed";

    // Expect NoAssertions flag to be set in cfg.warnings (bitwise OR behavior).
    EXPECT_NE(0, (cfg.warnings & Catch::WarnAbout::NoAssertions));
}

TEST(MakeCommandLineParserTest_583, WarnUnmatchedTestSpec_SetsFlag_583) {
    ConfigData cfg{};
    auto cli = Catch::makeCommandLineParser(cfg);

    auto res = ParseArgs(cli, "exe", {"--warn", "UnmatchedTestSpec"});
    ASSERT_TRUE(res);

    EXPECT_NE(0, (cfg.warnings & Catch::WarnAbout::UnmatchedTestSpec));
}

TEST(MakeCommandLineParserTest_583, SetTestOrder_Declared_583) {
    ConfigData cfg{};
    auto cli = Catch::makeCommandLineParser(cfg);

    auto res = ParseArgs(cli, "exe", {"--order", "declared"});
    ASSERT_TRUE(res);

    EXPECT_EQ(Catch::TestRunOrder::Declared, cfg.runOrder);
}

TEST(MakeCommandLineParserTest_583, SetTestOrder_Lexical_583) {
    ConfigData cfg{};
    auto cli = Catch::makeCommandLineParser(cfg);

    auto res = ParseArgs(cli, "exe", {"--order", "lexical"});
    ASSERT_TRUE(res);

    EXPECT_EQ(Catch::TestRunOrder::LexicographicallySorted, cfg.runOrder);
}

TEST(MakeCommandLineParserTest_583, SetTestOrder_Random_583) {
    ConfigData cfg{};
    auto cli = Catch::makeCommandLineParser(cfg);

    auto res = ParseArgs(cli, "exe", {"--order", "random"});
    ASSERT_TRUE(res);

    EXPECT_EQ(Catch::TestRunOrder::Randomized, cfg.runOrder);
}

TEST(MakeCommandLineParserTest_583, SetVerbosity_Quiet_583) {
    ConfigData cfg{};
    auto cli = Catch::makeCommandLineParser(cfg);

    auto res = ParseArgs(cli, "exe", {"--verbosity", "quiet"});
    ASSERT_TRUE(res);

    EXPECT_EQ(Catch::Verbosity::Quiet, cfg.verbosity);
}

TEST(MakeCommandLineParserTest_583, SetVerbosity_Normal_583) {
    ConfigData cfg{};
    auto cli = Catch::makeCommandLineParser(cfg);

    auto res = ParseArgs(cli, "exe", {"--verbosity", "normal"});
    ASSERT_TRUE(res);

    EXPECT_EQ(Catch::Verbosity::Normal, cfg.verbosity);
}

TEST(MakeCommandLineParserTest_583, SetVerbosity_High_583) {
    ConfigData cfg{};
    auto cli = Catch::makeCommandLineParser(cfg);

    auto res = ParseArgs(cli, "exe", {"--verbosity", "high"});
    ASSERT_TRUE(res);

    EXPECT_EQ(Catch::Verbosity::High, cfg.verbosity);
}

TEST(MakeCommandLineParserTest_583, SetWaitForKeypress_Both_583) {
    ConfigData cfg{};
    auto cli = Catch::makeCommandLineParser(cfg);

    auto res = ParseArgs(cli, "exe", {"--wait-for-keypress", "both"});
    ASSERT_TRUE(res);

    EXPECT_EQ(Catch::WaitForKeypress::BeforeStartAndExit, cfg.waitForKeypress);
}

TEST(MakeCommandLineParserTest_583, SetShardCountAndIndex_Valid_583) {
    ConfigData cfg{};
    auto cli = Catch::makeCommandLineParser(cfg);

    auto res = ParseArgs(cli, "exe", {"--shard-count", "3", "--shard-index", "2"});
    ASSERT_TRUE(res);

    EXPECT_EQ(3u, cfg.shardCount);
    EXPECT_EQ(2u, cfg.shardIndex);
}

TEST(MakeCommandLineParserTest_583, LoadTestNamesFromFile_ParsesNonCommentNonEmpty_583) {
    // Create a temporary file with various lines.
    const std::string fname = "cli_tests_583.tmp";
    {
        std::ofstream out(fname.c_str());
        ASSERT_TRUE(out.is_open());
        out << "# comment line\n";
        out << "  FooTest  \n";
        out << "\n";
        out << "BarTest\n";
        out << "  # another comment\n";
        out << "\"AlreadyQuoted\"\n";
    }

    ConfigData cfg{};
    auto cli = Catch::makeCommandLineParser(cfg);

    auto res = ParseArgs(cli, "exe", {"--input-file", fname});
    ASSERT_TRUE(res);

    // Expected behavior (from observable effects in code):
    // - lines trimmed
    // - comments & empty lines skipped
    // - unquoted names are wrapped with quotes
    // - names are separated by commas (inserted and last comma removed)
    // So resulting vector should interleave entries like:  "FooTest", ",", "BarTest", ",", "\"AlreadyQuoted\"" (without trailing comma)
    ASSERT_FALSE(cfg.testsOrTags.empty());

    // Reconstruct the effective pattern to check there is no trailing comma and commas between.
    std::string concatenated;
    for (auto const& s : cfg.testsOrTags) concatenated += s;

    // Should be exactly: "FooTest","BarTest","\"AlreadyQuoted\"" with commas between,
    // but since the code inserts ',' as separate items, we just assert structure:
    // no trailing comma and contains the expected names quoted at least once.
    EXPECT_NE(std::string::npos, concatenated.find("\"FooTest\""));
    EXPECT_NE(std::string::npos, concatenated.find("\"BarTest\""));
    EXPECT_NE(std::string::npos, concatenated.find("\"AlreadyQuoted\""));
    EXPECT_NE(std::string::npos, concatenated.find(","));
    EXPECT_NE(',', concatenated.back());

    // Cleanup
    std::remove(fname.c_str());
}

// ---------- Boundary & error cases ----------

TEST(MakeCommandLineParserTest_583, Warn_UnrecognizedOption_IsError_583) {
    ConfigData cfg{};
    auto cli = Catch::makeCommandLineParser(cfg);

    auto res = ParseArgs(cli, "exe", {"--warn", "TotallyNotAWarning"});
    ASSERT_FALSE(res);
    EXPECT_EQ(ParseResultType::NoMatch /* or runtime error propagates as failure */, res.type());
}

TEST(MakeCommandLineParserTest_583, SetTestOrder_Unrecognized_IsError_583) {
    ConfigData cfg{};
    auto cli = Catch::makeCommandLineParser(cfg);

    auto res = ParseArgs(cli, "exe", {"--order", "unknown-ordering"});
    ASSERT_FALSE(res);
    EXPECT_NE(ParseResultType::Matched, res.type());
}

TEST(MakeCommandLineParserTest_583, SetVerbosity_Unrecognized_IsError_583) {
    ConfigData cfg{};
    auto cli = Catch::makeCommandLineParser(cfg);

    auto res = ParseArgs(cli, "exe", {"--verbosity", "LOUDER"});
    ASSERT_FALSE(res);
    EXPECT_NE(ParseResultType::Matched, res.type());
}

TEST(MakeCommandLineParserTest_583, RngSeed_CannotParse_IsError_583) {
    ConfigData cfg{};
    auto cli = Catch::makeCommandLineParser(cfg);

    auto res = ParseArgs(cli, "exe", {"--rng-seed", "not-a-number"});
    ASSERT_FALSE(res);
    EXPECT_NE(ParseResultType::Matched, res.type());
}

TEST(MakeCommandLineParserTest_583, ShardCount_Zero_IsError_583) {
    ConfigData cfg{};
    auto cli = Catch::makeCommandLineParser(cfg);

    auto res = ParseArgs(cli, "exe", {"--shard-count", "0"});
    ASSERT_FALSE(res);
    EXPECT_NE(ParseResultType::Matched, res.type());
}

TEST(MakeCommandLineParserTest_583, ShardCount_NotANumber_IsError_583) {
    ConfigData cfg{};
    auto cli = Catch::makeCommandLineParser(cfg);

    auto res = ParseArgs(cli, "exe", {"--shard-count", "abc"});
    ASSERT_FALSE(res);
    EXPECT_NE(ParseResultType::Matched, res.type());
}

TEST(MakeCommandLineParserTest_583, ShardIndex_NotANumber_IsError_583) {
    ConfigData cfg{};
    auto cli = Catch::makeCommandLineParser(cfg);

    auto res = ParseArgs(cli, "exe", {"--shard-index", "x"});
    ASSERT_FALSE(res);
    EXPECT_NE(ParseResultType::Matched, res.type());
}

TEST(MakeCommandLineParserTest_583, InputFile_DoesNotExist_IsError_583) {
    ConfigData cfg{};
    auto cli = Catch::makeCommandLineParser(cfg);

    auto res = ParseArgs(cli, "exe", {"--input-file", "this_file_should_not_exist_583.txt"});
    ASSERT_FALSE(res);
    EXPECT_NE(ParseResultType::Matched, res.type());
}
