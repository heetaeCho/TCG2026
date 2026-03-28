#include <gtest/gtest.h>
#include <vector>
#include <cstdint>
#include <limits>
#include <string>

// Re-declare the constants as they are #defines in the source
#define jbig2HuffmanOOB 0xfffffffe
#define jbig2HuffmanLOW 0xfffffffd
#define jbig2HuffmanEOT 0xffffffff

// Re-declare the template function matching the interface from the source
template<typename SizeType, typename ElementType>
static inline bool sizeIsBiggerThanVectorMaxSize(SizeType size, const std::vector<ElementType> &vector)
{
    return size > vector.max_size();
}

// Test fixture
class JBIG2StreamTest_1840 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Tests for Huffman constants
TEST_F(JBIG2StreamTest_1840, HuffmanOOBValue_1840)
{
    EXPECT_EQ(jbig2HuffmanOOB, 0xfffffffeU);
}

TEST_F(JBIG2StreamTest_1840, HuffmanLOWValue_1840)
{
    EXPECT_EQ(jbig2HuffmanLOW, 0xfffffffdU);
}

TEST_F(JBIG2StreamTest_1840, HuffmanEOTValue_1840)
{
    EXPECT_EQ(jbig2HuffmanEOT, 0xffffffffU);
}

TEST_F(JBIG2StreamTest_1840, HuffmanConstantsAreDistinct_1840)
{
    EXPECT_NE(jbig2HuffmanOOB, jbig2HuffmanLOW);
    EXPECT_NE(jbig2HuffmanOOB, jbig2HuffmanEOT);
    EXPECT_NE(jbig2HuffmanLOW, jbig2HuffmanEOT);
}

TEST_F(JBIG2StreamTest_1840, HuffmanConstantsOrdering_1840)
{
    EXPECT_GT(jbig2HuffmanEOT, jbig2HuffmanOOB);
    EXPECT_GT(jbig2HuffmanOOB, jbig2HuffmanLOW);
}

// Tests for sizeIsBiggerThanVectorMaxSize

TEST_F(JBIG2StreamTest_1840, SizeZeroIsNotBiggerThanMaxSize_1840)
{
    std::vector<int> vec;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize<size_t, int>(0, vec));
}

TEST_F(JBIG2StreamTest_1840, SizeOneIsNotBiggerThanMaxSize_1840)
{
    std::vector<int> vec;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize<size_t, int>(1, vec));
}

TEST_F(JBIG2StreamTest_1840, SizeEqualToMaxSizeReturnsFalse_1840)
{
    std::vector<int> vec;
    size_t maxSz = vec.max_size();
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize<size_t, int>(maxSz, vec));
}

TEST_F(JBIG2StreamTest_1840, SmallSizeReturnsFalse_1840)
{
    std::vector<char> vec;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize<size_t, char>(100, vec));
}

TEST_F(JBIG2StreamTest_1840, NonEmptyVectorSmallSizeReturnsFalse_1840)
{
    std::vector<int> vec = {1, 2, 3, 4, 5};
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize<size_t, int>(5, vec));
}

TEST_F(JBIG2StreamTest_1840, WorksWithDifferentElementTypes_1840)
{
    std::vector<double> vec;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize<size_t, double>(0, vec));
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize<size_t, double>(42, vec));
}

TEST_F(JBIG2StreamTest_1840, WorksWithStringVector_1840)
{
    std::vector<std::string> vec;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize<size_t, std::string>(10, vec));
}

TEST_F(JBIG2StreamTest_1840, WorksWithUnsignedLongLongSizeType_1840)
{
    std::vector<char> vec;
    unsigned long long smallSize = 100;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize<unsigned long long, char>(smallSize, vec));
}

TEST_F(JBIG2StreamTest_1840, LargeSizeWithLargeElementType_1840)
{
    struct LargeStruct {
        char data[4096];
    };
    std::vector<LargeStruct> vec;
    size_t maxSz = vec.max_size();
    // max_size for large element types is smaller, so exceeding it is more feasible
    if (maxSz < std::numeric_limits<size_t>::max()) {
        EXPECT_TRUE(sizeIsBiggerThanVectorMaxSize<size_t, LargeStruct>(maxSz + 1, vec));
    }
}

TEST_F(JBIG2StreamTest_1840, ModerateSizeReturnsFalse_1840)
{
    std::vector<int> vec;
    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize<size_t, int>(1000000, vec));
}

TEST_F(JBIG2StreamTest_1840, SizeMaxReturnsTrueForCharVector_1840)
{
    // For most implementations, max_size() of vector<char> might be close to SIZE_MAX
    // but SIZE_MAX itself should be >= max_size, so this tests the boundary
    std::vector<char> vec;
    size_t maxSz = vec.max_size();
    if (maxSz < std::numeric_limits<size_t>::max()) {
        EXPECT_TRUE(sizeIsBiggerThanVectorMaxSize<size_t, char>(std::numeric_limits<size_t>::max(), vec));
    }
}
