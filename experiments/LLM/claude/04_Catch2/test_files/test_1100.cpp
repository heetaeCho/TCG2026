#include <gtest/gtest.h>
#include <catch2/catch_config.hpp>
#include <catch2/catch_test_spec.hpp>
#include <catch2/internal/catch_reporter_spec_parser.hpp>

using namespace Catch;

class ConfigTest_1100 : public ::testing::Test {
protected:
    ConfigData makeDefaultData() {
        ConfigData data;
        return data;
    }
};

// Test default construction with default ConfigData
TEST_F(ConfigTest_1100, DefaultConfigData_CreatesValidConfig_1100) {
    ConfigData data;
    Config config(data);
    // Should not throw and should create a valid config
    EXPECT_FALSE(config.hasTestFilters());
}

// Test that default reporter is added when no reporter specifications are provided
TEST_F(ConfigTest_1100, DefaultReporterAdded_WhenNoReporterSpecified_1100) {
    ConfigData data;
    Config config(data);
    auto const& specs = config.getProcessedReporterSpecs();
    ASSERT_FALSE(specs.empty());
    // Default reporter should be "console" (or CATCH_CONFIG_DEFAULT_REPORTER if defined)
    EXPECT_EQ(specs[0].name, "console");
}

// Test listTests accessor
TEST_F(ConfigTest_1100, ListTests_ReturnsFalseByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listTests());
}

TEST_F(ConfigTest_1100, ListTests_ReturnsTrueWhenSet_1100) {
    ConfigData data;
    data.listTests = true;
    Config config(data);
    EXPECT_TRUE(config.listTests());
}

// Test listTags accessor
TEST_F(ConfigTest_1100, ListTags_ReturnsFalseByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listTags());
}

TEST_F(ConfigTest_1100, ListTags_ReturnsTrueWhenSet_1100) {
    ConfigData data;
    data.listTags = true;
    Config config(data);
    EXPECT_TRUE(config.listTags());
}

// Test listReporters accessor
TEST_F(ConfigTest_1100, ListReporters_ReturnsFalseByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listReporters());
}

TEST_F(ConfigTest_1100, ListReporters_ReturnsTrueWhenSet_1100) {
    ConfigData data;
    data.listReporters = true;
    Config config(data);
    EXPECT_TRUE(config.listReporters());
}

// Test listListeners accessor
TEST_F(ConfigTest_1100, ListListeners_ReturnsFalseByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.listListeners());
}

TEST_F(ConfigTest_1100, ListListeners_ReturnsTrueWhenSet_1100) {
    ConfigData data;
    data.listListeners = true;
    Config config(data);
    EXPECT_TRUE(config.listListeners());
}

// Test allowThrows accessor
TEST_F(ConfigTest_1100, AllowThrows_ReturnsTrueByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.allowThrows());
}

TEST_F(ConfigTest_1100, AllowThrows_ReturnsFalseWhenNoThrowSet_1100) {
    ConfigData data;
    data.noThrow = true;
    Config config(data);
    EXPECT_FALSE(config.allowThrows());
}

// Test showHelp accessor
TEST_F(ConfigTest_1100, ShowHelp_ReturnsFalseByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.showHelp());
}

TEST_F(ConfigTest_1100, ShowHelp_ReturnsTrueWhenSet_1100) {
    ConfigData data;
    data.showHelp = true;
    Config config(data);
    EXPECT_TRUE(config.showHelp());
}

// Test name accessor
TEST_F(ConfigTest_1100, Name_ReturnsProcessName_1100) {
    ConfigData data;
    data.processName = "TestProcess";
    Config config(data);
    EXPECT_EQ(config.name(), "TestProcess");
}

TEST_F(ConfigTest_1100, Name_ReturnsEmptyByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.name(), "");
}

// Test includeSuccessfulResults accessor
TEST_F(ConfigTest_1100, IncludeSuccessfulResults_ReturnsFalseByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.includeSuccessfulResults());
}

TEST_F(ConfigTest_1100, IncludeSuccessfulResults_ReturnsTrueWhenSet_1100) {
    ConfigData data;
    data.showSuccessfulTests = true;
    Config config(data);
    EXPECT_TRUE(config.includeSuccessfulResults());
}

