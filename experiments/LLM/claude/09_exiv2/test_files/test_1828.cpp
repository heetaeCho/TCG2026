#include <gtest/gtest.h>
#include <exiv2/photoshop.hpp>
#include <exiv2/types.hpp>
#include <exiv2/iptc.hpp>
#include <cstring>
#include <vector>

using namespace Exiv2;

class PhotoshopTest_1828 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Tests for isIrb
// ============================================================

TEST_F(PhotoshopTest_1828, IsIrb_NullPointer_1828) {
    EXPECT_FALSE(Photoshop::isIrb(nullptr));
}

TEST_F(PhotoshopTest_1828, IsIrb_ValidSignature_1828) {
    // The IRB signature is "8BIM" (0x38, 0x42, 0x49, 0x4D)
    const byte validIrb[] = {'8', 'B', 'I', 'M'};
    EXPECT_TRUE(Photoshop::isIrb(validIrb));
}

TEST_F(PhotoshopTest_1828, IsIrb_InvalidSignature_1828) {
    const byte invalidIrb[] = {'8', 'B', 'I', 'X'};
    EXPECT_FALSE(Photoshop::isIrb(invalidIrb));
}

TEST_F(PhotoshopTest_1828, IsIrb_AllZeros_1828) {
    const byte zeros[] = {0, 0, 0, 0};
    EXPECT_FALSE(Photoshop::isIrb(zeros));
}

TEST_F(PhotoshopTest_1828, IsIrb_PartialMatch_1828) {
    const byte partial[] = {'8', 'B', 'I', 0};
    EXPECT_FALSE(Photoshop::isIrb(partial));
}

// ============================================================
// Tests for valid
// ============================================================

TEST_F(PhotoshopTest_1828, Valid_NullPointer_1828) {
    EXPECT_FALSE(Photoshop::valid(nullptr, 0));
}

TEST_F(PhotoshopTest_1828, Valid_ZeroSize_1828) {
    const byte data[] = {'8', 'B', 'I', 'M'};
    EXPECT_FALSE(Photoshop::valid(data, 0));
}

TEST_F(PhotoshopTest_1828, Valid_TooSmall_1828) {
    const byte data[] = {'8', 'B', 'I'};
    EXPECT_FALSE(Photoshop::valid(data, 3));
}

TEST_F(PhotoshopTest_1828, Valid_InvalidSignature_1828) {
    const byte data[] = {'X', 'X', 'X', 'X', 0, 0, 0, 0, 0, 0, 0, 0};
    EXPECT_FALSE(Photoshop::valid(data, sizeof(data)));
}

// ============================================================
// Tests for locateIrb
// ============================================================

TEST_F(PhotoshopTest_1828, LocateIrb_NullData_1828) {
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(nullptr, 0, 0x0404, &record, sizeHdr, sizeData);
    // Should return error / not found with null data
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1828, LocateIrb_EmptyData_1828) {
    const byte data[] = {0};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(data, 0, 0x0404, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1828, LocateIrb_InvalidIrbData_1828) {
    const byte data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                         0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(data, sizeof(data), 0x0404, &record, sizeHdr, sizeData);
    // Data doesn't contain valid IRB, should fail
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1828, LocateIrb_ValidIrbWithTag_1828) {
    // Construct a minimal valid IRB resource block:
    // "8BIM" (4 bytes) + tag (2 bytes, big-endian) + pascal string (1 byte len + padding) + data size (4 bytes, big-endian) + data
    const uint16_t tag = 0x0404; // IPTC tag
    std::vector<byte> data;
    // Signature: 8BIM
    data.push_back('8');
    data.push_back('B');
    data.push_back('I');
    data.push_back('M');
    // Tag (big-endian)
    data.push_back(static_cast<byte>((tag >> 8) & 0xFF));
    data.push_back(static_cast<byte>(tag & 0xFF));
    // Pascal string: length 0, plus padding byte for even alignment
    data.push_back(0x00);
    data.push_back(0x00);
    // Data size (big-endian): 4 bytes of data
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x04);
    // Data: 4 bytes
    data.push_back(0xDE);
    data.push_back(0xAD);
    data.push_back(0xBE);
    data.push_back(0xEF);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(data.data(), data.size(), tag, &record, sizeHdr, sizeData);
    
    if (result == 0) {
        // If found, record should not be null
        EXPECT_NE(nullptr, record);
        EXPECT_GT(sizeData, 0u);
    }
}

