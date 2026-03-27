// iterator_wrapper_set_test_377.cc
#include "table/iterator_wrapper.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;

namespace leveldb {

// A simple test double that flips a flag when destructed.
// This helps us verify that IteratorWrapper::Set deletes the prior iterator.
class DestructionFlagIterator : public Iterator {
 public:
  explicit DestructionFlagIterator(bool* destroyed_flag,
                                   bool valid = false,
                                   Slice key = Slice(),
                                   Slice value = Slice())
      : destroyed_flag_(destroyed_flag),
        valid_(valid),
        key_(key),
        value_(value) {
    if (destroyed_flag_) *destroyed_flag_ = false;
  }

  ~DestructionFlagIterator() override {
    if (destroyed_flag_) *destroyed_flag_ = true;
  }

  // Minimal observable surface
  bool Valid() const override { return valid_; }
  void SeekToFirst() override {}
  void SeekToLast() override {}
  void Seek(const Slice&) override {}
  void Next() override {}
  void Prev() override {}
  Slice key() const override { return key_; }
  Slice value() const override { return value_; }
  Status status() const override { return Status::OK(); }

  // Helpers to mutate observable state (used by some tests if needed)
  void SetValid(bool v) { valid_ = v; }
  void SetKey(const Slice& k) { key_ = k; }
  void SetValue(const Slice& v) { value_ = v; }

 private:
  bool* destroyed_flag_;
  bool valid_;
  Slice key_;
  Slice value_;
};

// A gMock-based iterator to control return values (observable behavior).
class MockIterator : public Iterator {
 public:
  ~MockIterator() override = default;

  MOCK_METHOD(bool, Valid, (), (const, override));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Seek, (const Slice&), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(Slice, key, (), (const, override));
  MOCK_METHOD(Slice, value, (), (const, override));
  MOCK_METHOD(Status, status, (), (const, override));
};

class IteratorWrapperTest_377 : public ::testing::Test {
protected:
  IteratorWrapper wrapper_;
};

// --- Tests ---

// 1) Setting nullptr should make the wrapper invalid.
TEST_F(IteratorWrapperTest_377, SetNull_MakesInvalid_377) {
  // Start with no iterator; calling Set(nullptr) must keep/force invalid state.
  wrapper_.Set(nullptr);
  EXPECT_FALSE(wrapper_.Valid());
}

// 2) Setting a non-null iterator that reports Valid() == true should result
//    in wrapper.Valid() == true after Set (observable via public API).
TEST_F(IteratorWrapperTest_377, SetNonNull_ReflectsValidTrue_377) {
  auto* it = new MockIterator();
  EXPECT_CALL(*it, Valid()).WillRepeatedly(Return(true));
  // key()/value() may be consulted by Update(); provide safe returns.
  EXPECT_CALL(*it, key()).WillRepeatedly(Return(Slice("k")));
  EXPECT_CALL(*it, value()).WillRepeatedly(Return(Slice("v")));
  EXPECT_CALL(*it, status()).WillRepeatedly(Return(Status::OK()));

  wrapper_.Set(it);
  EXPECT_TRUE(wrapper_.Valid());
  // If IteratorWrapper exposes key()/value() immediately after Set(),
  // they should reflect the underlying iterator's observable state.
  EXPECT_EQ(wrapper_.key().ToString(), "k");
  EXPECT_EQ(wrapper_.value().ToString(), "v");
}

// 3) Setting a non-null iterator that reports Valid() == false should result
//    in wrapper.Valid() == false after Set.
TEST_F(IteratorWrapperTest_377, SetNonNull_ReflectsValidFalse_377) {
  auto* it = new MockIterator();
  EXPECT_CALL(*it, Valid()).WillRepeatedly(Return(false));
  EXPECT_CALL(*it, status()).WillRepeatedly(Return(Status::OK()));
  // key()/value() shouldn't be relied on when invalid, but returning something is harmless.
  EXPECT_CALL(*it, key()).WillRepeatedly(Return(Slice()));
  EXPECT_CALL(*it, value()).WillRepeatedly(Return(Slice()));

  wrapper_.Set(it);
  EXPECT_FALSE(wrapper_.Valid());
}

// 4) Replacing an existing iterator should delete the previous one.
//    We verify by observing the destruction flag flip.
TEST_F(IteratorWrapperTest_377, Set_ReplacesAndDeletesOldIterator_377) {
  bool old_deleted = false;
  // Old iterator (owned by wrapper after Set).
  auto* old_it = new DestructionFlagIterator(&old_deleted, /*valid=*/true, Slice("old"), Slice("v"));
  wrapper_.Set(old_it);
  EXPECT_FALSE(old_deleted) << "Old iterator should not be deleted immediately after first Set";

  // New iterator replacement.
  bool new_deleted = false;
  auto* new_it = new DestructionFlagIterator(&new_deleted, /*valid=*/true, Slice("new"), Slice("v2"));
  wrapper_.Set(new_it);

  // Old must be deleted due to 'delete iter_' at the start of Set().
  EXPECT_TRUE(old_deleted) << "Old iterator was not deleted when replaced";

  // The new iterator is now owned; it should NOT be deleted yet.
  EXPECT_FALSE(new_deleted);
  // And wrapper's observable state should align with the new iterator's state.
  EXPECT_TRUE(wrapper_.Valid());
  EXPECT_EQ(wrapper_.key().ToString(), "new");
}

// 5) Setting nullptr when an iterator is already set should delete the previous iterator
//    and leave the wrapper invalid.
TEST_F(IteratorWrapperTest_377, SetNull_DeletesExistingAndLeavesInvalid_377) {
  bool deleted = false;
  auto* it = new DestructionFlagIterator(&deleted, /*valid=*/true, Slice("k"), Slice("v"));
  wrapper_.Set(it);
  EXPECT_FALSE(deleted);

  // Now clear it via Set(nullptr) — this should delete the existing iterator
  // and make the wrapper invalid.
  wrapper_.Set(nullptr);

  EXPECT_TRUE(deleted) << "Existing iterator should be deleted when Set(nullptr) is called";
  EXPECT_FALSE(wrapper_.Valid());
}

}  // namespace leveldb
