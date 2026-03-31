#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>
#include <vector>
#include <cstring>

using namespace Exiv2;

class IptcParserDecodeTest_703 : public ::testing::Test {
protected:
    IptcData iptcData;
    
    void SetUp() override {
        // Suppress warnings during tests to avoid noise
        LogMsg::setLevel(LogMsg::mute);
    }
    
    void TearDown() override {
        LogMsg::setLevel(LogMsg::warn);
    }
    
    // Helper: create a simple IPTC record
    // Format: marker(0x1c) + record(1 byte) + dataset(1 byte) + size(2 bytes big-endian) + data
    std::vector<byte> makeIptcRecord(uint8_t record, uint8_t dataset, const std::string& data) {
        std::vector<byte> result;
        result.push_back(0x1c); // marker
        result.push_back(static_cast<byte>(record));
        result.push_back(static_cast<byte>(dataset));
        uint16_t len = static_cast<uint16_t>(data.size());
        result.push_back(static_cast<byte>((len >> 8) & 0xFF));
        result.push_back(static_cast<byte>(len & 0xFF));
        for (char c : data) {
            result.push_back(static_cast<byte>(c));
        }
        return result;
    }
};

// Test with empty data (size = 0)
TEST_F(IptcParserDecodeTest_703, EmptyData_703) {
    byte data[] = {0};
    int rc = IptcParser::decode(iptcData, data, 0);
    EXPECT_EQ(rc, 0);
    EXPECT_TRUE(iptcData.empty());
}

// Test with nullptr and size 0
TEST_F(IptcParserDecodeTest_703, NullptrWithZeroSize_703) {
    int rc = IptcParser::decode(iptcData, nullptr, 0);
    EXPECT_EQ(rc, 0);
    EXPECT_TRUE(iptcData.empty());
}

// Test with data too small to contain any record (less than 6 bytes)
TEST_F(IptcParserDecodeTest_703, DataTooSmallForRecord_703) {
    byte data[] = {0x1c, 0x02, 0x05, 0x00};
    int rc = IptcParser::decode(iptcData, data, 4);
    EXPECT_EQ(rc, 0);
    EXPECT_TRUE(iptcData.empty());
}

// Test with exactly 5 bytes (still less than 6 needed for loop)
TEST_F(IptcParserDecodeTest_703, FiveBytesNotEnough_703) {
    byte data[] = {0x1c, 0x02, 0x05, 0x00, 0x01};
    int rc = IptcParser::decode(iptcData, data, 5);
    EXPECT_EQ(rc, 0);
    EXPECT_TRUE(iptcData.empty());
}

// Test with a single valid IPTC record (record 2, dataset 5 = ObjectName)
TEST_F(IptcParserDecodeTest_703, SingleValidRecord_703) {
    std::vector<byte> record = makeIptcRecord(0x02, 0x05, "Test");
    int rc = IptcParser::decode(iptcData, record.data(), record.size());
    EXPECT_EQ(rc, 0);
    EXPECT_FALSE(iptcData.empty());
}

// Test with a valid record with empty data (size = 0)
TEST_F(IptcParserDecodeTest_703, ValidRecordWithEmptyData_703) {
    std::vector<byte> record = makeIptcRecord(0x02, 0x05, "");
    int rc = IptcParser::decode(iptcData, record.data(), record.size());
    EXPECT_EQ(rc, 0);
}

// Test with multiple valid records
TEST_F(IptcParserDecodeTest_703, MultipleValidRecords_703) {
    std::vector<byte> rec1 = makeIptcRecord(0x02, 0x05, "Title");
    std::vector<byte> rec2 = makeIptcRecord(0x02, 0x78, "Caption");
    
    std::vector<byte> combined;
    combined.insert(combined.end(), rec1.begin(), rec1.end());
    combined.insert(combined.end(), rec2.begin(), rec2.end());
    
    int rc = IptcParser::decode(iptcData, combined.data(), combined.size());
    EXPECT_EQ(rc, 0);
    EXPECT_GE(iptcData.count(), 1u);
}

// Test with data that doesn't start with marker (garbage before marker)
TEST_F(IptcParserDecodeTest_703, GarbageBeforeMarker_703) {
    // Put some non-marker bytes before a valid record
    std::vector<byte> record = makeIptcRecord(0x02, 0x05, "Test");
    std::vector<byte> data;
    data.push_back(0x00); // garbage byte (not 0x1c)
    data.insert(data.end(), record.begin(), record.end());
    
    int rc = IptcParser::decode(iptcData, data.data(), data.size());
    EXPECT_EQ(rc, 0);
}

// Test with no marker bytes at all
TEST_F(IptcParserDecodeTest_703, NoMarkerBytes_703) {
    byte data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    int rc = IptcParser::decode(iptcData, data, sizeof(data));
    EXPECT_EQ(rc, 0);
    EXPECT_TRUE(iptcData.empty());
}

