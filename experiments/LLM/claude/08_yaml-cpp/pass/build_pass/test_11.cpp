#include <gtest/gtest.h>
#include "yaml-cpp/binary.h"
#include <vector>
#include <cstring>

class BinaryTest_11 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction
TEST_F(BinaryTest_11, DefaultConstructor_11) {
    YAML::Binary bin;
    EXPECT_EQ(bin.size(), 0u);
    EXPECT_EQ(bin.data(), nullptr);
}

// Test construction with data and size
TEST_F(BinaryTest_11, ConstructorWithData_11) {
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
    YAML::Binary bin(data, sizeof(data));
    EXPECT_EQ(bin.size(), 4u);
    EXPECT_NE(bin.data(), nullptr);
}

// Test that data contents are preserved after construction
TEST_F(BinaryTest_11, DataContentsPreserved_11) {
    const unsigned char data[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE};
    YAML::Binary bin(data, sizeof(data));
    EXPECT_EQ(bin.size(), sizeof(data));
    const unsigned char *result = bin.data();
    ASSERT_NE(result, nullptr);
    for (std::size_t i = 0; i < sizeof(data); ++i) {
        EXPECT_EQ(result[i], data[i]);
    }
}

// Test construction with nullptr and zero size
TEST_F(BinaryTest_11, ConstructorWithNullptrZeroSize_11) {
    YAML::Binary bin(nullptr, 0);
    EXPECT_EQ(bin.size(), 0u);
}

// Test equality of two default-constructed Binary objects
TEST_F(BinaryTest_11, DefaultObjectsAreEqual_11) {
    YAML::Binary bin1;
    YAML::Binary bin2;
    EXPECT_TRUE(bin1 == bin2);
    EXPECT_FALSE(bin1 != bin2);
}

// Test equality of two Binary objects with same data
TEST_F(BinaryTest_11, EqualDataAreEqual_11) {
    const unsigned char data[] = {0x01, 0x02, 0x03};
    YAML::Binary bin1(data, sizeof(data));
    YAML::Binary bin2(data, sizeof(data));
    EXPECT_TRUE(bin1 == bin2);
    EXPECT_FALSE(bin1 != bin2);
}

// Test inequality of two Binary objects with different data
TEST_F(BinaryTest_11, DifferentDataAreNotEqual_11) {
    const unsigned char data1[] = {0x01, 0x02, 0x03};
    const unsigned char data2[] = {0x04, 0x05, 0x06};
    YAML::Binary bin1(data1, sizeof(data1));
    YAML::Binary bin2(data2, sizeof(data2));
    EXPECT_FALSE(bin1 == bin2);
    EXPECT_TRUE(bin1 != bin2);
}

// Test inequality of two Binary objects with different sizes
TEST_F(BinaryTest_11, DifferentSizesAreNotEqual_11) {
    const unsigned char data1[] = {0x01, 0x02, 0x03};
    const unsigned char data2[] = {0x01, 0x02};
    YAML::Binary bin1(data1, sizeof(data1));
    YAML::Binary bin2(data2, sizeof(data2));
    EXPECT_FALSE(bin1 == bin2);
    EXPECT_TRUE(bin1 != bin2);
}

// Test copy constructor
TEST_F(BinaryTest_11, CopyConstructor_11) {
    const unsigned char data[] = {0x10, 0x20, 0x30};
    YAML::Binary bin1(data, sizeof(data));
    YAML::Binary bin2(bin1);
    EXPECT_EQ(bin1, bin2);
    EXPECT_EQ(bin2.size(), sizeof(data));
}

// Test copy assignment
TEST_F(BinaryTest_11, CopyAssignment_11) {
    const unsigned char data[] = {0x10, 0x20, 0x30};
    YAML::Binary bin1(data, sizeof(data));
    YAML::Binary bin2;
    bin2 = bin1;
    EXPECT_EQ(bin1, bin2);
    EXPECT_EQ(bin2.size(), sizeof(data));
}

// Test move constructor
TEST_F(BinaryTest_11, MoveConstructor_11) {
    const unsigned char data[] = {0x10, 0x20, 0x30};
    YAML::Binary bin1(data, sizeof(data));
    YAML::Binary bin2(std::move(bin1));
    EXPECT_EQ(bin2.size(), sizeof(data));
    const unsigned char *result = bin2.data();
    ASSERT_NE(result, nullptr);
    for (std::size_t i = 0; i < sizeof(data); ++i) {
        EXPECT_EQ(result[i], data[i]);
    }
}

// Test move assignment
TEST_F(BinaryTest_11, MoveAssignment_11) {
    const unsigned char data[] = {0x10, 0x20, 0x30};
    YAML::Binary bin1(data, sizeof(data));
    YAML::Binary bin2;
    bin2 = std::move(bin1);
    EXPECT_EQ(bin2.size(), sizeof(data));
    const unsigned char *result = bin2.data();
    ASSERT_NE(result, nullptr);
    for (std::size_t i = 0; i < sizeof(data); ++i) {
        EXPECT_EQ(result[i], data[i]);
    }
}

