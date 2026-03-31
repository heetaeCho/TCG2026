#include <gtest/gtest.h>
#include "yaml-cpp/binary.h"
#include <vector>
#include <cstring>

// Test default constructor
TEST(BinaryTest_7, DefaultConstructor_7) {
    YAML::Binary binary;
    EXPECT_EQ(binary.size(), 0u);
    EXPECT_EQ(binary.data(), nullptr);
}

// Test constructor with data and size
TEST(BinaryTest_7, ConstructorWithData_7) {
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    YAML::Binary binary(data, 5);
    EXPECT_EQ(binary.size(), 5u);
    EXPECT_NE(binary.data(), nullptr);
}

// Test constructor with nullptr and zero size
TEST(BinaryTest_7, ConstructorWithNullptrAndZeroSize_7) {
    YAML::Binary binary(nullptr, 0);
    EXPECT_EQ(binary.size(), 0u);
}

// Test size returns correct value for non-empty binary
TEST(BinaryTest_7, SizeReturnsCorrectValue_7) {
    const unsigned char data[] = {0xAA, 0xBB, 0xCC};
    YAML::Binary binary(data, 3);
    EXPECT_EQ(binary.size(), 3u);
}

// Test data returns pointer to the data
TEST(BinaryTest_7, DataReturnsPointer_7) {
    const unsigned char data[] = {0x10, 0x20, 0x30};
    YAML::Binary binary(data, 3);
    const unsigned char* ptr = binary.data();
    EXPECT_NE(ptr, nullptr);
}

// Test data content matches input
TEST(BinaryTest_7, DataContentMatchesInput_7) {
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
    YAML::Binary binary(data, 4);
    const unsigned char* result = binary.data();
    ASSERT_NE(result, nullptr);
    for (std::size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(result[i], data[i]);
    }
}

// Test copy constructor
TEST(BinaryTest_7, CopyConstructor_7) {
    const unsigned char data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    YAML::Binary original(data, 4);
    YAML::Binary copy(original);
    EXPECT_EQ(copy.size(), original.size());
    ASSERT_NE(copy.data(), nullptr);
    for (std::size_t i = 0; i < copy.size(); ++i) {
        EXPECT_EQ(copy.data()[i], original.data()[i]);
    }
}

// Test move constructor
TEST(BinaryTest_7, MoveConstructor_7) {
    const unsigned char data[] = {0x01, 0x02, 0x03};
    YAML::Binary original(data, 3);
    std::size_t originalSize = original.size();
    YAML::Binary moved(std::move(original));
    EXPECT_EQ(moved.size(), originalSize);
}

// Test copy assignment
TEST(BinaryTest_7, CopyAssignment_7) {
    const unsigned char data1[] = {0x01, 0x02};
    const unsigned char data2[] = {0x03, 0x04, 0x05};
    YAML::Binary b1(data1, 2);
    YAML::Binary b2(data2, 3);
    b1 = b2;
    EXPECT_EQ(b1.size(), 3u);
    for (std::size_t i = 0; i < b1.size(); ++i) {
        EXPECT_EQ(b1.data()[i], b2.data()[i]);
    }
}

// Test move assignment
TEST(BinaryTest_7, MoveAssignment_7) {
    const unsigned char data1[] = {0x01};
    const unsigned char data2[] = {0x02, 0x03, 0x04, 0x05};
    YAML::Binary b1(data1, 1);
    YAML::Binary b2(data2, 4);
    b1 = std::move(b2);
    EXPECT_EQ(b1.size(), 4u);
}

// Test equality operator for equal binaries
TEST(BinaryTest_7, EqualityOperatorEqual_7) {
    const unsigned char data[] = {0x01, 0x02, 0x03};
    YAML::Binary b1(data, 3);
    YAML::Binary b2(data, 3);
    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 != b2);
}

// Test equality operator for different binaries
TEST(BinaryTest_7, EqualityOperatorNotEqual_7) {
    const unsigned char data1[] = {0x01, 0x02, 0x03};
    const unsigned char data2[] = {0x04, 0x05, 0x06};
    YAML::Binary b1(data1, 3);
    YAML::Binary b2(data2, 3);
    EXPECT_FALSE(b1 == b2);
    EXPECT_TRUE(b1 != b2);
}

// Test equality operator for different sizes
TEST(BinaryTest_7, EqualityOperatorDifferentSizes_7) {
    const unsigned char data1[] = {0x01, 0x02};
    const unsigned char data2[] = {0x01, 0x02, 0x03};
    YAML::Binary b1(data1, 2);
    YAML::Binary b2(data2, 3);
    EXPECT_FALSE(b1 == b2);
    EXPECT_TRUE(b1 != b2);
}

