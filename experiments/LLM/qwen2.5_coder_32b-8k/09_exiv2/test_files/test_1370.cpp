#include <gtest/gtest.h>

#include "exiv2/tags.hpp"

#include "./TestProjects/exiv2/src/tags_int.cpp"



namespace Exiv2 {

namespace Internal {



class IfdNameTest : public ::testing::Test {

protected:

    // Setup and teardown can be done here if needed

};



TEST_F(IfdNameTest_1370, KnownIfdId_ReturnsCorrectName_1370) {

    EXPECT_STREQ(ifdName(IfdId::ifd0Id), "IFD0");

}



TEST_F(IfdNameTest_1370, AnotherKnownIfdId_ReturnsCorrectName_1370) {

    EXPECT_STREQ(ifdName(IfdId::exifId), "Exif");

}



TEST_F(IfdNameTest_1370, BoundaryCondition_FirstElement_ReturnsCorrectName_1370) {

    EXPECT_STREQ(ifdName(IfdId::ifdIdNotSet), "Unknown IFD");

}



TEST_F(IfdNameTest_1370, BoundaryCondition_LastElement_ReturnsCorrectName_1370) {

    EXPECT_STREQ(ifdName(IfdId::lastId), "(Last IFD info)");

}



TEST_F(IfdNameTest_1370, UnknownIfdId_ReturnsDefaultName_1370) {

    IfdId unknownId = static_cast<IfdId>(999); // Assuming 999 is not a valid IfdId in the provided list

    EXPECT_STREQ(ifdName(unknownId), "Unknown IFD");

}



} // namespace Internal

} // namespace Exiv2
