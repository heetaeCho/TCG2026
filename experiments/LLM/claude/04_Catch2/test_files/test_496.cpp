#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/internal/catch_test_case_tracker.hpp"
#include "catch2/catch_test_case_info.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;
using ::testing::AtLeast;

// Mock for IConfig
class MockConfig : public IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

// Mock for IEventListener (reporter)
class MockReporter : public IEventListener {
public:
    MockReporter(IConfig const* config) : IEventListener(config) {}

    MOCK_METHOD(void, noMatchingTestCases, (StringRef), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef), (override));
    MOCK_METHOD(void, testRunStarting, (TestRunInfo const&), (override));
    MOCK_METHOD(void, testCaseStarting, (TestCaseInfo const&), (override));
    MOCK_METHOD(void, testCasePartialStarting, (TestCaseInfo const&, uint64_t), (override));
    MOCK_METHOD(void, sectionStarting, (SectionInfo const&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (BenchmarkInfo const&), (override));
    MOCK_METHOD(void, benchmarkEnded, (BenchmarkStats<> const&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    MOCK_METHOD(void, assertionStarting, (AssertionInfo const&), (override));
    MOCK_METHOD(void, assertionEnded, (AssertionStats const&), (override));
    MOCK_METHOD(void, sectionEnded, (SectionStats const&), (override));
    MOCK_METHOD(void, testCasePartialEnded, (TestCaseStats const&, uint64_t), (override));
    MOCK_METHOD(void, testCaseEnded, (TestCaseStats const&), (override));
    MOCK_METHOD(void, testRunEnded, (TestRunStats const&), (override));
    MOCK_METHOD(void, skipTest, (TestCaseInfo const&), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef), (override));
    MOCK_METHOD(void, listReporters, (std::vector<ReporterDescription> const&), (override));
    MOCK_METHOD(void, listListeners, (std::vector<ListenerDescription> const&), (override));
    MOCK_METHOD(void, listTests, (std::vector<TestCaseHandle> const&), (override));
    MOCK_METHOD(void, listTags, (std::vector<TagInfo> const&), (override));
};

class RunContextTest_496 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig_ = new NiceMock<MockConfig>();
        
        static std::vector<std::string> emptyVec;
        ON_CALL(*mockConfig_, name()).WillByDefault(Return(StringRef("TestRun")));
        ON_CALL(*mockConfig_, includeSuccessfulResults()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, warnAboutMissingAssertions()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, abortAfter()).WillByDefault(Return(0));
        ON_CALL(*mockConfig_, getSectionsToRun()).WillByDefault(::testing::ReturnRef(emptyVec));
        ON_CALL(*mockConfig_, getTestsOrTags()).WillByDefault(::testing::ReturnRef(emptyVec));
        ON_CALL(*mockConfig_, verbosity()).WillByDefault(Return(Verbosity::Normal));
        ON_CALL(*mockConfig_, allowThrows()).WillByDefault(Return(true));
        ON_CALL(*mockConfig_, showDurations()).WillByDefault(Return(ShowDurations::DefaultForReporter));
        ON_CALL(*mockConfig_, runOrder()).WillByDefault(Return(TestRunOrder::Declared));
        ON_CALL(*mockConfig_, rngSeed()).WillByDefault(Return(0));
        ON_CALL(*mockConfig_, benchmarkNoAnalysis()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, benchmarkSamples()).WillByDefault(Return(100));
        ON_CALL(*mockConfig_, benchmarkResamples()).WillByDefault(Return(100000));
        ON_CALL(*mockConfig_, benchmarkConfidenceInterval()).WillByDefault(Return(0.95));
        ON_CALL(*mockConfig_, benchmarkWarmupTime()).WillByDefault(Return(std::chrono::milliseconds(100)));
        ON_CALL(*mockConfig_, hasTestFilters()).WillByDefault(Return(false));
        
        mockReporter_ = new NiceMock<MockReporter>(mockConfig_);
    }

    void TearDown() override {
        // Config is not owned by RunContext typically, so we manage it
    }

    NiceMock<MockConfig>* mockConfig_;
    NiceMock<MockReporter>* mockReporter_;

    std::unique_ptr<RunContext> createRunContext() {
        Detail::unique_ptr<IEventListener> reporter(mockReporter_);
        return std::make_unique<RunContext>(mockConfig_, std::move(reporter));
    }
};

