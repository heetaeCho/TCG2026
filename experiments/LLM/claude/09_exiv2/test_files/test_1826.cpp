#include <gtest/gtest.h>
#include <cstring>
#include <vector>

#include "exiv2/photoshop.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;

// Helper function to write a big-endian uint16_t
static void writeUShortBE(byte* buf, uint16_t val) {
    buf[0] = static_cast<byte>((val >> 8) & 0xFF);
    buf[1] = static_cast<byte>(val & 0xFF);
}

// Helper function to write a big-endian uint32_t
static void writeULongBE(byte* buf, uint32_t val) {
    buf[0] = static_cast<byte>((val >> 24) & 0xFF);
    buf[1] = static_cast<byte>((val >> 16) & 0xFF);
    buf[2] = static_cast<byte>((val >> 8) & 0xFF);
    buf[3] = static_cast<byte>(val & 0xFF);
}

// Helper to build a minimal valid IRB record
// Structure: "8BIM" (4 bytes) + type (2 bytes) + pascal string size byte + padding + data size (4 bytes) + data
static std::vector<byte> buildIrbRecord(uint16_t type, const std::vector<byte>& data, byte pascalStringLen = 0) {
    std::vector<byte> record;
    // "8BIM" signature
    record.push_back('8');
    record.push_back('B');
    record.push_back('I');
    record.push_back('M');
    // type (big endian)
    record.push_back(static_cast<byte>((type >> 8) & 0xFF));
    record.push_back(static_cast<byte>(type & 0xFF));
    // Pascal string: size byte (pascalStringLen) followed by that many chars
    // psSize = pPsData[position] + 1, then padded to even
    record.push_back(pascalStringLen);
    // Add pascalStringLen bytes of string content
    for (byte i = 0; i < pascalStringLen; i++) {
        record.push_back('A');
    }
    // psSize = pascalStringLen + 1; if odd, add 1 more for padding
    byte psSize = pascalStringLen + 1;
    if (psSize & 1) {
        record.push_back(0); // padding byte
    }
    // Data size (big endian)
    uint32_t dataSize = static_cast<uint32_t>(data.size());
    record.push_back(static_cast<byte>((dataSize >> 24) & 0xFF));
    record.push_back(static_cast<byte>((dataSize >> 16) & 0xFF));
    record.push_back(static_cast<byte>((dataSize >> 8) & 0xFF));
    record.push_back(static_cast<byte>(dataSize & 0xFF));
    // Data
    record.insert(record.end(), data.begin(), data.end());
    // Pad data to even size
    if (dataSize & 1) {
        record.push_back(0);
    }
    return record;
}

class PhotoshopLocateIrbTest_1826 : public ::testing::Test {
protected:
    const byte* record = nullptr;
    uint32_t sizeHdr = 0;
    uint32_t sizeData = 0;
};

// Test: Data smaller than 12 bytes should return 3
TEST_F(PhotoshopLocateIrbTest_1826, TooSmallData_Returns3_1826) {
    byte data[11] = {};
    int result = Photoshop::locateIrb(data, 11, 0x0404, &record, sizeHdr, sizeData);
    EXPECT_EQ(result, 3);
}

// Test: Empty data (size 0) should return 3
TEST_F(PhotoshopLocateIrbTest_1826, EmptyData_Returns3_1826) {
    byte data[1] = {0};
    int result = Photoshop::locateIrb(data, 0, 0x0404, &record, sizeHdr, sizeData);
    EXPECT_EQ(result, 3);
}

// Test: Exactly 12 bytes but not starting with "8BIM" should return 3
TEST_F(PhotoshopLocateIrbTest_1826, NotIrbSignature_Returns3_1826) {
    byte data[12] = {0};
    int result = Photoshop::locateIrb(data, 12, 0x0404, &record, sizeHdr, sizeData);
    EXPECT_EQ(result, 3);
}

