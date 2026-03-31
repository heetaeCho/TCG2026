#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <vector>

// We need to access the sonyTagCipher function which is static in the Internal namespace.
// Since it's static, we need to include the source or replicate the declaration.
// We'll include necessary Exiv2 headers and work with the function through its namespace.

#include <exiv2/exiv2.hpp>
#include "sonymn_int.hpp"

// Since sonyTagCipher is a static function in the .cpp file, we cannot directly call it
// from outside the translation unit. We need to include the source file to access it.
// This is a common technique for testing static/file-scope functions.

// Re-declare the function signature based on what we see in the code
namespace Exiv2 {
namespace Internal {

// We need to access this through the TiffMnCreator or similar mechanism,
// but since it's static, let's include the cpp file directly for testing purposes.

}  // namespace Internal
}  // namespace Exiv2

// Include the implementation file to get access to the static function
// This effectively compiles the function in our test translation unit
namespace TestAccess {
#include "sonymn_int.cpp"
}

using namespace TestAccess::Exiv2::Internal;

class SonyTagCipherTest_1624 : public ::testing::Test {
protected:
    // Helper to call the cipher function
    Exiv2::DataBuf callCipher(uint16_t tag, const Exiv2::byte* bytes, size_t size, bool bDecipher) {
        return sonyTagCipher(tag, bytes, size, nullptr, bDecipher);
    }
};

// Test that encrypting then decrypting returns the original data
TEST_F(SonyTagCipherTest_1624, EncryptThenDecryptReturnsOriginal_1624) {
    Exiv2::byte original[] = {0, 1, 2, 3, 4, 5, 10, 50, 100, 200, 248};
    size_t size = sizeof(original);

    // Encrypt (bDecipher = false)
    Exiv2::DataBuf encrypted = callCipher(0, original, size, false);
    ASSERT_EQ(encrypted.size(), size);

    // Decrypt (bDecipher = true)
    Exiv2::DataBuf decrypted = callCipher(0, encrypted.c_data(), encrypted.size(), true);
    ASSERT_EQ(decrypted.size(), size);

    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(decrypted.read_uint8(i), original[i])
            << "Mismatch at index " << i;
    }
}

// Test that decrypting then encrypting returns the original data
TEST_F(SonyTagCipherTest_1624, DecryptThenEncryptReturnsOriginal_1624) {
    Exiv2::byte original[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    size_t size = sizeof(original);

    // Decrypt first
    Exiv2::DataBuf decrypted = callCipher(0, original, size, true);
    ASSERT_EQ(decrypted.size(), size);

    // Then encrypt
    Exiv2::DataBuf reencrypted = callCipher(0, decrypted.c_data(), decrypted.size(), false);
    ASSERT_EQ(reencrypted.size(), size);

    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(reencrypted.read_uint8(i), original[i])
            << "Mismatch at index " << i;
    }
}

// Test with empty data
TEST_F(SonyTagCipherTest_1624, EmptyDataReturnsEmpty_1624) {
    Exiv2::byte dummy = 0;
    Exiv2::DataBuf result = callCipher(0, &dummy, 0, false);
    EXPECT_EQ(result.size(), 0u);
}

// Test with single byte
TEST_F(SonyTagCipherTest_1624, SingleByteEncryptDecrypt_1624) {
    for (int val = 0; val < 256; val++) {
        Exiv2::byte b = static_cast<Exiv2::byte>(val);
        Exiv2::DataBuf encrypted = callCipher(0, &b, 1, false);
        ASSERT_EQ(encrypted.size(), 1u);

        Exiv2::DataBuf decrypted = callCipher(0, encrypted.c_data(), 1, true);
        ASSERT_EQ(decrypted.size(), 1u);
        EXPECT_EQ(decrypted.read_uint8(0), b) << "Failed for value " << val;
    }
}

