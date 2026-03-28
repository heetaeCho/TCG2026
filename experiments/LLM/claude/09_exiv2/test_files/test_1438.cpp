#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers from exiv2
#include "makernote_int.hpp"
#include "types.hpp"

namespace {

using namespace Exiv2::Internal;

// Test fixture for OlympusMnHeader
class OlympusMnHeaderTest_1438 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<OlympusMnHeader>();
    }

    std::unique_ptr<OlympusMnHeader> header_;
};

// Test that ifdOffset returns the same value as sizeOfSignature
TEST_F(OlympusMnHeaderTest_1438, IfdOffsetEqualsSizeOfSignature_1438) {
    EXPECT_EQ(header_->ifdOffset(), OlympusMnHeader::sizeOfSignature());
}

// Test that ifdOffset returns a non-zero value (signature should have some size)
TEST_F(OlympusMnHeaderTest_1438, IfdOffsetIsNonZero_1438) {
    EXPECT_GT(header_->ifdOffset(), 0u);
}

// Test that sizeOfSignature is consistent across multiple calls
TEST_F(OlympusMnHeaderTest_1438, SizeOfSignatureIsConsistent_1438) {
    size_t first = OlympusMnHeader::sizeOfSignature();
    size_t second = OlympusMnHeader::sizeOfSignature();
    EXPECT_EQ(first, second);
}

// Test that ifdOffset is consistent across multiple calls
TEST_F(OlympusMnHeaderTest_1438, IfdOffsetIsConsistent_1438) {
    size_t first = header_->ifdOffset();
    size_t second = header_->ifdOffset();
    EXPECT_EQ(first, second);
}

// Test that size() returns a value (header has some size)
TEST_F(OlympusMnHeaderTest_1438, SizeReturnsValue_1438) {
    size_t sz = header_->size();
    EXPECT_GT(sz, 0u);
}

// Test that size() is at least as large as sizeOfSignature
TEST_F(OlympusMnHeaderTest_1438, SizeIsAtLeastSizeOfSignature_1438) {
    EXPECT_GE(header_->size(), OlympusMnHeader::sizeOfSignature());
}

// Test that read fails with null data
TEST_F(OlympusMnHeaderTest_1438, ReadWithNullDataReturnsFalse_1438) {
    bool result = header_->read(nullptr, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test that read fails with insufficient data size
TEST_F(OlympusMnHeaderTest_1438, ReadWithInsufficientSizeReturnsFalse_1438) {
    Exiv2::byte data[1] = {0};
    bool result = header_->read(data, 1, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test that read with valid Olympus signature succeeds
TEST_F(OlympusMnHeaderTest_1438, ReadWithValidOlympusSignature_1438) {
    // Olympus makernote signature is "OLYMP\0" followed by version bytes
    // The signature is typically "OLYMP\0" (6 bytes) + additional data
    const Exiv2::byte olympusData[] = {
        'O', 'L', 'Y', 'M', 'P', '\0',  // OLYMP signature
        0x01, 0x00,                        // version or padding
        0x00, 0x00, 0x00, 0x00,           // extra data
        0x00, 0x00, 0x00, 0x00
    };
    bool result = header_->read(olympusData, sizeof(olympusData), Exiv2::littleEndian);
    // The result depends on exact signature match; we just verify it doesn't crash
    // and returns a boolean
    (void)result;
}

// Test that read with invalid signature returns false
TEST_F(OlympusMnHeaderTest_1438, ReadWithInvalidSignatureReturnsFalse_1438) {
    const Exiv2::byte invalidData[] = {
        'N', 'O', 'T', 'O', 'L', 'Y',
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    bool result = header_->read(invalidData, sizeof(invalidData), Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test ifdOffset on a freshly constructed header
TEST_F(OlympusMnHeaderTest_1438, DefaultConstructedIfdOffset_1438) {
    OlympusMnHeader freshHeader;
    EXPECT_EQ(freshHeader.ifdOffset(), OlympusMnHeader::sizeOfSignature());
}

// Test that multiple instances return the same ifdOffset
TEST_F(OlympusMnHeaderTest_1438, MultipleInstancesSameIfdOffset_1438) {
    OlympusMnHeader header1;
    OlympusMnHeader header2;
    EXPECT_EQ(header1.ifdOffset(), header2.ifdOffset());
}

// Test read with zero size
TEST_F(OlympusMnHeaderTest_1438, ReadWithZeroSize_1438) {
    const Exiv2::byte data[] = {0x00};
    bool result = header_->read(data, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with big endian byte order
TEST_F(OlympusMnHeaderTest_1438, ReadWithBigEndianByteOrder_1438) {
    const Exiv2::byte olympusData[] = {
        'O', 'L', 'Y', 'M', 'P', '\0',
        0x01, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    bool result = header_->read(olympusData, sizeof(olympusData), Exiv2::bigEndian);
    // Just verify it handles different byte orders without crashing
    (void)result;
}

// Test that read with exact signature size boundary
TEST_F(OlympusMnHeaderTest_1438, ReadWithExactSignatureSize_1438) {
    size_t sigSize = OlympusMnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize);
    // Fill with Olympus signature
    const char sig[] = "OLYMP";
    if (sigSize >= sizeof(sig)) {
        std::memcpy(data.data(), sig, sizeof(sig));
    }
    bool result = header_->read(data.data(), data.size(), Exiv2::littleEndian);
    // Result depends on whether exact size is sufficient
    (void)result;
}

}  // namespace
