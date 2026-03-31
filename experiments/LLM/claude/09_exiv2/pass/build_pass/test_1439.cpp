#include <gtest/gtest.h>
#include <cstring>

// Include necessary Exiv2 headers
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class OlympusMnHeaderTest_1439 : public ::testing::Test {
protected:
    OlympusMnHeader header_;
};

// Test that read returns false when pData is nullptr
TEST_F(OlympusMnHeaderTest_1439, ReadNullPointerReturnsFalse_1439) {
    bool result = header_.read(nullptr, 100, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when size is 0
TEST_F(OlympusMnHeaderTest_1439, ReadZeroSizeReturnsFalse_1439) {
    const byte data[] = {0x4F, 0x4C, 0x59, 0x4D, 0x50, 0x00, 0x01, 0x00};
    bool result = header_.read(data, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when size is less than signature size
TEST_F(OlympusMnHeaderTest_1439, ReadSizeTooSmallReturnsFalse_1439) {
    const byte data[] = {0x4F, 0x4C, 0x59, 0x4D, 0x50};
    bool result = header_.read(data, 5, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns true with valid Olympus signature "OLYMP\0"
TEST_F(OlympusMnHeaderTest_1439, ReadValidOlympusSignatureReturnsTrue_1439) {
    // "OLYMP\0" followed by extra bytes
    const byte data[] = {0x4F, 0x4C, 0x59, 0x4D, 0x50, 0x00, 0x01, 0x00, 0x00, 0x00};
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_TRUE(result);
}

// Test that read returns false with invalid signature
TEST_F(OlympusMnHeaderTest_1439, ReadInvalidSignatureReturnsFalse_1439) {
    const byte data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when signature partially matches
TEST_F(OlympusMnHeaderTest_1439, ReadPartialSignatureReturnsFalse_1439) {
    // "OLYM" followed by wrong bytes
    const byte data[] = {0x4F, 0x4C, 0x59, 0x4D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with big endian byte order (should still work based on signature)
TEST_F(OlympusMnHeaderTest_1439, ReadValidSignatureWithBigEndian_1439) {
    const byte data[] = {0x4F, 0x4C, 0x59, 0x4D, 0x50, 0x00, 0x01, 0x00, 0x00, 0x00};
    bool result = header_.read(data, sizeof(data), bigEndian);
    EXPECT_TRUE(result);
}

// Test that read returns false with size exactly 1 (below minimum)
TEST_F(OlympusMnHeaderTest_1439, ReadSizeOneReturnsFalse_1439) {
    const byte data[] = {0x4F};
    bool result = header_.read(data, 1, littleEndian);
    EXPECT_FALSE(result);
}

// Test with data that has correct first 5 bytes but wrong 6th byte
TEST_F(OlympusMnHeaderTest_1439, ReadWrongSixthByteReturnsFalse_1439) {
    const byte data[] = {0x4F, 0x4C, 0x59, 0x4D, 0x50, 0x01, 0x01, 0x00, 0x00, 0x00};
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read can be called multiple times on the same header object
TEST_F(OlympusMnHeaderTest_1439, ReadCanBeCalledMultipleTimes_1439) {
    const byte validData[] = {0x4F, 0x4C, 0x59, 0x4D, 0x50, 0x00, 0x01, 0x00, 0x00, 0x00};
    const byte invalidData[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    EXPECT_TRUE(header_.read(validData, sizeof(validData), littleEndian));
    EXPECT_FALSE(header_.read(invalidData, sizeof(invalidData), littleEndian));
    EXPECT_TRUE(header_.read(validData, sizeof(validData), littleEndian));
}

// Test sizeOfSignature returns expected value
TEST_F(OlympusMnHeaderTest_1439, SizeOfSignatureReturnsExpectedValue_1439) {
    // The signature "OLYMP\0" plus possible version info; sizeOfSignature should be consistent
    size_t sigSize = header_.sizeOfSignature();
    EXPECT_GT(sigSize, static_cast<size_t>(0));
}

// Test read with exact minimum size matching sizeOfSignature
TEST_F(OlympusMnHeaderTest_1439, ReadWithExactSignatureSize_1439) {
    size_t sigSize = header_.sizeOfSignature();
    std::vector<byte> data(sigSize, 0);
    // Fill with "OLYMP\0" and pad
    if (sigSize >= 6) {
        data[0] = 0x4F; // O
        data[1] = 0x4C; // L
        data[2] = 0x59; // Y
        data[3] = 0x4D; // M
        data[4] = 0x50; // P
        data[5] = 0x00; // \0
    }
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_TRUE(result);
}

// Test read with size one less than sizeOfSignature
TEST_F(OlympusMnHeaderTest_1439, ReadWithSizeOneLessThanSignatureReturnsFalse_1439) {
    size_t sigSize = header_.sizeOfSignature();
    if (sigSize > 0) {
        std::vector<byte> data(sigSize - 1, 0);
        if (data.size() >= 6) {
            data[0] = 0x4F;
            data[1] = 0x4C;
            data[2] = 0x59;
            data[3] = 0x4D;
            data[4] = 0x50;
            data[5] = 0x00;
        }
        bool result = header_.read(data.data(), data.size(), littleEndian);
        EXPECT_FALSE(result);
    }
}

// Test with all 0xFF data (wrong signature)
TEST_F(OlympusMnHeaderTest_1439, ReadAllOnesReturnsFalse_1439) {
    const byte data[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_FALSE(result);
}
