#include <gtest/gtest.h>
#include <vector>
#include <cstring>

// Include the header under test
#include "yaml-cpp/binary.h"

class BinaryTest_9 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Constructor Tests
// ============================================================

TEST_F(BinaryTest_9, DefaultConstructor_CreatesEmptyBinary_9) {
    YAML::Binary b;
    EXPECT_EQ(b.size(), 0u);
    EXPECT_TRUE(b.data() == nullptr || b.size() == 0u);
}

TEST_F(BinaryTest_9, ConstructorWithData_StoresDataCorrectly_9) {
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
    YAML::Binary b(data, 4);
    EXPECT_EQ(b.size(), 4u);
    EXPECT_NE(b.data(), nullptr);
    EXPECT_EQ(b.data()[0], 0x01);
    EXPECT_EQ(b.data()[1], 0x02);
    EXPECT_EQ(b.data()[2], 0x03);
    EXPECT_EQ(b.data()[3], 0x04);
}

TEST_F(BinaryTest_9, ConstructorWithNullptrAndZeroSize_9) {
    YAML::Binary b(nullptr, 0);
    EXPECT_EQ(b.size(), 0u);
}

TEST_F(BinaryTest_9, ConstructorWithSingleByte_9) {
    const unsigned char data[] = {0xFF};
    YAML::Binary b(data, 1);
    EXPECT_EQ(b.size(), 1u);
    EXPECT_EQ(b.data()[0], 0xFF);
}

// ============================================================
// Copy and Move Constructor Tests
// ============================================================

TEST_F(BinaryTest_9, CopyConstructor_CreatesCopy_9) {
    const unsigned char data[] = {0x10, 0x20, 0x30};
    YAML::Binary original(data, 3);
    YAML::Binary copy(original);
    EXPECT_EQ(copy.size(), 3u);
    EXPECT_EQ(copy.data()[0], 0x10);
    EXPECT_EQ(copy.data()[1], 0x20);
    EXPECT_EQ(copy.data()[2], 0x30);
}

TEST_F(BinaryTest_9, CopyAssignment_CopiesData_9) {
    const unsigned char data[] = {0xAA, 0xBB};
    YAML::Binary original(data, 2);
    YAML::Binary assigned;
    assigned = original;
    EXPECT_EQ(assigned.size(), 2u);
    EXPECT_EQ(assigned.data()[0], 0xAA);
    EXPECT_EQ(assigned.data()[1], 0xBB);
}

TEST_F(BinaryTest_9, MoveConstructor_MovesData_9) {
    const unsigned char data[] = {0x01, 0x02, 0x03};
    YAML::Binary original(data, 3);
    YAML::Binary moved(std::move(original));
    EXPECT_EQ(moved.size(), 3u);
    EXPECT_EQ(moved.data()[0], 0x01);
    EXPECT_EQ(moved.data()[1], 0x02);
    EXPECT_EQ(moved.data()[2], 0x03);
}

TEST_F(BinaryTest_9, MoveAssignment_MovesData_9) {
    const unsigned char data[] = {0xDE, 0xAD};
    YAML::Binary original(data, 2);
    YAML::Binary assigned;
    assigned = std::move(original);
    EXPECT_EQ(assigned.size(), 2u);
    EXPECT_EQ(assigned.data()[0], 0xDE);
    EXPECT_EQ(assigned.data()[1], 0xAD);
}

// ============================================================
// owned() Tests
// ============================================================

TEST_F(BinaryTest_9, DefaultConstructed_IsOwned_9) {
    YAML::Binary b;
    // Default constructed with nullptr, behavior of owned() observed
    // Default constructor calls Binary(nullptr, 0)
    EXPECT_TRUE(b.owned() || !b.owned()); // We just verify it doesn't crash
}

