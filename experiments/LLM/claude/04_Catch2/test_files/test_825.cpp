#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "catch2/catch_totals.hpp"
#include "catch2/internal/catch_console_colour.hpp"
#include "catch2/reporters/catch_reporter_helpers.hpp"
#include "catch2/internal/catch_stream.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::HasSubstr;
using ::testing::Not;

// We need a concrete ColourImpl that does nothing with colours
// so we can capture stream output cleanly
class NoColourImpl : public ColourImpl {
public:
    NoColourImpl(IStream* stream) : ColourImpl(stream) {}
    
private:
    void use(Colour::Code) const override {}
};

// A minimal IStream wrapper for testing
class TestStream : public IStream {
public:
    TestStream(std::ostream& os) : m_os(os) {}
    std::ostream& stream() override { return m_os; }
private:
    std::ostream& m_os;
};

class PrintTestRunTotalsTest_825 : public ::testing::Test {
protected:
    std::ostringstream oss;
    TestStream* testStream;
    NoColourImpl* colourImpl;
    
    void SetUp() override {
        testStream = new TestStream(oss);
        colourImpl = new NoColourImpl(testStream);
    }
    
    void TearDown() override {
        delete colourImpl;
        delete testStream;
    }
};

// Test: When no test cases ran at all, should print "No tests ran"
TEST_F(PrintTestRunTotalsTest_825, NoTestsRan_PrintsWarning_825) {
    Totals totals;
    // All counts default to 0
    
    printTestRunTotals(oss, *colourImpl, totals);
    
    std::string output = oss.str();
    EXPECT_THAT(output, HasSubstr("No tests ran"));
}

// Test: All tests passed with some assertions
TEST_F(PrintTestRunTotalsTest_825, AllTestsPassed_PrintsSuccess_825) {
    Totals totals;
    totals.testCases.passed = 5;
    totals.assertions.passed = 10;
    
    printTestRunTotals(oss, *colourImpl, totals);
    
    std::string output = oss.str();
    EXPECT_THAT(output, HasSubstr("All tests passed"));
    EXPECT_THAT(output, HasSubstr("10 assertions"));
    EXPECT_THAT(output, HasSubstr("5 test cases"));
}

// Test: Single test case, single assertion - singular forms
TEST_F(PrintTestRunTotalsTest_825, SingleTestSingleAssertion_AllPassed_825) {
    Totals totals;
    totals.testCases.passed = 1;
    totals.assertions.passed = 1;
    
    printTestRunTotals(oss, *colourImpl, totals);
    
    std::string output = oss.str();
    EXPECT_THAT(output, HasSubstr("All tests passed"));
    EXPECT_THAT(output, HasSubstr("1 assertion"));
    EXPECT_THAT(output, HasSubstr("1 test case"));
}

// Test: Some tests failed - should print summary table, not "All tests passed"
TEST_F(PrintTestRunTotalsTest_825, SomeTestsFailed_PrintsSummary_825) {
    Totals totals;
    totals.testCases.passed = 3;
    totals.testCases.failed = 2;
    totals.assertions.passed = 8;
    totals.assertions.failed = 3;
    
    printTestRunTotals(oss, *colourImpl, totals);
    
    std::string output = oss.str();
    EXPECT_THAT(output, Not(HasSubstr("All tests passed")));
    EXPECT_THAT(output, Not(HasSubstr("No tests ran")));
    EXPECT_THAT(output, HasSubstr("test cases"));
    EXPECT_THAT(output, HasSubstr("assertions"));
    EXPECT_THAT(output, HasSubstr("passed"));
    EXPECT_THAT(output, HasSubstr("failed"));
}

// Test: All tests failed
TEST_F(PrintTestRunTotalsTest_825, AllTestsFailed_PrintsSummary_825) {
    Totals totals;
    totals.testCases.failed = 3;
    totals.assertions.failed = 5;
    
    printTestRunTotals(oss, *colourImpl, totals);
    
    std::string output = oss.str();
    EXPECT_THAT(output, Not(HasSubstr("All tests passed")));
    EXPECT_THAT(output, Not(HasSubstr("No tests ran")));
    EXPECT_THAT(output, HasSubstr("test cases"));
    EXPECT_THAT(output, HasSubstr("assertions"));
}

