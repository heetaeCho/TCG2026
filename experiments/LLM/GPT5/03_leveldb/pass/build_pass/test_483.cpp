// write_batch_ctor_test_483.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/write_batch.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"

using ::testing::_;
using ::testing::Exactly;
using ::testing::Return;

namespace {

// A mock Handler to verify external interactions through Iterate().
class MockHandler : public leveldb::WriteBatch::Handler {
 public:
  MOCK_METHOD(void, Put, (const leveldb::Slice& key, const leveldb::Slice& value), (override));
  MOCK_METHOD(void, Delete, (const leveldb::Slice& key), (override));
};

class WriteBatchCtorTest_483 : public ::testing::Test {
 protected:
  // Utility to get the initial "empty" size in a black-box manner.
  static size_t InitialSize() {
    leveldb::WriteBatch b;
    return b.ApproximateSize();
  }
};

// Verifies that a default-constructed batch has the same ApproximateSize()
// as a batch that was mutated and then cleared. This confirms constructor
// equivalence to Clear() without peeking into internal state.
TEST_F(WriteBatchCtorTest_483, DefaultConstructedEqualsClearedState_483) {
  const size_t initial = InitialSize();

  leveldb::WriteBatch mutated;
  mutated.Put(leveldb::Slice("k1"), leveldb::Slice("v1"));
  mutated.Put(leveldb::Slice("k2"), leveldb::Slice("v2"));
  mutated.Delete(leveldb::Slice("k1"));

  // Sanity: mutations should change the size in some observable way.
  EXPECT_GT(mutated.ApproximateSize(), initial);

  mutated.Clear();
  EXPECT_EQ(mutated.ApproximateSize(), initial);
}

// Iterating over a freshly constructed (empty) batch should not invoke
// any handler callbacks.
TEST_F(WriteBatchCtorTest_483, IterateOnFreshBatchInvokesNoHandlerMethods_483) {
  leveldb::WriteBatch fresh;

  MockHandler handler;
  EXPECT_CALL(handler, Put(_, _)).Times(Exactly(0));
  EXPECT_CALL(handler, Delete(_)).Times(Exactly(0));

  leveldb::Status s = fresh.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// After mutations, Clear() should restore the same observable size as
// a fresh-constructed batch.
TEST_F(WriteBatchCtorTest_483, ClearAfterMutationsRestoresInitialSize_483) {
  const size_t initial = InitialSize();

  leveldb::WriteBatch b;
  b.Put(leveldb::Slice("a"), leveldb::Slice("1"));
  b.Delete(leveldb::Slice("a"));
  b.Put(leveldb::Slice("b"), leveldb::Slice("2"));
  ASSERT_GT(b.ApproximateSize(), initial);  // sanity

  b.Clear();
  EXPECT_EQ(b.ApproximateSize(), initial);
}

// Appending something non-empty changes size, and a subsequent Clear()
// returns to the initial constructor state.
TEST_F(WriteBatchCtorTest_483, AppendThenClearReturnsToInitialSize_483) {
  const size_t initial = InitialSize();

  leveldb::WriteBatch source;
  source.Put(leveldb::Slice("x"), leveldb::Slice("y"));

  leveldb::WriteBatch target;  // default-constructed
  EXPECT_EQ(target.ApproximateSize(), initial);

  target.Append(source);
  EXPECT_GT(target.ApproximateSize(), initial);

  target.Clear();
  EXPECT_EQ(target.ApproximateSize(), initial);
}

}  // namespace
