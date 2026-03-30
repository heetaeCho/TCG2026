// File: add_to_queue_test_399.cc
#include <gtest/gtest.h>

#include "re2/sparse_set.h"
// Pull in the real static inline AddToQueue definition.
#include "re2/prog.cc"

namespace {

using re2::AddToQueue;
using re2::Workq;

class AddToQueueTest_399 : public ::testing::Test {
protected:
  Workq q_;
  void SetUp() override {
    // Ensure capacity comfortably covers tested IDs.
    q_.resize(128);
  }
};

// Normal operation: non-zero id should be inserted.
TEST_F(AddToQueueTest_399, InsertsNonZero_399) {
  EXPECT_EQ(q_.size(), 0);
  AddToQueue(&q_, 5);
  EXPECT_TRUE(q_.contains(5));
  EXPECT_EQ(q_.size(), 1);
}

// Boundary condition: zero is explicitly ignored by the interface.
TEST_F(AddToQueueTest_399, IgnoresZero_399) {
  EXPECT_EQ(q_.size(), 0);
  AddToQueue(&q_, 0);
  EXPECT_FALSE(q_.contains(0));
  EXPECT_EQ(q_.size(), 0);
}

// Idempotence with the same non-zero id: verify no observable duplicate effect.
TEST_F(AddToQueueTest_399, DuplicateNonZeroDoesNotIncreaseSize_399) {
  AddToQueue(&q_, 42);
  ASSERT_TRUE(q_.contains(42));
  const int size_after_first = q_.size();

  AddToQueue(&q_, 42);
  EXPECT_TRUE(q_.contains(42));
  EXPECT_EQ(q_.size(), size_after_first);
}

// Multiple distinct non-zero ids are all present; zero is ignored.
TEST_F(AddToQueueTest_399, InsertsMultipleDistinctIds_399) {
  const int ids[] = {1, 2, 3, 4, 5, 0, 6};
  for (int id : ids) {
    AddToQueue(&q_, id);
  }

  for (int id : {1, 2, 3, 4, 5, 6}) {
    EXPECT_TRUE(q_.contains(id)) << "missing id " << id;
  }
  EXPECT_EQ(q_.size(), 6);  // zero was ignored
}

// Boundary within capacity: highest valid index after a smaller resize works.
TEST_F(AddToQueueTest_399, InsertsHighBoundaryWithinCapacity_399) {
  q_.clear();
  q_.resize(64);
  AddToQueue(&q_, 63);  // top end of capacity
  EXPECT_TRUE(q_.contains(63));
  EXPECT_EQ(q_.size(), 1);
}

}  // namespace