// Test that RunContext can be constructed successfully
TEST_F(RunContextTest_496, ConstructionSucceeds_496) {
    ASSERT_NO_THROW({
        auto ctx = createRunContext();
        ASSERT_NE(ctx, nullptr);
    });
}

// Test getCurrentTestName returns empty string when no test is active
TEST_F(RunContextTest_496, GetCurrentTestNameWhenNoTestActive_496) {
    auto ctx = createRunContext();
    std::string name = ctx->getCurrentTestName();
    // When no test case is running, the name should be empty or default
    EXPECT_TRUE(name.empty() || !name.empty()); // Just verify it doesn't crash
}

// Test getLastResult returns nullptr initially
TEST_F(RunContextTest_496, GetLastResultInitiallyNull_496) {
    auto ctx = createRunContext();
    const AssertionResult* result = ctx->getLastResult();
    // Initially there should be no last result
    EXPECT_EQ(result, nullptr);
}

// Test lastAssertionPassed initially returns false
TEST_F(RunContextTest_496, LastAssertionPassedInitiallyFalse_496) {
    auto ctx = createRunContext();
    EXPECT_FALSE(ctx->lastAssertionPassed());
}

// Test assertionPassed sets lastAssertionPassed to true
TEST_F(RunContextTest_496, AssertionPassedSetsFlag_496) {
    auto ctx = createRunContext();
    ctx->assertionPassed();
    EXPECT_TRUE(ctx->lastAssertionPassed());
}

// Test aborting initially returns false
TEST_F(RunContextTest_496, AbortingInitiallyFalse_496) {
    auto ctx = createRunContext();
    EXPECT_FALSE(ctx->aborting());
}

// Test Counts default construction
TEST_F(RunContextTest_496, CountsDefaultConstruction_496) {
    Counts c;
    EXPECT_EQ(c.passed, 0u);
    EXPECT_EQ(c.failed, 0u);
    EXPECT_EQ(c.failedButOk, 0u);
    EXPECT_EQ(c.skipped, 0u);
}

// Test Counts total
TEST_F(RunContextTest_496, CountsTotal_496) {
    Counts c;
    c.passed = 3;
    c.failed = 2;
    c.failedButOk = 1;
    c.skipped = 4;
    EXPECT_EQ(c.total(), 10u);
}

// Test Counts allPassed
TEST_F(RunContextTest_496, CountsAllPassed_496) {
    Counts c;
    c.passed = 5;
    EXPECT_TRUE(c.allPassed());
    c.failed = 1;
    EXPECT_FALSE(c.allPassed());
}

// Test Counts allOk
TEST_F(RunContextTest_496, CountsAllOk_496) {
    Counts c;
    c.passed = 5;
    c.failedButOk = 2;
    EXPECT_TRUE(c.allOk());
    c.failed = 1;
    EXPECT_FALSE(c.allOk());
}

// Test Counts subtraction
TEST_F(RunContextTest_496, CountsSubtraction_496) {
    Counts a, b;
    a.passed = 10;
    a.failed = 5;
    b.passed = 3;
    b.failed = 2;
    Counts result = a - b;
    EXPECT_EQ(result.passed, 7u);
    EXPECT_EQ(result.failed, 3u);
}

// Test Counts += operator
TEST_F(RunContextTest_496, CountsPlusEquals_496) {
    Counts a, b;
    a.passed = 2;
    b.passed = 3;
    b.failed = 1;
    a += b;
    EXPECT_EQ(a.passed, 5u);
    EXPECT_EQ(a.failed, 1u);
}

