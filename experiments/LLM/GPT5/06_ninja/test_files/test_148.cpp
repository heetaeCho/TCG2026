// mount_point_parse_test_148.cc

#include "gtest/gtest.h"

#include <string>

// Include the implementation that defines MountPoint and parse().
#include "util.cc"

using std::string;

class MountPointParseTest_148 : public ::testing::Test {
 protected:
  MountPoint mp_;
};

TEST_F(MountPointParseTest_148, ParseValidLineWithoutOptionalFields_148) {
  // 10 fields total, '-' at index 6, no optionalFields.
  string line = "100 200 dev / /mnt opt1,opt2 - ext4 src sopt1,sopt2";

  EXPECT_TRUE(mp_.parse(line));

  EXPECT_EQ(100, mp_.mountId);
  EXPECT_EQ(200, mp_.parentId);
  EXPECT_EQ("dev", mp_.deviceId.AsString());
  EXPECT_EQ("/", mp_.root.AsString());
  EXPECT_EQ("/mnt", mp_.mountPoint.AsString());

  ASSERT_EQ(2u, mp_.options.size());
  EXPECT_EQ("opt1", mp_.options[0].AsString());
  EXPECT_EQ("opt2", mp_.options[1].AsString());

  EXPECT_TRUE(mp_.optionalFields.empty());

  EXPECT_EQ("ext4", mp_.fsType.AsString());
  EXPECT_EQ("src", mp_.mountSource.AsString());

  ASSERT_EQ(2u, mp_.superOptions.size());
  EXPECT_EQ("sopt1", mp_.superOptions[0].AsString());
  EXPECT_EQ("sopt2", mp_.superOptions[1].AsString());
}

TEST_F(MountPointParseTest_148, ParseValidLineWithOptionalFields_148) {
  // Optional fields between options (index 5) and '-' (index 8).
  string line =
      "1 2 dev / /mnt opt1,opt2 optField1 optField2 - ext4 src sopt1,sopt2";

  EXPECT_TRUE(mp_.parse(line));

  EXPECT_EQ(1, mp_.mountId);
  EXPECT_EQ(2, mp_.parentId);
  EXPECT_EQ("dev", mp_.deviceId.AsString());
  EXPECT_EQ("/", mp_.root.AsString());
  EXPECT_EQ("/mnt", mp_.mountPoint.AsString());

  ASSERT_EQ(2u, mp_.options.size());
  EXPECT_EQ("opt1", mp_.options[0].AsString());
  EXPECT_EQ("opt2", mp_.options[1].AsString());

  ASSERT_EQ(2u, mp_.optionalFields.size());
  EXPECT_EQ("optField1", mp_.optionalFields[0].AsString());
  EXPECT_EQ("optField2", mp_.optionalFields[1].AsString());

  EXPECT_EQ("ext4", mp_.fsType.AsString());
  EXPECT_EQ("src", mp_.mountSource.AsString());

  ASSERT_EQ(2u, mp_.superOptions.size());
  EXPECT_EQ("sopt1", mp_.superOptions[0].AsString());
  EXPECT_EQ("sopt2", mp_.superOptions[1].AsString());
}

TEST_F(MountPointParseTest_148, ParseFailsWhenTooFewFields_148) {
  // Only 9 fields (< 10), should fail the size check.
  string line = "1 2 dev / /mnt opt1,opt2 - ext4 src";

  EXPECT_FALSE(mp_.parse(line));
}

TEST_F(MountPointParseTest_148, ParseFailsWhenDashSeparatorMissing_148) {
  // At least 10 fields but no '-' from index 6 onward.
  string line =
      "1 2 dev / /mnt opt1,opt2 optField1 optField2 ext4 src sopt1,sopt2";

  EXPECT_FALSE(mp_.parse(line));
}

TEST_F(MountPointParseTest_148, ParseFailsWhenTrailerFieldCountInvalid_148) {
  // '-' found, but not exactly three fields after it.
  // Here: optionalStart + 3 != pieces.size(), so parse should fail.
  string line = "1 2 dev / /mnt opt1,opt2 optField1 - ext4 src";

  EXPECT_FALSE(mp_.parse(line));
}

TEST_F(MountPointParseTest_148, ParseOverwritesPreviousValuesOnSuccess_148) {
  string line1 = "100 200 dev1 / /mnt1 optA,optB - ext4 src1 super1,super2";
  string line2 = "10 20 dev2 /root /mnt2 o1,o2,o3 - xfs src2 so1";

  ASSERT_TRUE(mp_.parse(line1));
  EXPECT_EQ(100, mp_.mountId);
  EXPECT_EQ("dev1", mp_.deviceId.AsString());
  EXPECT_EQ("/mnt1", mp_.mountPoint.AsString());

  ASSERT_TRUE(mp_.parse(line2));
  EXPECT_EQ(10, mp_.mountId);
  EXPECT_EQ(20, mp_.parentId);
  EXPECT_EQ("dev2", mp_.deviceId.AsString());
  EXPECT_EQ("/root", mp_.root.AsString());
  EXPECT_EQ("/mnt2", mp_.mountPoint.AsString());

  ASSERT_EQ(3u, mp_.options.size());
  EXPECT_EQ("o1", mp_.options[0].AsString());
  EXPECT_EQ("o2", mp_.options[1].AsString());
  EXPECT_EQ("o3", mp_.options[2].AsString());

  EXPECT_TRUE(mp_.optionalFields.empty());
  EXPECT_EQ("xfs", mp_.fsType.AsString());
  EXPECT_EQ("src2", mp_.mountSource.AsString());

  ASSERT_EQ(1u, mp_.superOptions.size());
  EXPECT_EQ("so1", mp_.superOptions[0].AsString());
}
