#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "sonymn_int.hpp"
#include "tiffcomposite_int.hpp"

namespace Exiv2 {
namespace Internal {

// Declare the function under test
DataBuf sonyTagEncipher(uint16_t tag, const byte* bytes, size_t size, TiffComponent* object);
DataBuf sonyTagDecipher(uint16_t tag, const byte* bytes, size_t size, TiffComponent* object);

} // namespace Internal
} // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyTagEncipherTest_1626 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test with nullptr TiffComponent and empty data
TEST_F(SonyTagEncipherTest_1626, NullObjectEmptyData_1626) {
    DataBuf result = sonyTagEncipher(0x0000, nullptr, 0, nullptr);
    // With null bytes and zero size, we expect an empty or valid DataBuf
    EXPECT_EQ(result.size(), 0u);
}

// Test with nullptr TiffComponent and non-empty data
TEST_F(SonyTagEncipherTest_1626, NullObjectWithData_1626) {
    byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    DataBuf result = sonyTagEncipher(0x0000, data, sizeof(data), nullptr);
    // The function should return a DataBuf of same size
    EXPECT_EQ(result.size(), sizeof(data));
}

// Test that enciphering returns data of the same size as input
TEST_F(SonyTagEncipherTest_1626, ReturnsSameSizeAsInput_1626) {
    byte data[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    DataBuf result = sonyTagEncipher(0x9400, data, sizeof(data), nullptr);
    EXPECT_EQ(result.size(), sizeof(data));
}

// Test with a single byte
TEST_F(SonyTagEncipherTest_1626, SingleByteData_1626) {
    byte data[] = {0x42};
    DataBuf result = sonyTagEncipher(0x9400, data, 1, nullptr);
    EXPECT_EQ(result.size(), 1u);
}

// Test with various known Sony tags
TEST_F(SonyTagEncipherTest_1626, Tag9400_1626) {
    byte data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    DataBuf result = sonyTagEncipher(0x9400, data, sizeof(data), nullptr);
    EXPECT_EQ(result.size(), sizeof(data));
}

TEST_F(SonyTagEncipherTest_1626, Tag9401_1626) {
    byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    DataBuf result = sonyTagEncipher(0x9401, data, sizeof(data), nullptr);
    EXPECT_EQ(result.size(), sizeof(data));
}

TEST_F(SonyTagEncipherTest_1626, Tag9402_1626) {
    byte data[] = {0xFF, 0xFE, 0xFD, 0xFC};
    DataBuf result = sonyTagEncipher(0x9402, data, sizeof(data), nullptr);
    EXPECT_EQ(result.size(), sizeof(data));
}

TEST_F(SonyTagEncipherTest_1626, Tag9403_1626) {
    byte data[] = {0x00, 0x00, 0x00, 0x00};
    DataBuf result = sonyTagEncipher(0x9403, data, sizeof(data), nullptr);
    EXPECT_EQ(result.size(), sizeof(data));
}

// Test that encipher and decipher are inverse operations
TEST_F(SonyTagEncipherTest_1626, EncipherDecipherRoundTrip_1626) {
    byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    uint16_t tag = 0x9400;

    DataBuf enciphered = sonyTagEncipher(tag, data, sizeof(data), nullptr);
    ASSERT_EQ(enciphered.size(), sizeof(data));

    DataBuf deciphered = sonyTagDecipher(tag, enciphered.c_data(), enciphered.size(), nullptr);
    ASSERT_EQ(deciphered.size(), sizeof(data));

    for (size_t i = 0; i < sizeof(data); ++i) {
        EXPECT_EQ(deciphered.c_data()[i], data[i]) << "Mismatch at index " << i;
    }
}

// Test round trip with tag 9401
TEST_F(SonyTagEncipherTest_1626, EncipherDecipherRoundTrip9401_1626) {
    byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    uint16_t tag = 0x9401;

    DataBuf enciphered = sonyTagEncipher(tag, data, sizeof(data), nullptr);
    ASSERT_EQ(enciphered.size(), sizeof(data));

    DataBuf deciphered = sonyTagDecipher(tag, enciphered.c_data(), enciphered.size(), nullptr);
    ASSERT_EQ(deciphered.size(), sizeof(data));

    for (size_t i = 0; i < sizeof(data); ++i) {
        EXPECT_EQ(deciphered.c_data()[i], data[i]) << "Mismatch at index " << i;
    }
}

// Test with larger data buffer
TEST_F(SonyTagEncipherTest_1626, LargerDataBuffer_1626) {
    std::vector<byte> data(256);
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = static_cast<byte>(i & 0xFF);
    }

    DataBuf result = sonyTagEncipher(0x9400, data.data(), data.size(), nullptr);
    EXPECT_EQ(result.size(), data.size());
}

// Test with all zeros
TEST_F(SonyTagEncipherTest_1626, AllZerosData_1626) {
    byte data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    DataBuf result = sonyTagEncipher(0x9400, data, sizeof(data), nullptr);
    EXPECT_EQ(result.size(), sizeof(data));
}

// Test with all 0xFF bytes
TEST_F(SonyTagEncipherTest_1626, AllFFData_1626) {
    byte data[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    DataBuf result = sonyTagEncipher(0x9400, data, sizeof(data), nullptr);
    EXPECT_EQ(result.size(), sizeof(data));
}

// Test with non-Sony tag (arbitrary tag)
TEST_F(SonyTagEncipherTest_1626, ArbitraryTag_1626) {
    byte data[] = {0x01, 0x02, 0x03};
    DataBuf result = sonyTagEncipher(0x0100, data, sizeof(data), nullptr);
    EXPECT_EQ(result.size(), sizeof(data));
}

// Test round trip with arbitrary tag
TEST_F(SonyTagEncipherTest_1626, RoundTripArbitraryTag_1626) {
    byte data[] = {0x55, 0xAA, 0x55, 0xAA};
    uint16_t tag = 0x0100;

    DataBuf enciphered = sonyTagEncipher(tag, data, sizeof(data), nullptr);
    ASSERT_EQ(enciphered.size(), sizeof(data));

    DataBuf deciphered = sonyTagDecipher(tag, enciphered.c_data(), enciphered.size(), nullptr);
    ASSERT_EQ(deciphered.size(), sizeof(data));

    for (size_t i = 0; i < sizeof(data); ++i) {
        EXPECT_EQ(deciphered.c_data()[i], data[i]) << "Mismatch at index " << i;
    }
}

// Test with size 2 (minimum meaningful data)
TEST_F(SonyTagEncipherTest_1626, MinimalData_1626) {
    byte data[] = {0x12, 0x34};
    DataBuf result = sonyTagEncipher(0x9402, data, sizeof(data), nullptr);
    EXPECT_EQ(result.size(), sizeof(data));
}
