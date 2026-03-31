#include <gtest/gtest.h>
#include "yaml-cpp/binary.h"
#include <vector>
#include <cstring>

// Test default constructor
TEST(BinaryTest_8, DefaultConstructor_8) {
    YAML::Binary binary;
    EXPECT_EQ(binary.size(), 0u);
    EXPECT_EQ(binary.data(), nullptr);
}

// Test constructor with data and size
TEST(BinaryTest_8, ConstructorWithData_8) {
    const unsigned char raw[] = {0x01, 0x02, 0x03, 0x04};
    YAML::Binary binary(raw, sizeof(raw));
    EXPECT_EQ(binary.size(), sizeof(raw));
    EXPECT_NE(binary.data(), nullptr);
}

// Test that data content is correct after construction
TEST(BinaryTest_8, DataContentAfterConstruction_8) {
    const unsigned char raw[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE};
    YAML::Binary binary(raw, sizeof(raw));
    EXPECT_EQ(binary.size(), 5u);
    for (std::size_t i = 0; i < sizeof(raw); ++i) {
        EXPECT_EQ(binary.data()[i], raw[i]);
    }
}

// Test constructor with nullptr and zero size
TEST(BinaryTest_8, ConstructorWithNullptrAndZeroSize_8) {
    YAML::Binary binary(nullptr, 0);
    EXPECT_EQ(binary.size(), 0u);
}

// Test copy constructor
TEST(BinaryTest_8, CopyConstructor_8) {
    const unsigned char raw[] = {0x10, 0x20, 0x30};
    YAML::Binary original(raw, sizeof(raw));
    YAML::Binary copy(original);
    EXPECT_EQ(copy.size(), original.size());
    for (std::size_t i = 0; i < copy.size(); ++i) {
        EXPECT_EQ(copy.data()[i], original.data()[i]);
    }
}

// Test move constructor
TEST(BinaryTest_8, MoveConstructor_8) {
    const unsigned char raw[] = {0x10, 0x20, 0x30};
    YAML::Binary original(raw, sizeof(raw));
    std::size_t origSize = original.size();
    YAML::Binary moved(std::move(original));
    EXPECT_EQ(moved.size(), origSize);
    EXPECT_EQ(moved.data()[0], 0x10);
    EXPECT_EQ(moved.data()[1], 0x20);
    EXPECT_EQ(moved.data()[2], 0x30);
}

// Test copy assignment
TEST(BinaryTest_8, CopyAssignment_8) {
    const unsigned char raw1[] = {0x01, 0x02};
    const unsigned char raw2[] = {0x03, 0x04, 0x05};
    YAML::Binary b1(raw1, sizeof(raw1));
    YAML::Binary b2(raw2, sizeof(raw2));
    b1 = b2;
    EXPECT_EQ(b1.size(), b2.size());
    for (std::size_t i = 0; i < b1.size(); ++i) {
        EXPECT_EQ(b1.data()[i], b2.data()[i]);
    }
}

// Test move assignment
TEST(BinaryTest_8, MoveAssignment_8) {
    const unsigned char raw1[] = {0x01};
    const unsigned char raw2[] = {0xAA, 0xBB, 0xCC};
    YAML::Binary b1(raw1, sizeof(raw1));
    YAML::Binary b2(raw2, sizeof(raw2));
    b1 = std::move(b2);
    EXPECT_EQ(b1.size(), 3u);
    EXPECT_EQ(b1.data()[0], 0xAA);
    EXPECT_EQ(b1.data()[1], 0xBB);
    EXPECT_EQ(b1.data()[2], 0xCC);
}

// Test equality operator with equal binaries
TEST(BinaryTest_8, EqualityOperatorEqual_8) {
    const unsigned char raw[] = {0x01, 0x02, 0x03};
    YAML::Binary b1(raw, sizeof(raw));
    YAML::Binary b2(raw, sizeof(raw));
    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 != b2);
}

// Test equality operator with different binaries
TEST(BinaryTest_8, EqualityOperatorNotEqual_8) {
    const unsigned char raw1[] = {0x01, 0x02, 0x03};
    const unsigned char raw2[] = {0x04, 0x05, 0x06};
    YAML::Binary b1(raw1, sizeof(raw1));
    YAML::Binary b2(raw2, sizeof(raw2));
    EXPECT_FALSE(b1 == b2);
    EXPECT_TRUE(b1 != b2);
}

// Test equality operator with different sizes
TEST(BinaryTest_8, EqualityOperatorDifferentSizes_8) {
    const unsigned char raw1[] = {0x01, 0x02};
    const unsigned char raw2[] = {0x01, 0x02, 0x03};
    YAML::Binary b1(raw1, sizeof(raw1));
    YAML::Binary b2(raw2, sizeof(raw2));
    EXPECT_FALSE(b1 == b2);
    EXPECT_TRUE(b1 != b2);
}

