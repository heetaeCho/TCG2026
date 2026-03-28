#include "gtest/gtest.h"
#include "re2/pod_array.h"
#include <memory>
#include <cstring>

namespace re2 {

// Test basic construction of PODArray with default constructor
TEST(PODArrayTest_69, DefaultConstruction_69) {
  PODArray<int> arr;
  // Default constructed PODArray should be empty/null
  EXPECT_EQ(arr.data(), nullptr);
}

// Test construction with a specific size
TEST(PODArrayTest_69, SizedConstruction_69) {
  PODArray<int> arr(10);
  EXPECT_NE(arr.data(), nullptr);
}

// Test construction with size 0
TEST(PODArrayTest_69, ZeroSizedConstruction_69) {
  PODArray<int> arr(0);
  // Size 0 allocation - behavior depends on implementation
  // Just ensure no crash
}

// Test construction with size 1
TEST(PODArrayTest_69, SingleElementConstruction_69) {
  PODArray<int> arr(1);
  EXPECT_NE(arr.data(), nullptr);
  arr.data()[0] = 42;
  EXPECT_EQ(arr.data()[0], 42);
}

// Test that we can read and write through data()
TEST(PODArrayTest_69, ReadWriteData_69) {
  PODArray<int> arr(5);
  ASSERT_NE(arr.data(), nullptr);
  for (int i = 0; i < 5; i++) {
    arr.data()[i] = i * 10;
  }
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(arr.data()[i], i * 10);
  }
}

// Test with char type
TEST(PODArrayTest_69, CharType_69) {
  PODArray<char> arr(100);
  ASSERT_NE(arr.data(), nullptr);
  std::memset(arr.data(), 'A', 100);
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(arr.data()[i], 'A');
  }
}

// Test with double type
TEST(PODArrayTest_69, DoubleType_69) {
  PODArray<double> arr(50);
  ASSERT_NE(arr.data(), nullptr);
  for (int i = 0; i < 50; i++) {
    arr.data()[i] = i * 1.5;
  }
  for (int i = 0; i < 50; i++) {
    EXPECT_DOUBLE_EQ(arr.data()[i], i * 1.5);
  }
}

// Test move construction
TEST(PODArrayTest_69, MoveConstruction_69) {
  PODArray<int> arr1(10);
  ASSERT_NE(arr1.data(), nullptr);
  arr1.data()[0] = 123;
  int* original_ptr = arr1.data();

  PODArray<int> arr2(std::move(arr1));
  EXPECT_EQ(arr2.data(), original_ptr);
  EXPECT_EQ(arr2.data()[0], 123);
  EXPECT_EQ(arr1.data(), nullptr);
}

// Test move assignment
TEST(PODArrayTest_69, MoveAssignment_69) {
  PODArray<int> arr1(10);
  ASSERT_NE(arr1.data(), nullptr);
  arr1.data()[0] = 456;
  int* original_ptr = arr1.data();

  PODArray<int> arr2;
  arr2 = std::move(arr1);
  EXPECT_EQ(arr2.data(), original_ptr);
  EXPECT_EQ(arr2.data()[0], 456);
  EXPECT_EQ(arr1.data(), nullptr);
}

// Test large allocation
TEST(PODArrayTest_69, LargeAllocation_69) {
  PODArray<int> arr(100000);
  ASSERT_NE(arr.data(), nullptr);
  arr.data()[0] = 1;
  arr.data()[99999] = 2;
  EXPECT_EQ(arr.data()[0], 1);
  EXPECT_EQ(arr.data()[99999], 2);
}

// Test that destruction doesn't leak (just ensure no crash/ASAN error)
TEST(PODArrayTest_69, DestructionNoLeak_69) {
  {
    PODArray<int> arr(1000);
    ASSERT_NE(arr.data(), nullptr);
    for (int i = 0; i < 1000; i++) {
      arr.data()[i] = i;
    }
  }
  // If we reach here without memory errors, destruction worked
  SUCCEED();
}

// Test move assignment replaces existing allocation
TEST(PODArrayTest_69, MoveAssignmentReplacesExisting_69) {
  PODArray<int> arr1(10);
  PODArray<int> arr2(20);
  arr1.data()[0] = 111;
  arr2.data()[0] = 222;

  int* ptr2 = arr2.data();
  arr1 = std::move(arr2);
  EXPECT_EQ(arr1.data(), ptr2);
  EXPECT_EQ(arr1.data()[0], 222);
  EXPECT_EQ(arr2.data(), nullptr);
}

// Test with unsigned char (byte-like POD)
TEST(PODArrayTest_69, UnsignedCharType_69) {
  PODArray<unsigned char> arr(256);
  ASSERT_NE(arr.data(), nullptr);
  for (int i = 0; i < 256; i++) {
    arr.data()[i] = static_cast<unsigned char>(i);
  }
  for (int i = 0; i < 256; i++) {
    EXPECT_EQ(arr.data()[i], static_cast<unsigned char>(i));
  }
}

// Test Deleter struct directly
TEST(PODArrayDeleterTest_69, DefaultDeleterLen_69) {
  // Default Deleter should have len_ == 0
  typename PODArray<int>::Deleter d;
  // We can't directly access len_, but we can verify it doesn't crash
  // when called with nullptr conceptually (though we shouldn't call with nullptr)
  SUCCEED();
}

// Test Deleter with explicit length
TEST(PODArrayDeleterTest_69, ExplicitDeleterLen_69) {
  int* ptr = std::allocator<int>().allocate(5);
  typename PODArray<int>::Deleter d(5);
  // This should deallocate properly
  d(ptr);
  SUCCEED();
}

}  // namespace re2