// Test extended record with sizeOfSize > 4 should return error 5
TEST_F(IptcParserDecodeTest_703, ExtendedSizeOfSizeTooLarge_703) {
    // marker + record + dataset + extended size indicator
    // extTest with bit 7 set, sizeOfSize = 5 (0x80 | 0x05 = 0x85 in first byte, 0x05 in second)
    byte data[] = {
        0x1c, 0x02, 0x05,
        0x80, 0x05,  // sizeOfSize = 5 (too large, > 4)
        0x00, 0x00, 0x00, 0x00, 0x00
    };
    int rc = IptcParser::decode(iptcData, data, sizeof(data));
    EXPECT_EQ(rc, 5);
}

// Test extended record with sizeOfSize = 4 (max allowed)
TEST_F(IptcParserDecodeTest_703, ExtendedSizeOfSizeMaxAllowed_703) {
    // sizeOfSize = 4, then 4 bytes of size (small value), then data
    byte data[] = {
        0x1c, 0x02, 0x05,
        0x80, 0x04,  // sizeOfSize = 4
        0x00, 0x00, 0x00, 0x04, // sizeData = 4
        'T', 'e', 's', 't'
    };
    int rc = IptcParser::decode(iptcData, data, sizeof(data));
    EXPECT_EQ(rc, 0);
}

// Test extended record where sizeOfSize exceeds remaining data → return 6
TEST_F(IptcParserDecodeTest_703, ExtendedSizeOfSizeExceedsData_703) {
    // sizeOfSize = 4 but only 2 bytes remain after the size field
    byte data[] = {
        0x1c, 0x02, 0x05,
        0x80, 0x04,  // sizeOfSize = 4
        0x00, 0x00   // only 2 bytes available, need 4
    };
    int rc = IptcParser::decode(iptcData, data, sizeof(data));
    EXPECT_EQ(rc, 6);
}

// Test where sizeData exceeds remaining data → return 7
TEST_F(IptcParserDecodeTest_703, SizeDataExceedsRemainingData_703) {
    byte data[] = {
        0x1c, 0x02, 0x05,
        0x00, 0x10,  // sizeData = 16, but we only have a few bytes left
        'T', 'e'     // only 2 bytes of data
    };
    int rc = IptcParser::decode(iptcData, data, sizeof(data));
    EXPECT_EQ(rc, 7);
}

// Test that decode clears existing iptcData
TEST_F(IptcParserDecodeTest_703, DecodeClearsExistingData_703) {
    // First decode a valid record
    std::vector<byte> record = makeIptcRecord(0x02, 0x05, "First");
    int rc = IptcParser::decode(iptcData, record.data(), record.size());
    EXPECT_EQ(rc, 0);
    size_t firstCount = iptcData.count();
    
    // Now decode with empty data - should clear
    rc = IptcParser::decode(iptcData, record.data(), 0);
    EXPECT_EQ(rc, 0);
    EXPECT_TRUE(iptcData.empty());
}

// Test with sizeOfSize = 1 (extended format, minimal)
TEST_F(IptcParserDecodeTest_703, ExtendedSizeOfSizeOne_703) {
    byte data[] = {
        0x1c, 0x02, 0x05,
        0x80, 0x01,  // sizeOfSize = 1
        0x04,        // sizeData = 4
        'T', 'e', 's', 't'
    };
    int rc = IptcParser::decode(iptcData, data, sizeof(data));
    EXPECT_EQ(rc, 0);
}

// Test with extended sizeOfSize = 0 (edge case)
TEST_F(IptcParserDecodeTest_703, ExtendedSizeOfSizeZero_703) {
    byte data[] = {
        0x1c, 0x02, 0x05,
        0x80, 0x00,  // sizeOfSize = 0, sizeData = 0
        // No size bytes, no data
    };
    int rc = IptcParser::decode(iptcData, data, sizeof(data));
    EXPECT_EQ(rc, 0);
}

// Test record 1 (envelope record)
TEST_F(IptcParserDecodeTest_703, EnvelopeRecord_703) {
    std::vector<byte> record = makeIptcRecord(0x01, 0x00, "\x00\x04");
    int rc = IptcParser::decode(iptcData, record.data(), record.size());
    EXPECT_EQ(rc, 0);
}

// Test with sizeData exactly equal to remaining data
TEST_F(IptcParserDecodeTest_703, SizeDataExactlyFitsRemaining_703) {
    byte data[] = {
        0x1c, 0x02, 0x05,
        0x00, 0x03,  // sizeData = 3
        'A', 'B', 'C'
    };
    int rc = IptcParser::decode(iptcData, data, sizeof(data));
    EXPECT_EQ(rc, 0);
}

