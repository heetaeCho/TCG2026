#include <gtest/gtest.h>
#include "exiv2/slice.hpp"
#include <vector>
#include <array>
#include <string>

// Test fixture for Slice tests with raw pointers
class SliceTest_18 : public ::testing::Test {
protected:
    void SetUp() override {
        for (int i = 0; i < 10; ++i) {
            data[i] = i * 10;
        }
    }

    int data[10];
};

// Test fixture for Slice tests with const raw pointers
class ConstPtrSliceTest_18 : public ::testing::Test {
protected:
    void SetUp() override {
        for (int i = 0; i < 10; ++i) {
            data[i] = i * 10;
        }
    }

    int data[10];
};

// Test fixture for Slice tests with std::vector
class VectorSliceTest_18 : public ::testing::Test {
protected:
    void SetUp() override {
        vec = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
    }

    std::vector<int> vec;
};

// ==================== Const Pointer Slice Tests ====================

TEST_F(ConstPtrSliceTest_18, ConstructConstPtrSlice_18) {
    const int* cptr = data;
    Exiv2::Slice<const int*> slice(cptr, 0, 10);
    EXPECT_EQ(slice.size(), 10u);
}

TEST_F(ConstPtrSliceTest_18, ConstPtrSliceAccessElements_18) {
    const int* cptr = data;
    Exiv2::Slice<const int*> slice(cptr, 0, 10);
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(slice.at(i), static_cast<int>(i * 10));
    }
}

TEST_F(ConstPtrSliceTest_18, ConstPtrSliceSubSlice_18) {
    const int* cptr = data;
    Exiv2::Slice<const int*> slice(cptr, 0, 10);
    Exiv2::Slice<const int*> sub = slice.subSlice(2, 5);
    EXPECT_EQ(sub.size(), 3u);
    EXPECT_EQ(sub.at(0), 20);
    EXPECT_EQ(sub.at(1), 30);
    EXPECT_EQ(sub.at(2), 40);
}

TEST_F(ConstPtrSliceTest_18, ConstPtrSliceSubSliceOfSubSlice_18) {
    const int* cptr = data;
    Exiv2::Slice<const int*> slice(cptr, 0, 10);
    Exiv2::Slice<const int*> sub1 = slice.subSlice(2, 8);
    Exiv2::Slice<const int*> sub2 = sub1.subSlice(1, 4);
    EXPECT_EQ(sub2.size(), 3u);
    EXPECT_EQ(sub2.at(0), 30);
    EXPECT_EQ(sub2.at(1), 40);
    EXPECT_EQ(sub2.at(2), 50);
}

TEST_F(ConstPtrSliceTest_18, ConstPtrSliceSubSliceEmptyRange_18) {
    const int* cptr = data;
    Exiv2::Slice<const int*> slice(cptr, 0, 10);
    Exiv2::Slice<const int*> sub = slice.subSlice(3, 3);
    EXPECT_EQ(sub.size(), 0u);
}

TEST_F(ConstPtrSliceTest_18, ConstPtrSliceSubSliceFullRange_18) {
    const int* cptr = data;
    Exiv2::Slice<const int*> slice(cptr, 0, 10);
    Exiv2::Slice<const int*> sub = slice.subSlice(0, 10);
    EXPECT_EQ(sub.size(), 10u);
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(sub.at(i), static_cast<int>(i * 10));
    }
}

TEST_F(ConstPtrSliceTest_18, ConstPtrSliceSubSliceInvalidRange_18) {
    const int* cptr = data;
    Exiv2::Slice<const int*> slice(cptr, 0, 10);
    EXPECT_THROW(slice.subSlice(5, 3), std::out_of_range);
}

TEST_F(ConstPtrSliceTest_18, ConstPtrSliceSubSliceOutOfBounds_18) {
    const int* cptr = data;
    Exiv2::Slice<const int*> slice(cptr, 0, 10);
    EXPECT_THROW(slice.subSlice(0, 11), std::out_of_range);
}

TEST_F(ConstPtrSliceTest_18, ConstPtrSliceAtOutOfBounds_18) {
    const int* cptr = data;
    Exiv2::Slice<const int*> slice(cptr, 0, 5);
    EXPECT_THROW(slice.at(5), std::out_of_range);
}

TEST_F(ConstPtrSliceTest_18, ConstPtrSliceWithOffset_18) {
    const int* cptr = data;
    Exiv2::Slice<const int*> slice(cptr, 3, 7);
    EXPECT_EQ(slice.size(), 4u);
    EXPECT_EQ(slice.at(0), 30);
    EXPECT_EQ(slice.at(3), 60);
}

