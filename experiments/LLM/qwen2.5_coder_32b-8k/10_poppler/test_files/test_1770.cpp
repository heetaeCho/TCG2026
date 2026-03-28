#include <gtest/gtest.h>

#include "Object.h"



TEST(isRGBColorTest_1770, NormalOperation_RGBArray_1770) {

    Object red(0.5);

    Object green(0.3);

    Object blue(0.2);

    Object array;

    array.arrayAdd(std::move(red));

    array.arrayAdd(std::move(green));

    array.arrayAdd(std::move(blue));



    EXPECT_TRUE(isRGBColor(&array));

}



TEST(isRGBColorTest_1770, NormalOperation_NonRGBArray_1770) {

    Object red(0.5);

    Object green(0.3);

    Object blue(2.0); // Invalid RGB value

    Object array;

    array.arrayAdd(std::move(red));

    array.arrayAdd(std::move(green));

    array.arrayAdd(std::move(blue));



    EXPECT_FALSE(isRGBColor(&array));

}



TEST(isRGBColorTest_1770, BoundaryCondition_EmptyArray_1770) {

    Object emptyArray;

    EXPECT_FALSE(isRGBColor(&emptyArray));

}



TEST(isRGBColorTest_1770, BoundaryCondition_ArrayWithTwoElements_1770) {

    Object red(0.5);

    Object green(0.3);

    Object array;

    array.arrayAdd(std::move(red));

    array.arrayAdd(std::move(green));



    EXPECT_FALSE(isRGBColor(&array));

}



TEST(isRGBColorTest_1770, BoundaryCondition_ArrayWithFourElements_1770) {

    Object red(0.5);

    Object green(0.3);

    Object blue(0.2);

    Object extra(0.1);

    Object array;

    array.arrayAdd(std::move(red));

    array.arrayAdd(std::move(green));

    array.arrayAdd(std::move(blue));

    array.arrayAdd(std::move(extra));



    EXPECT_FALSE(isRGBColor(&array));

}



TEST(isRGBColorTest_1770, ExceptionalCase_ArrayWithNonNumericElements_1770) {

    Object red(0.5);

    Object green(Object::null()); // Non-numeric element

    Object blue(0.2);

    Object array;

    array.arrayAdd(std::move(red));

    array.arrayAdd(std::move(green));

    array.arrayAdd(std::move(blue));



    EXPECT_FALSE(isRGBColor(&array));

}
