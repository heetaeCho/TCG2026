#include <gtest/gtest.h>
#include "yaml-cpp/binary.h"
#include <vector>
#include <cstring>

class BinaryTest_10 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor creates an empty Binary
TEST_F(BinaryTest_10, DefaultConstructorCreatesEmptyBinary_10) {
    YAML::Binary bin;
    EXPECT_EQ(bin.size(), 0u);
    EXPECT_EQ(bin.data(), nullptr);
}

// Test constructor with data and size
TEST_F(BinaryTest_10, ConstructorWithDataAndSize_10) {
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
    YAML::Binary bin(data, sizeof(data));
    EXPECT_EQ(bin.size(), 4u);
    EXPECT_NE(bin.data(), nullptr);
    EXPECT_EQ(bin.data()[0], 0x01);
    EXPECT_EQ(bin.data()[1], 0x02);
    EXPECT_EQ(bin.data()[2], 0x03);
    EXPECT_EQ(bin.data()[3], 0x04);
}

// Test constructor with nullptr and zero size
TEST_F(BinaryTest_10, ConstructorWithNullptrAndZeroSize_10) {
    YAML::Binary bin(nullptr, 0);
    EXPECT_EQ(bin.size(), 0u);
}

// Test equality of two empty Binaries
TEST_F(BinaryTest_10, TwoEmptyBinariesAreEqual_10) {
    YAML::Binary bin1;
    YAML::Binary bin2;
    EXPECT_TRUE(bin1 == bin2);
    EXPECT_FALSE(bin1 != bin2);
}

// Test equality of two identical non-empty Binaries
TEST_F(BinaryTest_10, TwoIdenticalBinariesAreEqual_10) {
    const unsigned char data[] = {0x0A, 0x0B, 0x0C};
    YAML::Binary bin1(data, sizeof(data));
    YAML::Binary bin2(data, sizeof(data));
    EXPECT_TRUE(bin1 == bin2);
    EXPECT_FALSE(bin1 != bin2);
}

// Test inequality of Binaries with different sizes
TEST_F(BinaryTest_10, BinariesWithDifferentSizesAreNotEqual_10) {
    const unsigned char data1[] = {0x01, 0x02, 0x03};
    const unsigned char data2[] = {0x01, 0x02};
    YAML::Binary bin1(data1, sizeof(data1));
    YAML::Binary bin2(data2, sizeof(data2));
    EXPECT_FALSE(bin1 == bin2);
    EXPECT_TRUE(bin1 != bin2);
}

// Test inequality of Binaries with same size but different data
TEST_F(BinaryTest_10, BinariesWithSameSizeDifferentDataAreNotEqual_10) {
    const unsigned char data1[] = {0x01, 0x02, 0x03};
    const unsigned char data2[] = {0x01, 0x02, 0x04};
    YAML::Binary bin1(data1, sizeof(data1));
    YAML::Binary bin2(data2, sizeof(data2));
    EXPECT_FALSE(bin1 == bin2);
    EXPECT_TRUE(bin1 != bin2);
}

// Test equality of a Binary with itself (reflexive)
TEST_F(BinaryTest_10, BinaryIsEqualToItself_10) {
    const unsigned char data[] = {0xFF, 0xFE, 0xFD};
    YAML::Binary bin(data, sizeof(data));
    EXPECT_TRUE(bin == bin);
}

// Test copy constructor
TEST_F(BinaryTest_10, CopyConstructorProducesEqualBinary_10) {
    const unsigned char data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    YAML::Binary bin1(data, sizeof(data));
    YAML::Binary bin2(bin1);
    EXPECT_TRUE(bin1 == bin2);
    EXPECT_EQ(bin2.size(), sizeof(data));
}

// Test move constructor
TEST_F(BinaryTest_10, MoveConstructor_10) {
    const unsigned char data[] = {0xAA, 0xBB, 0xCC};
    YAML::Binary bin1(data, sizeof(data));
    YAML::Binary bin2(std::move(bin1));
    EXPECT_EQ(bin2.size(), 3u);
    EXPECT_EQ(bin2.data()[0], 0xAA);
    EXPECT_EQ(bin2.data()[1], 0xBB);
    EXPECT_EQ(bin2.data()[2], 0xCC);
}

// Test copy assignment operator
TEST_F(BinaryTest_10, CopyAssignmentProducesEqualBinary_10) {
    const unsigned char data[] = {0x11, 0x22};
    YAML::Binary bin1(data, sizeof(data));
    YAML::Binary bin2;
    bin2 = bin1;
    EXPECT_TRUE(bin1 == bin2);
    EXPECT_EQ(bin2.size(), 2u);
}

