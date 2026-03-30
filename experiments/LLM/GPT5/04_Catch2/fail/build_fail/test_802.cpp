// File: tests/MultiReporter_testCasePartialEnded_802.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <limits>

// Catch2 public headers (paths may vary in your tree/build setup)
#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using ::testing::_;
using ::testing::Invoke;
using ::testing::StrictMock;

namespace {

// A minimal mock that participates as a reporter/listener.
// It exposes preferences via the protected m_preferences inherited from IEventListener.
struct MockListenerish : Catch::IEventListener {
    explicit MockListenerish(const Catch::IConfig* cfg, bool redirectStdOut = false) : Catch::IEventListener(cfg) {
        m_preferences.shouldRedirectStdOut = redirectStdOut;
        // shouldReportAllAssertions left at default (false) unless needed elsewhere
    }

    // Only override what we need for these tests
    MOCK_METHOD(void, testCasePartialEnded,
                (Catch::TestCaseStats const& testStats, uint64_t partNumber),
                (override));
};

// Small helper to wrap raw pointer into Catch's unique_ptr type
static Catch::Detail::unique_ptr<Catch::IEventListener>
makePtr(Catch::IEventListener* p) {
    return Catch::Detail::unique_ptr<Catch::IEventListener>(p);
}

// Helper to build a TestCaseStats with controllable stdout/stderr.
// We treat all inputs as opaque (black box) and only set fields needed by the interface.
static Catch::TestCaseStats makeStats(const std::string& out, const std::string& err, bool aborting = false) {
    // The concrete definitions of TestCaseInfo and Totals are not relied upon;
    // we just need valid instances to satisfy the constructor.
    static Catch::TestCaseInfo dummyInfo{}; // assumes default-constructible in your build of Catch2
    static Catch::Totals dummyTotals{};
    return Catch::TestCaseStats(dummyInfo, dummyTotals, std::string(out), std::string(err), aborting);
}

} // namespace

// ---------- Tests ----------

class MultiReporterTest_802 : public ::testing::Test {
protected:
    // MultiReporter should be constructible with a (possibly null) config pointer.
    // If your tree requires a real config, replace nullptr with a proper stub.
    Catch::MultiReporter multi_{ /*IConfig*/ nullptr };
};

// Verifies the event is forwarded to all registered "reporter-likes" with the same partNumber.
// Also confirms that the exact TestCaseStats object is forwarded (observable via address).
TEST_F(MultiReporterTest_802, ForwardsToAllReporterLikes_802) {
    auto* mockA = new StrictMock<MockListenerish>(/*config*/nullptr, /*redirectStdOut*/false);
    auto* mockB = new StrictMock<MockListenerish>(/*config*/nullptr, /*redirectStdOut*/true);

    // Add one as a listener, one as a reporter — both must be notified.
    multi_.addListener(makePtr(mockA));
    multi_.addReporter(makePtr(mockB));

    const uint64_t part = 7;
    auto stats = makeStats("OUT", "ERR");

    const Catch::TestCaseStats* seenA = nullptr;
    const Catch::TestCaseStats* seenB = nullptr;

    EXPECT_CALL(*mockA, testCasePartialEnded(_, part))
        .WillOnce(Invoke([&](const Catch::TestCaseStats& s, uint64_t){ seenA = &s; }));
    EXPECT_CALL(*mockB, testCasePartialEnded(_, part))
        .WillOnce(Invoke([&](const Catch::TestCaseStats& s, uint64_t){ seenB = &s; }));

    multi_.testCasePartialEnded(stats, part);

    // Same exact object must be forwarded (observable identity)
    EXPECT_EQ(seenA, &stats);
    EXPECT_EQ(seenB, &stats);
}

