#include <gtest/gtest.h>

#include "exiv2/photoshop.hpp"



using namespace Exiv2;



// Test fixture for Photoshop class tests.

class PhotoshopTest_1824 : public ::testing::Test {

protected:

    // Setup and teardown can be done here if needed.

};



TEST_F(PhotoshopTest_1824, IsIrb_ReturnsFalseForNullPointer_1824) {

    EXPECT_FALSE(Photoshop::isIrb(nullptr));

}



TEST_F(PhotoshopTest_1824, IsIrb_ReturnsTrueForValidIrbData_1824) {

    const byte validIrbData[] = { '8B', 'IM', 0x04, 0x04 }; // Example IRB identifier

    EXPECT_TRUE(Photoshop::isIrb(validIrbData));

}



TEST_F(PhotoshopTest_1824, IsIrb_ReturnsFalseForInvalidIrbData_1824) {

    const byte invalidIrbData[] = { 0x00, 0x00, 0x00, 0x00 }; // Invalid IRB identifier

    EXPECT_FALSE(Photoshop::isIrb(invalidIrbData));

}



TEST_F(PhotoshopTest_1824, Valid_ReturnsFalseForNullPointer_1824) {

    EXPECT_FALSE(Photoshop::valid(nullptr, 0));

}



TEST_F(PhotoshopTest_1824, Valid_ReturnsTrueForValidData_1824) {

    const byte validData[] = { '8B', 'IM', 0x04, 0x04 }; // Example IRB identifier

    EXPECT_TRUE(Photoshop::valid(validData, sizeof(validData)));

}



TEST_F(PhotoshopTest_1824, Valid_ReturnsFalseForInvalidData_1824) {

    const byte invalidData[] = { 0x00, 0x00, 0x00, 0x00 }; // Invalid IRB identifier

    EXPECT_FALSE(Photoshop::valid(invalidData, sizeof(invalidData)));

}



TEST_F(PhotoshopTest_1824, LocateIrb_ReturnsErrorForNullPointer_1824) {

    const byte* record;

    uint32_t sizeHdr = 0;

    uint32_t sizeData = 0;

    EXPECT_EQ(-1, Photoshop::locateIrb(nullptr, 0, 0x00, &record, sizeHdr, sizeData));

}



TEST_F(PhotoshopTest_1824, LocateIrb_ReturnsSuccessForValidData_1824) {

    const byte validData[] = { '8B', 'IM', 0x04, 0x04 }; // Example IRB identifier

    const byte* record;

    uint32_t sizeHdr = 0;

    uint32_t sizeData = 0;

    EXPECT_EQ(0, Photoshop::locateIrb(validData, sizeof(validData), 0x00, &record, sizeHdr, sizeData));

}



TEST_F(PhotoshopTest_1824, LocateIptcIrb_ReturnsErrorForNullPointer_1824) {

    const byte* record;

    uint32_t sizeHdr = 0;

    uint32_t sizeData = 0;

    EXPECT_EQ(-1, Photoshop::locateIptcIrb(nullptr, 0, &record, sizeHdr, sizeData));

}



TEST_F(PhotoshopTest_1824, LocatePreviewIrb_ReturnsErrorForNullPointer_1824) {

    const byte* record;

    uint32_t sizeHdr = 0;

    uint32_t sizeData = 0;

    EXPECT_EQ(-1, Photoshop::locatePreviewIrb(nullptr, 0, &record, sizeHdr, sizeData));

}



TEST_F(PhotoshopTest_1824, SetIptcIrb_ReturnsValidDataBufForNullPointer_1824) {

    IptcData iptcData;

    DataBuf dataBuf = Photoshop::setIptcIrb(nullptr, 0, iptcData);

    EXPECT_TRUE(dataBuf.size_ > 0);

}



TEST_F(PhotoshopTest_1824, SetIptcIrb_ReturnsValidDataBufForValidData_1824) {

    const byte validData[] = { '8B', 'IM', 0x04, 0x04 }; // Example IRB identifier

    IptcData iptcData;

    DataBuf dataBuf = Photoshop::setIptcIrb(validData, sizeof(validData), iptcData);

    EXPECT_TRUE(dataBuf.size_ > 0);

}
