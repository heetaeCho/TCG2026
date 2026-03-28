// File: tests/junit_reporter_testRunEndedCumulative_754.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <string>

// Catch2 reporter under test
#include "catch2/reporters/catch_reporter_junit.hpp"
// Common reporter config bits (constructor + TestRunInfo)
#include "catch2/reporters/catch_reporter_common.hpp"

using ::testing::HasSubstr;

namespace {

class JunitReporterTest_754 : public ::testing::Test {
protected:
    std::ostringstream m_out;
    std::unique_ptr<Catch::JunitReporter> m_reporter;

    void SetUp() override {
        // Construct reporter with the capture stream
        Catch::ReporterConfig cfg{ m_out };
        m_reporter = std::make_unique<Catch::JunitReporter>(std::move(cfg));

        // Begin a run to ensure internal run node exists and writer is primed
        Catch::TestRunInfo tri{ "dummy-run-754" };
        m_reporter->testRunStarting(tri);
    }

    void TearDown() override {
        m_reporter.reset();
    }
};

} // namespace

// [Normal operation]
// Verifies that calling testRunEndedCumulative closes an XML element by
// checking that a closing tag `</...>` appears (or appears later) after the call.
TEST_F(JunitReporterTest_754, ClosesRootElement_754) {
    const std::string before = m_out.str();
    const auto beforeClose = before.rfind("</");

    // Act
    ASSERT_NO_THROW(m_reporter->testRunEndedCumulative());

    const std::string after = m_out.str();
    const auto afterClose = after.rfind("</");

    // An XML closing tag should be present after the call,
    // and (if already present) it should be at the same or a later position.
    ASSERT_NE(afterClose, std::string::npos);
    if (beforeClose != std::string::npos) {
        EXPECT_GE(afterClose, beforeClose);
    }

    // Output should grow or at least change after writing the run + closing the element
    EXPECT_GE(after.size(), before.size());
}

// [Boundary condition]
// Minimal run with no test cases or assertions: ensure it still emits a closing tag
// and does not throw.
TEST_F(JunitReporterTest_754, NoTestCases_StillProducesClosingTag_754) {
    // No test cases/sections/assertions added; immediately end the run.
    ASSERT_NO_THROW(m_reporter->testRunEndedCumulative());

    const std::string xml = m_out.str();
    // Look for a generic XML closing tag — we do not assert the exact tag name,
    // only that an element was closed as an observable side-effect.
    EXPECT_NE(xml.rfind("</"), std::string::npos);
}

// [External interaction evidence]
// While we cannot mock Timer or private XmlWriter, we can still observe that
// testRunEndedCumulative wrote the run summary (which typically includes a time attribute)
// and then closed an element. We look for a generic time attribute to avoid depending
// on exact formatting or values.
TEST_F(JunitReporterTest_754, OutputContainsTimeAttribute_754) {
    m_reporter->testRunEndedCumulative();

    const std::string xml = m_out.str();
    // Evidence that suite time was retrieved and serialized.
    // We do not assert the numeric value (depends on timer), only presence.
    EXPECT_THAT(xml, HasSubstr("time=\""));
}

// [Idempotence/robustness guard]
// Ending the run twice should not crash the process. We do not assert exact output,
// only that a second call does not throw. If the underlying implementation forbids
// this, this test documents the observable behavior (exception/abort would fail it).
TEST_F(JunitReporterTest_754, DoubleEndRun_DoesNotThrow_754) {
    m_reporter->testRunEndedCumulative();
    // A second call should not crash the test binary; if it throws, this will document it.
    EXPECT_NO_THROW(m_reporter->testRunEndedCumulative());
}
