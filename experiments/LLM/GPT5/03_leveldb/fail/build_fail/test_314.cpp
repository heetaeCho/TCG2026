// db_impl_getproperty_test_314.cc
#include <gtest/gtest.h>
#include <string>
#include "db/db_impl.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "leveldb/cache.h"

using namespace leveldb;

namespace {

// Minimal cache stub to control TotalCharge() for the memory-usage property.
class FixedChargeCache : public Cache {
 public:
  explicit FixedChargeCache(size_t charge) : charge_(charge) {}
  ~FixedChargeCache() override = default;

  // Only the method used by GetProperty needs definition.
  const size_t TotalCharge() override { return charge_; }

  // Stub out the rest to satisfy the abstract interface.
  Handle* Insert(const Slice&, void*, size_t, void (*)(const Slice&, void*)) override { return nullptr; }
  Handle* Lookup(const Slice&) override { return nullptr; }
  void Release(Handle*) override {}
  void* Value(Handle*) override { return nullptr; }
  void Erase(const Slice&) override {}
  uint64_t NewId() override { return 0; }
  void Prune() override {}

 private:
  size_t charge_;
};

// Simple fixture that constructs a DBImpl with controllable Options.
class DBImplGetPropertyTest_314 : public ::testing::Test {
 protected:
  // Helper to create a DBImpl with a provided Cache (so we can control memory usage).
  std::unique_ptr<DBImpl> MakeDBWithCache(Cache* cache) {
    Options opt;
    opt.create_if_missing = true; // typical default in tests; does not affect GetProperty
    opt.block_cache = cache;      // critical so GetProperty can call TotalCharge()
    // Use an arbitrary dbname; no filesystem assertions are made in these tests.
    return std::unique_ptr{new DBImpl(opt, "testdb_314")};
  }
};

} // namespace

// 1) Property must start with "leveldb." prefix
TEST_F(DBImplGetPropertyTest_314, ReturnsFalseWithoutPrefix_314) {
  auto db = MakeDBWithCache(new FixedChargeCache(0));
  std::string out = "pre-filled";
  const bool ok = db->GetProperty(Slice("num-files-at-level0"), &out);
  EXPECT_FALSE(ok);
  // The method clears *value at entry; for false return it should remain cleared.
  EXPECT_TRUE(out.empty());
}

// 2) num-files-at-level: invalid (non-numeric) level
TEST_F(DBImplGetPropertyTest_314, NumFilesAtLevel_NonNumeric_314) {
  auto db = MakeDBWithCache(new FixedChargeCache(0));
  std::string out;
  const bool ok = db->GetProperty(Slice("leveldb.num-files-at-levelX"), &out);
  EXPECT_FALSE(ok);
  EXPECT_TRUE(out.empty());
}

// 3) num-files-at-level: out-of-range level (>= kNumLevels)
TEST_F(DBImplGetPropertyTest_314, NumFilesAtLevel_LevelTooHigh_314) {
  auto db = MakeDBWithCache(new FixedChargeCache(0));
  std::string out;
  // kNumLevels == 7 → valid levels are 0..6; use 7 to trigger false.
  const bool ok = db->GetProperty(Slice("leveldb.num-files-at-level7"), &out);
  EXPECT_FALSE(ok);
  EXPECT_TRUE(out.empty());
}

// 4) num-files-at-level: valid level returns a decimal string (observable format)
TEST_F(DBImplGetPropertyTest_314, NumFilesAtLevel_ValidLevel_314) {
  auto db = MakeDBWithCache(new FixedChargeCache(0));
  std::string out;
  const bool ok = db->GetProperty(Slice("leveldb.num-files-at-level0"), &out);
  EXPECT_TRUE(ok);
  // We don't assume the internal count; just that it's formatted as a non-negative integer.
  EXPECT_FALSE(out.empty());
  // Simple numeric check: all chars are digits.
  EXPECT_TRUE(std::all_of(out.begin(), out.end(), ::isdigit));
}

// 5) stats: always includes the header block; per-level lines are conditional, so only assert header presence
TEST_F(DBImplGetPropertyTest_314, Stats_HeaderPresent_314) {
  auto db = MakeDBWithCache(new FixedChargeCache(0));
  std::string out;
  const bool ok = db->GetProperty(Slice("leveldb.stats"), &out);
  EXPECT_TRUE(ok);
  // The header is fixed per interface/format.
  EXPECT_NE(out.find(" Compactions\n"), std::string::npos);
  EXPECT_NE(out.find("Level Files Size(MB) Time(sec) Read(MB) Write(MB)\n"), std::string::npos);
  EXPECT_NE(out.find("--------------------------------------------------\n"), std::string::npos);
}

// 6) sstables: returns true; content is implementation-defined (may be empty), so only assert success
TEST_F(DBImplGetPropertyTest_314, Sstables_ReturnsTrue_314) {
  auto db = MakeDBWithCache(new FixedChargeCache(0));
  std::string out;
  const bool ok = db->GetProperty(Slice("leveldb.sstables"), &out);
  EXPECT_TRUE(ok);
  // No further assumptions about content.
}

// 7) approximate-memory-usage: uses cache+memtables; with no memtables and a fixed cache, it should match the cache charge
TEST_F(DBImplGetPropertyTest_314, ApproximateMemoryUsage_FromCacheOnly_314) {
  const size_t kCharge = 12345;
  auto db = MakeDBWithCache(new FixedChargeCache(kCharge));
  std::string out;
  const bool ok = db->GetProperty(Slice("leveldb.approximate-memory-usage"), &out);
  EXPECT_TRUE(ok);
  EXPECT_EQ(out, std::to_string(kCharge));
}
