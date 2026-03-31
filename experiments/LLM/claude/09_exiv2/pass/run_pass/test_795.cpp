#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <vector>
#include <cstring>

using namespace Exiv2;

class DataValueTest_795 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a default-constructed DataValue has size 0
TEST_F(DataValueTest_795, DefaultConstructedHasSizeZero_795) {
    DataValue dv;
    EXPECT_EQ(0u, dv.size());
}

// Test that a DataValue constructed with typeId stores the correct type
TEST_F(DataValueTest_795, ConstructedWithTypeId_795) {
    DataValue dv(invalidTypeId);
    EXPECT_EQ(invalidTypeId, dv.typeId());
}

// Test copy on an empty DataValue returns 0
TEST_F(DataValueTest_795, CopyEmptyReturnsZero_795) {
    DataValue dv;
    byte buf[1] = {0};
    size_t copied = dv.copy(buf, littleEndian);
    EXPECT_EQ(0u, copied);
}

// Test reading from a string and then copying data out
TEST_F(DataValueTest_795, ReadAndCopy_795) {
    DataValue dv;
    // read expects space-separated integers as string
    dv.read("72 101 108 108 111");
    EXPECT_EQ(5u, dv.size());
    
    byte buf[5] = {0};
    size_t copied = dv.copy(buf, littleEndian);
    EXPECT_EQ(5u, copied);
    EXPECT_EQ(72, buf[0]);   // 'H'
    EXPECT_EQ(101, buf[1]);  // 'e'
    EXPECT_EQ(108, buf[2]);  // 'l'
    EXPECT_EQ(108, buf[3]);  // 'l'
    EXPECT_EQ(111, buf[4]);  // 'o'
}

// Test reading raw bytes
TEST_F(DataValueTest_795, ReadFromByteBuffer_795) {
    DataValue dv;
    const byte data[] = {0x00, 0x01, 0x02, 0xFF};
    dv.read(data, 4);
    EXPECT_EQ(4u, dv.size());
    
    byte buf[4] = {0};
    size_t copied = dv.copy(buf, bigEndian);
    EXPECT_EQ(4u, copied);
    EXPECT_EQ(0x00, buf[0]);
    EXPECT_EQ(0x01, buf[1]);
    EXPECT_EQ(0x02, buf[2]);
    EXPECT_EQ(0xFF, buf[3]);
}

// Test that copy works regardless of byte order (DataValue ignores byte order)
TEST_F(DataValueTest_795, CopyIgnoresByteOrder_795) {
    DataValue dv;
    const byte data[] = {0xAB, 0xCD, 0xEF};
    dv.read(data, 3);
    
    byte buf_le[3] = {0};
    byte buf_be[3] = {0};
    
    size_t copied_le = dv.copy(buf_le, littleEndian);
    size_t copied_be = dv.copy(buf_be, bigEndian);
    
    EXPECT_EQ(copied_le, copied_be);
    EXPECT_EQ(0, std::memcmp(buf_le, buf_be, 3));
}

// Test count after reading values
TEST_F(DataValueTest_795, CountAfterRead_795) {
    DataValue dv;
    dv.read("1 2 3 4 5 6 7 8 9 10");
    EXPECT_EQ(10u, dv.count());
}

// Test single byte value
TEST_F(DataValueTest_795, SingleByteValue_795) {
    DataValue dv;
    dv.read("42");
    EXPECT_EQ(1u, dv.size());
    
    byte buf[1] = {0};
    size_t copied = dv.copy(buf, littleEndian);
    EXPECT_EQ(1u, copied);
    EXPECT_EQ(42, buf[0]);
}

// Test clone creates an independent copy
TEST_F(DataValueTest_795, CloneCreatesIndependentCopy_795) {
    DataValue dv;
    const byte data[] = {10, 20, 30};
    dv.read(data, 3);
    
    auto clone = dv.clone();
    ASSERT_NE(nullptr, clone.get());
    EXPECT_EQ(dv.size(), clone->size());
    
    byte buf_orig[3] = {0};
    byte buf_clone[3] = {0};
    dv.copy(buf_orig, littleEndian);
    clone->copy(buf_clone, littleEndian);
    EXPECT_EQ(0, std::memcmp(buf_orig, buf_clone, 3));
}

// Test reading boundary value 255
TEST_F(DataValueTest_795, BoundaryValue255_795) {
    DataValue dv;
    dv.read("255");
    EXPECT_EQ(1u, dv.size());
    
    byte buf[1] = {0};
    dv.copy(buf, littleEndian);
    EXPECT_EQ(255, buf[0]);
}

// Test reading boundary value 0
TEST_F(DataValueTest_795, BoundaryValue0_795) {
    DataValue dv;
    dv.read("0");
    EXPECT_EQ(1u, dv.size());
    
    byte buf[1] = {0xFF};
    dv.copy(buf, littleEndian);
    EXPECT_EQ(0, buf[0]);
}

// Test toLong
TEST_F(DataValueTest_795, ToLongReturnsByteValue_795) {
    DataValue dv;
    dv.read("42 99");
    // toLong(0) should return first value
    EXPECT_EQ(42, dv.toInt64(0));
    EXPECT_EQ(99, dv.toInt64(1));
}

// Test reading empty string
TEST_F(DataValueTest_795, ReadEmptyString_795) {
    DataValue dv;
    dv.read("");
    EXPECT_EQ(0u, dv.size());
}

// Test reading from raw bytes with size 0
TEST_F(DataValueTest_795, ReadZeroLengthRawBytes_795) {
    DataValue dv;
    const byte data[] = {0x01};
    dv.read(data, 0);
    EXPECT_EQ(0u, dv.size());
}

// Test large data
TEST_F(DataValueTest_795, LargeDataCopy_795) {
    DataValue dv;
    std::vector<byte> data(1024);
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = static_cast<byte>(i & 0xFF);
    }
    dv.read(data.data(), static_cast<long>(data.size()));
    EXPECT_EQ(1024u, dv.size());
    
    std::vector<byte> buf(1024, 0);
    size_t copied = dv.copy(buf.data(), littleEndian);
    EXPECT_EQ(1024u, copied);
    EXPECT_EQ(data, buf);
}

// Test that typeId is undefined for default DataValue
TEST_F(DataValueTest_795, DefaultTypeIdIsUndefined_795) {
    DataValue dv;
    EXPECT_EQ(undefined, dv.typeId());
}
