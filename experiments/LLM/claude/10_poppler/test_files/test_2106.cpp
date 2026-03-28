#include <gtest/gtest.h>
#include <glib.h>

// Forward declare the struct and function as they would be in the header
extern "C" {

typedef struct _PopplerAnnotCalloutLine PopplerAnnotCalloutLine;

struct _PopplerAnnotCalloutLine
{
    gboolean multiline;
    gdouble x1;
    gdouble y1;
    gdouble x2;
    gdouble y2;
    gdouble x3;
    gdouble y3;
};

PopplerAnnotCalloutLine *poppler_annot_callout_line_new(void);

}

class PopplerAnnotCalloutLineTest_2106 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any allocated memory if needed
    }
};

TEST_F(PopplerAnnotCalloutLineTest_2106, NewReturnsNonNull_2106) {
    PopplerAnnotCalloutLine *line = poppler_annot_callout_line_new();
    ASSERT_NE(line, nullptr);
    g_free(line);
}

TEST_F(PopplerAnnotCalloutLineTest_2106, NewReturnsZeroInitialized_2106) {
    PopplerAnnotCalloutLine *line = poppler_annot_callout_line_new();
    ASSERT_NE(line, nullptr);

    // g_new0 zero-initializes the memory, so all fields should be zero
    EXPECT_EQ(line->multiline, FALSE);
    EXPECT_DOUBLE_EQ(line->x1, 0.0);
    EXPECT_DOUBLE_EQ(line->y1, 0.0);
    EXPECT_DOUBLE_EQ(line->x2, 0.0);
    EXPECT_DOUBLE_EQ(line->y2, 0.0);
    EXPECT_DOUBLE_EQ(line->x3, 0.0);
    EXPECT_DOUBLE_EQ(line->y3, 0.0);

    g_free(line);
}

TEST_F(PopplerAnnotCalloutLineTest_2106, MultipleAllocationsAreIndependent_2106) {
    PopplerAnnotCalloutLine *line1 = poppler_annot_callout_line_new();
    PopplerAnnotCalloutLine *line2 = poppler_annot_callout_line_new();

    ASSERT_NE(line1, nullptr);
    ASSERT_NE(line2, nullptr);
    EXPECT_NE(line1, line2);

    // Modify one and verify the other is unaffected
    line1->x1 = 42.0;
    line1->y1 = 84.0;
    line1->multiline = TRUE;

    EXPECT_DOUBLE_EQ(line2->x1, 0.0);
    EXPECT_DOUBLE_EQ(line2->y1, 0.0);
    EXPECT_EQ(line2->multiline, FALSE);

    g_free(line1);
    g_free(line2);
}

TEST_F(PopplerAnnotCalloutLineTest_2106, FieldsAreWritableAndReadable_2106) {
    PopplerAnnotCalloutLine *line = poppler_annot_callout_line_new();
    ASSERT_NE(line, nullptr);

    line->multiline = TRUE;
    line->x1 = 1.5;
    line->y1 = 2.5;
    line->x2 = 3.5;
    line->y2 = 4.5;
    line->x3 = 5.5;
    line->y3 = 6.5;

    EXPECT_EQ(line->multiline, TRUE);
    EXPECT_DOUBLE_EQ(line->x1, 1.5);
    EXPECT_DOUBLE_EQ(line->y1, 2.5);
    EXPECT_DOUBLE_EQ(line->x2, 3.5);
    EXPECT_DOUBLE_EQ(line->y2, 4.5);
    EXPECT_DOUBLE_EQ(line->x3, 5.5);
    EXPECT_DOUBLE_EQ(line->y3, 6.5);

    g_free(line);
}

TEST_F(PopplerAnnotCalloutLineTest_2106, FieldsAcceptNegativeValues_2106) {
    PopplerAnnotCalloutLine *line = poppler_annot_callout_line_new();
    ASSERT_NE(line, nullptr);

    line->x1 = -100.25;
    line->y1 = -200.75;
    line->x2 = -300.5;
    line->y2 = -400.125;

    EXPECT_DOUBLE_EQ(line->x1, -100.25);
    EXPECT_DOUBLE_EQ(line->y1, -200.75);
    EXPECT_DOUBLE_EQ(line->x2, -300.5);
    EXPECT_DOUBLE_EQ(line->y2, -400.125);

    g_free(line);
}

TEST_F(PopplerAnnotCalloutLineTest_2106, FieldsAcceptLargeValues_2106) {
    PopplerAnnotCalloutLine *line = poppler_annot_callout_line_new();
    ASSERT_NE(line, nullptr);

    line->x1 = 1e15;
    line->y1 = 1e15;
    line->x2 = -1e15;
    line->y2 = -1e15;

    EXPECT_DOUBLE_EQ(line->x1, 1e15);
    EXPECT_DOUBLE_EQ(line->y1, 1e15);
    EXPECT_DOUBLE_EQ(line->x2, -1e15);
    EXPECT_DOUBLE_EQ(line->y2, -1e15);

    g_free(line);
}

TEST_F(PopplerAnnotCalloutLineTest_2106, CanFreeWithGFree_2106) {
    // Verifies that the allocation is compatible with g_free (no crash)
    PopplerAnnotCalloutLine *line = poppler_annot_callout_line_new();
    ASSERT_NE(line, nullptr);
    g_free(line);
    // If we reach here without crashing, the test passes
}

TEST_F(PopplerAnnotCalloutLineTest_2106, RepeatedAllocationsSucceed_2106) {
    // Stress test: allocate and free multiple times
    for (int i = 0; i < 100; ++i) {
        PopplerAnnotCalloutLine *line = poppler_annot_callout_line_new();
        ASSERT_NE(line, nullptr) << "Allocation failed on iteration " << i;
        EXPECT_DOUBLE_EQ(line->x1, 0.0);
        EXPECT_DOUBLE_EQ(line->y1, 0.0);
        g_free(line);
    }
}