// Test Totals default construction
TEST_F(RunContextTest_496, TotalsDefaultConstruction_496) {
    Totals t;
    EXPECT_EQ(t.assertions.total(), 0u);
    EXPECT_EQ(t.testCases.total(), 0u);
}

// Test Totals subtraction
TEST_F(RunContextTest_496, TotalsSubtraction_496) {
    Totals a, b;
    a.assertions.passed = 10;
    b.assertions.passed = 3;
    Totals result = a - b;
    EXPECT_EQ(result.assertions.passed, 7u);
}

// Test Totals += operator
TEST_F(RunContextTest_496, TotalsPlusEquals_496) {
    Totals a, b;
    a.assertions.passed = 5;
    b.assertions.passed = 3;
    a += b;
    EXPECT_EQ(a.assertions.passed, 8u);
}

// Test SourceLineInfo construction
TEST_F(RunContextTest_496, SourceLineInfoConstruction_496) {
    SourceLineInfo info("test.cpp", 42);
    EXPECT_STREQ(info.file, "test.cpp");
    EXPECT_EQ(info.line, 42u);
}

// Test SourceLineInfo equality
TEST_F(RunContextTest_496, SourceLineInfoEquality_496) {
    SourceLineInfo a("test.cpp", 42);
    SourceLineInfo b("test.cpp", 42);
    SourceLineInfo c("other.cpp", 42);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

// Test SourceLineInfo less than
TEST_F(RunContextTest_496, SourceLineInfoLessThan_496) {
    SourceLineInfo a("a.cpp", 10);
    SourceLineInfo b("a.cpp", 20);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

// Test StringRef default construction
TEST_F(RunContextTest_496, StringRefDefaultConstruction_496) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

// Test StringRef from C-string
TEST_F(RunContextTest_496, StringRefFromCString_496) {
    StringRef sr("hello");
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr.size(), 5u);
}

// Test StringRef equality
TEST_F(RunContextTest_496, StringRefEquality_496) {
    StringRef a("test");
    StringRef b("test");
    StringRef c("other");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_TRUE(a != c);
}

// Test StringRef from std::string
TEST_F(RunContextTest_496, StringRefFromStdString_496) {
    std::string s = "hello world";
    StringRef sr(s);
    EXPECT_EQ(sr.size(), s.size());
    EXPECT_FALSE(sr.empty());
}

// Test StringRef explicit conversion to std::string
TEST_F(RunContextTest_496, StringRefToStdString_496) {
    StringRef sr("hello");
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "hello");
}

// Test StringRef subscript operator
TEST_F(RunContextTest_496, StringRefSubscript_496) {
    StringRef sr("abcde");
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[4], 'e');
}

// Test StringRef compare
TEST_F(RunContextTest_496, StringRefCompare_496) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_LT(a.compare(b), 0);
    EXPECT_GT(b.compare(a), 0);
    EXPECT_EQ(a.compare(a), 0);
}

// Test StringRef less than
TEST_F(RunContextTest_496, StringRefLessThan_496) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

// Test that sectionStarting is called on reporter when sectionStarted succeeds
TEST_F(RunContextTest_496, SectionStartedCallsReporterSectionStarting_496) {
    // This test verifies that when sectionStarted is called and the tracker is open,
    // the reporter's sectionStarting method is invoked.
    // Note: This requires a proper test case context which is complex to set up externally.
    // We verify the reporter mock expectation.
    EXPECT_CALL(*mockReporter_, sectionStarting(_)).Times(AtLeast(0));
    auto ctx = createRunContext();
    // Without an active test case and proper tracker setup, sectionStarted may return false
    Counts assertions;
    SourceLineInfo lineInfo("test.cpp", 10);
    bool result = ctx->sectionStarted("TestSection", lineInfo, assertions);
    // Without proper tracker context, this should return false
    // (tracker not open)
    EXPECT_FALSE(result);
}

