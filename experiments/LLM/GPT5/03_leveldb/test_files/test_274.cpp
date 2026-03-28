// File: tests/db/c_readoptions_set_verify_checksums_test.cc

#include <gtest/gtest.h>

// If your project exposes official headers, prefer including them instead:
// #include "leveldb/c.h"
// #include "leveldb/options.h"

// Minimal declarations based on the provided interface snippets.
extern "C" {
  struct leveldb_readoptions_t;
  void leveldb_readoptions_set_verify_checksums(leveldb_readoptions_t* opt, uint8_t v);
}

namespace leveldb {
struct Snapshot;
struct ReadOptions {
  public:
    bool verify_checksums = false;
    bool fill_cache = true;
    const Snapshot* snapshot = nullptr;
};
}  // namespace leveldb

// As provided in the prompt (public for test visibility)
struct leveldb_readoptions_t {
  public:
    leveldb::ReadOptions rep;
};

// ---------- Tests ----------

TEST(ReadOptionsCAPI_274, DefaultIsFalse_274) {
  leveldb_readoptions_t opt{};
  // By interface: verify_checksums default should be false.
  EXPECT_FALSE(opt.rep.verify_checksums);
}

TEST(ReadOptionsCAPI_274, SetToTrueWithOne_274) {
  leveldb_readoptions_t opt{};
  ASSERT_FALSE(opt.rep.verify_checksums);  // sanity

  leveldb_readoptions_set_verify_checksums(&opt, /*v=*/1);
  EXPECT_TRUE(opt.rep.verify_checksums);
}

TEST(ReadOptionsCAPI_274, SetToFalseWithZero_274) {
  leveldb_readoptions_t opt{};
  // Flip to true first to ensure transition back to false is observable.
  leveldb_readoptions_set_verify_checksums(&opt, /*v=*/1);
  ASSERT_TRUE(opt.rep.verify_checksums);

  leveldb_readoptions_set_verify_checksums(&opt, /*v=*/0);
  EXPECT_FALSE(opt.rep.verify_checksums);
}

TEST(ReadOptionsCAPI_274, NonZeroValuesAreTreatedAsTrue_274) {
  leveldb_readoptions_t opt{};
  ASSERT_FALSE(opt.rep.verify_checksums);

  leveldb_readoptions_set_verify_checksums(&opt, /*v=*/255);  // boundary for uint8_t
  EXPECT_TRUE(opt.rep.verify_checksums);
}

TEST(ReadOptionsCAPI_274, MultipleTogglesPreserveLastSet_274) {
  leveldb_readoptions_t opt{};

  leveldb_readoptions_set_verify_checksums(&opt, 0);
  EXPECT_FALSE(opt.rep.verify_checksums);

  leveldb_readoptions_set_verify_checksums(&opt, 1);
  EXPECT_TRUE(opt.rep.verify_checksums);

  leveldb_readoptions_set_verify_checksums(&opt, 0);
  EXPECT_FALSE(opt.rep.verify_checksums);

  leveldb_readoptions_set_verify_checksums(&opt, 2);  // any non-zero -> true
  EXPECT_TRUE(opt.rep.verify_checksums);
}
