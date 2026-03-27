// File: test_xref_isModified_267.cpp
#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/XRef.h"

namespace {

class XRefTest_267 : public ::testing::Test {};

TEST_F(XRefTest_267, DefaultConstruction_IsModifiedIsCallableAndStable_267) {
  XRef xref;

  const bool first = xref.isModified();
  const bool second = xref.isModified();

  // Observable behavior: calling the const accessor should be stable
  // when no mutating API is invoked.
  EXPECT_EQ(first, second);
}

TEST_F(XRefTest_267, ConstObject_IsModifiedIsCallable_267) {
  const XRef xref;
  // Just verify it compiles/links and returns a bool.
  const bool v = xref.isModified();
  (void)v;
  SUCCEED();
}

TEST_F(XRefTest_267, SetModified_MakesIsModifiedTrueOrKeepsItTrue_267) {
  XRef xref;

  const bool before = xref.isModified();
  xref.setModified();
  const bool after = xref.isModified();

  // Observable contract we can safely assert without peeking into internals:
  // setModified should not make "modified" become false.
  EXPECT_TRUE(after);

  // If the object started unmodified, setModified should flip it to true.
  // If it started modified, it should remain modified (idempotent behavior).
  if (!before) {
    EXPECT_TRUE(after);
  } else {
    EXPECT_TRUE(before);
    EXPECT_TRUE(after);
  }
}

TEST_F(XRefTest_267, SetModified_IsIdempotent_267) {
  XRef xref;

  xref.setModified();
  const bool once = xref.isModified();

  xref.setModified();
  const bool twice = xref.isModified();

  // Boundary/robustness: repeated calls should not toggle back to false.
  EXPECT_TRUE(once);
  EXPECT_TRUE(twice);
}

}  // namespace