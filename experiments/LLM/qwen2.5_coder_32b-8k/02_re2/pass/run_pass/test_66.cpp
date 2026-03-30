#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/re2/re2/pod_array.h"



using namespace re2;



class PODArrayTest_66 : public ::testing::Test {

protected:

    PODArray<int> pod_array;

};



TEST_F(PODArrayTest_66, DefaultConstructorInitializesEmptyArray_66) {

    EXPECT_EQ(pod_array.data(), nullptr);

    EXPECT_EQ(pod_array.size(), 0);

}



TEST_F(PODArrayTest_66, ConstructorWithLengthAllocatesMemory_66) {

    PODArray<int> array_with_length(10);

    EXPECT_NE(array_with_length.data(), nullptr);

    EXPECT_EQ(array_with_length.size(), 10);

}



TEST_F(PODArrayTest_66, AccessOperatorReturnsCorrectElement_66) {

    PODArray<int> array_with_length(3);

    array_with_length[0] = 42;

    array_with_length[1] = 84;

    array_with_length[2] = 168;



    EXPECT_EQ(array_with_length[0], 42);

    EXPECT_EQ(array_with_length[1], 84);

    EXPECT_EQ(array_with_length[2], 168);

}



TEST_F(PODArrayTest_66, BoundaryConditionZeroLength_66) {

    PODArray<int> zero_length_array(0);

    EXPECT_EQ(zero_length_array.data(), nullptr);

    EXPECT_EQ(zero_length_array.size(), 0);

}



TEST_F(PODArrayTest_66, AccessOperatorThrowsForOutOfBoundIndex_66) {

    PODArray<int> array_with_length(1);

    EXPECT_DEATH(array_with_length[1], "");

}
