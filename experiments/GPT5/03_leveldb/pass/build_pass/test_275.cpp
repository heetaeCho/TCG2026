#include <gtest/gtest.h>
#include <cstdint>

// --- Minimal interface surface from the prompt ---
// In your real tree, prefer including the actual headers instead of these
// minimal declarations, to avoid ODR issues.

namespace leveldb {
  struct Snapshot;  // forward-declare; not used directly
  struct ReadOptions {
    bool verify_checksums = false;
    bool fill_cache = true;          // default from prompt
    const Snapshot* snapshot = nullptr;
  };
}

// C-API wrapper type from the prompt
struct leveldb_readoptions_t { leveldb::ReadOptions rep; };

// Function under test (do NOT define; link against production code)
extern "C" void leveldb_readoptions_set_fill_cache(leveldb_readoptions_t* opt, uint8_t v);

// -------------------- Tests --------------------

class ReadOptionsFillCacheTest_275 : public ::testing::Test {
protected:
  leveldb_readoptions_t opt{};
};

// Default should match the provided interface (fill_cache = true)
TEST_F(ReadOptionsFillCacheTest_275, DefaultFillCacheIsTrue_275) {
  EXPECT_TRUE(opt.rep.fill_cache);
}

// Setting 0 should turn fill_cache off
TEST_F(ReadOptionsFillCacheTest_275, SetZeroDisablesFillCache_275) {
  leveldb_readoptions_set_fill_cache(&opt, static_cast<uint8_t>(0));
  EXPECT_FALSE(opt.rep.fill_cache);
}

// Setting 1 should turn fill_cache on
TEST_F(ReadOptionsFillCacheTest_275, SetOneEnablesFillCache_275) {
  // First flip it off to ensure we observe a change back to true
  leveldb_readoptions_set_fill_cache(&opt, static_cast<uint8_t>(0));
  ASSERT_FALSE(opt.rep.fill_cache);

  leveldb_readoptions_set_fill_cache(&opt, static_cast<uint8_t>(1));
  EXPECT_TRUE(opt.rep.fill_cache);
}

// Any non-zero value should be treated as "true" when assigned to bool
TEST_F(ReadOptionsFillCacheTest_275, NonZeroValueEnablesFillCache_275) {
  leveldb_readoptions_set_fill_cache(&opt, static_cast<uint8_t>(255));
  EXPECT_TRUE(opt.rep.fill_cache);
}

// Re-applying the same value should be idempotent (observable state unchanged)
TEST_F(ReadOptionsFillCacheTest_275, IdempotentWhenSettingSameValue_275) {
  // Start from the default true
  ASSERT_TRUE(opt.rep.fill_cache);

  // Setting true again keeps it true
  leveldb_readoptions_set_fill_cache(&opt, static_cast<uint8_t>(1));
  EXPECT_TRUE(opt.rep.fill_cache);

  // Turn it off
  leveldb_readoptions_set_fill_cache(&opt, static_cast<uint8_t>(0));
  ASSERT_FALSE(opt.rep.fill_cache);

  // Setting false again keeps it false
  leveldb_readoptions_set_fill_cache(&opt, static_cast<uint8_t>(0));
  EXPECT_FALSE(opt.rep.fill_cache);
}
