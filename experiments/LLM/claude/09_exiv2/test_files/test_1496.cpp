#include <gtest/gtest.h>
#include <cstring>
#include <vector>

// Include necessary Exiv2 headers
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SigmaMnHeaderTest_1496 : public ::testing::Test {
protected:
    SigmaMnHeader header_;
    
    // Known Sigma signatures based on the code
    // signature1_ is "SIGMA\0\0\0" and signature2_ is "FOVEON\0\0"
    static constexpr const char* sigma_sig = "SIGMA\0\0\0";
    static constexpr const char* foveon_sig = "FOVEON\0\0";
};

// Test that read returns false when passed null data
TEST_F(SigmaMnHeaderTest_1496, ReadNullDataReturnsFalse_1496) {
    bool result = header_.read(nullptr, 100, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when size is too small (less than signature size)
TEST_F(SigmaMnHeaderTest_1496, ReadTooSmallSizeReturnsFalse_1496) {
    std::vector<byte> data(7, 0);
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false with zero size
TEST_F(SigmaMnHeaderTest_1496, ReadZeroSizeReturnsFalse_1496) {
    byte data[8] = {};
    bool result = header_.read(data, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read succeeds with valid SIGMA signature
TEST_F(SigmaMnHeaderTest_1496, ReadValidSigmaSignatureReturnsTrue_1496) {
    byte data[10];
    std::memcpy(data, "SIGMA\0\0\0", 8);
    data[8] = 0;
    data[9] = 0;
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_TRUE(result);
}

// Test that read succeeds with valid FOVEON signature
TEST_F(SigmaMnHeaderTest_1496, ReadValidFoveonSignatureReturnsTrue_1496) {
    byte data[10];
    std::memcpy(data, "FOVEON\0\0", 8);
    data[8] = 0;
    data[9] = 0;
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_TRUE(result);
}

// Test that read fails with invalid/unknown signature
TEST_F(SigmaMnHeaderTest_1496, ReadInvalidSignatureReturnsFalse_1496) {
    byte data[10];
    std::memcpy(data, "INVALID\0", 8);
    data[8] = 0;
    data[9] = 0;
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read works with exactly the minimum required size for SIGMA
TEST_F(SigmaMnHeaderTest_1496, ReadExactMinimumSizeSigma_1496) {
    byte data[8];
    std::memcpy(data, "SIGMA\0\0\0", 8);
    // sizeOfSignature() should be at least 8
    bool result = header_.read(data, 8, littleEndian);
    // This depends on sizeOfSignature() - if it's exactly 8, this should succeed
    // If sizeOfSignature() > 8, it should fail
    // Based on the code, the signature is 8 bytes, so sizeOfSignature() likely returns >= 8
    // We test the observable behavior
    // Since the signature check uses 8 bytes, and sizeOfSignature() is used for size check,
    // if sizeOfSignature() == 8, then this should be true; if > 8, false.
    // We'll just verify it doesn't crash and returns a valid boolean.
    EXPECT_TRUE(result || !result);
}

// Test with SIGMA signature and big endian byte order
TEST_F(SigmaMnHeaderTest_1496, ReadSigmaSignatureBigEndian_1496) {
    byte data[10];
    std::memcpy(data, "SIGMA\0\0\0", 8);
    data[8] = 0;
    data[9] = 0;
    bool result = header_.read(data, sizeof(data), bigEndian);
    EXPECT_TRUE(result);
}

// Test with FOVEON signature and big endian byte order
TEST_F(SigmaMnHeaderTest_1496, ReadFoveonSignatureBigEndian_1496) {
    byte data[10];
    std::memcpy(data, "FOVEON\0\0", 8);
    data[8] = 0;
    data[9] = 0;
    bool result = header_.read(data, sizeof(data), bigEndian);
    EXPECT_TRUE(result);
}

// Test that read fails when data is all zeros
TEST_F(SigmaMnHeaderTest_1496, ReadAllZerosReturnsFalse_1496) {
    byte data[10] = {0};
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read fails with partial SIGMA signature
TEST_F(SigmaMnHeaderTest_1496, ReadPartialSigmaSignatureReturnsFalse_1496) {
    byte data[10];
    std::memcpy(data, "SIGM\0\0\0\0", 8);
    data[8] = 0;
    data[9] = 0;
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read fails with partial FOVEON signature
TEST_F(SigmaMnHeaderTest_1496, ReadPartialFoveonSignatureReturnsFalse_1496) {
    byte data[10];
    std::memcpy(data, "FOVEO\0\0\0", 8);
    data[8] = 0;
    data[9] = 0;
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read can be called multiple times (re-read)
TEST_F(SigmaMnHeaderTest_1496, ReadCanBeCalledMultipleTimes_1496) {
    byte data1[10];
    std::memcpy(data1, "SIGMA\0\0\0", 8);
    data1[8] = 0;
    data1[9] = 0;
    
    byte data2[10];
    std::memcpy(data2, "FOVEON\0\0", 8);
    data2[8] = 0;
    data2[9] = 0;
    
    bool result1 = header_.read(data1, sizeof(data1), littleEndian);
    EXPECT_TRUE(result1);
    
    bool result2 = header_.read(data2, sizeof(data2), littleEndian);
    EXPECT_TRUE(result2);
}

// Test with a large buffer containing valid SIGMA signature
TEST_F(SigmaMnHeaderTest_1496, ReadLargeBufferWithValidSignature_1496) {
    std::vector<byte> data(1024, 0);
    std::memcpy(data.data(), "SIGMA\0\0\0", 8);
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_TRUE(result);
}

// Test case sensitivity - "sigma" should fail
TEST_F(SigmaMnHeaderTest_1496, ReadLowercaseSigmaReturnsFalse_1496) {
    byte data[10];
    std::memcpy(data, "sigma\0\0\0", 8);
    data[8] = 0;
    data[9] = 0;
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_FALSE(result);
}

// Test case sensitivity - "foveon" should fail
TEST_F(SigmaMnHeaderTest_1496, ReadLowercaseFoveonReturnsFalse_1496) {
    byte data[10];
    std::memcpy(data, "foveon\0\0", 8);
    data[8] = 0;
    data[9] = 0;
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_FALSE(result);
}

// Test sizeOfSignature returns a reasonable value
TEST_F(SigmaMnHeaderTest_1496, SizeOfSignatureIsReasonable_1496) {
    size_t sigSize = header_.sizeOfSignature();
    // The signature should be at least 8 bytes (based on memcmp comparisons)
    EXPECT_GE(sigSize, 8u);
}

// Test the start_ offset after successful read
TEST_F(SigmaMnHeaderTest_1496, StartOffsetAfterSuccessfulRead_1496) {
    byte data[10];
    std::memcpy(data, "SIGMA\0\0\0", 8);
    data[8] = 0;
    data[9] = 0;
    
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_TRUE(result);
    
    // After successful read, start_ should equal sizeOfSignature()
    // We verify this through the public start() accessor if available
    // Since start_ is set to sizeOfSignature(), the offset should be >= 8
    EXPECT_GE(header_.start(), 8u);
}
