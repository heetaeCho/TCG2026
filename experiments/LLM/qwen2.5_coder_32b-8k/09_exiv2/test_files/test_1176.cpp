#include <gtest/gtest.h>

#include "tiffimage_int.hpp"



using namespace Exiv2::Internal;



class TiffHeaderBaseTest_1176 : public ::testing::Test {

protected:

    ByteOrder byteOrder = littleEndian;

    uint32_t offset = 0x100;

    uint16_t tag = 0x112;

    uint32_t size = 4;



    TiffHeaderBase* tiffHeader;



    void SetUp() override {

        tiffHeader = new TiffHeaderBase(tag, size, byteOrder, offset);

    }



    void TearDown() override {

        delete tiffHeader;

    }

};



TEST_F(TiffHeaderBaseTest_1176, InitialSizeCorrect_1176) {

    EXPECT_EQ(tiffHeader->size(), size);

}



TEST_F(TiffHeaderBaseTest_1176, SetByteOrderChangesByteOrder_1176) {

    ByteOrder newByteOrder = bigEndian;

    tiffHeader->setByteOrder(newByteOrder);

    EXPECT_EQ(tiffHeader->byteOrder(), newByteOrder);

}



TEST_F(TiffHeaderBaseTest_1176, SetOffsetChangesOffset_1176) {

    uint32_t newOffset = 0x200;

    tiffHeader->setOffset(newOffset);

    EXPECT_EQ(tiffHeader->offset(), newOffset);

}



TEST_F(TiffHeaderBaseTest_1176, TagIsCorrect_1176) {

    EXPECT_EQ(tiffHeader->tag(), tag);

}



TEST_F(TiffHeaderBaseTest_1176, ReadFunctionReturnsFalseForInvalidData_1176) {

    byte invalidData[] = {0xFF, 0xFF, 0xFF};

    size_t dataSize = sizeof(invalidData) / sizeof(byte);

    EXPECT_FALSE(tiffHeader->read(invalidData, dataSize));

}



TEST_F(TiffHeaderBaseTest_1176, WriteFunctionReturnsNonEmptyBuffer_1176) {

    DataBuf buffer = tiffHeader->write();

    EXPECT_FALSE(buffer.empty());

}



TEST_F(TiffHeaderBaseTest_1176, IsImageTagReturnsFalseForArbitraryTag_1176) {

    PrimaryGroups primaryGroups;

    EXPECT_FALSE(tiffHeader->isImageTag(0x9999, ifd0Id, primaryGroups));

}
