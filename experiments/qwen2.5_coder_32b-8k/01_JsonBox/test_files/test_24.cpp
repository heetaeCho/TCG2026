#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest : public ::testing::Test {

protected:

    Value defaultValue;

    Value stringValue = "test";

    Value intValue = 42;

    Value doubleValue = 3.14;

    Value booleanValue = true;

    Value nullValue;

    Value objectValue = Object{{"key", "value"}};

    Value arrayValue = Array{42, 3.14};



    ValueTest() {

        // Setup code if needed

    }



    virtual ~ValueTest() {

        // Teardown code if needed

    }

};



TEST_F(ValueTest_24, EqualOperator_SameValues_ReturnTrue_24) {

    EXPECT_TRUE(stringValue == stringValue);

}



TEST_F(ValueTest_24, NotEqualOperator_DifferentValues_ReturnTrue_24) {

    EXPECT_TRUE(stringValue != intValue);

}



TEST_F(ValueTest_24, EqualOperator_StringAndCString_ReturnTrue_24) {

    Value cStringValue = "test";

    EXPECT_TRUE(stringValue == cStringValue);

}



TEST_F(ValueTest_24, NotEqualOperator_StringAndDifferentCString_ReturnTrue_24) {

    Value differentCStringValue = "different";

    EXPECT_TRUE(stringValue != differentCStringValue);

}



TEST_F(ValueTest_24, EqualOperator_SameIntegers_ReturnTrue_24) {

    Value sameIntValue = 42;

    EXPECT_TRUE(intValue == sameIntValue);

}



TEST_F(ValueTest_24, NotEqualOperator_DifferentIntegers_ReturnTrue_24) {

    Value differentIntValue = 0;

    EXPECT_TRUE(intValue != differentIntValue);

}



TEST_F(ValueTest_24, EqualOperator_SameDoubles_ReturnTrue_24) {

    Value sameDoubleValue = 3.14;

    EXPECT_TRUE(doubleValue == sameDoubleValue);

}



TEST_F(ValueTest_24, NotEqualOperator_DifferentDoubles_ReturnTrue_24) {

    Value differentDoubleValue = 0.0;

    EXPECT_TRUE(doubleValue != differentDoubleValue);

}



TEST_F(ValueTest_24, EqualOperator_SameBooleans_ReturnTrue_24) {

    Value sameBooleanValue = true;

    EXPECT_TRUE(booleanValue == sameBooleanValue);

}



TEST_F(ValueTest_24, NotEqualOperator_DifferentBooleans_ReturnTrue_24) {

    Value differentBooleanValue = false;

    EXPECT_TRUE(booleanValue != differentBooleanValue);

}



TEST_F(ValueTest_24, EqualOperator_DefaultAndNull_ReturnTrue_24) {

    EXPECT_TRUE(defaultValue == nullValue);

}



TEST_F(ValueTest_24, NotEqualOperator_DefaultAndStringValue_ReturnTrue_24) {

    EXPECT_TRUE(defaultValue != stringValue);

}



TEST_F(ValueTest_24, EqualOperator_SameObjects_ReturnTrue_24) {

    Value sameObjectValue = Object{{"key", "value"}};

    EXPECT_TRUE(objectValue == sameObjectValue);

}



TEST_F(ValueTest_24, NotEqualOperator_DifferentObjects_ReturnTrue_24) {

    Value differentObjectValue = Object{{"otherKey", "otherValue"}};

    EXPECT_TRUE(objectValue != differentObjectValue);

}



TEST_F(ValueTest_24, EqualOperator_SameArrays_ReturnTrue_24) {

    Value sameArrayValue = Array{42, 3.14};

    EXPECT_TRUE(arrayValue == sameArrayValue);

}



TEST_F(ValueTest_24, NotEqualOperator_DifferentArrays_ReturnTrue_24) {

    Value differentArrayValue = Array{0, 0.0};

    EXPECT_TRUE(arrayValue != differentArrayValue);

}