// Test equality of two default-constructed binaries
TEST(BinaryTest_7, EqualityOfDefaultConstructed_7) {
    YAML::Binary b1;
    YAML::Binary b2;
    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 != b2);
}

// Test swap functionality
TEST(BinaryTest_7, SwapWithVector_7) {
    const unsigned char data[] = {0x01, 0x02, 0x03};
    YAML::Binary binary(data, 3);
    std::vector<unsigned char> vec = {0xAA, 0xBB};
    binary.swap(vec);
    // After swap, binary should have the vector's old data
    EXPECT_EQ(binary.size(), 2u);
    EXPECT_EQ(binary.data()[0], 0xAA);
    EXPECT_EQ(binary.data()[1], 0xBB);
    // The vector should have the binary's old data
    EXPECT_EQ(vec.size(), 3u);
    EXPECT_EQ(vec[0], 0x01);
    EXPECT_EQ(vec[1], 0x02);
    EXPECT_EQ(vec[2], 0x03);
}

// Test swap with empty vector
TEST(BinaryTest_7, SwapWithEmptyVector_7) {
    const unsigned char data[] = {0x01, 0x02};
    YAML::Binary binary(data, 2);
    std::vector<unsigned char> emptyVec;
    binary.swap(emptyVec);
    EXPECT_EQ(binary.size(), 0u);
    EXPECT_EQ(emptyVec.size(), 2u);
}

// Test owned() for constructed with data
TEST(BinaryTest_7, OwnedAfterConstruction_7) {
    const unsigned char data[] = {0x01};
    YAML::Binary binary(data, 1);
    // After swap, binary should be owned
    std::vector<unsigned char> vec = {0x01};
    YAML::Binary binary2(data, 1);
    binary2.swap(vec);
    EXPECT_TRUE(binary2.owned());
}

// Test with single byte data
TEST(BinaryTest_7, SingleByteData_7) {
    const unsigned char data[] = {0xFF};
    YAML::Binary binary(data, 1);
    EXPECT_EQ(binary.size(), 1u);
    EXPECT_EQ(binary.data()[0], 0xFF);
}

// Test with large data
TEST(BinaryTest_7, LargeData_7) {
    std::vector<unsigned char> largeData(10000, 0x42);
    YAML::Binary binary(largeData.data(), largeData.size());
    EXPECT_EQ(binary.size(), 10000u);
    ASSERT_NE(binary.data(), nullptr);
    for (std::size_t i = 0; i < 10000; ++i) {
        EXPECT_EQ(binary.data()[i], 0x42);
    }
}

// Test data with zero bytes embedded
TEST(BinaryTest_7, DataWithZeroBytes_7) {
    const unsigned char data[] = {0x00, 0x00, 0x00};
    YAML::Binary binary(data, 3);
    EXPECT_EQ(binary.size(), 3u);
    for (std::size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(binary.data()[i], 0x00);
    }
}

// Test self-equality
TEST(BinaryTest_7, SelfEquality_7) {
    const unsigned char data[] = {0x01, 0x02};
    YAML::Binary binary(data, 2);
    EXPECT_TRUE(binary == binary);
    EXPECT_FALSE(binary != binary);
}

// Test swap makes binary owned
TEST(BinaryTest_7, SwapMakesBinaryOwned_7) {
    const unsigned char data[] = {0x01, 0x02, 0x03};
    YAML::Binary binary(data, 3);
    std::vector<unsigned char> vec = {0x0A, 0x0B};
    binary.swap(vec);
    EXPECT_TRUE(binary.owned());
}

// Test inequality operator is consistent with equality
TEST(BinaryTest_7, InequalityConsistentWithEquality_7) {
    const unsigned char data1[] = {0x01};
    const unsigned char data2[] = {0x02};
    YAML::Binary b1(data1, 1);
    YAML::Binary b2(data2, 1);
    EXPECT_EQ(b1 == b2, !(b1 != b2));
}

// Test default constructed then swapped with data
TEST(BinaryTest_7, DefaultThenSwap_7) {
    YAML::Binary binary;
    std::vector<unsigned char> vec = {0x01, 0x02, 0x03, 0x04};
    binary.swap(vec);
    EXPECT_EQ(binary.size(), 4u);
    EXPECT_TRUE(binary.owned());
    EXPECT_EQ(vec.size(), 0u);
}
