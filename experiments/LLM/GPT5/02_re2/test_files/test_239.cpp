// File: empty_group_names_test_239.cc

#include <gtest/gtest.h>
#include <map>
#include <string>

// Include the implementation unit so we can access the internal static inline symbol.
// This follows the constraint of testing observable behavior only.
#include "re2/re2/re2.cc"

class EmptyGroupNamesTest_239 : public ::testing::Test {
protected:
  void SetUp() override {
    map_ptr_ = re2::empty_group_names();
    original_ = *map_ptr_;  // snapshot to restore later
  }

  void TearDown() override {
    // Restore original contents to avoid cross-test interference.
    *map_ptr_ = original_;
  }

  std::map<int, std::string>* map_ptr_{nullptr};
  std::map<int, std::string> original_;
};

// ---- Tests ----

TEST_F(EmptyGroupNamesTest_239, ReturnsNonNull_239) {
  ASSERT_NE(map_ptr_, nullptr);
}

TEST_F(EmptyGroupNamesTest_239, InitiallyEmptyOrAsProvided_239) {
  // Observable state: whatever the current contents are, we can observe them.
  // If this is truly an "empty" storage map, it should be empty; if not, we
  // at least assert it is in a valid state (no crash & size observable).
  // Prefer a strict expectation of emptiness to validate the contract.
  EXPECT_TRUE(map_ptr_->empty());
}

TEST_F(EmptyGroupNamesTest_239, SameAddressAcrossCalls_239) {
  auto* again = re2::empty_group_names();
  EXPECT_EQ(map_ptr_, again);
}

TEST_F(EmptyGroupNamesTest_239, InsertAndRetrieve_239) {
  // Normal operation: inserting and reading through the returned map pointer.
  const size_t start_size = map_ptr_->size();

  auto inserted = map_ptr_->insert({{1, "one"}});
  EXPECT_TRUE(inserted.second);         // key 1 was not present before
  EXPECT_EQ(map_ptr_->size(), start_size + 1);
  EXPECT_EQ(map_ptr_->at(1), "one");    // observable retrieval
}

TEST_F(EmptyGroupNamesTest_239, UpdateExistingKey_239) {
  // Boundary-ish behavior: updating an existing key's value.
  (*map_ptr_)[1] = "first";
  EXPECT_EQ(map_ptr_->at(1), "first");

  (*map_ptr_)[1] = "updated";
  EXPECT_EQ(map_ptr_->at(1), "updated");
}

TEST_F(EmptyGroupNamesTest_239, ModificationsPersistAcrossCalls_239) {
  // External interaction verification: changes via one call are visible via another.
  (*map_ptr_)[2] = "two";

  auto* again = re2::empty_group_names();
  ASSERT_EQ(map_ptr_, again);           // same object
  EXPECT_EQ(again->at(2), "two");       // persisted observation
}

TEST_F(EmptyGroupNamesTest_239, MultipleInsertions_239) {
  const size_t start_size = map_ptr_->size();

  map_ptr_->insert({{3, "three"}, {4, "four"}});
  EXPECT_EQ(map_ptr_->size(), start_size + 2);

  auto it3 = map_ptr_->find(3);
  auto it4 = map_ptr_->find(4);
  ASSERT_NE(it3, map_ptr_->end());
  ASSERT_NE(it4, map_ptr_->end());
  EXPECT_EQ(it3->second, "three");
  EXPECT_EQ(it4->second, "four");
}
