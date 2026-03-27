// VersionSet_tests_481.cc
#include <gtest/gtest.h>
#include "db/version_set.h"
#include "db/dbformat.h"
#include "leveldb/options.h"

namespace {

// Minimal user comparator to satisfy InternalKeyComparator construction.
// We do NOT assert anything about its behavior beyond what's needed to
// instantiate the class under test.
class DummyUserComparator : public leveldb::Comparator {
 public:
  const char* Name() const override { return "dummy"; }
  int Compare(const leveldb::Slice& a, const leveldb::Slice& b) const override {
    // Any deterministic total order is fine for constructing the CUT.
    if (a.size() != b.size()) return (a.size() < b.size()) ? -1 : 1;
    int r = std::memcmp(a.data(), b.data(), a.size());
    return (r < 0) ? -1 : (r > 0 ? 1 : 0);
  }
  void FindShortestSeparator(std::string*, const leveldb::Slice&) const override {}
  void FindShortSuccessor(std::string*) const override {}
};

// Test fixture to centralize common setup.
class VersionSetTest_481 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Options: we only set env non-null to satisfy constructor requirements.
    // We do not depend on any Env behavior in these tests.
    opts_.env = reinterpret_cast<leveldb::Env*>(0x1);

    // Build an InternalKeyComparator from a trivial user comparator.
    ikc_ = std::make_unique<leveldb::InternalKeyComparator>(&user_cmp_);

    // TableCache is not used by the behaviors we test; pass nullptr safely.
    table_cache_ = nullptr;

    vs_ = std::make_unique<leveldb::VersionSet>(
        dbname_, &opts_, table_cache_, ikc_.get());
  }

  std::string dbname_ = "vs_test_db_481";
  leveldb::Options opts_;
  DummyUserComparator user_cmp_;
  std::unique_ptr<leveldb::InternalKeyComparator> ikc_;
  leveldb::TableCache* table_cache_;  // intentionally nullptr
  std::unique_ptr<leveldb::VersionSet> vs_;
};

}  // namespace

// --- Tests ---

// Constructor initializes observable state to known defaults.
TEST_F(VersionSetTest_481, ConstructorInitialState_481) {
  ASSERT_NE(vs_->current(), nullptr) << "current() should be non-null after construction";
  EXPECT_EQ(vs_->ManifestFileNumber(), 0u);
  EXPECT_EQ(vs_->LastSequence(), 0u);
  EXPECT_EQ(vs_->LogNumber(), 0u);
  EXPECT_EQ(vs_->PrevLogNumber(), 0u);
  // We do NOT assert anything about NeedsCompaction() unless clearly defined
  // by the public contract; if it is expected to be false initially, uncomment:
  // EXPECT_FALSE(vs_->NeedsCompaction());
}

// NewFileNumber should start at 2 (per interface-observable behavior) and increment.
TEST_F(VersionSetTest_481, NewFileNumberMonotonicFromTwo_481) {
  uint64_t a = vs_->NewFileNumber();
  uint64_t b = vs_->NewFileNumber();
  uint64_t c = vs_->NewFileNumber();

  EXPECT_EQ(a, 2u) << "First allocated file number should be 2";
  EXPECT_EQ(b, 3u);
  EXPECT_EQ(c, 4u);
  EXPECT_LT(a, b);
  EXPECT_LT(b, c);
}

// ReuseFileNumber should cause the next allocation to return the reused number.
TEST_F(VersionSetTest_481, ReuseFileNumberReturnsReusedValue_481) {
  uint64_t first = vs_->NewFileNumber();  // expect 2
  // Request reuse of the just-allocated number; next call should return it.
  vs_->ReuseFileNumber(first);
  uint64_t reused = vs_->NewFileNumber();
  EXPECT_EQ(reused, first);
}

// MarkFileNumberUsed should advance the next allocation past the given number.
TEST_F(VersionSetTest_481, MarkFileNumberUsedAdvancesNext_481) {
  // Jump the internal counter past a large value via MarkFileNumberUsed.
  vs_->MarkFileNumberUsed(200);
  uint64_t x = vs_->NewFileNumber();
  // Observable contract: the next allocated number should be > 200.
  EXPECT_GE(x, 201u);
}

// LastSequence should be settable and retrievable via the public API.
TEST_F(VersionSetTest_481, SetAndGetLastSequence_481) {
  EXPECT_EQ(vs_->LastSequence(), 0u);
  const uint64_t kSeq = 123456789ull;
  vs_->SetLastSequence(kSeq);
  EXPECT_EQ(vs_->LastSequence(), kSeq);
}

// Log/PrevLog numbers should be 0 initially (observable getters).
TEST_F(VersionSetTest_481, LogNumbersInitialZero_481) {
  EXPECT_EQ(vs_->LogNumber(), 0u);
  EXPECT_EQ(vs_->PrevLogNumber(), 0u);
}

// current() should remain valid after benign operations that do not apply edits.
TEST_F(VersionSetTest_481, CurrentRemainsNonNullAfterSimpleCalls_481) {
  (void)vs_->NewFileNumber();
  (void)vs_->LastSequence();
  EXPECT_NE(vs_->current(), nullptr);
}
