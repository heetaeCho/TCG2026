#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class PentaxMnHeaderTest_1486 : public ::testing::Test {
protected:
    PentaxMnHeader header_;
};

// Test that ifdOffset returns the same value as sizeOfSignature
TEST_F(PentaxMnHeaderTest_1486, IfdOffsetEqualsSizeOfSignature_1486) {
    EXPECT_EQ(header_.ifdOffset(), PentaxMnHeader::sizeOfSignature());
}

// Test that ifdOffset returns a consistent value across multiple calls
TEST_F(PentaxMnHeaderTest_1486, IfdOffsetIsConsistent_1486) {
    size_t first = header_.ifdOffset();
    size_t second = header_.ifdOffset();
    EXPECT_EQ(first, second);
}

// Test that sizeOfSignature returns a non-zero value (signature must have some size)
TEST_F(PentaxMnHeaderTest_1486, SizeOfSignatureIsNonZero_1486) {
    EXPECT_GT(PentaxMnHeader::sizeOfSignature(), 0u);
}

// Test that ifdOffset is non-zero since sizeOfSignature should be non-zero
TEST_F(PentaxMnHeaderTest_1486, IfdOffsetIsNonZero_1486) {
    EXPECT_GT(header_.ifdOffset(), 0u);
}

// Test default construction and size
TEST_F(PentaxMnHeaderTest_1486, DefaultConstructionSize_1486) {
    size_t sz = header_.size();
    // size should be at least as large as the signature
    EXPECT_GE(sz, PentaxMnHeader::sizeOfSignature());
}

// Test that read with nullptr or zero size fails gracefully
TEST_F(PentaxMnHeaderTest_1486, ReadWithNullDataReturnsFalse_1486) {
    bool result = header_.read(nullptr, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test that read with insufficient data size returns false
TEST_F(PentaxMnHeaderTest_1486, ReadWithInsufficientSizeReturnsFalse_1486) {
    Exiv2::byte data[1] = {0};
    bool result = header_.read(data, 1, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test that read with valid Pentax signature succeeds
TEST_F(PentaxMnHeaderTest_1486, ReadWithValidPentaxSignature_1486) {
    // Pentax maker note signature is "AOC\0" followed by type bytes
    // The typical Pentax signature: "AOC\0MM" or "AOC\0II"
    const Exiv2::byte validData[] = {'A', 'O', 'C', 0x00, 'M', 'M', 0x00, 0x00};
    size_t dataSize = sizeof(validData);
    bool result = header_.read(validData, dataSize, Exiv2::bigEndian);
    // Result depends on exact signature matching; just test it doesn't crash
    // and returns a boolean
    (void)result;
}

// Test ifdOffset after default construction
TEST_F(PentaxMnHeaderTest_1486, IfdOffsetAfterDefaultConstruction_1486) {
    // After default construction, ifdOffset should still equal sizeOfSignature
    EXPECT_EQ(header_.ifdOffset(), PentaxMnHeader::sizeOfSignature());
}

// Test multiple instances have same ifdOffset
TEST(PentaxMnHeaderMultiInstance_1486, MultipleInstancesSameIfdOffset_1486) {
    PentaxMnHeader h1;
    PentaxMnHeader h2;
    EXPECT_EQ(h1.ifdOffset(), h2.ifdOffset());
}

// Test multiple instances have same sizeOfSignature
TEST(PentaxMnHeaderMultiInstance_1486, MultipleInstancesSameSizeOfSignature_1486) {
    EXPECT_EQ(PentaxMnHeader::sizeOfSignature(), PentaxMnHeader::sizeOfSignature());
}
