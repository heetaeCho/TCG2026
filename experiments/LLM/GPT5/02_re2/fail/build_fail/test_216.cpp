// File: walker_walk_test_216.cc

#include <gtest/gtest.h>
#include <vector>
#include "re2/regexp.h"
#include "re2/walker-inl.h"

using re2::Regexp;

namespace {

// A concrete Walker that records how its hooks are invoked and
// returns simple, easy-to-check values without assuming any internal logic.
struct RecordingWalker : public Regexp::Walker<int> {
  // Counters to observe external interactions.
  int pre_calls = 0;
  int post_calls = 0;
  int short_calls = 0;
  int copy_calls = 0;

  // Behavior: make return values a simple deterministic function of inputs,
  // so we can assert on the final Walk(...) result without relying on internals.
  int PreVisit(Regexp* /*re*/, int parent_arg, bool* stop) override {
    ++pre_calls;
    if (stop) *stop = false;   // Never stop from here (observable behavior only).
    return parent_arg + 10;    // Deterministic transformation for testing.
  }

  int PostVisit(Regexp* /*re*/,
                int /*parent_arg*/,
                int pre_arg,
                int* /*child_args*/,
                int /*nchild_args*/) override {
    ++post_calls;
    return pre_arg + 100;      // Deterministic transformation for testing.
  }

  int ShortVisit(Regexp* /*re*/, int parent_arg) override {
    ++short_calls;
    return parent_arg + 1000;  // If ever used, clearly different value.
  }

  int Copy(int arg) override {
    ++copy_calls;
    return arg;                // Identity copy; we only observe that it happened.
  }
};

// Helper to build a simple leaf (literal) regexp.
static Regexp* MakeLiteral(char c) {
  using PF = Regexp::ParseFlags;
  return Regexp::NewLiteral(static_cast<Rune>(static_cast<unsigned char>(c)),
                            static_cast<PF>(0));
}

// Helper to build a concat of two regexps (takes ownership of subs on success).
static Regexp* MakeConcat(Regexp* a, Regexp* b) {
  using PF = Regexp::ParseFlags;
  Regexp* subs[2] = {a, b};
  return Regexp::Concat(subs, 2, static_cast<PF>(0));
}

// Helper to build a linear concat chain of N literals: "aaaa...a" (N times).
static Regexp* MakeConcatChain(int n) {
  ASSERT_GT(n, 0);
  Regexp* root = MakeLiteral('a');
  for (int i = 1; i < n; ++i) {
    Regexp* next = MakeLiteral('a');
    Regexp* cat = MakeConcat(root, next);
    // The Concat takes ownership on success; if it fails (unlikely), decref to avoid leaks.
    if (cat == nullptr) {
      if (root) root->Decref();
      if (next) next->Decref();
      return nullptr;
    }
    root = cat;
  }
  return root;
}

}  // namespace

// 1) Normal operation with a single leaf.
//    Verifies that Walk returns a value consistent with PreVisit/PostVisit’s public behavior,
//    and that it doesn’t report early stop for a tiny tree.
TEST(WalkerWalkTest_216, Walk_SingleLiteral_ReturnsPostVisitResult_216) {
  std::unique_ptr<Regexp, void(*)(Regexp*)> re(MakeLiteral('x'),
                                               [](Regexp* r){ if (r) r->Decref(); });
  ASSERT_NE(re.get(), nullptr);

  RecordingWalker w;
  const int top_arg = 5;

  // Expected purely from hook behavior (not from internals):
  // pre = top_arg + 10; result = pre + 100 = top_arg + 110
  const int expected = top_arg + 110;

  const int got = w.Walk(re.get(), top_arg);

  EXPECT_EQ(got, expected);
  EXPECT_GE(w.pre_calls, 1);      // At least one visit for the leaf.
  EXPECT_GE(w.post_calls, 1);     // PostVisit should run for the leaf.
  EXPECT_FALSE(w.stopped_early());  // Small tree should not trip early-stop.
}

// 2) Interaction observation on a composite (Concat) tree.
//    We DO NOT assume how many times Copy is called internally, only that using Walk(...)
//    (which sets use_copy=true in its own implementation) plausibly triggers some copying.
//    We assert a minimal, non-brittle condition: Copy() was called at least once when
//    walking a non-leaf structure. This avoids asserting hidden internals.
TEST(WalkerWalkTest_216, Walk_Composite_MayUseCopy_216) {
  std::unique_ptr<Regexp, void(*)(Regexp*)> re(MakeConcat(MakeLiteral('a'), MakeLiteral('b')),
                                               [](Regexp* r){ if (r) r->Decref(); });
  ASSERT_NE(re.get(), nullptr);

  RecordingWalker w;
  (void)w.Walk(re.get(), /*top_arg=*/0);

  // We only check *some* observable copying happened on a non-leaf input.
  // (Not asserting exact counts to avoid coupling to hidden traversal details.)
  EXPECT_GE(w.copy_calls, 1);
  EXPECT_FALSE(w.stopped_early());
  // Basic sanity: we visited and posted at least once.
  EXPECT_GE(w.pre_calls, 1);
  EXPECT_GE(w.post_calls, 1);
}

// 3) Boundary-ish scenario: a longer chain should still not trigger early stop,
//    since Walk() sets a very large maximum internally (implementation detail),
//    but we only check the *observable* effect that the walk didn't stop early.
TEST(WalkerWalkTest_216, Walk_LongChain_DoesNotStopEarly_216) {
  // Build a moderately sized chain. We keep this reasonable so the test stays fast.
  std::unique_ptr<Regexp, void(*)(Regexp*)> re(MakeConcatChain(100),
                                               [](Regexp* r){ if (r) r->Decref(); });
  ASSERT_NE(re.get(), nullptr);

  RecordingWalker w;
  (void)w.Walk(re.get(), /*top_arg=*/123);

  EXPECT_FALSE(w.stopped_early());   // Observable boundary behavior.
  EXPECT_GE(w.pre_calls, 1);
  EXPECT_GE(w.post_calls, 1);
}

// 4) Reset() should leave the walker in a reusable, non-stopped state.
//    We don’t depend on any prior internal state—just check public flags stay sane.
TEST(WalkerWalkTest_216, Reset_MakesWalkerReusable_216) {
  std::unique_ptr<Regexp, void(*)(Regexp*)> re(MakeConcat(MakeLiteral('a'), MakeLiteral('b')),
                                               [](Regexp* r){ if (r) r->Decref(); });
  ASSERT_NE(re.get(), nullptr);

  RecordingWalker w;

  // First run
  (void)w.Walk(re.get(), /*top_arg=*/7);
  EXPECT_FALSE(w.stopped_early());

  // Reset and run again; should still behave normally.
  w.Reset();
  const int result2 = w.Walk(re.get(), /*top_arg=*/1);
  // From our hook math: (1 + 10) + 100 = 111 for each node aggregation;
  // But we **do not** assert a specific aggregate, since internal aggregation is unknown.
  // We only check that it produced some int and didn’t set early stop.
  (void)result2;
  EXPECT_FALSE(w.stopped_early());
}

