// File: db/version_set_numlevelbytes_test.cc

#include "db/version_set.h"
#include "db/dbformat.h"
#include "util/env.h"
#include "util/coding.h"
#include "gtest/gtest.h"

using namespace leveldb;

class VersionSet_NumLevelBytesTest_170 : public ::testing::Test {
protected:
  std::string dbname_ = "NumLevelBytesTestDB_170";
  Options options_;
  const Comparator* user_cmp_ = BytewiseComparator();
  InternalKeyComparator icmp_{user_cmp_};
  TableCache* table_cache_ = nullptr;
  VersionSet* vset_ = nullptr;

  void SetUp() override {
    options_.env = Env::Default();
    // Construct minimal TableCache; entries count is arbitrary for test.
    table_cache_ = new TableCache(dbname_, &options_, /*entries=*/16);
    vset_ = new VersionSet(dbname_, &options_, table_cache_, &icmp_);

    // Death tests are safer/more reliable with this style.
    GTEST_FLAG_SET(death_test_style, "threadsafe");
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
  }
};

// [Boundary] Negative level should trigger an assertion.
TEST_F(VersionSet_NumLevelBytesTest_170, NumLevelBytes_AssertOnNegative_170) {
  EXPECT_DEATH(
      {
        // N.B. We only test the assertion behavior; we do not depend on any
        // internal state or file layout.
        (void)vset->NumLevelBytes(-1);
      },
      ".*");
}

// [Boundary] level == config::kNumLevels (upper bound) should trigger an assertion.
TEST_F(VersionSet_NumLevelBytesTest_170, NumLevelBytes_AssertOnEqualToKNumLevels_170) {
  const int out_of_range_level = config::kNumLevels; // equal to upper bound
  EXPECT_DEATH(
      {
        (void)vset->NumLevelBytes(out_of_range_level);
      },
      ".*");
}

// [Sanity] Verify the test harness uses the expected level count (public constant).
TEST_F(VersionSet_NumLevelBytesTest_170, KNumLevels_PublicConstantIsSeven_170) {
  // This does not assert behavior of NumLevelBytes; it documents the public
  // boundary used by the API and ensures the tests track the interface contract.
  EXPECT_EQ(7, config::kNumLevels);
}
