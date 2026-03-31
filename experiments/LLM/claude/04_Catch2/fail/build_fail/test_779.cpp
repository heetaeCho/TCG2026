#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_common_base.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_istream.hpp"
#include "catch2/catch_session.hpp"
#include "catch2/internal/catch_stream.hpp"
#include "catch2/catch_tag_alias_autoregistrar.hpp"

#include <vector>
#include <string>
#include <sstream>

using namespace Catch;
using ::testing::_;
using ::testing::Return;
using ::testing::ReturnRef;

// Mock for IConfig
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

// Helper to create a string-based IStream
class StringIStream : public IStream {
    std::ostringstream m_oss;
public:
    std::ostream& stream() override { return m_oss; }
    std::string str() const { return m_oss.str(); }
};

class ReporterBaseTest_779 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig_ = new MockConfig();
        
        // Set up default expectations
        ON_CALL(*mockConfig_, hasTestFilters()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, verbosity()).WillByDefault(Return(Verbosity::Normal));
        ON_CALL(*mockConfig_, defaultColourMode()).WillByDefault(Return(ColourMode::None));
    }

    void TearDown() override {
        // Config is owned by the test, reporter just holds a pointer
    }

    MockConfig* mockConfig_;
};

// Test: listTests with empty vector produces some output (or at least doesn't crash)
TEST_F(ReporterBaseTest_779, ListTestsWithEmptyVector_779) {
    auto streamPtr = Detail::unique_ptr<IStream>(new StringIStream());
    auto* rawStream = static_cast<StringIStream*>(streamPtr.get());
    
    std::map<std::string, std::string> customOptions;
    ReporterConfig config(mockConfig_, CATCH_MOVE(streamPtr), ColourMode::None, customOptions);
    ReporterBase reporter(CATCH_MOVE(config));

    std::vector<TestCaseHandle> emptyTests;
    
    EXPECT_CALL(*mockConfig_, hasTestFilters()).Times(::testing::AtLeast(1));
    EXPECT_CALL(*mockConfig_, verbosity()).Times(::testing::AtLeast(1));
    
    ASSERT_NO_THROW(reporter.listTests(emptyTests));
}

// Test: listTests with hasTestFilters returning true
TEST_F(ReporterBaseTest_779, ListTestsWithTestFilters_779) {
    auto streamPtr = Detail::unique_ptr<IStream>(new StringIStream());
    auto* rawStream = static_cast<StringIStream*>(streamPtr.get());
    
    ON_CALL(*mockConfig_, hasTestFilters()).WillByDefault(Return(true));
    
    std::map<std::string, std::string> customOptions;
    ReporterConfig config(mockConfig_, CATCH_MOVE(streamPtr), ColourMode::None, customOptions);
    ReporterBase reporter(CATCH_MOVE(config));

    std::vector<TestCaseHandle> emptyTests;
    
    EXPECT_CALL(*mockConfig_, hasTestFilters()).Times(::testing::AtLeast(1));
    EXPECT_CALL(*mockConfig_, verbosity()).Times(::testing::AtLeast(1));
    
    ASSERT_NO_THROW(reporter.listTests(emptyTests));
}

// Test: listTests with High verbosity
TEST_F(ReporterBaseTest_779, ListTestsWithHighVerbosity_779) {
    auto streamPtr = Detail::unique_ptr<IStream>(new StringIStream());
    auto* rawStream = static_cast<StringIStream*>(streamPtr.get());
    
    ON_CALL(*mockConfig_, verbosity()).WillByDefault(Return(Verbosity::High));
    
    std::map<std::string, std::string> customOptions;
    ReporterConfig config(mockConfig_, CATCH_MOVE(streamPtr), ColourMode::None, customOptions);
    ReporterBase reporter(CATCH_MOVE(config));

    std::vector<TestCaseHandle> emptyTests;
    
    ASSERT_NO_THROW(reporter.listTests(emptyTests));
}

// Test: listTests with Quiet verbosity
TEST_F(ReporterBaseTest_779, ListTestsWithQuietVerbosity_779) {
    auto streamPtr = Detail::unique_ptr<IStream>(new StringIStream());
    
    ON_CALL(*mockConfig_, verbosity()).WillByDefault(Return(Verbosity::Quiet));
    
    std::map<std::string, std::string> customOptions;
    ReporterConfig config(mockConfig_, CATCH_MOVE(streamPtr), ColourMode::None, customOptions);
    ReporterBase reporter(CATCH_MOVE(config));

    std::vector<TestCaseHandle> emptyTests;
    
    ASSERT_NO_THROW(reporter.listTests(emptyTests));
}

