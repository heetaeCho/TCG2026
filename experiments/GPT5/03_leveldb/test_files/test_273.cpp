// File: db/readoptions_destroy_test_273.cc

#include <gtest/gtest.h>

extern "C" {
// Only use the public C API — no peeking at internals.
#include "leveldb/c.h"
}

// No fixture is necessary since we're just exercising a simple destructor API.

// [Boundary] Destroy should be safe on nullptr.
TEST(LevelDBReadOptionsDestroy_273, DestroyNullptr_273) {
  // Expect: no crash / no throw.
  ASSERT_NO_THROW(leveldb_readoptions_destroy(nullptr));
}

// [Normal] Destroy should be safe on a freshly created object.
TEST(LevelDBReadOptionsDestroy_273, DestroyCreatedOptions_273) {
  leveldb_readoptions_t* opt = leveldb_readoptions_create();
  ASSERT_NE(opt, nullptr);

  // Expect: destroying a valid handle succeeds without throwing/crashing.
  ASSERT_NO_THROW(leveldb_readoptions_destroy(opt));
}

// [Normal + Variety] Destroy should be safe after options have been configured via public API.
TEST(LevelDBReadOptionsDestroy_273, DestroyConfiguredOptions_273) {
  leveldb_readoptions_t* opt = leveldb_readoptions_create();
  ASSERT_NE(opt, nullptr);

  // Configure via public interface only (observable inputs).
  // These setters are part of LevelDB's public C API; we avoid any internal access.
  leveldb_readoptions_set_verify_checksums(opt, 1);   // enable
  leveldb_readoptions_set_fill_cache(opt, 0);         // disable
  // Snapshot is typically optional; just ensure setter paths don't affect destruction when unused.
  leveldb_readoptions_set_snapshot(opt, nullptr);

  // Expect: still safe to destroy after being configured.
  ASSERT_NO_THROW(leveldb_readoptions_destroy(opt));
}
