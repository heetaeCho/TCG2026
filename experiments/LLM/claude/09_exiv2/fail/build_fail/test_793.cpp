#include <gtest/gtest.h>
#include <cstdint>
#include <vector>

// Include necessary Exiv2 headers
#include "exiv2/value.hpp"

using namespace Exiv2;

class DataValueTest_793 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that reading a normal byte buffer returns 0
TEST_F(DataValueTest_793, ReadNormalBuffer_ReturnsZero_793) {
    DataValue dv;
    const byte buf[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    int result = dv.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(0, result);
}

// Test that reading an empty buffer returns 0
TEST_F(DataValueTest_793, ReadEmptyBuffer_ReturnsZero_793) {
    DataValue dv;
    const byte buf[] = {0x00};
    int result = dv.read(buf, 0, littleEndian);
    EXPECT_EQ(0, result);
}

// Test that after reading, the size reflects the number of bytes read
TEST_F(DataValueTest_793, ReadBuffer_SizeMatchesLength_793) {
    DataValue dv;
    const byte buf[] = {0xAA, 0xBB, 0xCC};
    dv.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(3u, dv.size());
}

// Test reading a single byte
TEST_F(DataValueTest_793, ReadSingleByte_793) {
    DataValue dv;
    const byte buf[] = {0xFF};
    int result = dv.read(buf, 1, bigEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ(1u, dv.size());
}

// Test that byte order does not affect the result (both little and big endian)
TEST_F(DataValueTest_793, ReadWithDifferentByteOrders_SameResult_793) {
    DataValue dv1;
    DataValue dv2;
    const byte buf[] = {0x01, 0x02, 0x03};

    int result1 = dv1.read(buf, sizeof(buf), littleEndian);
    int result2 = dv2.read(buf, sizeof(buf), bigEndian);

    EXPECT_EQ(result1, result2);
    EXPECT_EQ(dv1.size(), dv2.size());
}

// Test reading a larger buffer
TEST_F(DataValueTest_793, ReadLargerBuffer_793) {
    DataValue dv;
    std::vector<byte> buf(1024, 0x42);
    int result = dv.read(buf.data(), buf.size(), littleEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ(1024u, dv.size());
}

// Test that reading twice overwrites the previous data
TEST_F(DataValueTest_793, ReadTwice_OverwritesPreviousData_793) {
    DataValue dv;
    const byte buf1[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    const byte buf2[] = {0xAA, 0xBB};

    dv.read(buf1, sizeof(buf1), littleEndian);
    EXPECT_EQ(5u, dv.size());

    dv.read(buf2, sizeof(buf2), littleEndian);
    EXPECT_EQ(2u, dv.size());
}

// Test that the data can be copied out correctly
TEST_F(DataValueTest_793, ReadAndCopyData_793) {
    DataValue dv;
    const byte buf[] = {0x10, 0x20, 0x30, 0x40};
    dv.read(buf, sizeof(buf), littleEndian);

    DataBuf dataBuf = dv.copy();
    ASSERT_EQ(4u, dataBuf.size());
    EXPECT_EQ(0x10, dataBuf.data()[0]);
    EXPECT_EQ(0x20, dataBuf.data()[1]);
    EXPECT_EQ(0x30, dataBuf.data()[2]);
    EXPECT_EQ(0x40, dataBuf.data()[3]);
}

// Test reading zero-valued bytes
TEST_F(DataValueTest_793, ReadZeroBytes_793) {
    DataValue dv;
    const byte buf[] = {0x00, 0x00, 0x00};
    int result = dv.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ(3u, dv.size());
}

// Test reading with all 0xFF bytes
TEST_F(DataValueTest_793, ReadAllOnesBytes_793) {
    DataValue dv;
    const byte buf[] = {0xFF, 0xFF, 0xFF, 0xFF};
    int result = dv.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ(4u, dv.size());
}

// Test that DataValue count returns expected value after read
TEST_F(DataValueTest_793, ReadBuffer_CountMatchesLength_793) {
    DataValue dv;
    const byte buf[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    dv.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(5u, dv.count());
}

// Test reading from a string representation
TEST_F(DataValueTest_793, ReadFromString_793) {
    DataValue dv;
    int result = dv.read("48 65 6C 6C 6F");
    EXPECT_EQ(0, result);
}

// Test typeId returns expected type
TEST_F(DataValueTest_793, TypeIdIsUndefined_793) {
    DataValue dv;
    EXPECT_EQ(undefined, dv.typeId());
}