// Test: Tests passed but zero assertions (edge case - testCases.allPassed() true but assertions.total() == 0)
TEST_F(PrintTestRunTotalsTest_825, TestsPassedButZeroAssertions_PrintsSummary_825) {
    Totals totals;
    totals.testCases.passed = 2;
    // assertions all zero
    
    printTestRunTotals(oss, *colourImpl, totals);
    
    std::string output = oss.str();
    // assertions.total() == 0, so the "All tests passed" branch is NOT taken
    // Falls through to summary table
    EXPECT_THAT(output, Not(HasSubstr("All tests passed")));
    EXPECT_THAT(output, HasSubstr("test cases"));
}

// Test: Some tests skipped, some passed, none failed
TEST_F(PrintTestRunTotalsTest_825, SkippedTests_NotAllPassed_PrintsSummary_825) {
    Totals totals;
    totals.testCases.passed = 3;
    totals.testCases.skipped = 1;
    totals.assertions.passed = 5;
    totals.assertions.skipped = 2;
    
    printTestRunTotals(oss, *colourImpl, totals);
    
    std::string output = oss.str();
    // testCases.allPassed() checks if passed == total(), with skipped > 0, allPassed() should be false
    // So it falls to summary
    EXPECT_THAT(output, HasSubstr("test cases"));
    EXPECT_THAT(output, HasSubstr("skipped"));
}

// Test: failedButOk tests
TEST_F(PrintTestRunTotalsTest_825, FailedButOkTests_PrintsSummary_825) {
    Totals totals;
    totals.testCases.passed = 2;
    totals.testCases.failedButOk = 1;
    totals.assertions.passed = 4;
    totals.assertions.failedButOk = 2;
    
    printTestRunTotals(oss, *colourImpl, totals);
    
    std::string output = oss.str();
    EXPECT_THAT(output, HasSubstr("test cases"));
    EXPECT_THAT(output, HasSubstr("failed as expected"));
}

// Test: Large numbers
TEST_F(PrintTestRunTotalsTest_825, LargeNumbers_AllPassed_825) {
    Totals totals;
    totals.testCases.passed = 10000;
    totals.assertions.passed = 100000;
    
    printTestRunTotals(oss, *colourImpl, totals);
    
    std::string output = oss.str();
    EXPECT_THAT(output, HasSubstr("All tests passed"));
    EXPECT_THAT(output, HasSubstr("100000 assertions"));
    EXPECT_THAT(output, HasSubstr("10000 test cases"));
}

// Test: Mixed results with all types of counts
TEST_F(PrintTestRunTotalsTest_825, MixedResults_AllCountTypes_825) {
    Totals totals;
    totals.testCases.passed = 5;
    totals.testCases.failed = 2;
    totals.testCases.failedButOk = 1;
    totals.testCases.skipped = 1;
    totals.assertions.passed = 20;
    totals.assertions.failed = 5;
    totals.assertions.failedButOk = 3;
    totals.assertions.skipped = 2;
    
    printTestRunTotals(oss, *colourImpl, totals);
    
    std::string output = oss.str();
    EXPECT_THAT(output, Not(HasSubstr("All tests passed")));
    EXPECT_THAT(output, Not(HasSubstr("No tests ran")));
    EXPECT_THAT(output, HasSubstr("test cases"));
    EXPECT_THAT(output, HasSubstr("assertions"));
}

// Test: Only failed tests, no passed
TEST_F(PrintTestRunTotalsTest_825, OnlyFailedTests_825) {
    Totals totals;
    totals.testCases.failed = 1;
    totals.assertions.failed = 1;
    
    printTestRunTotals(oss, *colourImpl, totals);
    
    std::string output = oss.str();
    EXPECT_THAT(output, Not(HasSubstr("All tests passed")));
    EXPECT_THAT(output, Not(HasSubstr("No tests ran")));
    EXPECT_THAT(output, HasSubstr("test cases"));
    EXPECT_THAT(output, HasSubstr("assertions"));
}

// Test: Output contains newline at the end for "No tests ran"
TEST_F(PrintTestRunTotalsTest_825, NoTestsRan_EndsWithNewline_825) {
    Totals totals;
    
    printTestRunTotals(oss, *colourImpl, totals);
    
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.back(), '\n');
}

// Test: Output contains newline at the end for "All tests passed"
TEST_F(PrintTestRunTotalsTest_825, AllPassed_EndsWithNewline_825) {
    Totals totals;
    totals.testCases.passed = 1;
    totals.assertions.passed = 1;
    
    printTestRunTotals(oss, *colourImpl, totals);
    
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.back(), '\n');
}
