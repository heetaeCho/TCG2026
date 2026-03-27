#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/crwimage_int.cpp"



using namespace Exiv2::Internal;



class CiffComponentTest_1791 : public ::testing::Test {

protected:

    CrwDirs crwDirs;

    uint16_t crwTagId = 0x0001;

    CiffComponent ciffComponent;

};



TEST_F(CiffComponentTest_1791, DoAddThrowsError_1791) {

    EXPECT_THROW(ciffComponent.doAdd(crwDirs, crwTagId), Exiv2::Error);

}



TEST_F(CiffComponentTest_1791, DoAddThrowsSpecificErrorCode_1791) {

    try {

        ciffComponent.doAdd(crwDirs, crwTagId);

        FAIL() << "Expected an exception to be thrown";

    } catch (const Exiv2::Error& e) {

        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerFunctionNotSupported);

    }

}



TEST_F(CiffComponentTest_1791, DoAddThrowsSpecificErrorMessage_1791) {

    try {

        ciffComponent.doAdd(crwDirs, crwTagId);

        FAIL() << "Expected an exception to be thrown";

    } catch (const Exiv2::Error& e) {

        EXPECT_STREQ(e.what(), "CiffEntry::doAdd");

    }

}



TEST_F(CiffComponentTest_1791, DoAddBoundaryCondition_1791) {

    uint16_t boundaryTagId = 0xFFFF; // Boundary condition test for maximum uint16_t value

    EXPECT_THROW(ciffComponent.doAdd(crwDirs, boundaryTagId), Exiv2::Error);

}



TEST_F(CiffComponentTest_1791, DoAddZeroTagId_1791) {

    uint16_t zeroTagId = 0x0000; // Boundary condition test for minimum uint16_t value

    EXPECT_THROW(ciffComponent.doAdd(crwDirs, zeroTagId), Exiv2::Error);

}
