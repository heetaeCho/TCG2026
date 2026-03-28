#include <gtest/gtest.h>

#include "exiv2/slice.hpp"



namespace Exiv2 {

    class SliceTest_19 : public ::testing::Test {

    protected:

        using T = int;

        std::vector<T> data = {1, 2, 3, 4, 5};

        Slice<T*> slice;



        void SetUp() override {

            slice = Slice<T*>(data.data(), 0, data.size());

        }

    };



    TEST_F(SliceTest_19, SubSliceValidRange_19) {

        auto sub = slice.subSlice(1, 4);

        EXPECT_EQ(sub.begin(), data.data() + 1);

        EXPECT_EQ(sub.end(), data.data() + 4);

    }



    TEST_F(SliceTest_19, SubSliceFullRange_19) {

        auto sub = slice.subSlice(0, data.size());

        EXPECT_EQ(sub.begin(), data.data());

        EXPECT_EQ(sub.end(), data.data() + data.size());

    }



    TEST_F(SliceTest_19, SubSliceBoundaryStart_19) {

        auto sub = slice.subSlice(0, 1);

        EXPECT_EQ(sub.begin(), data.data());

        EXPECT_EQ(sub.end(), data.data() + 1);

    }



    TEST_F(SliceTest_19, SubSliceBoundaryEnd_19) {

        auto sub = slice.subSlice(data.size() - 1, data.size());

        EXPECT_EQ(sub.begin(), data.data() + data.size() - 1);

        EXPECT_EQ(sub.end(), data.data() + data.size());

    }



    TEST_F(SliceTest_19, SubSliceEmptyRange_19) {

        auto sub = slice.subSlice(2, 2);

        EXPECT_EQ(sub.begin(), data.data() + 2);

        EXPECT_EQ(sub.end(), data.data() + 2);

    }



    TEST_F(SliceTest_19, SubSliceInvalidRangeStartGreaterThanEnd_19) {

        EXPECT_THROW(slice.subSlice(3, 2), std::invalid_argument);

    }



    TEST_F(SliceTest_19, SubSliceInvalidRangeEndGreaterThanSize_19) {

        EXPECT_THROW(slice.subSlice(0, data.size() + 1), std::out_of_range);

    }

}
