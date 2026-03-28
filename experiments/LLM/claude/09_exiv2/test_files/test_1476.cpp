#include <gtest/gtest.h>
#include <cstring>
#include <vector>

// Include necessary Exiv2 headers
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PanasonicMnHeaderTest_1476 : public ::testing::Test {
protected:
    PanasonicMnHeader header_;
    
    // The known Panasonic signature is "Panasonic" (9 bytes)
    const unsigned char validSignature_[12] = {'P', 'a', 'n', 'a', 's', 'o', 'n', 'i', 'c', 0, 0, 0};
};

// Test that read returns false when pData is nullptr
TEST_F(PanasonicMnHeaderTest_1476, ReadNullPointerReturnsFalse_1476) {
    bool result = header_.read(nullptr, 100, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when size is 0
TEST_F(PanasonicMnHeaderTest_1476, ReadZeroSizeReturnsFalse_1476) {
    bool result = header_.read(validSignature_, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when size is less than signature size
TEST_F(PanasonicMnHeaderTest_1476, ReadSizeTooSmallReturnsFalse_1476) {
    // Signature size is at least 9 bytes, try with smaller sizes
    for (size_t i = 0; i < 9; ++i) {
        PanasonicMnHeader h;
        bool result = h.read(validSignature_, i, littleEndian);
        EXPECT_FALSE(result) << "Expected false for size=" << i;
    }
}

// Test that read returns false when signature doesn't match
TEST_F(PanasonicMnHeaderTest_1476, ReadInvalidSignatureReturnsFalse_1476) {
    unsigned char invalidData[12] = {'N', 'o', 't', 'P', 'a', 'n', 'a', 's', 'o', 0, 0, 0};
    bool result = header_.read(invalidData, sizeof(invalidData), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns true with valid Panasonic signature and sufficient size
TEST_F(PanasonicMnHeaderTest_1476, ReadValidSignatureReturnsTrue_1476) {
    bool result = header_.read(validSignature_, sizeof(validSignature_), littleEndian);
    EXPECT_TRUE(result);
}

// Test that read works with exactly the minimum required size (sizeOfSignature)
TEST_F(PanasonicMnHeaderTest_1476, ReadExactSignatureSizeReturnsTrue_1476) {
    // sizeOfSignature() should be 12 based on typical Panasonic makernote header
    // Try with 12 bytes first; if that's the signature size
    bool result = header_.read(validSignature_, 12, littleEndian);
    EXPECT_TRUE(result);
}

// Test that read returns false with partially matching signature
TEST_F(PanasonicMnHeaderTest_1476, ReadPartiallyMatchingSignatureReturnsFalse_1476) {
    unsigned char partialMatch[12] = {'P', 'a', 'n', 'a', 's', 'o', 'n', 'i', 'X', 0, 0, 0};
    bool result = header_.read(partialMatch, sizeof(partialMatch), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read works with bigEndian byte order (signature check is byte-order independent)
TEST_F(PanasonicMnHeaderTest_1476, ReadValidSignatureBigEndianReturnsTrue_1476) {
    bool result = header_.read(validSignature_, sizeof(validSignature_), bigEndian);
    EXPECT_TRUE(result);
}

// Test that read with all zeros returns false (invalid signature)
TEST_F(PanasonicMnHeaderTest_1476, ReadAllZerosReturnsFalse_1476) {
    unsigned char zeros[12] = {0};
    bool result = header_.read(zeros, sizeof(zeros), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read can be called multiple times - second call with valid data succeeds
TEST_F(PanasonicMnHeaderTest_1476, ReadCalledTwiceSecondCallSucceeds_1476) {
    unsigned char invalidData[12] = {'X', 'Y', 'Z', 0, 0, 0, 0, 0, 0, 0, 0, 0};
    bool result1 = header_.read(invalidData, sizeof(invalidData), littleEndian);
    EXPECT_FALSE(result1);

    bool result2 = header_.read(validSignature_, sizeof(validSignature_), littleEndian);
    EXPECT_TRUE(result2);
}

// Test that read with a large buffer still works
TEST_F(PanasonicMnHeaderTest_1476, ReadLargeBufferReturnsTrue_1476) {
    std::vector<unsigned char> largeBuffer(1024, 0);
    std::memcpy(largeBuffer.data(), validSignature_, 12);
    bool result = header_.read(largeBuffer.data(), largeBuffer.size(), littleEndian);
    EXPECT_TRUE(result);
}

// Test that the start_ field is set after successful read (observable via the interface if available)
// Since we only have read(), we verify the return value is consistent
TEST_F(PanasonicMnHeaderTest_1476, ReadSuccessfullyMultipleTimes_1476) {
    PanasonicMnHeader h1;
    EXPECT_TRUE(h1.read(validSignature_, sizeof(validSignature_), littleEndian));
    
    PanasonicMnHeader h2;
    EXPECT_TRUE(h2.read(validSignature_, sizeof(validSignature_), bigEndian));
}

// Test signature where only the 9th byte differs
TEST_F(PanasonicMnHeaderTest_1476, ReadSignatureDiffersAtLastByte_1476) {
    unsigned char almostValid[12] = {'P', 'a', 'n', 'a', 's', 'o', 'n', 'i', 'd', 0, 0, 0};
    bool result = header_.read(almostValid, sizeof(almostValid), littleEndian);
    EXPECT_FALSE(result);
}

// Test with size of exactly 1
TEST_F(PanasonicMnHeaderTest_1476, ReadSizeOneReturnsFalse_1476) {
    bool result = header_.read(validSignature_, 1, littleEndian);
    EXPECT_FALSE(result);
}
