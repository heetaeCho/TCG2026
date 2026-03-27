// handle_signal_tests_484.cpp
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

// ----------------------- Test doubles & declarations -----------------------
namespace {
    // Captured call data (observable effects)
    vector<string> g_calls;
    bool g_restored = false;
    bool g_report_called = false;
    const char* g_report_arg = nullptr;
    int g_raise_called = 0;
    int g_raise_arg = 0;

    void ResetCaptured() {
        g_calls.clear();
        g_restored = false;
        g_report_called = false;
        g_report_arg = nullptr;
        g_raise_called = 0;
        g_raise_arg = 0;
    }
}

// Forward declarations for collaborators and data used by the SUT
namespace Catch {
    struct SignalDefs { int id; const char* name; };
    extern SignalDefs signalDefs[6];

    // These are called by handleSignal; we provide test doubles.
    void restorePreviousSignalHandlers();
    void reportFatal(char const* name);
}

// Intercept raise() inside the included implementation.
// We rename raise to TEST_RAISE just for this translation unit.
int TEST_RAISE(int sig);
#define raise TEST_RAISE

// ----------------------- SUT inclusion (single TU) -------------------------
// Include the partial implementation so we can call the internal-linkage function.
#include "Catch2/src/catch2/internal/catch_fatal_condition_handler.cpp"

// Stop affecting other code
#undef raise

// ----------------------- Provide data & test doubles -----------------------
namespace Catch {
    // Provide the global table exactly as specified (observable dependency)
    SignalDefs signalDefs[6] = {
        {2,  "SIGINT - Terminal interrupt signal"},
        {4,  "SIGILL - Illegal instruction signal"},
        {8,  "SIGFPE - Floating point error signal"},
        {11, "SIGSEGV - Segmentation violation signal"},
        {15, "SIGTERM - Termination request signal"},
        {6,  "SIGABRT - Abort (abnormal termination) signal"}
    };

    void restorePreviousSignalHandlers() {
        g_restored = true;
        g_calls.push_back("restore");
    }

    void reportFatal(char const* name) {
        g_report_called = true;
        g_report_arg = name;
        g_calls.push_back("report");
    }
}

// Our intercepted raise()
int TEST_RAISE(int sig) {
    ++g_raise_called;
    g_raise_arg = sig;
    g_calls.push_back("raise");
    return 0; // Do not actually send a signal during tests.
}

// ------------------------------ Fixture ------------------------------------
class HandleSignalTest_484 : public ::testing::Test {
protected:
    void SetUp() override { ResetCaptured(); }
};

// ------------------------------ Tests --------------------------------------

// Normal path: known signal (first entry). Verifies mapping, interactions & order.
TEST_F(HandleSignalTest_484, KnownSignal_SIGINT_TriggersRestoreReportRaise_484) {
    Catch::handleSignal(2);

    EXPECT_TRUE(g_restored);
    ASSERT_TRUE(g_report_called);
    EXPECT_STREQ(g_report_arg, "SIGINT - Terminal interrupt signal");

    EXPECT_EQ(g_raise_called, 1);
    EXPECT_EQ(g_raise_arg, 2);

    // Order: restore -> report -> raise
    ASSERT_EQ(g_calls.size(), 3u);
    EXPECT_EQ(g_calls[0], "restore");
    EXPECT_EQ(g_calls[1], "report");
    EXPECT_EQ(g_calls[2], "raise");
}

// Boundary: known signal (last entry). Ensures table edge behaves as expected.
TEST_F(HandleSignalTest_484, KnownSignal_SIGABRT_TableBoundary_TriggersCorrectName_484) {
    Catch::handleSignal(6);

    EXPECT_TRUE(g_restored);
    ASSERT_TRUE(g_report_called);
    EXPECT_STREQ(g_report_arg, "SIGABRT - Abort (abnormal termination) signal");

    EXPECT_EQ(g_raise_called, 1);
    EXPECT_EQ(g_raise_arg, 6);

    ASSERT_EQ(g_calls.size(), 3u);
    EXPECT_EQ(g_calls[0], "restore");
    EXPECT_EQ(g_calls[1], "report");
    EXPECT_EQ(g_calls[2], "raise");
}

// Exceptional/edge: unknown signal resolves to "<unknown signal>" and still raises.
TEST_F(HandleSignalTest_484, UnknownSignal_ReportsUnknownAndRaisesSameSignal_484) {
    const int unknownSig = 999;
    Catch::handleSignal(unknownSig);

    EXPECT_TRUE(g_restored);
    ASSERT_TRUE(g_report_called);
    EXPECT_STREQ(g_report_arg, "<unknown signal>");

    EXPECT_EQ(g_raise_called, 1);
    EXPECT_EQ(g_raise_arg, unknownSig);

    ASSERT_EQ(g_calls.size(), 3u);
    EXPECT_EQ(g_calls[0], "restore");
    EXPECT_EQ(g_calls[1], "report");
    EXPECT_EQ(g_calls[2], "raise");
}

// Sanity: verify all known ids in the table map to their exact names via observable call.
TEST_F(HandleSignalTest_484, AllKnownSignals_MapToExactNames_484) {
    struct Expectation { int sig; const char* name; } cases[] = {
        {2,  "SIGINT - Terminal interrupt signal"},
        {4,  "SIGILL - Illegal instruction signal"},
        {8,  "SIGFPE - Floating point error signal"},
        {11, "SIGSEGV - Segmentation violation signal"},
        {15, "SIGTERM - Termination request signal"},
        {6,  "SIGABRT - Abort (abnormal termination) signal"},
    };

    for (const auto& c : cases) {
        ResetCaptured();
        Catch::handleSignal(c.sig);
        ASSERT_TRUE(g_report_called);
        EXPECT_STREQ(g_report_arg, c.name) << "Signal " << c.sig << " mapped incorrectly";
        EXPECT_EQ(g_raise_called, 1);
        EXPECT_EQ(g_raise_arg, c.sig);
    }
}