// Test: Valid IRB record with matching tag should return 0
TEST_F(PhotoshopLocateIrbTest_1826, ValidIrbMatchingTag_Returns0_1826) {
    uint16_t targetTag = 0x0404;
    std::vector<byte> payload = {0x01, 0x02, 0x03, 0x04};
    std::vector<byte> data = buildIrbRecord(targetTag, payload);

    int result = Photoshop::locateIrb(data.data(), data.size(), targetTag, &record, sizeHdr, sizeData);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sizeData, 4u);
    EXPECT_NE(record, nullptr);
    EXPECT_EQ(record, data.data());
}

// Test: Valid IRB record with non-matching tag should return 3 (no more records)
TEST_F(PhotoshopLocateIrbTest_1826, ValidIrbNonMatchingTag_Returns3_1826) {
    uint16_t recordTag = 0x0404;
    uint16_t searchTag = 0x0425;
    std::vector<byte> payload = {0x01, 0x02, 0x03, 0x04};
    std::vector<byte> data = buildIrbRecord(recordTag, payload);

    int result = Photoshop::locateIrb(data.data(), data.size(), searchTag, &record, sizeHdr, sizeData);
    EXPECT_EQ(result, 3);
}

// Test: Multiple IRB records, target is in the second one
TEST_F(PhotoshopLocateIrbTest_1826, MultipleRecords_MatchSecond_Returns0_1826) {
    uint16_t firstTag = 0x0404;
    uint16_t secondTag = 0x0425;
    std::vector<byte> payload1 = {0x01, 0x02};
    std::vector<byte> payload2 = {0xAA, 0xBB, 0xCC, 0xDD};

    std::vector<byte> rec1 = buildIrbRecord(firstTag, payload1);
    std::vector<byte> rec2 = buildIrbRecord(secondTag, payload2);

    std::vector<byte> data;
    data.insert(data.end(), rec1.begin(), rec1.end());
    data.insert(data.end(), rec2.begin(), rec2.end());

    int result = Photoshop::locateIrb(data.data(), data.size(), secondTag, &record, sizeHdr, sizeData);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sizeData, 4u);
    // record should point to the second record
    EXPECT_EQ(record, data.data() + rec1.size());
}

// Test: Valid IRB with zero-length data
TEST_F(PhotoshopLocateIrbTest_1826, ValidIrbZeroLengthData_Returns0_1826) {
    uint16_t targetTag = 0x0404;
    std::vector<byte> payload; // empty
    std::vector<byte> data = buildIrbRecord(targetTag, payload);

    int result = Photoshop::locateIrb(data.data(), data.size(), targetTag, &record, sizeHdr, sizeData);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sizeData, 0u);
    EXPECT_NE(record, nullptr);
}

// Test: IRB with data size exceeding remaining data should return -2
TEST_F(PhotoshopLocateIrbTest_1826, DataSizeExceedsRemaining_ReturnsMinus2_1826) {
    // Build a record with claimed data size larger than actual
    std::vector<byte> data;
    // "8BIM"
    data.push_back('8'); data.push_back('B'); data.push_back('I'); data.push_back('M');
    // type
    data.push_back(0x04); data.push_back(0x04);
    // Pascal string: length 0, then padded
    data.push_back(0x00); // pascal string length = 0, psSize = 1, padded to 2
    data.push_back(0x00); // padding
    // Data size: claim 100 bytes but we won't provide them
    writeULongBE(data.data() + data.size(), 100);
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x64);

    int result = Photoshop::locateIrb(data.data(), data.size(), 0x0404, &record, sizeHdr, sizeData);
    EXPECT_EQ(result, -2);
}

