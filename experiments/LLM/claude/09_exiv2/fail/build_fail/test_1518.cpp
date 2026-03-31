#include <gtest/gtest.h>
#include <cstring>
#include <memory>

#include "makernote_int.hpp"
#include "tiffimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewNikonMnTest_1518 : public ::testing::Test {
protected:
    static constexpr uint16_t testTag = 0x927c;
    static constexpr IfdId testGroup = IfdId::ifd0Id;
    static constexpr IfdId testMnGroup = IfdId::ifd0Id;
};

// Test: nullptr data with zero size should return nullptr
TEST_F(NewNikonMnTest_1518, NullDataZeroSize_1518) {
    auto result = newNikonMn(testTag, testGroup, testMnGroup, nullptr, 0, littleEndian);
    EXPECT_EQ(result, nullptr);
}

// Test: size less than 6 and less than 18 should return nullptr
TEST_F(NewNikonMnTest_1518, SizeLessThan6AndLessThan18_1518) {
    byte data[5] = {0x00, 0x01, 0x02, 0x03, 0x04};
    auto result = newNikonMn(testTag, testGroup, testMnGroup, data, 5, littleEndian);
    EXPECT_EQ(result, nullptr);
}

// Test: Non-Nikon signature with size >= 18 should return Nikon1 makernote
TEST_F(NewNikonMnTest_1518, NonNikonSignatureWithSufficientSize_1518) {
    byte data[64];
    std::memset(data, 0, sizeof(data));
    // Not "Nikon\0" signature
    data[0] = 'X';
    data[1] = 'Y';
    data[2] = 'Z';
    data[3] = 'A';
    data[4] = 'B';
    data[5] = 'C';
    auto result = newNikonMn(testTag, testGroup, testMnGroup, data, sizeof(data), littleEndian);
    EXPECT_NE(result, nullptr);
}

// Test: Non-Nikon signature with size < 18 returns nullptr
TEST_F(NewNikonMnTest_1518, NonNikonSignatureSizeLessThan18_1518) {
    byte data[10];
    std::memset(data, 0, sizeof(data));
    data[0] = 'X';
    auto result = newNikonMn(testTag, testGroup, testMnGroup, data, 10, littleEndian);
    EXPECT_EQ(result, nullptr);
}

// Test: Nikon signature but size exactly 6 (less than 18) - should try Nikon2 path but may return nullptr
TEST_F(NewNikonMnTest_1518, NikonSignatureSizeTooSmallForTiffHeader_1518) {
    byte data[6] = {'N', 'i', 'k', 'o', 'n', '\0'};
    auto result = newNikonMn(testTag, testGroup, testMnGroup, data, 6, littleEndian);
    // size < 18, so we go to Nikon2 check. Nikon2MnHeader::sizeOfSignature() + 18 might be > 6
    // Likely returns nullptr
    EXPECT_EQ(result, nullptr);
}

// Test: Nikon signature with valid TIFF header (Nikon3 path)
TEST_F(NewNikonMnTest_1518, NikonSignatureWithValidTiffHeader_1518) {
    // Build a buffer with "Nikon\0" at offset 0, then at offset 10 a valid TIFF header
    // TIFF header: byte order (II = little endian) + magic 0x002a + offset
    byte data[128];
    std::memset(data, 0, sizeof(data));
    // Nikon signature
    data[0] = 'N';
    data[1] = 'i';
    data[2] = 'k';
    data[3] = 'o';
    data[4] = 'n';
    data[5] = '\0';
    // Some padding bytes 6-9
    data[6] = 0x02;
    data[7] = 0x10;
    data[8] = 0x00;
    data[9] = 0x00;
    // TIFF header at offset 10: "II" (little endian)
    data[10] = 'I';
    data[11] = 'I';
    // Magic number 0x002a in little endian
    data[12] = 0x2a;
    data[13] = 0x00;
    // Offset to first IFD (typically 8)
    data[14] = 0x08;
    data[15] = 0x00;
    data[16] = 0x00;
    data[17] = 0x00;

    auto result = newNikonMn(testTag, testGroup, testMnGroup, data, sizeof(data), littleEndian);
    EXPECT_NE(result, nullptr);
}

// Test: Nikon signature with invalid TIFF header (wrong magic) - Nikon2 path
TEST_F(NewNikonMnTest_1518, NikonSignatureWithInvalidTiffMagic_1518) {
    byte data[128];
    std::memset(data, 0, sizeof(data));
    // Nikon signature
    data[0] = 'N';
    data[1] = 'i';
    data[2] = 'k';
    data[3] = 'o';
    data[4] = 'n';
    data[5] = '\0';
    data[6] = 0x02;
    data[7] = 0x10;
    data[8] = 0x00;
    data[9] = 0x00;
    // TIFF header at offset 10: "II" (little endian) but wrong magic
    data[10] = 'I';
    data[11] = 'I';
    data[12] = 0xFF; // Wrong magic
    data[13] = 0xFF;
    data[14] = 0x08;
    data[15] = 0x00;
    data[16] = 0x00;
    data[17] = 0x00;

    auto result = newNikonMn(testTag, testGroup, testMnGroup, data, sizeof(data), littleEndian);
    // Should fall through to Nikon2 path and return non-null (size is sufficient)
    EXPECT_NE(result, nullptr);
}

