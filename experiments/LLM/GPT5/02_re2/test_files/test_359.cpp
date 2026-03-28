// File: named_captures_walker_test_359.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"

using re2::Regexp;
using re2::NamedCapturesWalker;

namespace {

class NamedCapturesWalkerTest_359 : public ::testing::Test {
protected:
  // Helper: Parse a pattern and return a Regexp*. Caller must Decref().
  Regexp* ParseOrNull(const std::string& pattern) {
    re2::RegexpStatus status;
    // Treat flags as a black box: pass 0.
    return Regexp::Parse(pattern, static_cast<Regexp::ParseFlags>(0), &status);
  }
};

TEST_F(NamedCapturesWalkerTest_359, TakeMapInitiallyNull_359) {
  NamedCapturesWalker w;
  // No traversal yet -> internal map should not exist.
  std::map<std::string, int>* m = w.TakeMap();
  EXPECT_EQ(m, nullptr);
}

TEST_F(NamedCapturesWalkerTest_359, NoNamedCapturesProducesNoMap_359) {
  Regexp* re = ParseOrNull("(abc)");  // plain capturing group, no name
  ASSERT_NE(re, nullptr);

  NamedCapturesWalker w;
  bool stop = false;
  // Walk the tree; should not allocate a map because there are no named caps.
  (void)w.Walk(re, 0, &stop);

  std::map<std::string, int>* m = w.TakeMap();
  EXPECT_EQ(m, nullptr);

  re->Decref();
}

TEST_F(NamedCapturesWalkerTest_359, SingleNamedCaptureCollected_359) {
  Regexp* re = ParseOrNull("(?P<foo>a)");
  ASSERT_NE(re, nullptr);

  NamedCapturesWalker w;
  bool stop = false;
  (void)w.Walk(re, 0, &stop);

  std::map<std::string, int>* m = w.TakeMap();
  ASSERT_NE(m, nullptr);
  // Expect exactly one entry: "foo" -> its capture index.
  ASSERT_EQ(m->size(), 1u);
  ASSERT_TRUE(m->find("foo") != m->end());

  // For a single named group, capture index should be 1.
  EXPECT_EQ(m->at("foo"), 1);

  delete m;
  re->Decref();
}

TEST_F(NamedCapturesWalkerTest_359, MultipleNamedCapturesCollected_359) {
  Regexp* re = ParseOrNull("(?P<foo>a)(?P<bar>b)");
  ASSERT_NE(re, nullptr);

  NamedCapturesWalker w;
  bool stop = false;
  (void)w.Walk(re, 0, &stop);

  std::map<std::string, int>* m = w.TakeMap();
  ASSERT_NE(m, nullptr);
  // Two distinct names should be present.
  EXPECT_EQ(m->size(), 2u);
  ASSERT_TRUE(m->find("foo") != m->end());
  ASSERT_TRUE(m->find("bar") != m->end());

  // Left-to-right numbering is observable via Parse().
  EXPECT_EQ(m->at("foo"), 1);
  EXPECT_EQ(m->at("bar"), 2);

  delete m;
  re->Decref();
}

TEST_F(NamedCapturesWalkerTest_359, DuplicateNameKeepsFirstMapping_359) {
  Regexp* re = ParseOrNull("(?P<dup>a)(?P<dup>b)");
  ASSERT_NE(re, nullptr);

  NamedCapturesWalker w;
  bool stop = false;
  (void)w.Walk(re, 0, &stop);

  std::map<std::string, int>* m = w.TakeMap();
  ASSERT_NE(m, nullptr);

  // Only one entry for "dup" should exist because insert() doesn't overwrite.
  EXPECT_EQ(m->size(), 1u);
  ASSERT_TRUE(m->find("dup") != m->end());
  // The first group's index should be kept (observable numbering).
  EXPECT_EQ(m->at("dup"), 1);

  delete m;
  re->Decref();
}

TEST_F(NamedCapturesWalkerTest_359, PreVisitReturnsIgnoredUnchanged_359) {
  Regexp* re = ParseOrNull("a");  // non-capture node
  ASSERT_NE(re, nullptr);

  NamedCapturesWalker w;
  bool stop = false;

  // Call PreVisit directly and verify it returns the same 'ignored' value.
  int in = 12345;
  int out = w.PreVisit(re, in, &stop);
  EXPECT_EQ(out, in);

  // Also ensure no map was created as this is not a capture node.
  EXPECT_EQ(w.TakeMap(), nullptr);

  re->Decref();
}

TEST_F(NamedCapturesWalkerTest_359, TakeMapTransfersOwnershipAndResets_359) {
  Regexp* re = ParseOrNull("(?P<x>a)");
  ASSERT_NE(re, nullptr);

  NamedCapturesWalker w;
  bool stop = false;
  (void)w.Walk(re, 0, &stop);

  std::map<std::string, int>* first = w.TakeMap();
  ASSERT_NE(first, nullptr);
  // After TakeMap(), internal pointer should be cleared.
  std::map<std::string, int>* second = w.TakeMap();
  EXPECT_EQ(second, nullptr);

  delete first;
  re->Decref();
}

}  // namespace
