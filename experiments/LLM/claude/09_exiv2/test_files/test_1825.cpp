#include <gtest/gtest.h>
#include <exiv2/photoshop.hpp>
#include <exiv2/types.hpp>
#include <exiv2/iptc.hpp>
#include <cstring>
#include <vector>

using namespace Exiv2;

// Helper: Photoshop IRB marker is "8BIM" (0x38, 0x42, 0x49, 0x4D)
static const byte psSignature[] = {0x38, 0x42, 0x49, 0x4D};

class PhotoshopTest_1825 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== isIrb tests ====================

TEST_F(PhotoshopTest_1825, IsIrb_ValidSignature_1825) {
    // "8BIM" is the Photoshop IRB signature
    byte data[] = {0x38, 0x42, 0x49, 0x4D};
    EXPECT_TRUE(Photoshop::isIrb(data));
}

TEST_F(PhotoshopTest_1825, IsIrb_InvalidSignature_1825) {
    byte data[] = {0x00, 0x00, 0x00, 0x00};
    EXPECT_FALSE(Photoshop::isIrb(data));
}

TEST_F(PhotoshopTest_1825, IsIrb_PartiallyCorrectSignature_1825) {
    byte data[] = {0x38, 0x42, 0x49, 0x00};
    EXPECT_FALSE(Photoshop::isIrb(data));
}

TEST_F(PhotoshopTest_1825, IsIrb_AlmostCorrectSignature_1825) {
    byte data[] = {0x38, 0x42, 0x49, 0x4E};  // last byte differs
    EXPECT_FALSE(Photoshop::isIrb(data));
}

// ==================== valid tests ====================

TEST_F(PhotoshopTest_1825, Valid_EmptyData_1825) {
    byte data[] = {0};
    // Zero size should be valid (no records to check, loop doesn't execute, ret stays 0 which is >= 0)
    EXPECT_TRUE(Photoshop::valid(data, 0));
}

TEST_F(PhotoshopTest_1825, Valid_NullDataZeroSize_1825) {
    // Passing nullptr with zero size - pCur == pEnd so loop doesn't execute
    // ret == 0 which is >= 0
    EXPECT_TRUE(Photoshop::valid(nullptr, 0));
}

TEST_F(PhotoshopTest_1825, Valid_RandomGarbage_1825) {
    byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    // Random data without valid IRB - locateIptcIrb should return negative
    // The valid function checks if ret >= 0
    bool result = Photoshop::valid(data, sizeof(data));
    // We can't know for sure, but garbage data likely returns negative from locateIptcIrb
    // Just ensure it doesn't crash; the actual result depends on implementation
    (void)result;
}

TEST_F(PhotoshopTest_1825, Valid_TooSmallForIRB_1825) {
    byte data[] = {0x38, 0x42};
    bool result = Photoshop::valid(data, sizeof(data));
    // Data too small to contain a valid IRB record
    (void)result; // Just ensure no crash
}

// ==================== locateIrb tests ====================

TEST_F(PhotoshopTest_1825, LocateIrb_EmptyData_1825) {
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    byte data[] = {0};
    int ret = Photoshop::locateIrb(data, 0, 0x0404, &record, sizeHdr, sizeData);
    // With empty data, should return non-zero (not found or error)
    EXPECT_NE(0, ret);
}

TEST_F(PhotoshopTest_1825, LocateIrb_NoMatchingTag_1825) {
    // Construct a minimal valid-looking IRB with a different tag
    // 8BIM + tag(2bytes) + pascal string (1 byte length + padding) + size(4bytes) + data
    std::vector<byte> data;
    // Signature: 8BIM
    data.push_back(0x38); data.push_back(0x42); data.push_back(0x49); data.push_back(0x4D);
    // Tag: 0x0425 (not IPTC 0x0404)
    data.push_back(0x04); data.push_back(0x25);
    // Pascal string: length 0, then padding byte for even alignment
    data.push_back(0x00); data.push_back(0x00);
    // Size: 0 bytes of data
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x00);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int ret = Photoshop::locateIrb(data.data(), data.size(), 0x0404, &record, sizeHdr, sizeData);
    // Should not find tag 0x0404
    EXPECT_NE(0, ret);
}

