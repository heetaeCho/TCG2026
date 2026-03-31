#include <gtest/gtest.h>
#include <cstring>
#include <vector>

// We need to include the necessary Exiv2 headers to use the class
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Casio2MnHeaderTest_1507 : public ::testing::Test {
protected:
    Casio2MnHeader header_;
};

// Test that read returns false when pData is nullptr
TEST_F(Casio2MnHeaderTest_1507, ReadNullData_1507) {
    bool result = header_.read(nullptr, 100, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when size is 0
TEST_F(Casio2MnHeaderTest_1507, ReadZeroSize_1507) {
    byte data[1] = {0};
    bool result = header_.read(data, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when size is less than signature size
TEST_F(Casio2MnHeaderTest_1507, ReadSizeTooSmall_1507) {
    byte data[1] = {0x51};
    bool result = header_.read(data, 1, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when data doesn't match signature
TEST_F(Casio2MnHeaderTest_1507, ReadWrongSignature_1507) {
    // The Casio2 signature is "QVC\0\0\0" (6 bytes)
    // Provide data that doesn't match
    std::vector<byte> data(64, 0x00);
    data[0] = 'X';
    data[1] = 'Y';
    data[2] = 'Z';
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns true with correct Casio2 signature
TEST_F(Casio2MnHeaderTest_1507, ReadValidSignature_1507) {
    // Casio2 signature is "QVC\0\0\0" — 6 bytes
    byte data[] = {'Q', 'V', 'C', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_TRUE(result);
}

// Test that read works with big endian byte order (should not affect signature check)
TEST_F(Casio2MnHeaderTest_1507, ReadValidSignatureBigEndian_1507) {
    byte data[] = {'Q', 'V', 'C', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool result = header_.read(data, sizeof(data), bigEndian);
    EXPECT_TRUE(result);
}

// Test that read returns true when size exactly equals signature size
TEST_F(Casio2MnHeaderTest_1507, ReadExactSignatureSize_1507) {
    byte data[] = {'Q', 'V', 'C', 0x00, 0x00, 0x00};
    bool result = header_.read(data, 6, littleEndian);
    EXPECT_TRUE(result);
}

// Test that read returns false when size is one byte less than signature
TEST_F(Casio2MnHeaderTest_1507, ReadOneByteLessThanSignature_1507) {
    byte data[] = {'Q', 'V', 'C', 0x00, 0x00};
    bool result = header_.read(data, 5, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read can be called multiple times (second call with valid data)
TEST_F(Casio2MnHeaderTest_1507, ReadMultipleTimes_1507) {
    // First read with invalid data
    byte badData[] = {'X', 'Y', 'Z', 0x00, 0x00, 0x00, 0x00, 0x00};
    bool result1 = header_.read(badData, sizeof(badData), littleEndian);
    EXPECT_FALSE(result1);

    // Second read with valid data
    byte goodData[] = {'Q', 'V', 'C', 0x00, 0x00, 0x00, 0x00, 0x00};
    bool result2 = header_.read(goodData, sizeof(goodData), littleEndian);
    EXPECT_TRUE(result2);
}

// Test that partial signature match fails
TEST_F(Casio2MnHeaderTest_1507, ReadPartialSignatureMatch_1507) {
    // Match first two bytes but not the rest
    byte data[] = {'Q', 'V', 'X', 0x00, 0x00, 0x00, 0x00, 0x00};
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_FALSE(result);
}

// Test sizeOfSignature method
TEST_F(Casio2MnHeaderTest_1507, SizeOfSignature_1507) {
    // The Casio2 signature "QVC\0\0\0" should be 6 bytes
    EXPECT_EQ(header_.sizeOfSignature(), 6u);
}

// Test start_ is set correctly after successful read
TEST_F(Casio2MnHeaderTest_1507, StartAfterSuccessfulRead_1507) {
    byte data[] = {'Q', 'V', 'C', 0x00, 0x00, 0x00, 0x00, 0x00};
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_TRUE(result);
    // start_ should equal sizeOfSignature after successful read
    // We verify this through the start() accessor if available
    EXPECT_EQ(header_.start(), header_.sizeOfSignature());
}

// Test with nullptr and size > 0
TEST_F(Casio2MnHeaderTest_1507, ReadNullWithPositiveSize_1507) {
    bool result = header_.read(nullptr, 10, littleEndian);
    EXPECT_FALSE(result);
}

// Test with all zeros (no signature match)
TEST_F(Casio2MnHeaderTest_1507, ReadAllZeros_1507) {
    byte data[10] = {0};
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_FALSE(result);
}

// Test large buffer with correct signature at start
TEST_F(Casio2MnHeaderTest_1507, ReadLargeBufferValidSignature_1507) {
    std::vector<byte> data(1024, 0xFF);
    data[0] = 'Q';
    data[1] = 'V';
    data[2] = 'C';
    data[3] = 0x00;
    data[4] = 0x00;
    data[5] = 0x00;
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_TRUE(result);
}
