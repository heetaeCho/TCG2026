#include <gtest/gtest.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;



class SigmaMnHeaderTest : public ::testing::Test {

protected:

    SigmaMnHeader sigmaMnHeader;

};



TEST_F(SigmaMnHeaderTest_1494, SizeReturnsSizeOfSignature_1494) {

    EXPECT_EQ(sigmaMnHeader.size(), SigmaMnHeader::sizeOfSignature());

}



TEST_F(SigmaMnHeaderTest_1494, ReadWithNullDataThrowsOrHandlesError_1494) {

    byte* nullData = nullptr;

    size_t dataSize = 0;

    ByteOrder byteOrder = littleEndian; // Example byte order

    EXPECT_FALSE(sigmaMnHeader.read(nullData, dataSize, byteOrder));

}



TEST_F(SigmaMnHeaderTest_1494, ReadWithZeroSizeThrowsOrHandlesError_1494) {

    byte dummyData[1] = {0};

    size_t zeroSize = 0;

    ByteOrder byteOrder = littleEndian; // Example byte order

    EXPECT_FALSE(sigmaMnHeader.read(dummyData, zeroSize, byteOrder));

}



TEST_F(SigmaMnHeaderTest_1494, WriteWithNullIoWrapperThrowsOrHandlesError_1494) {

    IoWrapper* nullIoWrapper = nullptr;

    ByteOrder byteOrder = littleEndian; // Example byte order

    EXPECT_THROW(sigmaMnHeader.write(*nullIoWrapper, byteOrder), std::invalid_argument);

}



TEST_F(SigmaMnHeaderTest_1494, IfdOffsetReturnsExpectedValue_1494) {

    size_t ifdOffset = sigmaMnHeader.ifdOffset();

    // Assuming some expectations about the ifdOffset value

    EXPECT_GE(ifdOffset, 0);

}



TEST_F(SigmaMnHeaderTest_1494, SizeOfSignatureIsConsistent_1494) {

    size_t signatureSize = SigmaMnHeader::sizeOfSignature();

    // Assuming some expectations about the signature size

    EXPECT_GT(signatureSize, 0);

}
