#include <gtest/gtest.h>

#include <memory>

#include "Object.h"

#include "Array.h"

#include "PDFRectangle.h"



// Assuming parseDiffRectangle is a static function within a class or namespace for testing purposes.

// We'll wrap it in a simple struct to facilitate testing.

struct Annot {

    static std::unique_ptr<PDFRectangle> parseDiffRectangle(Array *array, PDFRectangle *rect);

};



TEST_F(AnnotTest_2018, NormalOperationWithValidArrayAndRect_2018) {

    Array array;

    array.add(Object(1.0));

    array.add(Object(2.0));

    array.add(Object(3.0));

    array.add(Object(4.0));



    PDFRectangle rect(5.0, 6.0, 15.0, 20.0);

    

    auto result = Annot::parseDiffRectangle(&array, &rect);



    ASSERT_NE(result, nullptr);

    EXPECT_DOUBLE_EQ(result->x1, 6.0);

    EXPECT_DOUBLE_EQ(result->y1, 8.0);

    EXPECT_DOUBLE_EQ(result->x2, 12.0);

    EXPECT_DOUBLE_EQ(result->y2, 16.0);

}



TEST_F(AnnotTest_2018, BoundaryConditionWithZeroDifferences_2018) {

    Array array;

    array.add(Object(0.0));

    array.add(Object(0.0));

    array.add(Object(0.0));

    array.add(Object(0.0));



    PDFRectangle rect(5.0, 6.0, 15.0, 20.0);

    

    auto result = Annot::parseDiffRectangle(&array, &rect);



    ASSERT_NE(result, nullptr);

    EXPECT_DOUBLE_EQ(result->x1, 5.0);

    EXPECT_DOUBLE_EQ(result->y1, 6.0);

    EXPECT_DOUBLE_EQ(result->x2, 15.0);

    EXPECT_DOUBLE_EQ(result->y2, 20.0);

}



TEST_F(AnnotTest_2018, BoundaryConditionWithNegativeDifferences_2018) {

    Array array;

    array.add(Object(-1.0));

    array.add(Object(-2.0));

    array.add(Object(-3.0));

    array.add(Object(-4.0));



    PDFRectangle rect(5.0, 6.0, 15.0, 20.0);

    

    auto result = Annot::parseDiffRectangle(&array, &rect);



    EXPECT_EQ(result, nullptr);

}



TEST_F(AnnotTest_2018, BoundaryConditionWithInsufficientArrayLength_2018) {

    Array array;

    array.add(Object(1.0));

    array.add(Object(2.0));



    PDFRectangle rect(5.0, 6.0, 15.0, 20.0);

    

    auto result = Annot::parseDiffRectangle(&array, &rect);



    EXPECT_EQ(result, nullptr);

}



TEST_F(AnnotTest_2018, BoundaryConditionWithInvalidDifferencesExceedingRectSize_2018) {

    Array array;

    array.add(Object(6.0));

    array.add(Object(5.0));

    array.add(Object(10.0));

    array.add(Object(15.0));



    PDFRectangle rect(5.0, 6.0, 15.0, 20.0);

    

    auto result = Annot::parseDiffRectangle(&array, &rect);



    EXPECT_EQ(result, nullptr);

}