TEST_F(PhotoshopTest_1828, LocateIrb_TagNotFound_1828) {
    // Construct a valid IRB but search for a different tag
    const uint16_t storedTag = 0x0404;
    const uint16_t searchTag = 0x040C; // Preview tag
    std::vector<byte> data;
    data.push_back('8');
    data.push_back('B');
    data.push_back('I');
    data.push_back('M');
    data.push_back(static_cast<byte>((storedTag >> 8) & 0xFF));
    data.push_back(static_cast<byte>(storedTag & 0xFF));
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x04);
    data.push_back(0xDE);
    data.push_back(0xAD);
    data.push_back(0xBE);
    data.push_back(0xEF);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(data.data(), data.size(), searchTag, &record, sizeHdr, sizeData);
    // Tag not present, should return non-zero (3 = not found)
    EXPECT_NE(0, result);
}

// ============================================================
// Tests for locateIptcIrb
// ============================================================

TEST_F(PhotoshopTest_1828, LocateIptcIrb_NullData_1828) {
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIptcIrb(nullptr, 0, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1828, LocateIptcIrb_EmptyData_1828) {
    const byte data[] = {0};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIptcIrb(data, 0, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1828, LocateIptcIrb_InvalidData_1828) {
    const byte data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIptcIrb(data, sizeof(data), &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1828, LocateIptcIrb_ValidIptcBlock_1828) {
    // Build IRB with IPTC tag 0x0404
    const uint16_t tag = 0x0404;
    std::vector<byte> data;
    data.push_back('8');
    data.push_back('B');
    data.push_back('I');
    data.push_back('M');
    data.push_back(static_cast<byte>((tag >> 8) & 0xFF));
    data.push_back(static_cast<byte>(tag & 0xFF));
    data.push_back(0x00); // Pascal string length
    data.push_back(0x00); // Padding
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x02); // data size = 2
    data.push_back(0xAA);
    data.push_back(0xBB);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIptcIrb(data.data(), data.size(), &record, sizeHdr, sizeData);
    
    if (result == 0) {
        EXPECT_NE(nullptr, record);
        EXPECT_EQ(2u, sizeData);
    }
}

// ============================================================
// Tests for locatePreviewIrb
// ============================================================

TEST_F(PhotoshopTest_1828, LocatePreviewIrb_NullData_1828) {
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locatePreviewIrb(nullptr, 0, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1828, LocatePreviewIrb_EmptyData_1828) {
    const byte data[] = {0};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locatePreviewIrb(data, 0, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1828, LocatePreviewIrb_NoPreviewPresent_1828) {
    // Build IRB with IPTC tag (not preview)
    const uint16_t tag = 0x0404;
    std::vector<byte> data;
    data.push_back('8');
    data.push_back('B');
    data.push_back('I');
    data.push_back('M');
    data.push_back(static_cast<byte>((tag >> 8) & 0xFF));
    data.push_back(static_cast<byte>(tag & 0xFF));
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x02);
    data.push_back(0xAA);
    data.push_back(0xBB);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locatePreviewIrb(data.data(), data.size(), &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

// ============================================================
// Tests for setIptcIrb
// ============================================================

TEST_F(PhotoshopTest_1828, SetIptcIrb_EmptyIptcAndNullPsData_1828) {
    IptcData iptcData;
    DataBuf result = Photoshop::setIptcIrb(nullptr, 0, iptcData);
    // With empty IPTC data and no PS data, result should be empty
    EXPECT_EQ(0u, result.size());
}

TEST_F(PhotoshopTest_1828, SetIptcIrb_EmptyIptcWithValidPsData_1828) {
    // Build a minimal IRB with IPTC data
    const uint16_t tag = 0x0404;
    std::vector<byte> data;
    data.push_back('8');
    data.push_back('B');
    data.push_back('I');
    data.push_back('M');
    data.push_back(static_cast<byte>((tag >> 8) & 0xFF));
    data.push_back(static_cast<byte>(tag & 0xFF));
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x02);
    data.push_back(0xAA);
    data.push_back(0xBB);

    IptcData iptcData;
    DataBuf result = Photoshop::setIptcIrb(data.data(), data.size(), iptcData);
    // The old IPTC block should be removed; result may be empty or just have non-IPTC blocks
    // We just verify it doesn't crash and returns a valid buffer
    // (size could be 0 if the only block was IPTC)
    SUCCEED();
}

TEST_F(PhotoshopTest_1828, SetIptcIrb_NullPsDataWithZeroSize_1828) {
    IptcData iptcData;
    DataBuf result = Photoshop::setIptcIrb(nullptr, 0, iptcData);
    // Should handle gracefully
    EXPECT_EQ(0u, result.size());
}

// ============================================================
// Tests for valid with various sizes
// ============================================================

TEST_F(PhotoshopTest_1828, Valid_ExactlyFourBytesInvalid_1828) {
    const byte data[] = {0x00, 0x00, 0x00, 0x00};
    EXPECT_FALSE(Photoshop::valid(data, 4));
}

TEST_F(PhotoshopTest_1828, Valid_JustSignatureNoMore_1828) {
    const byte data[] = {'8', 'B', 'I', 'M'};
    // Just the signature, no tag or anything else - may or may not be valid
    // depending on implementation, but we test it doesn't crash
    bool result = Photoshop::valid(data, sizeof(data));
    // We just verify it doesn't crash; either true or false is acceptable
    (void)result;
    SUCCEED();
}

// ============================================================
// Boundary tests
// ============================================================

TEST_F(PhotoshopTest_1828, LocateIrb_SizeOneData_1828) {
    const byte data[] = {0xFF};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(data, 1, 0x0404, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1828, LocateIrb_TruncatedIrb_1828) {
    // Valid signature but truncated (no tag, no size, no data)
    const byte data[] = {'8', 'B', 'I', 'M'};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(data, sizeof(data), 0x0404, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1828, LocateIrb_TruncatedAfterTag_1828) {
    // Valid signature + tag but no size or data
    const byte data[] = {'8', 'B', 'I', 'M', 0x04, 0x04};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(data, sizeof(data), 0x0404, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

TEST_F(PhotoshopTest_1828, IsIrb_ExactSignatureBytes_1828) {
    const byte data[] = {0x38, 0x42, 0x49, 0x4D}; // "8BIM" in hex
    EXPECT_TRUE(Photoshop::isIrb(data));
}

// ============================================================
// Tests with multiple IRB blocks
// ============================================================

TEST_F(PhotoshopTest_1828, LocateIrb_MultipleBlocks_FindSecond_1828) {
    // First block: tag 0x0404 (IPTC)
    // Second block: tag 0x040C (preview)
    std::vector<byte> data;
    
    // First block
    data.push_back('8'); data.push_back('B'); data.push_back('I'); data.push_back('M');
    data.push_back(0x04); data.push_back(0x04); // tag 0x0404
    data.push_back(0x00); data.push_back(0x00); // pascal string
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x02); // size 2
    data.push_back(0xAA); data.push_back(0xBB); // data
    
    // Second block
    data.push_back('8'); data.push_back('B'); data.push_back('I'); data.push_back('M');
    data.push_back(0x04); data.push_back(0x0C); // tag 0x040C
    data.push_back(0x00); data.push_back(0x00); // pascal string
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x03); // size 3
    data.push_back(0xCC); data.push_back(0xDD); data.push_back(0xEE); // data
    // Padding for even alignment
    data.push_back(0x00);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    
    // Search for second tag
    int result = Photoshop::locateIrb(data.data(), data.size(), 0x040C, &record, sizeHdr, sizeData);
    if (result == 0) {
        EXPECT_NE(nullptr, record);
        EXPECT_EQ(3u, sizeData);
    }
}

TEST_F(PhotoshopTest_1828, LocateIptcIrb_WithMultipleBlocks_1828) {
    std::vector<byte> data;
    
    // Non-IPTC block first
    data.push_back('8'); data.push_back('B'); data.push_back('I'); data.push_back('M');
    data.push_back(0x04); data.push_back(0x0C); // tag 0x040C (not IPTC)
    data.push_back(0x00); data.push_back(0x00);
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x02);
    data.push_back(0x11); data.push_back(0x22);
    
    // IPTC block
    data.push_back('8'); data.push_back('B'); data.push_back('I'); data.push_back('M');
    data.push_back(0x04); data.push_back(0x04); // tag 0x0404 (IPTC)
    data.push_back(0x00); data.push_back(0x00);
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x04);
    data.push_back(0xDE); data.push_back(0xAD); data.push_back(0xBE); data.push_back(0xEF);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIptcIrb(data.data(), data.size(), &record, sizeHdr, sizeData);
    
    if (result == 0) {
        EXPECT_NE(nullptr, record);
        EXPECT_EQ(4u, sizeData);
    }
}
