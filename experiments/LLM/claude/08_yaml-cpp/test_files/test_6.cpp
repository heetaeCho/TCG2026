#include <gtest/gtest.h>
#include "yaml-cpp/binary.h"
#include <vector>
#include <cstring>

// Test default constructor
TEST(BinaryTest_6, DefaultConstructor_6) {
    YAML::Binary b;
    EXPECT_EQ(b.size(), 0u);
    EXPECT_TRUE(b.owned());
}

// Test constructor with data and size
TEST(BinaryTest_6, ConstructorWithData_6) {
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
    YAML::Binary b(data, sizeof(data));
    EXPECT_EQ(b.size(), sizeof(data));
    EXPECT_NE(b.data(), nullptr);
}

// Test constructor with nullptr and zero size
TEST(BinaryTest_6, ConstructorWithNullptrAndZeroSize_6) {
    YAML::Binary b(nullptr, 0);
    EXPECT_EQ(b.size(), 0u);
    EXPECT_TRUE(b.owned());
}

// Test owned() returns true for default-constructed Binary
TEST(BinaryTest_6, OwnedForDefaultConstructed_6) {
    YAML::Binary b;
    EXPECT_TRUE(b.owned());
}

// Test owned() for Binary constructed with data
TEST(BinaryTest_6, OwnedForDataConstructed_6) {
    const unsigned char data[] = {0xAA, 0xBB};
    YAML::Binary b(data, sizeof(data));
    // After construction with data, the binary should have copied the data
    // and owned() should reflect the internal state
    // Based on the interface, we just check it doesn't crash
    bool ownedResult = b.owned();
    (void)ownedResult;
}

// Test size() returns correct size
TEST(BinaryTest_6, SizeReturnsCorrectValue_6) {
    const unsigned char data[] = {0x10, 0x20, 0x30};
    YAML::Binary b(data, 3);
    EXPECT_EQ(b.size(), 3u);
}

// Test data() returns non-null for non-empty binary
TEST(BinaryTest_6, DataReturnsNonNullForNonEmpty_6) {
    const unsigned char data[] = {0xFF};
    YAML::Binary b(data, 1);
    EXPECT_NE(b.data(), nullptr);
}

// Test data content matches input
TEST(BinaryTest_6, DataContentMatchesInput_6) {
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    YAML::Binary b(data, sizeof(data));
    const unsigned char* result = b.data();
    ASSERT_NE(result, nullptr);
    for (std::size_t i = 0; i < sizeof(data); ++i) {
        EXPECT_EQ(result[i], data[i]) << "Mismatch at index " << i;
    }
}

// Test copy constructor
TEST(BinaryTest_6, CopyConstructor_6) {
    const unsigned char data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    YAML::Binary original(data, sizeof(data));
    YAML::Binary copy(original);
    EXPECT_EQ(copy.size(), original.size());
    ASSERT_NE(copy.data(), nullptr);
    EXPECT_EQ(std::memcmp(copy.data(), original.data(), original.size()), 0);
}

// Test move constructor
TEST(BinaryTest_6, MoveConstructor_6) {
    const unsigned char data[] = {0xCA, 0xFE};
    YAML::Binary original(data, sizeof(data));
    std::size_t origSize = original.size();
    YAML::Binary moved(std::move(original));
    EXPECT_EQ(moved.size(), origSize);
}

// Test copy assignment
TEST(BinaryTest_6, CopyAssignment_6) {
    const unsigned char data1[] = {0x01, 0x02};
    const unsigned char data2[] = {0x03, 0x04, 0x05};
    YAML::Binary b1(data1, sizeof(data1));
    YAML::Binary b2(data2, sizeof(data2));
    b1 = b2;
    EXPECT_EQ(b1.size(), b2.size());
    ASSERT_NE(b1.data(), nullptr);
    EXPECT_EQ(std::memcmp(b1.data(), b2.data(), b2.size()), 0);
}

// Test move assignment
TEST(BinaryTest_6, MoveAssignment_6) {
    const unsigned char data[] = {0xAB, 0xCD};
    YAML::Binary b1;
    YAML::Binary b2(data, sizeof(data));
    b1 = std::move(b2);
    EXPECT_EQ(b1.size(), sizeof(data));
}

// Test equality operator for equal binaries
TEST(BinaryTest_6, EqualityOperatorEqual_6) {
    const unsigned char data[] = {0x01, 0x02, 0x03};
    YAML::Binary b1(data, sizeof(data));
    YAML::Binary b2(data, sizeof(data));
    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 != b2);
}

// Test equality operator for unequal binaries (different data)
TEST(BinaryTest_6, EqualityOperatorDifferentData_6) {
    const unsigned char data1[] = {0x01, 0x02, 0x03};
    const unsigned char data2[] = {0x04, 0x05, 0x06};
    YAML::Binary b1(data1, sizeof(data1));
    YAML::Binary b2(data2, sizeof(data2));
    EXPECT_FALSE(b1 == b2);
    EXPECT_TRUE(b1 != b2);
}

