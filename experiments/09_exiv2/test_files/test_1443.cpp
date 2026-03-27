#include <gtest/gtest.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;



class Olympus2MnHeaderTest_1443 : public ::testing::Test {

protected:

    Olympus2MnHeader header;

};



TEST_F(Olympus2MnHeaderTest_1443, IfdOffsetReturnsSizeOfSignature_1443) {

    EXPECT_EQ(header.ifdOffset(), header.sizeOfSignature());

}



TEST_F(Olympus2MnHeaderTest_1443, SizeOfSignatureIsConsistent_1443) {

    size_t size1 = Olympus2MnHeader::sizeOfSignature();

    size_t size2 = Olympus2MnHeader::sizeOfSignature();

    EXPECT_EQ(size1, size2);

}



TEST_F(Olympus2MnHeaderTest_1443, SizeReturnsPositiveValue_1443) {

    EXPECT_GT(header.size(), 0u);

}



TEST_F(Olympus2MnHeaderTest_1443, BaseOffsetCalculatesCorrectly_1443) {

    size_t mnOffset = 10;

    EXPECT_EQ(header.baseOffset(mnOffset), header.ifdOffset() + mnOffset);

}



// Assuming read and write methods can be tested for basic behavior

TEST_F(Olympus2MnHeaderTest_1443, ReadReturnsFalseForNullData_1443) {

    const byte* pData = nullptr;

    size_t size = 0;

    ByteOrder byteOrder = littleEndian; // or any valid ByteOrder value

    EXPECT_FALSE(header.read(pData, size, byteOrder));

}



TEST_F(Olympus2MnHeaderTest_1443, WriteReturnsNonZeroForValidIoWrapper_1443) {

    IoWrapper ioWrapper; // Assuming IoWrapper has a default constructor

    ByteOrder byteOrder = littleEndian; // or any valid ByteOrder value

    EXPECT_GT(header.write(ioWrapper, byteOrder), 0u);

}
