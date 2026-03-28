#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/tiffimage_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class FindExifdatumTest_1162 : public ::testing::Test {

protected:

    IfdId testIfdId = 0x8769; // Example IFD ID

    Exifdatum exifDatumWithMatchingIfd;

    Exifdatum exifDatumWithNonMatchingIfd;



    FindExifdatumTest_1162()

        : exifDatumWithMatchingIfd(ExifKey(), nullptr),

          exifDatumWithNonMatchingIfd(ExifKey(), nullptr) {

        // Mock ifdId() return value for exifDatumWithMatchingIfd

        EXPECT_CALL(exifDatumWithMatchingIfd, ifdId()).WillRepeatedly(::testing::Return(testIfdId));

        // Mock ifdId() return value for exifDatumWithNonMatchingIfd to a different IFD ID

        EXPECT_CALL(exifDatumWithNonMatchingIfd, ifdId()).WillRepeatedly(::testing::Return(0x8768));

    }

};



TEST_F(FindExifdatumTest_1162, MatchesCorrectIfd_1162) {

    FindExifdatum finder(testIfdId);

    EXPECT_TRUE(finder(exifDatumWithMatchingIfd));

}



TEST_F(FindExifdatumTest_1162, DoesNotMatchIncorrectIfd_1162) {

    FindExifdatum finder(testIfdId);

    EXPECT_FALSE(finder(exifDatumWithNonMatchingIfd));

}



TEST_F(FindExifdatumTest_1162, MatchesBoundaryCondition_1162) {

    IfdId boundaryIfdId = 0x0000; // Boundary condition: minimum possible IFD ID

    FindExifdatum finder(boundaryIfdId);

    Exifdatum exifDatumWithBoundaryIfd(ExifKey(), nullptr);

    EXPECT_CALL(exifDatumWithBoundaryIfd, ifdId()).WillRepeatedly(::testing::Return(boundaryIfdId));

    EXPECT_TRUE(finder(exifDatumWithBoundaryIfd));

}



TEST_F(FindExifdatumTest_1162, DoesNotMatchDifferentBoundaryCondition_1162) {

    IfdId boundaryIfdId = 0x0000; // Boundary condition: minimum possible IFD ID

    FindExifdatum finder(boundaryIfdId);

    Exifdatum exifDatumWithNonBoundaryIfd(ExifKey(), nullptr);

    EXPECT_CALL(exifDatumWithNonBoundaryIfd, ifdId()).WillRepeatedly(::testing::Return(testIfdId));

    EXPECT_FALSE(finder(exifDatumWithNonBoundaryIfd));

}
