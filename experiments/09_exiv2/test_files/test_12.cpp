#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/slice.hpp"

#include <vector>



using namespace Exiv2::Internal;

using ::testing::_;



class ContainerStorageTest : public ::testing::Test {

protected:

    std::vector<int> data = {1, 2, 3, 4, 5};

    ContainerStorage<std::vector<int>> containerStorage{data, 0, data.size()};

};



TEST_F(ContainerStorageTest_12, NormalOperation_UnsafeAt_ReturnsCorrectValue_12) {

    EXPECT_EQ(containerStorage.unsafeAt(0), 1);

    EXPECT_EQ(containerStorage.unsafeAt(4), 5);

}



TEST_F(ContainerStorageTest_12, BoundaryCondition_UnsafeAt_FirstElement_12) {

    EXPECT_EQ(containerStorage.unsafeAt(0), 1);

}



TEST_F(ContainerStorageTest_12, BoundaryCondition_UnsafeAt_LastElement_12) {

    EXPECT_EQ(containerStorage.unsafeAt(data.size() - 1), 5);

}



TEST_F(ContainerStorageTest_12, ExceptionalCase_UnsafeAt_OutOfBounds_12) {

    EXPECT_THROW(containerStorage.unsafeAt(data.size()), std::out_of_range);

    EXPECT_THROW(containerStorage.unsafeAt(data.size() + 1), std::out_of_range);

}



TEST_F(ContainerStorageTest_12, ExceptionalCase_UnsafeAt_NegativeIndex_12) {

    EXPECT_THROW(containerStorage.unsafeAt(-1), std::out_of_range);

}
