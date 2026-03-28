#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



namespace Exiv2 {

namespace Internal {



TEST(groupNameTest_1371, NormalOperation_Ifd0Id_1371) {

    EXPECT_STREQ(groupName(IfdId::ifd0Id), "Image");

}



TEST(groupNameTest_1371, NormalOperation_ExifId_1371) {

    EXPECT_STREQ(groupName(IfdId::exifId), "Photo");

}



TEST(groupNameTest_1371, NormalOperation_GpsId_1371) {

    EXPECT_STREQ(groupName(IfdId::gpsId), "GPSInfo");

}



TEST(groupNameTest_1371, NormalOperation_IopId_1371) {

    EXPECT_STREQ(groupName(IfdId::iopId), "Iop");

}



TEST(groupNameTest_1371, BoundaryCondition_FirstEntry_1371) {

    EXPECT_STREQ(groupName(IfdId::ifdIdNotSet), "Unknown");

}



TEST(groupNameTest_1371, BoundaryCondition_LastEntry_1371) {

    EXPECT_STREQ(groupName(IfdId::lastId), "(Last IFD item)");

}



TEST(groupNameTest_1371, UnrecognizedIfdId_ReturnsFirstGroupName_1371) {

    EXPECT_STREQ(groupName(static_cast<IfdId>(-1)), "Unknown");

    EXPECT_STREQ(groupName(static_cast<IfdId>(999)), "Unknown");

}



}  // namespace Internal

}  // namespace Exiv2