// Test move assignment operator
TEST_F(BinaryTest_10, MoveAssignment_10) {
    const unsigned char data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    YAML::Binary bin1(data, sizeof(data));
    YAML::Binary bin2;
    bin2 = std::move(bin1);
    EXPECT_EQ(bin2.size(), 4u);
    EXPECT_EQ(bin2.data()[0], 0xDE);
    EXPECT_EQ(bin2.data()[3], 0xEF);
}

// Test swap functionality
TEST_F(BinaryTest_10, SwapWithVector_10) {
    const unsigned char data[] = {0x01, 0x02, 0x03};
    YAML::Binary bin(data, sizeof(data));

    std::vector<unsigned char> newData = {0x0A, 0x0B, 0x0C, 0x0D, 0x0E};
    bin.swap(newData);

    // After swap, bin should have the newData contents
    EXPECT_EQ(bin.size(), 5u);
    EXPECT_EQ(bin.data()[0], 0x0A);
    EXPECT_EQ(bin.data()[4], 0x0E);

    // The vector should have the old binary data
    EXPECT_EQ(newData.size(), 3u);
    EXPECT_EQ(newData[0], 0x01);
    EXPECT_EQ(newData[2], 0x03);
}

// Test swap with empty vector
TEST_F(BinaryTest_10, SwapWithEmptyVector_10) {
    const unsigned char data[] = {0x01, 0x02};
    YAML::Binary bin(data, sizeof(data));

    std::vector<unsigned char> emptyVec;
    bin.swap(emptyVec);

    EXPECT_EQ(bin.size(), 0u);
    EXPECT_EQ(emptyVec.size(), 2u);
    EXPECT_EQ(emptyVec[0], 0x01);
    EXPECT_EQ(emptyVec[1], 0x02);
}

// Test swap from empty Binary to non-empty vector
TEST_F(BinaryTest_10, SwapEmptyBinaryWithNonEmptyVector_10) {
    YAML::Binary bin;
    std::vector<unsigned char> vec = {0xAA, 0xBB};
    bin.swap(vec);

    EXPECT_EQ(bin.size(), 2u);
    EXPECT_EQ(bin.data()[0], 0xAA);
    EXPECT_EQ(vec.size(), 0u);
}

// Test single byte Binary
TEST_F(BinaryTest_10, SingleByteBinary_10) {
    const unsigned char data[] = {0x42};
    YAML::Binary bin(data, 1);
    EXPECT_EQ(bin.size(), 1u);
    EXPECT_EQ(bin.data()[0], 0x42);
}

// Test equality where first bytes differ
TEST_F(BinaryTest_10, InequalityFirstByteDiffers_10) {
    const unsigned char data1[] = {0x00, 0x02, 0x03};
    const unsigned char data2[] = {0x01, 0x02, 0x03};
    YAML::Binary bin1(data1, 3);
    YAML::Binary bin2(data2, 3);
    EXPECT_FALSE(bin1 == bin2);
    EXPECT_TRUE(bin1 != bin2);
}

// Test equality where last byte differs
TEST_F(BinaryTest_10, InequalityLastByteDiffers_10) {
    const unsigned char data1[] = {0x01, 0x02, 0x03};
    const unsigned char data2[] = {0x01, 0x02, 0x04};
    YAML::Binary bin1(data1, 3);
    YAML::Binary bin2(data2, 3);
    EXPECT_FALSE(bin1 == bin2);
    EXPECT_TRUE(bin1 != bin2);
}

// Test non-empty Binary compared with empty Binary
TEST_F(BinaryTest_10, NonEmptyNotEqualToEmpty_10) {
    const unsigned char data[] = {0x01};
    YAML::Binary bin1(data, 1);
    YAML::Binary bin2;
    EXPECT_FALSE(bin1 == bin2);
    EXPECT_TRUE(bin1 != bin2);
    EXPECT_FALSE(bin2 == bin1);
    EXPECT_TRUE(bin2 != bin1);
}

// Test large Binary
TEST_F(BinaryTest_10, LargeBinaryEquality_10) {
    std::vector<unsigned char> largeData(10000);
    for (std::size_t i = 0; i < largeData.size(); ++i) {
        largeData[i] = static_cast<unsigned char>(i % 256);
    }
    YAML::Binary bin1(largeData.data(), largeData.size());
    YAML::Binary bin2(largeData.data(), largeData.size());
    EXPECT_TRUE(bin1 == bin2);
}