TEST_F(PhotoshopTest_1825, LocateIrb_GarbageData_1825) {
    byte data[] = {0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int ret = Photoshop::locateIrb(data, sizeof(data), 0x0404, &record, sizeHdr, sizeData);
    EXPECT_NE(0, ret);
}

// ==================== locateIptcIrb tests ====================

TEST_F(PhotoshopTest_1825, LocateIptcIrb_EmptyData_1825) {
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    byte data[] = {0};
    int ret = Photoshop::locateIptcIrb(data, 0, &record, sizeHdr, sizeData);
    EXPECT_NE(0, ret);
}

TEST_F(PhotoshopTest_1825, LocateIptcIrb_GarbageData_1825) {
    byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int ret = Photoshop::locateIptcIrb(data, sizeof(data), &record, sizeHdr, sizeData);
    EXPECT_NE(0, ret);
}

TEST_F(PhotoshopTest_1825, LocateIptcIrb_ValidIptcIrb_1825) {
    // Construct a minimal IRB with IPTC tag 0x0404
    std::vector<byte> data;
    // Signature: 8BIM
    data.push_back(0x38); data.push_back(0x42); data.push_back(0x49); data.push_back(0x4D);
    // Tag: 0x0404 (IPTC-NAA)
    data.push_back(0x04); data.push_back(0x04);
    // Pascal string: length 0, padding byte
    data.push_back(0x00); data.push_back(0x00);
    // Size: 4 bytes of data
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x04);
    // IPTC data (4 bytes of dummy data)
    data.push_back(0x1C); data.push_back(0x02); data.push_back(0x00); data.push_back(0x00);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int ret = Photoshop::locateIptcIrb(data.data(), data.size(), &record, sizeHdr, sizeData);
    EXPECT_EQ(0, ret);
    EXPECT_NE(nullptr, record);
    EXPECT_GT(sizeData, 0u);
}

// ==================== locatePreviewIrb tests ====================

TEST_F(PhotoshopTest_1825, LocatePreviewIrb_EmptyData_1825) {
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    byte data[] = {0};
    int ret = Photoshop::locatePreviewIrb(data, 0, &record, sizeHdr, sizeData);
    EXPECT_NE(0, ret);
}

TEST_F(PhotoshopTest_1825, LocatePreviewIrb_GarbageData_1825) {
    byte data[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int ret = Photoshop::locatePreviewIrb(data, sizeof(data), &record, sizeHdr, sizeData);
    EXPECT_NE(0, ret);
}

// ==================== setIptcIrb tests ====================

TEST_F(PhotoshopTest_1825, SetIptcIrb_EmptyIptcEmptyPsData_1825) {
    IptcData iptcData;
    DataBuf result = Photoshop::setIptcIrb(nullptr, 0, iptcData);
    // With empty IPTC data and no PS data, result should be empty
    EXPECT_EQ(0u, result.size());
}

TEST_F(PhotoshopTest_1825, SetIptcIrb_EmptyIptcWithPsData_1825) {
    // Construct a minimal IRB with IPTC tag 0x0404
    std::vector<byte> data;
    // Signature: 8BIM
    data.push_back(0x38); data.push_back(0x42); data.push_back(0x49); data.push_back(0x4D);
    // Tag: 0x0404
    data.push_back(0x04); data.push_back(0x04);
    // Pascal string: length 0, padding
    data.push_back(0x00); data.push_back(0x00);
    // Size: 4 bytes
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x04);
    // Dummy IPTC data
    data.push_back(0x1C); data.push_back(0x02); data.push_back(0x00); data.push_back(0x00);

    IptcData emptyIptc;
    DataBuf result = Photoshop::setIptcIrb(data.data(), data.size(), emptyIptc);
    // With empty IPTC, the IPTC IRB should be removed, result might be empty or contain non-IPTC IRBs
    // Just check it doesn't crash
    (void)result;
}