// Test that values 249-255 are preserved (identity mapping)
TEST_F(SonyTagCipherTest_1624, HighValuesPreservedOnEncrypt_1624) {
    for (int val = 249; val < 256; val++) {
        Exiv2::byte b = static_cast<Exiv2::byte>(val);
        Exiv2::DataBuf encrypted = callCipher(0, &b, 1, false);
        ASSERT_EQ(encrypted.size(), 1u);
        EXPECT_EQ(encrypted.read_uint8(0), b) << "Value " << val << " should be identity mapped on encrypt";
    }
}

// Test that values 249-255 are preserved on decrypt
TEST_F(SonyTagCipherTest_1624, HighValuesPreservedOnDecrypt_1624) {
    for (int val = 249; val < 256; val++) {
        Exiv2::byte b = static_cast<Exiv2::byte>(val);
        Exiv2::DataBuf decrypted = callCipher(0, &b, 1, true);
        ASSERT_EQ(decrypted.size(), 1u);
        EXPECT_EQ(decrypted.read_uint8(0), b) << "Value " << val << " should be identity mapped on decrypt";
    }
}

// Test that the output size matches input size
TEST_F(SonyTagCipherTest_1624, OutputSizeMatchesInputSize_1624) {
    std::vector<size_t> sizes = {1, 2, 10, 100, 256, 1000};
    for (size_t sz : sizes) {
        std::vector<Exiv2::byte> data(sz, 42);
        Exiv2::DataBuf result = callCipher(0, data.data(), sz, false);
        EXPECT_EQ(result.size(), sz) << "Size mismatch for input size " << sz;
    }
}

// Test that encryption actually changes data (for values in 0-248 range)
TEST_F(SonyTagCipherTest_1624, EncryptionChangesData_1624) {
    // Value 0 maps to (0^3 % 249) = 0, so 0 is a fixed point.
    // Value 1 maps to (1^3 % 249) = 1, another fixed point.
    // Let's try value 2: 2^3 % 249 = 8
    Exiv2::byte b = 2;
    Exiv2::DataBuf encrypted = callCipher(0, &b, 1, false);
    ASSERT_EQ(encrypted.size(), 1u);
    EXPECT_EQ(encrypted.read_uint8(0), 8u); // 2^3 % 249 = 8
}

// Test specific known value: 0 encrypts to 0 (0^3 % 249 = 0)
TEST_F(SonyTagCipherTest_1624, ZeroMapsToZeroOnEncrypt_1624) {
    Exiv2::byte b = 0;
    Exiv2::DataBuf encrypted = callCipher(0, &b, 1, false);
    EXPECT_EQ(encrypted.read_uint8(0), 0u);
}

// Test specific known value: 1 encrypts to 1 (1^3 % 249 = 1)
TEST_F(SonyTagCipherTest_1624, OneMapsToOneOnEncrypt_1624) {
    Exiv2::byte b = 1;
    Exiv2::DataBuf encrypted = callCipher(0, &b, 1, false);
    EXPECT_EQ(encrypted.read_uint8(0), 1u);
}

// Test that tag parameter doesn't affect the result (it's unused)
TEST_F(SonyTagCipherTest_1624, TagDoesNotAffectResult_1624) {
    Exiv2::byte data[] = {5, 10, 15, 20, 25};
    size_t size = sizeof(data);

    Exiv2::DataBuf result1 = callCipher(0, data, size, false);
    Exiv2::DataBuf result2 = callCipher(100, data, size, false);
    Exiv2::DataBuf result3 = callCipher(0xFFFF, data, size, false);

    ASSERT_EQ(result1.size(), size);
    ASSERT_EQ(result2.size(), size);
    ASSERT_EQ(result3.size(), size);

    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(result1.read_uint8(i), result2.read_uint8(i));
        EXPECT_EQ(result1.read_uint8(i), result3.read_uint8(i));
    }
}

