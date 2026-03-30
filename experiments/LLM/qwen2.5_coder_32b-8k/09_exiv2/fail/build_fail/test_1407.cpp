#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "TestProjects/exiv2/src/tags_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class Print0xa001Test_1407 : public ::testing::Test {

protected:

    std::ostringstream os;

    Value value;

    const ExifData* metadata = nullptr;

};



TEST_F(Print0xa001Test_1407, NormalOperation_sRGB_1407) {

    // Arrange

    value.setDataArea(reinterpret_cast<const byte*>(&exifColorSpace[0].value_), sizeof(exifColorSpace[0].value_));

    

    // Act

    print0xa001(os, value, metadata);



    // Assert

    EXPECT_EQ(os.str(), "sRGB");

}



TEST_F(Print0xa001Test_1407, NormalOperation_AdobeRGB_1407) {

    // Arrange

    value.setDataArea(reinterpret_cast<const byte*>(&exifColorSpace[1].value_), sizeof(exifColorSpace[1].value_));

    

    // Act

    print0xa001(os, value, metadata);



    // Assert

    EXPECT_EQ(os.str(), "Adobe RGB");

}



TEST_F(Print0xa001Test_1407, NormalOperation_Uncalibrated_1407) {

    // Arrange

    value.setDataArea(reinterpret_cast<const byte*>(&exifColorSpace[2].value_), sizeof(exifColorSpace[2].value_));

    

    // Act

    print0xa001(os, value, metadata);



    // Assert

    EXPECT_EQ(os.str(), "Uncalibrated");

}



TEST_F(Print0xa001Test_1407, BoundaryCondition_InvalidValue_1407) {

    // Arrange

    uint32_t invalidValue = 9999;

    value.setDataArea(reinterpret_cast<const byte*>(&invalidValue), sizeof(invalidValue));

    

    // Act

    print0xa001(os, value, metadata);



    // Assert

    EXPECT_EQ(os.str(), "");

}



TEST_F(Print0xa001Test_1407, BoundaryCondition_ZeroValue_1407) {

    // Arrange

    uint32_t zeroValue = 0;

    value.setDataArea(reinterpret_cast<const byte*>(&zeroValue), sizeof(zeroValue));

    

    // Act

    print0xa001(os, value, metadata);



    // Assert

    EXPECT_EQ(os.str(), "");

}



TEST_F(Print0xa001Test_1407, BoundaryCondition_MaxUInt32Value_1407) {

    // Arrange

    uint32_t maxUInt32 = 4294967295;

    value.setDataArea(reinterpret_cast<const byte*>(&maxUInt32), sizeof(maxUInt32));

    

    // Act

    print0xa001(os, value, metadata);



    // Assert

    EXPECT_EQ(os.str(), "Uncalibrated");

}
