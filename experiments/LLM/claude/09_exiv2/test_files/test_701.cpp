#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <cstring>

#include "exiv2/iptc.hpp"
#include "exiv2/slice.hpp"
#include "exiv2/types.hpp"
#include "exiv2/error.hpp"
#include "exiv2/datasets.hpp"

using namespace Exiv2;

class IptcDataPrintStructureTest_701 : public ::testing::Test {
protected:
    IptcData iptcData;
    std::ostringstream oss;
};

// Test: Empty input (size < 3) should produce no output
TEST_F(IptcDataPrintStructureTest_701, EmptyBytes_701) {
    std::vector<byte> data;
    auto slice = makeSlice(data.data(), 0, data.size());
    IptcData::printStructure(oss, slice, 0);
    EXPECT_TRUE(oss.str().empty());
}

// Test: Input with exactly 1 byte (size < 3) should produce no output
TEST_F(IptcDataPrintStructureTest_701, OneByte_701) {
    std::vector<byte> data = {0x1c};
    auto slice = makeSlice(data.data(), 0, data.size());
    IptcData::printStructure(oss, slice, 0);
    EXPECT_TRUE(oss.str().empty());
}

// Test: Input with exactly 2 bytes (size < 3) should produce no output
TEST_F(IptcDataPrintStructureTest_701, TwoBytes_701) {
    std::vector<byte> data = {0x1c, 0x02};
    auto slice = makeSlice(data.data(), 0, data.size());
    IptcData::printStructure(oss, slice, 0);
    EXPECT_TRUE(oss.str().empty());
}

// Test: Input with 3 bytes but no 0x1c marker should output header only
TEST_F(IptcDataPrintStructureTest_701, ThreeBytesNoMarker_701) {
    std::vector<byte> data = {0x00, 0x00, 0x00};
    auto slice = makeSlice(data.data(), 0, data.size());
    IptcData::printStructure(oss, slice, 0);
    // The function skips bytes until it finds 0x1c. If none found it just prints header.
    std::string output = oss.str();
    EXPECT_NE(output.find("Record"), std::string::npos);
    EXPECT_NE(output.find("DataSet"), std::string::npos);
}

