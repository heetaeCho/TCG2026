// UnrefEntry_test_348.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/cache.h"

// Include the implementation unit so the internal-linkage function
// `leveldb::UnrefEntry` is visible in this translation unit.
#include "db/table_cache.cc"

namespace leveldb {

// A strict mock to ensure only the expected interaction(s) occur.
class MockCache : public Cache {
 public:
  MOCK_METHOD(Handle*, Insert,
              (const Slice& key, void* value, size_t charge,
               void (*deleter)(const Slice&, void*)),
              (override));
  MOCK_METHOD(Handle*, Lookup, (const Slice& key), (override));
  MOCK_METHOD(void, Release, (Handle* handle), (override));
  MOCK_METHOD(void*, Value, (Handle* handle), (override));
  MOCK_METHOD(void, Erase, (const Slice& key), (override));
  MOCK_METHOD(uint64_t, NewId, (), (override));
  MOCK_METHOD(const size_t, TotalCharge, (), (override));
  MOCK_METHOD(void, Prune, (), (override));

  // Ensure a virtual destructor is available.
  ~MockCache() override = default;
};

// Test fixture (empty for now, reserved for future extensions)
class UnrefEntryTest_348 : public ::testing::Test {};

TEST_F(UnrefEntryTest_348, CallsReleaseWithHandle_348) {
  StrictMock<MockCache> cache;

  // Any non-null opaque pointer value works; it is never dereferenced.
  Cache::Handle* handle = reinterpret_cast<Cache::Handle*>(0x1);

  EXPECT_CALL(cache, Release(handle)).Times(1);

  // Act: UnrefEntry should forward to Cache::Release(handle).
  UnrefEntry(static_cast<void*>(&cache), static_cast<void*>(handle));
}

TEST_F(UnrefEntryTest_348, CallsReleaseWithNullHandle_348) {
  StrictMock<MockCache> cache;

  // Expect Release to be invoked even if the handle is null.
  EXPECT_CALL(cache, Release(nullptr)).Times(1);

  UnrefEntry(static_cast<void*>(&cache), /*arg2=*/nullptr);
}

}  // namespace leveldb
