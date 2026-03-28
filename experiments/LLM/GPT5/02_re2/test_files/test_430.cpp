// File: simplify_postvisit_test_430.cc

#include <gtest/gtest.h>

// Use the public RE2 interfaces.
#include "re2/regexp.h"

// We include the .cc for SimplifyWalker so the tests can instantiate it directly.
// (This project layout exposes SimplifyWalker in simplify.cc.)
#include "re2/simplify.cc"

namespace re2 {

class SimplifyWalkerPostVisitTest_430 : public ::testing::Test {
protected:
  using PF = Regexp::ParseFlags;
  PF flags_ = static_cast<PF>(0);
  SimplifyWalker walker_;
};

// -- Leaf op cases that should Incref(re) and set simple() --------------------

TEST_F(SimplifyWalkerPostVisitTest_430, Literal_IncrefAndSimple_430) {
  Regexp* lit = Regexp::NewLiteral('a', flags_);
  ASSERT_NE(lit, nullptr);

  Regexp* out = walker_.PostVisit(lit, /*parent_arg=*/nullptr,
                                  /*pre_arg=*/nullptr,
                                  /*child_args=*/nullptr, /*nchild_args=*/0);
  ASSERT_EQ(out, lit);              // returns Incref() of the same node
  EXPECT_TRUE(lit->simple());       // marked simple via public accessor

  out->Decref();  // balance Incref() from PostVisit
  lit->Decref();  // destroy
}

// -- kRegexpConcat ------------------------------------------------------------

TEST_F(SimplifyWalkerPostVisitTest_430, Concat_NoChildChange_ReturnsIncref_430) {
  Regexp* a = Regexp::NewLiteral('a', flags_);
  Regexp* b = Regexp::NewLiteral('b', flags_);
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  Regexp* subs[2] = {a, b};
  Regexp* cat = Regexp::Concat(subs, 2, flags_);
  ASSERT_NE(cat, nullptr);

  // Prepare child_args equal to original children. Use Incref so PostVisit may
  // safely consume/decref if needed. For concat "no-change" branch, it does not
  // Decref them, so we will after the call.
  Regexp* child_args[2] = {cat->sub()[0]->Incref(), cat->sub()[1]->Incref()};

  Regexp* out = walker_.PostVisit(cat, /*parent_arg=*/nullptr,
                                  /*pre_arg=*/nullptr,
                                  child_args, /*nchild_args=*/2);
  ASSERT_EQ(out, cat);
  EXPECT_TRUE(cat->simple());

  out->Decref();            // balance Incref() of cat
  child_args[0]->Decref();  // balance our explicit Incref()s above
  child_args[1]->Decref();
  cat->Decref();            // destroy (and its owned children a,b)
}

TEST_F(SimplifyWalkerPostVisitTest_430, Concat_ChildChanged_RebuiltFromArgs_430) {
  // Original concat: ("a" , "b")
  Regexp* a = Regexp::NewLiteral('a', flags_);
  Regexp* b = Regexp::NewLiteral('b', flags_);
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  Regexp* subs[2] = {a, b};
  Regexp* cat = Regexp::Concat(subs, 2, flags_);
  ASSERT_NE(cat, nullptr);

  // New children differ from the originals -> should build a new concat node
  Regexp* x = Regexp::NewLiteral('x', flags_);
  Regexp* y = Regexp::NewLiteral('y', flags_);
  ASSERT_NE(x, nullptr);
  ASSERT_NE(y, nullptr);
  Regexp* child_args[2] = {x, y};

  Regexp* out = walker_.PostVisit(cat, /*parent_arg=*/nullptr,
                                  /*pre_arg=*/nullptr,
                                  child_args, /*nchild_args=*/2);
  ASSERT_NE(out, nullptr);
  EXPECT_NE(out, cat);
  EXPECT_EQ(out->op(), kRegexpConcat);
  ASSERT_EQ(out->nsub(), 2);
  EXPECT_EQ(out->sub()[0], x);  // ownership transferred into out
  EXPECT_EQ(out->sub()[1], y);
  EXPECT_TRUE(out->simple());

  out->Decref();  // destroys out and its children x,y
  cat->Decref();  // destroys cat and its children a,b
}

// -- kRegexpCapture -----------------------------------------------------------

TEST_F(SimplifyWalkerPostVisitTest_430, Capture_NoChildChange_ReturnsIncref_430) {
  Regexp* inner = Regexp::NewLiteral('q', flags_);
  ASSERT_NE(inner, nullptr);
  Regexp* cap = Regexp::Capture(inner, flags_, /*cap=*/7);
  ASSERT_NE(cap, nullptr);

  // Pass the same child pointer but Incref() it – PostVisit will Decref it.
  Regexp* child_args[1] = {cap->sub()[0]->Incref()};

  Regexp* out = walker_.PostVisit(cap, /*parent_arg=*/nullptr,
                                  /*pre_arg=*/nullptr,
                                  child_args, /*nchild_args=*/1);
  ASSERT_EQ(out, cap);
  EXPECT_TRUE(cap->simple());

  // child_args[0] was Decref()'d inside PostVisit; do NOT Decref it again.
  out->Decref();
  cap->Decref();
}

TEST_F(SimplifyWalkerPostVisitTest_430, Capture_ChildChanged_NewCaptureKeepsCap_430) {
  Regexp* inner = Regexp::NewLiteral('x', flags_);
  ASSERT_NE(inner, nullptr);
  const int kCap = 42;
  Regexp* cap = Regexp::Capture(inner, flags_, kCap);
  ASSERT_NE(cap, nullptr);

  // Different child -> PostVisit should build a new capture with same cap id.
  Regexp* new_child = Regexp::NewLiteral('y', flags_);
  ASSERT_NE(new_child, nullptr);
  Regexp* child_args[1] = {new_child};

  Regexp* out = walker_.PostVisit(cap, /*parent_arg=*/nullptr,
                                  /*pre_arg=*/nullptr,
                                  child_args, /*nchild_args=*/1);
  ASSERT_NE(out, nullptr);
  EXPECT_NE(out, cap);
  EXPECT_EQ(out->op(), kRegexpCapture);
  ASSERT_EQ(out->nsub(), 1);
  EXPECT_EQ(out->sub()[0], new_child);  // ownership moved into out
  EXPECT_EQ(out->cap(), cap->cap());    // cap id preserved
  EXPECT_TRUE(out->simple());

  out->Decref();  // destroys out and new_child
  cap->Decref();  // destroys original capture and its original child
}

// -- kRegexpStar / Plus / Quest ----------------------------------------------

TEST_F(SimplifyWalkerPostVisitTest_430, Star_ChildUnchanged_ReturnsIncref_430) {
  Regexp* inner = Regexp::NewLiteral('s', flags_);
  ASSERT_NE(inner, nullptr);
  Regexp* star = Regexp::Star(inner, flags_);
  ASSERT_NE(star, nullptr);

  // Same child pointer (Incref'd) -> PostVisit Decref(child) and Incref(re)
  Regexp* child_args[1] = {star->sub()[0]->Incref()};

  Regexp* out = walker_.PostVisit(star, /*parent_arg=*/nullptr,
                                  /*pre_arg=*/nullptr,
                                  child_args, /*nchild_args=*/1);
  ASSERT_EQ(out, star);
  EXPECT_TRUE(star->simple());

  out->Decref();
  star->Decref();
}

TEST_F(SimplifyWalkerPostVisitTest_430, Star_ChildIsSameOp_ReturnsChild_430) {
  // re is STAR(of 'a'), but child result is STAR(of 'b') with same flags.
  Regexp* inner_a = Regexp::NewLiteral('a', flags_);
  ASSERT_NE(inner_a, nullptr);
  Regexp* re_star = Regexp::Star(inner_a, flags_);
  ASSERT_NE(re_star, nullptr);

  Regexp* inner_b = Regexp::NewLiteral('b', flags_);
  ASSERT_NE(inner_b, nullptr);
  Regexp* child_star = Regexp::Star(inner_b, flags_);
  ASSERT_NE(child_star, nullptr);

  Regexp* child_args[1] = {child_star};

  Regexp* out = walker_.PostVisit(re_star, /*parent_arg=*/nullptr,
                                  /*pre_arg=*/nullptr,
                                  child_args, /*nchild_args=*/1);
  // For same op and flags, PostVisit returns the child directly.
  ASSERT_EQ(out, child_star);

  out->Decref();    // destroys child_star (and its inner_b)
  re_star->Decref(); // destroys re_star (and its inner_a)
}

// -- kRegexpRepeat ------------------------------------------------------------

TEST_F(SimplifyWalkerPostVisitTest_430, Repeat_NonEmptyChild_DelegatesAndSetsSimple_430) {
  // Build a {2,3} repeat. We don't assert the exact structure returned by
  // SimplifyRepeat (black-box); we only assert that we got a non-null Regexp
  // and that it was marked simple().
  Regexp* inner = Regexp::NewLiteral('r', flags_);
  ASSERT_NE(inner, nullptr);
  Regexp* rpt = Regexp::Repeat(inner, flags_, /*min=*/2, /*max=*/3);
  ASSERT_NE(rpt, nullptr);

  Regexp* new_child = Regexp::NewLiteral('z', flags_);
  ASSERT_NE(new_child, nullptr);
  Regexp* child_args[1] = {new_child};  // PostVisit will Decref(new_child)

  Regexp* out = walker_.PostVisit(rpt, /*parent_arg=*/nullptr,
                                  /*pre_arg=*/nullptr,
                                  child_args, /*nchild_args=*/1);
  ASSERT_NE(out, nullptr);
  EXPECT_TRUE(out->simple());

  out->Decref();  // destroy result of SimplifyRepeat
  rpt->Decref();  // destroy original repeat node
}

}  // namespace re2
