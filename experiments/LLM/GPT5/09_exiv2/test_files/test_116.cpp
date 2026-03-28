#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/helper_functions.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

namespace Exiv2 {

class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));
    MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));
    MOCK_METHOD(const size_t, tell, (), (const, override));
    MOCK_METHOD(const size_t, size, (), (const, override));
};

class ReadQWORDTagTest : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

TEST_F(ReadQWORDTagTest, ValidReadQWORD_116) {
    // Arrange
    uint64_t expected_value = 1234567890123456789;
    DataBuf mockData(8);
    mockData.write_uint64(0, expected_value, littleEndian);
    
    // Set up the mock to return the expected DataBuf
    EXPECT_CALL(mockIo, read(8))
        .WillOnce(testing::Return(mockData));
    
    // Act
    uint64_t result = readQWORDTag(mockIo);
    
    // Assert
    EXPECT_EQ(result, expected_value);
}

TEST_F(ReadQWORDTagTest, InsufficientDataThrowsError_117) {
    // Arrange
    DataBuf mockData(4);  // Less than QWORD (8 bytes)
    
    // Set up the mock to return insufficient data
    EXPECT_CALL(mockIo, read(8))
        .WillOnce(testing::Return(mockData));
    
    // Act and Assert
    EXPECT_THROW(readQWORDTag(mockIo), std::runtime_error);  // Expect ErrorCode::kerCorruptedMetadata
}

TEST_F(ReadQWORDTagTest, ReadFromInvalidPositionThrowsError_118) {
    // Arrange
    uint64_t expected_value = 1234567890123456789;
    DataBuf mockData(8);
    mockData.write_uint64(0, expected_value, littleEndian);
    
    // Mock the tell() function to simulate an invalid position
    EXPECT_CALL(mockIo, tell())
        .WillOnce(testing::Return(0));  // Position 0, indicating no valid data to read.
    EXPECT_CALL(mockIo, read(8))
        .WillOnce(testing::Return(mockData));

    // Act and Assert
    EXPECT_THROW(readQWORDTag(mockIo), std::runtime_error);  // Expect ErrorCode::kerCorruptedMetadata
}

}  // namespace Exiv2