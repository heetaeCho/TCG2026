#include <gtest/gtest.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;



class Nikon2MnHeaderTest_1460 : public ::testing::Test {

protected:

    Nikon2MnHeader header;

};



TEST_F(Nikon2MnHeaderTest_1460, SizeOfSignature_ReturnsCorrectSize_1460) {

    EXPECT_EQ(header.sizeOfSignature(), sizeof(header.signature_));

}



TEST_F(Nikon2MnHeaderTest_1460, Read_WithValidData_ReturnsTrue_1460) {

    const byte data[] = { 0x01, 0x02, 0x03 };

    EXPECT_TRUE(header.read(data, sizeof(data), littleEndian));

}



TEST_F(Nikon2MnHeaderTest_1460, Read_WithNullData_ReturnsFalse_1460) {

    EXPECT_FALSE(header.read(nullptr, 0, littleEndian));

}



TEST_F(Nikon2MnHeaderTest_1460, Size_ReturnsNonZeroSize_1460) {

    EXPECT_GT(header.size(), 0);

}



TEST_F(Nikon2MnHeaderTest_1460, IfdOffset_ReturnsValidOffset_1460) {

    EXPECT_GE(header.ifdOffset(), 0);

}



TEST_F(Nikon2MnHeaderTest_1460, Write_WithValidIoWrapper_ReturnsNonZeroSize_1460) {

    IoWrapper ioWrapper;

    EXPECT_GT(header.write(ioWrapper, littleEndian), 0);

}