// Test that exactly 6 bytes with valid marker and zero-length data works
TEST_F(IptcParserDecodeTest_703, ExactlySixBytesZeroLength_703) {
    byte data[] = {
        0x1c, 0x02, 0x05,
        0x00, 0x00  // sizeData = 0
    };
    int rc = IptcParser::decode(iptcData, data, 5);
    // 5 bytes is less than 6, so the while loop won't enter
    EXPECT_EQ(rc, 0);
    EXPECT_TRUE(iptcData.empty());
}

// Test with exactly 6 bytes including marker (minimum valid)
TEST_F(IptcParserDecodeTest_703, MinimumValidRecordSixBytes_703) {
    // 1 marker + 1 record + 1 dataset + 2 size + 0 data = 5 bytes from marker
    // But we need pEnd - pRead >= 6 at the start of the loop
    // So we need at least 6 bytes total
    byte data[] = {
        0x1c, 0x02, 0x05,
        0x00, 0x00, // sizeData = 0
        0x00        // extra byte to make 6
    };
    int rc = IptcParser::decode(iptcData, data, 6);
    EXPECT_EQ(rc, 0);
}

// Test encode and decode roundtrip
TEST_F(IptcParserDecodeTest_703, EncodeDecodeRoundtrip_703) {
    // First create a valid record and decode it
    std::vector<byte> record = makeIptcRecord(0x02, 0x05, "TestTitle");
    int rc = IptcParser::decode(iptcData, record.data(), record.size());
    EXPECT_EQ(rc, 0);
    
    if (!iptcData.empty()) {
        // Encode
        DataBuf encoded = IptcParser::encode(iptcData);
        
        // Decode the encoded data
        IptcData iptcData2;
        if (encoded.size() > 0) {
            rc = IptcParser::decode(iptcData2, encoded.data(), encoded.size());
            EXPECT_EQ(rc, 0);
            EXPECT_EQ(iptcData.count(), iptcData2.count());
        }
    }
}

// Test extended size with sizeOfSize = 2
TEST_F(IptcParserDecodeTest_703, ExtendedSizeOfSizeTwo_703) {
    byte data[] = {
        0x1c, 0x02, 0x05,
        0x80, 0x02,     // sizeOfSize = 2
        0x00, 0x04,     // sizeData = 4
        'T', 'e', 's', 't'
    };
    int rc = IptcParser::decode(iptcData, data, sizeof(data));
    EXPECT_EQ(rc, 0);
}

// Test with sizeOfSize = 3 in extended format
TEST_F(IptcParserDecodeTest_703, ExtendedSizeOfSizeThree_703) {
    byte data[] = {
        0x1c, 0x02, 0x05,
        0x80, 0x03,        // sizeOfSize = 3
        0x00, 0x00, 0x02,  // sizeData = 2
        'A', 'B'
    };
    int rc = IptcParser::decode(iptcData, data, sizeof(data));
    EXPECT_EQ(rc, 0);
}

// Test that data with only non-marker bytes still returns 0
TEST_F(IptcParserDecodeTest_703, AllNonMarkerBytes_703) {
    byte data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    int rc = IptcParser::decode(iptcData, data, sizeof(data));
    EXPECT_EQ(rc, 0);
    EXPECT_TRUE(iptcData.empty());
}

// Test with marker bytes but wrong record forming invalid data still returns within expected range
TEST_F(IptcParserDecodeTest_703, MarkerWithInvalidSizeData_703) {
    // sizeData = 0xFFFF which is larger than remaining data
    byte data[] = {
        0x1c, 0x02, 0x05,
        0xFF, 0xFF,  // sizeData = 65535, way more than remaining
        0x00
    };
    int rc = IptcParser::decode(iptcData, data, sizeof(data));
    // sizeData (65535) > remaining (1), so should return 7
    EXPECT_EQ(rc, 7);
}

// Test with multiple markers, second one having invalid size
TEST_F(IptcParserDecodeTest_703, SecondRecordInvalidSize_703) {
    byte data[] = {
        // First record: valid
        0x1c, 0x02, 0x05,
        0x00, 0x02,  // sizeData = 2
        'A', 'B',
        // Second record: invalid size
        0x1c, 0x02, 0x78,
        0x00, 0xFF,  // sizeData = 255, exceeds remaining
    };
    int rc = IptcParser::decode(iptcData, data, sizeof(data));
    EXPECT_EQ(rc, 7);
}

// Test encode with empty IptcData
TEST_F(IptcParserDecodeTest_703, EncodeEmptyData_703) {
    DataBuf encoded = IptcParser::encode(iptcData);
    // Empty data should produce empty or minimal buffer
    EXPECT_TRUE(encoded.size() == 0 || encoded.data() != nullptr);
}
