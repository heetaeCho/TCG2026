#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest_56 : public ::testing::Test {

protected:

    Value value;

};



TEST_F(ValueTest_56, GetArray_ReturnsEmptyArrayForNonArrayType_56) {

    EXPECT_EQ(&EMPTY_ARRAY, &value.getArray());

}



TEST_F(ValueTest_56, GetArray_ReturnsValidArrayForArrayType_56) {

    Array testArray = {Value(1), Value("test")};

    value.setArray(testArray);

    const Array& returnedArray = value.getArray();

    EXPECT_EQ(testArray.size(), returnedArray.size());

    for (size_t i = 0; i < testArray.size(); ++i) {

        EXPECT_EQ(testArray[i], returnedArray[i]);

    }

}