// When redirection is enabled (via preferences aggregation) AND there exists a non-capturing listener,
// MultiReporter should mirror stdOut/stdErr to cout/cerr respectively.
TEST_F(MultiReporterTest_802, MirrorsStdoutAndStderrWhenRedirectEnabledAndHaveNoncapturing_802) {
    // One "reporter" that requests redirection
    multi_.addReporter(makePtr(new StrictMock<MockListenerish>(nullptr, /*redirectStdOut*/true)));
    // One "listener" (generally non-capturing)
    multi_.addListener(makePtr(new StrictMock<MockListenerish>(nullptr, /*redirectStdOut*/false)));

    // Capture std::cout / std::cerr (Catch::cout()/cerr() are expected to forward there)
    std::ostringstream capturedOut, capturedErr;
    auto* oldCout = std::cout.rdbuf(capturedOut.rdbuf());
    auto* oldCerr = std::cerr.rdbuf(capturedErr.rdbuf());

    auto stats = makeStats("hello-out", "oops-err");
    multi_.testCasePartialEnded(stats, /*part*/ 1);

    std::cout.rdbuf(oldCout);
    std::cerr.rdbuf(oldCerr);

    EXPECT_EQ(capturedOut.str(), "hello-out");
    EXPECT_EQ(capturedErr.str(), "oops-err");
}

// Even if redirection is requested by a reporter, if there are NO non-capturing listeners,
// MultiReporter should NOT mirror stdOut/stdErr.
TEST_F(MultiReporterTest_802, NoMirroringIfNoNoncapturingPresent_802) {
    // Only a redirecting reporter; no listener added.
    multi_.addReporter(makePtr(new StrictMock<MockListenerish>(nullptr, /*redirectStdOut*/true)));

    std::ostringstream capturedOut, capturedErr;
    auto* oldCout = std::cout.rdbuf(capturedOut.rdbuf());
    auto* oldCerr = std::cerr.rdbuf(capturedErr.rdbuf());

    auto stats = makeStats("out-shall-not-appear", "err-shall-not-appear");
    multi_.testCasePartialEnded(stats, /*part*/ 2);

    std::cout.rdbuf(oldCout);
    std::cerr.rdbuf(oldCerr);

    EXPECT_TRUE(capturedOut.str().empty());
    EXPECT_TRUE(capturedErr.str().empty());
}

// If redirection is NOT requested (preferences false), then nothing is mirrored,
// even if there is a non-capturing participant.
TEST_F(MultiReporterTest_802, NoMirroringIfRedirectPreferenceFalse_802) {
    // Add only a listener (non-capturing). No reporter requests redirect.
    multi_.addListener(makePtr(new StrictMock<MockListenerish>(nullptr, /*redirectStdOut*/false)));

    std::ostringstream capturedOut, capturedErr;
    auto* oldCout = std::cout.rdbuf(capturedOut.rdbuf());
    auto* oldCerr = std::cerr.rdbuf(capturedErr.rdbuf());

    auto stats = makeStats("no-out", "no-err");
    multi_.testCasePartialEnded(stats, /*part*/ 3);

    std::cout.rdbuf(oldCout);
    std::cerr.rdbuf(oldCerr);

    EXPECT_TRUE(capturedOut.str().empty());
    EXPECT_TRUE(capturedErr.str().empty());
}

// Boundary checks:
//  - Empty stdOut/stdErr should not write anything (even when redirection conditions are met).
//  - Large partNumber (uint64_t max) should be forwarded unchanged to listeners/reporters.
TEST_F(MultiReporterTest_802, HandlesEmptyStreamsAndLargePartNumber_802) {
    auto* mock = new StrictMock<MockListenerish>(nullptr, /*redirectStdOut*/true);
    multi_.addReporter(makePtr(mock));
    multi_.addListener(makePtr(new StrictMock<MockListenerish>(nullptr, /*redirectStdOut*/false)));

    const uint64_t bigPart = std::numeric_limits<uint64_t>::max();
    auto stats = makeStats("", ""); // empty outputs

    EXPECT_CALL(*mock, testCasePartialEnded(_, bigPart));

    std::ostringstream capturedOut, capturedErr;
    auto* oldCout = std::cout.rdbuf(capturedOut.rdbuf());
    auto* oldCerr = std::cerr.rdbuf(capturedErr.rdbuf());

    multi_.testCasePartialEnded(stats, bigPart);

    std::cout.rdbuf(oldCout);
    std::cerr.rdbuf(oldCerr);

    EXPECT_TRUE(capturedOut.str().empty());
    EXPECT_TRUE(capturedErr.str().empty());
}
