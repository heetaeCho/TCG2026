#include "gtest/gtest.h"
#include <string>
#include <vector>
#include "util.h"
#include "string_piece.h"

class MountPointTest_148 : public ::testing::Test {
protected:
    MountPoint mp;
};

// Normal operation: A valid mountinfo line with typical fields
TEST_F(MountPointTest_148, ParseValidLine_148) {
    std::string line = "22 1 8:1 / /mnt/disk rw,relatime shared:1 - ext4 /dev/sda1 rw,errors=continue";
    EXPECT_TRUE(mp.parse(line));
    EXPECT_EQ(mp.mountId, 22);
    EXPECT_EQ(mp.parentId, 1);
    EXPECT_EQ(mp.deviceId.AsString(), "8:1");
    EXPECT_EQ(mp.root.AsString(), "/");
    EXPECT_EQ(mp.mountPoint.AsString(), "/mnt/disk");
    ASSERT_EQ(mp.options.size(), 2u);
    EXPECT_EQ(mp.options[0].AsString(), "rw");
    EXPECT_EQ(mp.options[1].AsString(), "relatime");
    ASSERT_EQ(mp.optionalFields.size(), 1u);
    EXPECT_EQ(mp.optionalFields[0].AsString(), "shared:1");
    EXPECT_EQ(mp.fsType.AsString(), "ext4");
    EXPECT_EQ(mp.mountSource.AsString(), "/dev/sda1");
    ASSERT_EQ(mp.superOptions.size(), 2u);
    EXPECT_EQ(mp.superOptions[0].AsString(), "rw");
    EXPECT_EQ(mp.superOptions[1].AsString(), "errors=continue");
}

// Normal operation: No optional fields (dash immediately after mount options)
TEST_F(MountPointTest_148, ParseValidLineNoOptionalFields_148) {
    std::string line = "36 35 98:0 /mnt1 /mnt2 rw,noatime - nfs server:/export rw,vers=3";
    EXPECT_TRUE(mp.parse(line));
    EXPECT_EQ(mp.mountId, 36);
    EXPECT_EQ(mp.parentId, 35);
    EXPECT_EQ(mp.deviceId.AsString(), "98:0");
    EXPECT_EQ(mp.root.AsString(), "/mnt1");
    EXPECT_EQ(mp.mountPoint.AsString(), "/mnt2");
    ASSERT_EQ(mp.options.size(), 2u);
    EXPECT_EQ(mp.options[0].AsString(), "rw");
    EXPECT_EQ(mp.options[1].AsString(), "noatime");
    EXPECT_EQ(mp.optionalFields.size(), 0u);
    EXPECT_EQ(mp.fsType.AsString(), "nfs");
    EXPECT_EQ(mp.mountSource.AsString(), "server:/export");
    ASSERT_EQ(mp.superOptions.size(), 2u);
    EXPECT_EQ(mp.superOptions[0].AsString(), "rw");
    EXPECT_EQ(mp.superOptions[1].AsString(), "vers=3");
}

// Boundary: Minimum valid line (exactly 10 fields with dash at position 6)
TEST_F(MountPointTest_148, ParseMinimumValidLine_148) {
    std::string line = "1 2 3:4 / /mnt rw - ext4 /dev/sda rw";
    EXPECT_TRUE(mp.parse(line));
    EXPECT_EQ(mp.mountId, 1);
    EXPECT_EQ(mp.parentId, 2);
    EXPECT_EQ(mp.deviceId.AsString(), "3:4");
    EXPECT_EQ(mp.root.AsString(), "/");
    EXPECT_EQ(mp.mountPoint.AsString(), "/mnt");
    EXPECT_EQ(mp.optionalFields.size(), 0u);
    EXPECT_EQ(mp.fsType.AsString(), "ext4");
    EXPECT_EQ(mp.mountSource.AsString(), "/dev/sda");
}

// Error case: Too few fields (less than 10)
TEST_F(MountPointTest_148, ParseTooFewFields_148) {
    std::string line = "1 2 3:4 / /mnt rw - ext4 /dev/sda";
    // This has 9 fields, should fail
    EXPECT_FALSE(mp.parse(line));
}

// Error case: Even fewer fields
TEST_F(MountPointTest_148, ParseVeryFewFields_148) {
    std::string line = "1 2 3:4";
    EXPECT_FALSE(mp.parse(line));
}

// Error case: Empty line
TEST_F(MountPointTest_148, ParseEmptyLine_148) {
    std::string line = "";
    EXPECT_FALSE(mp.parse(line));
}

// Error case: No dash separator found
TEST_F(MountPointTest_148, ParseNoDashSeparator_148) {
    std::string line = "1 2 3:4 / /mnt rw shared:1 ext4 /dev/sda rw,errors=continue";
    EXPECT_FALSE(mp.parse(line));
}

// Error case: Dash found but wrong number of fields after it
TEST_F(MountPointTest_148, ParseDashWrongFieldCountAfter_148) {
    // Dash found but only 2 fields after instead of 3
    std::string line = "1 2 3:4 / /mnt rw shared:1 - ext4 /dev/sda";
    // After dash we have ext4 and /dev/sda, that's 2 fields, need 3
    // Total: 10 fields. optionalStart = 8, pieces.size() = 10, optionalStart + 3 = 11 != 10
    EXPECT_FALSE(mp.parse(line));
}

