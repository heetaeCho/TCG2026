#include <gtest/gtest.h>

#include <exiv2/tiffimage_int.hpp>

#include <vector>



using namespace Exiv2::Internal;



class TiffHeaderTest_1181 : public ::testing::Test {

protected:

    void SetUp() override {

        primaryGroups = {IfdId::ifd0Id, IfdId::ifd1Id};

        tiffHeaderWithTags = TiffHeader(Exiv2::littleEndian, 0, true);

        tiffHeaderWithoutTags = TiffHeader(Exiv2::bigEndian, 0, false);

    }



    std::vector<IfdId> primaryGroups;

    TiffHeader tiffHeaderWithTags;

    TiffHeader tiffHeaderWithoutTags;

};



TEST_F(TiffHeaderTest_1181, IsImageTag_ReturnsFalseWhenNoImageTags_1181) {

    EXPECT_FALSE(tiffHeaderWithoutTags.isImageTag(0x0112, IfdId::ifd0Id, primaryGroups));

}



TEST_F(TiffHeaderTest_1181, IsImageTag_ReturnsTrueForValidImageTagAndGroup_1181) {

    EXPECT_TRUE(tiffHeaderWithTags.isImageTag(0x0112, IfdId::ifd0Id, primaryGroups));

}



TEST_F(TiffHeaderTest_1181, IsImageTag_ReturnsFalseForInvalidGroup_1181) {

    EXPECT_FALSE(tiffHeaderWithTags.isImageTag(0x0112, IfdId::gpsId, primaryGroups));

}



TEST_F(TiffHeaderTest_1181, IsImageTag_ReturnsTrueForIfd0IdRegardlessOfPrimaryGroups_1181) {

    EXPECT_TRUE(tiffHeaderWithTags.isImageTag(0x0112, IfdId::ifd0Id, {}));

}



TEST_F(TiffHeaderTest_1181, IsImageTag_ReturnsFalseForNonIfd0IdWithoutGroupInPrimaryGroups_1181) {

    EXPECT_FALSE(tiffHeaderWithTags.isImageTag(0x0112, IfdId::ifd1Id, {}));

}



TEST_F(TiffHeaderTest_1181, IsImageTag_HandlesBoundaryConditionOfEmptyPrimaryGroups_1181) {

    EXPECT_TRUE(tiffHeaderWithTags.isImageTag(0x0112, IfdId::ifd0Id, {}));

}