// Test warnAboutMissingAssertions accessor
TEST_F(ConfigTest_1100, WarnAboutMissingAssertions_ReturnsFalseByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.warnAboutMissingAssertions());
}

// Test warnAboutUnmatchedTestSpecs accessor
TEST_F(ConfigTest_1100, WarnAboutUnmatchedTestSpecs_ReturnsFalseByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());
}

// Test zeroTestsCountAsSuccess accessor
TEST_F(ConfigTest_1100, ZeroTestsCountAsSuccess_ReturnsFalseByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.zeroTestsCountAsSuccess());
}

TEST_F(ConfigTest_1100, ZeroTestsCountAsSuccess_ReturnsTrueWhenSet_1100) {
    ConfigData data;
    data.allowZeroTests = true;
    Config config(data);
    EXPECT_TRUE(config.zeroTestsCountAsSuccess());
}

// Test showDurations accessor
TEST_F(ConfigTest_1100, ShowDurations_ReturnsDefaultForReporterByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);
}

// Test minDuration accessor
TEST_F(ConfigTest_1100, MinDuration_ReturnsNegativeOneByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);
}

TEST_F(ConfigTest_1100, MinDuration_ReturnsSetValue_1100) {
    ConfigData data;
    data.minDuration = 0.5;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.5);
}

// Test runOrder accessor
TEST_F(ConfigTest_1100, RunOrder_ReturnsDeclaredByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);
}

TEST_F(ConfigTest_1100, RunOrder_ReturnsRandomized_1100) {
    ConfigData data;
    data.runOrder = TestRunOrder::Randomized;
    Config config(data);
    EXPECT_EQ(config.runOrder(), TestRunOrder::Randomized);
}

// Test rngSeed accessor
TEST_F(ConfigTest_1100, RngSeed_ReturnsSetValue_1100) {
    ConfigData data;
    data.rngSeed = 42;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 42u);
}

// Test shardCount accessor
TEST_F(ConfigTest_1100, ShardCount_ReturnsOneByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 1u);
}

TEST_F(ConfigTest_1100, ShardCount_ReturnsSetValue_1100) {
    ConfigData data;
    data.shardCount = 5;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 5u);
}

// Test shardIndex accessor
TEST_F(ConfigTest_1100, ShardIndex_ReturnsZeroByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 0u);
}

TEST_F(ConfigTest_1100, ShardIndex_ReturnsSetValue_1100) {
    ConfigData data;
    data.shardIndex = 3;
    Config config(data);
    EXPECT_EQ(config.shardIndex(), 3u);
}

// Test defaultColourMode accessor
TEST_F(ConfigTest_1100, DefaultColourMode_ReturnsPlatformDefaultByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);
}

// Test abortAfter accessor
TEST_F(ConfigTest_1100, AbortAfter_ReturnsNegativeOneByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), -1);
}

TEST_F(ConfigTest_1100, AbortAfter_ReturnsSetValue_1100) {
    ConfigData data;
    data.abortAfter = 3;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 3);
}

// Test showInvisibles accessor
TEST_F(ConfigTest_1100, ShowInvisibles_ReturnsFalseByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.showInvisibles());
}

TEST_F(ConfigTest_1100, ShowInvisibles_ReturnsTrueWhenSet_1100) {
    ConfigData data;
    data.showInvisibles = true;
    Config config(data);
    EXPECT_TRUE(config.showInvisibles());
}

// Test verbosity accessor
TEST_F(ConfigTest_1100, Verbosity_ReturnsNormalByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Normal);
}

TEST_F(ConfigTest_1100, Verbosity_ReturnsHighWhenSet_1100) {
    ConfigData data;
    data.verbosity = Verbosity::High;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::High);
}

// Test skipBenchmarks accessor
TEST_F(ConfigTest_1100, SkipBenchmarks_ReturnsFalseByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.skipBenchmarks());
}

TEST_F(ConfigTest_1100, SkipBenchmarks_ReturnsTrueWhenSet_1100) {
    ConfigData data;
    data.skipBenchmarks = true;
    Config config(data);
    EXPECT_TRUE(config.skipBenchmarks());
}

