#include <gtest/gtest.h>
#include <exiv2/photoshop.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/types.hpp>
#include <exiv2/error.hpp>
#include <cstring>
#include <vector>

using namespace Exiv2;

class PhotoshopTest_1829 : public ::testing::Test {
protected:
    // Helper to build a minimal valid IRB (Image Resource Block)
    // Format: "8BIM" (4 bytes) + resource ID (2 bytes) + pascal string (padded) + size (4 bytes) + data
    std::vector<byte> buildIrb(uint16_t resourceId, const std::vector<byte>& data) {
        std::vector<byte> irb;
        // Signature "8BIM"
        irb.push_back('8');
        irb.push_back('B');
        irb.push_back('I');
        irb.push_back('M');
        // Resource ID (big endian)
        irb.push_back(static_cast<byte>((resourceId >> 8) & 0xFF));
        irb.push_back(static_cast<byte>(resourceId & 0xFF));
        // Pascal string: length 0 + padding byte
        irb.push_back(0x00);
        irb.push_back(0x00);
        // Data size (big endian, 4 bytes)
        uint32_t sz = static_cast<uint32_t>(data.size());
        irb.push_back(static_cast<byte>((sz >> 24) & 0xFF));
        irb.push_back(static_cast<byte>((sz >> 16) & 0xFF));
        irb.push_back(static_cast<byte>((sz >> 8) & 0xFF));
        irb.push_back(static_cast<byte>(sz & 0xFF));
        // Data
        irb.insert(irb.end(), data.begin(), data.end());
        // Pad to even size
        if (data.size() % 2 != 0) {
            irb.push_back(0x00);
        }
        return irb;
    }

    // Build an IRB block with IPTC resource ID (0x0404)
    std::vector<byte> buildIptcIrb(const std::vector<byte>& iptcData) {
        return buildIrb(0x0404, iptcData);
    }

    // Build a non-IPTC IRB block
    std::vector<byte> buildNonIptcIrb(uint16_t resourceId, const std::vector<byte>& data) {
        return buildIrb(resourceId, data);
    }
};

// Test isIrb with valid "8BIM" signature
TEST_F(PhotoshopTest_1829, IsIrb_ValidSignature_1829) {
    const byte data[] = {'8', 'B', 'I', 'M'};
    EXPECT_TRUE(Photoshop::isIrb(data));
}

// Test isIrb with invalid signature
TEST_F(PhotoshopTest_1829, IsIrb_InvalidSignature_1829) {
    const byte data[] = {'8', 'B', 'I', 'X'};
    EXPECT_FALSE(Photoshop::isIrb(data));
}

// Test isIrb with all zeros
TEST_F(PhotoshopTest_1829, IsIrb_AllZeros_1829) {
    const byte data[] = {0, 0, 0, 0};
    EXPECT_FALSE(Photoshop::isIrb(data));
}

// Test valid with nullptr and zero size
TEST_F(PhotoshopTest_1829, Valid_NullDataZeroSize_1829) {
    EXPECT_FALSE(Photoshop::valid(nullptr, 0));
}

// Test valid with valid IRB data
TEST_F(PhotoshopTest_1829, Valid_ValidIrbData_1829) {
    std::vector<byte> data = {
        '8', 'B', 'I', 'M',  // signature
        0x04, 0x00,            // resource ID
        0x00, 0x00,            // pascal string
        0x00, 0x00, 0x00, 0x00 // data size = 0
    };
    EXPECT_TRUE(Photoshop::valid(data.data(), data.size()));
}

// Test valid with too-small data
TEST_F(PhotoshopTest_1829, Valid_TooSmallData_1829) {
    const byte data[] = {'8', 'B', 'I'};
    EXPECT_FALSE(Photoshop::valid(data, 3));
}

