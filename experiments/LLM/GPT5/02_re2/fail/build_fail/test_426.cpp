// File: coalesce_walker_postvisit_test_426.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "re2/regexp.h"

namespace re2 {
// Minimal declaration to access the public method under test,
// without re-implementing internal details or private helpers.
class CoalesceWalker {
public:
  Regexp* PostVisit(Regexp* re,
                    Regexp* parent_arg,
                    Regexp* pre_arg,
                    Regexp** child_args,
                    int nchild_args);
};
}  // namespace re2

using re2::Regexp;
using ::testing::NotNull;
using ::testing::Eq;
using ::testing::Ne;

class CoalesceWalkerPostVisitTest_426 : public ::testing::Test {
protected:
  using PF = Regexp::ParseFlags;
  static PF F() { return static_cast<PF>(0); }

  // Helper: build a leaf node (no children) via a public factory.
  static Regexp* Leaf(int id = 1) { return Regexp::HaveMatch(id, F()); }
};

// 1) Leaf input (nsub()==0) must return Incref of the same node.
TEST_F(CoalesceWalkerPostVisitTest_426, LeafReturnsIncref_426) {
  re2::CoalesceWalker w;

  Regexp* leaf = Leaf(123);                 // nsub()==0 leaf
  const int before = leaf->Ref();           // observable refcount
  Regexp* out = w.PostVisit(leaf, nullptr, nullptr, nullptr, 0);

  ASSERT_THAT(out, NotNull());
  EXPECT_THAT(out, Eq(leaf)) << "PostVisit on leaf should Incref and return same pointer";
  EXPECT_EQ(leaf->Ref(), before + 1);

  // Cleanup: decref the returned Incref once.
  out->Decref();
  // And the original.
  leaf->Decref();
}

// 2) Non-concat with UNCHANGED children -> Incref (no clone).
TEST_F(CoalesceWalkerPostVisitTest_426, NonConcat_UnchangedChildren_ReturnsIncref_426) {
  re2::CoalesceWalker w;

  // Build a PLUS node with one child.
  Regexp* child = Leaf(1);
  Regexp* plus  = Regexp::Plus(child, F());

  // Prepare child_args pointing to the *same* child pointer (unchanged).
  Regexp* children[1] = { plus->sub()[0] };

  const int before = plus->Ref();
  Regexp* out = w.PostVisit(plus, nullptr, nullptr, children, 1);

  ASSERT_THAT(out, NotNull());
  EXPECT_THAT(out, Eq(plus)) << "Unchanged children should Incref original node";
  EXPECT_EQ(plus->Ref(), before + 1);

  out->Decref();
  plus->Decref();  // releases the structure (which releases child)
}

// 3) Non-concat with CHANGED child (kRegexpRepeat) -> clone preserving min/max.
TEST_F(CoalesceWalkerPostVisitTest_426, NonConcat_ChangedChildren_Repeat_PreservesMinMax_426) {
  re2::CoalesceWalker w;

  // Repeat(min=2, max=5) over some leaf.
  Regexp* base   = Leaf(2);
  Regexp* repeat = Regexp::Repeat(base, F(), /*min=*/2, /*max=*/5);

  // Replace the only child with a different leaf.
  Regexp* new_child = Leaf(3);
  Regexp* children[1] = { new_child };

  Regexp* out = w.PostVisit(repeat, nullptr, nullptr, children, 1);

  ASSERT_THAT(out, NotNull());
  EXPECT_EQ(out->op(), kRegexpRepeat);
  // Observable: min/max must be preserved on the new node.
  EXPECT_EQ(out->min(), 2);
  EXPECT_EQ(out->max(), 5);
  // And the new child must be adopted.
  ASSERT_EQ(out->nsub(), 1);
  EXPECT_EQ(out->sub()[0], new_child);

  // Cleanup
  out->Decref();        // releases new_child as adopted
  repeat->Decref();     // releases original structure (and its original child)
}

// 4) Non-concat with CHANGED child (kRegexpCapture) -> clone preserving cap.
TEST_F(CoalesceWalkerPostVisitTest_426, NonConcat_ChangedChildren_Capture_PreservesCap_426) {
  re2::CoalesceWalker w;

  Regexp* base     = Leaf(10);
  Regexp* capture  = Regexp::Capture(base, F(), /*cap=*/7);

  // Swap its child to a different one.
  Regexp* new_child = Leaf(11);
  Regexp* children[1] = { new_child };

  Regexp* out = w.PostVisit(capture, nullptr, nullptr, children, 1);

  ASSERT_THAT(out, NotNull());
  EXPECT_EQ(out->op(), kRegexpCapture);
  EXPECT_EQ(out->cap(), 7);        // observable: cap preserved
  ASSERT_EQ(out->nsub(), 1);
  EXPECT_EQ(out->sub()[0], new_child);

  // Cleanup
  out->Decref();       // releases new_child as adopted
  capture->Decref();   // releases original structure (and its original child)
}

// 5) Concat with NO coalescing & UNCHANGED children -> Incref.
TEST_F(CoalesceWalkerPostVisitTest_426, Concat_NoCoalesce_UnchangedChildren_ReturnsIncref_426) {
  re2::CoalesceWalker w;

  // Use two captures to avoid coalescing of sibling nodes.
  Regexp* a = Regexp::Capture(Leaf(21), F(), 1);
  Regexp* b = Regexp::Capture(Leaf(22), F(), 2);

  Regexp* subs[2] = { a, b };
  Regexp* concat = Regexp::Concat(subs, 2, F());

  // Child args unchanged: same pointers.
  Regexp* children[2] = { concat->sub()[0], concat->sub()[1] };

  const int before = concat->Ref();
  Regexp* out = w.PostVisit(concat, nullptr, nullptr, children, 2);

  ASSERT_THAT(out, NotNull());
  EXPECT_THAT(out, Eq(concat));     // unchanged -> Incref
  EXPECT_EQ(concat->Ref(), before + 1);

  out->Decref();
  concat->Decref();  // releases structure and its children
}

// 6) Concat with NO coalescing & CHANGED children -> new concat adopting children.
TEST_F(CoalesceWalkerPostVisitTest_426, Concat_NoCoalesce_ChangedChildren_ReturnsNewConcat_426) {
  re2::CoalesceWalker w;

  Regexp* a = Regexp::Capture(Leaf(31), F(), 1);
  Regexp* b = Regexp::Capture(Leaf(32), F(), 2);

  Regexp* subs[2] = { a, b };
  Regexp* concat = Regexp::Concat(subs, 2, F());

  // Replace second child with a different capture to ensure "changed".
  Regexp* new_b = Regexp::Capture(Leaf(33), F(), 3);
  Regexp* children[2] = { concat->sub()[0], new_b };

  Regexp* out = w.PostVisit(concat, nullptr, nullptr, children, 2);

  ASSERT_THAT(out, NotNull());
  EXPECT_NE(out, concat);
  EXPECT_EQ(out->op(), kRegexpConcat);
  ASSERT_EQ(out->nsub(), 2);
  EXPECT_EQ(out->sub()[0], children[0]);
  EXPECT_EQ(out->sub()[1], children[1]);  // adopted new_b

  // Cleanup
  out->Decref();       // releases children[0] (original a) and new_b
  concat->Decref();    // releases original (and its original b)
}
