// TEST_ID: 265
#include <gtest/gtest.h>

#include "XRef.h"

namespace {

// Simple fixture for grouping XRef tests (no assumptions about internal state).
class XRefTest_265 : public ::testing::Test {
protected:
  XRef xref_;
};

} // namespace

TEST_F(XRefTest_265, GetRootMatchesGetRootNumAndGen_265) {
  const Ref root = xref_.getRoot();

  // Observable consistency between public getters.
  EXPECT_EQ(root.num, xref_.getRootNum());
  EXPECT_EQ(root.gen, xref_.getRootGen());
}

TEST_F(XRefTest_265, GetRootIsStableAcrossCalls_265) {
  const Ref r1 = xref_.getRoot();
  const Ref r2 = xref_.getRoot();

  EXPECT_EQ(r1.num, r2.num);
  EXPECT_EQ(r1.gen, r2.gen);

  // Still consistent with numeric getters.
  EXPECT_EQ(r1.num, xref_.getRootNum());
  EXPECT_EQ(r1.gen, xref_.getRootGen());
}

TEST_F(XRefTest_265, GetRootWorksOnConstObject_265) {
  const XRef &cxref = xref_;
  const Ref root = cxref.getRoot();

  EXPECT_EQ(root.num, cxref.getRootNum());
  EXPECT_EQ(root.gen, cxref.getRootGen());
}

TEST_F(XRefTest_265, GetRootDoesNotChangeModifiedFlag_265) {
  const bool before = xref_.isModified();
  (void)xref_.getRoot();
  const bool after = xref_.isModified();

  EXPECT_EQ(before, after);
}

TEST_F(XRefTest_265, SetModifiedDoesNotChangeRoot_265) {
  const Ref before = xref_.getRoot();

  xref_.setModified();
  EXPECT_TRUE(xref_.isModified());

  const Ref after = xref_.getRoot();
  EXPECT_EQ(before.num, after.num);
  EXPECT_EQ(before.gen, after.gen);

  // Keep consistency checks too.
  EXPECT_EQ(after.num, xref_.getRootNum());
  EXPECT_EQ(after.gen, xref_.getRootGen());
}

TEST_F(XRefTest_265, CopyPreservesRootIfCopySucceeds_265) {
  const Ref originalRoot = xref_.getRoot();

  const XRef *copied = xref_.copy();

  // We avoid assuming copy() must succeed.
  if (copied) {
    const Ref copiedRoot = copied->getRoot();
    EXPECT_EQ(copiedRoot.num, copied->getRootNum());
    EXPECT_EQ(copiedRoot.gen, copied->getRootGen());

    EXPECT_EQ(copiedRoot.num, originalRoot.num);
    EXPECT_EQ(copiedRoot.gen, originalRoot.gen);
  }
}