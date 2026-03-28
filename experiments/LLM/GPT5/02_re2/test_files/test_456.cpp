// File: prog_buildentiredfa_test_456.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "re2/prog.h"  // Declares re2::Prog, MatchKind, DFAStateCallback

using ::testing::_;
using ::testing::Return;
using ::testing::SaveArg;
using ::testing::StrictMock;

namespace re2 {

// ---------- Test seam (external collaborator injection) ----------
//
// We interpose Prog::GetDFA so that BuildEntireDFA(kind, cb)
// calls into our mock DFA instead of the real one.
//
// We also capture the 'kind' argument to verify correct forwarding.

class MockDFA {
public:
  // We only need the single method that BuildEntireDFA calls.
  MOCK_METHOD(int, BuildAllStates, (const Prog::DFAStateCallback&), ());
};

// Global pointer used by our interposed GetDFA to return the mock.
static MockDFA* g_mock_dfa_for_tests_456 = nullptr;

// Capture of last requested MatchKind for verification.
static Prog::MatchKind g_last_kind_requested_456 = static_cast<Prog::MatchKind>(0);

// Provide a *definition* for the private member function.
// Even though it's private, defining it here is allowed; the test is linked
// with this symbol so BuildEntireDFA will use our seam.
DFA* Prog::GetDFA(Prog::MatchKind kind) {
  // Record the kind we were asked for.
  g_last_kind_requested_456 = kind;

  // We don't need a real 're2::DFA' here; BuildEntireDFA will immediately call
  // BuildAllStates(cb) on whatever pointer we return.
  // To keep a strict black-box boundary, we avoid redefining the production DFA
  // type in tests. Instead, we cast our mock object to a byte-compatible stub.
  //
  // Create a tiny shim type that only exists to satisfy the return type.
  struct DFAShim {};
  static_assert(sizeof(DFAShim*) == sizeof(MockDFA*), "pointer sizes must match");

  return reinterpret_cast<DFA*>(reinterpret_cast<DFAShim*>(g_mock_dfa_for_tests_456));
}

}  // namespace re2

namespace {

// A small helper callback we can pass through the API.
// We don't rely on any internal DFA behavior; we only need an object
// of the correct type to verify that it is forwarded intact.
struct CountingCallback {
  int* counter;
  // Adapt to DFAStateCallback via implicit conversion if it is a std::function-like type.
  void operator()(/* state or whatever the real signature expects */) const {
    if (counter) (*counter)++;
  }
};

class BuildEntireDFATest_456 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure no stray pointers.
    re2::g_mock_dfa_for_tests_456 = nullptr;
    // Reset the captured kind to a sentinel.
    re2::g_last_kind_requested_456 = static_cast<re2::Prog::MatchKind>(-1);
  }

  void TearDown() override {
    re2::g_mock_dfa_for_tests_456 = nullptr;
  }
};

TEST_F(BuildEntireDFATest_456, ForwardsToDFAAndReturnsValue_456) {
  re2::Prog prog;

  StrictMock<re2::MockDFA> mock_dfa;
  re2::g_mock_dfa_for_tests_456 = &mock_dfa;

  // Prepare a callback object; we only verify it is the same object
  // passed through to BuildAllStates (no assumptions on DFA's internal use).
  int cb_seen_count = 0;
  CountingCallback cb_impl{&cb_seen_count};

  // We'll capture the exact callback reference passed to BuildAllStates,
  // then invoke it once here to increment 'cb_seen_count' so we can prove
  // the same instance traveled across the boundary.
  re2::Prog::DFAStateCallback captured_cb;

  EXPECT_CALL(mock_dfa, BuildAllStates(_))
      .WillOnce(DoAll(SaveArg<0>(&captured_cb), Return(123)));

  // Call the method under test.
  int result = prog.BuildEntireDFA(static_cast<re2::Prog::MatchKind>(0),
                                   reinterpret_cast<const re2::Prog::DFAStateCallback&>(cb_impl));

  // Verify return value is propagated from DFA::BuildAllStates.
  EXPECT_EQ(result, 123);

  // Sanity: we received a callback and can invoke it (no assumption on DFA logic).
  // This proves the same callback object was forwarded.
  if (captured_cb) {
    // Invoke the forwarded callback once; increment happens on our side.
    captured_cb(/* whatever args the real type ignores or defaults */);
    EXPECT_EQ(cb_seen_count, 1);
  }
}

TEST_F(BuildEntireDFATest_456, PassesThroughMatchKind_456) {
  re2::Prog prog;
  StrictMock<re2::MockDFA> mock_dfa;
  re2::g_mock_dfa_for_tests_456 = &mock_dfa;

  EXPECT_CALL(mock_dfa, BuildAllStates(_)).WillOnce(Return(0));

  // Try two distinct kinds (treated as opaque enums/ints).
  auto kind_a = static_cast<re2::Prog::MatchKind>(0);
  auto kind_b = static_cast<re2::Prog::MatchKind>(1);

  // First call with kind_a
  (void)prog.BuildEntireDFA(kind_a, re2::Prog::DFAStateCallback{});
  EXPECT_EQ(re2::g_last_kind_requested_456, kind_a);

  // Second call with kind_b
  EXPECT_CALL(mock_dfa, BuildAllStates(_)).WillOnce(Return(0));
  (void)prog.BuildEntireDFA(kind_b, re2::Prog::DFAStateCallback{});
  EXPECT_EQ(re2::g_last_kind_requested_456, kind_b);
}

TEST_F(BuildEntireDFATest_456, PropagatesZeroAndNegativeReturnValues_456) {
  re2::Prog prog;
  StrictMock<re2::MockDFA> mock_dfa;
  re2::g_mock_dfa_for_tests_456 = &mock_dfa;

  // Return zero
  EXPECT_CALL(mock_dfa, BuildAllStates(_)).WillOnce(Return(0));
  EXPECT_EQ(prog.BuildEntireDFA(static_cast<re2::Prog::MatchKind>(0),
                                re2::Prog::DFAStateCallback{}),
            0);

  // Return a negative value (e.g., error code) – should be propagated as-is.
  EXPECT_CALL(mock_dfa, BuildAllStates(_)).WillOnce(Return(-7));
  EXPECT_EQ(prog.BuildEntireDFA(static_cast<re2::Prog::MatchKind>(0),
                                re2::Prog::DFAStateCallback{}),
            -7);
}

TEST_F(BuildEntireDFATest_456, CallsBuildAllStatesExactlyOncePerInvocation_456) {
  re2::Prog prog;
  StrictMock<re2::MockDFA> mock_dfa;
  re2::g_mock_dfa_for_tests_456 = &mock_dfa;

  // Each call to BuildEntireDFA should result in exactly one call to BuildAllStates.
  EXPECT_CALL(mock_dfa, BuildAllStates(_)).WillOnce(Return(1));
  (void)prog.BuildEntireDFA(static_cast<re2::Prog::MatchKind>(0),
                            re2::Prog::DFAStateCallback{});

  EXPECT_CALL(mock_dfa, BuildAllStates(_)).WillOnce(Return(2));
  (void)prog.BuildEntireDFA(static_cast<re2::Prog::MatchKind>(0),
                            re2::Prog::DFAStateCallback{});
}

}  // namespace
