#include <gtest/gtest.h>

#include "exiv2/slice.hpp"

#include <vector>



using namespace Exiv2::Internal;



class MutableSliceBaseTest_8 : public ::testing::Test {

protected:

    using StorageType = std::vector<int>;

    using DataType = int;

    MutableSliceBase<StorageType, DataType> slice;



    void SetUp() override {

        StorageType storage = {10, 20, 30, 40, 50};

        slice = MutableSliceBase<StorageType, DataType>(std::move(storage));

    }

};



TEST_F(MutableSliceBaseTest_8, BeginReturnsValidIterator_8) {

    auto it = slice.begin();

    EXPECT_EQ(*it, 10);

}



TEST_F(MutableSliceBaseTest_8, EndPointsPastLastElement_8) {

    auto it = slice.end();

    EXPECT_TRUE(it == slice.begin() + 5);

}



TEST_F(MutableSliceBaseTest_8, AtAccessesCorrectElement_8) {

    EXPECT_EQ(slice.at(2), 30);

    EXPECT_EQ(slice.at(4), 50);

}



TEST_F(MutableSliceBaseTest_8, AtThrowsForOutOfRangeIndex_8) {

    EXPECT_THROW(slice.at(5), std::out_of_range);

    EXPECT_THROW(slice.at(-1), std::out_of_range);

}
