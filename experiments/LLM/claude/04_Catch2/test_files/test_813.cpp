#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <memory>

#include "catch2/reporters/catch_reporter_compact.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/catch_session.hpp"
#include "catch2/reporters/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_stream.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"

using namespace Catch;

namespace {

// Helper to create a stream wrapper around an ostringstream
class StringStream : public IStream {
public:
    StringStream() {}
    std::ostream& stream() override { return m_oss; }
    std::string str() const { return m_oss.str(); }
private:
    std::ostringstream m_oss;
};

// Helper to create a minimal config for reporter construction
class TestConfig : public IConfig {
public:
    bool allowThrows() const override { return true; }
    StringRef name() const override { return "test"; }
    int abortAfter() const override { return -1; }
    bool showInvisibles() const override { return false; }
    ShowDurations showDurations() const override { return ShowDurations::DefaultForReporter; }
    double minDuration() const override { return -1; }
    TestRunOrder runOrder() const override { return TestRunOrder::Declared; }
    unsigned int rngSeed() const override { return 0; }
    ColourMode defaultColourMode() const override { return ColourMode::None; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    std::vector<std::string> const& getSectionsToRun() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    std::vector<std::string> const& getTestsOrTags() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    Verbosity verbosity() const override { return Verbosity::Normal; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds benchmarkWarmupTime() const override {
        return std::chrono::milliseconds(100);
    }
    bool hasTestFilters() const override { return false; }
};

} // anonymous namespace

class CompactReporterTest_813 : public ::testing::Test {
protected:
    void SetUp() override {
        m_stringStream = new StringStream();
        m_config = std::make_shared<TestConfig>();

        Detail::unique_ptr<IStream> streamPtr(m_stringStream);
        ReporterConfig reporterConfig(
            m_config.get(),
            CATCH_MOVE(streamPtr),
            ColourMode::None,
            {}
        );
        m_reporter = Detail::make_unique<CompactReporter>(CATCH_MOVE(reporterConfig));
    }

    StringStream* m_stringStream = nullptr; // owned by reporter
    std::shared_ptr<TestConfig> m_config;
    Detail::unique_ptr<CompactReporter> m_reporter;

    std::string getOutput() const {
        return m_stringStream->str();
    }
};

TEST_F(CompactReporterTest_813, GetDescription_ReturnsNonEmptyString_813) {
    std::string desc = CompactReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

TEST_F(CompactReporterTest_813, NoMatchingTestCases_OutputsUnmatchedSpec_813) {
    m_reporter->noMatchingTestCases("SomeTestSpec");
    std::string output = getOutput();
    EXPECT_NE(output.find("SomeTestSpec"), std::string::npos);
}

TEST_F(CompactReporterTest_813, NoMatchingTestCases_ContainsNoMatchMessage_813) {
    m_reporter->noMatchingTestCases("FooBarSpec");
    std::string output = getOutput();
    EXPECT_NE(output.find("No test cases matched"), std::string::npos);
    EXPECT_NE(output.find("FooBarSpec"), std::string::npos);
}

TEST_F(CompactReporterTest_813, NoMatchingTestCases_EmptySpec_813) {
    m_reporter->noMatchingTestCases("");
    std::string output = getOutput();
    EXPECT_NE(output.find("No test cases matched"), std::string::npos);
}

TEST_F(CompactReporterTest_813, NoMatchingTestCases_SpecialCharacters_813) {
    m_reporter->noMatchingTestCases("[tag1][tag2]*");
    std::string output = getOutput();
    EXPECT_NE(output.find("[tag1][tag2]*"), std::string::npos);
}

TEST_F(CompactReporterTest_813, NoMatchingTestCases_MultipleCallsAppend_813) {
    m_reporter->noMatchingTestCases("Spec1");
    m_reporter->noMatchingTestCases("Spec2");
    std::string output = getOutput();
    EXPECT_NE(output.find("Spec1"), std::string::npos);
    EXPECT_NE(output.find("Spec2"), std::string::npos);
}

TEST_F(CompactReporterTest_813, NoMatchingTestCases_LongSpec_813) {
    std::string longSpec(500, 'x');
    m_reporter->noMatchingTestCases(StringRef(longSpec));
    std::string output = getOutput();
    EXPECT_NE(output.find(longSpec), std::string::npos);
}

TEST_F(CompactReporterTest_813, NoMatchingTestCases_OutputEndsWithNewline_813) {
    m_reporter->noMatchingTestCases("TestSpec");
    std::string output = getOutput();
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.back(), '\n');
}

TEST_F(CompactReporterTest_813, NoMatchingTestCases_SpecWithSpaces_813) {
    m_reporter->noMatchingTestCases("test with spaces");
    std::string output = getOutput();
    EXPECT_NE(output.find("test with spaces"), std::string::npos);
}

TEST_F(CompactReporterTest_813, NoMatchingTestCases_QuotedSpec_813) {
    m_reporter->noMatchingTestCases("MySpec");
    std::string output = getOutput();
    // The spec should appear quoted in the output
    EXPECT_NE(output.find("'MySpec'"), std::string::npos);
}

TEST_F(CompactReporterTest_813, Destructor_DoesNotCrash_813) {
    // Verify that destroying the reporter does not cause issues
    m_reporter.reset();
    SUCCEED();
}

TEST_F(CompactReporterTest_813, TestRunStarting_DoesNotCrash_813) {
    TestRunInfo runInfo("TestGroup");
    m_reporter->testRunStarting(runInfo);
    SUCCEED();
}

TEST_F(CompactReporterTest_813, GetDescription_ContainsReporterInfo_813) {
    std::string desc = CompactReporter::getDescription();
    // Description should be meaningful; just verify it has some content
    EXPECT_GT(desc.size(), 5u);
}
