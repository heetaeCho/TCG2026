#include "gtest/gtest.h"
#include "re2/pod_array.h"

namespace re2 {
namespace {

// Test default constructor creates an array with size 0
TEST(PODArrayTest_67, DefaultConstructorHasSizeZero_67) {
  PODArray<int> arr;
  EXPECT_EQ(arr.size(), 0);
}

// Test constructor with specific length
TEST(PODArrayTest_67, ConstructorWithLengthSetsSizeCorrectly_67) {
  PODArray<int> arr(10);
  EXPECT_EQ(arr.size(), 10);
}

// Test constructor with length 1
TEST(PODArrayTest_67, ConstructorWithLengthOne_67) {
  PODArray<int> arr(1);
  EXPECT_EQ(arr.size(), 1);
}

// Test constructor with large length
TEST(PODArrayTest_67, ConstructorWithLargeLength_67) {
  PODArray<int> arr(10000);
  EXPECT_EQ(arr.size(), 10000);
}

// Test data() returns non-null for non-empty array
TEST(PODArrayTest_67, DataReturnsNonNullForNonEmptyArray_67) {
  PODArray<int> arr(5);
  EXPECT_NE(arr.data(), nullptr);
}

// Test data() returns null for default-constructed array
TEST(PODArrayTest_67, DataReturnsNullForDefaultConstructedArray_67) {
  PODArray<int> arr;
  EXPECT_EQ(arr.data(), nullptr);
}

// Test operator[] can write and read back values
TEST(PODArrayTest_67, OperatorBracketWriteAndRead_67) {
  PODArray<int> arr(5);
  arr[0] = 42;
  arr[1] = 100;
  arr[4] = -7;
  EXPECT_EQ(arr[0], 42);
  EXPECT_EQ(arr[1], 100);
  EXPECT_EQ(arr[4], -7);
}

// Test operator[] with different types
TEST(PODArrayTest_67, OperatorBracketWithCharType_67) {
  PODArray<char> arr(3);
  arr[0] = 'a';
  arr[1] = 'b';
  arr[2] = 'c';
  EXPECT_EQ(arr[0], 'a');
  EXPECT_EQ(arr[1], 'b');
  EXPECT_EQ(arr[2], 'c');
}

// Test operator[] with double type
TEST(PODArrayTest_67, OperatorBracketWithDoubleType_67) {
  PODArray<double> arr(2);
  arr[0] = 3.14;
  arr[1] = 2.71;
  EXPECT_DOUBLE_EQ(arr[0], 3.14);
  EXPECT_DOUBLE_EQ(arr[1], 2.71);
}

// Test that data() points to the same memory as operator[]
TEST(PODArrayTest_67, DataConsistentWithOperatorBracket_67) {
  PODArray<int> arr(3);
  arr[0] = 10;
  arr[1] = 20;
  arr[2] = 30;
  int* d = arr.data();
  EXPECT_EQ(d[0], 10);
  EXPECT_EQ(d[1], 20);
  EXPECT_EQ(d[2], 30);
}

// Test move constructor
TEST(PODArrayTest_67, MoveConstructor_67) {
  PODArray<int> arr(5);
  arr[0] = 99;
  PODArray<int> arr2(std::move(arr));
  EXPECT_EQ(arr2.size(), 5);
  EXPECT_EQ(arr2[0], 99);
  EXPECT_EQ(arr.size(), 0);
}

// Test move assignment
TEST(PODArrayTest_67, MoveAssignment_67) {
  PODArray<int> arr(5);
  arr[0] = 77;
  PODArray<int> arr2;
  arr2 = std::move(arr);
  EXPECT_EQ(arr2.size(), 5);
  EXPECT_EQ(arr2[0], 77);
  EXPECT_EQ(arr.size(), 0);
}

// Test overwriting values
TEST(PODArrayTest_67, OverwriteValues_67) {
  PODArray<int> arr(3);
  arr[0] = 1;
  arr[0] = 2;
  EXPECT_EQ(arr[0], 2);
}

// Test with unsigned char type
TEST(PODArrayTest_67, UnsignedCharType_67) {
  PODArray<unsigned char> arr(256);
  EXPECT_EQ(arr.size(), 256);
  for (int i = 0; i < 256; i++) {
    arr[i] = static_cast<unsigned char>(i);
  }
  for (int i = 0; i < 256; i++) {
    EXPECT_EQ(arr[i], static_cast<unsigned char>(i));
  }
}

// Test boundary: size of exactly 1
TEST(PODArrayTest_67, BoundarySizeOne_67) {
  PODArray<int> arr(1);
  EXPECT_EQ(arr.size(), 1);
  arr[0] = 12345;
  EXPECT_EQ(arr[0], 12345);
}

}  // namespace
}  // namespace re2
