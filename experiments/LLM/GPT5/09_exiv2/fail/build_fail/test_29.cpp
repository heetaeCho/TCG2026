#include <gtest/gtest.h>
#include "exiv2/types.hpp"

namespace Exiv2 {

class DataBufTest_29 : public ::testing::Test {
protected:
    // Set up necessary mock data and environment for tests
    DataBufTest_29() {}
    ~DataBufTest_29() override {}

    // Example helper to initialize DataBuf with a certain size
    DataBuf createDataBufWithSize(size_t size) {
        return DataBuf(size);
    }
};

// Test Case 1: Test Default Constructor of DataBuf
TEST_F(DataBufTest_29, DefaultConstructor_29) {
    DataBuf buf;
    // Verifying the object initializes correctly as an empty buffer
    EXPECT_TRUE(buf.empty());
}

// Test Case 2: Test Constructor with Size Argument
TEST_F(DataBufTest_29, ConstructorWithSize_29) {
    size_t size = 100;
    DataBuf buf(size);
    // Verifying the buffer is initialized with the expected size
    EXPECT_EQ(buf.size(), size);
    EXPECT_FALSE(buf.empty());
}

// Test Case 3: Test Allocating Memory with Alloc Method
TEST_F(DataBufTest_29, Alloc_29) {
    DataBuf buf;
    size_t size = 50;
    buf.alloc(size);
    // Verifying the buffer has been allocated with the expected size
    EXPECT_EQ(buf.size(), size);
    EXPECT_FALSE(buf.empty());
}

// Test Case 4: Test Resizing Memory
TEST_F(DataBufTest_29, Resize_29) {
    size_t initial_size = 50;
    DataBuf buf(initial_size);
    size_t new_size = 100;
    buf.resize(new_size);

    // Verifying the buffer has been resized correctly
    EXPECT_EQ(buf.size(), new_size);
}

// Test Case 5: Test Resetting the Buffer
TEST_F(DataBufTest_29, Reset_29) {
    size_t size = 100;
    DataBuf buf(size);
    buf.reset();
    // Verifying that the buffer is reset (empty)
    EXPECT_TRUE(buf.empty());
}

// Test Case 6: Test Read/Write uint8_t Methods
TEST_F(DataBufTest_29, ReadWriteUint8_29) {
    size_t offset = 0;
    uint8_t value = 42;
    DataBuf buf(10); // Buffer with size 10

    buf.write_uint8(offset, value); // Writing value to buffer
    uint8_t read_value = buf.read_uint8(offset); // Reading value back

    // Verifying the written value matches the read value
    EXPECT_EQ(read_value, value);
}

// Test Case 7: Test Read/Write uint16_t Methods
TEST_F(DataBufTest_29, ReadWriteUint16_29) {
    size_t offset = 0;
    uint16_t value = 300;
    DataBuf buf(10);

    buf.write_uint16(offset, value, ByteOrder::BigEndian); // Writing value to buffer
    uint16_t read_value = buf.read_uint16(offset, ByteOrder::BigEndian); // Reading value back

    // Verifying the written value matches the read value
    EXPECT_EQ(read_value, value);
}

// Test Case 8: Test Read/Write uint32_t Methods
TEST_F(DataBufTest_29, ReadWriteUint32_29) {
    size_t offset = 0;
    uint32_t value = 100000;
    DataBuf buf(10);

    buf.write_uint32(offset, value, ByteOrder::BigEndian); // Writing value to buffer
    uint32_t read_value = buf.read_uint32(offset, ByteOrder::BigEndian); // Reading value back

    // Verifying the written value matches the read value
    EXPECT_EQ(read_value, value);
}

// Test Case 9: Test cmpBytes Method
TEST_F(DataBufTest_29, CmpBytes_29) {
    size_t offset = 0;
    const char* data = "Test";
    DataBuf buf(10);

    // Writing bytes to buffer
    std::memcpy(buf.data(offset), data, 4);

    // Comparing the written bytes with the test data
    EXPECT_EQ(buf.cmpBytes(offset, data, 4), 0); // Expecting 0 since the data should match
}

// Test Case 10: Test if the buffer is empty after reset
TEST_F(DataBufTest_29, EmptyAfterReset_29) {
    size_t size = 100;
    DataBuf buf(size);
    buf.reset();
    // Verifying that the buffer is empty after reset
    EXPECT_TRUE(buf.empty());
}

}  // namespace Exiv2

// Main function to run tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}