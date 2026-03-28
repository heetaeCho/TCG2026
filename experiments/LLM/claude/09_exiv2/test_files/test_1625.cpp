#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include "sonymn_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// A minimal concrete TiffComponent for testing purposes
class TestTiffEntry : public TiffEntryBase {
public:
    TestTiffEntry(uint16_t tag, IfdId group) : TiffEntryBase(tag, group) {}

protected:
    void doAccept(TiffVisitor& /*visitor*/) override {}
    size_t doWrite(IoWrapper& /*ioWrapper*/, ByteOrder /*byteOrder*/, size_t /*offset*/,
                   size_t /*valueIdx*/, size_t /*dataIdx*/, size_t& /*imageIdx*/) override {
        return 0;
    }
};

class SonyTagDecipherTest_1625 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that sonyTagDecipher with null bytes and zero size returns empty DataBuf
TEST_F(SonyTagDecipherTest_1625, NullBytesZeroSize_1625) {
    DataBuf result = sonyTagDecipher(0x9400, nullptr, 0, nullptr);
    EXPECT_EQ(result.size(), 0u);
}

// Test that sonyTagDecipher with valid bytes returns a DataBuf of the same size
TEST_F(SonyTagDecipherTest_1625, ValidBytesReturnsSameSize_1625) {
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf result = sonyTagDecipher(0x9400, data, sizeof(data), nullptr);
    EXPECT_EQ(result.size(), sizeof(data));
}

// Test with a single byte
TEST_F(SonyTagDecipherTest_1625, SingleByte_1625) {
    byte data[] = {0xFF};
    DataBuf result = sonyTagDecipher(0x9400, data, 1, nullptr);
    EXPECT_EQ(result.size(), 1u);
}

// Test with a larger buffer
TEST_F(SonyTagDecipherTest_1625, LargerBuffer_1625) {
    const size_t bufSize = 256;
    byte data[bufSize];
    for (size_t i = 0; i < bufSize; ++i) {
        data[i] = static_cast<byte>(i & 0xFF);
    }
    DataBuf result = sonyTagDecipher(0x9400, data, bufSize, nullptr);
    EXPECT_EQ(result.size(), bufSize);
}

// Test with different tag values - tag 0x9400
TEST_F(SonyTagDecipherTest_1625, Tag9400_1625) {
    byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80};
    DataBuf result = sonyTagDecipher(0x9400, data, sizeof(data), nullptr);
    EXPECT_EQ(result.size(), sizeof(data));
}

// Test with different tag values - tag 0x9401
TEST_F(SonyTagDecipherTest_1625, Tag9401_1625) {
    byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80};
    DataBuf result = sonyTagDecipher(0x9401, data, sizeof(data), nullptr);
    EXPECT_EQ(result.size(), sizeof(data));
}

// Test with different tag values - tag 0x9402
TEST_F(SonyTagDecipherTest_1625, Tag9402_1625) {
    byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80};
    DataBuf result = sonyTagDecipher(0x9402, data, sizeof(data), nullptr);
    EXPECT_EQ(result.size(), sizeof(data));
}

// Test with different tag values - tag 0x9403
TEST_F(SonyTagDecipherTest_1625, Tag9403_1625) {
    byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80};
    DataBuf result = sonyTagDecipher(0x9403, data, sizeof(data), nullptr);
    EXPECT_EQ(result.size(), sizeof(data));
}

// Test with tag 0x9406
TEST_F(SonyTagDecipherTest_1625, Tag9406_1625) {
    byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    DataBuf result = sonyTagDecipher(0x9406, data, sizeof(data), nullptr);
    EXPECT_EQ(result.size(), sizeof(data));
}

// Test that deciphering produces non-null data pointer when size > 0
TEST_F(SonyTagDecipherTest_1625, NonNullDataPointer_1625) {
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf result = sonyTagDecipher(0x9400, data, sizeof(data), nullptr);
    EXPECT_NE(result.data(), nullptr);
}

// Test with all zeros input
TEST_F(SonyTagDecipherTest_1625, AllZerosInput_1625) {
    byte data[] = {0x00, 0x00, 0x00, 0x00};
    DataBuf result = sonyTagDecipher(0x9400, data, sizeof(data), nullptr);
    EXPECT_EQ(result.size(), sizeof(data));
}

// Test with all 0xFF input
TEST_F(SonyTagDecipherTest_1625, AllOnesInput_1625) {
    byte data[] = {0xFF, 0xFF, 0xFF, 0xFF};
    DataBuf result = sonyTagDecipher(0x9400, data, sizeof(data), nullptr);
    EXPECT_EQ(result.size(), sizeof(data));
}

// Test that cipher followed by decipher is identity (roundtrip)
// sonyTagCipher is the encipher, sonyTagDecipher is the decipher
TEST_F(SonyTagDecipherTest_1625, RoundtripCipherDecipher_1625) {
    byte original[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    // First encipher
    DataBuf enciphered = sonyTagCipher(0x9400, original, sizeof(original), nullptr);
    ASSERT_EQ(enciphered.size(), sizeof(original));
    
    // Then decipher
    DataBuf deciphered = sonyTagDecipher(0x9400, enciphered.data(), enciphered.size(), nullptr);
    ASSERT_EQ(deciphered.size(), sizeof(original));
    
    // Should match original
    for (size_t i = 0; i < sizeof(original); ++i) {
        EXPECT_EQ(deciphered.data()[i], original[i]) << "Mismatch at index " << i;
    }
}

// Test roundtrip with tag 0x9402
TEST_F(SonyTagDecipherTest_1625, RoundtripTag9402_1625) {
    byte original[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22};
    DataBuf enciphered = sonyTagCipher(0x9402, original, sizeof(original), nullptr);
    ASSERT_EQ(enciphered.size(), sizeof(original));
    
    DataBuf deciphered = sonyTagDecipher(0x9402, enciphered.data(), enciphered.size(), nullptr);
    ASSERT_EQ(deciphered.size(), sizeof(original));
    
    for (size_t i = 0; i < sizeof(original); ++i) {
        EXPECT_EQ(deciphered.data()[i], original[i]) << "Mismatch at index " << i;
    }
}

// Test with an unrecognized tag - should still return data of same size
TEST_F(SonyTagDecipherTest_1625, UnrecognizedTag_1625) {
    byte data[] = {0x12, 0x34, 0x56, 0x78};
    DataBuf result = sonyTagDecipher(0x0000, data, sizeof(data), nullptr);
    EXPECT_EQ(result.size(), sizeof(data));
}

// Test with size of 2 bytes
TEST_F(SonyTagDecipherTest_1625, TwoBytes_1625) {
    byte data[] = {0xAB, 0xCD};
    DataBuf result = sonyTagDecipher(0x9400, data, sizeof(data), nullptr);
    EXPECT_EQ(result.size(), sizeof(data));
}
