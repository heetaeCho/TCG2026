#include <gtest/gtest.h>

#include "exiv2/photoshop.hpp"



namespace {



class PhotoshopTest : public ::testing::Test {

protected:

    Exiv2::Photoshop photoshop;

};



TEST_F(PhotoshopTest_1827, LocateIptcIrb_NormalOperation_1827) {

    const byte psData[] = { /* Mock data that contains a valid IPTC IRB */ };

    size_t sizePsData = sizeof(psData);

    const byte* record;

    uint32_t sizeHdr, sizeData;



    int result = photoshop.locateIptcIrb(psData, sizePsData, &record, sizeHdr, sizeData);



    EXPECT_EQ(result, 0); // Assuming 0 indicates success

    EXPECT_NE(record, nullptr);

    EXPECT_GT(sizeHdr, 0);

    EXPECT_GT(sizeData, 0);

}



TEST_F(PhotoshopTest_1827, LocateIptcIrb_NoIptcIrb_1827) {

    const byte psData[] = { /* Mock data that does not contain an IPTC IRB */ };

    size_t sizePsData = sizeof(psData);

    const byte* record;

    uint32_t sizeHdr, sizeData;



    int result = photoshop.locateIptcIrb(psData, sizePsData, &record, sizeHdr, sizeData);



    EXPECT_NE(result, 0); // Assuming non-zero indicates failure

    EXPECT_EQ(record, nullptr);

    EXPECT_EQ(sizeHdr, 0);

    EXPECT_EQ(sizeData, 0);

}



TEST_F(PhotoshopTest_1827, LocateIptcIrb_EmptyData_1827) {

    const byte psData[] = {};

    size_t sizePsData = sizeof(psData);

    const byte* record;

    uint32_t sizeHdr, sizeData;



    int result = photoshop.locateIptcIrb(psData, sizePsData, &record, sizeHdr, sizeData);



    EXPECT_NE(result, 0); // Assuming non-zero indicates failure

    EXPECT_EQ(record, nullptr);

    EXPECT_EQ(sizeHdr, 0);

    EXPECT_EQ(sizeData, 0);

}



TEST_F(PhotoshopTest_1827, LocateIptcIrb_BoundaryCondition_MaxSize_1827) {

    const byte psData[SIZE_MAX] = {}; // This will likely cause an issue due to size

    size_t sizePsData = sizeof(psData);

    const byte* record;

    uint32_t sizeHdr, sizeData;



    int result = photoshop.locateIptcIrb(psData, sizePsData, &record, sizeHdr, sizeData);



    EXPECT_NE(result, 0); // Assuming non-zero indicates failure due to invalid size

    EXPECT_EQ(record, nullptr);

    EXPECT_EQ(sizeHdr, 0);

    EXPECT_EQ(sizeData, 0);

}



} // namespace