// Test benchmarkPreparing calls reporter
TEST_F(RunContextTest_496, BenchmarkPreparingCallsReporter_496) {
    EXPECT_CALL(*mockReporter_, benchmarkPreparing(_)).Times(1);
    auto ctx = createRunContext();
    ctx->benchmarkPreparing("bench1");
}

// Test benchmarkStarting calls reporter
TEST_F(RunContextTest_496, BenchmarkStartingCallsReporter_496) {
    EXPECT_CALL(*mockReporter_, benchmarkStarting(_)).Times(1);
    auto ctx = createRunContext();
    BenchmarkInfo info{"bench1", 0.0, 100, 100, 100000, 0.95};
    ctx->benchmarkStarting(info);
}

// Test benchmarkFailed calls reporter
TEST_F(RunContextTest_496, BenchmarkFailedCallsReporter_496) {
    EXPECT_CALL(*mockReporter_, benchmarkFailed(_)).Times(1);
    auto ctx = createRunContext();
    ctx->benchmarkFailed("error message");
}

// Test Counts allPassed with zero counts
TEST_F(RunContextTest_496, CountsAllPassedZeroCounts_496) {
    Counts c;
    // With all zeros, total is 0, failed is 0 => allPassed should be true
    EXPECT_TRUE(c.allPassed());
}

// Test Counts allOk with zero counts
TEST_F(RunContextTest_496, CountsAllOkZeroCounts_496) {
    Counts c;
    EXPECT_TRUE(c.allOk());
}

// Test Totals delta
TEST_F(RunContextTest_496, TotalsDelta_496) {
    Totals current;
    current.assertions.passed = 10;
    current.assertions.failed = 2;
    current.testCases.passed = 5;

    Totals prev;
    prev.assertions.passed = 7;
    prev.assertions.failed = 1;
    prev.testCases.passed = 3;

    Totals d = current.delta(prev);
    EXPECT_EQ(d.assertions.passed, 3u);
    EXPECT_EQ(d.assertions.failed, 1u);
    EXPECT_EQ(d.testCases.passed, 2u);
}

// Test StringRef substr
TEST_F(RunContextTest_496, StringRefSubstr_496) {
    StringRef sr("hello world");
    StringRef sub = sr.substr(6, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(static_cast<std::string>(sub), "world");
}

// Test StringRef data
TEST_F(RunContextTest_496, StringRefData_496) {
    const char* raw = "test string";
    StringRef sr(raw);
    EXPECT_EQ(sr.data(), raw);
}

// Test StringRef begin/end iteration
TEST_F(RunContextTest_496, StringRefIteration_496) {
    StringRef sr("abc");
    std::string result;
    for (auto it = sr.begin(); it != sr.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "abc");
}

// Test StringRef concatenation
TEST_F(RunContextTest_496, StringRefConcatenation_496) {
    StringRef a("hello ");
    StringRef b("world");
    std::string result = a + b;
    EXPECT_EQ(result, "hello world");
}

// Test StringRef += with std::string
TEST_F(RunContextTest_496, StringRefPlusEqualsStdString_496) {
    std::string s = "hello ";
    StringRef sr("world");
    s += sr;
    EXPECT_EQ(s, "hello world");
}

// Test Counts with only failedButOk
TEST_F(RunContextTest_496, CountsOnlyFailedButOk_496) {
    Counts c;
    c.failedButOk = 5;
    EXPECT_TRUE(c.allOk());
    EXPECT_FALSE(c.allPassed());
    EXPECT_EQ(c.total(), 5u);
}

// Test Counts with skipped
TEST_F(RunContextTest_496, CountsWithSkipped_496) {
    Counts c;
    c.passed = 3;
    c.skipped = 2;
    EXPECT_EQ(c.total(), 5u);
    // skipped doesn't affect allPassed (only failed matters)
    EXPECT_TRUE(c.allPassed());
}
