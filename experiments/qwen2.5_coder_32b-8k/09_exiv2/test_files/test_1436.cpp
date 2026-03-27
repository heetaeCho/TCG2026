#include <gtest/gtest.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;



class OlympusMnHeaderTest : public ::testing::Test {

protected:

    OlympusMnHeader olympusMnHeader;

};



TEST_F(OlympusMnHeaderTest_1436, SizeOfSignature_ReturnsCorrectSize_1436) {

    EXPECT_EQ(olympusMnHeader.sizeOfSignature(), sizeof(signature_));

}



TEST_F(OlympusMnHeaderTest_1436, Size_ReturnsNonZeroForDefaultInstance_1436) {

    EXPECT_NE(olympusMnHeader.size(), 0);

}



TEST_F(OlympusMnHeaderTest_1436, IfdOffset_ReturnsZeroForDefaultInstance_1436) {

    EXPECT_EQ(olympusMnHeader.ifdOffset(), 0);

}



TEST_F(OlympusMnHeaderTest_1436, Read_ReturnsFalseForNullData_1436) {

    const byte* pData = nullptr;

    size_t size = 10;

    ByteOrder byteOrder = littleEndian;

    EXPECT_FALSE(olympusMnHeader.read(pData, size, byteOrder));

}



TEST_F(OlympusMnHeaderTest_1436, Read_ReturnsFalseForZeroSize_1436) {

    const byte* pData = reinterpret_cast<const byte*>("dummy data");

    size_t size = 0;

    ByteOrder byteOrder = littleEndian;

    EXPECT_FALSE(olympusMnHeader.read(pData, size, byteOrder));

}



TEST_F(OlympusMnHeaderTest_1436, Write_ReturnsNonZeroForValidIoWrapper_1436) {

    IoWrapper ioWrapper; // Assuming IoWrapper is default-constructible

    ByteOrder byteOrder = littleEndian;

    EXPECT_NE(olympusMnHeader.write(ioWrapper, byteOrder), 0);

}
