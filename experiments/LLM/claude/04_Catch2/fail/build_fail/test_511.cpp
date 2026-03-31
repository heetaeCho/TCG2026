#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/internal/catch_run_context.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/catch_totals.hpp>
#include <catch2/catch_section_info.hpp>
#include <catch2/internal/catch_stringref.hpp>
#include <catch2/catch_assertion_result.hpp>
#include <catch2/internal/catch_test_case_tracker.hpp>

using namespace Catch;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

namespace {

class MockReporter : public IEventListener {
public:
    MockReporter(IConfig const* config) : IEventListener(config) {}

    MOCK_METHOD(void, fatalErrorEncountered, (StringRef error), (override));
    MOCK_METHOD(void, testRunStarting, (TestRunInfo const& testRunInfo), (override));
    MOCK_METHOD(void, testCaseStarting, (TestCaseInfo const& testInfo), (override));
    MOCK_METHOD(void, testCasePartialStarting, (TestCaseInfo const& testInfo, uint64_t partNumber), (override));
    MOCK_METHOD(void, sectionStarting, (SectionInfo const& sectionInfo), (override));
    MOCK_METHOD(void, assertionStarting, (AssertionInfo const& assertionInfo), (override));
    MOCK_METHOD(void, assertionEnded, (AssertionStats const& assertionStats), (override));
    MOCK_METHOD(void, sectionEnded, (SectionStats const& sectionStats), (override));
    MOCK_METHOD(void, testCasePartialEnded, (TestCaseStats const& testCaseStats, uint64_t partNumber), (override));
    MOCK_METHOD(void, testCaseEnded, (TestCaseStats const& testCaseStats), (override));
    MOCK_METHOD(void, testRunEnded, (TestRunStats const& testRunStats), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef benchmarkName), (override));
    MOCK_METHOD(void, benchmarkStarting, (BenchmarkInfo const& benchmarkInfo), (override));
    MOCK_METHOD(void, benchmarkEnded, (BenchmarkStats<> const& benchmarkStats), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef benchmarkName), (override));
    MOCK_METHOD(void, noMatchingTestCases, (StringRef unmatchedSpec), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef invalidArgument), (override));
    MOCK_METHOD(void, skipTest, (TestCaseInfo const& testInfo), (override));
    MOCK_METHOD(void, listReporters, (std::vector<ReporterDescription> const& descriptions), (override));
    MOCK_METHOD(void, listListeners, (std::vector<ListenerDescription> const& descriptions), (override));
    MOCK_METHOD(void, listTests, (std::vector<TestCaseHandle> const& tests), (override));
    MOCK_METHOD(void, listTags, (std::vector<TagInfo> const& tags), (override));
};

class MockConfig : public IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(TestSpec const&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

} // anonymous namespace

// Test Counts struct basic operations
class CountsTest_511 : public ::testing::Test {};

TEST_F(CountsTest_511, DefaultConstruction_511) {
    Counts c;
    EXPECT_EQ(c.passed, 0u);
    EXPECT_EQ(c.failed, 0u);
    EXPECT_EQ(c.failedButOk, 0u);
    EXPECT_EQ(c.skipped, 0u);
}

TEST_F(CountsTest_511, Total_511) {
    Counts c;
    c.passed = 3;
    c.failed = 2;
    c.failedButOk = 1;
    c.skipped = 4;
    EXPECT_EQ(c.total(), 10u);
}

TEST_F(CountsTest_511, AllPassed_WhenOnlyPassed_511) {
    Counts c;
    c.passed = 5;
    EXPECT_TRUE(c.allPassed());
}

TEST_F(CountsTest_511, AllPassed_WhenFailed_511) {
    Counts c;
    c.passed = 5;
    c.failed = 1;
    EXPECT_FALSE(c.allPassed());
}

TEST_F(CountsTest_511, AllOk_WhenFailedButOk_511) {
    Counts c;
    c.passed = 5;
    c.failedButOk = 2;
    EXPECT_TRUE(c.allOk());
}

TEST_F(CountsTest_511, AllOk_WhenFailed_511) {
    Counts c;
    c.passed = 5;
    c.failed = 1;
    EXPECT_FALSE(c.allOk());
}

TEST_F(CountsTest_511, PlusEquals_511) {
    Counts a;
    a.passed = 1;
    a.failed = 2;
    Counts b;
    b.passed = 3;
    b.failed = 4;
    a += b;
    EXPECT_EQ(a.passed, 4u);
    EXPECT_EQ(a.failed, 6u);
}

TEST_F(CountsTest_511, Subtraction_511) {
    Counts a;
    a.passed = 5;
    a.failed = 3;
    Counts b;
    b.passed = 2;
    b.failed = 1;
    Counts result = a - b;
    EXPECT_EQ(result.passed, 3u);
    EXPECT_EQ(result.failed, 2u);
}

// Test Totals struct
class TotalsTest_511 : public ::testing::Test {};

TEST_F(TotalsTest_511, DefaultConstruction_511) {
    Totals t;
    EXPECT_EQ(t.assertions.passed, 0u);
    EXPECT_EQ(t.assertions.failed, 0u);
    EXPECT_EQ(t.testCases.passed, 0u);
    EXPECT_EQ(t.testCases.failed, 0u);
}

TEST_F(TotalsTest_511, PlusEquals_511) {
    Totals a;
    a.assertions.passed = 1;
    a.testCases.failed = 2;
    Totals b;
    b.assertions.passed = 3;
    b.testCases.failed = 4;
    a += b;
    EXPECT_EQ(a.assertions.passed, 4u);
    EXPECT_EQ(a.testCases.failed, 6u);
}