TEST_F(ConstPtrSliceTest_18, ConstPtrSliceWithOffsetSubSlice_18) {
    const int* cptr = data;
    Exiv2::Slice<const int*> slice(cptr, 3, 7);
    Exiv2::Slice<const int*> sub = slice.subSlice(1, 3);
    EXPECT_EQ(sub.size(), 2u);
    EXPECT_EQ(sub.at(0), 40);
    EXPECT_EQ(sub.at(1), 50);
}

// ==================== Mutable Pointer Slice Tests ====================

TEST_F(SliceTest_18, ConstructMutablePtrSlice_18) {
    Exiv2::Slice<int*> slice(data, 0, 10);
    EXPECT_EQ(slice.size(), 10u);
}

TEST_F(SliceTest_18, MutablePtrSliceAccessElements_18) {
    Exiv2::Slice<int*> slice(data, 0, 10);
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(slice.at(i), static_cast<int>(i * 10));
    }
}

TEST_F(SliceTest_18, MutablePtrSliceModifyElements_18) {
    Exiv2::Slice<int*> slice(data, 0, 10);
    slice.at(3) = 999;
    EXPECT_EQ(data[3], 999);
    EXPECT_EQ(slice.at(3), 999);
}

TEST_F(SliceTest_18, MutablePtrSliceSubSliceMutable_18) {
    Exiv2::Slice<int*> slice(data, 0, 10);
    Exiv2::Slice<int*> sub = slice.subSlice(2, 5);
    EXPECT_EQ(sub.size(), 3u);
    sub.at(0) = 111;
    EXPECT_EQ(data[2], 111);
}

TEST_F(SliceTest_18, MutablePtrSliceConstSubSlice_18) {
    Exiv2::Slice<int*> slice(data, 0, 10);
    const Exiv2::Slice<int*>& constRef = slice;
    // Taking a const subslice from a const reference
    Exiv2::Slice<const int*> sub = constRef.subSlice(2, 5);
    EXPECT_EQ(sub.size(), 3u);
    EXPECT_EQ(sub.at(0), 20);
    EXPECT_EQ(sub.at(1), 30);
    EXPECT_EQ(sub.at(2), 40);
}

TEST_F(SliceTest_18, MutablePtrSliceAtOutOfBounds_18) {
    Exiv2::Slice<int*> slice(data, 0, 5);
    EXPECT_THROW(slice.at(5), std::out_of_range);
}

TEST_F(SliceTest_18, MutablePtrSliceSubSliceInvalidRange_18) {
    Exiv2::Slice<int*> slice(data, 0, 10);
    EXPECT_THROW(slice.subSlice(7, 3), std::out_of_range);
}

TEST_F(SliceTest_18, MutablePtrSliceSubSliceOutOfBounds_18) {
    Exiv2::Slice<int*> slice(data, 0, 10);
    EXPECT_THROW(slice.subSlice(0, 11), std::out_of_range);
}

// ==================== Vector Slice Tests ====================

TEST_F(VectorSliceTest_18, ConstructVectorSlice_18) {
    Exiv2::Slice<std::vector<int>> slice(vec, 0, 10);
    EXPECT_EQ(slice.size(), 10u);
}

TEST_F(VectorSliceTest_18, VectorSliceAccessElements_18) {
    Exiv2::Slice<std::vector<int>> slice(vec, 0, 10);
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(slice.at(i), static_cast<int>(i * 10));
    }
}

TEST_F(VectorSliceTest_18, VectorSliceModifyElements_18) {
    Exiv2::Slice<std::vector<int>> slice(vec, 0, 10);
    slice.at(5) = 555;
    EXPECT_EQ(vec[5], 555);
}

TEST_F(VectorSliceTest_18, VectorSliceSubSlice_18) {
    Exiv2::Slice<std::vector<int>> slice(vec, 0, 10);
    auto sub = slice.subSlice(2, 6);
    EXPECT_EQ(sub.size(), 4u);
    EXPECT_EQ(sub.at(0), 20);
    EXPECT_EQ(sub.at(3), 50);
}

TEST_F(VectorSliceTest_18, VectorSliceConstSubSlice_18) {
    Exiv2::Slice<std::vector<int>> slice(vec, 0, 10);
    const auto& constSlice = slice;
    auto sub = constSlice.subSlice(1, 4);
    EXPECT_EQ(sub.size(), 3u);
    EXPECT_EQ(sub.at(0), 10);
    EXPECT_EQ(sub.at(1), 20);
    EXPECT_EQ(sub.at(2), 30);
}

