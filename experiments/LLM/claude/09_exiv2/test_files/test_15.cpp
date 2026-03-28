#include <gtest/gtest.h>
#include "exiv2/slice.hpp"

namespace {

// Test fixture for PtrSliceStorage with int pointers
class PtrSliceStorageTest_15 : public ::testing::Test {
 protected:
  void SetUp() override {
    for (int i = 0; i < 10; ++i) {
      data_[i] = i * 10;
    }
  }

  int data_[10];
};

// Test that unsafeGetIteratorAt returns a pointer to the correct element at index 0
TEST_F(PtrSliceStorageTest_15, UnsafeGetIteratorAtZero_15) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  auto it = storage.unsafeGetIteratorAt(0);
  EXPECT_EQ(it, data_);
  EXPECT_EQ(*it, 0);
}

// Test that unsafeGetIteratorAt returns a pointer to the correct element at a middle index
TEST_F(PtrSliceStorageTest_15, UnsafeGetIteratorAtMiddle_15) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  auto it = storage.unsafeGetIteratorAt(5);
  EXPECT_EQ(it, data_ + 5);
  EXPECT_EQ(*it, 50);
}

// Test that unsafeGetIteratorAt returns a pointer to the last valid element
TEST_F(PtrSliceStorageTest_15, UnsafeGetIteratorAtLastElement_15) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  auto it = storage.unsafeGetIteratorAt(9);
  EXPECT_EQ(it, data_ + 9);
  EXPECT_EQ(*it, 90);
}

// Test that unsafeGetIteratorAt returns the one-past-end pointer
TEST_F(PtrSliceStorageTest_15, UnsafeGetIteratorAtOnePastEnd_15) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  auto it = storage.unsafeGetIteratorAt(10);
  EXPECT_EQ(it, data_ + 10);
}

// Test unsafeAt returns the correct element by reference at index 0
TEST_F(PtrSliceStorageTest_15, UnsafeAtZero_15) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  auto& val = storage.unsafeAt(0);
  EXPECT_EQ(val, 0);
}

// Test unsafeAt returns the correct element by reference at a middle index
TEST_F(PtrSliceStorageTest_15, UnsafeAtMiddle_15) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  auto& val = storage.unsafeAt(5);
  EXPECT_EQ(val, 50);
}

// Test unsafeAt returns a mutable reference - modifications affect underlying data
TEST_F(PtrSliceStorageTest_15, UnsafeAtModifiesUnderlyingData_15) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  storage.unsafeAt(3) = 999;
  EXPECT_EQ(data_[3], 999);
}

// Test that unsafeGetIteratorAt with different indices produces correct pointer arithmetic
TEST_F(PtrSliceStorageTest_15, UnsafeGetIteratorAtConsecutive_15) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  for (size_t i = 0; i < 10; ++i) {
    auto it = storage.unsafeGetIteratorAt(i);
    EXPECT_EQ(it, data_ + i);
    EXPECT_EQ(*it, static_cast<int>(i * 10));
  }
}

// Test with const pointer storage
TEST_F(PtrSliceStorageTest_15, ConstPointerStorage_15) {
  const int* const_data = data_;
  Exiv2::Internal::PtrSliceStorage<const int*> storage(const_data, 0, 10);
  auto it = storage.unsafeGetIteratorAt(3);
  EXPECT_EQ(*it, 30);
}

// Test unsafeAt with const pointer returns correct value
TEST_F(PtrSliceStorageTest_15, ConstPointerUnsafeAt_15) {
  const int* const_data = data_;
  Exiv2::Internal::PtrSliceStorage<const int*> storage(const_data, 0, 10);
  const auto& val = storage.unsafeAt(7);
  EXPECT_EQ(val, 70);
}

// Test that the begin and end parameters in constructor don't affect data_ pointer
TEST_F(PtrSliceStorageTest_15, ConstructorBeginEndDoNotAffectData_15) {
  Exiv2::Internal::PtrSliceStorage<int*> storage1(data_, 0, 10);
  Exiv2::Internal::PtrSliceStorage<int*> storage2(data_, 2, 8);
  // Both should point to the same base data pointer
  EXPECT_EQ(storage1.unsafeGetIteratorAt(0), storage2.unsafeGetIteratorAt(0));
}

// Test with char pointer
TEST(PtrSliceStorageCharTest_15, CharPointer_15) {
  char str[] = "Hello";
  Exiv2::Internal::PtrSliceStorage<char*> storage(str, 0, 5);
  EXPECT_EQ(*storage.unsafeGetIteratorAt(0), 'H');
  EXPECT_EQ(*storage.unsafeGetIteratorAt(4), 'o');
  EXPECT_EQ(storage.unsafeAt(1), 'e');
}

// Test iterator difference between two positions
TEST_F(PtrSliceStorageTest_15, IteratorDifference_15) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  auto begin = storage.unsafeGetIteratorAt(0);
  auto end = storage.unsafeGetIteratorAt(10);
  EXPECT_EQ(end - begin, 10);
}

// Test with unsigned char pointer (common in image processing)
TEST(PtrSliceStorageUCharTest_15, UnsignedCharPointer_15) {
  unsigned char bytes[] = {0x00, 0xFF, 0x80, 0x40};
  Exiv2::Internal::PtrSliceStorage<unsigned char*> storage(bytes, 0, 4);
  EXPECT_EQ(storage.unsafeAt(0), 0x00);
  EXPECT_EQ(storage.unsafeAt(1), 0xFF);
  EXPECT_EQ(storage.unsafeAt(2), 0x80);
  EXPECT_EQ(storage.unsafeAt(3), 0x40);
}

}  // namespace
