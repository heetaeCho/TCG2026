// File: memtable_approx_memory_usage_test_354.cc

#include <gtest/gtest.h>
#include "db/memtable.h"
#include "db/dbformat.h"          // InternalKeyComparator
#include "util/comparator.h"      // BytewiseComparator
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {

class MemTableTest_354 : public ::testing::Test {
protected:
  InternalKeyComparator icmp_;
  MemTable* mem_;
  SequenceNumber seq_;

  MemTableTest_354()
      : icmp_(BytewiseComparator()), mem_(nullptr), seq_(1) {}

  void SetUp() override {
    mem_ = new MemTable(icmp_);
    // MemTable uses manual ref-counting.
    mem_->Ref();
  }

  void TearDown() override {
    mem_->Unref();
    mem_ = nullptr;
  }

  void AddKV(const std::string& key,
             const std::string& value,
             ValueType type = kTypeValue) {
    mem_->Add(seq_++, type, Slice(key), Slice(value));
  }
};

// -- Tests --

// 1) Calling ApproximateMemoryUsage without changes should be non-decreasing.
TEST_F(MemTableTest_354, ApproximateMemoryUsage_NonDecreasing_354) {
  const size_t u1 = mem_->ApproximateMemoryUsage();
  const size_t u2 = mem_->ApproximateMemoryUsage();
  EXPECT_LE(u1, u2) << "Memory usage must not decrease without mutations";
}

// 2) Adding even a small entry should not decrease reported memory usage.
TEST_F(MemTableTest_354, ApproximateMemoryUsage_IncreasesAfterAddSmall_354) {
  const size_t before = mem_->ApproximateMemoryUsage();
  AddKV("a", "1");
  const size_t after = mem_->ApproximateMemoryUsage();
  EXPECT_GE(after, before) << "Adding an entry must not reduce memory usage";
  EXPECT_GT(after, before) << "Adding an entry should typically increase usage";
}

// 3) Adding a large value should cause a noticeable increase (strictly >).
TEST_F(MemTableTest_354, ApproximateMemoryUsage_IncreasesAfterAddLarge_354) {
  const size_t before = mem_->ApproximateMemoryUsage();
  std::string large(1 << 20, 'x'); // ~1 MiB payload (size exactness not assumed)
  AddKV("big-key", large);
  const size_t after = mem_->ApproximateMemoryUsage();
  EXPECT_GT(after, before)
      << "Adding a large value should increase memory usage";
}

// 4) Multiple additions should make usage monotonic non-decreasing.
TEST_F(MemTableTest_354, ApproximateMemoryUsage_MultipleAddsMonotonic_354) {
  size_t u_prev = mem_->ApproximateMemoryUsage();

  AddKV("k1", "v1");
  size_t u1 = mem_->ApproximateMemoryUsage();
  EXPECT_GE(u1, u_prev);
  u_prev = u1;

  AddKV("k2", "value-2");
  size_t u2 = mem_->ApproximateMemoryUsage();
  EXPECT_GE(u2, u_prev);
  u_prev = u2;

  AddKV("k3", std::string(8192, 'y')); // reasonably bigger value
  size_t u3 = mem_->ApproximateMemoryUsage();
  EXPECT_GE(u3, u_prev);
}

// 5) Adding an entry with an empty value should not decrease usage.
TEST_F(MemTableTest_354, ApproximateMemoryUsage_AddEmptyValue_DoesNotDecrease_354) {
  const size_t before = mem_->ApproximateMemoryUsage();
  AddKV("empty-value", "");
  const size_t after = mem_->ApproximateMemoryUsage();
  EXPECT_GE(after, before)
      << "Adding an entry (even empty value) must not reduce usage";
}

// 6) Stress: many small entries lead to growth vs. initial.
TEST_F(MemTableTest_354, ApproximateMemoryUsage_AddManyEntries_Grows_354) {
  const size_t initial = mem_->ApproximateMemoryUsage();

  for (int i = 0; i < 1000; ++i) {
    AddKV("k" + std::to_string(i), "v");
  }

  const size_t final_usage = mem_->ApproximateMemoryUsage();
  EXPECT_GT(final_usage, initial)
      << "Adding many entries should increase memory usage overall";
}

}  // namespace leveldb
