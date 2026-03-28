// TEST_ID: 112
// File: test_array_getlength_112.cpp

#include <gtest/gtest.h>

#include "poppler/Array.h"

namespace {

class ArrayTest_112 : public ::testing::Test {
protected:
  // Many Poppler classes take an XRef*; for getLength() specifically,
  // the observable behavior should not depend on XRef interaction.
  // Passing nullptr keeps the test focused on the public interface.
  XRef* xref_ = nullptr;
};

TEST_F(ArrayTest_112, GetLength_IsNonNegative_112) {
  Array arr(xref_);
  const int len = arr.getLength();
  EXPECT_GE(len, 0);
}

TEST_F(ArrayTest_112, GetLength_IsStableAcrossRepeatedCalls_112) {
  Array arr(xref_);
  const int len1 = arr.getLength();
  const int len2 = arr.getLength();
  const int len3 = arr.getLength();

  EXPECT_EQ(len1, len2);
  EXPECT_EQ(len2, len3);
}

TEST_F(ArrayTest_112, GetLength_IsCallableOnConstArray_112) {
  Array arr(xref_);
  const Array& carr = arr;

  const int len = carr.getLength();
  EXPECT_GE(len, 0);
}

TEST_F(ArrayTest_112, GetLength_DoesNotThrow_112) {
  Array arr(xref_);
  EXPECT_NO_THROW({
    (void)arr.getLength();
  });
}

}  // namespace