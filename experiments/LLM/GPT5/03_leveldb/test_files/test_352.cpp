// File: table_cache_evict_test_352.cc
#include "db/table_cache.h"
#include "leveldb/cache.h"
#include "leveldb/slice.h"
#include "util/coding.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::InSequence;
using ::testing::NiceMock;

// --- Test double injection point -------------------------------------------
// We override NewLRUCache so TableCache will receive our mock without
// accessing private state or re-implementing TableCache internals.
namespace {
class MockCache : public leveldb::Cache {
public:
  // Only Erase is observed in these tests; other virtuals are unused.
  MOCK_METHOD(void, Erase, (const leveldb::Slice& key), (override));
  ~MockCache() override = default;
};

// Pointer set by the test fixture before constructing TableCache.
static MockCache* g_injected_cache_352 = nullptr;
}  // namespace

namespace leveldb {
Cache* NewLRUCache(int /*entries*/) {
  // Return the test-provided mock. Tests ensure it's set beforehand.
  return g_injected_cache_352;
}
}  // namespace leveldb

// --- Helpful matcher --------------------------------------------------------
MATCHER_P(KeyFor_352, num, "Slice equals fixed64 encoding of the given file number") {
  char buf[sizeof(uint64_t)];
  leveldb::EncodeFixed64(buf, static_cast<uint64_t>(num));
  return arg.size() == sizeof(buf) &&
         ::memcmp(arg.data(), buf, sizeof(buf)) == 0;
}

// --- Fixture ----------------------------------------------------------------
class TableCacheEvictTest_352 : public ::testing::Test {
protected:
  void SetUp() override {
    // Provide a NiceMock to ignore any unrelated virtual calls.
    mock_cache_ = new NiceMock<MockCache>();
    g_injected_cache_352 = mock_cache_;

    // Construct TableCache normally; it will pick up our mock via NewLRUCache.
    leveldb::Options opts;            // Use defaults; env/others are irrelevant here.
    cache_.reset(new leveldb::TableCache("testdb", opts, /*entries=*/16));
  }

  void TearDown() override {
    // TableCache owns and deletes the Cache* it received.
    cache_.reset();
    mock_cache_ = nullptr;
    g_injected_cache_352 = nullptr;
  }

  MockCache* mock_cache_ = nullptr;  // Non-owning; owned by TableCache instance.
  std::unique_ptr<leveldb::TableCache> cache_;
};

// --- Tests ------------------------------------------------------------------

// Normal operation: Evict must call Cache::Erase with the fixed64-encoded key.
TEST_F(TableCacheEvictTest_352, CallsEraseWithEncodedKey_352) {
  const uint64_t file_number = 0x1122334455667788ULL;  // an arbitrary non-boundary value
  EXPECT_CALL(*mock_cache_, Erase(KeyFor_352(file_number))).Times(1);

  cache_->Evict(file_number);
}

// Boundary conditions: verify encoding for 0 and for UINT64_MAX.
TEST_F(TableCacheEvictTest_352, EraseKeyEncodingBoundaries_352) {
  InSequence seq;  // enforce call order just to make expectations precise

  EXPECT_CALL(*mock_cache_, Erase(KeyFor_352(0ULL))).Times(1);
  EXPECT_CALL(*mock_cache_, Erase(KeyFor_352(std::numeric_limits<uint64_t>::max()))).Times(1);

  cache_->Evict(0ULL);
  cache_->Evict(std::numeric_limits<uint64_t>::max());
}
