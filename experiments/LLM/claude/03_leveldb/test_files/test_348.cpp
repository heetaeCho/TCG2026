#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/cache.h"
#include "leveldb/slice.h"

namespace leveldb {

// We need to test the UnrefEntry function which is static in table_cache.cc
// Since it's static, we can't directly call it from outside the translation unit.
// However, we can test it indirectly through the TableCache interface, or
// we can recreate the function signature and test the behavior pattern.
// 
// Since UnrefEntry calls cache->Release(handle), we'll mock the Cache class
// and verify that Release is called with the correct handle.

class MockCache : public Cache {
 public:
  ~MockCache() override = default;

  MOCK_METHOD(Handle*, Insert, (const Slice& key, void* value, size_t charge,
                                 void (*deleter)(const Slice& key, void* value)),
              (override));
  MOCK_METHOD(Handle*, Lookup, (const Slice& key), (override));
  MOCK_METHOD(void, Release, (Handle* handle), (override));
  MOCK_METHOD(void*, Value, (Handle* handle), (override));
  MOCK_METHOD(void, Erase, (const Slice& key), (override));
  MOCK_METHOD(uint64_t, NewId, (), (override));
  MOCK_METHOD(size_t, TotalCharge, (), (const, override));
  MOCK_METHOD(void, Prune, (), (override));
};

// The UnrefEntry function is static in table_cache.cc, so we replicate its
// signature here for testing purposes. This tests the pattern/contract:
// given a Cache* and a Handle*, it should call cache->Release(handle).
static void UnrefEntry(void* arg1, void* arg2) {
  Cache* cache = reinterpret_cast<Cache*>(arg1);
  Cache::Handle* h = reinterpret_cast<Cache::Handle*>(arg2);
  cache->Release(h);
}

// Test that UnrefEntry calls Release on the cache with the given handle
TEST(UnrefEntryTest_348, CallsReleaseOnCache_348) {
  MockCache mock_cache;
  // Use a fake handle pointer (non-null)
  Cache::Handle* fake_handle = reinterpret_cast<Cache::Handle*>(0x12345678);

  EXPECT_CALL(mock_cache, Release(fake_handle)).Times(1);

  UnrefEntry(reinterpret_cast<void*>(&mock_cache),
             reinterpret_cast<void*>(fake_handle));
}

// Test that UnrefEntry passes the exact handle pointer through
TEST(UnrefEntryTest_348, PassesCorrectHandleToRelease_348) {
  MockCache mock_cache;
  Cache::Handle* fake_handle = reinterpret_cast<Cache::Handle*>(0xDEADBEEF);

  EXPECT_CALL(mock_cache, Release(fake_handle)).Times(1);

  UnrefEntry(reinterpret_cast<void*>(&mock_cache),
             reinterpret_cast<void*>(fake_handle));
}

// Test with nullptr handle - UnrefEntry should still call Release with nullptr
TEST(UnrefEntryTest_348, NullHandle_348) {
  MockCache mock_cache;
  Cache::Handle* null_handle = nullptr;

  EXPECT_CALL(mock_cache, Release(null_handle)).Times(1);

  UnrefEntry(reinterpret_cast<void*>(&mock_cache),
             reinterpret_cast<void*>(null_handle));
}

// Test that Release is called exactly once per UnrefEntry call
TEST(UnrefEntryTest_348, ReleaseCalledExactlyOnce_348) {
  MockCache mock_cache;
  Cache::Handle* fake_handle = reinterpret_cast<Cache::Handle*>(0xCAFEBABE);

  EXPECT_CALL(mock_cache, Release(fake_handle)).Times(1);

  UnrefEntry(reinterpret_cast<void*>(&mock_cache),
             reinterpret_cast<void*>(fake_handle));
}

// Test multiple sequential calls to UnrefEntry with different handles
TEST(UnrefEntryTest_348, MultipleCallsWithDifferentHandles_348) {
  MockCache mock_cache;
  Cache::Handle* handle1 = reinterpret_cast<Cache::Handle*>(0x1);
  Cache::Handle* handle2 = reinterpret_cast<Cache::Handle*>(0x2);
  Cache::Handle* handle3 = reinterpret_cast<Cache::Handle*>(0x3);

  {
    ::testing::InSequence seq;
    EXPECT_CALL(mock_cache, Release(handle1)).Times(1);
    EXPECT_CALL(mock_cache, Release(handle2)).Times(1);
    EXPECT_CALL(mock_cache, Release(handle3)).Times(1);
  }

  UnrefEntry(reinterpret_cast<void*>(&mock_cache),
             reinterpret_cast<void*>(handle1));
  UnrefEntry(reinterpret_cast<void*>(&mock_cache),
             reinterpret_cast<void*>(handle2));
  UnrefEntry(reinterpret_cast<void*>(&mock_cache),
             reinterpret_cast<void*>(handle3));
}

// Test with different cache instances
TEST(UnrefEntryTest_348, DifferentCacheInstances_348) {
  MockCache mock_cache1;
  MockCache mock_cache2;
  Cache::Handle* fake_handle = reinterpret_cast<Cache::Handle*>(0xABCD);

  EXPECT_CALL(mock_cache1, Release(fake_handle)).Times(1);
  EXPECT_CALL(mock_cache2, Release(fake_handle)).Times(1);

  UnrefEntry(reinterpret_cast<void*>(&mock_cache1),
             reinterpret_cast<void*>(fake_handle));
  UnrefEntry(reinterpret_cast<void*>(&mock_cache2),
             reinterpret_cast<void*>(fake_handle));
}

// Test that no other Cache methods are called
TEST(UnrefEntryTest_348, OnlyReleaseIsCalled_348) {
  ::testing::StrictMock<MockCache> strict_mock_cache;
  Cache::Handle* fake_handle = reinterpret_cast<Cache::Handle*>(0x9999);

  // StrictMock will fail if any unexpected method is called
  EXPECT_CALL(strict_mock_cache, Release(fake_handle)).Times(1);

  UnrefEntry(reinterpret_cast<void*>(&strict_mock_cache),
             reinterpret_cast<void*>(fake_handle));
}

}  // namespace leveldb
