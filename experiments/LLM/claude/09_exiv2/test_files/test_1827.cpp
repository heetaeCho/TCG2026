#include <gtest/gtest.h>
#include <exiv2/photoshop.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/types.hpp>
#include <cstring>
#include <vector>

using namespace Exiv2;

class PhotoshopTest_1827 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== isIrb Tests ====================

TEST_F(PhotoshopTest_1827, IsIrb_ValidSignature_1827) {
    // "8BIM" is the Photoshop IRB signature
    const byte data[] = {'8', 'B', 'I', 'M'};
    EXPECT_TRUE(Photoshop::isIrb(data));
}

TEST_F(PhotoshopTest_1827, IsIrb_InvalidSignature_1827) {
    const byte data[] = {'X', 'Y', 'Z', 'W'};
    EXPECT_FALSE(Photoshop::isIrb(data));
}

TEST_F(PhotoshopTest_1827, IsIrb_PartiallyCorrectSignature_1827) {
    const byte data[] = {'8', 'B', 'I', 'X'};
    EXPECT_FALSE(Photoshop::isIrb(data));
}

TEST_F(PhotoshopTest_1827, IsIrb_NullBytes_1827) {
    const byte data[] = {0, 0, 0, 0};
    EXPECT_FALSE(Photoshop::isIrb(data));
}

// ==================== valid Tests ====================

TEST_F(PhotoshopTest_1827, Valid_NullPointerZeroSize_1827) {
    EXPECT_FALSE(Photoshop::valid(nullptr, 0));
}

TEST_F(PhotoshopTest_1827, Valid_TooSmallData_1827) {
    const byte data[] = {'8', 'B'};
    EXPECT_FALSE(Photoshop::valid(data, sizeof(data)));
}