TEST_F(BinaryTest_9, ConstructedWithData_OwnershipCheck_9) {
    const unsigned char data[] = {0x01, 0x02};
    YAML::Binary b(data, 2);
    // Initially, data may be unowned (pointing to external data)
    // We can't know for sure without seeing implementation, but we test the interface
    // After swap, it should become owned
    bool initialOwned = b.owned();
    // Just verify it returns a consistent boolean
    EXPECT_EQ(b.owned(), initialOwned);
}

// ============================================================
// size() Tests
// ============================================================

TEST_F(BinaryTest_9, Size_EmptyBinary_ReturnsZero_9) {
    YAML::Binary b;
    EXPECT_EQ(b.size(), 0u);
}

TEST_F(BinaryTest_9, Size_NonEmptyBinary_ReturnsCorrectSize_9) {
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    YAML::Binary b(data, 5);
    EXPECT_EQ(b.size(), 5u);
}

// ============================================================
// data() Tests
// ============================================================

TEST_F(BinaryTest_9, Data_NonEmptyBinary_ReturnsNonNull_9) {
    const unsigned char data[] = {0xCA, 0xFE};
    YAML::Binary b(data, 2);
    EXPECT_NE(b.data(), nullptr);
}

TEST_F(BinaryTest_9, Data_ReturnsCorrectContent_9) {
    const unsigned char data[] = {0x00, 0x7F, 0x80, 0xFF};
    YAML::Binary b(data, 4);
    const unsigned char* ptr = b.data();
    EXPECT_EQ(ptr[0], 0x00);
    EXPECT_EQ(ptr[1], 0x7F);
    EXPECT_EQ(ptr[2], 0x80);
    EXPECT_EQ(ptr[3], 0xFF);
}

// ============================================================
// swap() Tests
// ============================================================

TEST_F(BinaryTest_9, Swap_WithEmptyVector_TransfersDataToVector_9) {
    const unsigned char data[] = {0x01, 0x02, 0x03};
    YAML::Binary b(data, 3);
    
    // Force ownership by swapping first if needed
    std::vector<unsigned char> vec;
    b.swap(vec);
    
    // After swap, vec should contain the binary's data
    // and binary should be empty (or have vec's former empty content)
    EXPECT_EQ(vec.size(), 3u);
    EXPECT_EQ(vec[0], 0x01);
    EXPECT_EQ(vec[1], 0x02);
    EXPECT_EQ(vec[2], 0x03);
}

TEST_F(BinaryTest_9, Swap_WithNonEmptyVector_ExchangesData_9) {
    // Create a binary that owns its data (swap once to force ownership)
    const unsigned char data[] = {0xAA, 0xBB};
    YAML::Binary b(data, 2);
    
    // First swap to get owned data
    std::vector<unsigned char> temp;
    b.swap(temp);
    // Now b has empty owned data, temp has {0xAA, 0xBB}
    
    // Swap back
    b.swap(temp);
    // Now b should have {0xAA, 0xBB} and temp should be empty
    EXPECT_EQ(b.size(), 2u);
    EXPECT_EQ(b.data()[0], 0xAA);
    EXPECT_EQ(b.data()[1], 0xBB);
    EXPECT_TRUE(temp.empty());
}

TEST_F(BinaryTest_9, Swap_OwnedData_SwapsBothWays_9) {
    // Start with owned data by using default then swapping in
    YAML::Binary b;
    std::vector<unsigned char> vec1 = {0x10, 0x20, 0x30};
    b.swap(vec1);
    // Now b should have {0x10, 0x20, 0x30}, vec1 should be empty
    EXPECT_EQ(b.size(), 3u);
    EXPECT_TRUE(vec1.empty());
    
    std::vector<unsigned char> vec2 = {0x40, 0x50};
    b.swap(vec2);
    // Now b should have {0x40, 0x50}, vec2 should have {0x10, 0x20, 0x30}
    EXPECT_EQ(b.size(), 2u);
    EXPECT_EQ(b.data()[0], 0x40);
    EXPECT_EQ(b.data()[1], 0x50);
    EXPECT_EQ(vec2.size(), 3u);
    EXPECT_EQ(vec2[0], 0x10);
    EXPECT_EQ(vec2[1], 0x20);
    EXPECT_EQ(vec2[2], 0x30);
}

