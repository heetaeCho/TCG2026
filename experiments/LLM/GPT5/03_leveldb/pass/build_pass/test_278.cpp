// tests/c_writeoptions_destroy_test.cc
#include <gtest/gtest.h>

extern "C" {
// We rely only on the C API surface.
// `leveldb_writeoptions_create` is part of the public C API in typical LevelDB builds.
typedef struct leveldb_writeoptions_t leveldb_writeoptions_t;

leveldb_writeoptions_t* leveldb_writeoptions_create();
void leveldb_writeoptions_destroy(leveldb_writeoptions_t* opt);
}

class WriteOptionsDestroyTest_278 : public ::testing::Test {};

// Normal operation: destroying a valid, created handle should succeed without crash/throw.
TEST_F(WriteOptionsDestroyTest_278, Destroy_ValidHandle_DoesNotCrash_278) {
  leveldb_writeoptions_t* opt = leveldb_writeoptions_create();
  ASSERT_NE(opt, nullptr) << "create() should return a valid handle for normal operation";

  // Act & Assert: should not crash or throw
  leveldb_writeoptions_destroy(opt);
  SUCCEED();
}

// Boundary case: passing nullptr must be a no-op (safe delete on nullptr).
TEST_F(WriteOptionsDestroyTest_278, Destroy_Nullptr_IsNoOp_278) {
  leveldb_writeoptions_t* opt = nullptr;

  // Act & Assert: should not crash or throw
  leveldb_writeoptions_destroy(opt);
  SUCCEED();
}
