#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "re2/pod_array.h"



using namespace re2;



class PODArrayTest_67 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(PODArrayTest_67, DefaultConstructorCreatesEmptyArray_67) {

    PODArray<int> podArray;

    EXPECT_EQ(podArray.size(), 0);

}



TEST_F(PODArrayTest_67, ConstructorWithZeroLengthCreatesEmptyArray_67) {

    PODArray<int> podArray(0);

    EXPECT_EQ(podArray.size(), 0);

}



TEST_F(PODArrayTest_67, ConstructorWithPositiveLengthCreatesProperSizeArray_67) {

    PODArray<int> podArray(5);

    EXPECT_EQ(podArray.size(), 5);

}



TEST_F(PODArrayTest_67, AccessOperatorDoesNotCauseSegFaultForValidIndex_67) {

    PODArray<int> podArray(3);

    EXPECT_NO_THROW(podArray[0] = 1);

    EXPECT_NO_THROW(podArray[1] = 2);

    EXPECT_NO_THROW(podArray[2] = 3);

}



TEST_F(PODArrayTest_67, AccessOperatorReturnsProperValues_67) {

    PODArray<int> podArray(3);

    podArray[0] = 1;

    podArray[1] = 2;

    podArray[2] = 3;

    EXPECT_EQ(podArray[0], 1);

    EXPECT_EQ(podArray[1], 2);

    EXPECT_EQ(podArray[2], 3);

}



TEST_F(PODArrayTest_67, AccessOperatorThrowsForNegativeIndex_67) {

    PODArray<int> podArray(3);

    EXPECT_THROW(podArray[-1], std::exception);

}



TEST_F(PODArrayTest_67, AccessOperatorThrowsForIndexEqualToSize_67) {

    PODArray<int> podArray(3);

    EXPECT_THROW(podArray[3], std::exception);

}



TEST_F(PODArrayTest_67, DataMethodReturnsNonNullPointer_67) {

    PODArray<int> podArray(5);

    EXPECT_NE(podArray.data(), nullptr);

}