// Test equality operator for unequal binaries (different sizes)
TEST(BinaryTest_6, EqualityOperatorDifferentSizes_6) {
    const unsigned char data1[] = {0x01, 0x02};
    const unsigned char data2[] = {0x01, 0x02, 0x03};
    YAML::Binary b1(data1, sizeof(data1));
    YAML::Binary b2(data2, sizeof(data2));
    EXPECT_FALSE(b1 == b2);
    EXPECT_TRUE(b1 != b2);
}

// Test equality of two default-constructed (empty) binaries
TEST(BinaryTest_6, EqualityOfEmptyBinaries_6) {
    YAML::Binary b1;
    YAML::Binary b2;
    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 != b2);
}

// Test swap with a vector
TEST(BinaryTest_6, SwapWithVector_6) {
    const unsigned char data[] = {0x10, 0x20, 0x30};
    YAML::Binary b(data, sizeof(data));
    
    std::vector<unsigned char> vec = {0xAA, 0xBB};
    b.swap(vec);
    
    // After swap, b should contain the vector's old data
    EXPECT_EQ(b.size(), 2u);
    ASSERT_NE(b.data(), nullptr);
    EXPECT_EQ(b.data()[0], 0xAA);
    EXPECT_EQ(b.data()[1], 0xBB);
    
    // The vector should contain b's old data
    EXPECT_EQ(vec.size(), 3u);
    EXPECT_EQ(vec[0], 0x10);
    EXPECT_EQ(vec[1], 0x20);
    EXPECT_EQ(vec[2], 0x30);
}

// Test swap with empty vector
TEST(BinaryTest_6, SwapWithEmptyVector_6) {
    const unsigned char data[] = {0x01};
    YAML::Binary b(data, sizeof(data));
    
    std::vector<unsigned char> emptyVec;
    b.swap(emptyVec);
    
    EXPECT_EQ(b.size(), 0u);
    EXPECT_EQ(emptyVec.size(), 1u);
    EXPECT_EQ(emptyVec[0], 0x01);
}

// Test swap on default-constructed Binary with a non-empty vector
TEST(BinaryTest_6, SwapDefaultBinaryWithNonEmptyVector_6) {
    YAML::Binary b;
    std::vector<unsigned char> vec = {0x55, 0x66, 0x77};
    b.swap(vec);
    
    EXPECT_EQ(b.size(), 3u);
    EXPECT_TRUE(vec.empty());
}

// Test owned() after swap
TEST(BinaryTest_6, OwnedAfterSwap_6) {
    YAML::Binary b;
    std::vector<unsigned char> vec = {0x01, 0x02};
    b.swap(vec);
    EXPECT_TRUE(b.owned());
}

// Test with large data
TEST(BinaryTest_6, LargeData_6) {
    std::vector<unsigned char> largeData(10000, 0x42);
    YAML::Binary b(largeData.data(), largeData.size());
    EXPECT_EQ(b.size(), 10000u);
    ASSERT_NE(b.data(), nullptr);
    for (std::size_t i = 0; i < b.size(); ++i) {
        EXPECT_EQ(b.data()[i], 0x42) << "Mismatch at index " << i;
    }
}

// Test single byte data
TEST(BinaryTest_6, SingleByteData_6) {
    const unsigned char data[] = {0x00};
    YAML::Binary b(data, 1);
    EXPECT_EQ(b.size(), 1u);
    EXPECT_EQ(b.data()[0], 0x00);
}

// Test self-equality
TEST(BinaryTest_6, SelfEquality_6) {
    const unsigned char data[] = {0x01, 0x02};
    YAML::Binary b(data, sizeof(data));
    EXPECT_TRUE(b == b);
    EXPECT_FALSE(b != b);
}

// Test data with all zeros
TEST(BinaryTest_6, AllZerosData_6) {
    const unsigned char data[] = {0x00, 0x00, 0x00, 0x00};
    YAML::Binary b(data, sizeof(data));
    EXPECT_EQ(b.size(), 4u);
    for (std::size_t i = 0; i < b.size(); ++i) {
        EXPECT_EQ(b.data()[i], 0x00);
    }
}

// Test data with all 0xFF
TEST(BinaryTest_6, AllOnesData_6) {
    const unsigned char data[] = {0xFF, 0xFF, 0xFF};
    YAML::Binary b(data, sizeof(data));
    EXPECT_EQ(b.size(), 3u);
    for (std::size_t i = 0; i < b.size(); ++i) {
        EXPECT_EQ(b.data()[i], 0xFF);
    }
}

// Test inequality operator is consistent with equality
TEST(BinaryTest_6, InequalityConsistentWithEquality_6) {
    const unsigned char data[] = {0x01};
    YAML::Binary b1(data, sizeof(data));
    YAML::Binary b2(data, sizeof(data));
    EXPECT_EQ((b1 == b2), !(b1 != b2));
    
    const unsigned char data2[] = {0x02};
    YAML::Binary b3(data2, sizeof(data2));
    EXPECT_EQ((b1 == b3), !(b1 != b3));
}
