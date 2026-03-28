// tests/restore_previous_signal_handlers_test_483.cpp
#include <gtest/gtest.h>
#include <signal.h>
#include <vector>

// ---------- Test doubles for external collaborators ----------
namespace {
struct SigactionCall {
  int signum;
  const struct sigaction* act;
  struct sigaction* oldact;
};

struct SigaltstackCall {
  const stack_t* ss;
  stack_t* old_ss;
};

static std::vector<SigactionCall> g_sigaction_calls;
static std::vector<SigaltstackCall> g_sigaltstack_calls;
static bool g_fail_sigaction = false;
static bool g_fail_sigaltstack = false;

extern "C" int test_sigaction(int signum,
                              const struct sigaction* act,
                              struct sigaction* oldact) {
  g_sigaction_calls.push_back({signum, act, oldact});
  return g_fail_sigaction ? -1 : 0;
}

extern "C" int test_sigaltstack(const stack_t* ss, stack_t* old_ss) {
  g_sigaltstack_calls.push_back({ss, old_ss});
  return g_fail_sigaltstack ? -1 : 0;
}
}  // namespace

// Redirect only the function calls inside the implementation unit.
#pragma push_macro("sigaction")
#pragma push_macro("sigaltstack")
#undef sigaction
#undef sigaltstack
#define sigaction   test_sigaction
#define sigaltstack test_sigaltstack

// Include the implementation so the internal-linkage function is visible here.
#include "Catch2/src/catch2/internal/catch_fatal_condition_handler.cpp"

#pragma pop_macro("sigaltstack")
#pragma pop_macro("sigaction")

// Test fixture
class RestorePreviousSignalHandlersTest_483 : public ::testing::Test {
protected:
  void SetUp() override {
    g_sigaction_calls.clear();
    g_sigaltstack_calls.clear();
    g_fail_sigaction = false;
    g_fail_sigaltstack = false;
  }

  // Convenience to compute how many signals are defined
  static constexpr std::size_t NumSignals() {
    return sizeof(Catch::signalDefs) / sizeof(Catch::SignalDefs);
  }
};

// --- Tests ---

TEST_F(RestorePreviousSignalHandlersTest_483, CallsSigactionForEachSignal_483) {
  ASSERT_NO_THROW(Catch::restorePreviousSignalHandlers());

  const auto expected = NumSignals();
  ASSERT_EQ(g_sigaction_calls.size(), expected)
      << "sigaction should be called once per signalDefs entry";

  for (std::size_t i = 0; i < expected; ++i) {
    EXPECT_EQ(g_sigaction_calls[i].signum, Catch::signalDefs[i].id);
    EXPECT_EQ(g_sigaction_calls[i].act, &Catch::oldSigActions[i]);
    EXPECT_EQ(g_sigaction_calls[i].oldact, nullptr);
  }
}

TEST_F(RestorePreviousSignalHandlersTest_483, CallsSigaltstackWithOldStack_483) {
  Catch::restorePreviousSignalHandlers();

  ASSERT_EQ(g_sigaltstack_calls.size(), 1u)
      << "sigaltstack should be called exactly once";
  EXPECT_EQ(g_sigaltstack_calls[0].ss, &Catch::oldSigStack);
  EXPECT_EQ(g_sigaltstack_calls[0].old_ss, nullptr);
}

TEST_F(RestorePreviousSignalHandlersTest_483, PreservesOrderAcrossSignals_483) {
  Catch::restorePreviousSignalHandlers();

  ASSERT_EQ(g_sigaction_calls.size(), NumSignals());
  // Order must match the order of entries in signalDefs
  for (std::size_t i = 0; i < NumSignals(); ++i) {
    EXPECT_EQ(g_sigaction_calls[i].signum, Catch::signalDefs[i].id);
  }
}

TEST_F(RestorePreviousSignalHandlersTest_483, NoThrowEvenIfSystemCallsFail_483) {
  // Simulate failures in underlying syscalls. The function is noexcept and
  // should still perform all calls.
  g_fail_sigaction = true;
  g_fail_sigaltstack = true;

  EXPECT_NO_THROW(Catch::restorePreviousSignalHandlers());

  EXPECT_EQ(g_sigaction_calls.size(), NumSignals());
  EXPECT_EQ(g_sigaltstack_calls.size(), 1u);
}