TEST_F(TotalsTest_511, Subtraction_511) {
    Totals a;
    a.assertions.passed = 10;
    a.testCases.passed = 5;
    Totals b;
    b.assertions.passed = 3;
    b.testCases.passed = 2;
    Totals result = a - b;
    EXPECT_EQ(result.assertions.passed, 7u);
    EXPECT_EQ(result.testCases.passed, 3u);
}

TEST_F(TotalsTest_511, Delta_511) {
    Totals current;
    current.assertions.passed = 10;
    current.assertions.failed = 3;
    current.testCases.passed = 5;
    current.testCases.failed = 1;

    Totals prev;
    prev.assertions.passed = 7;
    prev.assertions.failed = 2;
    prev.testCases.passed = 4;
    prev.testCases.failed = 0;

    Totals d = current.delta(prev);
    EXPECT_EQ(d.assertions.passed, 3u);
    EXPECT_EQ(d.assertions.failed, 1u);
    EXPECT_EQ(d.testCases.passed, 1u);
    EXPECT_EQ(d.testCases.failed, 1u);
}

// Test StringRef
class StringRefTest_511 : public ::testing::Test {};

TEST_F(StringRefTest_511, DefaultConstruction_511) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST_F(StringRefTest_511, ConstructFromCString_511) {
    StringRef sr("hello");
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr.size(), 5u);
}

TEST_F(StringRefTest_511, ConstructFromStdString_511) {
    std::string s = "world";
    StringRef sr(s);
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_FALSE(sr.empty());
}

TEST_F(StringRefTest_511, Equality_511) {
    StringRef a("test");
    StringRef b("test");
    EXPECT_TRUE(a == b);
}

TEST_F(StringRefTest_511, Inequality_511) {
    StringRef a("test");
    StringRef b("other");
    EXPECT_TRUE(a != b);
}

TEST_F(StringRefTest_511, ExplicitConversionToString_511) {
    StringRef sr("hello");
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "hello");
}

TEST_F(StringRefTest_511, IndexOperator_511) {
    StringRef sr("abc");
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[1], 'b');
    EXPECT_EQ(sr[2], 'c');
}

TEST_F(StringRefTest_511, Substr_511) {
    StringRef sr("hello world");
    StringRef sub = sr.substr(6, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(static_cast<std::string>(sub), "world");
}

TEST_F(StringRefTest_511, Compare_511) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_LT(a.compare(b), 0);
    EXPECT_GT(b.compare(a), 0);
    EXPECT_EQ(a.compare(a), 0);
}

TEST_F(StringRefTest_511, LessThan_511) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(StringRefTest_511, EmptyStringRef_511) {
    StringRef sr("");
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST_F(StringRefTest_511, ConstructWithSizeZero_511) {
    StringRef sr("hello", 0);
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST_F(StringRefTest_511, DataPointer_511) {
    const char* raw = "test";
    StringRef sr(raw);
    EXPECT_EQ(sr.data(), raw);
}

TEST_F(StringRefTest_511, BeginEnd_511) {
    StringRef sr("ab");
    auto it = sr.begin();
    EXPECT_EQ(*it, 'a');
    ++it;
    EXPECT_EQ(*it, 'b');
    ++it;
    EXPECT_EQ(it, sr.end());
}

TEST_F(StringRefTest_511, ConcatenationOperator_511) {
    StringRef a("hello");
    StringRef b(" world");
    std::string result = a + b;
    EXPECT_EQ(result, "hello world");
}

TEST_F(StringRefTest_511, PlusEqualsOnString_511) {
    std::string s = "hello";
    StringRef sr(" world");
    s += sr;
    EXPECT_EQ(s, "hello world");
}

// Test Counts boundary conditions
TEST_F(CountsTest_511, AllPassedWithZeroCounts_511) {
    Counts c;
    // With all zeros, allPassed should be true (no failures)
    EXPECT_TRUE(c.allPassed());
}

TEST_F(CountsTest_511, AllOkWithZeroCounts_511) {
    Counts c;
    EXPECT_TRUE(c.allOk());
}

TEST_F(CountsTest_511, TotalWithAllZeros_511) {
    Counts c;
    EXPECT_EQ(c.total(), 0u);
}

TEST_F(CountsTest_511, AllPassedWithSkipped_511) {
    Counts c;
    c.passed = 5;
    c.skipped = 3;
    // skipped doesn't affect allPassed if there are no failures
    // This tests boundary behavior
    EXPECT_FALSE(c.allPassed()); // skipped counts affect allPassed
}

TEST_F(CountsTest_511, AllOkWithSkipped_511) {
    Counts c;
    c.passed = 5;
    c.skipped = 3;
    EXPECT_TRUE(c.allOk());
}

// Totals delta boundary
TEST_F(TotalsTest_511, DeltaWithSameTotals_511) {
    Totals t;
    t.assertions.passed = 5;
    t.testCases.passed = 2;
    Totals d = t.delta(t);
    EXPECT_EQ(d.assertions.passed, 0u);
    EXPECT_EQ(d.testCases.passed, 0u);
}

TEST_F(TotalsTest_511, DeltaWithZeroPrev_511) {
    Totals current;
    current.assertions.passed = 5;
    current.assertions.failed = 2;
    Totals prev;
    Totals d = current.delta(prev);
    EXPECT_EQ(d.assertions.passed, 5u);
    EXPECT_EQ(d.assertions.failed, 2u);
}
