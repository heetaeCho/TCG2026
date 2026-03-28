// File: table_cache_get_test_351.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "db/table_cache.h"
#include "leveldb/status.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "leveldb/table.h"
#include "leveldb/cache.h"

using ::testing::Eq;
using ::testing::Ne;
using ::testing::StrEq;

namespace leveldb {

// ---------- Test seams & helpers (only for testing) ----------

// Forward from db/table_cache.cc
struct TableAndFile { RandomAccessFile* file; Table* table; };

// Global knobs/records to control collaborator behavior
namespace test_seams_351 {
  // Controls for FindTable
  static Status findtable_status = Status::OK();
  static Cache::Handle* findtable_handle_to_return =
      reinterpret_cast<Cache::Handle*>(0xDEADBEEF);

  // Controls for Table::InternalGet
  static Status internalget_status = Status::OK();
  static bool internalget_should_invoke_cb = true;

  // Observe InternalGet call arguments
  static bool internalget_called = false;
  static Slice internalget_last_key;
  static const void* internalget_last_arg = nullptr;

  // Observe cache Release usage
  static int release_call_count = 0;
  static Cache::Handle* last_released_handle = nullptr;

  inline void Reset() {
    findtable_status = Status::OK();
    findtable_handle_to_return =
        reinterpret_cast<Cache::Handle*>(0xDEADBEEF);
    internalget_status = Status::OK();
    internalget_should_invoke_cb = true;
    internalget_called = false;
    internalget_last_key = Slice();
    internalget_last_arg = nullptr;
    release_call_count = 0;
    last_released_handle = nullptr;
  }
}  // namespace test_seams_351

using namespace test_seams_351;

// A tiny test cache that lets us observe Value()/Release() interactions.
class TestCache351 : public Cache {
 public:
  // We'll use a single static TableAndFile that points to any Table*.
  TableAndFile tf_{};

  // Handle passed back by FindTable that TableCache will later pass here.
  Cache::Handle* expected_handle_ = nullptr;

  // Cache API overrides we need:
  void* Value(Handle* h) override {
    // Return TableAndFile* only when handle matches; otherwise nullptr.
    if (h == expected_handle_) return &tf_;
    return nullptr;
  }
  void Release(Handle* h) override {
    ++release_call_count;
    last_released_handle = h;
  }

  // The rest are unused in these tests; provide trivial stubs.
  Handle* Insert(const Slice&, void*, size_t,
                 void (*)(const Slice&, void*)) override { return nullptr; }
  Handle* Lookup(const Slice&) override { return nullptr; }
  void Erase(const Slice&) override {}
  void Prune() override {}
  uint64_t NewId() override { return 0; }
  const size_t TotalCharge() override { return 0; }
};

// Singleton test cache instance returned by NewLRUCache seam.
static TestCache351 g_test_cache_351;

// Seam: override the production factory to inject our TestCache.
Cache* NewLRUCache(int /*entries*/) {
  return &g_test_cache_351;
}

// Seam: override TableCache::FindTable to control status/handle returned.
Status TableCache::FindTable(uint64_t /*file_number*/, uint64_t /*file_size*/,
                             Cache::Handle** handle) {
  if (findtable_status.ok()) {
    *handle = findtable_handle_to_return;  // Provide the handle to Get()
  } else {
    *handle = nullptr;
  }
  // Also set the cache's expected handle (used in Value/Release).
  g_test_cache_351.expected_handle_ = *handle;
  return findtable_status;
}

// Seam: override Table::InternalGet so we can simulate outcomes and
// verify callback invocations without needing a real Table implementation.
Status Table::InternalGet(const ReadOptions& /*options*/,
                          const Slice& k,
                          void* arg,
                          void (*handle_result)(void*, const Slice&, const Slice&)) {
  internalget_called = true;
  internalget_last_key = k;
  internalget_last_arg = arg;

  if (internalget_should_invoke_cb && handle_result != nullptr) {
    // Simulate a found KV pair; value content itself is not important here.
    static const Slice v("val");
    handle_result(arg, k, v);
  }
  return internalget_status;
}

// Simple callback used in tests to collect results observed from Get().
struct CollectedKV {
  std::string key;
  std::string value;
};
static void CollectKVCallback(void* vec_ptr, const Slice& k, const Slice& v) {
  auto* out = reinterpret_cast<std::vector<CollectedKV>*>(vec_ptr);
  out->push_back(CollectedKV{k.ToString(), v.ToString()});
}

// ---------- Test Fixture ----------
class TableCacheGetTest_351 : public ::testing::Test {
 protected:
  Options default_options_;
  std::unique_ptr<TableCache> cache_;

