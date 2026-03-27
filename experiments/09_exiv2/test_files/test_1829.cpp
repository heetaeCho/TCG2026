#include <gtest/gtest.h>

#include "exiv2/photoshop.hpp"

#include "exiv2/iptc.hpp"

#include "exiv2/types.hpp"



namespace Exiv2 {



class PhotoshopTest : public ::testing::Test {

protected:

    Photoshop ps;

    IptcData iptcData;

};



TEST_F(PhotoshopTest_1829, SetIptcIrb_EmptyInput_ReturnsEmptyDataBuf_1829) {

    const byte* pPsData = nullptr;

    size_t sizePsData = 0;

    DataBuf result = ps.setIptcIrb(pPsData, sizePsData, iptcData);

    EXPECT_TRUE(result.empty());

}



TEST_F(PhotoshopTest_1829, SetIptcIrb_NoIPTCInInput_ReturnsOriginalData_1829) {

    std::array<byte, 10> pPsData = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    size_t sizePsData = pPsData.size();

    DataBuf result = ps.setIptcIrb(pPsData.data(), sizePsData, iptcData);

    EXPECT_EQ(result.size(), sizePsData);

    EXPECT_TRUE(std::equal(pPsData.begin(), pPsData.end(), result.c_data()));

}



TEST_F(PhotoshopTest_1829, SetIptcIrb_ValidIPTCInInput_ReturnsModifiedData_1829) {

    std::array<byte, 10> pPsData = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    size_t sizePsData = pPsData.size();

    iptcData.add(IptcKey("Iptc.Application2.Caption"), new StringValue("Test Caption"));

    DataBuf result = ps.setIptcIrb(pPsData.data(), sizePsData, iptcData);

    EXPECT_FALSE(result.empty());

    EXPECT_NE(result.size(), sizePsData); // The result should be larger due to the added IPTC data

}



TEST_F(PhotoshopTest_1829, SetIptcIrb_LargeInput_ReturnsModifiedData_1829) {

    std::vector<byte> pPsData(1024, 0);

    size_t sizePsData = pPsData.size();

    iptcData.add(IptcKey("Iptc.Application2.Caption"), new StringValue("Test Caption"));

    DataBuf result = ps.setIptcIrb(pPsData.data(), sizePsData, iptcData);

    EXPECT_FALSE(result.empty());

    EXPECT_NE(result.size(), sizePsData); // The result should be larger due to the added IPTC data

}



TEST_F(PhotoshopTest_1829, SetIptcIrb_CorruptedMetadataThrowsException_1829) {

    std::array<byte, 10> pPsData = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    size_t sizePsData = pPsData.size();

    iptcData.add(IptcKey("Iptc.Application2.Caption"), new StringValue("Test Caption"));

    EXPECT_THROW({

        ps.setIptcIrb(pPsData.data(), -1, iptcData); // Negative size should trigger an error

    }, Exiv2::Error);

}



TEST_F(PhotoshopTest_1829, SetIptcIrb_IPTCDataEmpty_ReturnsOriginalData_1829) {

    std::array<byte, 10> pPsData = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    size_t sizePsData = pPsData.size();

    DataBuf result = ps.setIptcIrb(pPsData.data(), sizePsData, iptcData); // Empty IPTC data

    EXPECT_TRUE(result.empty());

}



TEST_F(PhotoshopTest_1829, SetIptcIrb_IPTCEncodingError_ReturnsEmptyDataBuf_1829) {

    std::array<byte, 10> pPsData = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    size_t sizePsData = pPsData.size();

    iptcData.add(IptcKey("Iptc.Application2.Caption"), new StringValue("\xFF")); // Invalid character

    DataBuf result = ps.setIptcIrb(pPsData.data(), sizePsData, iptcData);

    EXPECT_TRUE(result.empty());

}



}  // namespace Exiv2
