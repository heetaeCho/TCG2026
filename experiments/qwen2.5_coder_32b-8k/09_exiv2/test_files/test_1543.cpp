#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/cr2header_int.hpp"



namespace Exiv2 { namespace Internal {



class Cr2HeaderTest_1543 : public ::testing::Test {

protected:

    Cr2Header header_{ByteOrder::bigEndian};

};



TEST_F(Cr2HeaderTest_1543, Offset2Addr_ReturnsCorrectValue_1543) {

    EXPECT_EQ(Cr2Header::offset2addr(), 12u);

}



TEST_F(Cr2HeaderTest_1543, Read_WithValidData_ReturnsTrue_1543) {

    byte data[] = {0x00, 0x01, 0x02, 0x03};

    EXPECT_TRUE(header_.read(data, sizeof(data)));

}



TEST_F(Cr2HeaderTest_1543, Read_WithInvalidData_ReturnsFalse_1543) {

    byte data[] = {0xFF, 0xFE, 0xFD};

    EXPECT_FALSE(header_.read(data, sizeof(data)));

}



TEST_F(Cr2HeaderTest_1543, Write_ReturnsValidDataBuf_1543) {

    DataBuf dataBuf = header_.write();

    EXPECT_NE(dataBuf.pData_, nullptr);

    EXPECT_EQ(dataBuf.size_, 0u); // Assuming write returns an empty buffer if no data is set

}



TEST_F(Cr2HeaderTest_1543, IsImageTag_WithKnownImageTag_ReturnsTrue_1543) {

    uint16_t tag = 0x8769; // Example of a known image tag

    IfdId group = IfdId::ifdExif;

    PrimaryGroups primaryGroups;

    EXPECT_TRUE(header_.isImageTag(tag, group, primaryGroups));

}



TEST_F(Cr2HeaderTest_1543, IsImageTag_WithUnknownImageTag_ReturnsFalse_1543) {

    uint16_t tag = 0xFFFF; // Example of an unknown image tag

    IfdId group = IfdId::ifdExif;

    PrimaryGroups primaryGroups;

    EXPECT_FALSE(header_.isImageTag(tag, group, primaryGroups));

}



}} // namespace Exiv2::Internal
