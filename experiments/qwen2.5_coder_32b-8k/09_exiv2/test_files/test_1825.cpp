#include <gtest/gtest.h>

#include "exiv2/photoshop.hpp"



namespace Exiv2 {

    struct Photoshop;

}



TEST(PhotoshopTest_1825, Valid_ReturnsTrueForValidData_1825) {

    const uint8_t data[] = { /* Example valid Photoshop data */ };

    EXPECT_TRUE(Exiv2::Photoshop::valid(data, sizeof(data)));

}



TEST(PhotoshopTest_1825, Valid_ReturnsFalseForInvalidData_1825) {

    const uint8_t data[] = { /* Example invalid Photoshop data */ };

    EXPECT_FALSE(Exiv2::Photoshop::valid(data, sizeof(data)));

}



TEST(PhotoshopTest_1825, Valid_ReturnsTrueForEmptyData_1825) {

    const uint8_t data[] = {};

    EXPECT_TRUE(Exiv2::Photoshop::valid(data, sizeof(data)));

}



TEST(PhotoshopTest_1825, LocateIptcIrb_FindsIptcIrb_1825) {

    const uint8_t data[] = { /* Example Photoshop data containing IPTC IRB */ };

    const byte* record;

    uint32_t sizeHdr;

    uint32_t sizeData;

    EXPECT_EQ(0, Exiv2::Photoshop::locateIptcIrb(data, sizeof(data), &record, sizeHdr, sizeData));

}



TEST(PhotoshopTest_1825, LocateIptcIrb_ReturnsErrorForNoIptcIrb_1825) {

    const uint8_t data[] = { /* Example Photoshop data without IPTC IRB */ };

    const byte* record;

    uint32_t sizeHdr;

    uint32_t sizeData;

    EXPECT_NE(0, Exiv2::Photoshop::locateIptcIrb(data, sizeof(data), &record, sizeHdr, sizeData));

}



TEST(PhotoshopTest_1825, LocatePreviewIrb_FindsPreviewIrb_1825) {

    const uint8_t data[] = { /* Example Photoshop data containing Preview IRB */ };

    const byte* record;

    uint32_t sizeHdr;

    uint32_t sizeData;

    EXPECT_EQ(0, Exiv2::Photoshop::locatePreviewIrb(data, sizeof(data), &record, sizeHdr, sizeData));

}



TEST(PhotoshopTest_1825, LocatePreviewIrb_ReturnsErrorForNoPreviewIrb_1825) {

    const uint8_t data[] = { /* Example Photoshop data without Preview IRB */ };

    const byte* record;

    uint32_t sizeHdr;

    uint32_t sizeData;

    EXPECT_NE(0, Exiv2::Photoshop::locatePreviewIrb(data, sizeof(data), &record, sizeHdr, sizeData));

}



TEST(PhotoshopTest_1825, LocateIrb_FindsSpecificTag_1825) {

    const uint8_t data[] = { /* Example Photoshop data containing specific IRB tag */ };

    const byte* record;

    uint32_t sizeHdr;

    uint32_t sizeData;

    EXPECT_EQ(0, Exiv2::Photoshop::locateIrb(data, sizeof(data), 1234, &record, sizeHdr, sizeData));

}



TEST(PhotoshopTest_1825, LocateIrb_ReturnsErrorForUnknownTag_1825) {

    const uint8_t data[] = { /* Example Photoshop data without specific IRB tag */ };

    const byte* record;

    uint32_t sizeHdr;

    uint32_t sizeData;

    EXPECT_NE(0, Exiv2::Photoshop::locateIrb(data, sizeof(data), 1234, &record, sizeHdr, sizeData));

}



TEST(PhotoshopTest_1825, IsIrb_ReturnsTrueForIrbData_1825) {

    const uint8_t data[] = { /* Example IRB Photoshop data */ };

    EXPECT_TRUE(Exiv2::Photoshop::isIrb(data));

}



TEST(PhotoshopTest_1825, IsIrb_ReturnsFalseForNonIrbData_1825) {

    const uint8_t data[] = { /* Example non-IRB Photoshop data */ };

    EXPECT_FALSE(Exiv2::Photoshop::isIrb(data));

}