TEST_F(PhotoshopTest_1825, SetIptcIrb_GarbagePsData_1825) {
    byte data[] = {0x01, 0x02, 0x03};
    IptcData iptcData;
    DataBuf result = Photoshop::setIptcIrb(data, sizeof(data), iptcData);
    // Garbage data with empty IPTC - should not crash
    (void)result;
}

// ==================== valid with constructed IRB ====================

TEST_F(PhotoshopTest_1825, Valid_ValidIptcIrb_1825) {
    // Construct a valid IRB with IPTC
    std::vector<byte> data;
    // Signature: 8BIM
    data.push_back(0x38); data.push_back(0x42); data.push_back(0x49); data.push_back(0x4D);
    // Tag: 0x0404
    data.push_back(0x04); data.push_back(0x04);
    // Pascal string: length 0, padding
    data.push_back(0x00); data.push_back(0x00);
    // Size: 4 bytes
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x04);
    // Dummy data
    data.push_back(0x1C); data.push_back(0x02); data.push_back(0x00); data.push_back(0x00);

    EXPECT_TRUE(Photoshop::valid(data.data(), data.size()));
}

TEST_F(PhotoshopTest_1825, Valid_SingleByteData_1825) {
    byte data[] = {0x00};
    bool result = Photoshop::valid(data, 1);
    // Single byte - too small for any IRB, but shouldn't crash
    (void)result;
}

// ==================== locateIrb with matching tag ====================

TEST_F(PhotoshopTest_1825, LocateIrb_MatchingTag_1825) {
    std::vector<byte> data;
    // Signature: 8BIM
    data.push_back(0x38); data.push_back(0x42); data.push_back(0x49); data.push_back(0x4D);
    // Tag: 0x0425
    data.push_back(0x04); data.push_back(0x25);
    // Pascal string: length 0, padding
    data.push_back(0x00); data.push_back(0x00);
    // Size: 2 bytes
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x02);
    // Data
    data.push_back(0xAB); data.push_back(0xCD);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int ret = Photoshop::locateIrb(data.data(), data.size(), 0x0425, &record, sizeHdr, sizeData);
    EXPECT_EQ(0, ret);
    EXPECT_NE(nullptr, record);
    EXPECT_EQ(2u, sizeData);
}

// ==================== Boundary: very large size field ====================

TEST_F(PhotoshopTest_1825, LocateIptcIrb_OversizedSizeField_1825) {
    std::vector<byte> data;
    // Signature: 8BIM
    data.push_back(0x38); data.push_back(0x42); data.push_back(0x49); data.push_back(0x4D);
    // Tag: 0x0404
    data.push_back(0x04); data.push_back(0x04);
    // Pascal string: length 0, padding
    data.push_back(0x00); data.push_back(0x00);
    // Size: extremely large (0xFFFFFFFF) - exceeds actual data
    data.push_back(0xFF); data.push_back(0xFF); data.push_back(0xFF); data.push_back(0xFF);
    // Only 4 bytes of actual data
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x00);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    // This should detect the inconsistency and return error
    int ret = Photoshop::locateIptcIrb(data.data(), data.size(), &record, sizeHdr, sizeData);
    // Expect negative return (error) since the size field is invalid
    EXPECT_NE(0, ret);
}

// ==================== Multiple IRBs ====================

