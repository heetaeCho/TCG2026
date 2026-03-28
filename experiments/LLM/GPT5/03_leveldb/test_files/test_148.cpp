// File: version_get_test_148.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/table_cache.h"
#include "db/dbformat.h"
#include "leveldb/options.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

// ---- Mock for TableCache (external collaborator) ----
class MockTableCache_148 : public leveldb::TableCache {
public:
  // We never construct the real base (it needs env/cache/etc); just provide mock vtable.
  MockTableCache_148() : leveldb::TableCache("", *(new leveldb::Options), 1) {}

  // We only mock the methods Version::Get may call.
  MOCK_METHOD(leveldb::Status, Get,
              (const leveldb::ReadOptions&,
               uint64_t /*file_number*/,
               uint64_t /*file_size*/,
               const leveldb::Slice& /*key*/,
               void* /*arg*/,
               void (*handle_result)(void*, const leveldb::Slice&, const leveldb::Slice&)),
              (override));
};

// ---- Minimal user comparator for InternalKeyComparator wiring in VersionSet ----
class BytewiseComparator_148 : public leveldb::Comparator {
public:
  const char* Name() const override { return "test.BytewiseComparator_148"; }
  int Compare(const leveldb::Slice& a, const leveldb::Slice& b) const override {
    const size_t n = std::min(a.size(), b.size());
    int r = std::memcmp(a.data(), b.data(), n);
    if (r == 0) {
      if (a.size() < b.size()) return -1;
      if (a.size() > b.size()) return +1;
    }
    return r;
  }
  void FindShortestSeparator(std::string*, const leveldb::Slice&) const override {}
  void FindShortSuccessor(std::string*) const override {}
};

// ---- Test fixture wiring a Version via VersionSet with an injectable TableCache ----
class VersionGetTest_148 : public ::testing::Test {
protected:
  BytewiseComparator_148 ucmp_;
  leveldb::InternalKeyComparator ikey_cmp_{&ucmp_};
  leveldb::Options options_;
  std::unique_ptr<MockTableCache_148> mock_cache_;
  std::unique_ptr<leveldb::VersionSet> vset_;  // will hold the Version under test

  void SetUp() override {
    // Options minimal wiring; env/cache not used by our mock.
    options_.create_if_missing = true;

    mock_cache_ = std::make_unique<MockTableCache_148>();

    // NOTE: Your codebase must allow constructing VersionSet with our mock TableCache.
    // If ctor takes a TableCache*, pass mock_cache_.get(). If not, provide a seam/factory.
    vset_.reset(new leveldb::VersionSet("testdb_148", &options_, mock_cache_.get(), &ikey_cmp_));

    // In many setups VersionSet::current() becomes valid only after Recover/LogAndApply.
    // If your project requires it, call Recover() or LogAndApply() here with a no-op edit.
    // bool save_manifest = false;
    // ASSERT_TRUE(vset_->Recover(&save_manifest).ok());
  }

  // Helper to get a Version* under test.
  leveldb::Version* CurrentVersion() {
    return vset_->current();
  }
};

// --- Test cases ---

// Normal operation: returns NotFound if no table reports a match and the iterator/callback never
// sets a value (i.e., TableCache::Get returns ok but doesn't invoke handle_result).
TEST_F(VersionGetTest_148, NotFoundWhenNoMatchingEntry_148) {
  using namespace leveldb;

  // Arrange: TableCache::Get returns OK but never calls the handle_result callback.
  EXPECT_CALL(*mock_cache_, Get(_, _, _, _, _, _))
      .WillOnce(Return(Status::OK()));

  // Act
  ReadOptions ro;
  std::string value_out;
  Version::GetStats stats;  // seek_file=nullptr, level=-1 are expected defaults
  LookupKey lk(Slice("userkey"), /*sequence*/ 1);

  // NOTE: We assume CurrentVersion() is valid in your harness.
  Status s = CurrentVersion()->Get(ro, lk, &value_out, &stats);

  // Assert
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_TRUE(value_out.empty());
  EXPECT_EQ(nullptr, stats.seek_file);
  EXPECT_EQ(-1, stats.seek_file_level);
}

// Error propagation: if TableCache::Get returns a non-ok Status (e.g., IOError),
// Version::Get must return that Status (found=true, early exit path).
TEST_F(VersionGetTest_148, ReturnsErrorStatusOnTableCacheFailure_148) {
  using namespace leveldb;

  EXPECT_CALL(*mock_cache_, Get(_, _, _, _, _, _))
      .WillOnce(Return(Status::IOError(Slice("boom"))));

  ReadOptions ro;
  std::string value_out;
  Version::GetStats stats;
  LookupKey lk(Slice("k"), 1);

  Status s = CurrentVersion()->Get(ro, lk, &value_out, &stats);

  EXPECT_TRUE(s.IsIOError());
  EXPECT_TRUE(value_out.empty());
}

// Found path: when TableCache::Get returns ok AND invokes the provided SaveValue callback,
// Version::Get must return OK and populate the value.
TEST_F(VersionGetTest_148, ReturnsValueOnFound_148) {
  using namespace leveldb;

  // We simulate a table hit by *invoking the provided handle_result* once with
  // (user_key, value). We do not rely on SaveValue’s internal logic beyond its
  // documented observable: when provided with a matching key/value pair, it sets
  // the Saver state so that Version::Get treats it as found.
  EXPECT_CALL(*mock_cache_, Get(_, _, _, _, _, _))
      .WillOnce(Invoke([](const ReadOptions&,
                          uint64_t, uint64_t,
                          const Slice& lookup_internal_key,
                          void* arg,
                          void (*handle_result)(void*, const Slice&, const Slice&)) -> Status {
        // Derive a plausible user key from the LookupKey. We avoid inspecting internals:
        // Instead, we supply the *same* user key as the caller constructed.
        // In LevelDB’s contract, TableCache passes the user key to handle_result.
        const Slice user_key("userkey");
        const Slice value("val148");
        handle_result(arg, user_key, value);
        return Status::OK();
      }));

  ReadOptions ro;
  std::string value_out;
  Version::GetStats stats;
  LookupKey lk(Slice("userkey"), 1);

  Status s = CurrentVersion()->Get(ro, lk, &value_out, &stats);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ("val148", value_out);
}

// Boundary-ish behavior: If the first TableCache::Get call is OK but yields no match,
// and there are no further overlapping files, Version::Get should end with NotFound
// without mutating stats (seek_file stays nullptr, level -1).
TEST_F(VersionGetTest_148, StatsRemainDefaultWhenSingleProbeNoHit_148) {
  using namespace leveldb;

  EXPECT_CALL(*mock_cache_, Get(_, _, _, _, _, _))
      .WillOnce(Return(Status::OK()));

  ReadOptions ro;
  std::string value_out;
  Version::GetStats stats;
  LookupKey lk(Slice("zzz"), 7);

  Status s = CurrentVersion()->Get(ro, lk, &value_out, &stats);

  EXPECT_TRUE(s.IsNotFound());
  EXPECT_EQ(nullptr, stats.seek_file);
  EXPECT_EQ(-1, stats.seek_file_level);
}
