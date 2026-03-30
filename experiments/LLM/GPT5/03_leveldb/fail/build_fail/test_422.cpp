// File: table/release_block_test_422.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/cache.h"

// Include the implementation so the internal-linkage function is visible in this TU.
// This is necessary because ReleaseBlock has internal linkage (static) in the .cc.
#include "table/table.cc"

using ::testing::StrictMock;
using ::testing::_;
using ::testing::Eq;

namespace {

// Minimal mock of leveldb::Cache as an external collaborator.
// We only care about observing that Release(...) is called with the correct pointer.
// Other virtuals are left unmocked since tests never call them.
class MockCache : public leveldb::Cache {
 public:
  MOCK_METHOD(void, Release, (Handle* handle), (override));
};

struct DummyHandleTag { int x; };  // used only to obtain a stable, non-null address

}  // namespace

// Normal operation: verifies that Release(...) is invoked exactly once on the
// provided cache instance with the exact handle pointer.
TEST(ReleaseBlockTest_422, CallsReleaseWithProvidedHandle_422) {
  StrictMock<MockCache> cache;

  DummyHandleTag dummy{42};
  auto* handle = reinterpret_cast<leveldb::Cache::Handle*>(&dummy);

  EXPECT_CALL(cache, Release(Eq(handle))).Times(1);

  // Act: call the function under test with the cache and handle.
  leveldb::ReleaseBlock(&cache, handle);
}

// Boundary condition: handle can be nullptr. We verify the function forwards
// the nullptr to Cache::Release without crashing (assuming the cache is valid).
TEST(ReleaseBlockTest_422, ForwardsNullHandle_422) {
  StrictMock<MockCache> cache;

  leveldb::Cache::Handle* null_handle = nullptr;

  EXPECT_CALL(cache, Release(Eq(null_handle))).Times(1);

  leveldb::ReleaseBlock(&cache, null_handle);
}

// Interaction verification: ensures it calls Release on the *same* cache
// instance that is passed as arg, and not on some other cache.
TEST(ReleaseBlockTest_422, UsesExactCacheInstance_422) {
  StrictMock<MockCache> cache_a;
  StrictMock<MockCache> cache_b;

  DummyHandleTag dummy{7};
  auto* handle = reinterpret_cast<leveldb::Cache::Handle*>(&dummy);

  EXPECT_CALL(cache_a, Release(Eq(handle))).Times(1);
  EXPECT_CALL(cache_b, Release(_)).Times(0);

  leveldb::ReleaseBlock(&cache_a, handle);
}

// Sanity: verifies the pointer identity is preserved (no transformation).
// (This is already covered by Eq(handle), but this test highlights the intent.)
TEST(ReleaseBlockTest_422, PreservesHandleIdentity_422) {
  StrictMock<MockCache> cache;

  DummyHandleTag dummy{99};
  auto* handle = reinterpret_cast<leveldb::Cache::Handle*>(&dummy);

  // If ReleaseBlock altered the pointer, this expectation would fail.
  EXPECT_CALL(cache, Release(Eq(handle))).Times(1);

  leveldb::ReleaseBlock(&cache, handle);
}
