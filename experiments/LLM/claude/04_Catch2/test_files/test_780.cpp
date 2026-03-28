#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/reporters/catch_reporter_common_base.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/catch_tag_alias_autoregistrar.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>
#include <catch2/internal/catch_istream.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/reporters/catch_reporter_event_listener.hpp>

#include <sstream>
#include <vector>
#include <string>
#include <memory>

// Mock for IConfig
class MockConfig : public Catch::IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(Catch::StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(Catch::ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(const Catch::TestSpec&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(Catch::TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(Catch::ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Catch::Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

// A simple IStream wrapper around a stringstream for capturing output
class StringIStream : public Catch::IStream {
    std::ostringstream m_oss;
public:
    std::ostream& stream() override { return m_oss; }
    std::string str() const { return m_oss.str(); }
};

class ReporterBaseTest_780 : public ::testing::Test {
protected:
    MockConfig mockConfig;
    std::vector<std::string> emptyVec;
    Catch::TestSpec emptySpec;

    void SetUp() override {
        // Set up default expectations for config methods that might be called
        ON_CALL(mockConfig, allowThrows()).WillByDefault(::testing::Return(true));
        ON_CALL(mockConfig, name()).WillByDefault(::testing::Return(Catch::StringRef()));
        ON_CALL(mockConfig, includeSuccessfulResults()).WillByDefault(::testing::Return(false));
        ON_CALL(mockConfig, shouldDebugBreak()).WillByDefault(::testing::Return(false));
        ON_CALL(mockConfig, warnAboutMissingAssertions()).WillByDefault(::testing::Return(false));
        ON_CALL(mockConfig, warnAboutUnmatchedTestSpecs()).WillByDefault(::testing::Return(false));
        ON_CALL(mockConfig, zeroTestsCountAsSuccess()).WillByDefault(::testing::Return(false));
        ON_CALL(mockConfig, abortAfter()).WillByDefault(::testing::Return(-1));
        ON_CALL(mockConfig, showInvisibles()).WillByDefault(::testing::Return(false));
        ON_CALL(mockConfig, showDurations()).WillByDefault(::testing::Return(Catch::ShowDurations::DefaultForReporter));
        ON_CALL(mockConfig, minDuration()).WillByDefault(::testing::Return(-1.0));
        ON_CALL(mockConfig, testSpec()).WillByDefault(::testing::ReturnRef(emptySpec));
        ON_CALL(mockConfig, hasTestFilters()).WillByDefault(::testing::Return(false));
        ON_CALL(mockConfig, getTestsOrTags()).WillByDefault(::testing::ReturnRef(emptyVec));
        ON_CALL(mockConfig, runOrder()).WillByDefault(::testing::Return(Catch::TestRunOrder::Declared));
        ON_CALL(mockConfig, rngSeed()).WillByDefault(::testing::Return(0));
        ON_CALL(mockConfig, shardCount()).WillByDefault(::testing::Return(1));
        ON_CALL(mockConfig, shardIndex()).WillByDefault(::testing::Return(0));
        ON_CALL(mockConfig, defaultColourMode()).WillByDefault(::testing::Return(Catch::ColourMode::None));
        ON_CALL(mockConfig, getSectionsToRun()).WillByDefault(::testing::ReturnRef(emptyVec));
        ON_CALL(mockConfig, verbosity()).WillByDefault(::testing::Return(Catch::Verbosity::Normal));
        ON_CALL(mockConfig, skipBenchmarks()).WillByDefault(::testing::Return(false));
        ON_CALL(mockConfig, benchmarkNoAnalysis()).WillByDefault(::testing::Return(false));
        ON_CALL(mockConfig, benchmarkSamples()).WillByDefault(::testing::Return(100));
        ON_CALL(mockConfig, benchmarkConfidenceInterval()).WillByDefault(::testing::Return(0.95));
        ON_CALL(mockConfig, benchmarkResamples()).WillByDefault(::testing::Return(100000));
        ON_CALL(mockConfig, benchmarkWarmupTime()).WillByDefault(::testing::Return(std::chrono::milliseconds(100)));
    }

    // Helper to create a ReporterConfig with a string stream for output capture
    struct ReporterSetup {
        StringIStream* rawStream; // non-owning pointer
        Catch::Detail::unique_ptr<Catch::ReporterBase> reporter;
    };

    ReporterSetup createReporter() {
        auto streamPtr = Catch::Detail::make_unique<StringIStream>();
        auto* rawStream = streamPtr.get();

        Catch::ReporterConfig config(
            &mockConfig,
            CATCH_MOVE(streamPtr),
            Catch::ColourMode::None,
            {}
        );

        auto reporter = Catch::Detail::make_unique<Catch::ReporterBase>(CATCH_MOVE(config));
        return { rawStream, CATCH_MOVE(reporter) };
    }
};

// Test: listTags with empty vector produces some output (or at least doesn't crash)
TEST_F(ReporterBaseTest_780, ListTagsEmptyVector_780) {
    ON_CALL(mockConfig, hasTestFilters()).WillByDefault(::testing::Return(false));
    auto [stream, reporter] = createReporter();

    std::vector<Catch::TagInfo> emptyTags;
    EXPECT_NO_THROW(reporter->listTags(emptyTags));

    // With empty tags, the output should reflect zero tags
    std::string output = stream->str();
    // We just verify it doesn't crash; output format is implementation detail
}

// Test: listTags with hasTestFilters returning true
TEST_F(ReporterBaseTest_780, ListTagsWithTestFilters_780) {
    ON_CALL(mockConfig, hasTestFilters()).WillByDefault(::testing::Return(true));
    auto [stream, reporter] = createReporter();

    std::vector<Catch::TagInfo> emptyTags;
    EXPECT_NO_THROW(reporter->listTags(emptyTags));
}

// Test: listTags with hasTestFilters returning false
TEST_F(ReporterBaseTest_780, ListTagsWithoutTestFilters_780) {
    ON_CALL(mockConfig, hasTestFilters()).WillByDefault(::testing::Return(false));
    auto [stream, reporter] = createReporter();

    std::vector<Catch::TagInfo> emptyTags;
    EXPECT_NO_THROW(reporter->listTags(emptyTags));
}

// Test: listTags calls hasTestFilters on config
TEST_F(ReporterBaseTest_780, ListTagsCallsHasTestFilters_780) {
    EXPECT_CALL(mockConfig, hasTestFilters()).WillRepeatedly(::testing::Return(false));
    auto [stream, reporter] = createReporter();

    std::vector<Catch::TagInfo> tags;
    reporter->listTags(tags);
}

// Test: listReporters with empty descriptions
TEST_F(ReporterBaseTest_780, ListReportersEmpty_780) {
    auto [stream, reporter] = createReporter();

    std::vector<Catch::ReporterDescription> emptyDescs;
    EXPECT_NO_THROW(reporter->listReporters(emptyDescs));
}

// Test: listListeners with empty descriptions
TEST_F(ReporterBaseTest_780, ListListenersEmpty_780) {
    auto [stream, reporter] = createReporter();

    std::vector<Catch::ListenerDescription> emptyDescs;
    EXPECT_NO_THROW(reporter->listListeners(emptyDescs));
}

// Test: listTests with empty test handles
TEST_F(ReporterBaseTest_780, ListTestsEmpty_780) {
    auto [stream, reporter] = createReporter();

    std::vector<Catch::TestCaseHandle> emptyTests;
    EXPECT_NO_THROW(reporter->listTests(emptyTests));
}

// Test: listTags produces output to stream
TEST_F(ReporterBaseTest_780, ListTagsProducesOutput_780) {
    ON_CALL(mockConfig, hasTestFilters()).WillByDefault(::testing::Return(false));
    auto [stream, reporter] = createReporter();

    std::vector<Catch::TagInfo> emptyTags;
    reporter->listTags(emptyTags);

    // Even with empty tags, the default listing function typically produces some output
    // (like "0 tags" or similar). We verify stream was written to.
    std::string output = stream->str();
    // At minimum, we expect something was written (the summary line)
    EXPECT_FALSE(output.empty());
}

// Test: listReporters produces output to stream
TEST_F(ReporterBaseTest_780, ListReportersProducesOutput_780) {
    auto [stream, reporter] = createReporter();

    std::vector<Catch::ReporterDescription> emptyDescs;
    reporter->listReporters(emptyDescs);

    std::string output = stream->str();
    EXPECT_FALSE(output.empty());
}

// Test: listListeners produces output to stream
TEST_F(ReporterBaseTest_780, ListListenersProducesOutput_780) {
    auto [stream, reporter] = createReporter();

    std::vector<Catch::ListenerDescription> emptyDescs;
    reporter->listListeners(emptyDescs);

    std::string output = stream->str();
    EXPECT_FALSE(output.empty());
}

// Test: listTests produces output to stream
TEST_F(ReporterBaseTest_780, ListTestsProducesOutput_780) {
    auto [stream, reporter] = createReporter();

    std::vector<Catch::TestCaseHandle> emptyTests;
    reporter->listTests(emptyTests);

    std::string output = stream->str();
    EXPECT_FALSE(output.empty());
}

// Test: ReporterBase can be constructed and destructed without issues
TEST_F(ReporterBaseTest_780, ConstructionDestruction_780) {
    EXPECT_NO_THROW({
        auto [stream, reporter] = createReporter();
        // reporter goes out of scope and is destroyed
    });
}

// Test: getPreferences returns valid preferences
TEST_F(ReporterBaseTest_780, GetPreferences_780) {
    auto [stream, reporter] = createReporter();

    const auto& prefs = reporter->getPreferences();
    // Just verify we can access it without crashing
    (void)prefs.shouldRedirectStdOut;
    (void)prefs.shouldReportAllAssertions;
}

// Test: Multiple calls to listTags accumulate output
TEST_F(ReporterBaseTest_780, ListTagsMultipleCalls_780) {
    ON_CALL(mockConfig, hasTestFilters()).WillByDefault(::testing::Return(false));
    auto [stream, reporter] = createReporter();

    std::vector<Catch::TagInfo> emptyTags;
    reporter->listTags(emptyTags);
    std::string firstOutput = stream->str();

    reporter->listTags(emptyTags);
    std::string secondOutput = stream->str();

    // Second output should be longer (accumulated)
    EXPECT_GE(secondOutput.size(), firstOutput.size());
}
