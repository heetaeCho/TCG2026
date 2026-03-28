// File: db/c_writeoptions_set_sync_test_279.cc
#include <gtest/gtest.h>
#include <cstdint>

// ---- Minimal interface surface (as provided in the prompt) ----
namespace leveldb {
struct WriteOptions {
  bool sync = false;
  WriteOptions() = default;
};
}  // namespace leveldb

struct leveldb_writeoptions_t {
  leveldb::WriteOptions rep;
};

// Function under test (provided by the production code).
extern void leveldb_writeoptions_set_sync(leveldb_writeoptions_t* opt, uint8_t v);

// -------- Tests --------

// Normal operation: setting to true with 1
TEST(LeveldbWriteOptionsCAPI_279, SetSync_ToTrue_WhenValueIs1_279) {
  leveldb_writeoptions_t opt;
  opt.rep.sync = false;  // start from a known state

  leveldb_writeoptions_set_sync(&opt, static_cast<uint8_t>(1));

  EXPECT_TRUE(opt.rep.sync);
}

// Boundary: setting to false with 0
TEST(LeveldbWriteOptionsCAPI_279, SetSync_ToFalse_WhenValueIs0_279) {
  leveldb_writeoptions_t opt;
  opt.rep.sync = true;  // start from opposite state

  leveldb_writeoptions_set_sync(&opt, static_cast<uint8_t>(0));

  EXPECT_FALSE(opt.rep.sync);
}

// Boundary/observability: any non-zero should be treated as true (e.g., 255)
TEST(LeveldbWriteOptionsCAPI_279, SetSync_TreatsNonZeroAsTrue_279) {
  leveldb_writeoptions_t opt;
  opt.rep.sync = false;

  leveldb_writeoptions_set_sync(&opt, static_cast<uint8_t>(255));

  EXPECT_TRUE(opt.rep.sync);
}

// Repeated calls: last call determines observable state
TEST(LeveldbWriteOptionsCAPI_279, SetSync_MultipleCalls_LastValueWins_279) {
  leveldb_writeoptions_t opt;
  opt.rep.sync = false;

  leveldb_writeoptions_set_sync(&opt, static_cast<uint8_t>(1));
  EXPECT_TRUE(opt.rep.sync);

  leveldb_writeoptions_set_sync(&opt, static_cast<uint8_t>(0));
  EXPECT_FALSE(opt.rep.sync);
}
