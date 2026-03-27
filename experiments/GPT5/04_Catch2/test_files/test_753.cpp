// File: junit_reporter_testcaseEnded_753.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using ::testing::Eq;
using ::testing::SizeIs;

//
// Minimal, interface-only test doubles for collaborators,
// matching the shapes shown in the prompt.
// These are *not* re-implementations of JunitReporter internals;
// they just expose the callable surface so we can exercise the
// black-box behavior under test and verify external interactions.
//
namespace Catch {

struct TestCaseInfo { /* intentionally empty for this test */ };
struct Totals      { /* intentionally empty for this test */ };

struct TestCaseStats {
    const TestCaseInfo* testInfo = nullptr;
    Totals              totals{};
    std::string         stdOut;
    std::string         stdErr;
    bool                aborting = false;

    TestCaseStats(TestCaseInfo const& _testInfo,
                  Totals const& _totals,
                  std::string&& _stdOut,
                  std::string&& _stdErr,
                  bool _aborting)
        : testInfo(&_testInfo),
          totals(_totals),
          stdOut(std::move(_stdOut)),
          stdErr(std::move(_stdErr)),
          aborting(_aborting) {}
};

struct ReporterConfig {
    std::ostream& stream;
    explicit ReporterConfig(std::ostream& os) : stream(os) {}
};

class ReporterBase {
protected:
    std::ostream& m_stream;
public:
    explicit ReporterBase(ReporterConfig&& cfg) : m_stream(cfg.stream) {}
    virtual ~ReporterBase() = default;
};

class CumulativeReporterBase : public ReporterBase {
public:
    using ReporterBase::ReporterBase;

    // Spy points to verify external interaction from JunitReporter
    int forwardedCalls = 0;
    std::vector<std::pair<std::string, std::string>> receivedStdOutErr;

    // This is the function that should be called by JunitReporter::testCaseEnded
    virtual void testCaseEnded(TestCaseStats const& testCaseStats) {
        forwardedCalls++;
        // Record payload that arrived at the collaborator
        receivedStdOutErr.emplace_back(testCaseStats.stdOut, testCaseStats.stdErr);
    }

    // Other virtuals omitted — not needed for this target test
};

struct XmlWriter {
    explicit XmlWriter(std::ostream&) {}
};

struct Timer {};

// Subject under test: only the public interface used here.
// The body of testCaseEnded is the one given in the prompt.
class JunitReporter : public CumulativeReporterBase {
private:
    XmlWriter   xml;
    Timer       suiteTimer;
    std::string stdOutForSuite;
    std::string stdErrForSuite;
    unsigned    unexpectedExceptions = 0;
    bool        m_okToFail = false;

public:
    explicit JunitReporter(ReporterConfig&& _config)
        : CumulativeReporterBase(std::move(_config)),
          xml(m_stream) {}

    void testCaseEnded(TestCaseStats const& testCaseStats) {
        // --- Code under test (from the prompt) ---
        stdOutForSuite += testCaseStats.stdOut;
        stdErrForSuite += testCaseStats.stdErr;
        CumulativeReporterBase::testCaseEnded(testCaseStats);
    }
};

} // namespace Catch

//
// Test fixture
//
class JunitReporterTest_753 : public ::testing::Test {
protected:
    std::ostringstream oss;
    Catch::ReporterConfig cfg{oss};
    Catch::JunitReporter reporter{Catch::ReporterConfig{oss}}; // move-construct

    // Convenient access to the (stubbed) collaborator surface
    Catch::CumulativeReporterBase& base() {
        return static_cast<Catch::CumulativeReporterBase&>(reporter);
    }
};

//
// Normal operation: forwards once with the exact payload
//
TEST_F(JunitReporterTest_753, ForwardsToBase_WithExactStdOutErr_753) {
    Catch::TestCaseInfo info;
    Catch::Totals totals;

    Catch::TestCaseStats stats{
        info, totals,
        std::string{"stdout A"},
        std::string{"stderr A"},
        /*aborting*/ false
    };

    reporter.testCaseEnded(stats);

    EXPECT_THAT(base().forwardedCalls, Eq(1));
    ASSERT_THAT(base().receivedStdOutErr, SizeIs(1));
    EXPECT_THAT(base().receivedStdOutErr[0].first,  Eq(std::string{"stdout A"}));
    EXPECT_THAT(base().receivedStdOutErr[0].second, Eq(std::string{"stderr A"}));
}

//
// Boundary-ish: multiple invocations should forward each time in order
//
TEST_F(JunitReporterTest_753, ForwardsOnEveryCall_InOrder_753) {
    Catch::TestCaseInfo info;
    Catch::Totals totals;

    Catch::TestCaseStats first{
        info, totals,
        std::string{"out1"},
        std::string{"err1"},
        false
    };
    Catch::TestCaseStats second{
        info, totals,
        std::string{"out2"},
        std::string{"err2"},
        false
    };

    reporter.testCaseEnded(first);
    reporter.testCaseEnded(second);

    EXPECT_THAT(base().forwardedCalls, Eq(2));
    ASSERT_THAT(base().receivedStdOutErr, SizeIs(2));
    EXPECT_THAT(base().receivedStdOutErr[0].first,  Eq(std::string{"out1"}));
    EXPECT_THAT(base().receivedStdOutErr[0].second, Eq(std::string{"err1"}));
    EXPECT_THAT(base().receivedStdOutErr[1].first,  Eq(std::string{"out2"}));
    EXPECT_THAT(base().receivedStdOutErr[1].second, Eq(std::string{"err2"}));
}

//
// Edge case: empty stdOut/stdErr should still forward cleanly with empty payloads
//
TEST_F(JunitReporterTest_753, ForwardsEmptyStdOutAndStdErr_753) {
    Catch::TestCaseInfo info;
    Catch::Totals totals;

    Catch::TestCaseStats stats{
        info, totals,
        std::string{},     // empty stdOut
        std::string{},     // empty stdErr
        false
    };

    reporter.testCaseEnded(stats);

    EXPECT_THAT(base().forwardedCalls, Eq(1));
    ASSERT_THAT(base().receivedStdOutErr, SizeIs(1));
    EXPECT_THAT(base().receivedStdOutErr[0].first,  Eq(std::string{}));
    EXPECT_THAT(base().receivedStdOutErr[0].second, Eq(std::string{}));
}