TEST_F(VectorSliceTest_18, VectorSliceSubSliceEmpty_18) {
    Exiv2::Slice<std::vector<int>> slice(vec, 0, 10);
    auto sub = slice.subSlice(5, 5);
    EXPECT_EQ(sub.size(), 0u);
}

TEST_F(VectorSliceTest_18, VectorSliceSubSliceOutOfBounds_18) {
    Exiv2::Slice<std::vector<int>> slice(vec, 0, 10);
    EXPECT_THROW(slice.subSlice(0, 11), std::out_of_range);
}

TEST_F(VectorSliceTest_18, VectorSliceSubSliceInvalidRange_18) {
    Exiv2::Slice<std::vector<int>> slice(vec, 0, 10);
    EXPECT_THROW(slice.subSlice(6, 2), std::out_of_range);
}

TEST_F(VectorSliceTest_18, VectorSliceAtOutOfBounds_18) {
    Exiv2::Slice<std::vector<int>> slice(vec, 0, 5);
    EXPECT_THROW(slice.at(5), std::out_of_range);
}

TEST_F(VectorSliceTest_18, VectorSliceWithOffset_18) {
    Exiv2::Slice<std::vector<int>> slice(vec, 3, 8);
    EXPECT_EQ(slice.size(), 5u);
    EXPECT_EQ(slice.at(0), 30);
    EXPECT_EQ(slice.at(4), 70);
}

TEST_F(VectorSliceTest_18, VectorSliceConstructionOutOfBounds_18) {
    EXPECT_THROW(Exiv2::Slice<std::vector<int>>(vec, 0, 11), std::out_of_range);
}

TEST_F(VectorSliceTest_18, VectorSliceConstructionInvalidRange_18) {
    EXPECT_THROW(Exiv2::Slice<std::vector<int>>(vec, 5, 2), std::out_of_range);
}

// ==================== Edge Case Tests ====================

TEST_F(ConstPtrSliceTest_18, EmptySliceConstPtr_18) {
    const int* cptr = data;
    Exiv2::Slice<const int*> slice(cptr, 0, 0);
    EXPECT_EQ(slice.size(), 0u);
    EXPECT_THROW(slice.at(0), std::out_of_range);
}

TEST_F(SliceTest_18, EmptySliceMutablePtr_18) {
    Exiv2::Slice<int*> slice(data, 0, 0);
    EXPECT_EQ(slice.size(), 0u);
    EXPECT_THROW(slice.at(0), std::out_of_range);
}

TEST_F(SliceTest_18, SingleElementSlice_18) {
    Exiv2::Slice<int*> slice(data, 4, 5);
    EXPECT_EQ(slice.size(), 1u);
    EXPECT_EQ(slice.at(0), 40);
    EXPECT_THROW(slice.at(1), std::out_of_range);
}

TEST_F(ConstPtrSliceTest_18, SingleElementConstSlice_18) {
    const int* cptr = data;
    Exiv2::Slice<const int*> slice(cptr, 9, 10);
    EXPECT_EQ(slice.size(), 1u);
    EXPECT_EQ(slice.at(0), 90);
}

TEST_F(ConstPtrSliceTest_18, SubSliceSingleElement_18) {
    const int* cptr = data;
    Exiv2::Slice<const int*> slice(cptr, 0, 10);
    Exiv2::Slice<const int*> sub = slice.subSlice(5, 6);
    EXPECT_EQ(sub.size(), 1u);
    EXPECT_EQ(sub.at(0), 50);
}

// ==================== Nested SubSlice Tests ====================

TEST_F(SliceTest_18, NestedSubSliceMutable_18) {
    Exiv2::Slice<int*> slice(data, 0, 10);
    auto sub1 = slice.subSlice(1, 9);
    auto sub2 = sub1.subSlice(1, 6);
    auto sub3 = sub2.subSlice(1, 4);
    EXPECT_EQ(sub3.size(), 3u);
    EXPECT_EQ(sub3.at(0), 30);
    EXPECT_EQ(sub3.at(1), 40);
    EXPECT_EQ(sub3.at(2), 50);
}

