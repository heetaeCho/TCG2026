#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <cassert>
#include <string>

// Include the header under test
#include "exiv2/slice.hpp"

// Test fixture for ContainerStorage with vector
class ContainerStorageVectorTest_13 : public ::testing::Test {
 protected:
  void SetUp() override {
    vec = {10, 20, 30, 40, 50};
  }

  std::vector<int> vec;
};

// Test fixture for ContainerStorage with list
class ContainerStorageListTest_13 : public ::testing::Test {
 protected:
  void SetUp() override {
    lst = {100, 200, 300, 400, 500};
  }

  std::list<int> lst;
};

// ============================================================
// Tests for unsafeGetIteratorAt with vector
// ============================================================

TEST_F(ContainerStorageVectorTest_13, UnsafeGetIteratorAtBeginning_13) {
  Exiv2::Internal::ContainerStorage<std::vector<int>> storage(vec, 0, vec.size());
  auto it = storage.unsafeGetIteratorAt(0);
  EXPECT_EQ(*it, 10);
}

TEST_F(ContainerStorageVectorTest_13, UnsafeGetIteratorAtMiddle_13) {
  Exiv2::Internal::ContainerStorage<std::vector<int>> storage(vec, 0, vec.size());
  auto it = storage.unsafeGetIteratorAt(2);
  EXPECT_EQ(*it, 30);
}

TEST_F(ContainerStorageVectorTest_13, UnsafeGetIteratorAtLastElement_13) {
  Exiv2::Internal::ContainerStorage<std::vector<int>> storage(vec, 0, vec.size());
  auto it = storage.unsafeGetIteratorAt(4);
  EXPECT_EQ(*it, 50);
}

TEST_F(ContainerStorageVectorTest_13, UnsafeGetIteratorAtEnd_13) {
  // Index == size should return end iterator (past-the-end), which is valid but not dereferenceable
  Exiv2::Internal::ContainerStorage<std::vector<int>> storage(vec, 0, vec.size());
  auto it = storage.unsafeGetIteratorAt(vec.size());
  EXPECT_EQ(it, vec.end());
}

TEST_F(ContainerStorageVectorTest_13, UnsafeGetIteratorAtIndex1_13) {
  Exiv2::Internal::ContainerStorage<std::vector<int>> storage(vec, 0, vec.size());
  auto it = storage.unsafeGetIteratorAt(1);
  EXPECT_EQ(*it, 20);
}

TEST_F(ContainerStorageVectorTest_13, UnsafeGetIteratorAtModifyThroughIterator_13) {
  Exiv2::Internal::ContainerStorage<std::vector<int>> storage(vec, 0, vec.size());
  auto it = storage.unsafeGetIteratorAt(2);
  *it = 999;
  EXPECT_EQ(vec[2], 999);
}

TEST_F(ContainerStorageVectorTest_13, UnsafeGetIteratorAtConsistentWithBegin_13) {
  Exiv2::Internal::ContainerStorage<std::vector<int>> storage(vec, 0, vec.size());
  auto it0 = storage.unsafeGetIteratorAt(0);
  EXPECT_EQ(it0, vec.begin());
}

// ============================================================
// Tests for unsafeAt with vector
// ============================================================

TEST_F(ContainerStorageVectorTest_13, UnsafeAtFirstElement_13) {
  Exiv2::Internal::ContainerStorage<std::vector<int>> storage(vec, 0, vec.size());
  EXPECT_EQ(storage.unsafeAt(0), 10);
}

TEST_F(ContainerStorageVectorTest_13, UnsafeAtMiddleElement_13) {
  Exiv2::Internal::ContainerStorage<std::vector<int>> storage(vec, 0, vec.size());
  EXPECT_EQ(storage.unsafeAt(2), 30);
}

TEST_F(ContainerStorageVectorTest_13, UnsafeAtLastElement_13) {
  Exiv2::Internal::ContainerStorage<std::vector<int>> storage(vec, 0, vec.size());
  EXPECT_EQ(storage.unsafeAt(4), 50);
}

TEST_F(ContainerStorageVectorTest_13, UnsafeAtReturnsConstRef_13) {
  Exiv2::Internal::ContainerStorage<std::vector<int>> storage(vec, 0, vec.size());
  const auto& val = storage.unsafeAt(0);
  EXPECT_EQ(val, 10);
  // Modify original and check reference is still connected
  vec[0] = 77;
  EXPECT_EQ(val, 77);
}

// ============================================================
// Tests for ContainerStorage with list
// ============================================================

