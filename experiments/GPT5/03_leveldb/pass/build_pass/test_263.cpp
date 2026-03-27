// File: db/c_options_set_block_size_test.cc

#include <gtest/gtest.h>
#include <limits>

// Public headers (assumed to exist in the build)
// - leveldb/c.h should declare leveldb_options_t and leveldb_options_set_block_size
// - leveldb/options.h should declare leveldb::Options used by leveldb_options_t::rep
#include "leveldb/options.h"

// If your C API is in a separate header (e.g., "leveldb/c.h"), include it instead.
// We forward-declare here only the symbols we use; no logic is re-implemented.
extern "C" {
  struct leveldb_options_t;  // opaque to C callers; tests rely only on the public 'rep' field
  void leveldb_options_set_block_size(leveldb_options_t* opt, size_t s);
}

// The partial code shows that leveldb_options_t publicly exposes `rep` (an Options) member.
// We rely on this *public* surface to observe effects. No private state is touched.
struct leveldb_options_t {
  // NOTE: This mirrors the public layout shown in the prompt. If your project already
  // provides this in a header, remove this and include that header instead.
  leveldb::Options rep;
};

// ---------- Tests ----------

// Normal operation: setting a typical value updates rep.block_size.
TEST(LevelDB_OptionsSetBlockSize_263, SetsBlockSize_NormalValue_263) {
  leveldb_options_t opt;                 // default-constructed Options inside
  const size_t before = opt.rep.block_size;
  const size_t desired = 32 * 1024;      // 32 KiB

  leveldb_options_set_block_size(&opt, desired);

  EXPECT_NE(before, opt.rep.block_size);
  EXPECT_EQ(desired, opt.rep.block_size);
}

// Calling the setter again should overwrite the previous value (idempotent wrt last call).
TEST(LevelDB_OptionsSetBlockSize_263, OverridesPreviousValue_263) {
  leveldb_options_t opt;
  const size_t first = 8 * 1024;
  const size_t second = 64 * 1024;

  leveldb_options_set_block_size(&opt, first);
  EXPECT_EQ(first, opt.rep.block_size);

  leveldb_options_set_block_size(&opt, second);
  EXPECT_EQ(second, opt.rep.block_size);
}

// Boundary: zero. If zero is accepted by the API, the observable effect is that the field equals 0.
TEST(LevelDB_OptionsSetBlockSize_263, SetsBlockSize_ToZero_263) {
  leveldb_options_t opt;

  leveldb_options_set_block_size(&opt, 0);

  EXPECT_EQ(static_cast<size_t>(0), opt.rep.block_size);
}

// Boundary: very large size (max of size_t). We verify the value is stored as provided.
TEST(LevelDB_OptionsSetBlockSize_263, SetsBlockSize_ToMax_263) {
  leveldb_options_t opt;
  const size_t big = std::numeric_limits<size_t>::max();

  leveldb_options_set_block_size(&opt, big);

  EXPECT_EQ(big, opt.rep.block_size);
}

// Exceptional case (observable): passing a null pointer should cause the process to die
// due to dereferencing a null pointer. Use a death test to assert this behavior.
// Note: Death tests may require running with --gtest_death_test_style=threadsafe.
TEST(LevelDB_OptionsSetBlockSize_263, NullOptionsPointer_Death_263) {
  // On many platforms this will segfault; we only assert that it dies.
  EXPECT_DEATH(
      {
        // NOLINTNEXTLINE(bugprone-use-after-move,hicpp-no-array-decay)
        leveldb_options_set_block_size(nullptr, 4096);
      },
      ".*");
}
