#include <gtest/gtest.h>

#include "tiffimage_int.hpp"



using namespace Exiv2::Internal;



class TiffHeaderBaseTest_1173 : public ::testing::Test {

protected:

    ByteOrder initialByteOrder = littleEndian;

    uint32_t initialSize = 16;

    uint16_t tag = 0x011A; // Example TIFF tag

    uint32_t offset = 42;



    std::unique_ptr<TiffHeaderBase> tiffHeader;



    void SetUp() override {

        tiffHeader = std::make_unique<TiffHeaderBase>(tag, initialSize, initialByteOrder, offset);

    }

};



TEST_F(TiffHeaderBaseTest_1173, InitialByteOrder_1173) {

    EXPECT_EQ(tiffHeader->byteOrder(), initialByteOrder);

}



TEST_F(TiffHeaderBaseTest_1173, SetByteOrder_1173) {

    tiffHeader->setByteOrder(bigEndian);

    EXPECT_EQ(tiffHeader->byteOrder(), bigEndian);

}



TEST_F(TiffHeaderBaseTest_1173, InitialSize_1173) {

    EXPECT_EQ(tiffHeader->size(), initialSize);

}



TEST_F(TiffHeaderBaseTest_1173, SetOffset_1173) {

    uint32_t newOffset = 100;

    tiffHeader->setOffset(newOffset);

    EXPECT_EQ(tiffHeader->offset(), newOffset);

}



TEST_F(TiffHeaderBaseTest_1173, TagValue_1173) {

    EXPECT_EQ(tiffHeader->tag(), tag);

}



TEST_F(TiffHeaderBaseTest_1173, IsImageTag_Default_1173) {

    PrimaryGroups primaryGroups;

    EXPECT_FALSE(tiffHeader->isImageTag(tag, IfdId::ifd0Id, primaryGroups));

}



// Assuming read and write are observable through side effects or return values

// Since we don't have details, we can test for basic functionality



TEST_F(TiffHeaderBaseTest_1173, Read_ReturnsFalseForInvalidData_1173) {

    const byte invalidData[] = {0xFF, 0xFE};

    EXPECT_FALSE(tiffHeader->read(invalidData, sizeof(invalidData)));

}



TEST_F(TiffHeaderBaseTest_1173, Write_ReturnsNonEmptyBuffer_1173) {

    DataBuf data = tiffHeader->write();

    EXPECT_FALSE(data.empty());

}