// Test: listReporters with empty vector doesn't crash
TEST_F(ReporterBaseTest_779, ListReportersWithEmptyVector_779) {
    auto streamPtr = Detail::unique_ptr<IStream>(new StringIStream());
    
    std::map<std::string, std::string> customOptions;
    ReporterConfig config(mockConfig_, CATCH_MOVE(streamPtr), ColourMode::None, customOptions);
    ReporterBase reporter(CATCH_MOVE(config));

    std::vector<ReporterDescription> emptyDescs;
    
    ASSERT_NO_THROW(reporter.listReporters(emptyDescs));
}

// Test: listListeners with empty vector doesn't crash
TEST_F(ReporterBaseTest_779, ListListenersWithEmptyVector_779) {
    auto streamPtr = Detail::unique_ptr<IStream>(new StringIStream());
    
    std::map<std::string, std::string> customOptions;
    ReporterConfig config(mockConfig_, CATCH_MOVE(streamPtr), ColourMode::None, customOptions);
    ReporterBase reporter(CATCH_MOVE(config));

    std::vector<ListenerDescription> emptyDescs;
    
    ASSERT_NO_THROW(reporter.listListeners(emptyDescs));
}

// Test: listTags with empty vector doesn't crash
TEST_F(ReporterBaseTest_779, ListTagsWithEmptyVector_779) {
    auto streamPtr = Detail::unique_ptr<IStream>(new StringIStream());
    
    std::map<std::string, std::string> customOptions;
    ReporterConfig config(mockConfig_, CATCH_MOVE(streamPtr), ColourMode::None, customOptions);
    ReporterBase reporter(CATCH_MOVE(config));

    std::vector<TagInfo> emptyTags;
    
    ASSERT_NO_THROW(reporter.listTags(emptyTags));
}

// Test: listTests produces output to the stream for empty list
TEST_F(ReporterBaseTest_779, ListTestsEmptyProducesOutput_779) {
    auto streamPtr = Detail::unique_ptr<IStream>(new StringIStream());
    auto* rawStream = static_cast<StringIStream*>(streamPtr.get());
    
    std::map<std::string, std::string> customOptions;
    ReporterConfig config(mockConfig_, CATCH_MOVE(streamPtr), ColourMode::None, customOptions);
    ReporterBase reporter(CATCH_MOVE(config));

    std::vector<TestCaseHandle> emptyTests;
    reporter.listTests(emptyTests);
    
    // After listing, even with empty tests, there should be some output 
    // (e.g., a count line like "0 test cases")
    std::string output = rawStream->str();
    EXPECT_FALSE(output.empty());
}

// Test: Verify config interactions during listTests
TEST_F(ReporterBaseTest_779, ListTestsQueriesConfigCorrectly_779) {
    auto streamPtr = Detail::unique_ptr<IStream>(new StringIStream());
    
    std::map<std::string, std::string> customOptions;
    ReporterConfig config(mockConfig_, CATCH_MOVE(streamPtr), ColourMode::None, customOptions);
    ReporterBase reporter(CATCH_MOVE(config));

    std::vector<TestCaseHandle> emptyTests;
    
    // Verify that listTests queries hasTestFilters and verbosity from config
    EXPECT_CALL(*mockConfig_, hasTestFilters()).Times(::testing::AtLeast(1)).WillRepeatedly(Return(false));
    EXPECT_CALL(*mockConfig_, verbosity()).Times(::testing::AtLeast(1)).WillRepeatedly(Return(Verbosity::Normal));
    
    reporter.listTests(emptyTests);
}

// Test: listTests with hasTestFilters true and normal verbosity
TEST_F(ReporterBaseTest_779, ListTestsWithFiltersAndNormalVerbosity_779) {
    auto streamPtr = Detail::unique_ptr<IStream>(new StringIStream());
    auto* rawStream = static_cast<StringIStream*>(streamPtr.get());
    
    ON_CALL(*mockConfig_, hasTestFilters()).WillByDefault(Return(true));
    ON_CALL(*mockConfig_, verbosity()).WillByDefault(Return(Verbosity::Normal));
    
    std::map<std::string, std::string> customOptions;
    ReporterConfig config(mockConfig_, CATCH_MOVE(streamPtr), ColourMode::None, customOptions);
    ReporterBase reporter(CATCH_MOVE(config));

    std::vector<TestCaseHandle> emptyTests;
    reporter.listTests(emptyTests);
    
    std::string output = rawStream->str();
    // With filters and empty tests, there should still be summary output
    EXPECT_FALSE(output.empty());
}
