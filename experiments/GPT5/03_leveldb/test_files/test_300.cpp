// db_impl_destructor_test_300.cc
#include "db/db_impl.h"
#include "leveldb/options.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::Exactly;
using ::testing::NiceMock;

namespace leveldb {

// --- Test doubles for external collaborators ---

// Minimal tracking Logger that flips a flag on destruction.
// We pass an instance in Options to ensure DBImpl does NOT delete it.
class TrackingLogger : public Logger {
 public:
  static bool destroyed;
  ~TrackingLogger() override { destroyed = true; }
};
bool TrackingLogger::destroyed = false;

// Minimal tracking Cache that flips a flag on destruction.
// We pass an instance in Options to ensure DBImpl does NOT delete it.
class TrackingCache : public Cache {
 public:
  static bool destroyed;
  ~TrackingCache() override { destroyed = true; }

  // Provide no-op overrides to satisfy abstract interface (signatures may vary
  // in your tree; keep them as thin pass-throughs with no internal logic).
  Handle* Insert(const Slice&, void*, size_t, void (*)(const Slice&, void*),
                 ChargePolicy) override { return nullptr; }
  Handle* Lookup(const Slice&) override { return nullptr; }
  void Release(Handle*) override {}
  void* Value(Handle*) override { return nullptr; }
  void Erase(const Slice&) override {}
  uint64_t NewId() override { return 0; }
  void Prune() override {}
  size_t TotalCharge() const override { return 0; }
};
bool TrackingCache::destroyed = false;

// NiceMock Env to observe UnlockFile calls without forcing overrides
// for the whole Env interface.
class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, UnlockFile, (FileLock* lock), (override));
};

// --- Fixture ---
class DBImplDestructorTest_300 : public ::testing::Test {
 protected:
  // Build minimal Options suitable for constructing DBImpl.
  // We attach our mock Env and (optionally) user-provided logger/cache.
  static Options MakeBaseOptions(Env* env) {
    Options opt;
    opt.env = env;            // DBImpl will store this pointer
    opt.comparator = BytewiseComparator();
    return opt;
  }
};

// 1) Ensures DBImpl does NOT call Env::UnlockFile when it never acquired a lock.
//    (db_lock_ remains nullptr through this public construction path.)
TEST_F(DBImplDestructorTest_300, Destructor_DoesNotUnlockFileWhenNoLock_300) {
  NiceMock<MockEnv> env;

  // Expect no UnlockFile calls during destruction.
  EXPECT_CALL(env, UnlockFile(_)).Times(Exactly(0));

  Options opt = DBImplDestructorTest_300::MakeBaseOptions(&env);
  // Provide explicit user cache/logger so we isolate UnlockFile behavior only.
  TrackingLogger::destroyed = false;
  TrackingCache::destroyed = false;
  TrackingLogger logger;
  TrackingCache cache;
  opt.info_log = &logger;    // user-provided -> should NOT be deleted
  opt.block_cache = &cache;  // user-provided -> should NOT be deleted

  // Create then destroy DBImpl.
  DBImpl* db = new DBImpl(opt, "dummy-db-for-destructor-300");
  delete db;

  // Also verify our user-owned objects were not deleted by DBImpl.
  EXPECT_FALSE(TrackingLogger::destroyed);
  EXPECT_FALSE(TrackingCache::destroyed);
}

// 2) If user supplies a Logger, DBImpl must NOT delete it on destruction.
//    (owns_info_log_ should be false when raw_options.info_log is non-null.)
TEST_F(DBImplDestructorTest_300, Destructor_DoesNotDeleteUserProvidedLogger_300) {
  NiceMock<MockEnv> env;
  EXPECT_CALL(env, UnlockFile(_)).Times(Exactly(0));

  Options opt = DBImplDestructorTest_300::MakeBaseOptions(&env);

  TrackingLogger::destroyed = false;
  TrackingLogger logger;
  opt.info_log = &logger;  // user-provided

  DBImpl* db = new DBImpl(opt, "dummy-db-logger-300");
  delete db;

  EXPECT_FALSE(TrackingLogger::destroyed) << "DBImpl deleted a user-provided Logger";
}

// 3) If user supplies a Cache, DBImpl must NOT delete it on destruction.
//    (owns_cache_ should be false when raw_options.block_cache is non-null.)
TEST_F(DBImplDestructorTest_300, Destructor_DoesNotDeleteUserProvidedCache_300) {
  NiceMock<MockEnv> env;
  EXPECT_CALL(env, UnlockFile(_)).Times(Exactly(0));

  Options opt = DBImplDestructorTest_300::MakeBaseOptions(&env);

  TrackingCache::destroyed = false;
  TrackingCache cache;
  opt.block_cache = &cache;  // user-provided

  DBImpl* db = new DBImpl(opt, "dummy-db-cache-300");
  delete db;

  EXPECT_FALSE(TrackingCache::destroyed) << "DBImpl deleted a user-provided Cache";
}

}  // namespace leveldb
