#include <gtest/gtest.h>

#include "Object.h"



// Assuming Object and gdouble are defined in appropriate headers



TEST(convert_double_or_4_doubles_Test_2560, SingleNumberConversion_2560) {

    Object obj(10.5);

    gdouble value[4] = {0};

    convert_double_or_4_doubles(&obj, value);

    EXPECT_EQ(value[0], 10.5);

    EXPECT_EQ(value[1], 10.5);

    EXPECT_EQ(value[2], 10.5);

    EXPECT_EQ(value[3], 10.5);

}



TEST(convert_double_or_4_doubles_Test_2560, ArrayConversion_2560) {

    Object arrayObj(new Array());

    arrayObj.arrayAdd(Object(1.0));

    arrayObj.arrayAdd(Object(2.0));

    arrayObj.arrayAdd(Object(3.0));

    arrayObj.arrayAdd(Object(4.0));



    gdouble value[4] = {0};

    convert_double_or_4_doubles(&arrayObj, value);

    EXPECT_EQ(value[0], 1.0);

    EXPECT_EQ(value[1], 2.0);

    EXPECT_EQ(value[2], 3.0);

    EXPECT_EQ(value[3], 4.0);

}



TEST(convert_double_or_4_doubles_Test_2560, ArrayLengthMismatch_2560) {

    Object arrayObj(new Array());

    arrayObj.arrayAdd(Object(1.0));

    arrayObj.arrayAdd(Object(2.0));



    gdouble value[4] = {0};

    EXPECT_DEATH(convert_double_or_4_doubles(&arrayObj, value), ".*g_assertion failed.*");

}



TEST(convert_double_or_4_doubles_Test_2560, NullObject_2560) {

    Object *obj = nullptr;

    gdouble value[4] = {0};

    EXPECT_DEATH(convert_double_or_4_doubles(obj, value), ".*g_assertion failed.*");

}



TEST(convert_double_or_4_doubles_Test_2560, NonNumericArrayElement_2560) {

    Object arrayObj(new Array());

    arrayObj.arrayAdd(Object(1.0));

    arrayObj.arrayAdd(Object("invalid"));

    arrayObj.arrayAdd(Object(3.0));

    arrayObj.arrayAdd(Object(4.0));



    gdouble value[4] = {0};

    EXPECT_DEATH(convert_double_or_4_doubles(&arrayObj, value), ".*g_assertion failed.*");

}



TEST(convert_double_or_4_doubles_Test_2560, NonNumericObject_2560) {

    Object obj("invalid");

    gdouble value[4] = {0};

    EXPECT_DEATH(convert_double_or_4_doubles(&obj, value), ".*g_assertion failed.*");

}
