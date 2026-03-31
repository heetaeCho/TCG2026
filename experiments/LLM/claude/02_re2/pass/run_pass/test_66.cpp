#include "gtest/gtest.h"
#include "re2/pod_array.h"

namespace re2 {
namespace {

// Test default construction
TEST(PODArrayTest_66, DefaultConstruction_66) {
  PODArray<int> arr;
  EXPECT_EQ(arr.data(), nullptr);
  EXPECT_EQ(arr.size(), 0);
}

// Test construction with a specific length
TEST(PODArrayTest_66, ConstructWithLength_66) {
  PODArray<int> arr(10);
  EXPECT_NE(arr.data(), nullptr);
  EXPECT_EQ(arr.size(), 10);
}

// Test that data() returns a valid pointer after construction with length
TEST(PODArrayTest_66, DataReturnsValidPointer_66) {
  PODArray<double> arr(5);
  double* ptr = arr.data();
  EXPECT_NE(ptr, nullptr);
}

// Test operator[] for read and write access
TEST(PODArrayTest_66, SubscriptOperatorReadWrite_66) {
  PODArray<int> arr(5);
  for (int i = 0; i < 5; i++) {
    arr[i] = i * 10;
  }
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(arr[i], i * 10);
  }
}

// Test size() returns the correct length
TEST(PODArrayTest_66, SizeReturnsCorrectLength_66) {
  PODArray<char> arr(100);
  EXPECT_EQ(arr.size(), 100);
}

// Test construction with length 1 (boundary)
TEST(PODArrayTest_66, ConstructWithLengthOne_66) {
  PODArray<int> arr(1);
  EXPECT_NE(arr.data(), nullptr);
  EXPECT_EQ(arr.size(), 1);
  arr[0] = 42;
  EXPECT_EQ(arr[0], 42);
}

// Test that data() and operator[] refer to the same memory
TEST(PODArrayTest_66, DataAndSubscriptConsistent_66) {
  PODArray<int> arr(3);
  arr[0] = 100;
  arr[1] = 200;
  arr[2] = 300;
  int* ptr = arr.data();
  EXPECT_EQ(ptr[0], 100);
  EXPECT_EQ(ptr[1], 200);
  EXPECT_EQ(ptr[2], 300);
}

// Test with different POD types (float)
TEST(PODArrayTest_66, FloatType_66) {
  PODArray<float> arr(4);
  arr[0] = 1.5f;
  arr[1] = 2.5f;
  arr[2] = 3.5f;
  arr[3] = 4.5f;
  EXPECT_FLOAT_EQ(arr[0], 1.5f);
  EXPECT_FLOAT_EQ(arr[1], 2.5f);
  EXPECT_FLOAT_EQ(arr[2], 3.5f);
  EXPECT_FLOAT_EQ(arr[3], 4.5f);
}

// Test with char type
TEST(PODArrayTest_66, CharType_66) {
  PODArray<char> arr(3);
  arr[0] = 'a';
  arr[1] = 'b';
  arr[2] = 'c';
  EXPECT_EQ(arr[0], 'a');
  EXPECT_EQ(arr[1], 'b');
  EXPECT_EQ(arr[2], 'c');
}

// Test with a larger allocation
TEST(PODArrayTest_66, LargeAllocation_66) {
  const int len = 10000;
  PODArray<int> arr(len);
  EXPECT_EQ(arr.size(), len);
  EXPECT_NE(arr.data(), nullptr);
  for (int i = 0; i < len; i++) {
    arr[i] = i;
  }
  for (int i = 0; i < len; i++) {
    EXPECT_EQ(arr[i], i);
  }
}

// Test move construction
TEST(PODArrayTest_66, MoveConstruction_66) {
  PODArray<int> arr(5);
  arr[0] = 42;
  arr[4] = 99;
  PODArray<int> arr2(std::move(arr));
  EXPECT_EQ(arr2.size(), 5);
  EXPECT_EQ(arr2[0], 42);
  EXPECT_EQ(arr2[4], 99);
  // Original should be in a moved-from state
  EXPECT_EQ(arr.data(), nullptr);
  EXPECT_EQ(arr.size(), 0);
}

// Test move assignment
TEST(PODArrayTest_66, MoveAssignment_66) {
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
  EXPECT_EQ(arr.data(), nullptr);
  EXPECT_EQ(arr.size(), 0);
}

// Test boundary: first and last element access
TEST(PODArrayTest_66, FirstAndLastElement_66) {
  PODArray<int> arr(10);
  arr[0] = -1;
  arr[9] = -2;
  EXPECT_EQ(arr[0], -1);
  EXPECT_EQ(arr[9], -2);
}

// Test with unsigned char (byte-like POD)
TEST(PODArrayTest_66, UnsignedCharType_66) {
  PODArray<unsigned char> arr(256);
  EXPECT_EQ(arr.size(), 256);
  for (int i = 0; i < 256; i++) {
    arr[i] = static_cast<unsigned char>(i);
  }
  for (int i = 0; i < 256; i++) {
    EXPECT_EQ(arr[i], static_cast<unsigned char>(i));
  }
}

}  // namespace
}  // namespace re2
