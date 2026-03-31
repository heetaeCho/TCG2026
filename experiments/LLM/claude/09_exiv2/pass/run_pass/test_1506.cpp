#include <gtest/gtest.h>
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Casio2MnHeaderTest_1506 : public ::testing::Test {
protected:
    Casio2MnHeader header_;
};

// Test default construction and initial byte order
TEST_F(Casio2MnHeaderTest_1506, DefaultConstructor_ByteOrder_1506) {
    // After default construction, byteOrder() should return a valid ByteOrder
    ByteOrder bo = header_.byteOrder();
    // The byte order should be one of the known values
    EXPECT_TRUE(bo == bigEndian || bo == littleEndian || bo == invalidByteOrder);
}

// Test size of signature is non-zero
TEST_F(Casio2MnHeaderTest_1506, SizeOfSignature_1506) {
    size_t sigSize = Casio2MnHeader::sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test size() returns a value >= sizeOfSignature
TEST_F(Casio2MnHeaderTest_1506, SizeReturnsNonZero_1506) {
    size_t sz = header_.size();
    EXPECT_GT(sz, 0u);
    EXPECT_GE(sz, Casio2MnHeader::sizeOfSignature());
}

// Test ifdOffset returns a reasonable value
TEST_F(Casio2MnHeaderTest_1506, IfdOffsetReturnsValue_1506) {
    size_t offset = header_.ifdOffset();
    // The IFD offset should be within the header size
    EXPECT_LE(offset, header_.size());
}

// Test read with nullptr data returns false
TEST_F(Casio2MnHeaderTest_1506, ReadNullDataReturnsFalse_1506) {
    bool result = header_.read(nullptr, 0, bigEndian);
    EXPECT_FALSE(result);
}

// Test read with too small data returns false
TEST_F(Casio2MnHeaderTest_1506, ReadTooSmallDataReturnsFalse_1506) {
    byte smallData[1] = {0};
    bool result = header_.read(smallData, 1, bigEndian);
    EXPECT_FALSE(result);
}

// Test read with zero size returns false
TEST_F(Casio2MnHeaderTest_1506, ReadZeroSizeReturnsFalse_1506) {
    byte data[16] = {0};
    bool result = header_.read(data, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid Casio2 signature
TEST_F(Casio2MnHeaderTest_1506, ReadValidSignature_1506) {
    // Casio2 maker note signature is "QVC\0\0\0"
    const size_t sigSize = Casio2MnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 100, 0);
    // Set the known Casio2 signature: "QVC\0\0\0"
    data[0] = 'Q';
    data[1] = 'V';
    data[2] = 'C';
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;

    bool result = header_.read(data.data(), data.size(), bigEndian);
    EXPECT_TRUE(result);
}

// Test that after successful read, byteOrder reflects the expected order
TEST_F(Casio2MnHeaderTest_1506, ByteOrderAfterRead_BigEndian_1506) {
    const size_t sigSize = Casio2MnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 100, 0);
    data[0] = 'Q';
    data[1] = 'V';
    data[2] = 'C';
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;

    header_.read(data.data(), data.size(), bigEndian);
    ByteOrder bo = header_.byteOrder();
    // After reading, the byte order should be a valid one
    EXPECT_TRUE(bo == bigEndian || bo == littleEndian);
}

// Test read with invalid signature returns false
TEST_F(Casio2MnHeaderTest_1506, ReadInvalidSignature_1506) {
    const size_t sigSize = Casio2MnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 100, 0);
    // Set invalid signature
    data[0] = 'X';
    data[1] = 'Y';
    data[2] = 'Z';
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;

    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with size exactly equal to signature size
TEST_F(Casio2MnHeaderTest_1506, ReadExactSignatureSize_1506) {
    const size_t sigSize = Casio2MnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize, 0);
    data[0] = 'Q';
    data[1] = 'V';
    data[2] = 'C';
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;

    bool result = header_.read(data.data(), data.size(), bigEndian);
    // Should succeed with exactly the signature size
    EXPECT_TRUE(result);
}

// Test read with size one less than signature size
TEST_F(Casio2MnHeaderTest_1506, ReadOneLessThanSignatureSize_1506) {
    const size_t sigSize = Casio2MnHeader::sizeOfSignature();
    if (sigSize > 0) {
        std::vector<byte> data(sigSize - 1, 0);
        if (!data.empty()) {
            data[0] = 'Q';
            if (data.size() > 1) data[1] = 'V';
            if (data.size() > 2) data[2] = 'C';
        }
        bool result = header_.read(data.data(), data.size(), bigEndian);
        EXPECT_FALSE(result);
    }
}

// Test that multiple reads can be performed
TEST_F(Casio2MnHeaderTest_1506, MultipleReads_1506) {
    const size_t sigSize = Casio2MnHeader::sizeOfSignature();
    std::vector<byte> validData(sigSize + 50, 0);
    validData[0] = 'Q';
    validData[1] = 'V';
    validData[2] = 'C';

    // First read with valid data
    bool result1 = header_.read(validData.data(), validData.size(), bigEndian);
    EXPECT_TRUE(result1);

    // Second read with invalid data
    std::vector<byte> invalidData(sigSize + 50, 0xFF);
    bool result2 = header_.read(invalidData.data(), invalidData.size(), bigEndian);
    EXPECT_FALSE(result2);
}

// Test sizeOfSignature is consistent across calls
TEST_F(Casio2MnHeaderTest_1506, SizeOfSignatureConsistent_1506) {
    size_t s1 = Casio2MnHeader::sizeOfSignature();
    size_t s2 = Casio2MnHeader::sizeOfSignature();
    EXPECT_EQ(s1, s2);
}

// Test size is consistent across calls
TEST_F(Casio2MnHeaderTest_1506, SizeConsistent_1506) {
    size_t s1 = header_.size();
    size_t s2 = header_.size();
    EXPECT_EQ(s1, s2);
}

// Test ifdOffset is consistent across calls
TEST_F(Casio2MnHeaderTest_1506, IfdOffsetConsistent_1506) {
    size_t o1 = header_.ifdOffset();
    size_t o2 = header_.ifdOffset();
    EXPECT_EQ(o1, o2);
}
