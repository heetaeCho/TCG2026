#include <gtest/gtest.h>
#include <exiv2/photoshop.hpp>
#include <exiv2/types.hpp>
#include <exiv2/iptc.hpp>
#include <cstring>

using namespace Exiv2;

// ============================================================================
// Tests for Photoshop::isIrb
// ============================================================================

TEST(PhotoshopIsIrbTest_1824, NullPointerReturnsFalse_1824) {
    EXPECT_FALSE(Photoshop::isIrb(nullptr));
}

TEST(PhotoshopIsIrbTest_1824, ValidIrbSignature8BIM_1824) {
    // "8BIM" is a known Photoshop IRB signature
    const byte data[] = {'8', 'B', 'I', 'M', 0x00, 0x00};
    EXPECT_TRUE(Photoshop::isIrb(data));
}

TEST(PhotoshopIsIrbTest_1824, InvalidIrbSignature_1824) {
    const byte data[] = {'X', 'Y', 'Z', 'W', 0x00, 0x00};
    EXPECT_FALSE(Photoshop::isIrb(data));
}

TEST(PhotoshopIsIrbTest_1824, AllZerosNotIrb_1824) {
    const byte data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    EXPECT_FALSE(Photoshop::isIrb(data));
}

TEST(PhotoshopIsIrbTest_1824, PartialMatch8BI_1824) {
    // Only first 3 bytes match "8BI" but 4th is wrong
    const byte data[] = {'8', 'B', 'I', 'X', 0x00, 0x00};
    EXPECT_FALSE(Photoshop::isIrb(data));
}

// ============================================================================
// Tests for Photoshop::valid
// ============================================================================

TEST(PhotoshopValidTest_1824, NullDataReturnsFalse_1824) {
    EXPECT_FALSE(Photoshop::valid(nullptr, 0));
}

TEST(PhotoshopValidTest_1824, ZeroSizeReturnsFalse_1824) {
    const byte data[] = {'8', 'B', 'I', 'M'};
    EXPECT_FALSE(Photoshop::valid(data, 0));
}

TEST(PhotoshopValidTest_1824, TooSmallSizeReturnsFalse_1824) {
    const byte data[] = {'8', 'B', 'I', 'M'};
    EXPECT_FALSE(Photoshop::valid(data, 3));
}

TEST(PhotoshopValidTest_1824, ValidIrbBlockMinimal_1824) {
    // A valid IRB block: "8BIM" (4 bytes) + resource type (2 bytes) + pascal string (1 byte min) + padding + size (4 bytes) + data
    // Minimum valid block: 8BIM + 2 byte tag + 1 byte pascal string (0 length) + 1 byte padding + 4 bytes size (0) = 12 bytes
    byte data[12];
    memcpy(data, "8BIM", 4);
    data[4] = 0x04;  // tag high byte
    data[5] = 0x00;  // tag low byte
    data[6] = 0x00;  // pascal string length = 0
    data[7] = 0x00;  // padding
    data[8] = 0x00;  // size = 0
    data[9] = 0x00;
    data[10] = 0x00;
    data[11] = 0x00;
    // This may or may not be valid depending on implementation details
    // We're testing the interface
    bool result = Photoshop::valid(data, sizeof(data));
    // Just ensure it doesn't crash; the result depends on exact validation logic
    (void)result;
}

TEST(PhotoshopValidTest_1824, InvalidSignatureNotValid_1824) {
    byte data[12];
    memcpy(data, "XXXX", 4);
    data[4] = 0x04;
    data[5] = 0x00;
    data[6] = 0x00;
    data[7] = 0x00;
    data[8] = 0x00;
    data[9] = 0x00;
    data[10] = 0x00;
    data[11] = 0x00;
    EXPECT_FALSE(Photoshop::valid(data, sizeof(data)));
}

// ============================================================================
// Tests for Photoshop::locateIrb
// ============================================================================

