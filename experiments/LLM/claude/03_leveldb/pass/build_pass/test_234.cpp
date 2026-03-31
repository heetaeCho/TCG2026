#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Forward declarations and necessary includes
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

// Replicate the C API struct as defined in the known dependencies
struct leveldb_iterator_t {
  leveldb::Iterator* rep;
};

// Declare the C function under test
extern "C" {
void leveldb_iter_destroy(leveldb_iterator_t* iter);
}

// A mock iterator to track whether delete is called on the rep
class MockIterator : public leveldb::Iterator {
 public:
  MOCK_METHOD(bool, Valid, (), (const, override));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Seek, (const leveldb::Slice& target), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(leveldb::Slice, key, (), (const, override));
  MOCK_METHOD(leveldb::Slice, value, (), (const, override));
  MOCK_METHOD(leveldb::Status, status, (), (const, override));
};

// We use a flag to detect if the destructor of Iterator rep is invoked
// Since we can't directly mock delete, we use a custom approach
namespace {
bool g_iterator_destroyed = false;

class TrackableIterator : public leveldb::Iterator {
 public:
  ~TrackableIterator() override { g_iterator_destroyed = true; }
  bool Valid() const override { return false; }
  void SeekToFirst() override {}
  void SeekToLast() override {}
  void Seek(const leveldb::Slice& target) override {}
  void Next() override {}
  void Prev() override {}
  leveldb::Slice key() const override { return leveldb::Slice(); }
  leveldb::Slice value() const override { return leveldb::Slice(); }
  leveldb::Status status() const override { return leveldb::Status::OK(); }
};
}  // namespace

class LevelDBIterDestroyTest_234 : public ::testing::Test {
 protected:
  void SetUp() override { g_iterator_destroyed = false; }
};

// Test that leveldb_iter_destroy deletes the underlying Iterator (rep)
TEST_F(LevelDBIterDestroyTest_234, DestroysRepIterator_234) {
  g_iterator_destroyed = false;
  auto* iter = new leveldb_iterator_t;
  iter->rep = new TrackableIterator();

  ASSERT_FALSE(g_iterator_destroyed);
  leveldb_iter_destroy(iter);
  EXPECT_TRUE(g_iterator_destroyed);
  // Note: iter itself is also deleted by leveldb_iter_destroy, so no need to free it.
}

// Test that leveldb_iter_destroy works with a valid iterator that has been used
TEST_F(LevelDBIterDestroyTest_234, DestroysAfterUsage_234) {
  g_iterator_destroyed = false;
  auto* trackable = new TrackableIterator();
  auto* iter = new leveldb_iterator_t;
  iter->rep = trackable;

  // Simulate some usage before destroy
  iter->rep->SeekToFirst();
  iter->rep->Valid();

  ASSERT_FALSE(g_iterator_destroyed);
  leveldb_iter_destroy(iter);
  EXPECT_TRUE(g_iterator_destroyed);
}

// Test that leveldb_iter_destroy properly handles the struct and rep being heap-allocated
TEST_F(LevelDBIterDestroyTest_234, NoDoubleFreeOrCrash_234) {
  // This test mainly verifies no crash occurs during normal destruction
  auto* iter = new leveldb_iterator_t;
  iter->rep = new TrackableIterator();

  // Should not crash
  EXPECT_NO_FATAL_FAILURE(leveldb_iter_destroy(iter));
}

// Test with a freshly created iterator (no operations performed)
TEST_F(LevelDBIterDestroyTest_234, DestroyFreshIterator_234) {
  g_iterator_destroyed = false;
  auto* iter = new leveldb_iterator_t;
  iter->rep = new TrackableIterator();

  leveldb_iter_destroy(iter);
  EXPECT_TRUE(g_iterator_destroyed);
}