// Test benchmarkNoAnalysis accessor
TEST_F(ConfigTest_1100, BenchmarkNoAnalysis_ReturnsFalseByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.benchmarkNoAnalysis());
}

TEST_F(ConfigTest_1100, BenchmarkNoAnalysis_ReturnsTrueWhenSet_1100) {
    ConfigData data;
    data.benchmarkNoAnalysis = true;
    Config config(data);
    EXPECT_TRUE(config.benchmarkNoAnalysis());
}

// Test benchmarkSamples accessor
TEST_F(ConfigTest_1100, BenchmarkSamples_Returns100ByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 100u);
}

TEST_F(ConfigTest_1100, BenchmarkSamples_ReturnsSetValue_1100) {
    ConfigData data;
    data.benchmarkSamples = 200;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 200u);
}

// Test benchmarkConfidenceInterval accessor
TEST_F(ConfigTest_1100, BenchmarkConfidenceInterval_ReturnsDefaultValue_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);
}

TEST_F(ConfigTest_1100, BenchmarkConfidenceInterval_ReturnsSetValue_1100) {
    ConfigData data;
    data.benchmarkConfidenceInterval = 0.99;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.99);
}

// Test benchmarkResamples accessor
TEST_F(ConfigTest_1100, BenchmarkResamples_Returns100000ByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 100000u);
}

TEST_F(ConfigTest_1100, BenchmarkResamples_ReturnsSetValue_1100) {
    ConfigData data;
    data.benchmarkResamples = 50000;
    Config config(data);
    EXPECT_EQ(config.benchmarkResamples(), 50000u);
}

// Test benchmarkWarmupTime accessor
TEST_F(ConfigTest_1100, BenchmarkWarmupTime_Returns100msByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(100));
}

TEST_F(ConfigTest_1100, BenchmarkWarmupTime_ReturnsSetValue_1100) {
    ConfigData data;
    data.benchmarkWarmupTime = 500;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(500));
}

// Test hasTestFilters with test specifications
TEST_F(ConfigTest_1100, HasTestFilters_ReturnsTrueWhenTestsOrTagsProvided_1100) {
    ConfigData data;
    data.testsOrTags.push_back("SomeTest");
    Config config(data);
    EXPECT_TRUE(config.hasTestFilters());
}

TEST_F(ConfigTest_1100, HasTestFilters_ReturnsFalseWhenNoTestsOrTags_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.hasTestFilters());
}

// Test getTestsOrTags accessor
TEST_F(ConfigTest_1100, GetTestsOrTags_ReturnsProvidedTests_1100) {
    ConfigData data;
    data.testsOrTags.push_back("Test1");
    data.testsOrTags.push_back("Test2");
    Config config(data);
    auto const& tests = config.getTestsOrTags();
    ASSERT_EQ(tests.size(), 2u);
    EXPECT_EQ(tests[0], "Test1");
    EXPECT_EQ(tests[1], "Test2");
}

// Test getSectionsToRun accessor
TEST_F(ConfigTest_1100, GetSectionsToRun_ReturnsProvidedSections_1100) {
    ConfigData data;
    data.sectionsToRun.push_back("Section1");
    data.sectionsToRun.push_back("Section2");
    Config config(data);
    auto const& sections = config.getSectionsToRun();
    ASSERT_EQ(sections.size(), 2u);
    EXPECT_EQ(sections[0], "Section1");
    EXPECT_EQ(sections[1], "Section2");
}

// Test trimming of testsOrTags
TEST_F(ConfigTest_1100, TestsOrTags_AreTrimmed_1100) {
    ConfigData data;
    data.testsOrTags.push_back("  Test1  ");
    Config config(data);
    auto const& tests = config.getTestsOrTags();
    ASSERT_EQ(tests.size(), 1u);
    EXPECT_EQ(tests[0], "Test1");
}

// Test trimming of sectionsToRun
TEST_F(ConfigTest_1100, SectionsToRun_AreTrimmed_1100) {
    ConfigData data;
    data.sectionsToRun.push_back("  Section1  ");
    Config config(data);
    auto const& sections = config.getSectionsToRun();
    ASSERT_EQ(sections.size(), 1u);
    EXPECT_EQ(sections[0], "Section1");
}

