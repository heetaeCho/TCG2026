// iterator_wrapper_destructor_test_375.cc
#include <gtest/gtest.h>

//
// Minimal collaborator stub to allow deletion through base pointer.
// We model only what's needed for black-box verification of destruction.
//
namespace leveldb {
class Iterator {
 public:
  virtual ~Iterator() = default;
};
}  // namespace leveldb

#include "table/iterator_wrapper.h"  // uses leveldb::IteratorWrapper

#include <atomic>

namespace leveldb {

// A test double whose destructor bumps a counter so we can observe deletion.
class TrackingIterator : public Iterator {
 public:
  TrackingIterator() { /* no-op */ }
  ~TrackingIterator() override { ++destruct_count_; }

  static void Reset() { destruct_count_.store(0); }
  static int Destructions() { return destruct_count_.load(); }

 private:
  static std::atomic<int> destruct_count_;
};

std::atomic<int> TrackingIterator::destruct_count_{0};

}  // namespace leveldb

using leveldb::IteratorWrapper;
using leveldb::TrackingIterator;

class IteratorWrapperTest_375 : public ::testing::Test {
 protected:
  void SetUp() override { TrackingIterator::Reset(); }
};

// Verifies that when the wrapper goes out of scope, it deletes the iterator it owns.
TEST_F(IteratorWrapperTest_375, DestructorDeletesOwnedIterator_375) {
  {
    IteratorWrapper w;                 // Construct with no iterator (per interface)
    w.Set(new TrackingIterator());     // Hand in ownership via the public interface
    // No further assumptions; we just let 'w' be destroyed at scope exit.
  }
  EXPECT_EQ(1, TrackingIterator::Destructions());
}

// Verifies that destroying a default-constructed wrapper (with nullptr iterator)
// does not attempt an invalid delete (i.e., no crash / undefined behavior).
TEST_F(IteratorWrapperTest_375, DestructorHandlesNullIteratorSafely_375) {
  {
    IteratorWrapper w;  // Default-constructed; no iterator set
    // Scope exit triggers ~IteratorWrapper(); test passes if no crash occurs.
  }
  SUCCEED();  // Explicitly mark that reaching here means the behavior is safe.
}
