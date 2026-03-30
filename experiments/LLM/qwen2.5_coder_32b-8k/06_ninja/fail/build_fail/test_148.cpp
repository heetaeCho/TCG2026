#include <gtest/gtest.h>

#include "string_piece.h"

#include "util.cc"



using namespace std;



class MountPointTest_148 : public ::testing::Test {

protected:

    MountPoint mount_point;

};



TEST_F(MountPointTest_148, ParseValidLine_148) {

    string line = "1 2 device /root /mountpoint opt1,opt2 - optionalField fsType source superOpt1,superOpt2";

    EXPECT_TRUE(mount_point.parse(line));

    EXPECT_EQ(1, mount_point.mountId);

    EXPECT_EQ(2, mount_point.parentId);

    EXPECT_EQ("device", mount_point.deviceId.AsString());

    EXPECT_EQ("/root", mount_point.root.AsString());

    EXPECT_EQ("/mountpoint", mount_point.mountPoint.AsString());

    EXPECT_EQ(vector<StringPiece>({"opt1", "opt2"}), mount_point.options);

    EXPECT_EQ(vector<StringPiece>({"optionalField"}), mount_point.optionalFields);

    EXPECT_EQ("fsType", mount_point.fsType.AsString());

    EXPECT_EQ("source", mount_point.mountSource.AsString());

    EXPECT_EQ(vector<StringPiece>({"superOpt1", "superOpt2"}), mount_point.superOptions);

}



TEST_F(MountPointTest_148, ParseLineWithMissingFields_148) {

    string line = "1 2 device /root";

    EXPECT_FALSE(mount_point.parse(line));

}



TEST_F(MountPointTest_148, ParseLineWithInvalidOptionalStart_148) {

    string line = "1 2 device /root /mountpoint opt1,opt2 fsType source superOpt1,superOpt2";

    EXPECT_FALSE(mount_point.parse(line));

}



TEST_F(MountPointTest_148, ParseLineWithExtraFieldsAfterOptionalStart_148) {

    string line = "1 2 device /root /mountpoint opt1,opt2 - optionalField fsType source superOpt1,superOpt2 extra";

    EXPECT_FALSE(mount_point.parse(line));

}



TEST_F(MountPointTest_148, ParseLineWithMissingOptionalFields_148) {

    string line = "1 2 device /root /mountpoint opt1,opt2 - fsType source superOpt1,superOpt2";

    EXPECT_TRUE(mount_point.parse(line));

    EXPECT_EQ(vector<StringPiece>(), mount_point.optionalFields);

}



TEST_F(MountPointTest_148, ParseLineWithEmptyOptionalFields_148) {

    string line = "1 2 device /root /mountpoint opt1,opt2 - fsType source superOpt1,superOpt2";

    EXPECT_TRUE(mount_point.parse(line));

    EXPECT_EQ(vector<StringPiece>(), mount_point.optionalFields);

}



TEST_F(MountPointTest_148, ParseLineWithEmptyOptions_148) {

    string line = "1 2 device /root /mountpoint - optionalField fsType source superOpt1,superOpt2";

    EXPECT_TRUE(mount_point.parse(line));

    EXPECT_EQ(vector<StringPiece>(), mount_point.options);

}



TEST_F(MountPointTest_148, ParseLineWithEmptySuperOptions_148) {

    string line = "1 2 device /root /mountpoint opt1,opt2 - optionalField fsType source";

    EXPECT_TRUE(mount_point.parse(line));

    EXPECT_EQ(vector<StringPiece>(), mount_point.superOptions);

}
