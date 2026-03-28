// junit_reporter_test_751.cpp
#include <gtest/gtest.h>
#include <atomic>

// The tests operate with the provided interface signatures only.
// We declare only what we must from the Catch namespace to compile
// and to observe the interaction. No private/internal state is touched.

namespace Catch {

// ---- Minimal declarations to satisfy the interface (no logic) ----

// Forward decls of types used by the ctor signature we won't call here.
struct StringRef { const char* s = nullptr; };
struct NameAndTags { /* not used here */ };
struct SourceLineInfo { /* not used here */ };

// Public interface of TestCaseInfo we need (as per prompt).
struct TestCaseInfo {
    // We do not reimplement any internal logic; in tests we provide
    // a stub definition of okToFail() below to observe calls.
    bool okToFail() const;
};

// Public reporter with the single method under test, as per Partial Code.
class JunitReporter {
public:
    // This is exactly the method under test.
    void testCaseStarting( TestCaseInfo const& testCaseInfo ) {
        // Implementation provided by the prompt; we do not modify it.
        m_okToFail = testCaseInfo.okToFail();
    }

private:
    // Private internal state; we do not read it from tests.
    bool m_okToFail = false;
};

} // namespace Catch

// ---------- Stubs / Spies for external interaction observation ----------
// We want to verify that JunitReporter::testCaseStarting actually CALLS
// TestCaseInfo::okToFail(), and that it uses the returned value.
//
// To do so, we provide a test-local stub definition for
// Catch::TestCaseInfo::okToFail() that records invocation and returns
// a controllable value. This treats TestCaseInfo as an external
// collaborator whose observable behavior (its return) we can control.

namespace {
std::atomic<int> g_okToFail_callCount{0};
std::atomic<bool> g_okToFail_return{false};
}

namespace Catch {
bool TestCaseInfo::okToFail() const {
    ++g_okToFail_callCount;
    return g_okToFail_return.load();
}
} // namespace Catch

// ------------------------- Test Fixture -------------------------

class JunitReporter_751 : public ::testing::Test {
protected:
    void SetUp() override {
        g_okToFail_callCount = 0;
        g_okToFail_return = false;
    }
};

// --------------------------- Tests -----------------------------

// Verifies that testCaseStarting queries the external collaborator
// (TestCaseInfo::okToFail) exactly once.
// Name includes TEST_ID as requested.
TEST_F(JunitReporter_751, CallsOkToFailExactlyOnce_751) {
    Catch::JunitReporter reporter;
    Catch::TestCaseInfo tc; // construction requires no internal state here

    g_okToFail_return = false; // value irrelevant for call-count test

    reporter.testCaseStarting(tc);

    // Observable behavior: external interaction happened once.
    EXPECT_EQ(g_okToFail_callCount.load(), 1) << "okToFail() should be called exactly once";
}

// Verifies behavior when okToFail returns true — we can only observe that
// the value was requested from the collaborator; we do NOT peek reporter state.
TEST_F(JunitReporter_751, UsesOkToFailTruePath_751) {
    Catch::JunitReporter reporter;
    Catch::TestCaseInfo tc;

    g_okToFail_return = true;

    reporter.testCaseStarting(tc);

    // Only observable fact we can assert without touching private state:
    // method queried the collaborator.
    EXPECT_EQ(g_okToFail_callCount.load(), 1);
}

// Verifies behavior when okToFail returns false — symmetric case.
TEST_F(JunitReporter_751, UsesOkToFailFalsePath_751) {
    Catch::JunitReporter reporter;
    Catch::TestCaseInfo tc;

    g_okToFail_return = false;

    reporter.testCaseStarting(tc);

    EXPECT_EQ(g_okToFail_callCount.load(), 1);
}

// Idempotence-like check: multiple calls should query each time,
// but we still do not assert on private state.
TEST_F(JunitReporter_751, MultipleStartsQueryEachTime_751) {
    Catch::JunitReporter reporter;
    Catch::TestCaseInfo tc;

    g_okToFail_return = true;
    reporter.testCaseStarting(tc);

    g_okToFail_return = false;
    reporter.testCaseStarting(tc);

    EXPECT_EQ(g_okToFail_callCount.load(), 2) << "okToFail() should be queried on each start";
}
