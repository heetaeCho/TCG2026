// File: pod_array_test_68.cc
#include <gtest/gtest.h>
#include "re2/pod_array.h"

using re2::PODArray;

namespace {

// A simple POD type to verify templated behavior on non-primitive types.
struct PODSample {
  int a;
  unsigned b;
};

TEST(PODArrayTest_68, ConstructWithLength_SetsSizeAndAllowsRW_68) {
  const int kLen = 5;
  PODArray<int> arr(kLen);

  // Observable behavior: size() reports the requested length.
  EXPECT_EQ(arr.size(), kLen);

  // Observable behavior: operator[] returns a reference that can be written/read.
  for (int i = 0; i < kLen; ++i) {
    arr[i] = i * 10;  // write
  }
  for (int i = 0; i < kLen; ++i) {
    EXPECT_EQ(arr[i], i * 10);  // read back
  }
}

TEST(PODArrayTest_68, DataPointsToFirstElement_68) {
  PODArray<int> arr(3);
  // Write a value to the first slot.
  arr[0] = 42;

  // Observable: data() returns a T*; &arr[0] should be that same address.
  ASSERT_NE(arr.data(), nullptr);
  EXPECT_EQ(&arr[0], arr.data());
  EXPECT_EQ(arr.data()[0], 42);
}

TEST(PODArrayTest_68, Boundary_LastValidIndexIsAccessible_68) {
  PODArray<int> arr(3);
  arr[0] = 1;
  arr[1] = 2;
  arr[2] = 3;  // last valid index

  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

TEST(PODArrayTest_68, ZeroLength_HasSizeZero_68) {
  PODArray<int> arr(0);

  // Only assert what the interface guarantees and is observable.
  EXPECT_EQ(arr.size(), 0);

  // Do NOT touch arr[0] or arr.data()[0] here, as behavior is not defined by the interface.
}

TEST(PODArrayTest_68, WorksWithPODStructType_68) {
  PODArray<PODSample> arr(2);

  PODSample s0{10, 20u};
  PODSample s1{30, 40u};

  arr[0] = s0;
  arr[1] = s1;

  EXPECT_EQ(arr.size(), 2);
  EXPECT_EQ(arr[0].a, 10);
  EXPECT_EQ(arr[0].b, 20u);
  EXPECT_EQ(arr[1].a, 30);
  EXPECT_EQ(arr[1].b, 40u);
}

TEST(PODArrayTest_68, ConstOperatorBracket_ReturnsModifiableRef_68) {
  PODArray<int> mutable_arr(2);
  mutable_arr[0] = 7;
  mutable_arr[1] = 11;

  // The interface declares: T& operator[](int) const;
  // Through a const reference, we should still be able to modify elements (as declared).
  const PODArray<int>& const_ref = mutable_arr;
  const_ref[0] = 100;  // modify via const-qualified operator[]

  EXPECT_EQ(mutable_arr[0], 100);
  EXPECT_EQ(mutable_arr[1], 11);
}

}  // namespace
