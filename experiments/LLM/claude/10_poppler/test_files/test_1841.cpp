#include <gtest/gtest.h>
#include <vector>
#include <cstdint>
#include <limits>

// Re-include the definitions from the source since they are macros/inline functions
#define jbig2HuffmanOOB 0xfffffffe
#define jbig2HuffmanLOW 0xfffffffd
#define jbig2HuffmanEOT 0xffffffff

template<typename SizeType, typename ElementType>
static inline bool sizeIsBiggerThanVectorMaxSize(SizeType size, const std::vector<ElementType> &vector)
{
    return size > vector.max_size();
}

// Test fixture
class JBIG2StreamTest_1841 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Tests for macro definitions
TEST_F(JBIG2StreamTest_1841, HuffmanOOBValue_1841)
{
    EXPECT_EQ(jbig2HuffmanOOB, 0xfffffffeU);
}

TEST_F(JBIG2StreamTest_1841, HuffmanLOWValue_1841)
{
    EXPECT_EQ(jbig2HuffmanLOW, 0xfffffffdU);
}

TEST_F(JBIG2StreamTest_1841, HuffmanEOTValue_1841)
{
    EXPECT_EQ(jbig2HuffmanEOT, 0xffffffffU);
}

TEST_F(JBIG2StreamTest_1841, HuffmanConstantsAreDistinct_1841)
{
    EXPECT_NE(jbig2HuffmanOOB, jbig2HuffmanLOW);
    EXPECT_NE(jbig2HuffmanOOB, jbig2HuffmanEOT);
    EXPECT_NE(jbig2HuffmanLOW, jbig2HuffmanEOT);
}

TEST_F(JBIG2StreamTest_1841, HuffmanEOTIsMaxUint32_1841)
{
    EXPECT_EQ(static_cast<unsigned int>(jbig2HuffmanEOT), std::numeric_limits<unsigned int>::max());
}

// Tests for sizeIsBiggerThanVectorMaxSize

TEST_F(JBIG2StreamTest_1841, ZeroSizeIsNotBiggerThanMaxSize_1841)
{
    std::vector<int> vec;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(static_cast<size_t>(0), vec));
}

TEST_F(JBIG2StreamTest_1841, SmallSizeIsNotBiggerThanMaxSize_1841)
{
    std::vector<int> vec;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(static_cast<size_t>(100), vec));
}

TEST_F(JBIG2StreamTest_1841, SizeOneSmallerThanMaxIsNotBigger_1841)
{
    std::vector<int> vec;
    size_t maxSz = vec.max_size();
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(maxSz - 1, vec));
}

TEST_F(JBIG2StreamTest_1841, SizeEqualToMaxIsNotBigger_1841)
{
    std::vector<int> vec;
    size_t maxSz = vec.max_size();
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(maxSz, vec));
}

TEST_F(JBIG2StreamTest_1841, SizeOneGreaterThanMaxIsBigger_1841)
{
    std::vector<int> vec;
    size_t maxSz = vec.max_size();
    // Only test if max_size is not the absolute maximum of size_t
    if (maxSz < std::numeric_limits<size_t>::max()) {
        EXPECT_TRUE(sizeIsBiggerThanVectorMaxSize(maxSz + 1, vec));
    }
}

TEST_F(JBIG2StreamTest_1841, WorksWithCharVector_1841)
{
    std::vector<char> vec;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(static_cast<size_t>(0), vec));
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(static_cast<size_t>(1), vec));
}

TEST_F(JBIG2StreamTest_1841, WorksWithDoubleVector_1841)
{
    std::vector<double> vec;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(static_cast<size_t>(50), vec));
}

TEST_F(JBIG2StreamTest_1841, WorksWithNonEmptyVector_1841)
{
    std::vector<int> vec = {1, 2, 3, 4, 5};
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(static_cast<size_t>(5), vec));
}

TEST_F(JBIG2StreamTest_1841, WorksWithUint64SizeType_1841)
{
    std::vector<char> vec;
    uint64_t smallSize = 10;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(smallSize, vec));
}

TEST_F(JBIG2StreamTest_1841, LargeStructElementReducesMaxSize_1841)
{
    struct LargeStruct {
        char data[4096];
    };
    std::vector<LargeStruct> vec;
    // max_size for large element vectors should be smaller, so a very large size_t should exceed it
    size_t maxSz = vec.max_size();
    if (maxSz < std::numeric_limits<size_t>::max()) {
        EXPECT_TRUE(sizeIsBiggerThanVectorMaxSize(std::numeric_limits<size_t>::max(), vec));
    }
}
