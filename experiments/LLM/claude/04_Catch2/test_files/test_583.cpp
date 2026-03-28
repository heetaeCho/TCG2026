#include "catch2/internal/catch_commandline.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_clara.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include "catch2/internal/catch_random_seed_generation.hpp"

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <sstream>

class CommandLineParserTest_583 : public ::testing::Test {
protected:
    Catch::ConfigData config;
    
    void SetUp() override {
        config = Catch::ConfigData{};
    }
    
    Catch::Clara::Detail::InternalParseResult parseArgs(std::vector<std::string> args) {
        auto parser = Catch::makeCommandLineParser(config);
        // First element is exe name
        std::string exeName = "test_exe";
        
        // Build token stream from args
        // We need to use Clara's parse interface
        // Clara expects: parser.parse(exeName, TokenStream(args))
        // Let's construct the full command line
        std::vector<const char*> cargs;
        cargs.push_back(exeName.c_str());
        for (auto& a : args) {
            cargs.push_back(a.c_str());
        }
        
        auto result = parser.parse(std::string(cargs[0]), 
            Catch::Clara::Detail::TokenStream(
                static_cast<int>(cargs.size()) - 1, 
                cargs.data() + 1));
        return result;
    }
};

// Test default config values
TEST_F(CommandLineParserTest_583, DefaultConfigValues_583) {
    auto parser = Catch::makeCommandLineParser(config);
    EXPECT_FALSE(config.showHelp);
    EXPECT_FALSE(config.showSuccessfulTests);
    EXPECT_FALSE(config.shouldDebugBreak);
    EXPECT_FALSE(config.noThrow);
    EXPECT_FALSE(config.showInvisibles);
    EXPECT_EQ(config.abortAfter, -1);
    EXPECT_EQ(config.verbosity, Catch::Verbosity::Normal);
    EXPECT_EQ(config.warnings, Catch::WarnAbout::Nothing);
    EXPECT_EQ(config.runOrder, Catch::TestRunOrder::Declared);
    EXPECT_EQ(config.waitForKeypress, Catch::WaitForKeypress::Never);
}

