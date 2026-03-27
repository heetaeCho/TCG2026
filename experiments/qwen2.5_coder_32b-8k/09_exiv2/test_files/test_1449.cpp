#include <gtest/gtest.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;



class OMSystemMnHeaderTest : public ::testing::Test {

protected:

    OMSystemMnHeader header;

};



TEST_F(OMSystemMnHeaderTest_1449, IfdOffsetReturnsSizeOfSignature_1449) {

    EXPECT_EQ(header.ifdOffset(), OMSystemMnHeader::sizeOfSignature());

}



TEST_F(OMSystemMnHeaderTest_1449, SizeOfSignatureIsConsistent_1449) {

    size_t signatureSize = OMSystemMnHeader::sizeOfSignature();

    EXPECT_EQ(signatureSize, OMSystemMnHeader::sizeOfSignature()); // Ensure it's consistent

}



TEST_F(OMSystemMnHeaderTest_1449, BaseOffsetCalculatesCorrectly_1449) {

    size_t mnOffset = 10;

    EXPECT_EQ(header.baseOffset(mnOffset), header.ifdOffset() + mnOffset);

}



TEST_F(OMSystemMnHeaderTest_1449, ReadFunctionExists_1449) {

    const byte* pData = nullptr;

    size_t size = 0;

    ByteOrder byteOrder = littleEndian; // Example value

    EXPECT_NO_THROW(header.read(pData, size, byteOrder));

}



TEST_F(OMSystemMnHeaderTest_1449, WriteFunctionExists_1449) {

    IoWrapper ioWrapper; // Assuming default constructor exists and is valid for this context

    ByteOrder byteOrder = littleEndian; // Example value

    EXPECT_NO_THROW(header.write(ioWrapper, byteOrder));

}



TEST_F(OMSystemMnHeaderTest_1449, SizeFunctionExists_1449) {

    EXPECT_NO_THROW(header.size());

}