// Test swap functionality
TEST_F(BinaryTest_11, SwapWithVector_11) {
    const unsigned char data[] = {0x01, 0x02, 0x03};
    YAML::Binary bin(data, sizeof(data));

    std::vector<unsigned char> vec = {0xAA, 0xBB};
    bin.swap(vec);

    // After swap, bin should have the vec's data and vec should have bin's old data
    EXPECT_EQ(bin.size(), 2u);
    EXPECT_NE(bin.data(), nullptr);
    EXPECT_EQ(bin.data()[0], 0xAA);
    EXPECT_EQ(bin.data()[1], 0xBB);

    EXPECT_EQ(vec.size(), 3u);
    EXPECT_EQ(vec[0], 0x01);
    EXPECT_EQ(vec[1], 0x02);
    EXPECT_EQ(vec[2], 0x03);
}

// Test swap with empty vector
TEST_F(BinaryTest_11, SwapWithEmptyVector_11) {
    const unsigned char data[] = {0x01, 0x02, 0x03};
    YAML::Binary bin(data, sizeof(data));

    std::vector<unsigned char> vec;
    bin.swap(vec);

    EXPECT_EQ(bin.size(), 0u);
    EXPECT_EQ(vec.size(), 3u);
    EXPECT_EQ(vec[0], 0x01);
    EXPECT_EQ(vec[1], 0x02);
    EXPECT_EQ(vec[2], 0x03);
}

// Test swap on default-constructed binary with non-empty vector
TEST_F(BinaryTest_11, SwapDefaultWithNonEmptyVector_11) {
    YAML::Binary bin;
    std::vector<unsigned char> vec = {0x10, 0x20};
    bin.swap(vec);

    EXPECT_EQ(bin.size(), 2u);
    EXPECT_EQ(bin.data()[0], 0x10);
    EXPECT_EQ(bin.data()[1], 0x20);
    EXPECT_TRUE(vec.empty());
}

// Test owned - Binary constructed with data should be owned after swap or copy
TEST_F(BinaryTest_11, OwnedAfterSwap_11) {
    YAML::Binary bin;
    std::vector<unsigned char> vec = {0x01, 0x02};
    bin.swap(vec);
    EXPECT_TRUE(bin.owned());
}

// Test self-equality
TEST_F(BinaryTest_11, SelfEquality_11) {
    const unsigned char data[] = {0x01, 0x02, 0x03};
    YAML::Binary bin(data, sizeof(data));
    EXPECT_TRUE(bin == bin);
    EXPECT_FALSE(bin != bin);
}

// Test with single byte
TEST_F(BinaryTest_11, SingleByte_11) {
    const unsigned char data[] = {0xFF};
    YAML::Binary bin(data, 1);
    EXPECT_EQ(bin.size(), 1u);
    EXPECT_NE(bin.data(), nullptr);
    EXPECT_EQ(bin.data()[0], 0xFF);
}

// Test with large data
TEST_F(BinaryTest_11, LargeData_11) {
    std::vector<unsigned char> data(10000, 0x42);
    YAML::Binary bin(data.data(), data.size());
    EXPECT_EQ(bin.size(), 10000u);
    for (std::size_t i = 0; i < bin.size(); ++i) {
        EXPECT_EQ(bin.data()[i], 0x42);
    }
}

// Test equality between empty and non-empty
TEST_F(BinaryTest_11, EmptyAndNonEmptyNotEqual_11) {
    YAML::Binary bin1;
    const unsigned char data[] = {0x01};
    YAML::Binary bin2(data, sizeof(data));
    EXPECT_FALSE(bin1 == bin2);
    EXPECT_TRUE(bin1 != bin2);
}

// Test that data with same prefix but different length are not equal
TEST_F(BinaryTest_11, SamePrefixDifferentLength_11) {
    const unsigned char data1[] = {0x01, 0x02, 0x03};
    const unsigned char data2[] = {0x01, 0x02, 0x03, 0x04};
    YAML::Binary bin1(data1, 3);
    YAML::Binary bin2(data2, 4);
    EXPECT_FALSE(bin1 == bin2);
    EXPECT_TRUE(bin1 != bin2);
}

// Test binary data with null bytes
TEST_F(BinaryTest_11, DataWithNullBytes_11) {
    const unsigned char data[] = {0x00, 0x00, 0x00};
    YAML::Binary bin(data, sizeof(data));
    EXPECT_EQ(bin.size(), 3u);
    EXPECT_EQ(bin.data()[0], 0x00);
    EXPECT_EQ(bin.data()[1], 0x00);
    EXPECT_EQ(bin.data()[2], 0x00);
}

// Test that != is consistent with ==
TEST_F(BinaryTest_11, NotEqualConsistentWithEqual_11) {
    const unsigned char data1[] = {0x01, 0x02};
    const unsigned char data2[] = {0x01, 0x02};
    const unsigned char data3[] = {0x03, 0x04};

    YAML::Binary bin1(data1, sizeof(data1));
    YAML::Binary bin2(data2, sizeof(data2));
    YAML::Binary bin3(data3, sizeof(data3));

    // Equal case
    EXPECT_EQ((bin1 == bin2), !(bin1 != bin2));
    // Not equal case
    EXPECT_EQ((bin1 == bin3), !(bin1 != bin3));
}