// Test: Valid single IPTC record with zero-length data
TEST_F(IptcDataPrintStructureTest_701, SingleRecordZeroLength_701) {
    // 0x1c, record=2, dataset=0, length=0 (big-endian: 0x00, 0x00)
    std::vector<byte> data = {0x1c, 0x02, 0x00, 0x00, 0x00};
    auto slice = makeSlice(data.data(), 0, data.size());
    IptcData::printStructure(oss, slice, 0);
    std::string output = oss.str();
    EXPECT_NE(output.find("Record"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
}

// Test: Valid single IPTC record with some data
TEST_F(IptcDataPrintStructureTest_701, SingleRecordWithData_701) {
    // Record 2, Dataset 5 (Object Name), length=5, data="Hello"
    std::vector<byte> data = {0x1c, 0x02, 0x05, 0x00, 0x05, 'H', 'e', 'l', 'l', 'o'};
    auto slice = makeSlice(data.data(), 0, data.size());
    IptcData::printStructure(oss, slice, 0);
    std::string output = oss.str();
    EXPECT_NE(output.find("Hello"), std::string::npos);
    EXPECT_NE(output.find("5"), std::string::npos);
}

// Test: Multiple consecutive IPTC records
TEST_F(IptcDataPrintStructureTest_701, MultipleRecords_701) {
    // Record 1: record=2, dataset=5, length=3, data="ABC"
    // Record 2: record=2, dataset=120, length=2, data="XY"
    std::vector<byte> data = {
        0x1c, 0x02, 0x05, 0x00, 0x03, 'A', 'B', 'C',
        0x1c, 0x02, 0x78, 0x00, 0x02, 'X', 'Y'
    };
    auto slice = makeSlice(data.data(), 0, data.size());
    IptcData::printStructure(oss, slice, 0);
    std::string output = oss.str();
    EXPECT_NE(output.find("ABC"), std::string::npos);
    EXPECT_NE(output.find("XY"), std::string::npos);
}

// Test: Data with leading non-0x1c bytes that are skipped
TEST_F(IptcDataPrintStructureTest_701, LeadingGarbageBeforeMarker_701) {
    // Some garbage bytes, then a valid record
    std::vector<byte> data = {
        0x00, 0xFF, 0xAA,
        0x1c, 0x02, 0x05, 0x00, 0x02, 'H', 'i'
    };
    auto slice = makeSlice(data.data(), 0, data.size());
    IptcData::printStructure(oss, slice, 0);
    std::string output = oss.str();
    EXPECT_NE(output.find("Hi"), std::string::npos);
}

// Test: Record that would exceed buffer should throw (corrupt metadata)
TEST_F(IptcDataPrintStructureTest_701, CorruptedMetadataLengthTooLarge_701) {
    // Record with length=100 but only 2 bytes of data available
    std::vector<byte> data = {0x1c, 0x02, 0x05, 0x00, 0x64, 'A', 'B'};
    auto slice = makeSlice(data.data(), 0, data.size());
    EXPECT_THROW(IptcData::printStructure(oss, slice, 0), Exiv2::Error);
}

// Test: Buffer too short for length field (less than 5 bytes after marker)
TEST_F(IptcDataPrintStructureTest_701, CorruptedMetadataTooShortForLength_701) {
    // 0x1c at position 0, but only 4 bytes total (need at least 5 after marker position)
    std::vector<byte> data = {0x1c, 0x02, 0x05, 0x00};
    auto slice = makeSlice(data.data(), 0, data.size());
    EXPECT_THROW(IptcData::printStructure(oss, slice, 0), Exiv2::Error);
}

// Test: Data longer than 40 bytes should be truncated with "..."
TEST_F(IptcDataPrintStructureTest_701, DataTruncatedOver40Bytes_701) {
    // Create a record with 50 bytes of data
    std::vector<byte> data;
    data.push_back(0x1c);
    data.push_back(0x02);
    data.push_back(0x05);
    data.push_back(0x00);
    data.push_back(0x32); // 50 in decimal
    for (int i = 0; i < 50; i++) {
        data.push_back('A');
    }
    auto slice = makeSlice(data.data(), 0, data.size());
    IptcData::printStructure(oss, slice, 0);
    std::string output = oss.str();
    EXPECT_NE(output.find("..."), std::string::npos);
}

// Test: Data exactly 40 bytes should NOT have "..."
TEST_F(IptcDataPrintStructureTest_701, DataExactly40Bytes_701) {
    std::vector<byte> data;
    data.push_back(0x1c);
    data.push_back(0x02);
    data.push_back(0x05);
    data.push_back(0x00);
    data.push_back(0x28); // 40 in decimal
    for (int i = 0; i < 40; i++) {
        data.push_back('B');
    }
    auto slice = makeSlice(data.data(), 0, data.size());
    IptcData::printStructure(oss, slice, 0);
    std::string output = oss.str();
    EXPECT_EQ(output.find("..."), std::string::npos);
}

// Test: Header output contains expected column names
TEST_F(IptcDataPrintStructureTest_701, HeaderContainsExpectedColumns_701) {
    std::vector<byte> data = {0x1c, 0x02, 0x00, 0x00, 0x00};
    auto slice = makeSlice(data.data(), 0, data.size());
    IptcData::printStructure(oss, slice, 0);
    std::string output = oss.str();
    EXPECT_NE(output.find("Record"), std::string::npos);
    EXPECT_NE(output.find("DataSet"), std::string::npos);
    EXPECT_NE(output.find("Name"), std::string::npos);
    EXPECT_NE(output.find("Length"), std::string::npos);
    EXPECT_NE(output.find("Data"), std::string::npos);
}

// Test: Stops parsing when a non-0x1c byte is encountered after valid records
TEST_F(IptcDataPrintStructureTest_701, StopsAtNonMarkerByte_701) {
    // First valid record, then a non-0x1c byte, then what would be another record
    std::vector<byte> data = {
        0x1c, 0x02, 0x05, 0x00, 0x02, 'H', 'i',
        0xFF, // non-marker byte - should stop here
        0x1c, 0x02, 0x05, 0x00, 0x02, 'N', 'o'
    };
    auto slice = makeSlice(data.data(), 0, data.size());
    IptcData::printStructure(oss, slice, 0);
    std::string output = oss.str();
    EXPECT_NE(output.find("Hi"), std::string::npos);
    EXPECT_EQ(output.find("No"), std::string::npos);
}

// Test: Depth parameter affects indentation
TEST_F(IptcDataPrintStructureTest_701, DepthAffectsIndentation_701) {
    std::vector<byte> data = {0x1c, 0x02, 0x00, 0x00, 0x00};
    auto slice = makeSlice(data.data(), 0, data.size());

    std::ostringstream oss1, oss2;
    IptcData::printStructure(oss1, slice, 0);
    IptcData::printStructure(oss2, slice, 5);

    // Different depths should produce different output (different indentation)
    EXPECT_NE(oss1.str(), oss2.str());
}

// Test: Record 1 (envelope record) is correctly displayed
TEST_F(IptcDataPrintStructureTest_701, EnvelopeRecord_701) {
    // Record 1, dataset 0 (Model Version), length=2, data=0x00,0x04
    std::vector<byte> data = {0x1c, 0x01, 0x00, 0x00, 0x02, 0x00, 0x04};
    auto slice = makeSlice(data.data(), 0, data.size());
    IptcData::printStructure(oss, slice, 0);
    std::string output = oss.str();
    EXPECT_NE(output.find("1"), std::string::npos); // record 1
}

// Test: Exactly 3 bytes with marker at position 0 but not enough for full record
TEST_F(IptcDataPrintStructureTest_701, ThreeBytesWithMarkerInsufficientData_701) {
    std::vector<byte> data = {0x1c, 0x02, 0x05};
    auto slice = makeSlice(data.data(), 0, data.size());
    // The while loop condition is i < bytes.size() - 3, which is i < 0, so won't enter
    // But header should still be printed
    IptcData::printStructure(oss, slice, 0);
    std::string output = oss.str();
    EXPECT_NE(output.find("Record"), std::string::npos);
}

// Test: Data with length=1
TEST_F(IptcDataPrintStructureTest_701, SingleByteData_701) {
    std::vector<byte> data = {0x1c, 0x02, 0x05, 0x00, 0x01, 'Z'};
    auto slice = makeSlice(data.data(), 0, data.size());
    IptcData::printStructure(oss, slice, 0);
    std::string output = oss.str();
    EXPECT_NE(output.find("Z"), std::string::npos);
    EXPECT_NE(output.find("1"), std::string::npos); // length 1
}

// Test: All garbage bytes with no 0x1c marker in larger buffer
TEST_F(IptcDataPrintStructureTest_701, AllGarbageNoMarker_701) {
    std::vector<byte> data(20, 0xFF);
    auto slice = makeSlice(data.data(), 0, data.size());
    IptcData::printStructure(oss, slice, 0);
    std::string output = oss.str();
    // Should output header but no records
    EXPECT_NE(output.find("Record"), std::string::npos);
}

// Test: IptcData basic operations - empty by default
TEST_F(IptcDataPrintStructureTest_701, IptcDataEmptyByDefault_701) {
    IptcData data;
    EXPECT_TRUE(data.empty());
    EXPECT_EQ(data.count(), 0u);
}

// Test: IptcData add and size
TEST_F(IptcDataPrintStructureTest_701, IptcDataAddAndSize_701) {
    IptcData data;
    IptcKey key("Iptc.Application2.ObjectName");
    StringValue value("Test");
    int result = data.add(key, &value);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(data.count(), 1u);
    EXPECT_FALSE(data.empty());
}

// Test: IptcData clear
TEST_F(IptcDataPrintStructureTest_701, IptcDataClear_701) {
    IptcData data;
    IptcKey key("Iptc.Application2.ObjectName");
    StringValue value("Test");
    data.add(key, &value);
    EXPECT_EQ(data.count(), 1u);
    data.clear();
    EXPECT_TRUE(data.empty());
    EXPECT_EQ(data.count(), 0u);
}

// Test: IptcData findKey
TEST_F(IptcDataPrintStructureTest_701, IptcDataFindKey_701) {
    IptcData data;
    IptcKey key("Iptc.Application2.ObjectName");
    StringValue value("Test");
    data.add(key, &value);

    auto it = data.findKey(IptcKey("Iptc.Application2.ObjectName"));
    EXPECT_NE(it, data.end());
}

// Test: IptcData findKey not found
TEST_F(IptcDataPrintStructureTest_701, IptcDataFindKeyNotFound_701) {
    IptcData data;
    auto it = data.findKey(IptcKey("Iptc.Application2.ObjectName"));
    EXPECT_EQ(it, data.end());
}

// Test: IptcData erase
TEST_F(IptcDataPrintStructureTest_701, IptcDataErase_701) {
    IptcData data;
    IptcKey key("Iptc.Application2.ObjectName");
    StringValue value("Test");
    data.add(key, &value);
    EXPECT_EQ(data.count(), 1u);

    auto it = data.begin();
    data.erase(it);
    EXPECT_EQ(data.count(), 0u);
}

// Test: IptcData operator[] creates entry if not found
TEST_F(IptcDataPrintStructureTest_701, IptcDataSubscriptOperator_701) {
    IptcData data;
    Iptcdatum& datum = data["Iptc.Application2.ObjectName"];
    // Accessing via operator[] should create the entry
    EXPECT_GE(data.count(), 1u);
}

// Test: Data exactly 39 bytes should NOT have "..."
TEST_F(IptcDataPrintStructureTest_701, DataExactly39Bytes_701) {
    std::vector<byte> data;
    data.push_back(0x1c);
    data.push_back(0x02);
    data.push_back(0x05);
    data.push_back(0x00);
    data.push_back(39); // 39 bytes
    for (int i = 0; i < 39; i++) {
        data.push_back('C');
    }
    auto slice = makeSlice(data.data(), 0, data.size());
    IptcData::printStructure(oss, slice, 0);
    std::string output = oss.str();
    EXPECT_EQ(output.find("..."), std::string::npos);
}

// Test: Data exactly 41 bytes should have "..."
TEST_F(IptcDataPrintStructureTest_701, DataExactly41Bytes_701) {
    std::vector<byte> data;
    data.push_back(0x1c);
    data.push_back(0x02);
    data.push_back(0x05);
    data.push_back(0x00);
    data.push_back(41); // 41 bytes
    for (int i = 0; i < 41; i++) {
        data.push_back('D');
    }
    auto slice = makeSlice(data.data(), 0, data.size());
    IptcData::printStructure(oss, slice, 0);
    std::string output = oss.str();
    EXPECT_NE(output.find("..."), std::string::npos);
}