// Test large Binary inequality (single byte difference in middle)
TEST_F(BinaryTest_10, LargeBinaryInequalitySingleByteDiff_10) {
    std::vector<unsigned char> data1(10000, 0x00);
    std::vector<unsigned char> data2(10000, 0x00);
    data2[5000] = 0x01;

    YAML::Binary bin1(data1.data(), data1.size());
    YAML::Binary bin2(data2.data(), data2.size());
    EXPECT_FALSE(bin1 == bin2);
    EXPECT_TRUE(bin1 != bin2);
}

// Test owned() for default constructed Binary
TEST_F(BinaryTest_10, DefaultConstructedIsOwned_10) {
    YAML::Binary bin;
    // Default constructed with nullptr should behave consistently
    // We just verify owned() is callable and returns a bool
    bool isOwned = bin.owned();
    // Default constructed might be unowned (nullptr, 0) per the known interface
    (void)isOwned;
}

// Test owned() for Binary constructed with data
TEST_F(BinaryTest_10, ConstructedWithDataOwnership_10) {
    const unsigned char data[] = {0x01, 0x02};
    YAML::Binary bin(data, sizeof(data));
    // The binary should report its ownership status
    bool isOwned = bin.owned();
    (void)isOwned;
    // Regardless of ownership, data should be accessible
    EXPECT_EQ(bin.size(), 2u);
    EXPECT_NE(bin.data(), nullptr);
}

// Test all zero bytes
TEST_F(BinaryTest_10, AllZeroBytesEquality_10) {
    const unsigned char data1[] = {0x00, 0x00, 0x00};
    const unsigned char data2[] = {0x00, 0x00, 0x00};
    YAML::Binary bin1(data1, 3);
    YAML::Binary bin2(data2, 3);
    EXPECT_TRUE(bin1 == bin2);
}

// Test all 0xFF bytes
TEST_F(BinaryTest_10, AllMaxBytesEquality_10) {
    const unsigned char data1[] = {0xFF, 0xFF, 0xFF};
    const unsigned char data2[] = {0xFF, 0xFF, 0xFF};
    YAML::Binary bin1(data1, 3);
    YAML::Binary bin2(data2, 3);
    EXPECT_TRUE(bin1 == bin2);
}

// Test symmetry of equality
TEST_F(BinaryTest_10, EqualityIsSymmetric_10) {
    const unsigned char data1[] = {0x01, 0x02};
    const unsigned char data2[] = {0x01, 0x02};
    YAML::Binary bin1(data1, 2);
    YAML::Binary bin2(data2, 2);
    EXPECT_EQ(bin1 == bin2, bin2 == bin1);
}

// Test symmetry of inequality
TEST_F(BinaryTest_10, InequalityIsSymmetric_10) {
    const unsigned char data1[] = {0x01, 0x02};
    const unsigned char data2[] = {0x03, 0x04};
    YAML::Binary bin1(data1, 2);
    YAML::Binary bin2(data2, 2);
    EXPECT_EQ(bin1 != bin2, bin2 != bin1);
}

// Test != is negation of ==
TEST_F(BinaryTest_10, NotEqualIsNegationOfEqual_10) {
    const unsigned char data1[] = {0x01, 0x02, 0x03};
    const unsigned char data2[] = {0x01, 0x02, 0x03};
    YAML::Binary bin1(data1, 3);
    YAML::Binary bin2(data2, 3);
    EXPECT_EQ(bin1 != bin2, !(bin1 == bin2));
}

// Test != is negation of == when not equal
TEST_F(BinaryTest_10, NotEqualIsNegationOfEqualWhenDifferent_10) {
    const unsigned char data1[] = {0x01};
    const unsigned char data2[] = {0x02};
    YAML::Binary bin1(data1, 1);
    YAML::Binary bin2(data2, 1);
    EXPECT_EQ(bin1 != bin2, !(bin1 == bin2));
}

// Test swap then check ownership
TEST_F(BinaryTest_10, AfterSwapBinaryOwnsData_10) {
    YAML::Binary bin;
    std::vector<unsigned char> vec = {0x01, 0x02, 0x03};
    bin.swap(vec);
    EXPECT_EQ(bin.size(), 3u);
    EXPECT_EQ(bin.data()[0], 0x01);
    // After swapping with a vector, binary should own the data
    EXPECT_TRUE(bin.owned());
}
