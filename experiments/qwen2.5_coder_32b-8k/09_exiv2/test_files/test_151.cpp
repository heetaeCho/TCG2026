#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class ValueTypeTest_151 : public ::testing::Test {

protected:

    ValueType<int> intValueType;

};



TEST_F(ValueTypeTest_151, CountInitiallyZero_151) {

    EXPECT_EQ(intValueType.count(), 0);

}



TEST_F(ValueTypeTest_151, CountAfterAddingOneElement_151) {

    intValueType.value_.push_back(42);

    EXPECT_EQ(intValueType.count(), 1);

}



TEST_F(ValueTypeTest_151, CountAfterAddingMultipleElements_151) {

    for (int i = 0; i < 10; ++i) {

        intValueType.value_.push_back(i);

    }

    EXPECT_EQ(intValueType.count(), 10);

}



TEST_F(ValueTypeTest_151, CountBoundaryCondition_151) {

    // Assuming size_t can handle large values, testing with a large count

    for (size_t i = 0; i < 1000000; ++i) {

        intValueType.value_.push_back(static_cast<int>(i));

    }

    EXPECT_EQ(intValueType.count(), 1000000);

}



TEST_F(ValueTypeTest_151, CountAfterClearingElements_151) {

    for (int i = 0; i < 10; ++i) {

        intValueType.value_.push_back(i);

    }

    intValueType.value_.clear();

    EXPECT_EQ(intValueType.count(), 0);

}
