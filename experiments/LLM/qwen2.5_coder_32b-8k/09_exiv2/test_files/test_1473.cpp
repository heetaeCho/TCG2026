#include <gtest/gtest.h>

#include "./TestProjects/exiv2/src/makernote_int.hpp"

#include <gmock/gmock.h>



using namespace Exiv2::Internal;



class PanasonicMnHeaderTest_1473 : public ::testing::Test {

protected:

    PanasonicMnHeader header;

};



TEST_F(PanasonicMnHeaderTest_1473, SizeOfSignature_ReturnsCorrectSize_1473) {

    size_t expectedSize = sizeof(header.signature_);

    EXPECT_EQ(expectedSize, header.sizeOfSignature());

}



TEST_F(PanasonicMnHeaderTest_1473, Size_ReturnsExpectedValue_1473) {

    // Assuming default constructor initializes a specific size

    EXPECT_EQ(0u, header.size()); // This is an assumption based on observable behavior

}



TEST_F(PanasonicMnHeaderTest_1473, IfdOffset_ReturnsExpectedValue_1473) {

    // Assuming default constructor initializes ifdOffset to a specific value

    EXPECT_EQ(0u, header.ifdOffset()); // This is an assumption based on observable behavior

}



TEST_F(PanasonicMnHeaderTest_1473, Read_ReturnsFalseOnInvalidData_1473) {

    byte data[] = {0x00};

    ByteOrder byteOrder = littleEndian; // Example value

    EXPECT_FALSE(header.read(data, 0, byteOrder)); // Invalid size should return false

}



TEST_F(PanasonicMnHeaderTest_1473, Write_ReturnsZeroOnInvalidIoWrapper_1473) {

    IoWrapper ioWrapper; // Assuming default constructed IoWrapper is invalid

    ByteOrder byteOrder = littleEndian; // Example value

    EXPECT_EQ(0u, header.write(ioWrapper, byteOrder)); // Invalid IoWrapper should return 0

}
