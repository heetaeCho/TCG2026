#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"



// Assuming PopplerRectangleExtended is a struct extending PopplerRectangle

struct PopplerRectangleExtended : public _PopplerRectangle {

    int x1;

    int y1;

};



TEST(PopplerRectangleCopyTest_2465, CopyNullPointer_ReturnsNull_2465) {

    EXPECT_EQ(poppler_rectangle_copy(nullptr), nullptr);

}



TEST(PopplerRectangleCopyTest_2465, CopyValidRectangle_ReturnsNewInstance_2465) {

    PopplerRectangleExtended rect = {0, 1, 2, 3};

    PopplerRectangle* copy = poppler_rectangle_copy(reinterpret_cast<PopplerRectangle*>(&rect));

    EXPECT_NE(copy, nullptr);

    EXPECT_EQ(copy->x1, rect.x1);

    EXPECT_EQ(copy->y1, rect.y1);

    EXPECT_EQ(copy->x2, rect.x2);

    EXPECT_EQ(copy->y2, rect.y2);

    g_slice_free(PopplerRectangleExtended, copy);

}



TEST(PopplerRectangleCopyTest_2465, CopyBoundaryValues_ReturnsCorrectValues_2465) {

    PopplerRectangleExtended rect = {INT_MIN, INT_MIN, INT_MAX, INT_MAX};

    PopplerRectangle* copy = poppler_rectangle_copy(reinterpret_cast<PopplerRectangle*>(&rect));

    EXPECT_NE(copy, nullptr);

    EXPECT_EQ(copy->x1, rect.x1);

    EXPECT_EQ(copy->y1, rect.y1);

    EXPECT_EQ(copy->x2, rect.x2);

    EXPECT_EQ(copy->y2, rect.y2);

    g_slice_free(PopplerRectangleExtended, copy);

}