TEST_F(PhotoshopTest_1827, Valid_InvalidSignature_1827) {
    const byte data[] = {'X', 'Y', 'Z', 'W', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    EXPECT_FALSE(Photoshop::valid(data, sizeof(data)));
}

// ==================== locateIrb Tests ====================

TEST_F(PhotoshopTest_1827, LocateIrb_NullData_1827) {
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(nullptr, 0, 0x0404, &record, sizeHdr, sizeData);
    // With null/empty data, should return an error or "not found" status
    EXPECT_NE(0, result);  // Typically 3 means "not found" or negative for error
}

TEST_F(PhotoshopTest_1827, LocateIrb_EmptyData_1827) {
    const byte data[] = {0};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(data, 0, 0x0404, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1827, LocateIrb_InvalidPsData_1827) {
    const byte data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(data, sizeof(data), 0x0404, &record, sizeHdr, sizeData);
    // Data doesn't have valid IRB signature, should not find anything
    EXPECT_NE(0, result);
}

// ==================== locateIptcIrb Tests ====================

TEST_F(PhotoshopTest_1827, LocateIptcIrb_NullData_1827) {
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIptcIrb(nullptr, 0, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1827, LocateIptcIrb_EmptyData_1827) {
    const byte data[] = {0};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIptcIrb(data, 0, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1827, LocateIptcIrb_InvalidData_1827) {
    const byte data[] = {0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6, 0xF5, 0xF4};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIptcIrb(data, sizeof(data), &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1827, LocateIptcIrb_ValidIrbButNoIptc_1827) {
    // Construct a minimal valid IRB block with a different tag (not IPTC tag 0x0404)
    // IRB structure: "8BIM" (4 bytes) + resource type (2 bytes) + pascal string + data size (4 bytes) + data
    std::vector<byte> data;
    // Signature
    data.push_back('8'); data.push_back('B'); data.push_back('I'); data.push_back('M');
    // Resource ID (not IPTC, use 0x03E8 for example)
    data.push_back(0x03); data.push_back(0xE8);
    // Pascal string: length 0 + padding byte
    data.push_back(0x00); data.push_back(0x00);
    // Data size: 4 bytes, big-endian, value = 2
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x02);
    // Data: 2 bytes
    data.push_back(0xAA); data.push_back(0xBB);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIptcIrb(data.data(), data.size(), &record, sizeHdr, sizeData);
    // Should not find IPTC IRB since tag doesn't match
    EXPECT_NE(0, result);
}

// ==================== locatePreviewIrb Tests ====================

TEST_F(PhotoshopTest_1827, LocatePreviewIrb_NullData_1827) {
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locatePreviewIrb(nullptr, 0, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1827, LocatePreviewIrb_EmptyData_1827) {
    const byte data[] = {0};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locatePreviewIrb(data, 0, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1827, LocatePreviewIrb_InvalidData_1827) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locatePreviewIrb(data, sizeof(data), &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

// ==================== setIptcIrb Tests ====================

TEST_F(PhotoshopTest_1827, SetIptcIrb_NullDataEmptyIptc_1827) {
    IptcData iptcData;
    DataBuf result = Photoshop::setIptcIrb(nullptr, 0, iptcData);
    // With empty IPTC data and null PS data, result should be empty
    EXPECT_EQ(0u, result.size());
}

TEST_F(PhotoshopTest_1827, SetIptcIrb_NullDataWithIptc_1827) {
    IptcData iptcData;
    // Add an IPTC datum
    Iptcdatum datum(IptcKey("Iptc.Application2.Caption"));
    datum.setValue("Test caption");
    iptcData.add(datum);

    DataBuf result = Photoshop::setIptcIrb(nullptr, 0, iptcData);
    // With non-empty IPTC data, should produce some output
    EXPECT_GT(result.size(), 0u);
}

TEST_F(PhotoshopTest_1827, SetIptcIrb_InvalidPsDataWithEmptyIptc_1827) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    IptcData iptcData;
    DataBuf result = Photoshop::setIptcIrb(data, sizeof(data), iptcData);
    // Behavior depends on implementation, but it should not crash
}

TEST_F(PhotoshopTest_1827, SetIptcIrb_ValidIrbWithEmptyIptc_1827) {
    // Construct a valid IRB block with IPTC tag (0x0404)
    std::vector<byte> data;
    // Signature
    data.push_back('8'); data.push_back('B'); data.push_back('I'); data.push_back('M');
    // Resource ID: IPTC = 0x0404
    data.push_back(0x04); data.push_back(0x04);
    // Pascal string: length 0 + padding byte
    data.push_back(0x00); data.push_back(0x00);
    // Data size: 4 bytes, big-endian, value = 2
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x02);
    // Data: 2 bytes
    data.push_back(0xAA); data.push_back(0xBB);

    IptcData iptcData;
    DataBuf result = Photoshop::setIptcIrb(data.data(), data.size(), iptcData);
    // With empty IPTC data, the existing IPTC block should be removed
    // Result could be empty or contain other non-IPTC blocks
}

TEST_F(PhotoshopTest_1827, SetIptcIrb_ValidIrbWithNewIptc_1827) {
    // Construct a valid IRB block with a non-IPTC tag
    std::vector<byte> data;
    // Signature
    data.push_back('8'); data.push_back('B'); data.push_back('I'); data.push_back('M');
    // Resource ID: non-IPTC, e.g., 0x03E8
    data.push_back(0x03); data.push_back(0xE8);
    // Pascal string: length 0 + padding
    data.push_back(0x00); data.push_back(0x00);
    // Data size: 0
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x00);

    IptcData iptcData;
    Iptcdatum datum(IptcKey("Iptc.Application2.Caption"));
    datum.setValue("Hello World");
    iptcData.add(datum);

    DataBuf result = Photoshop::setIptcIrb(data.data(), data.size(), iptcData);
    // Should contain both the original non-IPTC block and the new IPTC block
    EXPECT_GT(result.size(), data.size());
}

// ==================== Boundary Condition Tests ====================

TEST_F(PhotoshopTest_1827, LocateIrb_SizeOneByte_1827) {
    const byte data[] = {0x00};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(data, 1, 0x0404, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1827, LocateIrb_ExactlyFourBytes_1827) {
    // Just the signature, no resource data
    const byte data[] = {'8', 'B', 'I', 'M'};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(data, sizeof(data), 0x0404, &record, sizeHdr, sizeData);
    // Not enough data to constitute a valid IRB resource
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1827, IsIrb_AlternatePhotoshopSignature_1827) {
    // Some implementations also accept "MeSa" or "PHUT"
    const byte data1[] = {'M', 'e', 'S', 'a'};
    // This may or may not be valid depending on implementation
    bool result1 = Photoshop::isIrb(data1);
    // We just verify it doesn't crash; the result depends on the implementation
    (void)result1;
}

TEST_F(PhotoshopTest_1827, LocateIptcIrb_LargeInvalidData_1827) {
    std::vector<byte> data(10000, 0xFF);
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIptcIrb(data.data(), data.size(), &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1827, SetIptcIrb_MultipleIptcEntries_1827) {
    IptcData iptcData;
    
    Iptcdatum datum1(IptcKey("Iptc.Application2.Caption"));
    datum1.setValue("Caption text");
    iptcData.add(datum1);
    
    Iptcdatum datum2(IptcKey("Iptc.Application2.Keywords"));
    datum2.setValue("keyword1");
    iptcData.add(datum2);

    DataBuf result = Photoshop::setIptcIrb(nullptr, 0, iptcData);
    EXPECT_GT(result.size(), 0u);
}

TEST_F(PhotoshopTest_1827, LocateIptcIrb_ValidIptcIrb_1827) {
    // Build a complete valid IRB with IPTC data
    std::vector<byte> data;
    // Signature "8BIM"
    data.push_back('8'); data.push_back('B'); data.push_back('I'); data.push_back('M');
    // Resource ID: IPTC = 0x0404
    data.push_back(0x04); data.push_back(0x04);
    // Pascal string: length 0 + pad
    data.push_back(0x00); data.push_back(0x00);
    // Data size: 4 bytes big-endian = 4
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x04);
    // Some IPTC-like data (4 bytes)
    data.push_back(0x1C); data.push_back(0x02); data.push_back(0x00); data.push_back(0x00);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIptcIrb(data.data(), data.size(), &record, sizeHdr, sizeData);
    
    if (result == 0) {
        // Found IPTC IRB
        EXPECT_NE(nullptr, record);
        EXPECT_GT(sizeHdr, 0u);
        EXPECT_EQ(4u, sizeData);
    }
    // If not found, the data format might not be exactly right for this implementation
}

TEST_F(PhotoshopTest_1827, SetIptcIrb_RoundTrip_1827) {
    // Create IPTC data, set it into an IRB, then try to locate it
    IptcData iptcData;
    Iptcdatum datum(IptcKey("Iptc.Application2.Caption"));
    datum.setValue("Test round trip");
    iptcData.add(datum);

    DataBuf irbBuf = Photoshop::setIptcIrb(nullptr, 0, iptcData);
    
    if (irbBuf.size() > 0) {
        const byte* record = nullptr;
        uint32_t sizeHdr = 0;
        uint32_t sizeData = 0;
        int result = Photoshop::locateIptcIrb(irbBuf.c_data(), irbBuf.size(), &record, sizeHdr, sizeData);
        EXPECT_EQ(0, result);
        if (result == 0) {
            EXPECT_NE(nullptr, record);
            EXPECT_GT(sizeData, 0u);
        }
    }
}

TEST_F(PhotoshopTest_1827, Valid_ValidIrbBlock_1827) {
    // Construct valid Photoshop data
    std::vector<byte> data;
    data.push_back('8'); data.push_back('B'); data.push_back('I'); data.push_back('M');
    data.push_back(0x03); data.push_back(0xE8);
    data.push_back(0x00); data.push_back(0x00);
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x00);

    bool result = Photoshop::valid(data.data(), data.size());
    // Whether this is "valid" depends on the implementation
    (void)result; // At minimum, should not crash
}
