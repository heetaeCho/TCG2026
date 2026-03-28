#include <gtest/gtest.h>

#include "exiv2/slice.hpp"



namespace Exiv2 {

    // Mock class to simulate a container

    template<typename T>

    struct MockContainer {

        std::vector<T> data;

        MockContainer(std::initializer_list<T> init) : data(init) {}

        const T* data() const { return data.data(); }

        size_t size() const { return data.size(); }

    };

}



using namespace Exiv2;



class SliceTest_17 : public ::testing::Test {

protected:

    MockContainer<int> mock_container_{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    Slice<MockContainer<int>> slice_;

    

    SliceTest_17() : slice_(mock_container_.data(), 0, mock_container_.size()) {}

};



TEST_F(SliceTest_17, SubSliceValidRange_17) {

    auto sub_slice = slice_.subSlice(2, 5);

    EXPECT_EQ(sub_slice.size(), 3U);

    for (size_t i = 0; i < 3; ++i) {

        EXPECT_EQ(sub_slice.data()[i], mock_container_.data()[i + 2]);

    }

}



TEST_F(SliceTest_17, SubSliceFullRange_17) {

    auto sub_slice = slice_.subSlice(0, slice_.size());

    EXPECT_EQ(sub_slice.size(), slice_.size());

    for (size_t i = 0; i < slice_.size(); ++i) {

        EXPECT_EQ(sub_slice.data()[i], mock_container_.data()[i]);

    }

}



TEST_F(SliceTest_17, SubSliceSingleElement_17) {

    auto sub_slice = slice_.subSlice(5, 6);

    EXPECT_EQ(sub_slice.size(), 1U);

    EXPECT_EQ(sub_slice.data()[0], mock_container_.data()[5]);

}



TEST_F(SliceTest_17, SubSliceEmptyRange_17) {

    auto sub_slice = slice_.subSlice(3, 3);

    EXPECT_EQ(sub_slice.size(), 0U);

}



TEST_F(SliceTest_17, SubSliceBoundaryStart_17) {

    auto sub_slice = slice_.subSlice(0, 2);

    EXPECT_EQ(sub_slice.size(), 2U);

    for (size_t i = 0; i < 2; ++i) {

        EXPECT_EQ(sub_slice.data()[i], mock_container_.data()[i]);

    }

}



TEST_F(SliceTest_17, SubSliceBoundaryEnd_17) {

    auto sub_slice = slice_.subSlice(slice_.size() - 2, slice_.size());

    EXPECT_EQ(sub_slice.size(), 2U);

    for (size_t i = 0; i < 2; ++i) {

        EXPECT_EQ(sub_slice.data()[i], mock_container_.data()[slice_.size() - 2 + i]);

    }

}



TEST_F(SliceTest_17, SubSliceInvalidRangeEndBeforeStart_17) {

    auto sub_slice = slice_.subSlice(5, 3);

    EXPECT_EQ(sub_slice.size(), 0U);

}



TEST_F(SliceTest_17, SubSliceInvalidRangeEndOutOfBounds_17) {

    auto sub_slice = slice_.subSlice(5, slice_.size() + 2);

    EXPECT_EQ(sub_slice.size(), slice_.size() - 5);

    for (size_t i = 0; i < slice_.size() - 5; ++i) {

        EXPECT_EQ(sub_slice.data()[i], mock_container_.data()[5 + i]);

    }

}



TEST_F(SliceTest_17, SubSliceInvalidRangeStartOutOfBounds_17) {

    auto sub_slice = slice_.subSlice(slice_.size() + 2, slice_.size() + 3);

    EXPECT_EQ(sub_slice.size(), 0U);

}
