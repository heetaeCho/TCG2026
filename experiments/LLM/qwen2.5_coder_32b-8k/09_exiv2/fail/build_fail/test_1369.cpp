#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



namespace Exiv2 {

    namespace Internal {

        IfdId groupId(const std::string& groupName);

    }

}



class GroupIdTest : public ::testing::Test {};



TEST_F(GroupIdTest_1369, NormalOperation_ImageGroup_1369) {

    EXPECT_EQ(Exiv2::IfdId::ifd0Id, Exiv2::Internal::groupId("Image"));

}



TEST_F(GroupIdTest_1369, NormalOperation_ThumbnailGroup_1369) {

    EXPECT_EQ(Exiv2::IfdId::ifd1Id, Exiv2::Internal::groupId("Thumbnail"));

}



TEST_F(GroupIdTest_1369, NormalOperation_ExifGroup_1369) {

    EXPECT_EQ(Exiv2::IfdId::exifId, Exiv2::Internal::groupId("Photo"));

}



TEST_F(GroupIdTest_1369, NormalOperation_GpsInfoGroup_1369) {

    EXPECT_EQ(Exiv2::IfdId::gpsId, Exiv2::Internal::groupId("GPSInfo"));

}



TEST_F(GroupIdTest_1369, BoundaryCondition_EmptyString_1369) {

    EXPECT_EQ(Exiv2::IfdId::ifdIdNotSet, Exiv2::Internal::groupId(""));

}



TEST_F(GroupIdTest_1369, ExceptionalCase_UnknownGroup_1369) {

    EXPECT_EQ(Exiv2::IfdId::ifdIdNotSet, Exiv2::Internal::groupId("UnknownGroupName"));

}



TEST_F(GroupIdTest_1369, NormalOperation_CanonMakerNoteGroup_1369) {

    EXPECT_EQ(Exiv2::IfdId::canonId, Exiv2::Internal::groupId("Canon"));

}



TEST_F(GroupIdTest_1369, NormalOperation_PanasonicRawGroup_1369) {

    EXPECT_EQ(Exiv2::IfdId::panaRawId, Exiv2::Internal::groupId("PanasonicRaw"));

}
