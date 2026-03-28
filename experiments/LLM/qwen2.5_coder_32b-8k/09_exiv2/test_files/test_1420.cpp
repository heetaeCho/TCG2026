#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/tags_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class PrintGPSDirRefTest_1420 : public ::testing::Test {

protected:

    std::ostringstream os;

    Value value;

    const ExifData* metadata = nullptr;

};



TEST_F(PrintGPSDirRefTest_1420, ValidTrueDirection_1420) {

    // Arrange

    value.setDataArea(reinterpret_cast<const byte*>("T"), 1);



    // Act

    std::ostream& result = printGPSDirRef(os, value, metadata);



    // Assert

    EXPECT_EQ(result.str(), "True direction");

}



TEST_F(PrintGPSDirRefTest_1420, ValidMagneticDirection_1420) {

    // Arrange

    value.setDataArea(reinterpret_cast<const byte*>("M"), 1);



    // Act

    std::ostream& result = printGPSDirRef(os, value, metadata);



    // Assert

    EXPECT_EQ(result.str(), "Magnetic direction");

}



TEST_F(PrintGPSDirRefTest_1420, InvalidDirection_1420) {

    // Arrange

    value.setDataArea(reinterpret_cast<const byte*>("X"), 1);



    // Act

    std::ostream& result = printGPSDirRef(os, value, metadata);



    // Assert

    EXPECT_EQ(result.str(), "");

}



TEST_F(PrintGPSDirRefTest_1420, EmptyValue_1420) {

    // Arrange

    value.setDataArea(nullptr, 0);



    // Act

    std::ostream& result = printGPSDirRef(os, value, metadata);



    // Assert

    EXPECT_EQ(result.str(), "");

}



TEST_F(PrintGPSDirRefTest_1420, NullMetadata_1420) {

    // Arrange

    value.setDataArea(reinterpret_cast<const byte*>("T"), 1);

    metadata = nullptr;



    // Act

    std::ostream& result = printGPSDirRef(os, value, metadata);



    // Assert

    EXPECT_EQ(result.str(), "True direction");

}