TEST_F(PhotoshopTest_1825, LocateIrb_MultipleIrbs_FindsCorrectOne_1825) {
    std::vector<byte> data;

    // First IRB: tag 0x0425, size 2
    data.push_back(0x38); data.push_back(0x42); data.push_back(0x49); data.push_back(0x4D);
    data.push_back(0x04); data.push_back(0x25);
    data.push_back(0x00); data.push_back(0x00);
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x02);
    data.push_back(0x11); data.push_back(0x22);

    // Second IRB: tag 0x0404 (IPTC), size 4
    data.push_back(0x38); data.push_back(0x42); data.push_back(0x49); data.push_back(0x4D);
    data.push_back(0x04); data.push_back(0x04);
    data.push_back(0x00); data.push_back(0x00);
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x04);
    data.push_back(0x1C); data.push_back(0x02); data.push_back(0x00); data.push_back(0x00);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;

    // Locate tag 0x0404
    int ret = Photoshop::locateIrb(data.data(), data.size(), 0x0404, &record, sizeHdr, sizeData);
    EXPECT_EQ(0, ret);
    EXPECT_NE(nullptr, record);
    EXPECT_EQ(4u, sizeData);
}

TEST_F(PhotoshopTest_1825, Valid_MultipleValidIrbs_1825) {
    std::vector<byte> data;

    // First IRB: tag 0x0404, size 4
    data.push_back(0x38); data.push_back(0x42); data.push_back(0x49); data.push_back(0x4D);
    data.push_back(0x04); data.push_back(0x04);
    data.push_back(0x00); data.push_back(0x00);
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x04);
    data.push_back(0x1C); data.push_back(0x02); data.push_back(0x00); data.push_back(0x00);

    // Second IRB: tag 0x0404, size 4
    data.push_back(0x38); data.push_back(0x42); data.push_back(0x49); data.push_back(0x4D);
    data.push_back(0x04); data.push_back(0x04);
    data.push_back(0x00); data.push_back(0x00);
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x04);
    data.push_back(0x1C); data.push_back(0x02); data.push_back(0x00); data.push_back(0x00);

    EXPECT_TRUE(Photoshop::valid(data.data(), data.size()));
}

// ==================== isIrb with all zero bytes ====================

TEST_F(PhotoshopTest_1825, IsIrb_AllZeros_1825) {
    byte data[] = {0x00, 0x00, 0x00, 0x00};
    EXPECT_FALSE(Photoshop::isIrb(data));
}

// ==================== IRB with pascal string name ====================

TEST_F(PhotoshopTest_1825, LocateIrb_WithPascalStringName_1825) {
    std::vector<byte> data;
    // Signature: 8BIM
    data.push_back(0x38); data.push_back(0x42); data.push_back(0x49); data.push_back(0x4D);
    // Tag: 0x0404
    data.push_back(0x04); data.push_back(0x04);
    // Pascal string: length 3, "abc", then padding for even alignment (total 4 bytes: 1 length + 3 chars)
    data.push_back(0x03); data.push_back('a'); data.push_back('b'); data.push_back('c');
    // Size: 4 bytes
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x04);
    // Data
    data.push_back(0x1C); data.push_back(0x02); data.push_back(0x00); data.push_back(0x00);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int ret = Photoshop::locateIrb(data.data(), data.size(), 0x0404, &record, sizeHdr, sizeData);
    EXPECT_EQ(0, ret);
    EXPECT_EQ(4u, sizeData);
}

// ==================== Zero-size IRB data ====================

TEST_F(PhotoshopTest_1825, LocateIrb_ZeroSizeData_1825) {
    std::vector<byte> data;
    // Signature: 8BIM
    data.push_back(0x38); data.push_back(0x42); data.push_back(0x49); data.push_back(0x4D);
    // Tag: 0x0404
    data.push_back(0x04); data.push_back(0x04);
    // Pascal string: length 0, padding
    data.push_back(0x00); data.push_back(0x00);
    // Size: 0 bytes
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x00);

    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int ret = Photoshop::locateIrb(data.data(), data.size(), 0x0404, &record, sizeHdr, sizeData);
    EXPECT_EQ(0, ret);
    EXPECT_EQ(0u, sizeData);
}
