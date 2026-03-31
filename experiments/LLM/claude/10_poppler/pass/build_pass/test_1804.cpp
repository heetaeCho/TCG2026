#include <gtest/gtest.h>
#include <vector>
#include <cstdint>
#include <limits>
#include <string>

// Reproduce the macros and function from the source since they are part of the interface
#define jbig2HuffmanOOB 0xfffffffe
#define jbig2HuffmanLOW 0xfffffffd
#define jbig2HuffmanEOT 0xffffffff

template<typename SizeType, typename ElementType>
static inline bool sizeIsBiggerThanVectorMaxSize(SizeType size, const std::vector<ElementType> &vector)
{
    return size > vector.max_size();
}

// Test fixture
class JBIG2StreamTest_1804 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ===== Macro Value Tests =====

TEST_F(JBIG2StreamTest_1804, HuffmanOOBValue_1804)
{
    EXPECT_EQ(jbig2HuffmanOOB, 0xfffffffeU);
}

TEST_F(JBIG2StreamTest_1804, HuffmanLOWValue_1804)
{
    EXPECT_EQ(jbig2HuffmanLOW, 0xfffffffdU);
}

TEST_F(JBIG2StreamTest_1804, HuffmanEOTValue_1804)
{
    EXPECT_EQ(jbig2HuffmanEOT, 0xffffffffU);
}

TEST_F(JBIG2StreamTest_1804, HuffmanMacrosAreDistinct_1804)
{
    EXPECT_NE(jbig2HuffmanOOB, jbig2HuffmanLOW);
    EXPECT_NE(jbig2HuffmanOOB, jbig2HuffmanEOT);
    EXPECT_NE(jbig2HuffmanLOW, jbig2HuffmanEOT);
}

TEST_F(JBIG2StreamTest_1804, HuffmanEOTIsMaxUint32_1804)
{
    EXPECT_EQ(static_cast<uint32_t>(jbig2HuffmanEOT), std::numeric_limits<uint32_t>::max());
}

TEST_F(JBIG2StreamTest_1804, HuffmanOOBIsMaxUint32MinusOne_1804)
{
    EXPECT_EQ(static_cast<uint32_t>(jbig2HuffmanOOB), std::numeric_limits<uint32_t>::max() - 1);
}

TEST_F(JBIG2StreamTest_1804, HuffmanLOWIsMaxUint32MinusTwo_1804)
{
    EXPECT_EQ(static_cast<uint32_t>(jbig2HuffmanLOW), std::numeric_limits<uint32_t>::max() - 2);
}

// ===== sizeIsBiggerThanVectorMaxSize Tests =====

TEST_F(JBIG2StreamTest_1804, SizeZeroIsNotBiggerThanMaxSize_Int_1804)
{
    std::vector<int> vec;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(static_cast<size_t>(0), vec));
}

TEST_F(JBIG2StreamTest_1804, SizeOneIsNotBiggerThanMaxSize_Int_1804)
{
    std::vector<int> vec;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(static_cast<size_t>(1), vec));
}

TEST_F(JBIG2StreamTest_1804, SizeEqualToMaxSizeReturnsFalse_Int_1804)
{
    std::vector<int> vec;
    size_t maxSz = vec.max_size();
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(maxSz, vec));
}

TEST_F(JBIG2StreamTest_1804, SizeLargerThanMaxSizeReturnsTrue_Char_1804)
{
    std::vector<char> vec;
    // max_size() for vector<char> is typically very large but still less than SIZE_MAX in some cases
    // We use a value guaranteed to be larger
    size_t maxSz = vec.max_size();
    if (maxSz < std::numeric_limits<size_t>::max()) {
        EXPECT_TRUE(sizeIsBiggerThanVectorMaxSize(maxSz + 1, vec));
    }
}

TEST_F(JBIG2StreamTest_1804, SmallSizeWithLargeElementType_1804)
{
    struct LargeStruct {
        char data[4096];
    };
    std::vector<LargeStruct> vec;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(static_cast<size_t>(1), vec));
}

TEST_F(JBIG2StreamTest_1804, LargeSizeWithLargeElementTypeReturnsTrue_1804)
{
    struct LargeStruct {
        char data[4096];
    };
    std::vector<LargeStruct> vec;
    size_t maxSz = vec.max_size();
    if (maxSz < std::numeric_limits<size_t>::max()) {
        EXPECT_TRUE(sizeIsBiggerThanVectorMaxSize(maxSz + 1, vec));
    }
}

TEST_F(JBIG2StreamTest_1804, SizeTypeUint64WithSmallValue_1804)
{
    std::vector<int> vec;
    uint64_t smallVal = 10;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(smallVal, vec));
}

TEST_F(JBIG2StreamTest_1804, SizeTypeUint32WithSmallValue_1804)
{
    std::vector<int> vec;
    uint32_t smallVal = 100;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(smallVal, vec));
}

TEST_F(JBIG2StreamTest_1804, SizeTypeIntWithZero_1804)
{
    std::vector<double> vec;
    int zero = 0;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(zero, vec));
}

TEST_F(JBIG2StreamTest_1804, VectorOfUint8_SmallSize_1804)
{
    std::vector<uint8_t> vec;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(static_cast<size_t>(256), vec));
}

TEST_F(JBIG2StreamTest_1804, VectorOfString_SmallSize_1804)
{
    std::vector<std::string> vec;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(static_cast<size_t>(10), vec));
}

TEST_F(JBIG2StreamTest_1804, VectorOfString_ExceedMaxSize_1804)
{
    std::vector<std::string> vec;
    size_t maxSz = vec.max_size();
    if (maxSz < std::numeric_limits<size_t>::max()) {
        EXPECT_TRUE(sizeIsBiggerThanVectorMaxSize(maxSz + 1, vec));
    }
}

TEST_F(JBIG2StreamTest_1804, NonEmptyVectorSameMaxSize_1804)
{
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::vector<int> emptyVec;
    // max_size should be the same regardless of current contents
    EXPECT_EQ(sizeIsBiggerThanVectorMaxSize(static_cast<size_t>(0), vec),
              sizeIsBiggerThanVectorMaxSize(static_cast<size_t>(0), emptyVec));
}

TEST_F(JBIG2StreamTest_1804, MaxSizeConsistencyBetweenCalls_1804)
{
    std::vector<int> vec;
    size_t testSize = 1000000;
    bool result1 = sizeIsBiggerThanVectorMaxSize(testSize, vec);
    bool result2 = sizeIsBiggerThanVectorMaxSize(testSize, vec);
    EXPECT_EQ(result1, result2);
}

TEST_F(JBIG2StreamTest_1804, SizeMaxForSizeT_1804)
{
    std::vector<int> vec;
    size_t maxSizeT = std::numeric_limits<size_t>::max();
    // If vector max_size < SIZE_MAX, then this should return true
    if (vec.max_size() < maxSizeT) {
        EXPECT_TRUE(sizeIsBiggerThanVectorMaxSize(maxSizeT, vec));
    } else {
        EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(maxSizeT, vec));
    }
}