// Test that the cipher is a bijection on [0, 248]
TEST_F(SonyTagCipherTest_1624, CipherIsBijectionOnLowRange_1624) {
    // Encrypt all values 0-248 and check they're all unique
    std::vector<bool> seen(256, false);
    for (int val = 0; val < 249; val++) {
        Exiv2::byte b = static_cast<Exiv2::byte>(val);
        Exiv2::DataBuf encrypted = callCipher(0, &b, 1, false);
        Exiv2::byte out = encrypted.read_uint8(0);
        EXPECT_FALSE(seen[out]) << "Collision detected: value " << val << " maps to " << (int)out << " which was already seen";
        seen[out] = true;
    }
}

// Test all 256 byte values round-trip through encrypt then decrypt
TEST_F(SonyTagCipherTest_1624, AllByteValuesRoundTrip_1624) {
    std::vector<Exiv2::byte> allBytes(256);
    for (int i = 0; i < 256; i++) {
        allBytes[i] = static_cast<Exiv2::byte>(i);
    }

    Exiv2::DataBuf encrypted = callCipher(0, allBytes.data(), allBytes.size(), false);
    ASSERT_EQ(encrypted.size(), 256u);

    Exiv2::DataBuf decrypted = callCipher(0, encrypted.c_data(), encrypted.size(), true);
    ASSERT_EQ(decrypted.size(), 256u);

    for (int i = 0; i < 256; i++) {
        EXPECT_EQ(decrypted.read_uint8(i), static_cast<Exiv2::byte>(i))
            << "Round-trip failed for byte value " << i;
    }
}

// Test that the original data is not modified (function takes const byte*)
TEST_F(SonyTagCipherTest_1624, OriginalDataNotModified_1624) {
    Exiv2::byte original[] = {10, 20, 30, 40, 50};
    Exiv2::byte copy[] = {10, 20, 30, 40, 50};
    size_t size = sizeof(original);

    callCipher(0, original, size, false);

    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(original[i], copy[i]);
    }
}

// Test large data block
TEST_F(SonyTagCipherTest_1624, LargeDataEncryptDecrypt_1624) {
    const size_t size = 10000;
    std::vector<Exiv2::byte> data(size);
    for (size_t i = 0; i < size; i++) {
        data[i] = static_cast<Exiv2::byte>(i % 256);
    }

    Exiv2::DataBuf encrypted = callCipher(0, data.data(), size, false);
    ASSERT_EQ(encrypted.size(), size);

    Exiv2::DataBuf decrypted = callCipher(0, encrypted.c_data(), encrypted.size(), true);
    ASSERT_EQ(decrypted.size(), size);

    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(decrypted.read_uint8(i), data[i])
            << "Mismatch at index " << i;
    }
}

// Test specific encryption values based on the cubic cipher formula
TEST_F(SonyTagCipherTest_1624, SpecificEncryptionValues_1624) {
    // For encrypt (bDecipher=false): code[i] = (i*i*i) % 249 for i < 249
    // So encrypting byte value 3: code[3] = (27) % 249 = 27
    Exiv2::byte b = 3;
    Exiv2::DataBuf encrypted = callCipher(0, &b, 1, false);
    EXPECT_EQ(encrypted.read_uint8(0), 27u);

    // Encrypting byte value 10: code[10] = (1000) % 249 = 1000 - 4*249 = 1000 - 996 = 4
    b = 10;
    encrypted = callCipher(0, &b, 1, false);
    EXPECT_EQ(encrypted.read_uint8(0), 4u);
}

// Test boundary value 248
TEST_F(SonyTagCipherTest_1624, BoundaryValue248_1624) {
    // code[248] = (248*248*248) % 249
    // 248 ≡ -1 (mod 249), so (-1)^3 = -1 ≡ 248 (mod 249)
    Exiv2::byte b = 248;
    Exiv2::DataBuf encrypted = callCipher(0, &b, 1, false);
    EXPECT_EQ(encrypted.read_uint8(0), 248u); // 248 is a fixed point
}
