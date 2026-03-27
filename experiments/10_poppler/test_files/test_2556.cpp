#include <gtest/gtest.h>

#include "TestProjects/poppler/glib/poppler-structure-element.cc"

#include "TestProjects/poppler/glib/poppler-page.h"



class ConvertColorTest_2556 : public ::testing::Test {

protected:

    Object arrayObject;

    PopplerColor color;



    void SetUp() override {

        // Create an array object with 3 elements for color conversion

        Array* array = new Array();

        array->add(Object(0.5)); // Red component

        array->add(Object(0.25)); // Green component

        array->add(Object(0.75)); // Blue component

        arrayObject = Object(array);

    }



    void TearDown() override {

        // Clean up the array object

        Array* array = arrayObject.getArray();

        if (array) {

            delete array;

        }

    }

};



TEST_F(ConvertColorTest_2556, NormalOperation_2556) {

    convert_color(&arrayObject, &color);

    EXPECT_EQ(color.red, 32768); // 0.5 * 65535

    EXPECT_EQ(color.green, 16384); // 0.25 * 65535

    EXPECT_EQ(color.blue, 49152); // 0.75 * 65535

}



TEST_F(ConvertColorTest_2556, BoundaryConditions_MinValues_2556) {

    Array* array = new Array();

    array->add(Object(0.0)); // Red component

    array->add(Object(0.0)); // Green component

    array->add(Object(0.0)); // Blue component

    Object minArrayObject(array);



    convert_color(&minArrayObject, &color);

    EXPECT_EQ(color.red, 0); // 0.0 * 65535

    EXPECT_EQ(color.green, 0); // 0.0 * 65535

    EXPECT_EQ(color.blue, 0); // 0.0 * 65535



    delete array;

}



TEST_F(ConvertColorTest_2556, BoundaryConditions_MaxValues_2556) {

    Array* array = new Array();

    array->add(Object(1.0)); // Red component

    array->add(Object(1.0)); // Green component

    array->add(Object(1.0)); // Blue component

    Object maxArrayObject(array);



    convert_color(&maxArrayObject, &color);

    EXPECT_EQ(color.red, 65535); // 1.0 * 65535

    EXPECT_EQ(color.green, 65535); // 1.0 * 65535

    EXPECT_EQ(color.blue, 65535); // 1.0 * 65535



    delete array;

}



TEST_F(ConvertColorTest_2556, ErrorCase_NotArray_2556) {

    Object nonArrayObject(42); // Integer object instead of Array

    EXPECT_DEATH(convert_color(&nonArrayObject, &color), "object->isArray\\(\\)");

}



TEST_F(ConvertColorTest_2556, ErrorCase_ArrayLengthNotThree_2556) {

    Array* array = new Array();

    array->add(Object(0.5)); // Only one element

    Object shortArrayObject(array);

    

    EXPECT_DEATH(convert_color(&shortArrayObject, &color), "object->arrayGetLength\\(\\) != 3");



    delete array;

}



TEST_F(ConvertColorTest_2556, ErrorCase_ColorNull_2556) {

    EXPECT_DEATH(convert_color(&arrayObject, nullptr), "g_assert\\(color != nullptr\\)");

}
