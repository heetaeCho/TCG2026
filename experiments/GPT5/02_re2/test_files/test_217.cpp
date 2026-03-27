// File: walker_walkexponential_test_217.cc

#include <gtest/gtest.h>
#include "re2/regexp.h"
#include "re2/walker-inl.h"

using re2::Regexp;

// Minimal derived walker to observe externally visible behavior only.
template <typename T>
class ObserverWalker217 : public Regexp::Walker<T> {
public:
  // Exposed observation fields (allowed: they're outside CUT)
  bool pre_called = false;
  bool post_called = false;
  bool short_called = false;

  // Records the *parent_arg* value passed into either PreVisit or ShortVisit.
  T last_parent_arg = T();

  // Control whether PreVisit will request an early stop.
  bool force_stop_in_pre = false;

  // All hooks return the same value so tests don't rely on internal traversal order.
  T unified_result;

  explicit ObserverWalker217(T result) : unified_result(result) {}

  T PreVisit(Regexp* /*re*/, T parent_arg, bool* stop) override {
    pre_called = true;
    last_parent_arg = parent_arg;
    if (force_stop_in_pre && stop) *stop = true;
    return unified_result;
  }

  T PostVisit(Regexp* /*re*/, T /*parent_arg*/, T /*pre_arg*/,
              T* /*child_args*/, int /*nchild_args*/) override {
    post_called = true;
    return unified_result;
  }

  T ShortVisit(Regexp* /*re*/, T parent_arg) override {
    short_called = true;
    last_parent_arg = parent_arg;
    return unified_result;
  }

  T Copy(T arg) override {  // Not used by WalkExponential per interface snippet
    // Keep deterministic in case it is ever invoked.
    return arg;
  }
};

class WalkerWalkExponentialTest_217 : public ::testing::Test {
protected:
  using PF = Regexp::ParseFlags;

  // Utility to build a single literal regexp.
  Regexp* Literal(char c) {
    return Regexp::NewLiteral(static_cast<Rune>(c), static_cast<PF>(0));
  }

  // Utility to build a concat of two literals.
  Regexp* Concat2(char a, char b) {
    Regexp* subs[2] = { Literal(a), Literal(b) };
    Regexp* cat = Regexp::Concat(subs, 2, static_cast<PF>(0));
    // The factory usually transfers references; to be safe, decref inputs.
    if (subs[0]) subs[0]->Decref();
    if (subs[1]) subs[1]->Decref();
    return cat;
  }
};

// 1) Normal operation: returns the traversal’s computed result and propagates top_arg.
TEST_F(WalkerWalkExponentialTest_217, ReturnsUnifiedResultAndPassesTopArg_217) {
  // Arrange: leaf regexp (literal) and a walker that always returns 42.
  Regexp* leaf = Literal('x');
  ASSERT_NE(leaf, nullptr);
  ObserverWalker217<int> w(42);

  // Act
  int top_arg = 7;
  int out = w.WalkExponential(leaf, top_arg, /*max_visits=*/100);

  // Assert: result is what the walker produced, not e.g. default-initialized.
  EXPECT_EQ(out, 42);
  // Either PreVisit or ShortVisit must have observed the same parent_arg we passed.
  EXPECT_EQ(w.last_parent_arg, top_arg);
  // For a tiny leaf, traversal should not have stopped early.
  EXPECT_FALSE(w.stopped_early());

  leaf->Decref();
}

// 2) Boundary/early-stop via PreVisit: setting *stop=true* should mark stopped_early().
TEST_F(WalkerWalkExponentialTest_217, EarlyStopSetsStoppedEarlyFlag_217) {
  // Arrange: a non-leaf so PreVisit of the parent node is guaranteed to run.
  Regexp* re = Concat2('a', 'b');
  ASSERT_NE(re, nullptr);
  ObserverWalker217<int> w(101);
  w.force_stop_in_pre = true;

  // Act
  int out = w.WalkExponential(re, /*top_arg=*/123, /*max_visits=*/1000);

  // Assert
  EXPECT_EQ(out, 101);            // Walker’s unified result is returned
  EXPECT_TRUE(w.pre_called);      // PreVisit executed and requested stop
  EXPECT_FALSE(w.post_called);    // PostVisit should not be needed after a stop
  EXPECT_TRUE(w.stopped_early()); // Observable via the public API

  re->Decref();
}

// 3) Reset() should clear observable traversal state such as stopped_early().
TEST_F(WalkerWalkExponentialTest_217, ResetClearsStoppedEarly_217) {
  // Arrange: trigger an early stop once
  Regexp* re = Concat2('c', 'd');
  ASSERT_NE(re, nullptr);
  ObserverWalker217<int> w(1);
  w.force_stop_in_pre = true;
  (void)w.WalkExponential(re, /*top_arg=*/0, /*max_visits=*/1);
  ASSERT_TRUE(w.stopped_early()); // precondition

  // Act
  w.Reset();

  // Assert
  EXPECT_FALSE(w.stopped_early());

  re->Decref();
}

// 4) Edge handling for max_visits parameter: calling with 0 should still be safe.
//    (We don't assert internal counters — only that the call succeeds and returns
//     the walker’s value, and that the stopped_early() flag is a valid observable.)
TEST_F(WalkerWalkExponentialTest_217, MaxVisitsZeroIsHandled_217) {
  Regexp* leaf = Literal('z');
  ASSERT_NE(leaf, nullptr);
  ObserverWalker217<int> w(777);

  int out = w.WalkExponential(leaf, /*top_arg=*/5, /*max_visits=*/0);

  EXPECT_EQ(out, 777);
  // Depending on internal policy, it may or may not stop early.
  // We only assert the flag is a valid boolean and the call did not crash.
  (void)w.stopped_early(); // Access for coverage without constraining behavior.

  leaf->Decref();
}
