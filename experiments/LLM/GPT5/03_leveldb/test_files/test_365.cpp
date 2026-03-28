// File: memtable_iterator_status_test_365.cc

#include "gtest/gtest.h"

// Assume the production build provides these headers / symbols.
// The prompt shows Status API and MemTableIterator with a public status() method.
#include "leveldb/status.h"
#include "db/memtable.cc"  // If there's a header, prefer it; otherwise this ensures the tiny test stub is visible.

namespace {

using leveldb::MemTableIterator;
using leveldb::Status;

// Basic: status() returns OK.
TEST(MemTableIteratorTest_365, StatusReturnsOk_365) {
  MemTableIterator it;  // Using the trivial class from the prompt snippet
  Status s = it.status();
  EXPECT_TRUE(s.ok());
}

// Idempotence: multiple calls yield OK each time.
TEST(MemTableIteratorTest_365, StatusIsIdempotent_365) {
  MemTableIterator it;
  EXPECT_TRUE(it.status().ok());
  EXPECT_TRUE(it.status().ok());
  EXPECT_TRUE(it.status().ok());
}

// Independence: different instances behave the same.
TEST(MemTableIteratorTest_365, MultipleInstancesReturnOk_365) {
  MemTableIterator it1;
  MemTableIterator it2;
  EXPECT_TRUE(it1.status().ok());
  EXPECT_TRUE(it2.status().ok());
}

// Safety: calling status() should not throw.
TEST(MemTableIteratorTest_365, StatusNoThrow_365) {
  MemTableIterator it;
  EXPECT_NO_THROW({
    auto s = it.status();
    (void)s;
  });
}

}  // namespace