// Test equality of two default-constructed binaries
TEST(BinaryTest_8, EqualityDefaultConstructed_8) {
    YAML::Binary b1;
    YAML::Binary b2;
    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 != b2);
}

// Test swap functionality
TEST(BinaryTest_8, SwapWithVector_8) {
    const unsigned char raw[] = {0x01, 0x02, 0x03};
    YAML::Binary binary(raw, sizeof(raw));

    std::vector<unsigned char> vec = {0xAA, 0xBB};
    binary.swap(vec);

    // After swap, binary should have the vector's data
    EXPECT_EQ(binary.size(), 2u);
    EXPECT_EQ(binary.data()[0], 0xAA);
    EXPECT_EQ(binary.data()[1], 0xBB);

    // The vector should have the binary's original data
    EXPECT_EQ(vec.size(), 3u);
    EXPECT_EQ(vec[0], 0x01);
    EXPECT_EQ(vec[1], 0x02);
    EXPECT_EQ(vec[2], 0x03);
}

// Test swap with empty vector
TEST(BinaryTest_8, SwapWithEmptyVector_8) {
    const unsigned char raw[] = {0x01, 0x02};
    YAML::Binary binary(raw, sizeof(raw));

    std::vector<unsigned char> emptyVec;
    binary.swap(emptyVec);

    EXPECT_EQ(binary.size(), 0u);
    EXPECT_EQ(emptyVec.size(), 2u);
    EXPECT_EQ(emptyVec[0], 0x01);
    EXPECT_EQ(emptyVec[1], 0x02);
}

// Test owned() returns true after construction with data
TEST(BinaryTest_8, OwnedAfterConstruction_8) {
    const unsigned char raw[] = {0x01, 0x02, 0x03};
    YAML::Binary binary(raw, sizeof(raw));
    EXPECT_TRUE(binary.owned());
}

// Test owned() for default constructed binary
TEST(BinaryTest_8, OwnedDefaultConstructed_8) {
    YAML::Binary binary;
    // Default constructed with nullptr, behavior depends on implementation
    // but we can at least call it without crashing
    bool isOwned = binary.owned();
    (void)isOwned; // just verify it doesn't crash
}

// Test single byte binary
TEST(BinaryTest_8, SingleByte_8) {
    const unsigned char raw[] = {0xFF};
    YAML::Binary binary(raw, 1);
    EXPECT_EQ(binary.size(), 1u);
    EXPECT_EQ(binary.data()[0], 0xFF);
}

// Test large binary data
TEST(BinaryTest_8, LargeBinaryData_8) {
    const std::size_t largeSize = 10000;
    std::vector<unsigned char> largeData(largeSize);
    for (std::size_t i = 0; i < largeSize; ++i) {
        largeData[i] = static_cast<unsigned char>(i % 256);
    }
    YAML::Binary binary(largeData.data(), largeData.size());
    EXPECT_EQ(binary.size(), largeSize);
    for (std::size_t i = 0; i < largeSize; ++i) {
        EXPECT_EQ(binary.data()[i], static_cast<unsigned char>(i % 256));
    }
}

// Test that after swap, binary becomes owned
TEST(BinaryTest_8, SwapMakesBinaryOwned_8) {
    YAML::Binary binary;
    std::vector<unsigned char> vec = {0x01, 0x02, 0x03};
    binary.swap(vec);
    EXPECT_TRUE(binary.owned());
    EXPECT_EQ(binary.size(), 3u);
}

// Test self-equality
TEST(BinaryTest_8, SelfEquality_8) {
    const unsigned char raw[] = {0x01, 0x02, 0x03};
    YAML::Binary binary(raw, sizeof(raw));
    EXPECT_TRUE(binary == binary);
    EXPECT_FALSE(binary != binary);
}

// Test binary with all zeros
TEST(BinaryTest_8, AllZeroData_8) {
    const unsigned char raw[] = {0x00, 0x00, 0x00, 0x00};
    YAML::Binary binary(raw, sizeof(raw));
    EXPECT_EQ(binary.size(), 4u);
    for (std::size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(binary.data()[i], 0x00);
    }
}

// Test binary with all 0xFF
TEST(BinaryTest_8, AllMaxData_8) {
    const unsigned char raw[] = {0xFF, 0xFF, 0xFF, 0xFF};
    YAML::Binary binary(raw, sizeof(raw));
    EXPECT_EQ(binary.size(), 4u);
    for (std::size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(binary.data()[i], 0xFF);
    }
}