// Test --success flag
TEST_F(CommandLineParserTest_583, SuccessFlag_583) {
    auto result = parseArgs({"--success"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(config.showSuccessfulTests);
}

// Test -s flag (short form of --success)
TEST_F(CommandLineParserTest_583, SuccessFlagShort_583) {
    auto result = parseArgs({"-s"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(config.showSuccessfulTests);
}

// Test --break flag
TEST_F(CommandLineParserTest_583, BreakFlag_583) {
    auto result = parseArgs({"--break"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(config.shouldDebugBreak);
}

// Test -b flag
TEST_F(CommandLineParserTest_583, BreakFlagShort_583) {
    auto result = parseArgs({"-b"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(config.shouldDebugBreak);
}

// Test --nothrow flag
TEST_F(CommandLineParserTest_583, NoThrowFlag_583) {
    auto result = parseArgs({"--nothrow"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(config.noThrow);
}

// Test --invisibles flag
TEST_F(CommandLineParserTest_583, InvisiblesFlag_583) {
    auto result = parseArgs({"--invisibles"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(config.showInvisibles);
}

// Test --abort flag sets abortAfter to 1
TEST_F(CommandLineParserTest_583, AbortFlag_583) {
    auto result = parseArgs({"--abort"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.abortAfter, 1);
}

// Test -a flag
TEST_F(CommandLineParserTest_583, AbortFlagShort_583) {
    auto result = parseArgs({"-a"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.abortAfter, 1);
}

// Test --abortx with a number
TEST_F(CommandLineParserTest_583, AbortXFlag_583) {
    auto result = parseArgs({"--abortx", "5"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.abortAfter, 5);
}

// Test -x with a number
TEST_F(CommandLineParserTest_583, AbortXFlagShort_583) {
    auto result = parseArgs({"-x", "3"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.abortAfter, 3);
}

// Test --out option
TEST_F(CommandLineParserTest_583, OutputFilename_583) {
    auto result = parseArgs({"--out", "output.txt"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.defaultOutputFilename, "output.txt");
}

// Test -o option
TEST_F(CommandLineParserTest_583, OutputFilenameShort_583) {
    auto result = parseArgs({"-o", "output.txt"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.defaultOutputFilename, "output.txt");
}

// Test --name option
TEST_F(CommandLineParserTest_583, NameOption_583) {
    auto result = parseArgs({"--name", "MySuite"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.name, "MySuite");
}

// Test -n option
TEST_F(CommandLineParserTest_583, NameOptionShort_583) {
    auto result = parseArgs({"-n", "MySuite"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.name, "MySuite");
}

// Test --warn NoAssertions
TEST_F(CommandLineParserTest_583, WarnNoAssertions_583) {
    auto result = parseArgs({"--warn", "NoAssertions"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(config.warnings & Catch::WarnAbout::NoAssertions);
}

// Test --warn UnmatchedTestSpec
TEST_F(CommandLineParserTest_583, WarnUnmatchedTestSpec_583) {
    auto result = parseArgs({"--warn", "UnmatchedTestSpec"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(config.warnings & Catch::WarnAbout::UnmatchedTestSpec);
}

// Test --warn with invalid warning
TEST_F(CommandLineParserTest_583, WarnInvalid_583) {
    auto result = parseArgs({"--warn", "InvalidWarning"});
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test --durations yes
TEST_F(CommandLineParserTest_583, DurationsYes_583) {
    auto result = parseArgs({"--durations", "yes"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.showDurations, Catch::ShowDurations::Always);
}

// Test --durations no
TEST_F(CommandLineParserTest_583, DurationsNo_583) {
    auto result = parseArgs({"--durations", "no"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.showDurations, Catch::ShowDurations::Never);
}

// Test --min-duration
TEST_F(CommandLineParserTest_583, MinDuration_583) {
    auto result = parseArgs({"--min-duration", "0.5"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_DOUBLE_EQ(config.minDuration, 0.5);
}

// Test --filenames-as-tags
TEST_F(CommandLineParserTest_583, FilenamesAsTags_583) {
    auto result = parseArgs({"--filenames-as-tags"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(config.filenamesAsTags);
}

// Test --section
TEST_F(CommandLineParserTest_583, SectionOption_583) {
    auto result = parseArgs({"--section", "mysection"});
    EXPECT_TRUE(static_cast<bool>(result));
    ASSERT_EQ(config.sectionsToRun.size(), 1u);
    EXPECT_EQ(config.sectionsToRun[0], "mysection");
}

// Test --verbosity quiet
TEST_F(CommandLineParserTest_583, VerbosityQuiet_583) {
    auto result = parseArgs({"--verbosity", "quiet"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.verbosity, Catch::Verbosity::Quiet);
}

// Test --verbosity normal
TEST_F(CommandLineParserTest_583, VerbosityNormal_583) {
    auto result = parseArgs({"--verbosity", "normal"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.verbosity, Catch::Verbosity::Normal);
}

// Test --verbosity high
TEST_F(CommandLineParserTest_583, VerbosityHigh_583) {
    auto result = parseArgs({"--verbosity", "high"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.verbosity, Catch::Verbosity::High);
}

// Test --verbosity with invalid value
TEST_F(CommandLineParserTest_583, VerbosityInvalid_583) {
    auto result = parseArgs({"--verbosity", "invalid"});
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test --list-tests
TEST_F(CommandLineParserTest_583, ListTests_583) {
    auto result = parseArgs({"--list-tests"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(config.listTests);
}

// Test --list-tags
TEST_F(CommandLineParserTest_583, ListTags_583) {
    auto result = parseArgs({"--list-tags"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(config.listTags);
}

// Test --list-reporters
TEST_F(CommandLineParserTest_583, ListReporters_583) {
    auto result = parseArgs({"--list-reporters"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(config.listReporters);
}

// Test --list-listeners
TEST_F(CommandLineParserTest_583, ListListeners_583) {
    auto result = parseArgs({"--list-listeners"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(config.listListeners);
}

// Test --order declared
TEST_F(CommandLineParserTest_583, OrderDeclared_583) {
    auto result = parseArgs({"--order", "decl"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.runOrder, Catch::TestRunOrder::Declared);
}

// Test --order lexical
TEST_F(CommandLineParserTest_583, OrderLexical_583) {
    auto result = parseArgs({"--order", "lex"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.runOrder, Catch::TestRunOrder::LexicographicallySorted);
}

// Test --order random
TEST_F(CommandLineParserTest_583, OrderRandom_583) {
    auto result = parseArgs({"--order", "rand"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.runOrder, Catch::TestRunOrder::Randomized);
}

// Test --order with invalid value
TEST_F(CommandLineParserTest_583, OrderInvalid_583) {
    auto result = parseArgs({"--order", "invalid"});
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test --rng-seed with numeric value
TEST_F(CommandLineParserTest_583, RngSeedNumeric_583) {
    auto result = parseArgs({"--rng-seed", "42"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.rngSeed, 42u);
}

// Test --rng-seed with zero
TEST_F(CommandLineParserTest_583, RngSeedZero_583) {
    auto result = parseArgs({"--rng-seed", "0"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.rngSeed, 0u);
}

// Test --rng-seed time
TEST_F(CommandLineParserTest_583, RngSeedTime_583) {
    auto result = parseArgs({"--rng-seed", "time"});
    EXPECT_TRUE(static_cast<bool>(result));
    // We can't know the exact seed, but it should have been set
}

// Test --rng-seed random-device
TEST_F(CommandLineParserTest_583, RngSeedRandomDevice_583) {
    auto result = parseArgs({"--rng-seed", "random-device"});
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test --rng-seed with invalid string
TEST_F(CommandLineParserTest_583, RngSeedInvalid_583) {
    auto result = parseArgs({"--rng-seed", "not-a-number"});
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test --wait-for-keypress never
TEST_F(CommandLineParserTest_583, WaitForKeypressNever_583) {
    auto result = parseArgs({"--wait-for-keypress", "never"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.waitForKeypress, Catch::WaitForKeypress::Never);
}

// Test --wait-for-keypress start
TEST_F(CommandLineParserTest_583, WaitForKeypressStart_583) {
    auto result = parseArgs({"--wait-for-keypress", "start"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.waitForKeypress, Catch::WaitForKeypress::BeforeStart);
}

// Test --wait-for-keypress exit
TEST_F(CommandLineParserTest_583, WaitForKeypressExit_583) {
    auto result = parseArgs({"--wait-for-keypress", "exit"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.waitForKeypress, Catch::WaitForKeypress::BeforeExit);
}

// Test --wait-for-keypress both
TEST_F(CommandLineParserTest_583, WaitForKeypressBoth_583) {
    auto result = parseArgs({"--wait-for-keypress", "both"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.waitForKeypress, Catch::WaitForKeypress::BeforeStartAndExit);
}

// Test --wait-for-keypress with invalid value
TEST_F(CommandLineParserTest_583, WaitForKeypressInvalid_583) {
    auto result = parseArgs({"--wait-for-keypress", "invalid"});
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test --libidentify
TEST_F(CommandLineParserTest_583, LibIdentify_583) {
    auto result = parseArgs({"--libidentify"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(config.libIdentify);
}

// Test --skip-benchmarks
TEST_F(CommandLineParserTest_583, SkipBenchmarks_583) {
    auto result = parseArgs({"--skip-benchmarks"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(config.skipBenchmarks);
}

// Test --benchmark-samples
TEST_F(CommandLineParserTest_583, BenchmarkSamples_583) {
    auto result = parseArgs({"--benchmark-samples", "200"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.benchmarkSamples, 200u);
}

// Test --benchmark-resamples
TEST_F(CommandLineParserTest_583, BenchmarkResamples_583) {
    auto result = parseArgs({"--benchmark-resamples", "50000"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.benchmarkResamples, 50000u);
}

// Test --benchmark-confidence-interval
TEST_F(CommandLineParserTest_583, BenchmarkConfidenceInterval_583) {
    auto result = parseArgs({"--benchmark-confidence-interval", "0.99"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval, 0.99);
}

// Test --benchmark-no-analysis
TEST_F(CommandLineParserTest_583, BenchmarkNoAnalysis_583) {
    auto result = parseArgs({"--benchmark-no-analysis"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(config.benchmarkNoAnalysis);
}

// Test --benchmark-warmup-time
TEST_F(CommandLineParserTest_583, BenchmarkWarmupTime_583) {
    auto result = parseArgs({"--benchmark-warmup-time", "200"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.benchmarkWarmupTime, 200);
}

// Test --shard-count with valid value
TEST_F(CommandLineParserTest_583, ShardCountValid_583) {
    auto result = parseArgs({"--shard-count", "4"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.shardCount, 4u);
}

// Test --shard-count with zero (error)
TEST_F(CommandLineParserTest_583, ShardCountZero_583) {
    auto result = parseArgs({"--shard-count", "0"});
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test --shard-count with invalid value
TEST_F(CommandLineParserTest_583, ShardCountInvalid_583) {
    auto result = parseArgs({"--shard-count", "abc"});
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test --shard-index with valid value
TEST_F(CommandLineParserTest_583, ShardIndexValid_583) {
    auto result = parseArgs({"--shard-index", "2"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.shardIndex, 2u);
}

// Test --shard-index with invalid value
TEST_F(CommandLineParserTest_583, ShardIndexInvalid_583) {
    auto result = parseArgs({"--shard-index", "abc"});
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test --allow-running-no-tests
TEST_F(CommandLineParserTest_583, AllowRunningNoTests_583) {
    auto result = parseArgs({"--allow-running-no-tests"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(config.allowZeroTests);
}

// Test positional arguments (test names/patterns)
TEST_F(CommandLineParserTest_583, PositionalTestNames_583) {
    auto result = parseArgs({"TestName1"});
    EXPECT_TRUE(static_cast<bool>(result));
    ASSERT_GE(config.testsOrTags.size(), 1u);
    EXPECT_EQ(config.testsOrTags[0], "TestName1");
}

// Test process name is set
TEST_F(CommandLineParserTest_583, ProcessNameSet_583) {
    auto parser = Catch::makeCommandLineParser(config);
    std::vector<const char*> args = {"my_test_exe"};
    auto result = parser.parse(std::string("my_test_exe"),
        Catch::Clara::Detail::TokenStream(0, args.data() + 1));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.processName, "my_test_exe");
}

// Test --input-file with non-existent file
TEST_F(CommandLineParserTest_583, InputFileNonExistent_583) {
    auto result = parseArgs({"--input-file", "this_file_does_not_exist_12345.txt"});
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test help flag
TEST_F(CommandLineParserTest_583, HelpFlag_583) {
    auto result = parseArgs({"--help"});
    // Help typically results in successful parse with showHelp set
    EXPECT_TRUE(config.showHelp);
}

// Test -h flag
TEST_F(CommandLineParserTest_583, HelpFlagShort_583) {
    auto result = parseArgs({"-h"});
    EXPECT_TRUE(config.showHelp);
}

// Test -? flag
TEST_F(CommandLineParserTest_583, HelpFlagQuestion_583) {
    auto result = parseArgs({"-?"});
    EXPECT_TRUE(config.showHelp);
}

// Test multiple options combined
TEST_F(CommandLineParserTest_583, MultipleOptions_583) {
    auto result = parseArgs({"--success", "--break", "--nothrow", "--verbosity", "high"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(config.showSuccessfulTests);
    EXPECT_TRUE(config.shouldDebugBreak);
    EXPECT_TRUE(config.noThrow);
    EXPECT_EQ(config.verbosity, Catch::Verbosity::High);
}

// Test --warn with multiple warnings
TEST_F(CommandLineParserTest_583, MultipleWarnings_583) {
    auto result = parseArgs({"--warn", "NoAssertions", "--warn", "UnmatchedTestSpec"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(config.warnings & Catch::WarnAbout::NoAssertions);
    EXPECT_TRUE(config.warnings & Catch::WarnAbout::UnmatchedTestSpec);
}

// Test empty arguments parse successfully
TEST_F(CommandLineParserTest_583, EmptyArguments_583) {
    auto result = parseArgs({});
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test --reporter with empty string
TEST_F(CommandLineParserTest_583, ReporterEmptyString_583) {
    auto result = parseArgs({"--reporter", ""});
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test --reporter with console (which should be a default available reporter)
TEST_F(CommandLineParserTest_583, ReporterConsole_583) {
    auto result = parseArgs({"--reporter", "console"});
    EXPECT_TRUE(static_cast<bool>(result));
    ASSERT_EQ(config.reporterSpecifications.size(), 1u);
    EXPECT_EQ(config.reporterSpecifications[0].name(), "console");
}

// Test --reporter with unknown reporter
TEST_F(CommandLineParserTest_583, ReporterUnknown_583) {
    auto result = parseArgs({"--reporter", "nonexistent_reporter_xyz"});
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test multiple sections
TEST_F(CommandLineParserTest_583, MultipleSections_583) {
    auto result = parseArgs({"--section", "sec1", "--section", "sec2"});
    EXPECT_TRUE(static_cast<bool>(result));
    ASSERT_EQ(config.sectionsToRun.size(), 2u);
    EXPECT_EQ(config.sectionsToRun[0], "sec1");
    EXPECT_EQ(config.sectionsToRun[1], "sec2");
}

// Test --colour-mode none
TEST_F(CommandLineParserTest_583, ColourModeNone_583) {
    auto result = parseArgs({"--colour-mode", "none"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.defaultColourMode, Catch::ColourMode::None);
}

// Test --colour-mode default
TEST_F(CommandLineParserTest_583, ColourModeDefault_583) {
    auto result = parseArgs({"--colour-mode", "default"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.defaultColourMode, Catch::ColourMode::PlatformDefault);
}

// Test --colour-mode ansi
TEST_F(CommandLineParserTest_583, ColourModeAnsi_583) {
    auto result = parseArgs({"--colour-mode", "ansi"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.defaultColourMode, Catch::ColourMode::ANSI);
}

// Test --colour-mode with invalid value
TEST_F(CommandLineParserTest_583, ColourModeInvalid_583) {
    auto result = parseArgs({"--colour-mode", "rainbow"});
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test --shard-index with zero (valid)
TEST_F(CommandLineParserTest_583, ShardIndexZero_583) {
    auto result = parseArgs({"--shard-index", "0"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.shardIndex, 0u);
}

// Test --shard-count 1 (minimum valid)
TEST_F(CommandLineParserTest_583, ShardCountOne_583) {
    auto result = parseArgs({"--shard-count", "1"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.shardCount, 1u);
}

// Test parser creation returns a valid parser
TEST_F(CommandLineParserTest_583, ParserCreation_583) {
    auto parser = Catch::makeCommandLineParser(config);
    // Just ensure it doesn't crash and can be validated
    auto validationResult = parser.validate();
    EXPECT_TRUE(static_cast<bool>(validationResult));
}

// Test --verbosity is case-insensitive
TEST_F(CommandLineParserTest_583, VerbosityCaseInsensitive_583) {
    auto result = parseArgs({"--verbosity", "QUIET"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.verbosity, Catch::Verbosity::Quiet);
}

// Test --wait-for-keypress is case-insensitive
TEST_F(CommandLineParserTest_583, WaitForKeypressCaseInsensitive_583) {
    auto result = parseArgs({"--wait-for-keypress", "START"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.waitForKeypress, Catch::WaitForKeypress::BeforeStart);
}

// Test large rng seed value
TEST_F(CommandLineParserTest_583, RngSeedLargeValue_583) {
    auto result = parseArgs({"--rng-seed", "4294967295"});
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(config.rngSeed, 4294967295u);
}

// Test --rng-seed with negative value (should fail)
TEST_F(CommandLineParserTest_583, RngSeedNegative_583) {
    auto result = parseArgs({"--rng-seed", "-1"});
    EXPECT_FALSE(static_cast<bool>(result));
}