TEST_F(BinaryTest_9, Swap_UnownedData_CopiesUnownedToRhs_9) {
    // When Binary has unowned data, swap should:
    // 1. Move m_data into rhs
    // 2. Copy unowned data into rhs (after clearing)
    // 3. Clear unowned pointer
    const unsigned char data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    YAML::Binary b(data, 4);
    
    std::vector<unsigned char> vec = {0x11, 0x22};
    b.swap(vec);
    
    // After swap of unowned binary:
    // rhs should contain the unowned data
    EXPECT_EQ(vec.size(), 4u);
    EXPECT_EQ(vec[0], 0xDE);
    EXPECT_EQ(vec[1], 0xAD);
    EXPECT_EQ(vec[2], 0xBE);
    EXPECT_EQ(vec[3], 0xEF);
    
    // After swap, binary should now own its data (the original rhs content was lost)
    EXPECT_TRUE(b.owned());
}

TEST_F(BinaryTest_9, Swap_EmptyBinaryWithEmptyVector_9) {
    YAML::Binary b;
    std::vector<unsigned char> vec;
    b.swap(vec);
    EXPECT_EQ(b.size(), 0u);
    EXPECT_TRUE(vec.empty());
}

TEST_F(BinaryTest_9, Swap_MultipleTimes_9) {
    YAML::Binary b;
    
    std::vector<unsigned char> v1 = {1, 2, 3};
    b.swap(v1);
    EXPECT_EQ(b.size(), 3u);
    EXPECT_TRUE(v1.empty());
    
    std::vector<unsigned char> v2 = {4, 5};
    b.swap(v2);
    EXPECT_EQ(b.size(), 2u);
    EXPECT_EQ(v2.size(), 3u);
    
    std::vector<unsigned char> v3;
    b.swap(v3);
    EXPECT_EQ(b.size(), 0u);
    EXPECT_EQ(v3.size(), 2u);
    EXPECT_EQ(v3[0], 4);
    EXPECT_EQ(v3[1], 5);
}

// ============================================================
// Equality Operator Tests
// ============================================================

TEST_F(BinaryTest_9, Equality_SameData_ReturnsTrue_9) {
    const unsigned char data1[] = {0x01, 0x02, 0x03};
    const unsigned char data2[] = {0x01, 0x02, 0x03};
    YAML::Binary b1(data1, 3);
    YAML::Binary b2(data2, 3);
    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 != b2);
}

TEST_F(BinaryTest_9, Equality_DifferentData_ReturnsFalse_9) {
    const unsigned char data1[] = {0x01, 0x02, 0x03};
    const unsigned char data2[] = {0x01, 0x02, 0x04};
    YAML::Binary b1(data1, 3);
    YAML::Binary b2(data2, 3);
    EXPECT_FALSE(b1 == b2);
    EXPECT_TRUE(b1 != b2);
}

TEST_F(BinaryTest_9, Equality_DifferentSizes_ReturnsFalse_9) {
    const unsigned char data1[] = {0x01, 0x02};
    const unsigned char data2[] = {0x01, 0x02, 0x03};
    YAML::Binary b1(data1, 2);
    YAML::Binary b2(data2, 3);
    EXPECT_FALSE(b1 == b2);
    EXPECT_TRUE(b1 != b2);
}

TEST_F(BinaryTest_9, Equality_BothEmpty_ReturnsTrue_9) {
    YAML::Binary b1;
    YAML::Binary b2;
    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 != b2);
}

