#include <gtest/gtest.h>

#include "exiv2/photoshop.hpp"



namespace Exiv2 {

    struct Photoshop;

}



TEST(PhotoshopTest_1826, LocateIrb_Returns3_WhenSizePsDataLessThan12_1826) {

    const byte* pPsData = nullptr;

    size_t sizePsData = 10;

    uint16_t psTag = 0x4949; // Example tag

    const byte** record = nullptr;

    uint32_t sizeHdr = 0;

    uint32_t sizeData = 0;



    int result = Exiv2::Photoshop::locateIrb(pPsData, sizePsData, psTag, record, sizeHdr, sizeData);

    EXPECT_EQ(result, 3);

}



TEST(PhotoshopTest_1826, LocateIrb_ReturnsMinus2_WhenInvalidPosition_1826) {

    byte data[] = {0x8B, 0x49, 0x4D, 0x04}; // Not enough data to form a valid IRB

    size_t sizePsData = sizeof(data);

    uint16_t psTag = 0x4949; // Example tag

    const byte** record = nullptr;

    uint32_t sizeHdr = 0;

    uint32_t sizeData = 0;



    int result = Exiv2::Photoshop::locateIrb(data, sizePsData, psTag, record, sizeHdr, sizeData);

    EXPECT_EQ(result, -2);

}



TEST(PhotoshopTest_1826, LocateIrb_ReturnsMinus2_WhenDataSizeExceedsRemainingData_1826) {

    byte data[] = {0x8B, 0x49, 0x4D, 0x04, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0xFF, 0xFF}; // Large dataSize

    size_t sizePsData = sizeof(data);

    uint16_t psTag = 0x4949; // Example tag

    const byte** record = nullptr;

    uint32_t sizeHdr = 0;

    uint32_t sizeData = 0;



    int result = Exiv2::Photoshop::locateIrb(data, sizePsData, psTag, record, sizeHdr, sizeData);

    EXPECT_EQ(result, -2);

}



TEST(PhotoshopTest_1826, LocateIrb_Returns0_WhenValidIRBFound_1826) {

    byte data[] = {0x8B, 0x49, 0x4D, 0x04, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x0A, 0x00}; // Valid IRB

    size_t sizePsData = sizeof(data);

    uint16_t psTag = 0x0001; // Matching tag

    const byte** record = nullptr;

    uint32_t sizeHdr = 0;

    uint32_t sizeData = 0;



    int result = Exiv2::Photoshop::locateIrb(data, sizePsData, psTag, record, sizeHdr, sizeData);

    EXPECT_EQ(result, 0);

    EXPECT_NE(record, nullptr);

    EXPECT_EQ(sizeHdr, 14U); // 10 + 4 (psSize + 10)

    EXPECT_EQ(sizeData, 10U);

}



TEST(PhotoshopTest_1826, LocateIrb_Returns3_WhenNoMatchingTagFound_1826) {

    byte data[] = {0x8B, 0x49, 0x4D, 0x04, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x0A, 0x00}; // Valid IRB

    size_t sizePsData = sizeof(data);

    uint16_t psTag = 0xFFFF; // Non-matching tag

    const byte** record = nullptr;

    uint32_t sizeHdr = 0;

    uint32_t sizeData = 0;



    int result = Exiv2::Photoshop::locateIrb(data, sizePsData, psTag, record, sizeHdr, sizeData);

    EXPECT_EQ(result, 3);

}