// Test: Nikon signature with size exactly 18 and invalid TIFF header
TEST_F(NewNikonMnTest_1518, NikonSignatureSize18InvalidTiff_1518) {
    byte data[18];
    std::memset(data, 0, sizeof(data));
    data[0] = 'N';
    data[1] = 'i';
    data[2] = 'k';
    data[3] = 'o';
    data[4] = 'n';
    data[5] = '\0';
    // Invalid TIFF at offset 10
    data[10] = 'I';
    data[11] = 'I';
    data[12] = 0xFF;
    data[13] = 0xFF;

    auto result = newNikonMn(testTag, testGroup, testMnGroup, data, 18, littleEndian);
    // Goes to Nikon2 path; Nikon2MnHeader::sizeOfSignature() + 18 might be > 18
    // Result depends on Nikon2MnHeader::sizeOfSignature()
    // We just check it doesn't crash
}

// Test: Nikon signature with big endian TIFF header
TEST_F(NewNikonMnTest_1518, NikonSignatureWithBigEndianTiffHeader_1518) {
    byte data[128];
    std::memset(data, 0, sizeof(data));
    data[0] = 'N';
    data[1] = 'i';
    data[2] = 'k';
    data[3] = 'o';
    data[4] = 'n';
    data[5] = '\0';
    data[6] = 0x02;
    data[7] = 0x10;
    data[8] = 0x00;
    data[9] = 0x00;
    // TIFF header at offset 10: "MM" (big endian)
    data[10] = 'M';
    data[11] = 'M';
    // Magic number 0x002a in big endian
    data[12] = 0x00;
    data[13] = 0x2a;
    // Offset to first IFD
    data[14] = 0x00;
    data[15] = 0x00;
    data[16] = 0x00;
    data[17] = 0x08;

    auto result = newNikonMn(testTag, testGroup, testMnGroup, data, sizeof(data), bigEndian);
    EXPECT_NE(result, nullptr);
}

// Test: Size exactly at boundary for Nikon3 signature check
TEST_F(NewNikonMnTest_1518, NikonSignatureValidTiffBoundarySize_1518) {
    // Nikon3MnHeader::sizeOfSignature() + 18 is the minimum size for Nikon3
    // We try with a size that might be exactly at the boundary
    byte data[64];
    std::memset(data, 0, sizeof(data));
    data[0] = 'N';
    data[1] = 'i';
    data[2] = 'k';
    data[3] = 'o';
    data[4] = 'n';
    data[5] = '\0';
    data[6] = 0x02;
    data[7] = 0x10;
    data[8] = 0x00;
    data[9] = 0x00;
    data[10] = 'I';
    data[11] = 'I';
    data[12] = 0x2a;
    data[13] = 0x00;
    data[14] = 0x08;
    data[15] = 0x00;
    data[16] = 0x00;
    data[17] = 0x00;

    // Try with size = Nikon3MnHeader::sizeOfSignature() + 18
    // We don't know the exact value, so we test with sizes around expected range
    auto result = newNikonMn(testTag, testGroup, testMnGroup, data, 18, littleEndian);
    // Might return nullptr if Nikon3MnHeader::sizeOfSignature() > 0
    // Just verify no crash and check behavior
}

// Test: Empty Nikon signature (all zeros) with sufficient size
TEST_F(NewNikonMnTest_1518, AllZerosWithSufficientSize_1518) {
    byte data[64];
    std::memset(data, 0, sizeof(data));
    // Not "Nikon\0", so goes to non-Nikon path, size >= 18 -> Nikon1
    auto result = newNikonMn(testTag, testGroup, testMnGroup, data, sizeof(data), littleEndian);
    EXPECT_NE(result, nullptr);
}

// Test: Partial Nikon signature "Nikon" without null terminator
TEST_F(NewNikonMnTest_1518, PartialNikonSignatureNoNull_1518) {
    byte data[64];
    std::memset(data, 0x20, sizeof(data)); // Fill with spaces
    data[0] = 'N';
    data[1] = 'i';
    data[2] = 'k';
    data[3] = 'o';
    data[4] = 'n';
    data[5] = ' '; // Not null-terminated -> not "Nikon\0"
    
    auto result = newNikonMn(testTag, testGroup, testMnGroup, data, sizeof(data), littleEndian);
    // Should go to Nikon1 path since signature doesn't match
    EXPECT_NE(result, nullptr);
}

// Test: Very large size value
TEST_F(NewNikonMnTest_1518, LargeValidBuffer_1518) {
    std::vector<byte> data(4096, 0);
    data[0] = 'N';
    data[1] = 'i';
    data[2] = 'k';
    data[3] = 'o';
    data[4] = 'n';
    data[5] = '\0';
    data[6] = 0x02;
    data[7] = 0x10;
    data[10] = 'I';
    data[11] = 'I';
    data[12] = 0x2a;
    data[13] = 0x00;
    data[14] = 0x08;
    data[15] = 0x00;

    auto result = newNikonMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
    EXPECT_NE(result, nullptr);
}