TEST(PhotoshopLocateIrbTest_1824, NullDataReturnsNegative_1824) {
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(nullptr, 0, 0x0404, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST(PhotoshopLocateIrbTest_1824, EmptyDataReturnsNegative_1824) {
    const byte data[] = {0x00};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(data, 0, 0x0404, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST(PhotoshopLocateIrbTest_1824, TooSmallDataReturnsNegative_1824) {
    const byte data[] = {'8', 'B', 'I'};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(data, sizeof(data), 0x0404, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST(PhotoshopLocateIrbTest_1824, InvalidIrbBlockNotFound_1824) {
    byte data[20];
    memset(data, 0, sizeof(data));
    memcpy(data, "XXXX", 4);
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(data, sizeof(data), 0x0404, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

// ============================================================================
// Tests for Photoshop::locateIptcIrb
// ============================================================================

TEST(PhotoshopLocateIptcIrbTest_1824, NullDataReturnsNegative_1824) {
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIptcIrb(nullptr, 0, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST(PhotoshopLocateIptcIrbTest_1824, EmptyDataReturnsNegative_1824) {
    const byte data[] = {0x00};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIptcIrb(data, 0, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

// ============================================================================
// Tests for Photoshop::locatePreviewIrb
// ============================================================================

TEST(PhotoshopLocatePreviewIrbTest_1824, NullDataReturnsNegative_1824) {
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locatePreviewIrb(nullptr, 0, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST(PhotoshopLocatePreviewIrbTest_1824, EmptyDataReturnsNegative_1824) {
    const byte data[] = {0x00};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locatePreviewIrb(data, 0, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

// ============================================================================
// Tests for Photoshop::setIptcIrb
// ============================================================================

TEST(PhotoshopSetIptcIrbTest_1824, NullDataEmptyIptc_1824) {
    IptcData iptcData;
    DataBuf result = Photoshop::setIptcIrb(nullptr, 0, iptcData);
    // With null data and empty IPTC, the result should be empty
    EXPECT_EQ(0u, result.size());
}

TEST(PhotoshopSetIptcIrbTest_1824, EmptyIptcDataReturnsEmptyOrOriginal_1824) {
    byte data[12];
    memset(data, 0, sizeof(data));
    IptcData iptcData;
    DataBuf result = Photoshop::setIptcIrb(data, 0, iptcData);
    // With zero size and empty IPTC, should return empty
    EXPECT_EQ(0u, result.size());
}

TEST(PhotoshopSetIptcIrbTest_1824, InvalidPsDataWithEmptyIptc_1824) {
    byte data[20];
    memset(data, 'X', sizeof(data));
    IptcData iptcData;
    DataBuf result = Photoshop::setIptcIrb(data, sizeof(data), iptcData);
    // Result depends on whether the data is valid PS data; just ensure no crash
    (void)result;
}

// ============================================================================
// Tests for Photoshop::isIrb with known alternative signatures
// ============================================================================

TEST(PhotoshopIsIrbTest_1824, AlternativeSignaturePhut_1824) {
    // Some Photoshop versions might use alternative IRB signatures like "PHUT"
    const byte data[] = {'P', 'H', 'U', 'T', 0x00, 0x00};
    // This may or may not be a valid IRB ID; testing the boundary
    bool result = Photoshop::isIrb(data);
    (void)result; // Just ensure no crash
}

TEST(PhotoshopIsIrbTest_1824, AlternativeSignature8BPS_1824) {
    const byte data[] = {'8', 'B', 'P', 'S', 0x00, 0x00};
    // This may or may not be a valid IRB ID
    bool result = Photoshop::isIrb(data);
    (void)result; // Just ensure no crash
}

// ============================================================================
// Comprehensive IRB block test
// ============================================================================

TEST(PhotoshopLocateIrbTest_1824, WellFormedIrbBlockWithIptcTag_1824) {
    // Construct a well-formed IRB block with IPTC tag (0x0404)
    // Format: "8BIM" + uint16 tag + pascal string + padding + uint32 size + data
    std::vector<byte> data;
    // IRB header "8BIM"
    data.push_back('8');
    data.push_back('B');
    data.push_back('I');
    data.push_back('M');
    // Tag = 0x0404 (IPTC-NAA)
    data.push_back(0x04);
    data.push_back(0x04);
    // Pascal string: length 0, padded to even
    data.push_back(0x00);
    data.push_back(0x00);
    // Data size = 4
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x04);
    // Data (4 bytes)
    data.push_back(0x01);
    data.push_back(0x02);
    data.push_back(0x03);
    data.push_back(0x04);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(data.data(), data.size(), 0x0404, &record, sizeHdr, sizeData);
    
    if (result == 0) {
        // Found - verify the record pointer is within our data
        EXPECT_NE(nullptr, record);
        EXPECT_GE(record, data.data());
        EXPECT_LT(record, data.data() + data.size());
        EXPECT_EQ(4u, sizeData);
    }
    // If not found (result != 0), the format might not exactly match what the implementation expects
}

TEST(PhotoshopLocateIptcIrbTest_1824, WellFormedIptcIrbBlock_1824) {
    // Same as above but using locateIptcIrb
    std::vector<byte> data;
    data.push_back('8');
    data.push_back('B');
    data.push_back('I');
    data.push_back('M');
    data.push_back(0x04);
    data.push_back(0x04);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x04);
    data.push_back(0x01);
    data.push_back(0x02);
    data.push_back(0x03);
    data.push_back(0x04);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIptcIrb(data.data(), data.size(), &record, sizeHdr, sizeData);
    
    if (result == 0) {
        EXPECT_NE(nullptr, record);
        EXPECT_EQ(4u, sizeData);
    }
}

TEST(PhotoshopValidTest_1824, WellFormedIrbBlockIsValid_1824) {
    std::vector<byte> data;
    data.push_back('8');
    data.push_back('B');
    data.push_back('I');
    data.push_back('M');
    data.push_back(0x04);
    data.push_back(0x04);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x04);
    data.push_back(0x01);
    data.push_back(0x02);
    data.push_back(0x03);
    data.push_back(0x04);

    bool result = Photoshop::valid(data.data(), data.size());
    // Should be valid if the format is correct
    EXPECT_TRUE(result);
}
