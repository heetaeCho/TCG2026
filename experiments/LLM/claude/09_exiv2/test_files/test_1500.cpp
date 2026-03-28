#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers from the exiv2 project
#include "makernote_int.hpp"
#include "types.hpp"

namespace {

using namespace Exiv2::Internal;

// Test fixture for SonyMnHeader
class SonyMnHeaderTest_1500 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<SonyMnHeader>();
    }

    std::unique_ptr<SonyMnHeader> header_;
};

// Test that default construction creates a valid object
TEST_F(SonyMnHeaderTest_1500, DefaultConstruction_1500) {
    ASSERT_NE(header_, nullptr);
}

// Test ifdOffset returns expected value after default construction
TEST_F(SonyMnHeaderTest_1500, IfdOffsetDefault_1500) {
    size_t offset = header_->ifdOffset();
    // After default construction, ifdOffset should return the start_ member's initial value
    // We can at least verify it returns a value without crashing
    EXPECT_GE(offset, 0u);
}

// Test size returns a non-zero value (signature size)
TEST_F(SonyMnHeaderTest_1500, SizeReturnsNonZero_1500) {
    size_t sz = header_->size();
    EXPECT_GT(sz, 0u);
}

// Test sizeOfSignature static method
TEST_F(SonyMnHeaderTest_1500, SizeOfSignatureReturnsExpected_1500) {
    size_t sigSize = SonyMnHeader::sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that size and sizeOfSignature are consistent
TEST_F(SonyMnHeaderTest_1500, SizeConsistentWithSignatureSize_1500) {
    size_t sz = header_->size();
    size_t sigSize = SonyMnHeader::sizeOfSignature();
    // size() should be at least as large as the signature size
    EXPECT_GE(sz, sigSize);
}

// Test read with nullptr data and zero size
TEST_F(SonyMnHeaderTest_1500, ReadWithNullptrAndZeroSize_1500) {
    bool result = header_->read(nullptr, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with data that is too small
TEST_F(SonyMnHeaderTest_1500, ReadWithTooSmallData_1500) {
    const Exiv2::byte smallData[] = {0x00, 0x01};
    bool result = header_->read(smallData, sizeof(smallData), Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid Sony maker note signature "SONY DSC \0\0\0"
TEST_F(SonyMnHeaderTest_1500, ReadWithValidSonySignature_1500) {
    // Sony maker note header: "SONY DSC \0\0\0"
    const Exiv2::byte sonyHeader[] = {
        'S', 'O', 'N', 'Y', ' ', 'D', 'S', 'C', ' ', '\0', '\0', '\0'
    };
    bool result = header_->read(sonyHeader, sizeof(sonyHeader), Exiv2::littleEndian);
    EXPECT_TRUE(result);
}

// Test read with valid Sony signature in big endian
TEST_F(SonyMnHeaderTest_1500, ReadWithValidSonySignatureBigEndian_1500) {
    const Exiv2::byte sonyHeader[] = {
        'S', 'O', 'N', 'Y', ' ', 'D', 'S', 'C', ' ', '\0', '\0', '\0'
    };
    bool result = header_->read(sonyHeader, sizeof(sonyHeader), Exiv2::bigEndian);
    EXPECT_TRUE(result);
}

// Test read with invalid signature
TEST_F(SonyMnHeaderTest_1500, ReadWithInvalidSignature_1500) {
    const Exiv2::byte invalidHeader[] = {
        'N', 'I', 'K', 'O', 'N', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
    };
    bool result = header_->read(invalidHeader, sizeof(invalidHeader), Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test ifdOffset after successful read
TEST_F(SonyMnHeaderTest_1500, IfdOffsetAfterValidRead_1500) {
    const Exiv2::byte sonyHeader[] = {
        'S', 'O', 'N', 'Y', ' ', 'D', 'S', 'C', ' ', '\0', '\0', '\0'
    };
    bool readResult = header_->read(sonyHeader, sizeof(sonyHeader), Exiv2::littleEndian);
    if (readResult) {
        size_t offset = header_->ifdOffset();
        // The IFD offset should be at least the signature size
        EXPECT_GE(offset, SonyMnHeader::sizeOfSignature());
    }
}

// Test read with exactly the signature size
TEST_F(SonyMnHeaderTest_1500, ReadWithExactSignatureSize_1500) {
    const Exiv2::byte sonyHeader[] = {
        'S', 'O', 'N', 'Y', ' ', 'D', 'S', 'C', ' ', '\0', '\0', '\0'
    };
    size_t sigSize = SonyMnHeader::sizeOfSignature();
    bool result = header_->read(sonyHeader, sigSize, Exiv2::littleEndian);
    // Should succeed if the data matches the expected signature size
    EXPECT_TRUE(result);
}

// Test read with data larger than signature
TEST_F(SonyMnHeaderTest_1500, ReadWithLargerData_1500) {
    const Exiv2::byte sonyHeader[] = {
        'S', 'O', 'N', 'Y', ' ', 'D', 'S', 'C', ' ', '\0', '\0', '\0',
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
    };
    bool result = header_->read(sonyHeader, sizeof(sonyHeader), Exiv2::littleEndian);
    EXPECT_TRUE(result);
}

// Test read with all zeros (invalid signature)
TEST_F(SonyMnHeaderTest_1500, ReadWithAllZeros_1500) {
    const Exiv2::byte zeroData[12] = {0};
    bool result = header_->read(zeroData, sizeof(zeroData), Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with size just below signature size
TEST_F(SonyMnHeaderTest_1500, ReadWithSizeBelowSignature_1500) {
    size_t sigSize = SonyMnHeader::sizeOfSignature();
    if (sigSize > 1) {
        const Exiv2::byte sonyHeader[] = {
            'S', 'O', 'N', 'Y', ' ', 'D', 'S', 'C', ' ', '\0', '\0', '\0'
        };
        bool result = header_->read(sonyHeader, sigSize - 1, Exiv2::littleEndian);
        EXPECT_FALSE(result);
    }
}

// Test multiple reads on same object - valid then invalid
TEST_F(SonyMnHeaderTest_1500, MultipleReadsValidThenInvalid_1500) {
    const Exiv2::byte validHeader[] = {
        'S', 'O', 'N', 'Y', ' ', 'D', 'S', 'C', ' ', '\0', '\0', '\0'
    };
    const Exiv2::byte invalidHeader[] = {
        'X', 'X', 'X', 'X', ' ', 'X', 'X', 'X', ' ', '\0', '\0', '\0'
    };

    bool result1 = header_->read(validHeader, sizeof(validHeader), Exiv2::littleEndian);
    EXPECT_TRUE(result1);

    bool result2 = header_->read(invalidHeader, sizeof(invalidHeader), Exiv2::littleEndian);
    EXPECT_FALSE(result2);
}

// Test multiple reads on same object - invalid then valid
TEST_F(SonyMnHeaderTest_1500, MultipleReadsInvalidThenValid_1500) {
    const Exiv2::byte invalidHeader[] = {
        'X', 'X', 'X', 'X', ' ', 'X', 'X', 'X', ' ', '\0', '\0', '\0'
    };
    const Exiv2::byte validHeader[] = {
        'S', 'O', 'N', 'Y', ' ', 'D', 'S', 'C', ' ', '\0', '\0', '\0'
    };

    bool result1 = header_->read(invalidHeader, sizeof(invalidHeader), Exiv2::littleEndian);
    EXPECT_FALSE(result1);

    bool result2 = header_->read(validHeader, sizeof(validHeader), Exiv2::littleEndian);
    EXPECT_TRUE(result2);
}

} // namespace
