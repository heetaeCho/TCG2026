#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/helper_functions.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

using ::testing::_;
using ::testing::Invoke;

// Mock for BasicIo class
class MockBasicIo : public Exiv2::BasicIo {
public:
    MOCK_METHOD(Exiv2::DataBuf, read, (size_t rcount), (override));
    MOCK_METHOD(size_t, tell, (), (const, override));
    MOCK_METHOD(size_t, size, (), (const, override));
};

// Test fixture for the readDWORDTag function
class ReadDWORDTagTest_117 : public ::testing::Test {
protected:
    MockBasicIo mockIo;

    // Helper method to set up the mock
    void SetUp() override {
        // Set default behavior for the mock (if needed)
    }

    // Helper method to simulate behavior for testing error cases
    void SetErrorBehavior() {
        EXPECT_CALL(mockIo, size())
            .WillOnce(testing::Return(0)); // Simulate a case where the size is too small
        EXPECT_CALL(mockIo, tell())
            .WillOnce(testing::Return(0)); // Simulate tell returning 0
    }
};

// Normal operation: Read a DWORD (4 bytes) correctly
TEST_F(ReadDWORDTagTest_117, ReadDWORDTag_Success_117) {
    const uint32_t expected = 12345678; // Expected DWORD value

    // Mock the read behavior
    EXPECT_CALL(mockIo, read(4))
        .WillOnce(testing::Invoke([expected](size_t rcount) {
            Exiv2::DataBuf buf(4);
            buf.write_uint32(0, expected, Exiv2::littleEndian); // Write the expected DWORD value
            return buf;
        }));

    // Call the function and check the result
    uint32_t result = Exiv2::readDWORDTag(mockIo);
    EXPECT_EQ(result, expected);
}

// Boundary test: Not enough data (less than 4 bytes)
TEST_F(ReadDWORDTagTest_117, ReadDWORDTag_InsufficientData_117) {
    // Simulate error where the available data is less than required
    SetErrorBehavior();

    EXPECT_THROW({
        Exiv2::readDWORDTag(mockIo);
    }, Exiv2::ErrorCode); // Should throw a kerCorruptedMetadata error
}

// Test case: File is empty (size == 0)
TEST_F(ReadDWORDTagTest_117, ReadDWORDTag_EmptyFile_117) {
    // Simulate an empty file
    EXPECT_CALL(mockIo, size())
        .WillOnce(testing::Return(0));  // Size is zero
    EXPECT_CALL(mockIo, tell())
        .WillOnce(testing::Return(0));  // tell also returns 0

    EXPECT_THROW({
        Exiv2::readDWORDTag(mockIo);
    }, Exiv2::ErrorCode); // Should throw a kerCorruptedMetadata error
}

// Test case: Invalid read offset
TEST_F(ReadDWORDTagTest_117, ReadDWORDTag_InvalidOffset_117) {
    // Simulate a scenario where the offset is invalid (i.e., the read will go out of bounds)
    EXPECT_CALL(mockIo, read(4))
        .WillOnce(testing::Invoke([](size_t rcount) {
            Exiv2::DataBuf buf(2);  // Buffer smaller than required
            return buf;
        }));

    EXPECT_THROW({
        Exiv2::readDWORDTag(mockIo);
    }, Exiv2::ErrorCode); // Should throw a kerCorruptedMetadata error
}

// Test case: Valid DWORD but non-little endian data
TEST_F(ReadDWORDTagTest_117, ReadDWORDTag_NonLittleEndian_117) {
    const uint32_t expected = 12345678;

    // Mock the read behavior with non-little-endian data
    EXPECT_CALL(mockIo, read(4))
        .WillOnce(testing::Invoke([expected](size_t rcount) {
            Exiv2::DataBuf buf(4);
            buf.write_uint32(0, expected, Exiv2::bigEndian); // Write in big-endian format
            return buf;
        }));

    // Call the function and check the result (expecting little endian conversion)
    uint32_t result = Exiv2::readDWORDTag(mockIo);
    EXPECT_EQ(result, expected); // Should convert big-endian to little-endian and match the expected value
}