// Test getReporterSpecs returns the correct reporter specifications
TEST_F(ConfigTest_1100, GetReporterSpecs_ReturnsDefaultWhenEmpty_1100) {
    ConfigData data;
    Config config(data);
    auto const& specs = config.getReporterSpecs();
    ASSERT_EQ(specs.size(), 1u);
    EXPECT_EQ(specs[0].name(), "console");
}

// Test with custom reporter specification
TEST_F(ConfigTest_1100, GetReporterSpecs_ReturnsCustomReporter_1100) {
    ConfigData data;
    data.reporterSpecifications.push_back(
        ReporterSpec("xml", Optional<std::string>(), Optional<ColourMode>(), {})
    );
    Config config(data);
    auto const& specs = config.getReporterSpecs();
    ASSERT_EQ(specs.size(), 1u);
    EXPECT_EQ(specs[0].name(), "xml");
}

// Test getProcessedReporterSpecs
TEST_F(ConfigTest_1100, GetProcessedReporterSpecs_HasCorrectName_1100) {
    ConfigData data;
    Config config(data);
    auto const& processed = config.getProcessedReporterSpecs();
    ASSERT_FALSE(processed.empty());
    EXPECT_EQ(processed[0].name, "console");
}

// Test reporter with output file
TEST_F(ConfigTest_1100, ProcessedReporterSpec_UsesOutputFile_1100) {
    ConfigData data;
    data.reporterSpecifications.push_back(
        ReporterSpec("xml", Optional<std::string>("output.xml"), Optional<ColourMode>(), {})
    );
    Config config(data);
    auto const& processed = config.getProcessedReporterSpecs();
    ASSERT_EQ(processed.size(), 1u);
    EXPECT_EQ(processed[0].name, "xml");
    EXPECT_EQ(processed[0].outputFilename, "output.xml");
}

// Test reporter without output file uses default
TEST_F(ConfigTest_1100, ProcessedReporterSpec_UsesDefaultOutputFilename_1100) {
    ConfigData data;
    data.defaultOutputFilename = "default_out.txt";
    data.reporterSpecifications.push_back(
        ReporterSpec("console", Optional<std::string>(), Optional<ColourMode>(), {})
    );
    Config config(data);
    auto const& processed = config.getProcessedReporterSpecs();
    ASSERT_EQ(processed.size(), 1u);
    EXPECT_EQ(processed[0].outputFilename, "default_out.txt");
}

// Test reporter colour mode
TEST_F(ConfigTest_1100, ProcessedReporterSpec_UsesSpecifiedColourMode_1100) {
    ConfigData data;
    data.reporterSpecifications.push_back(
        ReporterSpec("console", Optional<std::string>(), Optional<ColourMode>(ColourMode::ANSI), {})
    );
    Config config(data);
    auto const& processed = config.getProcessedReporterSpecs();
    ASSERT_EQ(processed.size(), 1u);
    EXPECT_EQ(processed[0].colourMode, ColourMode::ANSI);
}

// Test reporter colour mode defaults to ConfigData's defaultColourMode
TEST_F(ConfigTest_1100, ProcessedReporterSpec_UsesDefaultColourMode_1100) {
    ConfigData data;
    data.defaultColourMode = ColourMode::None;
    data.reporterSpecifications.push_back(
        ReporterSpec("console", Optional<std::string>(), Optional<ColourMode>(), {})
    );
    Config config(data);
    auto const& processed = config.getProcessedReporterSpecs();
    ASSERT_EQ(processed.size(), 1u);
    EXPECT_EQ(processed[0].colourMode, ColourMode::None);
}

// Test testSpec accessor returns valid TestSpec
TEST_F(ConfigTest_1100, TestSpec_ReturnsValidTestSpec_1100) {
    ConfigData data;
    Config config(data);
    auto const& spec = config.testSpec();
    EXPECT_FALSE(spec.hasFilters());
}

