#include "db/version_set.h"
#include "gtest/gtest.h"
#include <memory>

namespace {

class CompactionTest : public ::testing::Test {
 protected:
  Options options_;
};

TEST_F(CompactionTest, MakeReturnsValidCompaction) {
  auto compaction = CompactionTestPeer::Make(&options_, /*level=*/1);
  ASSERT_NE(compaction, nullptr);
}

TEST_F(CompactionTest, SetGrandparentsAffectsBehavior) {
  auto compaction = CompactionTestPeer::Make(&options_, 1);

  std::vector<FileMetaData*> grandparents;
  FileMetaData gp1, gp2;
  grandparents.push_back(&gp1);
  grandparents.push_back(&gp2);

  CompactionTestPeer::SetGrandparents(compaction.get(), grandparents);

  // Example: check an observable effect through a public method
  // (replace 'GrandparentCount' with an actual observable API)
  EXPECT_TRUE(compaction->ShouldStopBefore(/*some key*/));
}

TEST_F(CompactionTest, SetInputVersionChangesBehavior) {
  auto compaction = CompactionTestPeer::Make(&options_, 1);

  Version version;
  CompactionTestPeer::SetInputVersion(compaction.get(), &version);

  // Again, check via a public method that the injected version changes behavior
  EXPECT_EQ(compaction->NumInputFiles(0), 0);  // Example usage
}

} // namespace
