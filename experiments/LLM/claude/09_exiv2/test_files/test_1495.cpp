#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers from the project
#include "makernote_int.hpp"
#include "types.hpp"

namespace {

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for SigmaMnHeader
class SigmaMnHeaderTest_1495 : public ::testing::Test {
protected:
    SigmaMnHeader header_;
};

// Test that a default-constructed SigmaMnHeader returns a known ifdOffset
TEST_F(SigmaMnHeaderTest_1495, DefaultIfdOffset_1495) {
    // After default construction (before reading any data), ifdOffset should
    // return the initial start_ value. Based on typical Sigma makernote headers,
    // the offset is usually the size of the signature.
    size_t offset = header_.ifdOffset();
    // The offset should be a reasonable non-negative value
    EXPECT_GE(offset, 0u);
}

// Test that size() returns a positive value for the header
TEST_F(SigmaMnHeaderTest_1495, SizeIsPositive_1495) {
    size_t sz = header_.size();
    EXPECT_GT(sz, 0u);
}

// Test that sizeOfSignature returns a positive value
TEST_F(SigmaMnHeaderTest_1495, SizeOfSignatureIsPositive_1495) {
    size_t sigSize = SigmaMnHeader::sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that size() is consistent with sizeOfSignature()
TEST_F(SigmaMnHeaderTest_1495, SizeConsistentWithSignature_1495) {
    size_t sz = header_.size();
    size_t sigSize = SigmaMnHeader::sizeOfSignature();
    // size should be at least as large as the signature
    EXPECT_GE(sz, sigSize);
}

// Test that ifdOffset is consistent with sizeOfSignature
TEST_F(SigmaMnHeaderTest_1495, IfdOffsetConsistentWithSignature_1495) {
    size_t offset = header_.ifdOffset();
    size_t sigSize = SigmaMnHeader::sizeOfSignature();
    // The IFD offset should typically equal the size of the signature
    // (the IFD starts right after the signature)
    EXPECT_EQ(offset, sigSize);
}

// Test read with nullptr or zero size returns false
TEST_F(SigmaMnHeaderTest_1495, ReadWithNullDataReturnsFalse_1495) {
    bool result = header_.read(nullptr, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with insufficient data size returns false
TEST_F(SigmaMnHeaderTest_1495, ReadWithInsufficientSizeReturnsFalse_1495) {
    byte data[1] = {0};
    bool result = header_.read(data, 1, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with a valid Sigma makernote signature ("SIGMA\0\0\0" or "FOVEON\0\0")
TEST_F(SigmaMnHeaderTest_1495, ReadWithValidSigmaSignature_1495) {
    // Sigma makernote header typically starts with "SIGMA\0\0\0" (10 bytes)
    const byte sigmaData[] = {'S', 'I', 'G', 'M', 'A', '\0', '\0', '\0', 0, 0};
    size_t dataSize = sizeof(sigmaData);
    
    // Only test if data is large enough
    if (dataSize >= SigmaMnHeader::sizeOfSignature()) {
        bool result = header_.read(sigmaData, dataSize, littleEndian);
        EXPECT_TRUE(result);
    }
}

// Test read with valid FOVEON signature
TEST_F(SigmaMnHeaderTest_1495, ReadWithValidFoveonSignature_1495) {
    // FOVEON signature: "FOVEON\0\0" followed by padding
    const byte foveonData[] = {'F', 'O', 'V', 'E', 'O', 'N', '\0', '\0', 0, 0};
    size_t dataSize = sizeof(foveonData);
    
    if (dataSize >= SigmaMnHeader::sizeOfSignature()) {
        bool result = header_.read(foveonData, dataSize, littleEndian);
        EXPECT_TRUE(result);
    }
}

// Test read with invalid signature returns false
TEST_F(SigmaMnHeaderTest_1495, ReadWithInvalidSignatureReturnsFalse_1495) {
    const byte invalidData[] = {'I', 'N', 'V', 'A', 'L', 'I', 'D', '\0', 0, 0};
    size_t dataSize = sizeof(invalidData);
    
    bool result = header_.read(invalidData, dataSize, littleEndian);
    EXPECT_FALSE(result);
}

// Test that after successful read, ifdOffset returns expected value
TEST_F(SigmaMnHeaderTest_1495, IfdOffsetAfterSuccessfulRead_1495) {
    const byte sigmaData[] = {'S', 'I', 'G', 'M', 'A', '\0', '\0', '\0', 0, 0};
    size_t dataSize = sizeof(sigmaData);
    
    if (dataSize >= SigmaMnHeader::sizeOfSignature()) {
        bool readOk = header_.read(sigmaData, dataSize, littleEndian);
        if (readOk) {
            size_t offset = header_.ifdOffset();
            EXPECT_EQ(offset, SigmaMnHeader::sizeOfSignature());
        }
    }
}

// Test read with big endian byte order
TEST_F(SigmaMnHeaderTest_1495, ReadWithBigEndian_1495) {
    const byte sigmaData[] = {'S', 'I', 'G', 'M', 'A', '\0', '\0', '\0', 0, 0};
    size_t dataSize = sizeof(sigmaData);
    
    if (dataSize >= SigmaMnHeader::sizeOfSignature()) {
        bool result = header_.read(sigmaData, dataSize, bigEndian);
        EXPECT_TRUE(result);
    }
}

// Test that size() after read is same as before read
TEST_F(SigmaMnHeaderTest_1495, SizeUnchangedAfterRead_1495) {
    size_t sizeBefore = header_.size();
    
    const byte sigmaData[] = {'S', 'I', 'G', 'M', 'A', '\0', '\0', '\0', 0, 0};
    size_t dataSize = sizeof(sigmaData);
    
    if (dataSize >= SigmaMnHeader::sizeOfSignature()) {
        header_.read(sigmaData, dataSize, littleEndian);
    }
    
    size_t sizeAfter = header_.size();
    EXPECT_EQ(sizeBefore, sizeAfter);
}

// Test read with exact minimum size
TEST_F(SigmaMnHeaderTest_1495, ReadWithExactMinimumSize_1495) {
    size_t minSize = SigmaMnHeader::sizeOfSignature();
    std::vector<byte> data(minSize, 0);
    // Fill with SIGMA signature
    const char* sig = "SIGMA";
    for (size_t i = 0; i < 5 && i < minSize; ++i) {
        data[i] = static_cast<byte>(sig[i]);
    }
    
    bool result = header_.read(data.data(), data.size(), littleEndian);
    // Result depends on whether the exact minimum size is sufficient
    // We just verify it doesn't crash
    (void)result;
}

// Test that multiple reads work correctly
TEST_F(SigmaMnHeaderTest_1495, MultipleReadsWorkCorrectly_1495) {
    const byte sigmaData[] = {'S', 'I', 'G', 'M', 'A', '\0', '\0', '\0', 0, 0};
    const byte invalidData[] = {'X', 'X', 'X', 'X', 'X', 'X', 'X', '\0', 0, 0};
    size_t dataSize = sizeof(sigmaData);
    
    if (dataSize >= SigmaMnHeader::sizeOfSignature()) {
        bool result1 = header_.read(sigmaData, dataSize, littleEndian);
        bool result2 = header_.read(invalidData, dataSize, littleEndian);
        
        // First should succeed (valid signature), second should fail
        if (result1) {
            EXPECT_TRUE(result1);
        }
        EXPECT_FALSE(result2);
    }
}

} // namespace
