#include <gtest/gtest.h>

#include "tiffimage_int.hpp"



using namespace Exiv2::Internal;



class TiffHeaderBaseTest_1172 : public ::testing::Test {

protected:

    ByteOrder defaultByteOrder = ByteOrder::littleEndian;

    uint32_t defaultSize = 8;

    uint32_t defaultOffset = 0x100;

    uint16_t defaultTag = 0x112;



    TiffHeaderBase* tiffHeader;



    void SetUp() override {

        tiffHeader = new TiffHeaderBase(defaultTag, defaultSize, defaultByteOrder, defaultOffset);

    }



    void TearDown() override {

        delete tiffHeader;

    }

};



TEST_F(TiffHeaderBaseTest_1172, ByteOrderDefaultConstructor_1172) {

    EXPECT_EQ(tiffHeader->byteOrder(), defaultByteOrder);

}



TEST_F(TiffHeaderBaseTest_1172, SetByteOrderUpdatesValue_1172) {

    ByteOrder newByteOrder = ByteOrder::bigEndian;

    tiffHeader->setByteOrder(newByteOrder);

    EXPECT_EQ(tiffHeader->byteOrder(), newByteOrder);

}



TEST_F(TiffHeaderBaseTest_1172, OffsetDefaultConstructor_1172) {

    EXPECT_EQ(tiffHeader->offset(), defaultOffset);

}



TEST_F(TiffHeaderBaseTest_1172, SetOffsetUpdatesValue_1172) {

    uint32_t newOffset = 0x200;

    tiffHeader->setOffset(newOffset);

    EXPECT_EQ(tiffHeader->offset(), newOffset);

}



TEST_F(TiffHeaderBaseTest_1172, SizeDefaultConstructor_1172) {

    EXPECT_EQ(tiffHeader->size(), defaultSize);

}



TEST_F(TiffHeaderBaseTest_1172, TagDefaultConstructor_1172) {

    EXPECT_EQ(tiffHeader->tag(), defaultTag);

}



TEST_F(TiffHeaderBaseTest_1172, IsImageTagReturnsFalseForUnknownTag_1172) {

    uint16_t unknownTag = 0x999;

    IfdId group = IfdId::none;

    PrimaryGroups primaryGroups; // Assuming this is default-constructible

    EXPECT_FALSE(tiffHeader->isImageTag(unknownTag, group, primaryGroups));

}



TEST_F(TiffHeaderBaseTest_1172, ReadReturnsFalseForNullData_1172) {

    const byte* pData = nullptr;

    size_t size = 0;

    EXPECT_FALSE(tiffHeader->read(pData, size));

}



TEST_F(TiffHeaderBaseTest_1172, WriteCreatesNonEmptyBuffer_1172) {

    DataBuf buffer = tiffHeader->write();

    EXPECT_GT(buffer.size_, 0);

}



TEST_F(TiffHeaderBaseTest_1172, PrintDoesNotThrow_1172) {

    std::ostringstream os;

    const char* prefix = "TiffHeader: ";

    EXPECT_NO_THROW(tiffHeader->print(os, prefix));

}
