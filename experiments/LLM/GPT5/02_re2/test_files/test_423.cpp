// File: child_args_changed_test_423.cc
#include <gtest/gtest.h>

#include "re2/regexp.h"
// Include the TU so we can call the internal-linkage helper under test.
#include "re2/simplify.cc"

using namespace re2;

namespace {

static Regexp::ParseFlags kNoFlags = static_cast<Regexp::ParseFlags>(0);

TEST(ChildArgsChangedTest_423, ReturnsFalseAndDecrefsOnNoChange_423) {
  // Build a parent with two children.
  Regexp* a = Regexp::NewLiteral('a', kNoFlags);
  Regexp* b = Regexp::NewLiteral('b', kNoFlags);
  Regexp* subs[2] = {a, b};
  Regexp* parent = Regexp::Concat(subs, 2, kNoFlags);

  ASSERT_NE(parent, nullptr);
  ASSERT_EQ(parent->nsub(), 2);

  Regexp* s0 = parent->sub()[0];
  Regexp* s1 = parent->sub()[1];

  // Record baseline refs.
  int r0_before = s0->Ref();
  int r1_before = s1->Ref();

  // Prepare child_args as Incref’ed copies of existing subs.
  Regexp* child_args[2] = { s0->Incref(), s1->Incref() };

  // No change expected → false, and the function Decref’s child_args[i].
  bool changed = ChildArgsChanged(parent, child_args);
  EXPECT_FALSE(changed);

  // Refcounts should be back to baseline (Decref happened inside the function).
  EXPECT_EQ(s0->Ref(), r0_before);
  EXPECT_EQ(s1->Ref(), r1_before);

  // Cleanup: destroy parent (children are owned via refs).
  parent->Decref();
}

TEST(ChildArgsChangedTest_423, ReturnsTrueAndDoesNotDecrefWhenChangeAtIndex1_423) {
  // Build a parent with two children.
  Regexp* a = Regexp::NewLiteral('x', kNoFlags);
  Regexp* b = Regexp::NewLiteral('y', kNoFlags);
  Regexp* subs[2] = {a, b};
  Regexp* parent = Regexp::Concat(subs, 2, kNoFlags);

  ASSERT_NE(parent, nullptr);
  ASSERT_EQ(parent->nsub(), 2);

  Regexp* s0 = parent->sub()[0];
  Regexp* s1 = parent->sub()[1];

  int r0_before = s0->Ref();
  int r1_before = s1->Ref();

  // Make child_args: index 0 same (Incref'd), index 1 replaced with a different node.
  Regexp* different = Regexp::NewLiteral('z', kNoFlags);
  Regexp* child_args[2] = { s0->Incref(), different /* not equal to s1 */ };

  bool changed = ChildArgsChanged(parent, child_args);
  EXPECT_TRUE(changed);

  // Because it returned early, it must NOT have decref'ed child_args[0] or [1].
  EXPECT_EQ(s0->Ref(), r0_before + 1); // still holds our extra ref
  EXPECT_EQ(s1->Ref(), r1_before);     // we never touched s1

  // Cleanup: caller must Decref the child_args it created since function didn't.
  child_args[0]->Decref();
  different->Decref();
  parent->Decref();
}

TEST(ChildArgsChangedTest_423, ReturnsTrueAndDoesNotDecrefWhenChangeAtIndex0_423) {
  // Build a parent with two children.
  Regexp* a = Regexp::NewLiteral('m', kNoFlags);
  Regexp* b = Regexp::NewLiteral('n', kNoFlags);
  Regexp* subs[2] = {a, b};
  Regexp* parent = Regexp::Concat(subs, 2, kNoFlags);

  ASSERT_NE(parent, nullptr);
  ASSERT_EQ(parent->nsub(), 2);

  Regexp* s0 = parent->sub()[0];
  Regexp* s1 = parent->sub()[1];

  int r0_before = s0->Ref();
  int r1_before = s1->Ref();

  // child_args: index 0 different, index 1 same (Incref'd).
  Regexp* different0 = Regexp::NewLiteral('q', kNoFlags);
  Regexp* child_args[2] = { different0, s1->Incref() };

  bool changed = ChildArgsChanged(parent, child_args);
  EXPECT_TRUE(changed);

  // Since it returned at index 0, it must NOT have decref'ed child_args[1] either.
  EXPECT_EQ(s0->Ref(), r0_before);       // untouched
  EXPECT_EQ(s1->Ref(), r1_before + 1);   // our extra ref still held

  // Cleanup.
  different0->Decref();
  child_args[1]->Decref();
  parent->Decref();
}

TEST(ChildArgsChangedTest_423, HandlesZeroSubs_423) {
  // Leaf node has zero children.
  Regexp* leaf = Regexp::NewLiteral('k', kNoFlags);
  ASSERT_NE(leaf, nullptr);
  ASSERT_EQ(leaf->nsub(), 0);

  // Passing nullptr for child_args is fine; loops are zero-length.
  bool changed = ChildArgsChanged(leaf, /*child_args=*/nullptr);
  EXPECT_FALSE(changed);

  leaf->Decref();
}

}  // namespace
