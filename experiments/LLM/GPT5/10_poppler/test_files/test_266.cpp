// TEST_ID: 266
// File: test_xref_gettrailerdict_266.cpp

#include <gtest/gtest.h>

#include "poppler/XRef.h"

namespace {

// Simple fixture for TEST_ID 266
class XRefTest_266 : public ::testing::Test {
protected:
  XRef xref_;
};

TEST_F(XRefTest_266, GetTrailerDictReturnsNonNull_266) {
  Object* trailer = xref_.getTrailerDict();
  ASSERT_NE(trailer, nullptr);
}

TEST_F(XRefTest_266, GetTrailerDictReturnsSamePointerOnRepeatedCalls_266) {
  Object* trailer1 = xref_.getTrailerDict();
  Object* trailer2 = xref_.getTrailerDict();
  ASSERT_NE(trailer1, nullptr);
  ASSERT_NE(trailer2, nullptr);
  EXPECT_EQ(trailer1, trailer2);
}

TEST_F(XRefTest_266, DifferentInstancesReturnDifferentTrailerDictPointers_266) {
  XRef xref2;

  Object* trailer1 = xref_.getTrailerDict();
  Object* trailer2 = xref2.getTrailerDict();

  ASSERT_NE(trailer1, nullptr);
  ASSERT_NE(trailer2, nullptr);

  // Each XRef owns its own trailer dictionary object, so the addresses should differ.
  EXPECT_NE(trailer1, trailer2);
}

TEST_F(XRefTest_266, ReturnedPointerMatchesAddressFromRepeatedAccessAfterOtherWork_266) {
  Object* trailer1 = xref_.getTrailerDict();
  ASSERT_NE(trailer1, nullptr);

  // Do some unrelated operations that should not affect pointer stability.
  // (We intentionally avoid relying on any Object internals.)
  for (int i = 0; i < 10; ++i) {
    Object* tmp = xref_.getTrailerDict();
    ASSERT_NE(tmp, nullptr);
  }

  Object* trailer2 = xref_.getTrailerDict();
  ASSERT_NE(trailer2, nullptr);
  EXPECT_EQ(trailer1, trailer2);
}

}  // namespace