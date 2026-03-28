#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_common_base.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_istream.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_reusable_string_stream.hpp"

#include <sstream>
#include <vector>
#include <string>
#include <memory>

using namespace Catch;

// Mock IConfig
class MockConfig : public IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(const TestSpec&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

// A simple IStream wrapper around a stringstream
class StringIStream : public Catch::IStream {
public:
    std::ostringstream m_oss;
    std::ostream& stream() override { return m_oss; }
    std::string str() const { return m_oss.str(); }
};

class ReporterBaseTest_777 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig_ = new ::testing::NiceMock<MockConfig>();
        ON_CALL(*mockConfig_, verbosity()).WillByDefault(::testing::Return(Verbosity::Normal));
        ON_CALL(*mockConfig_, defaultColourMode()).WillByDefault(::testing::Return(ColourMode::None));
    }

    void TearDown() override {
        // Config lifetime is managed externally (raw pointer to IConfig)
    }

    std::unique_ptr<ReporterBase> makeReporter(StringIStream*& outStream) {
        auto streamPtr = Detail::make_unique<StringIStream>();
        outStream = streamPtr.get();
        ReporterConfig config(mockConfig_, CATCH_MOVE(streamPtr), ColourMode::None, {});
        return std::make_unique<ReporterBase>(CATCH_MOVE(config));
    }

    ::testing::NiceMock<MockConfig>* mockConfig_ = nullptr;
};

// Test that listReporters with an empty vector produces some output (or at least doesn't crash)
TEST_F(ReporterBaseTest_777, ListReportersEmptyDescriptions_777) {
    StringIStream* stream = nullptr;
    auto reporter = makeReporter(stream);

    std::vector<ReporterDescription> descriptions;
    ASSERT_NO_THROW(reporter->listReporters(descriptions));
    // With empty descriptions, output may be empty or contain a header
    // We just verify no crash and the function completes
}

// Test that listReporters with one description produces output containing the reporter name
TEST_F(ReporterBaseTest_777, ListReportersSingleDescription_777) {
    StringIStream* stream = nullptr;
    auto reporter = makeReporter(stream);

    std::vector<ReporterDescription> descriptions;
    descriptions.push_back({"test_reporter", "A test reporter description"});

    reporter->listReporters(descriptions);

    std::string output = stream->str();
    EXPECT_THAT(output, ::testing::HasSubstr("test_reporter"));
}

// Test that listReporters with multiple descriptions lists all of them
TEST_F(ReporterBaseTest_777, ListReportersMultipleDescriptions_777) {
    StringIStream* stream = nullptr;
    auto reporter = makeReporter(stream);

    std::vector<ReporterDescription> descriptions;
    descriptions.push_back({"reporter_a", "First reporter"});
    descriptions.push_back({"reporter_b", "Second reporter"});
    descriptions.push_back({"reporter_c", "Third reporter"});

    reporter->listReporters(descriptions);

    std::string output = stream->str();
    EXPECT_THAT(output, ::testing::HasSubstr("reporter_a"));
    EXPECT_THAT(output, ::testing::HasSubstr("reporter_b"));
    EXPECT_THAT(output, ::testing::HasSubstr("reporter_c"));
}

// Test that listReporters uses the verbosity from config
TEST_F(ReporterBaseTest_777, ListReportersNormalVerbosity_777) {
    EXPECT_CALL(*mockConfig_, verbosity())
        .WillRepeatedly(::testing::Return(Verbosity::Normal));

    StringIStream* stream = nullptr;
    auto reporter = makeReporter(stream);

    std::vector<ReporterDescription> descriptions;
    descriptions.push_back({"my_reporter", "My description"});

    reporter->listReporters(descriptions);

    std::string output = stream->str();
    EXPECT_THAT(output, ::testing::HasSubstr("my_reporter"));
}

// Test that listReporters with high verbosity includes description text
TEST_F(ReporterBaseTest_777, ListReportersHighVerbosity_777) {
    EXPECT_CALL(*mockConfig_, verbosity())
        .WillRepeatedly(::testing::Return(Verbosity::High));

    StringIStream* stream = nullptr;
    auto reporter = makeReporter(stream);

    std::vector<ReporterDescription> descriptions;
    descriptions.push_back({"verbose_reporter", "Detailed description of reporter"});

    reporter->listReporters(descriptions);

    std::string output = stream->str();
    EXPECT_THAT(output, ::testing::HasSubstr("verbose_reporter"));
    // High verbosity should include the description
    EXPECT_THAT(output, ::testing::HasSubstr("Detailed description of reporter"));
}

// Test that listListeners with empty vector doesn't crash
TEST_F(ReporterBaseTest_777, ListListenersEmpty_777) {
    StringIStream* stream = nullptr;
    auto reporter = makeReporter(stream);

    std::vector<ListenerDescription> descriptions;
    ASSERT_NO_THROW(reporter->listListeners(descriptions));
}

// Test that listListeners outputs listener names
TEST_F(ReporterBaseTest_777, ListListenersSingleDescription_777) {
    StringIStream* stream = nullptr;
    auto reporter = makeReporter(stream);

    std::vector<ListenerDescription> descriptions;
    descriptions.push_back({"test_listener", "A test listener"});

    reporter->listListeners(descriptions);

    std::string output = stream->str();
    EXPECT_THAT(output, ::testing::HasSubstr("test_listener"));
}

// Test listTests with empty vector
TEST_F(ReporterBaseTest_777, ListTestsEmpty_777) {
    StringIStream* stream = nullptr;
    auto reporter = makeReporter(stream);

    std::vector<TestCaseHandle> tests;
    ASSERT_NO_THROW(reporter->listTests(tests));
}

// Test listTags with empty vector
TEST_F(ReporterBaseTest_777, ListTagsEmpty_777) {
    StringIStream* stream = nullptr;
    auto reporter = makeReporter(stream);

    std::vector<TagInfo> tags;
    ASSERT_NO_THROW(reporter->listTags(tags));
}

// Test that listReporters with quiet verbosity produces minimal or no output for descriptions
TEST_F(ReporterBaseTest_777, ListReportersQuietVerbosity_777) {
    EXPECT_CALL(*mockConfig_, verbosity())
        .WillRepeatedly(::testing::Return(Verbosity::Quiet));

    StringIStream* stream = nullptr;
    auto reporter = makeReporter(stream);

    std::vector<ReporterDescription> descriptions;
    descriptions.push_back({"quiet_reporter", "Should be quiet"});

    reporter->listReporters(descriptions);

    std::string output = stream->str();
    // Reporter name should still appear even in quiet mode
    EXPECT_THAT(output, ::testing::HasSubstr("quiet_reporter"));
}

// Test that the reporter writes to the stream provided via ReporterConfig
TEST_F(ReporterBaseTest_777, ListReportersWritesToCorrectStream_777) {
    StringIStream* stream = nullptr;
    auto reporter = makeReporter(stream);

    EXPECT_TRUE(stream->str().empty());

    std::vector<ReporterDescription> descriptions;
    descriptions.push_back({"stream_test_reporter", "Testing stream output"});

    reporter->listReporters(descriptions);

    // After listing, stream should have content
    EXPECT_FALSE(stream->str().empty());
}

// Test destruction doesn't crash
TEST_F(ReporterBaseTest_777, DestructorDoesNotCrash_777) {
    StringIStream* stream = nullptr;
    {
        auto reporter = makeReporter(stream);
        // Reporter goes out of scope
    }
    SUCCEED();
}
