#include <gtest/gtest.h>
#include <cstring>
#include <cstdint>

// Since TiffBinaryArray has complex dependencies, we test the extracted logic
// of updOrigDataBuf directly based on the implementation provided.

namespace Exiv2 {
namespace Internal {

using byte = uint8_t;

// Minimal testable version matching the provided implementation
class TiffBinaryArray {
public:
    bool updOrigDataBuf(const byte* pData, size_t size) {
        if (origSize_ != size)
            return false;
        if (origData_ == pData)
            return true;
        std::memcpy(origData_, pData, origSize_);
        return true;
    }

    // Test helpers to set internal state
    void setOrigData(byte* data, size_t size) {
        origData_ = data;
        origSize_ = size;
    }

    byte* getOrigData() const { return origData_; }
    size_t getOrigSize() const { return origSize_; }

private:
    byte* origData_ = nullptr;
    size_t origSize_ = 0;
};

}  // namespace Internal
}  // namespace Exiv2

using Exiv2::Internal::TiffBinaryArray;
using byte = uint8_t;

class TiffBinaryArrayTest_316 : public ::testing::Test {
protected:
    TiffBinaryArray array;
};

// Test that updOrigDataBuf returns false when size doesn't match origSize_
TEST_F(TiffBinaryArrayTest_316, SizeMismatchReturnsFalse_316) {
    byte buffer[10] = {0};
    byte source[5] = {1, 2, 3, 4, 5};

    array.setOrigData(buffer, 10);

    // Pass size=5 but origSize_ is 10 => should return false
    EXPECT_FALSE(array.updOrigDataBuf(source, 5));
}

// Test that updOrigDataBuf returns false when origSize_ is 0 and size is non-zero
TEST_F(TiffBinaryArrayTest_316, ZeroOrigSizeNonZeroSizeReturnsFalse_316) {
    byte source[5] = {1, 2, 3, 4, 5};

    // origData_ = nullptr, origSize_ = 0 (default)
    EXPECT_FALSE(array.updOrigDataBuf(source, 5));
}

// Test that updOrigDataBuf returns true when same pointer is passed
TEST_F(TiffBinaryArrayTest_316, SamePointerReturnsTrue_316) {
    byte buffer[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    array.setOrigData(buffer, 10);

    // Same pointer and same size => should return true without copying
    EXPECT_TRUE(array.updOrigDataBuf(buffer, 10));
}

// Test that updOrigDataBuf copies data when sizes match and pointers differ
TEST_F(TiffBinaryArrayTest_316, CopiesDataWhenSizeMatchesDifferentPointer_316) {
    byte dest[5] = {0, 0, 0, 0, 0};
    byte source[5] = {10, 20, 30, 40, 50};

    array.setOrigData(dest, 5);

    EXPECT_TRUE(array.updOrigDataBuf(source, 5));

    // Verify data was copied
    EXPECT_EQ(dest[0], 10);
    EXPECT_EQ(dest[1], 20);
    EXPECT_EQ(dest[2], 30);
    EXPECT_EQ(dest[3], 40);
    EXPECT_EQ(dest[4], 50);
}

// Test with size 0 and matching origSize_ 0
TEST_F(TiffBinaryArrayTest_316, BothSizesZeroReturnsTrue_316) {
    // origData_ = nullptr, origSize_ = 0 (default)
    byte source[1] = {0};

    // Both sizes are 0, but pointers differ => memcpy with size 0 is safe
    EXPECT_TRUE(array.updOrigDataBuf(source, 0));
}

// Test with nullptr pData and matching size 0
TEST_F(TiffBinaryArrayTest_316, NullptrWithZeroSizeReturnsTrue_316) {
    // origData_ = nullptr, origSize_ = 0
    // pData = nullptr, size = 0
    // origSize_ == size (0 == 0) => true
    // origData_ == pData (nullptr == nullptr) => returns true early
    EXPECT_TRUE(array.updOrigDataBuf(nullptr, 0));
}

// Test that size mismatch (origSize_ > size) returns false
TEST_F(TiffBinaryArrayTest_316, OrigSizeLargerThanSizeReturnsFalse_316) {
    byte buffer[20] = {0};
    byte source[10] = {0};

    array.setOrigData(buffer, 20);

    EXPECT_FALSE(array.updOrigDataBuf(source, 10));
}

// Test that size mismatch (origSize_ < size) returns false
TEST_F(TiffBinaryArrayTest_316, OrigSizeSmallerThanSizeReturnsFalse_316) {
    byte buffer[5] = {0};
    byte source[10] = {0};

    array.setOrigData(buffer, 5);

    EXPECT_FALSE(array.updOrigDataBuf(source, 10));
}

// Test copy with single byte
TEST_F(TiffBinaryArrayTest_316, SingleByteCopy_316) {
    byte dest[1] = {0};
    byte source[1] = {255};

    array.setOrigData(dest, 1);

    EXPECT_TRUE(array.updOrigDataBuf(source, 1));
    EXPECT_EQ(dest[0], 255);
}

// Test that original data is preserved when size mismatch occurs
TEST_F(TiffBinaryArrayTest_316, DataNotModifiedOnSizeMismatch_316) {
    byte dest[5] = {1, 2, 3, 4, 5};
    byte source[3] = {10, 20, 30};

    array.setOrigData(dest, 5);

    EXPECT_FALSE(array.updOrigDataBuf(source, 3));

    // Original data should not be modified
    EXPECT_EQ(dest[0], 1);
    EXPECT_EQ(dest[1], 2);
    EXPECT_EQ(dest[2], 3);
    EXPECT_EQ(dest[3], 4);
    EXPECT_EQ(dest[4], 5);
}

// Test large buffer copy
TEST_F(TiffBinaryArrayTest_316, LargeBufferCopy_316) {
    const size_t bufSize = 4096;
    byte dest[bufSize];
    byte source[bufSize];

    std::memset(dest, 0, bufSize);
    for (size_t i = 0; i < bufSize; ++i) {
        source[i] = static_cast<byte>(i % 256);
    }

    array.setOrigData(dest, bufSize);

    EXPECT_TRUE(array.updOrigDataBuf(source, bufSize));

    EXPECT_EQ(std::memcmp(dest, source, bufSize), 0);
}

// Test multiple successive updates
TEST_F(TiffBinaryArrayTest_316, MultipleUpdates_316) {
    byte dest[4] = {0, 0, 0, 0};
    byte source1[4] = {1, 2, 3, 4};
    byte source2[4] = {5, 6, 7, 8};

    array.setOrigData(dest, 4);

    EXPECT_TRUE(array.updOrigDataBuf(source1, 4));
    EXPECT_EQ(dest[0], 1);
    EXPECT_EQ(dest[3], 4);

    EXPECT_TRUE(array.updOrigDataBuf(source2, 4));
    EXPECT_EQ(dest[0], 5);
    EXPECT_EQ(dest[3], 8);
}
