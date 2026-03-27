#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class PrintNormalSoftHardTest_1421 : public ::testing::Test {

protected:

    std::ostringstream os_;

    Value value_{TypeId::shortType}; // Assuming short type for testing

    ExifData metadata_;



    void SetUp() override {

        // Initialize value_ with a known state if necessary

        value_.setDataArea(reinterpret_cast<const byte*>(&exifNormalSoftHard[0].value_), sizeof(exifNormalSoftHard[0].value_));

    }

};



TEST_F(PrintNormalSoftHardTest_1421, NormalOperation_1421) {

    // Arrange

    value_.setDataArea(reinterpret_cast<const byte*>(&exifNormalSoftHard[1].value_), sizeof(exifNormalSoftHard[1].value_));



    // Act

    printNormalSoftHard(os_, value_, &metadata_);



    // Assert

    EXPECT_EQ(os_.str(), "Soft");

}



TEST_F(PrintNormalSoftHardTest_1421, BoundaryCondition_LowerBound_1421) {

    // Arrange

    value_.setDataArea(reinterpret_cast<const byte*>(&exifNormalSoftHard[0].value_), sizeof(exifNormalSoftHard[0].value_));



    // Act

    printNormalSoftHard(os_, value_, &metadata_);



    // Assert

    EXPECT_EQ(os_.str(), "Normal");

}



TEST_F(PrintNormalSoftHardTest_1421, BoundaryCondition_UpperBound_1421) {

    // Arrange

    value_.setDataArea(reinterpret_cast<const byte*>(&exifNormalSoftHard[2].value_), sizeof(exifNormalSoftHard[2].value_));



    // Act

    printNormalSoftHard(os_, value_, &metadata_);



    // Assert

    EXPECT_EQ(os_.str(), "Hard");

}



TEST_F(PrintNormalSoftHardTest_1421, ExceptionalCase_OutOfBounds_1421) {

    // Arrange

    short outOfBoundsValue = 3; // Assuming short type for testing and 3 is out of bounds

    value_.setDataArea(reinterpret_cast<const byte*>(&outOfBoundsValue), sizeof(outOfBoundsValue));



    // Act

    printNormalSoftHard(os_, value_, &metadata_);



    // Assert

    EXPECT_TRUE(os_.str().empty() || os_.str() == ""); // Assuming no output or empty string for out of bounds

}



TEST_F(PrintNormalSoftHardTest_1421, ExternalInteraction_MetadataNullptr_1421) {

    // Arrange

    value_.setDataArea(reinterpret_cast<const byte*>(&exifNormalSoftHard[0].value_), sizeof(exifNormalSoftHard[0].value_));



    // Act

    printNormalSoftHard(os_, value_, nullptr);



    // Assert

    EXPECT_EQ(os_.str(), "Normal");

}
