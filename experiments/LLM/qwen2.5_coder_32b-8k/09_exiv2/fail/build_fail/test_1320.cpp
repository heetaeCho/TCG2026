#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



using namespace Exiv2;



class GroupInfoTest_1320 : public ::testing::Test {

protected:

    GroupInfo groupInfo;

    

    void SetUp() override {

        // Initialize the GroupInfo object for testing

        groupInfo.ifdId_ = 0x8769; // Example IfdId value

        groupInfo.ifdName_ = "ExifIFD";

        groupInfo.groupName_ = "Exif";

        groupInfo.tagList_ = nullptr;

    }

};



TEST_F(GroupInfoTest_1320, OperatorEqualIfdId_Match_1320) {

    // Test if operator== with IfdId returns true when ids match

    EXPECT_TRUE(groupInfo == 0x8769);

}



TEST_F(GroupInfoTest_1320, OperatorEqualIfdId_NotMatch_1320) {

    // Test if operator== with IfdId returns false when ids do not match

    EXPECT_FALSE(groupInfo == 0x8768);

}



TEST_F(GroupInfoTest_1320, OperatorEqualGroupName_Match_1320) {

    // Test if operator== with GroupName returns true when names match

    GroupName groupName("Exif");

    EXPECT_TRUE(groupInfo == groupName);

}



TEST_F(GroupInfoTest_1320, OperatorEqualGroupName_NotMatch_1320) {

    // Test if operator== with GroupName returns false when names do not match

    GroupName groupName("IFD0");

    EXPECT_FALSE(groupInfo == groupName);

}
