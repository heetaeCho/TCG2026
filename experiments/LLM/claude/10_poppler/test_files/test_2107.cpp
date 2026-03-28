#include <gtest/gtest.h>
#include <glib.h>

extern "C" {
#include "poppler-annot.h"
}

// Since the header might not perfectly match, we need the function declaration
extern "C" {
PopplerAnnotCalloutLine *poppler_annot_callout_line_copy(PopplerAnnotCalloutLine *callout);
PopplerAnnotCalloutLine *poppler_annot_callout_line_new(void);
void poppler_annot_callout_line_free(PopplerAnnotCalloutLine *callout);
}

class PopplerAnnotCalloutLineCopyTest_2107 : public ::testing::Test {
protected:
    void TearDown() override {}
};

// Test that copying a valid callout line returns a non-null pointer
TEST_F(PopplerAnnotCalloutLineCopyTest_2107, CopyReturnsNonNull_2107)
{
    PopplerAnnotCalloutLine *original = g_new0(PopplerAnnotCalloutLine, 1);
    original->multiline = 1;
    original->x3 = 10;
    original->y3 = 20;

    PopplerAnnotCalloutLine *copy = poppler_annot_callout_line_copy(original);

    ASSERT_NE(copy, nullptr);

    g_free(copy);
    g_free(original);
}

// Test that the copied callout line has the same field values as the original
TEST_F(PopplerAnnotCalloutLineCopyTest_2107, CopyPreservesFieldValues_2107)
{
    PopplerAnnotCalloutLine *original = g_new0(PopplerAnnotCalloutLine, 1);
    original->multiline = 1;
    original->x3 = 42;
    original->y3 = 99;

    PopplerAnnotCalloutLine *copy = poppler_annot_callout_line_copy(original);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->multiline, original->multiline);
    EXPECT_EQ(copy->x3, original->x3);
    EXPECT_EQ(copy->y3, original->y3);

    g_free(copy);
    g_free(original);
}

// Test that the copy is a distinct object (different pointer)
TEST_F(PopplerAnnotCalloutLineCopyTest_2107, CopyIsDifferentObject_2107)
{
    PopplerAnnotCalloutLine *original = g_new0(PopplerAnnotCalloutLine, 1);
    original->multiline = 0;
    original->x3 = 5;
    original->y3 = 15;

    PopplerAnnotCalloutLine *copy = poppler_annot_callout_line_copy(original);

    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, original);

    g_free(copy);
    g_free(original);
}

// Test that passing nullptr returns NULL
TEST_F(PopplerAnnotCalloutLineCopyTest_2107, CopyNullReturnsNull_2107)
{
    PopplerAnnotCalloutLine *copy = poppler_annot_callout_line_copy(nullptr);

    EXPECT_EQ(copy, nullptr);
}

// Test that modifying the copy does not affect the original
TEST_F(PopplerAnnotCalloutLineCopyTest_2107, ModifyingCopyDoesNotAffectOriginal_2107)
{
    PopplerAnnotCalloutLine *original = g_new0(PopplerAnnotCalloutLine, 1);
    original->multiline = 1;
    original->x3 = 100;
    original->y3 = 200;

    PopplerAnnotCalloutLine *copy = poppler_annot_callout_line_copy(original);
    ASSERT_NE(copy, nullptr);

    copy->multiline = 0;
    copy->x3 = 999;
    copy->y3 = 888;

    EXPECT_EQ(original->multiline, 1);
    EXPECT_EQ(original->x3, 100);
    EXPECT_EQ(original->y3, 200);

    g_free(copy);
    g_free(original);
}

// Test copying with zero-initialized fields
TEST_F(PopplerAnnotCalloutLineCopyTest_2107, CopyZeroInitializedFields_2107)
{
    PopplerAnnotCalloutLine *original = g_new0(PopplerAnnotCalloutLine, 1);
    // All fields should be zero from g_new0

    PopplerAnnotCalloutLine *copy = poppler_annot_callout_line_copy(original);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->multiline, 0);
    EXPECT_EQ(copy->x3, 0);
    EXPECT_EQ(copy->y3, 0);

    g_free(copy);
    g_free(original);
}

// Test copying with negative field values
TEST_F(PopplerAnnotCalloutLineCopyTest_2107, CopyNegativeFieldValues_2107)
{
    PopplerAnnotCalloutLine *original = g_new0(PopplerAnnotCalloutLine, 1);
    original->multiline = -1;
    original->x3 = -500;
    original->y3 = -300;

    PopplerAnnotCalloutLine *copy = poppler_annot_callout_line_copy(original);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->multiline, -1);
    EXPECT_EQ(copy->x3, -500);
    EXPECT_EQ(copy->y3, -300);

    g_free(copy);
    g_free(original);
}

// Test copying with large field values (boundary)
TEST_F(PopplerAnnotCalloutLineCopyTest_2107, CopyLargeFieldValues_2107)
{
    PopplerAnnotCalloutLine *original = g_new0(PopplerAnnotCalloutLine, 1);
    original->multiline = G_MAXINT;
    original->x3 = G_MAXINT;
    original->y3 = G_MININT;

    PopplerAnnotCalloutLine *copy = poppler_annot_callout_line_copy(original);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->multiline, G_MAXINT);
    EXPECT_EQ(copy->x3, G_MAXINT);
    EXPECT_EQ(copy->y3, G_MININT);

    g_free(copy);
    g_free(original);
}

// Test multiple sequential copies produce independent objects
TEST_F(PopplerAnnotCalloutLineCopyTest_2107, MultipleCopiesAreIndependent_2107)
{
    PopplerAnnotCalloutLine *original = g_new0(PopplerAnnotCalloutLine, 1);
    original->multiline = 1;
    original->x3 = 50;
    original->y3 = 75;

    PopplerAnnotCalloutLine *copy1 = poppler_annot_callout_line_copy(original);
    PopplerAnnotCalloutLine *copy2 = poppler_annot_callout_line_copy(original);

    ASSERT_NE(copy1, nullptr);
    ASSERT_NE(copy2, nullptr);
    EXPECT_NE(copy1, copy2);
    EXPECT_NE(copy1, original);
    EXPECT_NE(copy2, original);

    EXPECT_EQ(copy1->multiline, copy2->multiline);
    EXPECT_EQ(copy1->x3, copy2->x3);
    EXPECT_EQ(copy1->y3, copy2->y3);

    // Modifying copy1 should not affect copy2
    copy1->x3 = 999;
    EXPECT_EQ(copy2->x3, 50);

    g_free(copy1);
    g_free(copy2);
    g_free(original);
}
