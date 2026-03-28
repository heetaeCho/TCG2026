#include "gtest/gtest.h"
#include "re2/pod_array.h"

namespace re2 {

// Test default construction
TEST(PODArrayTest_68, DefaultConstruction_68) {
  PODArray<int> arr;
  EXPECT_EQ(arr.data(), nullptr);
  EXPECT_EQ(arr.size(), 0);
}

// Test construction with a specific length
TEST(PODArrayTest_68, ConstructionWithLength_68) {
  PODArray<int> arr(10);
  EXPECT_NE(arr.data(), nullptr);
  EXPECT_EQ(arr.size(), 10);
}

// Test operator[] for read and write access
TEST(PODArrayTest_68, SubscriptOperatorReadWrite_68) {
  PODArray<int> arr(5);
  for (int i = 0; i < 5; i++) {
    arr[i] = i * 10;
  }
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(arr[i], i * 10);
  }
}

// Test operator[] at boundary indices
TEST(PODArrayTest_68, SubscriptOperatorBoundary_68) {
  PODArray<int> arr(3);
  arr[0] = 42;
  arr[2] = 99;
  EXPECT_EQ(arr[0], 42);
  EXPECT_EQ(arr[2], 99);
}

// Test data() returns pointer to underlying storage
TEST(PODArrayTest_68, DataPointerConsistency_68) {
  PODArray<int> arr(4);
  arr[0] = 100;
  arr[3] = 200;
  int* ptr = arr.data();
  EXPECT_EQ(ptr[0], 100);
  EXPECT_EQ(ptr[3], 200);
}

// Test with length 1
TEST(PODArrayTest_68, SingleElementArray_68) {
  PODArray<double> arr(1);
  arr[0] = 3.14;
  EXPECT_DOUBLE_EQ(arr[0], 3.14);
  EXPECT_EQ(arr.size(), 1);
}

// Test with a different POD type (char)
TEST(PODArrayTest_68, CharType_68) {
  PODArray<char> arr(3);
  arr[0] = 'a';
  arr[1] = 'b';
  arr[2] = 'c';
  EXPECT_EQ(arr[0], 'a');
  EXPECT_EQ(arr[1], 'b');
  EXPECT_EQ(arr[2], 'c');
}

// Test move construction
TEST(PODArrayTest_68, MoveConstruction_68) {
  PODArray<int> arr(5);
  for (int i = 0; i < 5; i++) {
    arr[i] = i;
  }
  PODArray<int> arr2(std::move(arr));
  EXPECT_EQ(arr2.size(), 5);
  EXPECT_NE(arr2.data(), nullptr);
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(arr2[i], i);
  }
  // After move, the source should be in a valid but unspecified state
  // Typically null/empty
  EXPECT_EQ(arr.data(), nullptr);
  EXPECT_EQ(arr.size(), 0);
}

// Test move assignment
TEST(PODArrayTest_68, MoveAssignment_68) {
  PODArray<int> arr(3);
  arr[0] = 10;
  arr[1] = 20;
  arr[2] = 30;

  PODArray<int> arr2;
  arr2 = std::move(arr);
  EXPECT_EQ(arr2.size(), 3);
  EXPECT_EQ(arr2[0], 10);
  EXPECT_EQ(arr2[1], 20);
  EXPECT_EQ(arr2[2], 30);
}

// Test larger array
TEST(PODArrayTest_68, LargerArray_68) {
  const int len = 10000;
  PODArray<int> arr(len);
  EXPECT_EQ(arr.size(), len);
  for (int i = 0; i < len; i++) {
    arr[i] = i;
  }
  for (int i = 0; i < len; i++) {
    EXPECT_EQ(arr[i], i);
  }
}

// Test with unsigned type
TEST(PODArrayTest_68, UnsignedType_68) {
  PODArray<unsigned int> arr(4);
  arr[0] = 0u;
  arr[1] = 1u;
  arr[2] = 4294967295u;  // max unsigned int
  arr[3] = 42u;
  EXPECT_EQ(arr[0], 0u);
  EXPECT_EQ(arr[1], 1u);
  EXPECT_EQ(arr[2], 4294967295u);
  EXPECT_EQ(arr[3], 42u);
}

// Test overwriting values
TEST(PODArrayTest_68, OverwriteValues_68) {
  PODArray<int> arr(2);
  arr[0] = 1;
  arr[1] = 2;
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  arr[0] = 100;
  arr[1] = 200;
  EXPECT_EQ(arr[0], 100);
  EXPECT_EQ(arr[1], 200);
}

}  // namespace re2
