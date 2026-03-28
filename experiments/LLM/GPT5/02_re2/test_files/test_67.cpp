// File: pod_array_size_test_67.cc

#include <gtest/gtest.h>
#include "re2/pod_array.h"

namespace {

using re2::PODArray;

// Suite focuses strictly on observable size() behavior.
class PODArrayTest_67 : public ::testing::Test {};

TEST(PODArrayTest_67, DefaultConstructedSizeIsZero_67) {
  PODArray<int> a;
  EXPECT_EQ(a.size(), 0);
}

TEST(PODArrayTest_67, SizeMatchesConstructorArgument_67) {
  const int sizes[] = {1, 2, 5, 16};
  for (int n : sizes) {
    PODArray<int> a(n);
    EXPECT_EQ(a.size(), n) << "size() should reflect constructor length";
  }
}

TEST(PODArrayTest_67, SizeUnaffectedByElementWrites_67) {
  // Verify that writing/reading through the public operator[] (observable behavior)
  // does not change size().
  const int n = 3;
  PODArray<int> a(n);
  for (int i = 0; i < n; ++i) {
    a[i] = i * 10;        // observable interaction via public operator[]
  }
  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(a[i], i * 10);
  }
  EXPECT_EQ(a.size(), n);
}

TEST(PODArrayTest_67, LargeSizeConstruction_67) {
  // Boundary-ish condition: reasonably large allocation that should succeed in typical test envs.
  const int n = 4096;
  PODArray<int> a(n);
  EXPECT_EQ(a.size(), n);
}

}  // namespace
