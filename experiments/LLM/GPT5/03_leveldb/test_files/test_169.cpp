// File: version_set_add_live_files_test.cc

#include "db/version_set.h"
#include "db/dbformat.h"

#include <gtest/gtest.h>
#include <set>

namespace leveldb {

class VersionSetAddLiveFilesTest_169 : public ::testing::Test {
protected:
  // Build a VersionSet using only publicly available types.
  // We pass a nullptr TableCache because AddLiveFiles does not depend on it.
  VersionSetAddLiveFilesTest_169()
      : options_(),
        icmp_(options_.comparator),
        vset_(dbname_, &options_, /*table_cache=*/nullptr, &icmp_) {
    options_.comparator = BytewiseComparator();
    options_.env = Env::Default();
  }

  std::string dbname_ = "gtest-db-AddLiveFiles-169";
  Options options_;
  InternalKeyComparator icmp_;
  VersionSet vset_;
};

// [Normal/empty] When there are no versions/files, live should remain empty.
TEST_F(VersionSetAddLiveFilesTest_169, EmptyWhenNoVersions_169) {
  std::set<uint64_t> live;
  vset_.AddLiveFiles(&live);
  EXPECT_TRUE(live.empty());
}

// [Boundary] If the caller provides a pre-populated set, the method should
// not remove anything and (with no files present) leave it unchanged.
TEST_F(VersionSetAddLiveFilesTest_169, PreservesPreExistingEntriesWhenNoFiles_169) {
  std::set<uint64_t> live = {1, 42, 9999};
  vset_.AddLiveFiles(&live);
  // Expect exactly the same contents (no duplicates added, nothing removed).
  EXPECT_EQ(live.size(), 3u);
  EXPECT_TRUE(live.count(1));
  EXPECT_TRUE(live.count(42));
  EXPECT_TRUE(live.count(9999));
}

// [Stability] Calling AddLiveFiles repeatedly with no files should be idempotent.
TEST_F(VersionSetAddLiveFilesTest_169, IdempotentWithNoFiles_169) {
  std::set<uint64_t> live;
  vset_.AddLiveFiles(&live);
  auto first_size = live.size();
  vset_.AddLiveFiles(&live);
  EXPECT_EQ(live.size(), first_size);
}

}  // namespace leveldb