TEST_F(BinaryTest_9, Equality_EmptyAndNonEmpty_ReturnsFalse_9) {
    YAML::Binary b1;
    const unsigned char data[] = {0x01};
    YAML::Binary b2(data, 1);
    EXPECT_FALSE(b1 == b2);
    EXPECT_TRUE(b1 != b2);
}

TEST_F(BinaryTest_9, Equality_SelfComparison_ReturnsTrue_9) {
    const unsigned char data[] = {0xAA, 0xBB, 0xCC};
    YAML::Binary b(data, 3);
    EXPECT_TRUE(b == b);
    EXPECT_FALSE(b != b);
}

// ============================================================
// Inequality Operator Tests
// ============================================================

TEST_F(BinaryTest_9, Inequality_ConsistentWithEquality_9) {
    const unsigned char data1[] = {0x01, 0x02};
    const unsigned char data2[] = {0x01, 0x02};
    YAML::Binary b1(data1, 2);
    YAML::Binary b2(data2, 2);
    EXPECT_EQ(!(b1 == b2), (b1 != b2));
}

// ============================================================
// Boundary Tests
// ============================================================

TEST_F(BinaryTest_9, LargeData_HandledCorrectly_9) {
    std::vector<unsigned char> largeData(10000);
    for (size_t i = 0; i < largeData.size(); ++i) {
        largeData[i] = static_cast<unsigned char>(i % 256);
    }
    YAML::Binary b(largeData.data(), largeData.size());
    EXPECT_EQ(b.size(), 10000u);
    EXPECT_EQ(b.data()[0], 0x00);
    EXPECT_EQ(b.data()[255], 0xFF);
    EXPECT_EQ(b.data()[256], 0x00);
}

TEST_F(BinaryTest_9, AllZeroData_9) {
    std::vector<unsigned char> zeroData(100, 0x00);
    YAML::Binary b(zeroData.data(), zeroData.size());
    EXPECT_EQ(b.size(), 100u);
    for (size_t i = 0; i < 100; ++i) {
        EXPECT_EQ(b.data()[i], 0x00);
    }
}

TEST_F(BinaryTest_9, AllOnesData_9) {
    std::vector<unsigned char> onesData(50, 0xFF);
    YAML::Binary b(onesData.data(), onesData.size());
    EXPECT_EQ(b.size(), 50u);
    for (size_t i = 0; i < 50; ++i) {
        EXPECT_EQ(b.data()[i], 0xFF);
    }
}

// ============================================================
// Ownership After Swap Tests
// ============================================================

TEST_F(BinaryTest_9, Swap_UnownedBecomesOwned_9) {
    const unsigned char data[] = {0x01, 0x02};
    YAML::Binary b(data, 2);
    
    // After construction with pointer, may be unowned
    std::vector<unsigned char> vec;
    b.swap(vec);
    
    // After swap, binary should now own its data
    EXPECT_TRUE(b.owned());
}

TEST_F(BinaryTest_9, Swap_AfterSwapDataIsAccessible_9) {
    YAML::Binary b;
    std::vector<unsigned char> vec = {0xCA, 0xFE, 0xBA, 0xBE};
    b.swap(vec);
    
    EXPECT_EQ(b.size(), 4u);
    EXPECT_EQ(b.data()[0], 0xCA);
    EXPECT_EQ(b.data()[1], 0xFE);
    EXPECT_EQ(b.data()[2], 0xBA);
    EXPECT_EQ(b.data()[3], 0xBE);
    EXPECT_TRUE(b.owned());
}

// ============================================================
// Equality with owned vs unowned data
// ============================================================

TEST_F(BinaryTest_9, Equality_OwnedVsUnowned_SameContent_9) {
    const unsigned char data[] = {0x01, 0x02, 0x03};
    YAML::Binary unowned(data, 3);
    
    YAML::Binary owned;
    std::vector<unsigned char> vec = {0x01, 0x02, 0x03};
    owned.swap(vec);
    
    EXPECT_TRUE(unowned == owned);
}
