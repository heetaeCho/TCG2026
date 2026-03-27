// iterator_wrapper_key_test_379.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "table/iterator_wrapper.h"   // SUT
#include "leveldb/iterator.h"         // Collaborator interface
#include "leveldb/slice.h"
#include "leveldb/status.h"

using ::testing::Return;
using ::testing::StrictMock;

namespace leveldb {

// ---- Mock for the external collaborator: leveldb::Iterator ----
class MockIterator : public Iterator {
 public:
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

}  // namespace leveldb

namespace {

using leveldb::IteratorWrapper;
using leveldb::MockIterator;
using leveldb::Slice;
using leveldb::Status;

// --------------------------- Tests -----------------------------

// key() must crash (assert) if the wrapper is not valid.
TEST(IteratorWrapperTest_379, KeyOnInvalidDies_379) {
  IteratorWrapper w;  // default-constructed: invalid by interface contract
  ASSERT_DEATH({ (void)w.key(); }, "");  // Any assert() failure pattern
}

// After Set() with a valid underlying iterator, key() returns the
// same bytes as the collaborator's key() (observable behavior).
TEST(IteratorWrapperTest_379, SetPropagatesKeyWhenValid_379) {
  StrictMock<MockIterator> it;

  EXPECT_CALL(it, Valid()).WillOnce(Return(true));
  EXPECT_CALL(it, key()).WillOnce(Return(Slice("k1")));

  IteratorWrapper w;
  w.Set(&it);

  ASSERT_TRUE(w.Valid());                       // observable
  EXPECT_EQ("k1", w.key().ToString());          // observable
}

// Next() should refresh the observable key when the collaborator advances
// to a new valid position.
TEST(IteratorWrapperTest_379, NextUpdatesKeyWhenStillValid_379) {
  StrictMock<MockIterator> it;

  // Initial Set() -> valid at "a"
  EXPECT_CALL(it, Valid()).WillOnce(Return(true));
  EXPECT_CALL(it, key()).WillOnce(Return(Slice("a")));

  IteratorWrapper w;
  w.Set(&it);
  ASSERT_TRUE(w.Valid());
  EXPECT_EQ("a", w.key().ToString());

  // After Next(): collaborator remains valid and exposes "b"
  EXPECT_CALL(it, Next());
  EXPECT_CALL(it, Valid()).WillOnce(Return(true));
  EXPECT_CALL(it, key()).WillOnce(Return(Slice("b")));

  w.Next();
  ASSERT_TRUE(w.Valid());
  EXPECT_EQ("b", w.key().ToString());
}

// If the collaborator becomes invalid after movement, wrapper becomes invalid,
// and key() must crash (assert).
TEST(IteratorWrapperTest_379, BecomesInvalidThenKeyDies_379) {
  StrictMock<MockIterator> it;

  // Set() -> valid at "x"
  EXPECT_CALL(it, Valid()).WillOnce(Return(true));
  EXPECT_CALL(it, key()).WillOnce(Return(Slice("x")));

  IteratorWrapper w;
  w.Set(&it);
  ASSERT_TRUE(w.Valid());
  EXPECT_EQ("x", w.key().ToString());

  // Move and become invalid
  EXPECT_CALL(it, Next());
  EXPECT_CALL(it, Valid()).WillOnce(Return(false));

  w.Next();
  ASSERT_FALSE(w.Valid());
  ASSERT_DEATH({ (void)w.key(); }, "");
}

// Seek-based navigation should update the observable key when valid.
TEST(IteratorWrapperTest_379, SeekPathsUpdateKey_379) {
  StrictMock<MockIterator> it;

  // Attach an iterator that starts invalid; Set should consult Valid() once.
  EXPECT_CALL(it, Valid()).WillOnce(Return(false));

  IteratorWrapper w;
  w.Set(&it);
  ASSERT_FALSE(w.Valid());

  // SeekToFirst -> valid at "first"
  EXPECT_CALL(it, SeekToFirst());
  EXPECT_CALL(it, Valid()).WillOnce(Return(true));
  EXPECT_CALL(it, key()).WillOnce(Return(Slice("first")));
  w.SeekToFirst();
  ASSERT_TRUE(w.Valid());
  EXPECT_EQ("first", w.key().ToString());

  // Seek to an internal key -> valid at "kX"
  EXPECT_CALL(it, Seek(Slice("kX")));
  EXPECT_CALL(it, Valid()).WillOnce(Return(true));
  EXPECT_CALL(it, key()).WillOnce(Return(Slice("kX")));
  w.Seek(Slice("kX"));
  ASSERT_TRUE(w.Valid());
  EXPECT_EQ("kX", w.key().ToString());

  // SeekToLast -> valid at "last"
  EXPECT_CALL(it, SeekToLast());
  EXPECT_CALL(it, Valid()).WillOnce(Return(true));
  EXPECT_CALL(it, key()).WillOnce(Return(Slice("last")));
  w.SeekToLast();
  ASSERT_TRUE(w.Valid());
  EXPECT_EQ("last", w.key().ToString());
}

}  // namespace