// Error case: Dash at the very end has no fields after
TEST_F(MountPointTest_148, ParseDashAtEndNoFieldsAfter_148) {
    std::string line = "1 2 3:4 / /mnt rw shared:1 shared:2 shared:3 -";
    EXPECT_FALSE(mp.parse(line));
}

// Normal: Multiple optional fields
TEST_F(MountPointTest_148, ParseMultipleOptionalFields_148) {
    std::string line = "22 1 8:1 / /mnt rw shared:1 master:2 - ext4 /dev/sda1 rw";
    EXPECT_TRUE(mp.parse(line));
    EXPECT_EQ(mp.mountId, 22);
    EXPECT_EQ(mp.parentId, 1);
    ASSERT_EQ(mp.optionalFields.size(), 2u);
    EXPECT_EQ(mp.optionalFields[0].AsString(), "shared:1");
    EXPECT_EQ(mp.optionalFields[1].AsString(), "master:2");
    EXPECT_EQ(mp.fsType.AsString(), "ext4");
    EXPECT_EQ(mp.mountSource.AsString(), "/dev/sda1");
}

// Normal: Single super option
TEST_F(MountPointTest_148, ParseSingleSuperOption_148) {
    std::string line = "22 1 8:1 / /mnt rw - ext4 /dev/sda1 rw";
    EXPECT_TRUE(mp.parse(line));
    ASSERT_EQ(mp.superOptions.size(), 1u);
    EXPECT_EQ(mp.superOptions[0].AsString(), "rw");
}

// Normal: Multiple comma-separated mount options
TEST_F(MountPointTest_148, ParseMultipleMountOptions_148) {
    std::string line = "22 1 8:1 / /mnt rw,nosuid,nodev,relatime - ext4 /dev/sda1 rw";
    EXPECT_TRUE(mp.parse(line));
    ASSERT_EQ(mp.options.size(), 4u);
    EXPECT_EQ(mp.options[0].AsString(), "rw");
    EXPECT_EQ(mp.options[1].AsString(), "nosuid");
    EXPECT_EQ(mp.options[2].AsString(), "nodev");
    EXPECT_EQ(mp.options[3].AsString(), "relatime");
}

// Boundary: mountId and parentId as zero
TEST_F(MountPointTest_148, ParseZeroIds_148) {
    std::string line = "0 0 8:1 / /mnt rw - ext4 /dev/sda1 rw";
    EXPECT_TRUE(mp.parse(line));
    EXPECT_EQ(mp.mountId, 0);
    EXPECT_EQ(mp.parentId, 0);
}

// Normal: Non-numeric mountId (atoi behavior)
TEST_F(MountPointTest_148, ParseNonNumericMountId_148) {
    std::string line = "abc 2 8:1 / /mnt rw - ext4 /dev/sda1 rw";
    EXPECT_TRUE(mp.parse(line));
    EXPECT_EQ(mp.mountId, 0);  // atoi("abc") returns 0
}

// Error case: Exactly 9 pieces (one short of minimum)
TEST_F(MountPointTest_148, ParseExactlyNineFields_148) {
    std::string line = "1 2 3:4 / /mnt rw - ext4 /dev";
    EXPECT_FALSE(mp.parse(line));
}

// Boundary: Dash appears at position 6 (first possible position) with exactly 3 fields after
TEST_F(MountPointTest_148, ParseDashAtEarliestPosition_148) {
    std::string line = "1 2 3:4 / /mnt rw - ext4 /dev/sda rw";
    EXPECT_TRUE(mp.parse(line));
    EXPECT_EQ(mp.optionalFields.size(), 0u);
}

// Error case: Dash too early (before position 6)
TEST_F(MountPointTest_148, ParseDashBeforePosition6_148) {
    // The loop starts at i=6, so dash at position < 6 won't be found
    // "1 2 - / /mnt rw field ext4 /dev/sda rw" — dash at position 2
    std::string line = "1 2 - / /mnt rw field ext4 /dev/sda rw";
    // pieces.size() = 11, loop from 6..10, checks pieces[6]="field", pieces[7]="ext4", etc.
    // No dash found from position 6 onward, so optionalStart stays 0
    EXPECT_FALSE(mp.parse(line));
}

// Error case: Multiple dashes, first one after position 6 is used
TEST_F(MountPointTest_148, ParseMultipleDashes_148) {
    std::string line = "1 2 8:1 / /mnt rw - - fstype source superopts";
    // pieces: 1 2 8:1 / /mnt rw - - fstype source superopts (11 pieces)
    // Loop finds dash at index 6, optionalStart = 7
    // optionalStart + 3 = 10 != 11 -> false
    EXPECT_FALSE(mp.parse(line));
}

// Normal: Large mountId
TEST_F(MountPointTest_148, ParseLargeMountId_148) {
    std::string line = "999999 888888 8:1 / /mnt rw - ext4 /dev/sda1 rw";
    EXPECT_TRUE(mp.parse(line));
    EXPECT_EQ(mp.mountId, 999999);
    EXPECT_EQ(mp.parentId, 888888);
}

// Normal: Paths with special characters
TEST_F(MountPointTest_148, ParseSpecialPaths_148) {
    std::string line = "22 1 8:1 /subdir /mnt/my-disk rw,relatime - ext4 /dev/sda1 rw";
    EXPECT_TRUE(mp.parse(line));
    EXPECT_EQ(mp.root.AsString(), "/subdir");
    EXPECT_EQ(mp.mountPoint.AsString(), "/mnt/my-disk");
}
