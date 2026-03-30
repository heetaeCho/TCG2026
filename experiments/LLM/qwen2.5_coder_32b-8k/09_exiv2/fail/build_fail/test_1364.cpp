#include <gtest/gtest.h>

#include "exiv2/tags.hpp"

#include "./TestProjects/exiv2/src/tags_int.cpp"



using namespace Exiv2::Internal;



TEST(isExifIfdTest_1364, ReturnsTrueForValidExifIFDs_1364) {

    EXPECT_TRUE(isExifIfd(IfdId::ifd0Id));

    EXPECT_TRUE(isExifIfd(IfdId::exifId));

    EXPECT_TRUE(isExifIfd(IfdId::gpsId));

    EXPECT_TRUE(isExifIfd(IfdId::iopId));

    EXPECT_TRUE(isExifIfd(IfdId::ifd1Id));

    EXPECT_TRUE(isExifIfd(IfdId::ifd2Id));

    EXPECT_TRUE(isExifIfd(IfdId::ifd3Id));

    EXPECT_TRUE(isExifIfd(IfdId::mpfId));

    EXPECT_TRUE(isExifIfd(IfdId::subImage1Id));

    EXPECT_TRUE(isExifIfd(IfdId::subImage2Id));

    EXPECT_TRUE(isExifIfd(IfdId::subImage3Id));

    EXPECT_TRUE(isExifIfd(IfdId::subImage4Id));

    EXPECT_TRUE(isExifIfd(IfdId::subImage5Id));

    EXPECT_TRUE(isExifIfd(IfdId::subImage6Id));

    EXPECT_TRUE(isExifIfd(IfdId::subImage7Id));

    EXPECT_TRUE(isExifIfd(IfdId::subImage8Id));

    EXPECT_TRUE(isExifIfd(IfdId::subImage9Id));

    EXPECT_TRUE(isExifIfd(IfdId::subThumb1Id));

    EXPECT_TRUE(isExifIfd(IfdId::panaRawId));

}



TEST(isExifIfdTest_1364, ReturnsFalseForInvalidExifIFDs_1364) {

    EXPECT_FALSE(isExifIfd(IfdId::mnId));

    EXPECT_FALSE(isExifIfd(IfdId::canonId));

    EXPECT_FALSE(isExifIfd(IfdId::casioId));

    EXPECT_FALSE(isExifIfd(IfdId::fujiId));

    EXPECT_FALSE(isExifIfd(IfdId::minoltaId));

    EXPECT_FALSE(isExifIfd(IfdId::nikon1Id));

    EXPECT_FALSE(isExifIfd(IfdId::olympusId));

    EXPECT_FALSE(isExifIfd(IfdId::panasonicId));

    EXPECT_FALSE(isExifIfd(IfdId::pentaxId));

    EXPECT_FALSE(isExifIfd(IfdId::sigmaId));

    EXPECT_FALSE(isExifIfd(IfdId::sony1Id));

    EXPECT_FALSE(isExifIfd(IfdId::tagInfoMvId));

    EXPECT_FALSE(isExifIfd(IfdId::ignoreId));

}



TEST(isExifIfdTest_1364, ReturnsFalseForUnsetIFD_1364) {

    EXPECT_FALSE(isExifIfd(IfdId::ifdIdNotSet));

}



TEST(isExifIfdTest_1364, ReturnsFalseForLastIFD_1364) {

    EXPECT_FALSE(isExifIfd(IfdId::lastId));

}
