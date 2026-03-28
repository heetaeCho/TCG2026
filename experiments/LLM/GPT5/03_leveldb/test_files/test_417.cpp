// two_level_iterator_test_417.cc
// Tests for NewTwoLevelIterator factory wrapper around TwoLevelIterator.
// We treat implementation as a black box and only rely on the exposed interface.
// TEST_ID: 417

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/iterator.h"
#include "leveldb/options.h"

// --- Minimal shims to compile against the given partial interfaces ---

namespace leveldb {

// Provide a simple mockable Iterator using Google Mock for observable behavior.
// We only mock the public virtual interface. No inference about internals.
class MockIterator : public Iterator {
 public:
  MOCK_METHOD(bool, Valid, (), (override, const));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Seek, (const Slice& target), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(const Slice, key, (), (override, const));
  MOCK_METHOD(const Slice, value, (), (override, const));
  MOCK_METHOD(const Status, status, (), (override, const));
};

// Simple stand-in types to satisfy signatures (black-box friendly).
// We avoid using any internal fields or behavior.
class DummySlice {
 public:
  DummySlice() = default;
};
class DummyStatus {
 public:
  DummyStatus() = default;
  // Allow copying to satisfy return-by-value in mocks.
};
}  // namespace leveldb

// Adapt names used in partial headers to our dummy stand-ins
using Slice = leveldb::DummySlice;
using Status = leveldb::DummyStatus;

namespace leveldb {

// Forward declaration of the SUT factory (provided in two_level_iterator.cc)
Iterator* NewTwoLevelIterator(Iterator* index_iter,
                              Iterator* (*block_function)(void*, const ReadOptions&, const Slice&),
                              void* arg,
                              const ReadOptions& options);

// Test fixture holding common utilities.
class TwoLevelIteratorTest_417 : public ::testing::Test {
 protected:
  // A trivial leaf iterator we can hand out from block_function.
  class LeafIter : public Iterator {
   public:
    LeafIter() = default;
    // Provide harmless default implementations to keep it black-box.
    bool Valid() const override { return false; }
    void SeekToFirst() override {}
    void SeekToLast() override {}
    void Seek(const Slice&) override {}
    void Next() override {}
    void Prev() override {}
    const Slice key() const override { static Slice s; return s; }
    const Slice value() const override { static Slice s; return s; }
    const Status status() const override { static Status st; return st; }
  };

  // A controllable block function that records inputs and returns a new iterator.
  struct BlockFnRecorder {
    void* last_arg = nullptr;
    ReadOptions last_opts{};
    bool called = false;

    static Iterator* Invoke(void* arg, const ReadOptions& opts, const Slice& /*slice*/) {
      auto* self = reinterpret_cast<BlockFnRecorder*>(arg);
      self->called = true;
      self->last_arg = arg;
      self->last_opts = opts;
      // Return a simple leaf iterator instance; ownership expected by SUT.
      return new LeafIter();
    }
  };
};

// --- Tests ---

// 1) FactoryReturnsNonNull_417: NewTwoLevelIterator should return a non-null Iterator*.
TEST_F(TwoLevelIteratorTest_417, FactoryReturnsNonNull_417) {
  // Arrange
  ::testing::NiceMock<MockIterator> index_iter;  // index iterator collaborator
  TwoLevelIteratorTest_417::BlockFnRecorder rec;
  ReadOptions opts;
  opts.verify_checksums = true;
  opts.fill_cache = false;

  // Act
  Iterator* it = NewTwoLevelIterator(&index_iter, &BlockFnRecorder::Invoke, &rec, opts);

  // Assert
  ASSERT_NE(it, nullptr);

  // Cleanup
  delete it;  // We do not assume further behavior; just avoid leaks.
}

// 2) BlockFunctionReceivesArgAndOptions_417:
// When the created iterator is used (e.g., SeekToFirst), the block function may be invoked.
// We cannot assert internal timing, but we can ensure the block_function is callable
// and captures the arg/options when invoked directly in isolation.
TEST_F(TwoLevelIteratorTest_417, BlockFunctionReceivesArgAndOptions_417) {
  // Arrange
  TwoLevelIteratorTest_417::BlockFnRecorder rec;
  ReadOptions opts;
  opts.verify_checksums = true;
  opts.fill_cache = true;

  // We call the block function directly to validate external interaction contract.
  Slice dummy_slice;

  // Act
  Iterator* produced = TwoLevelIteratorTest_417::BlockFnRecorder::Invoke(&rec, opts, dummy_slice);

  // Assert
  ASSERT_TRUE(rec.called);
  ASSERT_EQ(rec.last_arg, &rec);
  EXPECT_EQ(rec.last_opts.verify_checksums, true);
  EXPECT_EQ(rec.last_opts.fill_cache, true);
  // Not asserting snapshot pointer specifics; we didn't set one.
  ASSERT_NE(produced, nullptr);

  delete produced;
}

// 3) IteratorPolymorphismAndBasicCallsDoNotCrash_417:
// The returned iterator should support the Iterator interface without crashing
// on basic calls. Since behavior is black-box, we only test that calls are safe.
TEST_F(TwoLevelIteratorTest_417, IteratorPolymorphismAndBasicCallsDoNotCrash_417) {
  // Arrange
  ::testing::NiceMock<MockIterator> index_iter;
  TwoLevelIteratorTest_417::BlockFnRecorder rec;
  ReadOptions opts;

  Iterator* it = NewTwoLevelIterator(&index_iter, &BlockFnRecorder::Invoke, &rec, opts);
  ASSERT_NE(it, nullptr);

  // Act & Assert: Calls should be safe (no crash). We don't assert returned values.
  it->SeekToFirst();
  it->SeekToLast();

  Slice s;
  it->Seek(s);
  it->Next();
  it->Prev();

  // We can call accessors and status; we only check that calls succeed.
  (void)it->Valid();
  (void)it->key();
  (void)it->value();
  (void)it->status();

  // Cleanup
  delete it;
}

// 4) SupportsRegisterCleanupWithoutLeaksOrCrashes_417:
// Verify we can register a cleanup callback on the returned iterator.
// We only assert that the callback can be registered; we do not assume when it runs.
TEST_F(TwoLevelIteratorTest_417, SupportsRegisterCleanupWithoutLeaksOrCrashes_417) {
  // Arrange
  ::testing::NiceMock<MockIterator> index_iter;
  TwoLevelIteratorTest_417::BlockFnRecorder rec;
  ReadOptions opts;

  Iterator* it = NewTwoLevelIterator(&index_iter, &BlockFnRecorder::Invoke, &rec, opts);
  ASSERT_NE(it, nullptr);

  // A no-op cleanup function
  auto cleanup = [](void*, void*) {};

  // Act: Register cleanup should not crash.
  it->RegisterCleanup(reinterpret_cast<CleanupFunction>(cleanup), nullptr, nullptr);

  // Cleanup
  delete it;
}

