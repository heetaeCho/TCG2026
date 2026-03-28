// File: memtable_ref_test_103.cc
#include "gtest/gtest.h"

#include "db/memtable.h"
#include "db/dbformat.h"
#include "leveldb/comparator.h"

using namespace leveldb;

class MemTableRefTest_103 : public ::testing::Test {
protected:
  InternalKeyComparator ikc_;
  MemTable* mem_;

  MemTableRefTest_103() : ikc_(BytewiseComparator()) {}

  void SetUp() override {
    // Construct a MemTable with a valid comparator.
    mem_ = new MemTable(ikc_);
  }

  void TearDown() override {
    // Intentionally avoid calling Unref()/delete here:
    // the ownership / lifetime semantics are internal to MemTable
    // and must not be asserted by these tests.
  }
};

// [Normal] Single call to Ref is allowed and must not throw.
TEST_F(MemTableRefTest_103, SingleRef_DoesNotThrow_103) {
  EXPECT_NO_THROW(mem_->Ref());
}

// [Boundary] Multiple calls to Ref should be safe and must not throw.
TEST_F(MemTableRefTest_103, MultipleRef_DoesNotThrow_103) {
  // Call Ref() many times to simulate heavy aliasing.
  for (int i = 0; i < 1000; ++i) {
    EXPECT_NO_THROW(mem_->Ref());
  }
}

// [Normal] Creating an iterator before and after Ref() should both be valid.
// This checks that Ref() does not invalidate other public operations.
TEST_F(MemTableRefTest_103, NewIterator_UsableBeforeAndAfterRef_103) {
  // Before Ref()
  std::unique_ptr<Iterator> it_before(mem_->NewIterator());
  ASSERT_NE(it_before.get(), nullptr);

  // After Ref()
  mem_->Ref();
  std::unique_ptr<Iterator> it_after(mem_->NewIterator());
  ASSERT_NE(it_after.get(), nullptr);
}

// [Boundary] Ref interleaved with other benign public calls should not throw.
TEST_F(MemTableRefTest_103, InterleavedRef_WithApproximateMemoryUsage_103) {
  // A few interleaved calls — we only assert they are callable without error.
  EXPECT_NO_THROW((void)mem_->ApproximateMemoryUsage());
  EXPECT_NO_THROW(mem_->Ref());
  EXPECT_NO_THROW((void)mem_->ApproximateMemoryUsage());
  EXPECT_NO_THROW(mem_->Ref());
}
