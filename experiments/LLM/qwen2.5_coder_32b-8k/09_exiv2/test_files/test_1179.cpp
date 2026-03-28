#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



namespace Exiv2 {

namespace Internal {



// Mocking or stubbing the isTiffImageTagLookup function for testing purposes.

// Since we cannot modify the internal implementation, this is a hypothetical

// way to expose it for testing. In practice, you would need access to the

// function or refactor the code to make it testable.



bool isTiffImageTagLookup(uint16_t tag, IfdId group);



}  // namespace Internal

}  // namespace Exiv2



using namespace Exiv2;

using namespace Exiv2::Internal;



TEST(isTiffImageTagLookupTest_1179, ValidIfd0TagsReturnTrue_1179) {

    EXPECT_TRUE(isTiffImageTagLookup(0x00fe, IfdId::ifd0Id)); // NewSubfileType

    EXPECT_TRUE(isTiffImageTagLookup(0x0100, IfdId::ifd0Id)); // ImageWidth

    EXPECT_TRUE(isTiffImageTagLookup(0x828e, IfdId::ifd0Id)); // CFAPattern

}



TEST(isTiffImageTagLookupTest_1179, InvalidIfd0TagsReturnFalse_1179) {

    EXPECT_FALSE(isTiffImageTagLookup(0x00fe, IfdId::ifd1Id)); // NewSubfileType in ifd1

    EXPECT_FALSE(isTiffImageTagLookup(0xffff, IfdId::ifd0Id)); // Invalid tag

}



TEST(isTiffImageTagLookupTest_1179, NonIfd0GroupReturnsFalse_1179) {

    EXPECT_FALSE(isTiffImageTagLookup(0x00fe, IfdId::exifId));  // NewSubfileType in exif

    EXPECT_FALSE(isTiffImageTagLookup(0x0100, IfdId::gpsId));   // ImageWidth in gps

}



TEST(isTiffImageTagLookupTest_1179, BoundaryConditionTagsReturnTrue_1179) {

    EXPECT_TRUE(isTiffImageTagLookup(0x00fe, IfdId::ifd0Id));  // First valid tag

    EXPECT_TRUE(isTiffImageTagLookup(0x828e, IfdId::ifd0Id));  // Last valid tag in list

}



TEST(isTiffImageTagLookupTest_1179, BoundaryConditionTagsReturnFalse_1179) {

    EXPECT_FALSE(isTiffImageTagLookup(0x00fd, IfdId::ifd0Id)); // Before first valid tag

    EXPECT_FALSE(isTiffImageTagLookup(0x828f, IfdId::ifd0Id)); // After last valid tag

}
