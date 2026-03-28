#include <gtest/gtest.h>
#include "exiv2/slice.hpp"

namespace {

// Test fixture for PtrSliceStorage with int*
class PtrSliceStorageTest_14 : public ::testing::Test {
 protected:
  void SetUp() override {
    for (int i = 0; i < 10; ++i) {
      data_[i] = i * 10;
    }
  }

  int data_[10];
};

// Test that unsafeAt returns the correct element at index 0
TEST_F(PtrSliceStorageTest_14, UnsafeAtReturnsFirstElement_14) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  EXPECT_EQ(storage.unsafeAt(0), 0);
}

// Test that unsafeAt returns correct element at a middle index
TEST_F(PtrSliceStorageTest_14, UnsafeAtReturnsMiddleElement_14) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  EXPECT_EQ(storage.unsafeAt(5), 50);
}

// Test that unsafeAt returns correct element at the last valid index
TEST_F(PtrSliceStorageTest_14, UnsafeAtReturnsLastElement_14) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  EXPECT_EQ(storage.unsafeAt(9), 90);
}

// Test that unsafeAt returns a modifiable reference
TEST_F(PtrSliceStorageTest_14, UnsafeAtReturnsModifiableReference_14) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  storage.unsafeAt(3) = 999;
  EXPECT_EQ(data_[3], 999);
}

// Test that unsafeAt works with non-zero begin parameter (begin/end are unused in storage but passed)
TEST_F(PtrSliceStorageTest_14, ConstructionWithNonZeroBeginEnd_14) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 2, 8);
  // data_ pointer is stored as-is; unsafeAt accesses data_[index] directly
  EXPECT_EQ(storage.unsafeAt(0), 0);
  EXPECT_EQ(storage.unsafeAt(2), 20);
}

// Test that unsafeAt works with consecutive indices
TEST_F(PtrSliceStorageTest_14, UnsafeAtConsecutiveAccess_14) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(storage.unsafeAt(i), i * 10);
  }
}

// Test with const int* storage type
TEST_F(PtrSliceStorageTest_14, ConstPointerStorage_14) {
  const int* const_data = data_;
  Exiv2::Internal::PtrSliceStorage<const int*> storage(const_data, 0, 10);
  EXPECT_EQ(storage.unsafeAt(0), 0);
  EXPECT_EQ(storage.unsafeAt(5), 50);
}

// Test unsafeGetIteratorAt returns pointer to correct element
TEST_F(PtrSliceStorageTest_14, UnsafeGetIteratorAtReturnsCorrectPointer_14) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  auto iter = storage.unsafeGetIteratorAt(0);
  EXPECT_EQ(*iter, 0);
}

// Test unsafeGetIteratorAt at middle index
TEST_F(PtrSliceStorageTest_14, UnsafeGetIteratorAtMiddleIndex_14) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  auto iter = storage.unsafeGetIteratorAt(5);
  EXPECT_EQ(*iter, 50);
}

// Test unsafeGetIteratorAt at last element
TEST_F(PtrSliceStorageTest_14, UnsafeGetIteratorAtLastIndex_14) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  auto iter = storage.unsafeGetIteratorAt(9);
  EXPECT_EQ(*iter, 90);
}

// Test that modifying through iterator from unsafeGetIteratorAt works
TEST_F(PtrSliceStorageTest_14, UnsafeGetIteratorAtAllowsModification_14) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  auto iter = storage.unsafeGetIteratorAt(4);
  *iter = 777;
  EXPECT_EQ(data_[4], 777);
}

// Test with char* data type
TEST(PtrSliceStorageCharTest_14, WorksWithCharPointer_14) {
  char buffer[] = "Hello World";
  Exiv2::Internal::PtrSliceStorage<char*> storage(buffer, 0, 11);
  EXPECT_EQ(storage.unsafeAt(0), 'H');
  EXPECT_EQ(storage.unsafeAt(6), 'W');
}

// Test with unsigned char* data type
TEST(PtrSliceStorageUCharTest_14, WorksWithUnsignedCharPointer_14) {
  unsigned char buffer[5] = {0, 1, 2, 3, 4};
  Exiv2::Internal::PtrSliceStorage<unsigned char*> storage(buffer, 0, 5);
  EXPECT_EQ(storage.unsafeAt(0), 0);
  EXPECT_EQ(storage.unsafeAt(4), 4);
}

// Test that unsafeAt with single element array works
TEST(PtrSliceStorageSingleElementTest_14, SingleElementArray_14) {
  int val = 42;
  Exiv2::Internal::PtrSliceStorage<int*> storage(&val, 0, 1);
  EXPECT_EQ(storage.unsafeAt(0), 42);
}

// Test that modification through unsafeAt reflects in original array
TEST_F(PtrSliceStorageTest_14, ModificationReflectsInOriginal_14) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  for (int i = 0; i < 10; ++i) {
    storage.unsafeAt(i) = i + 100;
  }
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(data_[i], i + 100);
  }
}

// Test noexcept guarantee of unsafeAt
TEST_F(PtrSliceStorageTest_14, UnsafeAtIsNoexcept_14) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  EXPECT_TRUE(noexcept(storage.unsafeAt(0)));
}

// Test noexcept guarantee of unsafeGetIteratorAt
TEST_F(PtrSliceStorageTest_14, UnsafeGetIteratorAtIsNoexcept_14) {
  Exiv2::Internal::PtrSliceStorage<int*> storage(data_, 0, 10);
  EXPECT_TRUE(noexcept(storage.unsafeGetIteratorAt(0)));
}

}  // namespace
