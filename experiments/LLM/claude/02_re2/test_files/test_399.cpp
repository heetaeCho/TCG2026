#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/sparse_set.h"

namespace re2 {

// We need to access the AddToQueue function. Since it's defined as static inline
// in prog.cc, we need to either include it or redefine the test around observable behavior.
// Based on the interface, we test through SparseSet (Workq) behavior.

// Helper: reproduce the AddToQueue logic as it's static inline in the translation unit
// We test the observable behavior through the Workq (SparseSet) interface.
static inline void AddToQueue(SparseSet* q, int id) {
  if (id != 0) q->insert(id);
}

class AddToQueueTest_399 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Default queue with reasonable size
    q_ = new SparseSet(100);
  }

  void TearDown() override {
    delete q_;
  }

  SparseSet* q_;
};

// Test that adding a non-zero id inserts it into the queue
TEST_F(AddToQueueTest_399, NonZeroIdIsInserted_399) {
  AddToQueue(q_, 5);
  EXPECT_TRUE(q_->contains(5));
  EXPECT_EQ(q_->size(), 1);
}

// Test that adding id 0 does NOT insert into the queue
TEST_F(AddToQueueTest_399, ZeroIdIsNotInserted_399) {
  AddToQueue(q_, 0);
  EXPECT_FALSE(q_->contains(0));
  EXPECT_EQ(q_->size(), 0);
}

// Test adding multiple distinct non-zero ids
TEST_F(AddToQueueTest_399, MultipleNonZeroIdsInserted_399) {
  AddToQueue(q_, 1);
  AddToQueue(q_, 2);
  AddToQueue(q_, 3);
  EXPECT_TRUE(q_->contains(1));
  EXPECT_TRUE(q_->contains(2));
  EXPECT_TRUE(q_->contains(3));
  EXPECT_EQ(q_->size(), 3);
}

// Test that adding the same non-zero id multiple times doesn't duplicate
TEST_F(AddToQueueTest_399, DuplicateNonZeroIdNotDuplicated_399) {
  AddToQueue(q_, 7);
  AddToQueue(q_, 7);
  EXPECT_TRUE(q_->contains(7));
  EXPECT_EQ(q_->size(), 1);
}

// Test adding id 1 (boundary near zero)
TEST_F(AddToQueueTest_399, IdOneIsInserted_399) {
  AddToQueue(q_, 1);
  EXPECT_TRUE(q_->contains(1));
  EXPECT_EQ(q_->size(), 1);
}

// Test that queue is initially empty
TEST_F(AddToQueueTest_399, QueueInitiallyEmpty_399) {
  EXPECT_EQ(q_->size(), 0);
  EXPECT_TRUE(q_->empty());
}

// Test adding id at boundary of max_size - 1
TEST_F(AddToQueueTest_399, BoundaryMaxSizeMinusOne_399) {
  AddToQueue(q_, 99);  // max_size is 100, so valid range is 0..99
  EXPECT_TRUE(q_->contains(99));
  EXPECT_EQ(q_->size(), 1);
}

// Test mixing zero and non-zero additions
TEST_F(AddToQueueTest_399, MixedZeroAndNonZero_399) {
  AddToQueue(q_, 0);
  AddToQueue(q_, 10);
  AddToQueue(q_, 0);
  AddToQueue(q_, 20);
  EXPECT_FALSE(q_->contains(0));
  EXPECT_TRUE(q_->contains(10));
  EXPECT_TRUE(q_->contains(20));
  EXPECT_EQ(q_->size(), 2);
}

// Test that after clear, previously added items are gone
TEST_F(AddToQueueTest_399, ClearRemovesAllEntries_399) {
  AddToQueue(q_, 5);
  AddToQueue(q_, 10);
  EXPECT_EQ(q_->size(), 2);
  q_->clear();
  EXPECT_EQ(q_->size(), 0);
  EXPECT_FALSE(q_->contains(5));
  EXPECT_FALSE(q_->contains(10));
}

// Test adding after clear works correctly
TEST_F(AddToQueueTest_399, AddAfterClear_399) {
  AddToQueue(q_, 5);
  q_->clear();
  AddToQueue(q_, 5);
  EXPECT_TRUE(q_->contains(5));
  EXPECT_EQ(q_->size(), 1);
}

// Test with a small queue size
TEST_F(AddToQueueTest_399, SmallQueueSize_399) {
  SparseSet small_q(2);
  AddToQueue(&small_q, 1);
  EXPECT_TRUE(small_q.contains(1));
  EXPECT_EQ(small_q.size(), 1);
}

// Test adding many elements
TEST_F(AddToQueueTest_399, ManyElements_399) {
  for (int i = 1; i < 100; i++) {
    AddToQueue(q_, i);
  }
  EXPECT_EQ(q_->size(), 99);
  for (int i = 1; i < 100; i++) {
    EXPECT_TRUE(q_->contains(i));
  }
  EXPECT_FALSE(q_->contains(0));
}

// Test that iterators reflect inserted elements
TEST_F(AddToQueueTest_399, IteratorsReflectInsertedElements_399) {
  AddToQueue(q_, 3);
  AddToQueue(q_, 7);
  
  int count = 0;
  for (auto it = q_->begin(); it != q_->end(); ++it) {
    count++;
    EXPECT_TRUE(*it == 3 || *it == 7);
  }
  EXPECT_EQ(count, 2);
}

// Test empty() returns true for empty queue, false after insertion
TEST_F(AddToQueueTest_399, EmptyReflectsState_399) {
  EXPECT_TRUE(q_->empty());
  AddToQueue(q_, 42);
  EXPECT_FALSE(q_->empty());
}

}  // namespace re2
