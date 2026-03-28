#include <gtest/gtest.h>

extern "C" {
#include "poppler-page.h"
}

// We need the declarations for the functions we're testing
extern "C" {
PopplerPageTransition *poppler_page_transition_new(void);
PopplerPageTransition *poppler_page_transition_copy(PopplerPageTransition *transition);
void poppler_page_transition_free(PopplerPageTransition *transition);
}

class PopplerPageTransitionTest_2490 : public ::testing::Test {
protected:
    void TearDown() override {
        // Cleanup handled in individual tests
    }
};

TEST_F(PopplerPageTransitionTest_2490, CopyReturnsNonNull_2490)
{
    PopplerPageTransition *original = poppler_page_transition_new();
    ASSERT_NE(original, nullptr);

    PopplerPageTransition *copy = poppler_page_transition_copy(original);
    ASSERT_NE(copy, nullptr);

    poppler_page_transition_free(original);
    poppler_page_transition_free(copy);
}

TEST_F(PopplerPageTransitionTest_2490, CopyReturnsDifferentPointer_2490)
{
    PopplerPageTransition *original = poppler_page_transition_new();
    ASSERT_NE(original, nullptr);

    PopplerPageTransition *copy = poppler_page_transition_copy(original);
    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, original);

    poppler_page_transition_free(original);
    poppler_page_transition_free(copy);
}

TEST_F(PopplerPageTransitionTest_2490, CopyPreservesType_2490)
{
    PopplerPageTransition *original = poppler_page_transition_new();
    ASSERT_NE(original, nullptr);

    original->type = POPPLER_PAGE_TRANSITION_BLINDS;

    PopplerPageTransition *copy = poppler_page_transition_copy(original);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->type, original->type);
    EXPECT_EQ(copy->type, POPPLER_PAGE_TRANSITION_BLINDS);

    poppler_page_transition_free(original);
    poppler_page_transition_free(copy);
}

TEST_F(PopplerPageTransitionTest_2490, CopyPreservesAlignment_2490)
{
    PopplerPageTransition *original = poppler_page_transition_new();
    ASSERT_NE(original, nullptr);

    original->alignment = POPPLER_PAGE_TRANSITION_VERTICAL;

    PopplerPageTransition *copy = poppler_page_transition_copy(original);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->alignment, original->alignment);
    EXPECT_EQ(copy->alignment, POPPLER_PAGE_TRANSITION_VERTICAL);

    poppler_page_transition_free(original);
    poppler_page_transition_free(copy);
}

TEST_F(PopplerPageTransitionTest_2490, CopyPreservesDirection_2490)
{
    PopplerPageTransition *original = poppler_page_transition_new();
    ASSERT_NE(original, nullptr);

    original->direction = POPPLER_PAGE_TRANSITION_OUTWARD;

    PopplerPageTransition *copy = poppler_page_transition_copy(original);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->direction, original->direction);
    EXPECT_EQ(copy->direction, POPPLER_PAGE_TRANSITION_OUTWARD);

    poppler_page_transition_free(original);
    poppler_page_transition_free(copy);
}

TEST_F(PopplerPageTransitionTest_2490, CopyPreservesScale_2490)
{
    PopplerPageTransition *original = poppler_page_transition_new();
    ASSERT_NE(original, nullptr);

    original->scale = 42;

    PopplerPageTransition *copy = poppler_page_transition_copy(original);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->scale, 42);

    poppler_page_transition_free(original);
    poppler_page_transition_free(copy);
}

TEST_F(PopplerPageTransitionTest_2490, CopyPreservesRectangular_2490)
{
    PopplerPageTransition *original = poppler_page_transition_new();
    ASSERT_NE(original, nullptr);

    original->rectangular = 1;

    PopplerPageTransition *copy = poppler_page_transition_copy(original);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->rectangular, 1);

    poppler_page_transition_free(original);
    poppler_page_transition_free(copy);
}

TEST_F(PopplerPageTransitionTest_2490, CopyPreservesDurationReal_2490)
{
    PopplerPageTransition *original = poppler_page_transition_new();
    ASSERT_NE(original, nullptr);

    original->duration_real = 500;

    PopplerPageTransition *copy = poppler_page_transition_copy(original);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->duration_real, 500);

    poppler_page_transition_free(original);
    poppler_page_transition_free(copy);
}

TEST_F(PopplerPageTransitionTest_2490, CopyPreservesAllFields_2490)
{
    PopplerPageTransition *original = poppler_page_transition_new();
    ASSERT_NE(original, nullptr);

    original->type = POPPLER_PAGE_TRANSITION_DISSOLVE;
    original->alignment = POPPLER_PAGE_TRANSITION_HORIZONTAL;
    original->direction = POPPLER_PAGE_TRANSITION_INWARD;
    original->scale = 100;
    original->rectangular = 0;
    original->duration_real = 2000;

    PopplerPageTransition *copy = poppler_page_transition_copy(original);
    ASSERT_NE(copy, nullptr);

    EXPECT_EQ(copy->type, POPPLER_PAGE_TRANSITION_DISSOLVE);
    EXPECT_EQ(copy->alignment, POPPLER_PAGE_TRANSITION_HORIZONTAL);
    EXPECT_EQ(copy->direction, POPPLER_PAGE_TRANSITION_INWARD);
    EXPECT_EQ(copy->scale, 100);
    EXPECT_EQ(copy->rectangular, 0);
    EXPECT_EQ(copy->duration_real, 2000);

    poppler_page_transition_free(original);
    poppler_page_transition_free(copy);
}

