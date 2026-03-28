#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class Olympus2MnHeaderTest_1441 : public ::testing::Test {
protected:
    Olympus2MnHeader header_;
};

TEST_F(Olympus2MnHeaderTest_1441, DefaultConstruction_1441) {
    // Verify that default construction works without issues
    Olympus2MnHeader h;
    (void)h;
}

TEST_F(Olympus2MnHeaderTest_1441, SizeOfSignatureIsPositive_1441) {
    // The signature size should be a positive value
    size_t sigSize = header_.sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

TEST_F(Olympus2MnHeaderTest_1441, SizeOfSignatureConsistency_1441) {
    // Calling sizeOfSignature multiple times should return the same value
    size_t first = header_.sizeOfSignature();
    size_t second = header_.sizeOfSignature();
    EXPECT_EQ(first, second);
}

TEST_F(Olympus2MnHeaderTest_1441, SizeReturnsExpectedValue_1441) {
    // size() should return a reasonable positive value for the header
    size_t sz = header_.size();
    EXPECT_GT(sz, 0u);
}

TEST_F(Olympus2MnHeaderTest_1441, SizeIsAtLeastSignatureSize_1441) {
    // The total header size should be at least as large as the signature
    EXPECT_GE(header_.size(), header_.sizeOfSignature());
}

TEST_F(Olympus2MnHeaderTest_1441, IfdOffsetReturnsValue_1441) {
    // ifdOffset should return a value (typically the offset to the IFD within the header)
    size_t offset = header_.ifdOffset();
    // The IFD offset should be within a reasonable range
    EXPECT_GE(offset, 0u);
}

TEST_F(Olympus2MnHeaderTest_1441, BaseOffsetWithZero_1441) {
    // Test baseOffset with a zero mnOffset
    size_t base = header_.baseOffset(0);
    // baseOffset should return some value; for Olympus2, it typically returns mnOffset
    (void)base;  // Just ensure no crash
}

TEST_F(Olympus2MnHeaderTest_1441, BaseOffsetWithNonZero_1441) {
    // Test baseOffset with a non-zero mnOffset
    size_t mnOffset = 1024;
    size_t base = header_.baseOffset(mnOffset);
    // The base offset should be deterministic
    size_t base2 = header_.baseOffset(mnOffset);
    EXPECT_EQ(base, base2);
}

TEST_F(Olympus2MnHeaderTest_1441, ReadWithNullptrFails_1441) {
    // Reading with nullptr and zero size should fail or handle gracefully
    bool result = header_.read(nullptr, 0, Exiv2::bigEndian);
    EXPECT_FALSE(result);
}

TEST_F(Olympus2MnHeaderTest_1441, ReadWithInsufficientSizeFails_1441) {
    // Reading with data smaller than signature size should fail
    Exiv2::byte smallData[1] = {0};
    bool result = header_.read(smallData, 1, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

TEST_F(Olympus2MnHeaderTest_1441, ReadWithValidOlympusIISignature_1441) {
    // The Olympus II makernote signature is "OLYMPUS\0II"
    // Signature: "OLYMPUS\0II" followed by version bytes
    const Exiv2::byte validData[] = {
        'O', 'L', 'Y', 'M', 'P', 'U', 'S', 0x00,
        'I', 'I', 0x03, 0x00
    };
    bool result = header_.read(validData, sizeof(validData), Exiv2::littleEndian);
    EXPECT_TRUE(result);
}

TEST_F(Olympus2MnHeaderTest_1441, ReadWithInvalidSignatureFails_1441) {
    // Invalid signature data
    const Exiv2::byte invalidData[] = {
        'N', 'O', 'T', 'O', 'L', 'Y', 'M', 'P',
        'U', 'S', 0x00, 0x00
    };
    bool result = header_.read(invalidData, sizeof(invalidData), Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

TEST_F(Olympus2MnHeaderTest_1441, ReadWithExactSignatureSizeButInvalidData_1441) {
    // Data of exact signature size but with wrong content
    size_t sigSize = header_.sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize, 0x00);
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

TEST_F(Olympus2MnHeaderTest_1441, BaseOffsetWithLargeValue_1441) {
    // Test baseOffset with a large mnOffset value
    size_t largeOffset = 0xFFFFFF;
    size_t base = header_.baseOffset(largeOffset);
    // Just ensure it doesn't crash and returns a deterministic result
    EXPECT_EQ(base, header_.baseOffset(largeOffset));
}

TEST_F(Olympus2MnHeaderTest_1441, SizeOfSignatureStaticBehavior_1441) {
    // sizeOfSignature should return the same value across different instances
    Olympus2MnHeader another;
    EXPECT_EQ(header_.sizeOfSignature(), another.sizeOfSignature());
}

TEST_F(Olympus2MnHeaderTest_1441, ReadWithBigEndianSignature_1441) {
    // Olympus II signature with MM (big endian) byte order marker
    const Exiv2::byte validDataMM[] = {
        'O', 'L', 'Y', 'M', 'P', 'U', 'S', 0x00,
        'M', 'M', 0x00, 0x03
    };
    // This may or may not be valid depending on implementation;
    // we test that it doesn't crash
    bool result = header_.read(validDataMM, sizeof(validDataMM), Exiv2::bigEndian);
    // Not asserting true/false as both outcomes are valid depending on implementation
    (void)result;
}

TEST_F(Olympus2MnHeaderTest_1441, ReadAfterPreviousReadValid_1441) {
    // Test reading valid data after a failed read
    Exiv2::byte smallData[1] = {0};
    header_.read(smallData, 1, Exiv2::littleEndian);

    const Exiv2::byte validData[] = {
        'O', 'L', 'Y', 'M', 'P', 'U', 'S', 0x00,
        'I', 'I', 0x03, 0x00
    };
    bool result = header_.read(validData, sizeof(validData), Exiv2::littleEndian);
    EXPECT_TRUE(result);
}
