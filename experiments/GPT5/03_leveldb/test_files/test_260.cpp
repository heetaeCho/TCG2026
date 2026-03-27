// File: leveldb_options_set_write_buffer_size_test.cc

#include <gtest/gtest.h>
#include <limits>
#include <cstddef>

// Use the public LevelDB Options interface
#include "leveldb/options.h"

// Forward declare the C-API function under test.
extern "C" {
void leveldb_options_set_write_buffer_size(leveldb_options_t* opt, size_t s);
}

// Minimal public wrapper type, matching the C-API surface shown in the prompt.
// We use the *public* Options as an observable surface (no private state).
struct leveldb_options_t {
  leveldb::Options rep;
};

class LevelDBOptionsWriteBufferSizeTest_260 : public ::testing::Test {
 protected:
  leveldb_options_t opt_;
};

// Normal operation: updates from default to a new value.
TEST_F(LevelDBOptionsWriteBufferSizeTest_260, SetsCustomSize_260) {
  // Sanity: default (from Options) should be non-zero.
  ASSERT_GT(opt_.rep.write_buffer_size, static_cast<size_t>(0));

  const size_t new_size = 8 * 1024 * 1024;  // 8MB
  leveldb_options_set_write_buffer_size(&opt_, new_size);
  EXPECT_EQ(opt_.rep.write_buffer_size, new_size);
}

// Boundary: setting to zero should be reflected exactly.
TEST_F(LevelDBOptionsWriteBufferSizeTest_260, AcceptsZero_260) {
  leveldb_options_set_write_buffer_size(&opt_, 0);
  EXPECT_EQ(opt_.rep.write_buffer_size, static_cast<size_t>(0));
}

// Boundary: setting to a very large value should be reflected exactly.
TEST_F(LevelDBOptionsWriteBufferSizeTest_260, AcceptsMaxSizeT_260) {
  const size_t kMax = (std::numeric_limits<size_t>::max)();
  leveldb_options_set_write_buffer_size(&opt_, kMax);
  EXPECT_EQ(opt_.rep.write_buffer_size, kMax);
}

// Normal operation: last call wins when invoked multiple times.
TEST_F(LevelDBOptionsWriteBufferSizeTest_260, MultipleCallsOverride_260) {
  leveldb_options_set_write_buffer_size(&opt_, 1 * 1024 * 1024);
  leveldb_options_set_write_buffer_size(&opt_, 2 * 1024 * 1024);
  leveldb_options_set_write_buffer_size(&opt_, 3 * 1024 * 1024);
  EXPECT_EQ(opt_.rep.write_buffer_size, static_cast<size_t>(3 * 1024 * 1024));
}

// Exceptional/error case (observable via process death): null pointer.
// If your environment doesn't support death tests, you can exclude this test.
TEST(LevelDBOptionsWriteBufferSizeDeathTest_260, NullPointerCrashes_260) {
#if GTEST_HAS_DEATH_TEST
  ASSERT_DEATH(
      {
        leveldb_options_set_write_buffer_size(nullptr, 1024);
      },
      "");  // Don't assert on message; just that it dies.
#else
  GTEST_SKIP() << "Death tests not supported on this platform/config.";
#endif
}
