#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/slice.hpp"  // Include the relevant header for your slice code

namespace Exiv2 {
namespace Internal {

class SliceTest_4 : public ::testing::Test {
protected:
    // Test setup if needed (e.g., data initialization)
};

TEST_F(SliceTest_4, ConstSliceBase_Constructor_InitializesProperly_4) {
    size_t begin = 10;
    size_t end = 20;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    
    Exiv2::Internal::ConstSliceBase<int> slice(data, begin, end);

    // Validate that the size is correctly initialized
    EXPECT_EQ(slice.size(), end - begin);
}

TEST_F(SliceTest_4, ConstSliceBase_cbegin_IteratesCorrectly_4) {
    size_t begin = 5;
    size_t end = 10;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    Exiv2::Internal::ConstSliceBase<int> slice(data, begin, end);

    auto it = slice.cbegin();
    EXPECT_EQ(*it, data[begin]);
    ++it;
    EXPECT_EQ(*it, data[begin + 1]);
}

TEST_F(SliceTest_4, ConstSliceBase_at_ReturnsCorrectValue_4) {
    size_t begin = 3;
    size_t end = 8;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    Exiv2::Internal::ConstSliceBase<int> slice(data, begin, end);

    // Test accessing values within the range
    EXPECT_EQ(slice.at(0), data[begin]);
    EXPECT_EQ(slice.at(4), data[end - 1]);
}

TEST_F(SliceTest_4, ConstSliceBase_subSlice_ReturnsCorrectSlice_4) {
    size_t begin = 2;
    size_t end = 7;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    Exiv2::Internal::ConstSliceBase<int> slice(data, begin, end);
    auto sub_slice = slice.subSlice<size_t>(3, 6);

    // Validate subSlice is correct
    EXPECT_EQ(sub_slice.size(), 3);
    EXPECT_EQ(sub_slice.at(0), data[begin + 3]);
    EXPECT_EQ(sub_slice.at(2), data[begin + 5]);
}

TEST_F(SliceTest_4, SliceBase_rangeCheck_ThrowsOutOfRange_4) {
    size_t begin = 0;
    size_t end = 5;
    int data[] = {1, 2, 3, 4, 5};

    Exiv2::Internal::ConstSliceBase<int> slice(data, begin, end);
    
    // Boundary test
    EXPECT_THROW(slice.rangeCheck(10), std::out_of_range);
    EXPECT_NO_THROW(slice.rangeCheck(3));  // Valid index
}

}  // namespace Internal
}  // namespace Exiv2