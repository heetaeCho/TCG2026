#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



using namespace Exiv2;



// Test fixture for GroupInfo tests

class GroupInfoTest_1321 : public ::testing::Test {

protected:

    GroupInfo groupInfo;

    

    void SetUp() override {

        // Initialize with some known values

        groupInfo.ifdId_ = 0x0100; 

        groupInfo.ifdName_ = "IFD0";

        groupInfo.groupName_ = "Exif.Image";

        groupInfo.tagList_ = nullptr;

    }

};



// Test normal operation of operator==(const GroupName&)

TEST_F(GroupInfoTest_1321, CompareGroupName_Success_1321) {

    EXPECT_TRUE(groupInfo == GroupName("Exif.Image"));

    EXPECT_FALSE(groupInfo == GroupName("Exif.Thumbnail"));

}



// Test boundary condition with empty group name

TEST_F(GroupInfoTest_1321, CompareEmptyGroupName_Success_1321) {

    GroupInfo emptyGroup;

    emptyGroup.groupName_ = "";

    EXPECT_TRUE(emptyGroup == GroupName(""));

    EXPECT_FALSE(emptyGroup == GroupName("Exif.Image"));

}



// Test exceptional case with null group name

TEST_F(GroupInfoTest_1321, CompareNullGroupName_Success_1321) {

    GroupInfo nullGroup;

    nullGroup.groupName_ = nullptr;

    // Comparing a null groupName should be handled gracefully

    EXPECT_FALSE(nullGroup == GroupName("Exif.Image"));

}



// Test normal operation of operator==(IfdId)

TEST_F(GroupInfoTest_1321, CompareIfdId_Success_1321) {

    EXPECT_TRUE(groupInfo == IfdId(0x0100));

    EXPECT_FALSE(groupInfo == IfdId(0x8769));

}



// Test boundary condition with zero IfdId

TEST_F(GroupInfoTest_1321, CompareZeroIfdId_Success_1321) {

    GroupInfo zeroGroup;

    zeroGroup.ifdId_ = 0x0000;

    EXPECT_TRUE(zeroGroup == IfdId(0x0000));

}



// Test exceptional case with max IfdId

TEST_F(GroupInfoTest_1321, CompareMaxIfdId_Success_1321) {

    GroupInfo maxGroup;

    maxGroup.ifdId_ = 0xFFFF;

    EXPECT_TRUE(maxGroup == IfdId(0xFFFF));

}