TEST_F(ConstPtrSliceTest_18, NestedSubSliceConst_18) {
    const int* cptr = data;
    Exiv2::Slice<const int*> slice(cptr, 0, 10);
    auto sub1 = slice.subSlice(1, 9);
    auto sub2 = sub1.subSlice(1, 6);
    auto sub3 = sub2.subSlice(1, 4);
    EXPECT_EQ(sub3.size(), 3u);
    EXPECT_EQ(sub3.at(0), 30);
    EXPECT_EQ(sub3.at(1), 40);
    EXPECT_EQ(sub3.at(2), 50);
}

// ==================== Construction Error Tests ====================

TEST_F(ConstPtrSliceTest_18, ConstPtrSliceConstructionInvalidRange_18) {
    const int* cptr = data;
    EXPECT_THROW(Exiv2::Slice<const int*>(cptr, 5, 2), std::out_of_range);
}

TEST_F(SliceTest_18, MutablePtrSliceConstructionInvalidRange_18) {
    EXPECT_THROW(Exiv2::Slice<int*>(data, 5, 2), std::out_of_range);
}

// ==================== Iterator Tests (if available) ====================

TEST_F(SliceTest_18, MutablePtrSliceIteratorBeginEnd_18) {
    Exiv2::Slice<int*> slice(data, 0, 5);
    auto it = slice.begin();
    EXPECT_EQ(*it, 0);
    ++it;
    EXPECT_EQ(*it, 10);
}

TEST_F(ConstPtrSliceTest_18, ConstPtrSliceIteratorBeginEnd_18) {
    const int* cptr = data;
    Exiv2::Slice<const int*> slice(cptr, 0, 5);
    auto it = slice.begin();
    EXPECT_EQ(*it, 0);
    ++it;
    EXPECT_EQ(*it, 10);
}

// ==================== SubSlice boundary at end ====================

TEST_F(ConstPtrSliceTest_18, SubSliceAtEnd_18) {
    const int* cptr = data;
    Exiv2::Slice<const int*> slice(cptr, 0, 10);
    Exiv2::Slice<const int*> sub = slice.subSlice(8, 10);
    EXPECT_EQ(sub.size(), 2u);
    EXPECT_EQ(sub.at(0), 80);
    EXPECT_EQ(sub.at(1), 90);
}

TEST_F(ConstPtrSliceTest_18, SubSliceAtBeginning_18) {
    const int* cptr = data;
    Exiv2::Slice<const int*> slice(cptr, 0, 10);
    Exiv2::Slice<const int*> sub = slice.subSlice(0, 2);
    EXPECT_EQ(sub.size(), 2u);
    EXPECT_EQ(sub.at(0), 0);
    EXPECT_EQ(sub.at(1), 10);
}

// ==================== Data types other than int ====================

TEST(SliceCharTest_18, ConstCharPtrSlice_18) {
    const char str[] = "Hello World";
    Exiv2::Slice<const char*> slice(str, 0, 11);
    EXPECT_EQ(slice.size(), 11u);
    EXPECT_EQ(slice.at(0), 'H');
    EXPECT_EQ(slice.at(5), ' ');
    EXPECT_EQ(slice.at(6), 'W');
}

TEST(SliceCharTest_18, ConstCharPtrSubSlice_18) {
    const char str[] = "Hello World";
    Exiv2::Slice<const char*> slice(str, 0, 11);
    Exiv2::Slice<const char*> sub = slice.subSlice(6, 11);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub.at(0), 'W');
    EXPECT_EQ(sub.at(4), 'd');
}

TEST(SliceUnsignedCharTest_18, UnsignedCharPtrSlice_18) {
    unsigned char data[] = {0x00, 0x01, 0x02, 0xFF, 0xFE};
    Exiv2::Slice<unsigned char*> slice(data, 0, 5);
    EXPECT_EQ(slice.size(), 5u);
    EXPECT_EQ(slice.at(0), 0x00);
    EXPECT_EQ(slice.at(3), 0xFF);
    EXPECT_EQ(slice.at(4), 0xFE);
}

TEST(SliceUnsignedCharTest_18, UnsignedCharPtrConstSubSlice_18) {
    unsigned char data[] = {0x00, 0x01, 0x02, 0xFF, 0xFE};
    Exiv2::Slice<unsigned char*> slice(data, 0, 5);
    const auto& constSlice = slice;
    auto sub = constSlice.subSlice(1, 4);
    EXPECT_EQ(sub.size(), 3u);
    EXPECT_EQ(sub.at(0), 0x01);
    EXPECT_EQ(sub.at(2), 0xFF);
}
