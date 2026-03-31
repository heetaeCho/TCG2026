#include <gtest/gtest.h>
#include <exiv2/tags.hpp>

namespace {

using namespace Exiv2;

class GroupInfoTest_1320 : public ::testing::Test {
protected:
    GroupInfo groupInfo_;

    void SetUp() override {
        // Initialize with a known IfdId
        groupInfo_.ifdId_ = IfdId::ifdIdNotSet;
        groupInfo_.ifdName_ = "testIfd";
        groupInfo_.groupName_ = "testGroup";
        groupInfo_.tagList_ = nullptr;
    }
};

// Test that operator== returns true when IfdId matches
TEST_F(GroupInfoTest_1320, OperatorEqualIfdId_MatchingId_ReturnsTrue_1320) {
    groupInfo_.ifdId_ = IfdId::ifdIdNotSet;
    EXPECT_TRUE(groupInfo_ == IfdId::ifdIdNotSet);
}

// Test that operator== returns false when IfdId does not match
TEST_F(GroupInfoTest_1320, OperatorEqualIfdId_NonMatchingId_ReturnsFalse_1320) {
    groupInfo_.ifdId_ = IfdId::ifdIdNotSet;
    EXPECT_FALSE(groupInfo_ == IfdId::exifId);
}

// Test equality with exifId
TEST_F(GroupInfoTest_1320, OperatorEqualIfdId_ExifId_ReturnsTrue_1320) {
    groupInfo_.ifdId_ = IfdId::exifId;
    EXPECT_TRUE(groupInfo_ == IfdId::exifId);
}

// Test equality with gpsId
TEST_F(GroupInfoTest_1320, OperatorEqualIfdId_GpsId_ReturnsTrue_1320) {
    groupInfo_.ifdId_ = IfdId::gpsId;
    EXPECT_TRUE(groupInfo_ == IfdId::gpsId);
}

// Test inequality: groupInfo has gpsId, compared with exifId
TEST_F(GroupInfoTest_1320, OperatorEqualIfdId_GpsVsExif_ReturnsFalse_1320) {
    groupInfo_.ifdId_ = IfdId::gpsId;
    EXPECT_FALSE(groupInfo_ == IfdId::exifId);
}

// Test equality with iopId
TEST_F(GroupInfoTest_1320, OperatorEqualIfdId_IopId_ReturnsTrue_1320) {
    groupInfo_.ifdId_ = IfdId::iopId;
    EXPECT_TRUE(groupInfo_ == IfdId::iopId);
}

// Test inequality with iopId vs ifd0Id
TEST_F(GroupInfoTest_1320, OperatorEqualIfdId_IopVsIfd0_ReturnsFalse_1320) {
    groupInfo_.ifdId_ = IfdId::iopId;
    EXPECT_FALSE(groupInfo_ == IfdId::ifd0Id);
}

// Test with ifd0Id
TEST_F(GroupInfoTest_1320, OperatorEqualIfdId_Ifd0Id_ReturnsTrue_1320) {
    groupInfo_.ifdId_ = IfdId::ifd0Id;
    EXPECT_TRUE(groupInfo_ == IfdId::ifd0Id);
}

// Test symmetry: setting different IfdIds and verifying correct comparison
TEST_F(GroupInfoTest_1320, OperatorEqualIfdId_MultipleComparisons_1320) {
    groupInfo_.ifdId_ = IfdId::exifId;
    EXPECT_TRUE(groupInfo_ == IfdId::exifId);
    EXPECT_FALSE(groupInfo_ == IfdId::gpsId);
    EXPECT_FALSE(groupInfo_ == IfdId::ifdIdNotSet);
}

// Test that changing ifdId_ changes the result of operator==
TEST_F(GroupInfoTest_1320, OperatorEqualIfdId_ChangeId_ReflectsNewValue_1320) {
    groupInfo_.ifdId_ = IfdId::exifId;
    EXPECT_TRUE(groupInfo_ == IfdId::exifId);

    groupInfo_.ifdId_ = IfdId::gpsId;
    EXPECT_FALSE(groupInfo_ == IfdId::exifId);
    EXPECT_TRUE(groupInfo_ == IfdId::gpsId);
}

}  // namespace
