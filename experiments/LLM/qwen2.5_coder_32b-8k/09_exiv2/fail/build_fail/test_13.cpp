#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/slice.hpp"

#include <vector>



using namespace Exiv2::Internal;



class ContainerStorageTest : public ::testing::Test {

protected:

    std::vector<int> data;

    ContainerStorage<std::vector<int>> storage;



    ContainerStorageTest() 

        : data{1, 2, 3, 4, 5},

          storage(data, 0, data.size()) {}

};



TEST_F(ContainerStorageTest_13, GetIteratorAtValidIndex_13) {

    auto it = storage.unsafeGetIteratorAt(2);

    EXPECT_EQ(*it, 3);

}



TEST_F(ContainerStorageTest_13, GetIteratorAtZeroIndex_13) {

    auto it = storage.unsafeGetIteratorAt(0);

    EXPECT_EQ(*it, 1);

}



TEST_F(ContainerStorageTest_13, GetIteratorAtLastIndex_13) {

    auto it = storage.unsafeGetIteratorAt(data.size() - 1);

    EXPECT_EQ(*it, 5);

}



TEST_F(ContainerStorageTest_13, GetIteratorAtBoundaryCondition_13) {

    EXPECT_NO_THROW(storage.unsafeGetIteratorAt(0));

    EXPECT_NO_THROW(storage.unsafeGetIteratorAt(data.size()));

}



TEST_F(ContainerStorageTest_13, GetIteratorAtIndexOutOfRangeThrowsAssertion_13) {

    EXPECT_DEATH(storage.unsafeGetIteratorAt(data.size() + 1), "index <= data_.size()");

}
