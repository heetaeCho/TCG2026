// File: db/c_writebatch_create_test_244.cc

#include <gtest/gtest.h>

// We only rely on the public interface (signature). If there's a header, include it instead.
// Forward declarations to match the provided partial code.
extern "C" {
  struct leveldb_writebatch_t;
  leveldb_writebatch_t* leveldb_writebatch_create();
}

// A minimal, empty fixture for naming consistency and future extension.
class WriteBatchCreateTest_244 : public ::testing::Test {};

// [Normal] Creating a write batch returns a non-null handle.
TEST_F(WriteBatchCreateTest_244, CreateReturnsNonNull_244) {
  leveldb_writebatch_t* wb = leveldb_writebatch_create();
  ASSERT_NE(wb, nullptr);
  // Note: No destruction API was provided in the prompt; we do not assume one.
}

// [Boundary] Multiple independent creations each return a valid, distinct handle.
TEST_F(WriteBatchCreateTest_244, MultipleCreatesYieldDistinctNonNullHandles_244) {
  leveldb_writebatch_t* wb1 = leveldb_writebatch_create();
  leveldb_writebatch_t* wb2 = leveldb_writebatch_create();

  ASSERT_NE(wb1, nullptr);
  ASSERT_NE(wb2, nullptr);
  EXPECT_NE(wb1, wb2);  // Distinct instances should not alias.
}

// [Robustness] Stress a small batch of creations to ensure all are non-null and distinct.
// This still avoids any assumption about internal behavior beyond the interface.
TEST_F(WriteBatchCreateTest_244, ManyCreatesAreAllNonNullAndDistinct_244) {
  constexpr int kCount = 16;  // Modest number to avoid excessive allocations in a unit test.
  leveldb_writebatch_t* handles[kCount] = {nullptr};

  for (int i = 0; i < kCount; ++i) {
    handles[i] = leveldb_writebatch_create();
    ASSERT_NE(handles[i], nullptr) << "Handle at index " << i << " is null";
  }

  for (int i = 0; i < kCount; ++i) {
    for (int j = i + 1; j < kCount; ++j) {
      EXPECT_NE(handles[i], handles[j]) << "Handles " << i << " and " << j << " alias";
    }
  }
}
