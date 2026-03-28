// File: simplify_shortvisit_test.cc

#include "re2/regexp.h"
#include "re2/simplify.h"   // If SimplifyWalker is declared here; otherwise include the header that declares it.
#include <gtest/gtest.h>

namespace re2 {

// Minimal helper to create a simple Regexp instance via public API.
static Regexp* MakeLiteral(Rune r) {
  // Flags are an implementation-defined bitmask; using 0 is acceptable as “no flags”
  return Regexp::NewLiteral(r, static_cast<Regexp::ParseFlags>(0));
}

class SimplifyWalkerTest_428 : public ::testing::Test {};

// [Normal] ShortVisit returns the same pointer and increments refcount by 1.
TEST_F(SimplifyWalkerTest_428, ShortVisit_IncrementsRefAndReturnsSamePtr_428) {
  SimplifyWalker walker;
  Regexp* re = MakeLiteral('a');
  ASSERT_NE(re, nullptr);

  const int before = re->Ref();

  Regexp* ret = walker.ShortVisit(re, /*parent_arg=*/nullptr);

  // Observable effects:
  // 1) Returned pointer is the same object.
  EXPECT_EQ(ret, re);
  // 2) Refcount increased by exactly 1.
  EXPECT_EQ(re->Ref(), before + 1);

  // Cleanup: Decref once for ShortVisit's Incref, and once for the original.
  ret->Decref();
  re->Decref();
}

// [Boundary] Passing a non-null parent_arg should not change the result or the parent’s refcount.
TEST_F(SimplifyWalkerTest_428, ShortVisit_IgnoresParentArg_NoParentRefcountChange_428) {
  SimplifyWalker walker;
  Regexp* child = MakeLiteral('b');
  Regexp* parent = MakeLiteral('P');
  ASSERT_NE(child, nullptr);
  ASSERT_NE(parent, nullptr);

  const int child_before = child->Ref();
  const int parent_before = parent->Ref();

  Regexp* ret = walker.ShortVisit(child, /*parent_arg=*/parent);

  // Child behavior
  EXPECT_EQ(ret, child);
  EXPECT_EQ(child->Ref(), child_before + 1);

  // Parent must be untouched (no observable refcount change).
  EXPECT_EQ(parent->Ref(), parent_before);

  // Cleanup
  ret->Decref();     // for ShortVisit's Incref
  child->Decref();   // original
  parent->Decref();  // original
}

// [Stress/Boundary] Multiple ShortVisit calls accumulate reference count linearly.
TEST_F(SimplifyWalkerTest_428, ShortVisit_MultipleCalls_AccumulatesRefcount_428) {
  SimplifyWalker walker;
  Regexp* re = MakeLiteral('x');
  ASSERT_NE(re, nullptr);

  const int base = re->Ref();

  Regexp* r1 = walker.ShortVisit(re, nullptr);
  Regexp* r2 = walker.ShortVisit(re, nullptr);
  Regexp* r3 = walker.ShortVisit(re, nullptr);

  // All returns should be the same pointer.
  EXPECT_EQ(r1, re);
  EXPECT_EQ(r2, re);
  EXPECT_EQ(r3, re);

  // Refcount increased by 3 total.
  EXPECT_EQ(re->Ref(), base + 3);

  // Cleanup: three for the ShortVisit increfs, one for the original.
  r1->Decref();
  r2->Decref();
  r3->Decref();
  re->Decref();
}

}  // namespace re2