// Test: IRB truncated before data size field should return -2
TEST_F(PhotoshopLocateIrbTest_1826, TruncatedBeforeDataSize_ReturnsMinus2_1826) {
    // Build just enough to pass isIrb but not enough for data size
    std::vector<byte> data;
    // "8BIM"
    data.push_back('8'); data.push_back('B'); data.push_back('I'); data.push_back('M');
    // type
    data.push_back(0x04); data.push_back(0x04);
    // Pascal string: length 0, psSize = 1, padded to 2
    data.push_back(0x00);
    data.push_back(0x00);
    // Only 2 bytes for data size instead of 4 — truncated
    data.push_back(0x00);
    data.push_back(0x00);
    // Total = 12 bytes, position after pascal = 8, position + 4 = 12, sizePsData = 10
    // Actually let's be more precise about sizes

    // We have 10 bytes total. position after "8BIM" + type + pascal = 4+2+2 = 8
    // position + 4 = 12 > 10 = sizePsData, so should return -2

    int result = Photoshop::locateIrb(data.data(), data.size(), 0x0404, &record, sizeHdr, sizeData);
    EXPECT_EQ(result, -2);
}

// Test: Size exactly 12 with valid IRB signature but data size is 0, matching tag
TEST_F(PhotoshopLocateIrbTest_1826, ExactlyMinimalSize_MatchingTag_1826) {
    std::vector<byte> data;
    // "8BIM"
    data.push_back('8'); data.push_back('B'); data.push_back('I'); data.push_back('M');
    // type = 0x0404
    data.push_back(0x04); data.push_back(0x04);
    // Pascal string: length 0 => psSize = 1, padded to 2
    data.push_back(0x00);
    data.push_back(0x00);
    // Data size = 0
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x00);

    ASSERT_EQ(data.size(), 12u);

    int result = Photoshop::locateIrb(data.data(), data.size(), 0x0404, &record, sizeHdr, sizeData);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sizeData, 0u);
    EXPECT_EQ(record, data.data());
}

// Test: Valid IRB with odd-length data (tests padding handling)
TEST_F(PhotoshopLocateIrbTest_1826, OddLengthDataPadding_1826) {
    uint16_t tag1 = 0x0401;
    uint16_t tag2 = 0x0402;
    std::vector<byte> payload1 = {0xAA, 0xBB, 0xCC}; // 3 bytes (odd)
    std::vector<byte> payload2 = {0xDD, 0xEE};

    std::vector<byte> rec1 = buildIrbRecord(tag1, payload1);
    std::vector<byte> rec2 = buildIrbRecord(tag2, payload2);

    std::vector<byte> data;
    data.insert(data.end(), rec1.begin(), rec1.end());
    data.insert(data.end(), rec2.begin(), rec2.end());

    int result = Photoshop::locateIrb(data.data(), data.size(), tag2, &record, sizeHdr, sizeData);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sizeData, 2u);
}

// Test: sizeHdr is correctly computed (psSize + 10)
TEST_F(PhotoshopLocateIrbTest_1826, SizeHdrCorrectlyComputed_PascalLen0_1826) {
    uint16_t targetTag = 0x0404;
    std::vector<byte> payload = {0x01, 0x02};
    // pascalStringLen = 0 => psSize = 0+1 = 1, padded to 2
    // sizeHdr = psSize + 10 = 2 + 10 = 12
    std::vector<byte> data = buildIrbRecord(targetTag, payload, 0);

    int result = Photoshop::locateIrb(data.data(), data.size(), targetTag, &record, sizeHdr, sizeData);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sizeHdr, 12u);
}

// Test: sizeHdr with non-zero pascal string length
TEST_F(PhotoshopLocateIrbTest_1826, SizeHdrCorrectlyComputed_PascalLen3_1826) {
    uint16_t targetTag = 0x0404;
    std::vector<byte> payload = {0x01, 0x02};
    // pascalStringLen = 3 => psSize = 3+1 = 4 (even, no padding needed)
    // sizeHdr = 4 + 10 = 14
    std::vector<byte> data = buildIrbRecord(targetTag, payload, 3);

    int result = Photoshop::locateIrb(data.data(), data.size(), targetTag, &record, sizeHdr, sizeData);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sizeHdr, 14u);
}