TEST_F(PopplerPageTransitionTest_2490, CopyIsIndependentOfOriginal_2490)
{
    PopplerPageTransition *original = poppler_page_transition_new();
    ASSERT_NE(original, nullptr);

    original->type = POPPLER_PAGE_TRANSITION_BLINDS;
    original->scale = 50;

    PopplerPageTransition *copy = poppler_page_transition_copy(original);
    ASSERT_NE(copy, nullptr);

    // Modify original after copy
    original->type = POPPLER_PAGE_TRANSITION_REPLACE;
    original->scale = 999;

    // Copy should retain original values
    EXPECT_EQ(copy->type, POPPLER_PAGE_TRANSITION_BLINDS);
    EXPECT_EQ(copy->scale, 50);

    poppler_page_transition_free(original);
    poppler_page_transition_free(copy);
}

TEST_F(PopplerPageTransitionTest_2490, CopyDefaultTransition_2490)
{
    PopplerPageTransition *original = poppler_page_transition_new();
    ASSERT_NE(original, nullptr);

    // Copy a newly created transition with default values
    PopplerPageTransition *copy = poppler_page_transition_copy(original);
    ASSERT_NE(copy, nullptr);

    // Both should have the same default values
    EXPECT_EQ(copy->type, original->type);
    EXPECT_EQ(copy->alignment, original->alignment);
    EXPECT_EQ(copy->direction, original->direction);
    EXPECT_EQ(copy->scale, original->scale);
    EXPECT_EQ(copy->rectangular, original->rectangular);
    EXPECT_EQ(copy->duration_real, original->duration_real);

    poppler_page_transition_free(original);
    poppler_page_transition_free(copy);
}

TEST_F(PopplerPageTransitionTest_2490, MultipleCopiesAreIndependent_2490)
{
    PopplerPageTransition *original = poppler_page_transition_new();
    ASSERT_NE(original, nullptr);

    original->scale = 10;

    PopplerPageTransition *copy1 = poppler_page_transition_copy(original);
    ASSERT_NE(copy1, nullptr);

    original->scale = 20;

    PopplerPageTransition *copy2 = poppler_page_transition_copy(original);
    ASSERT_NE(copy2, nullptr);

    EXPECT_EQ(copy1->scale, 10);
    EXPECT_EQ(copy2->scale, 20);

    // Verify all three are different pointers
    EXPECT_NE(original, copy1);
    EXPECT_NE(original, copy2);
    EXPECT_NE(copy1, copy2);

    poppler_page_transition_free(original);
    poppler_page_transition_free(copy1);
    poppler_page_transition_free(copy2);
}

TEST_F(PopplerPageTransitionTest_2490, CopyOfCopyPreservesValues_2490)
{
    PopplerPageTransition *original = poppler_page_transition_new();
    ASSERT_NE(original, nullptr);

    original->type = POPPLER_PAGE_TRANSITION_COVER;
    original->scale = 77;
    original->duration_real = 1234;

    PopplerPageTransition *copy1 = poppler_page_transition_copy(original);
    ASSERT_NE(copy1, nullptr);

    PopplerPageTransition *copy2 = poppler_page_transition_copy(copy1);
    ASSERT_NE(copy2, nullptr);

    EXPECT_EQ(copy2->type, POPPLER_PAGE_TRANSITION_COVER);
    EXPECT_EQ(copy2->scale, 77);
    EXPECT_EQ(copy2->duration_real, 1234);

    poppler_page_transition_free(original);
    poppler_page_transition_free(copy1);
    poppler_page_transition_free(copy2);
}

TEST_F(PopplerPageTransitionTest_2490, CopyWithBoundaryValues_2490)
{
    PopplerPageTransition *original = poppler_page_transition_new();
    ASSERT_NE(original, nullptr);

    original->scale = 0;
    original->rectangular = 0;
    original->duration_real = 0;

    PopplerPageTransition *copy = poppler_page_transition_copy(original);
    ASSERT_NE(copy, nullptr);

    EXPECT_EQ(copy->scale, 0);
    EXPECT_EQ(copy->rectangular, 0);
    EXPECT_EQ(copy->duration_real, 0);

    poppler_page_transition_free(original);
    poppler_page_transition_free(copy);
}

TEST_F(PopplerPageTransitionTest_2490, NewTransitionIsNotNull_2490)
{
    PopplerPageTransition *transition = poppler_page_transition_new();
    EXPECT_NE(transition, nullptr);
    poppler_page_transition_free(transition);
}