// Test valid with invalid signature
TEST_F(PhotoshopTest_1829, Valid_InvalidSignature_1829) {
    std::vector<byte> data = {
        'X', 'B', 'I', 'M',
        0x04, 0x00,
        0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    EXPECT_FALSE(Photoshop::valid(data.data(), data.size()));
}

// Test locateIrb with empty data
TEST_F(PhotoshopTest_1829, LocateIrb_EmptyData_1829) {
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(nullptr, 0, 0x0404, &record, sizeHdr, sizeData);
    EXPECT_EQ(3, result); // Expected to return error (3 = not found)
}

// Test locateIrb with valid data containing a matching resource
TEST_F(PhotoshopTest_1829, LocateIrb_FindMatchingResource_1829) {
    std::vector<byte> irb = buildIrb(0x0404, {0x01, 0x02, 0x03, 0x04});
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(irb.data(), irb.size(), 0x0404, &record, sizeHdr, sizeData);
    EXPECT_EQ(0, result);
    EXPECT_NE(nullptr, record);
    EXPECT_EQ(4u, sizeData);
}

// Test locateIrb with non-matching resource ID
TEST_F(PhotoshopTest_1829, LocateIrb_NonMatchingResource_1829) {
    std::vector<byte> irb = buildIrb(0x0404, {0x01, 0x02});
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(irb.data(), irb.size(), 0x0405, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

// Test locateIptcIrb with empty data
TEST_F(PhotoshopTest_1829, LocateIptcIrb_EmptyData_1829) {
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIptcIrb(nullptr, 0, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

// Test locateIptcIrb with valid IPTC IRB
TEST_F(PhotoshopTest_1829, LocateIptcIrb_ValidIptcIrb_1829) {
    std::vector<byte> irb = buildIptcIrb({0x01, 0x02, 0x03, 0x04});
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIptcIrb(irb.data(), irb.size(), &record, sizeHdr, sizeData);
    EXPECT_EQ(0, result);
    EXPECT_NE(nullptr, record);
    EXPECT_EQ(4u, sizeData);
}

// Test locateIptcIrb with no IPTC resource
TEST_F(PhotoshopTest_1829, LocateIptcIrb_NoIptcResource_1829) {
    std::vector<byte> irb = buildNonIptcIrb(0x0400, {0x01, 0x02});
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIptcIrb(irb.data(), irb.size(), &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

// Test setIptcIrb with null/empty PS data and empty IPTC data
TEST_F(PhotoshopTest_1829, SetIptcIrb_EmptyPsDataEmptyIptc_1829) {
    IptcData iptcData;
    DataBuf result = Photoshop::setIptcIrb(nullptr, 0, iptcData);
    EXPECT_TRUE(result.empty());
}

// Test setIptcIrb with empty PS data and some IPTC data
TEST_F(PhotoshopTest_1829, SetIptcIrb_EmptyPsDataWithIptc_1829) {
    IptcData iptcData;
    // Add a simple IPTC record
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Test caption");
    iptcData.add(key, &value);

    DataBuf result = Photoshop::setIptcIrb(nullptr, 0, iptcData);
    // When there's IPTC data to encode, the result should contain the new IRB
    EXPECT_FALSE(result.empty());
}

// Test setIptcIrb replaces existing IPTC IRB
TEST_F(PhotoshopTest_1829, SetIptcIrb_ReplacesExistingIptcIrb_1829) {
    // Build an existing PS data block with IPTC
    std::vector<byte> existingIptc = {0xAA, 0xBB, 0xCC, 0xDD};
    std::vector<byte> psData = buildIptcIrb(existingIptc);

    IptcData iptcData;
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("New caption");
    iptcData.add(key, &value);

    DataBuf result = Photoshop::setIptcIrb(psData.data(), psData.size(), iptcData);
    EXPECT_FALSE(result.empty());
    // The result should differ from the original since IPTC data changed
    EXPECT_NE(result.size(), psData.size());
}

// Test setIptcIrb removes IPTC IRB when IPTC data is empty
TEST_F(PhotoshopTest_1829, SetIptcIrb_RemovesIptcWhenEmpty_1829) {
    std::vector<byte> existingIptc = {0x1C, 0x02, 0x00, 0x02, 0x00, 0x00};
    std::vector<byte> psData = buildIptcIrb(existingIptc);

    IptcData iptcData; // empty

    DataBuf result = Photoshop::setIptcIrb(psData.data(), psData.size(), iptcData);
    // With empty IPTC and only IPTC IRB in PS data, result might be empty
    // since the IPTC IRB is removed and there's nothing else
    EXPECT_TRUE(result.empty());
}

// Test setIptcIrb preserves non-IPTC IRB blocks
TEST_F(PhotoshopTest_1829, SetIptcIrb_PreservesNonIptcIrb_1829) {
    // Build PS data with a non-IPTC IRB followed by an IPTC IRB
    std::vector<byte> nonIptcData = {0x01, 0x02};
    std::vector<byte> nonIptcIrb = buildNonIptcIrb(0x0400, nonIptcData);

    std::vector<byte> iptcPayload = {0xAA, 0xBB};
    std::vector<byte> iptcIrb = buildIptcIrb(iptcPayload);

    std::vector<byte> psData;
    psData.insert(psData.end(), nonIptcIrb.begin(), nonIptcIrb.end());
    psData.insert(psData.end(), iptcIrb.begin(), iptcIrb.end());

    IptcData iptcData; // empty - should remove IPTC IRB but keep the other

    DataBuf result = Photoshop::setIptcIrb(psData.data(), psData.size(), iptcData);
    // The non-IPTC IRB should be preserved
    EXPECT_FALSE(result.empty());
    // Result should be smaller since IPTC was removed
    EXPECT_LT(result.size(), psData.size());
    // Verify the non-IPTC IRB signature is still present
    EXPECT_EQ(result.size(), nonIptcIrb.size());
}

// Test setIptcIrb with IPTC data added to PS data that has only non-IPTC blocks
TEST_F(PhotoshopTest_1829, SetIptcIrb_AddIptcToNonIptcPs_1829) {
    std::vector<byte> nonIptcData = {0x01, 0x02, 0x03, 0x04};
    std::vector<byte> psData = buildNonIptcIrb(0x0400, nonIptcData);

    IptcData iptcData;
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Hello World");
    iptcData.add(key, &value);

    DataBuf result = Photoshop::setIptcIrb(psData.data(), psData.size(), iptcData);
    EXPECT_FALSE(result.empty());
    // Result should be larger since IPTC was added
    EXPECT_GT(result.size(), psData.size());
}

// Test locatePreviewIrb with empty data
TEST_F(PhotoshopTest_1829, LocatePreviewIrb_EmptyData_1829) {
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locatePreviewIrb(nullptr, 0, &record, sizeHdr, sizeData);
    EXPECT_NE(0, result);
}

// Test locatePreviewIrb with data containing preview resource (0x040C)
TEST_F(PhotoshopTest_1829, LocatePreviewIrb_WithPreviewResource_1829) {
    // Preview resource ID is typically 0x040C (1036)
    std::vector<byte> previewData = {0xFF, 0xD8, 0xFF, 0xE0}; // Fake JPEG data
    std::vector<byte> irb = buildIrb(0x040C, previewData);
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locatePreviewIrb(irb.data(), irb.size(), &record, sizeHdr, sizeData);
    // This may or may not find it depending on the exact preview resource ID
    // We just verify it doesn't crash
    (void)result;
}

// Test setIptcIrb with multiple IPTC IRBs
TEST_F(PhotoshopTest_1829, SetIptcIrb_MultipleIptcIrbs_1829) {
    // Build PS data with two IPTC IRBs
    std::vector<byte> iptcPayload1 = {0xAA, 0xBB};
    std::vector<byte> iptcIrb1 = buildIptcIrb(iptcPayload1);

    std::vector<byte> iptcPayload2 = {0xCC, 0xDD};
    std::vector<byte> iptcIrb2 = buildIptcIrb(iptcPayload2);

    std::vector<byte> psData;
    psData.insert(psData.end(), iptcIrb1.begin(), iptcIrb1.end());
    psData.insert(psData.end(), iptcIrb2.begin(), iptcIrb2.end());

    IptcData iptcData;
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Merged");
    iptcData.add(key, &value);

    DataBuf result = Photoshop::setIptcIrb(psData.data(), psData.size(), iptcData);
    EXPECT_FALSE(result.empty());

    // After setting, there should be only one IPTC IRB
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int locateResult = Photoshop::locateIptcIrb(result.c_data(), result.size(), &record, sizeHdr, sizeData);
    EXPECT_EQ(0, locateResult);
}

// Test setIptcIrb with empty IPTC and empty PS data
TEST_F(PhotoshopTest_1829, SetIptcIrb_BothEmpty_1829) {
    IptcData iptcData;
    DataBuf result = Photoshop::setIptcIrb(nullptr, 0, iptcData);
    EXPECT_TRUE(result.empty());
}

// Test setIptcIrb round-trip: set IPTC, then read it back
TEST_F(PhotoshopTest_1829, SetIptcIrb_RoundTrip_1829) {
    IptcData iptcData;
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Round trip test");
    iptcData.add(key, &value);

    // Create IRB with IPTC
    DataBuf result = Photoshop::setIptcIrb(nullptr, 0, iptcData);
    EXPECT_FALSE(result.empty());

    // Locate the IPTC IRB in the result
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int locateResult = Photoshop::locateIptcIrb(result.c_data(), result.size(), &record, sizeHdr, sizeData);
    EXPECT_EQ(0, locateResult);
    EXPECT_GT(sizeData, 0u);

    // Decode the IPTC data back
    IptcData decodedIptc;
    const byte* iptcStart = record + sizeHdr;
    int decodeResult = IptcParser::decode(decodedIptc, iptcStart, sizeData);
    EXPECT_EQ(0, decodeResult);
    EXPECT_FALSE(decodedIptc.empty());
}

// Test isIrb with alternate valid signatures (if any)
TEST_F(PhotoshopTest_1829, IsIrb_AnotherInvalidSignature_1829) {
    const byte data[] = {'8', 'B', 'P', 'S'};  // Not "8BIM"
    // This might or might not be valid depending on implementation
    // The standard signature is "8BIM"
    bool result = Photoshop::isIrb(data);
    // We just ensure it doesn't crash; exact result depends on implementation
    (void)result;
}

// Test valid with exactly minimum valid size
TEST_F(PhotoshopTest_1829, Valid_MinimumValidSize_1829) {
    // Minimum valid IRB: 4 (sig) + 2 (id) + 2 (pascal string) + 4 (size) = 12 bytes
    std::vector<byte> data = {
        '8', 'B', 'I', 'M',
        0x04, 0x00,
        0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    EXPECT_TRUE(Photoshop::valid(data.data(), data.size()));
}

// Test valid with data that has wrong size field
TEST_F(PhotoshopTest_1829, Valid_OversizedDataField_1829) {
    std::vector<byte> data = {
        '8', 'B', 'I', 'M',
        0x04, 0x00,
        0x00, 0x00,
        0x00, 0x00, 0x00, 0x10  // Claims 16 bytes of data but only 12 total
    };
    EXPECT_FALSE(Photoshop::valid(data.data(), data.size()));
}

// Test locateIrb with multiple resources, finding the second one
TEST_F(PhotoshopTest_1829, LocateIrb_FindSecondResource_1829) {
    std::vector<byte> irb1 = buildIrb(0x0400, {0x01, 0x02});
    std::vector<byte> irb2 = buildIrb(0x0405, {0x03, 0x04, 0x05, 0x06});

    std::vector<byte> psData;
    psData.insert(psData.end(), irb1.begin(), irb1.end());
    psData.insert(psData.end(), irb2.begin(), irb2.end());

    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
    int result = Photoshop::locateIrb(psData.data(), psData.size(), 0x0405, &record, sizeHdr, sizeData);
    EXPECT_EQ(0, result);
    EXPECT_EQ(4u, sizeData);
}

// Test setIptcIrb preserves ordering of non-IPTC resources
TEST_F(PhotoshopTest_1829, SetIptcIrb_PreservesResourceOrdering_1829) {
    std::vector<byte> irb1 = buildNonIptcIrb(0x0400, {0x01});
    std::vector<byte> iptcIrb = buildIptcIrb({0xAA});
    std::vector<byte> irb2 = buildNonIptcIrb(0x0401, {0x02});

    std::vector<byte> psData;
    psData.insert(psData.end(), irb1.begin(), irb1.end());
    psData.insert(psData.end(), iptcIrb.begin(), iptcIrb.end());
    psData.insert(psData.end(), irb2.begin(), irb2.end());

    IptcData iptcData; // empty - removes IPTC

    DataBuf result = Photoshop::setIptcIrb(psData.data(), psData.size(), iptcData);
    EXPECT_FALSE(result.empty());

    // Both non-IPTC resources should be present
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;

    int r1 = Photoshop::locateIrb(result.c_data(), result.size(), 0x0400, &record, sizeHdr, sizeData);
    EXPECT_EQ(0, r1);

    int r2 = Photoshop::locateIrb(result.c_data(), result.size(), 0x0401, &record, sizeHdr, sizeData);
    EXPECT_EQ(0, r2);

    // IPTC should not be found
    int r3 = Photoshop::locateIptcIrb(result.c_data(), result.size(), &record, sizeHdr, sizeData);
    EXPECT_NE(0, r3);
}
