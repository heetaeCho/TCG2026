#include <gtest/gtest.h>

#include "exiv2/types.hpp"

#include "tiffimage_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class TiffHeaderBaseTest : public ::testing::Test {

protected:

    ByteOrder byteOrder_ = littleEndian;

    uint16_t tag_ = 0x4D4D; // Example tag

    uint32_t size_ = 8;

    uint32_t offset_ = 0;



    TiffHeaderBase* header_;



    void SetUp() override {

        header_ = new TiffHeaderBase(tag_, size_, byteOrder_, offset_);

    }



    void TearDown() override {

        delete header_;

    }

};



TEST_F(TiffHeaderBaseTest, WriteLittleEndian_1170) {

    DataBuf buffer = header_->write();

    EXPECT_EQ(buffer.size(), 8);

    EXPECT_EQ(buffer.read_uint8(0), 'I'); // littleEndian should write 'I'

    EXPECT_EQ(buffer.read_uint8(1), 'I');

    EXPECT_EQ(buffer.read_uint16(2, byteOrder_), tag_);

    EXPECT_EQ(buffer.read_uint32(4, byteOrder_), 0x00000008);

}



TEST_F(TiffHeaderBaseTest, WriteBigEndian_1170) {

    header_->setByteOrder(bigEndian);

    DataBuf buffer = header_->write();

    EXPECT_EQ(buffer.size(), 8);

    EXPECT_EQ(buffer.read_uint8(0), 'M'); // bigEndian should write 'M'

    EXPECT_EQ(buffer.read_uint8(1), 'M');

    EXPECT_EQ(buffer.read_uint16(2, byteOrder_), tag_);

    EXPECT_EQ(buffer.read_uint32(4, byteOrder_), 0x00000008);

}



TEST_F(TiffHeaderBaseTest, WriteInvalidByteOrder_1170) {

    header_->setByteOrder(invalidByteOrder);

    DataBuf buffer = header_->write();

    EXPECT_EQ(buffer.size(), 8);

    EXPECT_NE(buffer.read_uint8(0), 'I'); // invalidByteOrder should not write 'I'

    EXPECT_NE(buffer.read_uint8(0), 'M'); // invalidByteOrder should not write 'M'

    EXPECT_EQ(buffer.read_uint16(2, byteOrder_), tag_);

    EXPECT_EQ(buffer.read_uint32(4, byteOrder_), 0x00000008);

}



TEST_F(TiffHeaderBaseTest, SetAndGetByteOrder_1170) {

    header_->setByteOrder(bigEndian);

    EXPECT_EQ(header_->byteOrder(), bigEndian);



    header_->setByteOrder(littleEndian);

    EXPECT_EQ(header_->byteOrder(), littleEndian);



    header_->setByteOrder(invalidByteOrder);

    EXPECT_EQ(header_->byteOrder(), invalidByteOrder);

}



TEST_F(TiffHeaderBaseTest, SetAndGetOffset_1170) {

    uint32_t newOffset = 4;

    header_->setOffset(newOffset);

    EXPECT_EQ(header_->offset(), newOffset);

}



TEST_F(TiffHeaderBaseTest, SetAndGetTag_1170) {

    uint16_t newTag = 0x1234;

    header_->setTag(newTag);

    EXPECT_EQ(header_->tag(), newTag);

}



// Note: The following tests assume that the interface provides a way to set these values

// Since there is no setter for size in the provided interface, we can't test it directly.

// Similarly, `isImageTag` and `print` are not tested as they are not fully defined.



TEST_F(TiffHeaderBaseTest, BoundaryConditionByteOrder_1170) {

    header_->setByteOrder(static_cast<ByteOrder>(3)); // Assuming invalid value

    EXPECT_EQ(header_->byteOrder(), static_cast<ByteOrder>(3));

}
