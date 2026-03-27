// TEST_ID 268
// File: test_xref_setmodified_268.cpp

#include <gtest/gtest.h>

#include "poppler/XRef.h"

namespace {

class XRefTest_268 : public ::testing::Test {};

TEST_F(XRefTest_268, SetModifiedMakesIsModifiedTrue_268) {
  XRef xref;

  EXPECT_NO_THROW(xref.setModified());
  EXPECT_TRUE(xref.isModified());
}

TEST_F(XRefTest_268, SetModifiedIsIdempotent_268) {
  XRef xref;

  xref.setModified();
  const bool afterFirst = xref.isModified();

  EXPECT_NO_THROW(xref.setModified());
  EXPECT_TRUE(xref.isModified());

  // Once modified, it should not become "unmodified" by calling setModified again.
  if (afterFirst) {
    EXPECT_TRUE(xref.isModified());
  }
}

TEST_F(XRefTest_268, SetModifiedWorksRegardlessOfInitialState_268) {
  XRef xref;

  // Do not assume the initial state (could be false or true depending on construction).
  const bool initial = xref.isModified();

  xref.setModified();
  EXPECT_TRUE(xref.isModified());

  // If it was already modified, it should remain modified.
  if (initial) {
    EXPECT_TRUE(xref.isModified());
  }
}

}  // namespace