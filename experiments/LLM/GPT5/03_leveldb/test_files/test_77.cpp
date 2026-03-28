// File: versionset_prevlognumber_test_77.cc

#include "db/version_set.h"
#include "db/dbformat.h"            // InternalKeyComparator
#include "leveldb/options.h"        // Options
#include "leveldb/env.h"            // Env
#include "leveldb/comparator.h"     // BytewiseComparator
#include "gtest/gtest.h"

namespace leveldb {

class VersionSetTest_77 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_.env = Env::Default();
    icmp_ = std::make_unique<InternalKeyComparator>(BytewiseComparator());
    // Passing nullptr for TableCache* is safe here because we only call PrevLogNumber()
    vs_ = std::make_unique<VersionSet>("testdb", &options_, /*table_cache=*/nullptr, icmp_.get());
  }

  Options options_;
  std::unique_ptr<InternalKeyComparator> icmp_;
  std::unique_ptr<VersionSet> vs_;
};

// [Normal] Default constructed value should be zero.
TEST_F(VersionSetTest_77, DefaultIsZero_77) {
  EXPECT_EQ(static_cast<uint64_t>(0), vs_->PrevLogNumber());
}

// [Behavior] Multiple calls should be stable/idempotent.
TEST_F(VersionSetTest_77, StableAcrossCalls_77) {
  uint64_t first = vs_->PrevLogNumber();
  uint64_t second = vs_->PrevLogNumber();
  EXPECT_EQ(first, second);
}

// [Isolation] Unrelated operations should not affect PrevLogNumber().
// We exercise a couple of safe, unrelated public methods without relying on any internal behavior.
TEST_F(VersionSetTest_77, UnrelatedOpsDoNotChangePrevLogNumber_77) {
  const uint64_t before = vs_->PrevLogNumber();

  // Exercise methods that do not (by interface contract) mention prev log number.
  // We avoid any assumptions about their internal logic.
  vs_->MarkFileNumberUsed(123);
  (void)vs_->NewFileNumber();  // obtain but ignore result

  const uint64_t after = vs_->PrevLogNumber();
  EXPECT_EQ(before, after);
}

}  // namespace leveldb
