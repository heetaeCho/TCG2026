#include <gtest/gtest.h>

#include <gmock/gmock.h>

extern "C" {

    #include "./TestProjects/poppler/glib/poppler-annot.h"

}



TEST(PopplerAnnotCalloutLineCopyTest_2107, CopyValidObject_2107) {

    PopplerAnnotCalloutLine original = { 1, 10, 20 };

    PopplerAnnotCalloutLine *copy = poppler_annot_callout_line_copy(&original);



    ASSERT_NE(copy, nullptr);

    EXPECT_EQ(copy->multiline, original.multiline);

    EXPECT_EQ(copy->x3, original.x3);

    EXPECT_EQ(copy->y3, original.y3);



    g_free(copy); // Clean up the allocated memory

}



TEST(PopplerAnnotCalloutLineCopyTest_2107, CopyBoundaryConditions_2107) {

    PopplerAnnotCalloutLine original = { 0, INT_MIN, INT_MAX };

    PopplerAnnotCalloutLine *copy = poppler_annot_callout_line_copy(&original);



    ASSERT_NE(copy, nullptr);

    EXPECT_EQ(copy->multiline, original.multiline);

    EXPECT_EQ(copy->x3, original.x3);

    EXPECT_EQ(copy->y3, original.y3);



    g_free(copy); // Clean up the allocated memory

}



TEST(PopplerAnnotCalloutLineCopyTest_2107, NullInput_2107) {

    PopplerAnnotCalloutLine *copy = poppler_annot_callout_line_copy(nullptr);



    EXPECT_EQ(copy, nullptr);

}