TEST_F(ContainerStorageListTest_13, UnsafeGetIteratorAtBeginningList_13) {
  Exiv2::Internal::ContainerStorage<std::list<int>> storage(lst, 0, lst.size());
  auto it = storage.unsafeGetIteratorAt(0);
  EXPECT_EQ(*it, 100);
}

TEST_F(ContainerStorageListTest_13, UnsafeGetIteratorAtMiddleList_13) {
  Exiv2::Internal::ContainerStorage<std::list<int>> storage(lst, 0, lst.size());
  auto it = storage.unsafeGetIteratorAt(2);
  EXPECT_EQ(*it, 300);
}

TEST_F(ContainerStorageListTest_13, UnsafeGetIteratorAtEndList_13) {
  Exiv2::Internal::ContainerStorage<std::list<int>> storage(lst, 0, lst.size());
  auto it = storage.unsafeGetIteratorAt(lst.size());
  EXPECT_EQ(it, lst.end());
}

// ============================================================
// Tests for constructor and data_ reference
// ============================================================

TEST_F(ContainerStorageVectorTest_13, ConstructorStoresReference_13) {
  Exiv2::Internal::ContainerStorage<std::vector<int>> storage(vec, 0, vec.size());
  // Verify that storage references the same data
  EXPECT_EQ(&storage.data_, &vec);
}

TEST_F(ContainerStorageVectorTest_13, ConstructorWithPartialRange_13) {
  // Constructor accepts begin and end parameters
  Exiv2::Internal::ContainerStorage<std::vector<int>> storage(vec, 1, 3);
  // data_ still references the full container
  EXPECT_EQ(&storage.data_, &vec);
}

// ============================================================
// Tests with empty container
// ============================================================

TEST(ContainerStorageEmptyTest_13, EmptyVectorGetIteratorAtEnd_13) {
  std::vector<int> empty_vec;
  Exiv2::Internal::ContainerStorage<std::vector<int>> storage(empty_vec, 0, 0);
  auto it = storage.unsafeGetIteratorAt(0);
  EXPECT_EQ(it, empty_vec.end());
}

// ============================================================
// Tests with single element container
// ============================================================

TEST(ContainerStorageSingleElementTest_13, SingleElementUnsafeAt_13) {
  std::vector<int> single = {42};
  Exiv2::Internal::ContainerStorage<std::vector<int>> storage(single, 0, single.size());
  EXPECT_EQ(storage.unsafeAt(0), 42);
}

TEST(ContainerStorageSingleElementTest_13, SingleElementIteratorAtZero_13) {
  std::vector<int> single = {42};
  Exiv2::Internal::ContainerStorage<std::vector<int>> storage(single, 0, single.size());
  auto it = storage.unsafeGetIteratorAt(0);
  EXPECT_EQ(*it, 42);
}

TEST(ContainerStorageSingleElementTest_13, SingleElementIteratorAtEnd_13) {
  std::vector<int> single = {42};
  Exiv2::Internal::ContainerStorage<std::vector<int>> storage(single, 0, single.size());
  auto it = storage.unsafeGetIteratorAt(1);
  EXPECT_EQ(it, single.end());
}

// ============================================================
// Tests with string container
// ============================================================

TEST(ContainerStorageStringVectorTest_13, StringVectorUnsafeAt_13) {
  std::vector<std::string> strs = {"hello", "world", "test"};
  Exiv2::Internal::ContainerStorage<std::vector<std::string>> storage(strs, 0, strs.size());
  EXPECT_EQ(storage.unsafeAt(0), "hello");
  EXPECT_EQ(storage.unsafeAt(1), "world");
  EXPECT_EQ(storage.unsafeAt(2), "test");
}

TEST(ContainerStorageStringVectorTest_13, StringVectorIterator_13) {
  std::vector<std::string> strs = {"hello", "world", "test"};
  Exiv2::Internal::ContainerStorage<std::vector<std::string>> storage(strs, 0, strs.size());
  auto it = storage.unsafeGetIteratorAt(1);
  EXPECT_EQ(*it, "world");
}

// ============================================================
// Tests verifying iterator advancement correctness
// ============================================================

TEST_F(ContainerStorageVectorTest_13, IteratorSequentialAccess_13) {
  Exiv2::Internal::ContainerStorage<std::vector<int>> storage(vec, 0, vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    auto it = storage.unsafeGetIteratorAt(i);
    EXPECT_EQ(*it, vec[i]) << "Mismatch at index " << i;
  }
}

TEST_F(ContainerStorageVectorTest_13, UnsafeAtSequentialAccess_13) {
  Exiv2::Internal::ContainerStorage<std::vector<int>> storage(vec, 0, vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(storage.unsafeAt(i), vec[i]) << "Mismatch at index " << i;
  }
}