// Test testSpec with filters
TEST_F(ConfigTest_1100, TestSpec_HasFiltersWhenTestsProvided_1100) {
    ConfigData data;
    data.testsOrTags.push_back("SomeTestName");
    Config config(data);
    auto const& spec = config.testSpec();
    EXPECT_TRUE(spec.hasFilters());
}

// Test shouldDebugBreak accessor (default is false)
TEST_F(ConfigTest_1100, ShouldDebugBreak_ReturnsFalseByDefault_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_FALSE(config.shouldDebugBreak());
}

// Test with empty testsOrTags
TEST_F(ConfigTest_1100, EmptyTestsOrTags_NoFilters_1100) {
    ConfigData data;
    data.testsOrTags = {};
    Config config(data);
    EXPECT_FALSE(config.hasTestFilters());
    EXPECT_TRUE(config.getTestsOrTags().empty());
}

// Test with empty sectionsToRun
TEST_F(ConfigTest_1100, EmptySectionsToRun_ReturnsEmpty_1100) {
    ConfigData data;
    Config config(data);
    EXPECT_TRUE(config.getSectionsToRun().empty());
}

// Test multiple testsOrTags
TEST_F(ConfigTest_1100, MultipleTestsOrTags_AllTrimmed_1100) {
    ConfigData data;
    data.testsOrTags.push_back("  test1  ");
    data.testsOrTags.push_back("  test2  ");
    data.testsOrTags.push_back("test3");
    Config config(data);
    auto const& tests = config.getTestsOrTags();
    ASSERT_EQ(tests.size(), 3u);
    EXPECT_EQ(tests[0], "test1");
    EXPECT_EQ(tests[1], "test2");
    EXPECT_EQ(tests[2], "test3");
}

// Test boundary: abortAfter = 0
TEST_F(ConfigTest_1100, AbortAfter_Zero_1100) {
    ConfigData data;
    data.abortAfter = 0;
    Config config(data);
    EXPECT_EQ(config.abortAfter(), 0);
}

// Test boundary: shardCount = 0
TEST_F(ConfigTest_1100, ShardCount_Zero_1100) {
    ConfigData data;
    data.shardCount = 0;
    Config config(data);
    EXPECT_EQ(config.shardCount(), 0u);
}

// Test boundary: benchmarkSamples = 0
TEST_F(ConfigTest_1100, BenchmarkSamples_Zero_1100) {
    ConfigData data;
    data.benchmarkSamples = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkSamples(), 0u);
}

// Test boundary: rngSeed = 0
TEST_F(ConfigTest_1100, RngSeed_Zero_1100) {
    ConfigData data;
    data.rngSeed = 0;
    Config config(data);
    EXPECT_EQ(config.rngSeed(), 0u);
}

// Test boundary: rngSeed = max uint32
TEST_F(ConfigTest_1100, RngSeed_MaxUint32_1100) {
    ConfigData data;
    data.rngSeed = std::numeric_limits<uint32_t>::max();
    Config config(data);
    EXPECT_EQ(config.rngSeed(), std::numeric_limits<uint32_t>::max());
}

// Test benchmarkWarmupTime = 0
TEST_F(ConfigTest_1100, BenchmarkWarmupTime_Zero_1100) {
    ConfigData data;
    data.benchmarkWarmupTime = 0;
    Config config(data);
    EXPECT_EQ(config.benchmarkWarmupTime(), std::chrono::milliseconds(0));
}

// Test minDuration = 0
TEST_F(ConfigTest_1100, MinDuration_Zero_1100) {
    ConfigData data;
    data.minDuration = 0.0;
    Config config(data);
    EXPECT_DOUBLE_EQ(config.minDuration(), 0.0);
}

// Test Verbosity::Quiet
TEST_F(ConfigTest_1100, Verbosity_Quiet_1100) {
    ConfigData data;
    data.verbosity = Verbosity::Quiet;
    Config config(data);
    EXPECT_EQ(config.verbosity(), Verbosity::Quiet);
}

// Test processName with special characters
TEST_F(ConfigTest_1100, Name_SpecialCharacters_1100) {
    ConfigData data;
    data.processName = "my-test_process.exe";
    Config config(data);
    EXPECT_EQ(config.name(), "my-test_process.exe");
}
