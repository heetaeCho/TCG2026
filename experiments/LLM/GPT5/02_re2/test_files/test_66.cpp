// File: pod_array_test_66.cc
#include <gtest/gtest.h>
#include "re2/pod_array.h"

namespace {

using re2::PODArray;

class PODArrayTest_66 : public ::testing::Test {};

TEST_F(PODArrayTest_66, DefaultCtor_HasSizeZero_66) {
  PODArray<int> a;
  // Observable behavior: default-constructed container has zero size.
  EXPECT_EQ(a.size(), 0);
}

TEST_F(PODArrayTest_66, DefaultCtor_DataIsNullWhenEmpty_66) {
  PODArray<int> a;
  // When size() == 0, data() should be a null pointer (safe boundary behavior).
  EXPECT_EQ(a.data(), nullptr);
}

TEST_F(PODArrayTest_66, LenCtor_SetsSizeAndAllocates_66) {
  const int n = 3;
  PODArray<int> a(n);

  // Observable behaviors from the interface:
  // - size() reflects the length passed to the constructor
  // - data() is usable (non-null) when size() > 0
  EXPECT_EQ(a.size(), n);
  EXPECT_NE(a.data(), nullptr);
}

TEST_F(PODArrayTest_66, Indexing_ReadWriteRoundTrip_66) {
  const int n = 4;
  PODArray<int> a(n);

  // Write via operator[] and read back; verifies returned reference is writable.
  for (int i = 0; i < n; ++i) {
    a[i] = i * 10;
  }
  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(a[i], i * 10);
  }
}

TEST_F(PODArrayTest_66, DataPointsToFirstElement_66) {
  const int n = 2;
  PODArray<int> a(n);

  a[0] = 42;
  a[1] = 7;

  // For non-empty arrays, &a[0] should equal data().
  ASSERT_GT(a.size(), 0);
  EXPECT_EQ(a.data(), &a[0]);
  EXPECT_EQ(*a.data(), 42);
}

TEST_F(PODArrayTest_66, ConstAccess_AllowsReadingViaOperatorBracket_66) {
  const int n = 3;
  PODArray<int> a(n);
  a[0] = 1;
  a[1] = 2;
  a[2] = 3;

  const PODArray<int>& ca = a;  // Use const-qualified interface.
  // Only read through const; do not rely on ability to modify through const.
  EXPECT_EQ(ca.size(), n);
  EXPECT_NE(ca.data(), nullptr);
  EXPECT_EQ(ca[0], 1);
  EXPECT_EQ(ca[1], 2);
  EXPECT_EQ(ca[2], 3);
}

TEST_F(PODArrayTest_66, ZeroLengthArray_DisallowsIndexingButReportsZero_66) {
  PODArray<int> a;  // size() == 0
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a.data(), nullptr);

  // We do NOT attempt out-of-bounds access since behavior is undefined and
  // not specified by the interface. This test simply documents the boundary.
}

}  // namespace