  void SetUp() override {
    Reset();
    // g_test_cache_351's TableAndFile.table can be any non-null pointer,
    // because InternalGet seam doesn't use the object state.
    g_test_cache_351.tf_.table = reinterpret_cast<Table*>(0x1111);

    // Construct a TableCache; it will receive our TestCache via NewLRUCache().
    cache_.reset(new TableCache(/*dbname*/"db", default_options_, /*entries*/8));
  }

  void TearDown() override { cache_.reset(); }
};

// ---------- Tests ----------

// Normal path: FindTable OK -> InternalGet OK; callback invoked; Release called.
TEST_F(TableCacheGetTest_351, Get_Success_InvokesCallback_AndReleasesHandle_351) {
  // Arrange
  findtable_status = Status::OK();
  internalget_status = Status::OK();
  internalget_should_invoke_cb = true;

  ReadOptions ro;
  const Slice key("k1");
  std::vector<CollectedKV> out;

  // Act
  Status s = cache_->Get(ro, /*file_number*/1, /*file_size*/123, key,
                         &out, &CollectKVCallback);

  // Assert
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(internalget_called);
  EXPECT_THAT(internalget_last_key.ToString(), Eq("k1"));
  EXPECT_EQ(internalget_last_arg, &out);

  // Callback should have been invoked exactly once with the same key and some value.
  ASSERT_EQ(out.size(), 1u);
  EXPECT_THAT(out[0].key, Eq("k1"));
  // Value content is controlled by seam ("val"); we just verify non-empty.
  EXPECT_FALSE(out[0].value.empty());

  // Cache::Release should be called exactly once with the same handle provided by FindTable.
  EXPECT_EQ(release_call_count, 1);
  EXPECT_EQ(last_released_handle, findtable_handle_to_return);
}

// InternalGet returns NotFound: Get should propagate status; no callback.
TEST_F(TableCacheGetTest_351, Get_InternalGetNotFound_PropagatesStatus_NoCallback_351) {
  // Arrange
  findtable_status = Status::OK();
  internalget_status = Status::NotFound("missing");
  internalget_should_invoke_cb = false;

  ReadOptions ro;
  const Slice key("nope");
  std::vector<CollectedKV> out;

  // Act
  Status s = cache_->Get(ro, /*file_number*/7, /*file_size*/99, key,
                         &out, &CollectKVCallback);

  // Assert
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_TRUE(internalget_called);
  EXPECT_TRUE(out.empty());  // callback must not be invoked

  // Even on error from InternalGet, TableCache should still Release the handle it acquired.
  EXPECT_EQ(release_call_count, 1);
  EXPECT_EQ(last_released_handle, findtable_handle_to_return);
}

// FindTable fails: Get should return that status and must NOT call Release nor InternalGet.
TEST_F(TableCacheGetTest_351, Get_FindTableFails_SkipsInternalGet_NoRelease_351) {
  // Arrange
  findtable_status = Status::IOError("cannot open table");
  // Defensive: if InternalGet were called, we'd notice.
  internalget_status = Status::OK();
  internalget_should_invoke_cb = true;

  ReadOptions ro;
  const Slice key("kX");
  std::vector<CollectedKV> out;

  // Act
  Status s = cache_->Get(ro, /*file_number*/42, /*file_size*/0, key,
                         &out, &CollectKVCallback);

  // Assert
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(internalget_called);   // must not call through to the table
  EXPECT_TRUE(out.empty());           // no callback
  EXPECT_EQ(release_call_count, 0);   // handle was never acquired -> never released
}

// Boundary: empty key should still be forwarded to InternalGet and callback.
TEST_F(TableCacheGetTest_351, Get_EmptyKey_IsForwarded_ToInternalGet_351) {
  // Arrange
  findtable_status = Status::OK();
  internalget_status = Status::OK();
  internalget_should_invoke_cb = true;

  ReadOptions ro;
  const Slice empty_key("");
  std::vector<CollectedKV> out;

  // Act
  Status s = cache_->Get(ro, /*file_number*/3, /*file_size*/10, empty_key,
                         &out, &CollectKVCallback);

  // Assert
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(internalget_called);
  EXPECT_THAT(internalget_last_key.size(), Eq(0u));
  ASSERT_EQ(out.size(), 1u);
  EXPECT_THAT(out[0].key, Eq(""));  // callback receives the same (empty) key
  EXPECT_EQ(release_call_count, 1);
}

}  // namespace leveldb
