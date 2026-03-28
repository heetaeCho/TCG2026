#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class FujiMnHeaderTest_1455 : public ::testing::Test {
protected:
    FujiMnHeader header_;
};

// Test that a default-constructed FujiMnHeader has ifdOffset of 0
TEST_F(FujiMnHeaderTest_1455, DefaultIfdOffsetIsZero_1455) {
    EXPECT_EQ(0u, header_.ifdOffset());
}

// Test that size() returns a consistent value (the signature size)
TEST_F(FujiMnHeaderTest_1455, SizeReturnsExpectedValue_1455) {
    size_t s = header_.size();
    // Size should be positive (there's a signature)
    EXPECT_GT(s, 0u);
}

// Test that sizeOfSignature returns a positive value
TEST_F(FujiMnHeaderTest_1455, SizeOfSignatureIsPositive_1455) {
    size_t sigSize = FujiMnHeader::sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that size() and sizeOfSignature() are consistent
TEST_F(FujiMnHeaderTest_1455, SizeMatchesSizeOfSignature_1455) {
    EXPECT_EQ(header_.size(), FujiMnHeader::sizeOfSignature());
}

// Test that byteOrder returns littleEndian for Fuji
TEST_F(FujiMnHeaderTest_1455, DefaultByteOrderIsLittleEndian_1455) {
    EXPECT_EQ(Exiv2::littleEndian, header_.byteOrder());
}

// Test read with nullptr / zero size fails gracefully
TEST_F(FujiMnHeaderTest_1455, ReadWithNullDataReturnsFalse_1455) {
    bool result = header_.read(nullptr, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with data too small to contain the signature
TEST_F(FujiMnHeaderTest_1455, ReadWithTooSmallDataReturnsFalse_1455) {
    Exiv2::byte smallData[4] = {0, 0, 0, 0};
    bool result = header_.read(smallData, sizeof(smallData), Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid Fuji makernote signature
TEST_F(FujiMnHeaderTest_1455, ReadWithValidSignatureReturnsTrue_1455) {
    // Fuji makernote signature: "FUJIFILM" followed by a 4-byte offset (little-endian)
    // The signature is "FUJIFILM" (8 bytes) + 4-byte pointer = 12 bytes minimum
    Exiv2::byte fujiData[12] = {
        'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M',
        0x0C, 0x00, 0x00, 0x00  // offset 12 in little-endian
    };
    bool result = header_.read(fujiData, sizeof(fujiData), Exiv2::littleEndian);
    EXPECT_TRUE(result);
}

// Test that after a successful read, ifdOffset reflects the value from data
TEST_F(FujiMnHeaderTest_1455, IfdOffsetAfterValidRead_1455) {
    Exiv2::byte fujiData[12] = {
        'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M',
        0x0C, 0x00, 0x00, 0x00
    };
    header_.read(fujiData, sizeof(fujiData), Exiv2::littleEndian);
    EXPECT_EQ(12u, header_.ifdOffset());
}

// Test read with invalid signature returns false
TEST_F(FujiMnHeaderTest_1455, ReadWithInvalidSignatureReturnsFalse_1455) {
    Exiv2::byte badData[12] = {
        'N', 'O', 'T', 'F', 'U', 'J', 'I', 'X',
        0x0C, 0x00, 0x00, 0x00
    };
    bool result = header_.read(badData, sizeof(badData), Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test baseOffset returns mnOffset (Fuji uses the mnOffset as base)
TEST_F(FujiMnHeaderTest_1455, BaseOffsetReturnsMnOffset_1455) {
    size_t mnOffset = 100;
    EXPECT_EQ(mnOffset, header_.baseOffset(mnOffset));
}

// Test baseOffset with zero
TEST_F(FujiMnHeaderTest_1455, BaseOffsetWithZero_1455) {
    EXPECT_EQ(0u, header_.baseOffset(0));
}

// Test that after reading valid data, byteOrder is still littleEndian
TEST_F(FujiMnHeaderTest_1455, ByteOrderAfterRead_1455) {
    Exiv2::byte fujiData[12] = {
        'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M',
        0x0C, 0x00, 0x00, 0x00
    };
    header_.read(fujiData, sizeof(fujiData), Exiv2::bigEndian);
    // Fuji always uses little endian regardless of input byte order
    EXPECT_EQ(Exiv2::littleEndian, header_.byteOrder());
}

// Test read with exact minimum size
TEST_F(FujiMnHeaderTest_1455, ReadWithExactMinimumSize_1455) {
    size_t minSize = FujiMnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> fujiData(minSize, 0);
    // Fill with FUJIFILM signature
    const char sig[] = "FUJIFILM";
    for (size_t i = 0; i < 8 && i < minSize; ++i) {
        fujiData[i] = static_cast<Exiv2::byte>(sig[i]);
    }
    // Set offset bytes if there's room
    if (minSize >= 12) {
        fujiData[8] = 0x0C;
        fujiData[9] = 0x00;
        fujiData[10] = 0x00;
        fujiData[11] = 0x00;
    }
    bool result = header_.read(fujiData.data(), minSize, Exiv2::littleEndian);
    EXPECT_TRUE(result);
}

// Test read with size one less than minimum fails
TEST_F(FujiMnHeaderTest_1455, ReadWithOneLessThanMinSizeFails_1455) {
    size_t minSize = FujiMnHeader::sizeOfSignature();
    if (minSize > 0) {
        std::vector<Exiv2::byte> fujiData(minSize - 1, 0);
        const char sig[] = "FUJIFILM";
        for (size_t i = 0; i < 8 && i < minSize - 1; ++i) {
            fujiData[i] = static_cast<Exiv2::byte>(sig[i]);
        }
        bool result = header_.read(fujiData.data(), minSize - 1, Exiv2::littleEndian);
        EXPECT_FALSE(result);
    }
}

// Test ifdOffset with a different offset value after read
TEST_F(FujiMnHeaderTest_1455, IfdOffsetDifferentValue_1455) {
    Exiv2::byte fujiData[12] = {
        'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M',
        0x20, 0x00, 0x00, 0x00  // offset 32 in little-endian
    };
    header_.read(fujiData, sizeof(fujiData), Exiv2::littleEndian);
    EXPECT_EQ(32u, header_.ifdOffset());
}
