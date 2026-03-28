#include <gtest/gtest.h>

#include "re2/pod_array.h"



namespace re2 {



class PODArrayTest_68 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if necessary

    }



    void TearDown() override {

        // Teardown if necessary

    }

};



TEST_F(PODArrayTest_68, DefaultConstructorInitializesEmptyArray_68) {

    PODArray<int> array;

    EXPECT_EQ(array.size(), 0);

}



TEST_F(PODArrayTest_68, ConstructorWithLengthCreatesArrayOfSizeN_68) {

    int length = 10;

    PODArray<int> array(length);

    EXPECT_EQ(array.size(), length);

}



TEST_F(PODArrayTest_68, DataReturnsPointerToUnderlyingData_68) {

    int length = 5;

    PODArray<int> array(length);

    EXPECT_EQ(array.data(), &array[0]);

}



TEST_F(PODArrayTest_68, OperatorBracketAccessesElementsCorrectly_68) {

    int length = 3;

    PODArray<int> array(length);

    array[0] = 10;

    array[1] = 20;

    array[2] = 30;



    EXPECT_EQ(array[0], 10);

    EXPECT_EQ(array[1], 20);

    EXPECT_EQ(array[2], 30);

}



TEST_F(PODArrayTest_68, AccessingElementOutsideBoundsCausesUndefinedBehavior_68) {

    int length = 2;

    PODArray<int> array(length);



    // This test case is tricky because accessing out of bounds doesn't necessarily throw an exception.

    // We can only test that it compiles and runs, but not the behavior itself as it's undefined.

    EXPECT_NO_THROW(array[2] = 100); // Undefined behavior, but should not crash

}



TEST_F(PODArrayTest_68, SizeReturnsCorrectSizeAfterConstruction_68) {

    int length = 7;

    PODArray<int> array(length);

    EXPECT_EQ(array.size(), length);

}



}  // namespace re2