// Test: sizeHdr with pascal string length that results in odd psSize needing padding
TEST_F(PhotoshopLocateIrbTest_1826, SizeHdrCorrectlyComputed_PascalLen2_1826) {
    uint16_t targetTag = 0x0404;
    std::vector<byte> payload = {0x01, 0x02};
    // pascalStringLen = 2 => psSize = 2+1 = 3 (odd), padded to 4
    // sizeHdr = 4 + 10 = 14
    std::vector<byte> data = buildIrbRecord(targetTag, payload, 2);

    int result = Photoshop::locateIrb(data.data(), data.size(), targetTag, &record, sizeHdr, sizeData);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sizeHdr, 14u);
}

// Test: Boundary - sizePsData exactly 11 should return 3
TEST_F(PhotoshopLocateIrbTest_1826, Size11_Returns3_1826) {
    byte data[12] = {'8', 'B', 'I', 'M', 0, 0, 0, 0, 0, 0, 0, 0};
    int result = Photoshop::locateIrb(data, 11, 0x0404, &record, sizeHdr, sizeData);
    EXPECT_EQ(result, 3);
}

// Test: Multiple records, none matching, all valid - should return 3
TEST_F(PhotoshopLocateIrbTest_1826, MultipleRecords_NoneMatching_Returns3_1826) {
    std::vector<byte> rec1 = buildIrbRecord(0x0401, {0x01, 0x02});
    std::vector<byte> rec2 = buildIrbRecord(0x0402, {0x03, 0x04});
    std::vector<byte> rec3 = buildIrbRecord(0x0403, {0x05, 0x06});

    std::vector<byte> data;
    data.insert(data.end(), rec1.begin(), rec1.end());
    data.insert(data.end(), rec2.begin(), rec2.end());
    data.insert(data.end(), rec3.begin(), rec3.end());

    int result = Photoshop::locateIrb(data.data(), data.size(), 0x0999, &record, sizeHdr, sizeData);
    EXPECT_EQ(result, 3);
}

// Test: Record pointer points to the start of the matching IRB block
TEST_F(PhotoshopLocateIrbTest_1826, RecordPointerPointsToIrbStart_1826) {
    uint16_t targetTag = 0x0404;
    std::vector<byte> payload = {0xDE, 0xAD, 0xBE, 0xEF};
    std::vector<byte> data = buildIrbRecord(targetTag, payload);

    int result = Photoshop::locateIrb(data.data(), data.size(), targetTag, &record, sizeHdr, sizeData);
    EXPECT_EQ(result, 0);
    // Verify that the record starts with "8BIM"
    EXPECT_EQ(record[0], '8');
    EXPECT_EQ(record[1], 'B');
    EXPECT_EQ(record[2], 'I');
    EXPECT_EQ(record[3], 'M');
}

// Test: First record matches when there are multiple records
TEST_F(PhotoshopLocateIrbTest_1826, FirstRecordMatches_1826) {
    uint16_t targetTag = 0x0401;
    std::vector<byte> rec1 = buildIrbRecord(0x0401, {0xAA});
    std::vector<byte> rec2 = buildIrbRecord(0x0402, {0xBB, 0xCC});

    std::vector<byte> data;
    data.insert(data.end(), rec1.begin(), rec1.end());
    data.insert(data.end(), rec2.begin(), rec2.end());

    int result = Photoshop::locateIrb(data.data(), data.size(), targetTag, &record, sizeHdr, sizeData);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sizeData, 1u);
    EXPECT_EQ(record, data.data());
}

// Test: Large data size that is valid
TEST_F(PhotoshopLocateIrbTest_1826, LargeValidData_1826) {
    uint16_t targetTag = 0x0404;
    std::vector<byte> payload(1000, 0x42);
    std::vector<byte> data = buildIrbRecord(targetTag, payload);

    int result = Photoshop::locateIrb(data.data(), data.size(), targetTag, &record, sizeHdr, sizeData);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(sizeData, 1000u);
}
