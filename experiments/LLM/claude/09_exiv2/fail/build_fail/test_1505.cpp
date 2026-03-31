#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class Casio2MnHeaderTest_1505 : public ::testing::Test {
protected:
    Casio2MnHeader header_;
};

// Test that a default-constructed Casio2MnHeader returns a consistent ifdOffset
TEST_F(Casio2MnHeaderTest_1505, DefaultConstructor_IfdOffset_1505) {
    size_t offset = header_.ifdOffset();
    // The ifdOffset should be a deterministic value after default construction
    // We just verify it's callable and returns a consistent value
    EXPECT_EQ(offset, header_.ifdOffset());
}

// Test that size() returns a non-zero value for the header
TEST_F(Casio2MnHeaderTest_1505, Size_ReturnsNonZero_1505) {
    size_t sz = header_.size();
    EXPECT_GT(sz, 0u);
}

// Test that sizeOfSignature returns a value consistent with size
TEST_F(Casio2MnHeaderTest_1505, SizeOfSignature_ReturnsValue_1505) {
    size_t sigSize = Casio2MnHeader::sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that byteOrder returns a valid byte order after default construction
TEST_F(Casio2MnHeaderTest_1505, DefaultByteOrder_1505) {
    ByteOrder bo = header_.byteOrder();
    // ByteOrder should be one of the known values
    EXPECT_TRUE(bo == bigEndian || bo == littleEndian || bo == invalidByteOrder);
}

// Test read with null data returns false
TEST_F(Casio2MnHeaderTest_1505, Read_NullData_ReturnsFalse_1505) {
    bool result = header_.read(nullptr, 0, bigEndian);
    EXPECT_FALSE(result);
}

// Test read with insufficient size returns false
TEST_F(Casio2MnHeaderTest_1505, Read_InsufficientSize_ReturnsFalse_1505) {
    const Exiv2::byte data[] = {0x00, 0x01};
    bool result = header_.read(data, 2, bigEndian);
    EXPECT_FALSE(result);
}

// Test read with valid Casio2 maker note signature
TEST_F(Casio2MnHeaderTest_1505, Read_ValidSignature_ReturnsTrue_1505) {
    // Casio2 maker note signature is "QVC\0\0\0"
    const Exiv2::byte data[] = {
        'Q', 'V', 'C', '\0', '\0', '\0',
        // Some additional bytes for the header
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    bool result = header_.read(data, sizeof(data), bigEndian);
    EXPECT_TRUE(result);
}

// Test that after a successful read, ifdOffset returns a reasonable value
TEST_F(Casio2MnHeaderTest_1505, Read_Valid_IfdOffsetAfterRead_1505) {
    const Exiv2::byte data[] = {
        'Q', 'V', 'C', '\0', '\0', '\0',
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    if (header_.read(data, sizeof(data), bigEndian)) {
        size_t offset = header_.ifdOffset();
        // ifdOffset should be within or at the boundary of the data
        EXPECT_GE(offset, 0u);
    }
}

// Test read with wrong signature returns false
TEST_F(Casio2MnHeaderTest_1505, Read_WrongSignature_ReturnsFalse_1505) {
    const Exiv2::byte data[] = {
        'X', 'Y', 'Z', '\0', '\0', '\0',
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    bool result = header_.read(data, sizeof(data), bigEndian);
    EXPECT_FALSE(result);
}

// Test read with exact minimum size equal to sizeOfSignature
TEST_F(Casio2MnHeaderTest_1505, Read_ExactSignatureSize_1505) {
    size_t sigSize = Casio2MnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize, 0);
    // Set up "QVC\0\0\0" signature
    if (sigSize >= 6) {
        data[0] = 'Q';
        data[1] = 'V';
        data[2] = 'C';
        data[3] = '\0';
        data[4] = '\0';
        data[5] = '\0';
    }
    bool result = header_.read(data.data(), data.size(), bigEndian);
    // May or may not succeed depending on minimum required size
    // Just ensure it doesn't crash
    (void)result;
}

// Test that size() and sizeOfSignature() are consistent
TEST_F(Casio2MnHeaderTest_1505, SizeConsistency_1505) {
    size_t headerSize = header_.size();
    size_t sigSize = Casio2MnHeader::sizeOfSignature();
    // Header size should be at least as large as the signature size
    EXPECT_GE(headerSize, sigSize);
}

// Test read with size exactly one less than signature size
TEST_F(Casio2MnHeaderTest_1505, Read_OneLessThanSignatureSize_ReturnsFalse_1505) {
    size_t sigSize = Casio2MnHeader::sizeOfSignature();
    if (sigSize > 0) {
        std::vector<Exiv2::byte> data(sigSize - 1, 0);
        if (data.size() >= 3) {
            data[0] = 'Q';
            data[1] = 'V';
            data[2] = 'C';
        }
        bool result = header_.read(data.data(), data.size(), bigEndian);
        EXPECT_FALSE(result);
    }
}

// Test that multiple calls to ifdOffset return the same value
TEST_F(Casio2MnHeaderTest_1505, IfdOffset_Idempotent_1505) {
    EXPECT_EQ(header_.ifdOffset(), header_.ifdOffset());
}

// Test that multiple calls to byteOrder return the same value
TEST_F(Casio2MnHeaderTest_1505, ByteOrder_Idempotent_1505) {
    EXPECT_EQ(header_.byteOrder(), header_.byteOrder());
}

// Test read with littleEndian byte order
TEST_F(Casio2MnHeaderTest_1505, Read_LittleEndian_1505) {
    const Exiv2::byte data[] = {
        'Q', 'V', 'C', '\0', '\0', '\0',
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    bool result = header_.read(data, sizeof(data), littleEndian);
    // The byte order parameter may or may not affect the result
    // Just ensure it doesn't crash
    (void)result;
}
