#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/slice.hpp"



using namespace Exiv2::Internal;



class MutableSliceBaseTest_9 : public ::testing::Test {

protected:

    struct TestStorage {

        std::vector<int> data_;

        auto unsafeGetIteratorAt(size_t index) { return data_.begin() + index; }

    };



    using TestMutableSlice = MutableSliceBase<TestStorage, int>;

    TestMutableSlice slice_;



    void SetUp() override {

        slice_.storage_.data_ = {10, 20, 30, 40, 50};

        slice_.end_ = slice_.storage_.data_.size();

    }

};



TEST_F(MutableSliceBaseTest_9, EndReturnsCorrectIterator_9) {

    EXPECT_EQ(slice_.end(), slice_.storage_.unsafeGetIteratorAt(5));

}



TEST_F(MutableSliceBaseTest_9, BeginReturnsCorrectIterator_9) {

    EXPECT_EQ(slice_.begin(), slice_.storage_.unsafeGetIteratorAt(0));

}



TEST_F(MutableSliceBaseTest_9, AtAccessesElementAtIndex_9) {

    EXPECT_EQ(slice_.at(2), 30);

}



TEST_F(MutableSliceBaseTest_9, AtThrowsForOutOfRangeIndex_9) {

    EXPECT_THROW(slice_.at(10), std::out_of_range);

}



// Assuming subSlice is public for testing purposes

TEST_F(MutableSliceBaseTest_9, SubSliceCreatesCorrectSubslice_9) {

    auto subslice = slice_.subSlice<MutableSliceBase<TestStorage, int>>(1, 4);

    EXPECT_EQ(subslice.at(0), 20);

    EXPECT_EQ(subslice.at(1), 30);

    EXPECT_EQ(subslice.at(2), 40);

}



TEST_F(MutableSliceBaseTest_9, SubSliceThrowsForInvalidRange_9) {

    EXPECT_THROW(slice_.subSlice<MutableSliceBase<TestStorage, int>>(3, 2), std::invalid_argument);

}

```


