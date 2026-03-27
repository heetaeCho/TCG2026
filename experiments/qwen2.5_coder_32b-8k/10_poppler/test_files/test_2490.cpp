#include <gtest/gtest.h>

#include "poppler-page.h"



// Assuming poppler_page_transition_new and poppler_page_transition_copy are declared in poppler-page.h



TEST(PopplerPageTransitionTest_2490, CopyCreatesNewInstance_2490) {

    PopplerPageTransition original;

    original.type = POPPLER_PAGE_TRANSITION_TYPE_SPLIT;

    original.alignment = POPPLER_PAGE_TRANSITION_ALIGNMENT_HORIZONTAL;

    original.direction = POPPLER_PAGE_TRANSITION_DIRECTION_INWARD;

    original.scale = 150;

    original.rectangular = 1;

    original.duration_real = 3;



    PopplerPageTransition* copy = poppler_page_transition_copy(&original);



    EXPECT_NE(copy, &original);

    EXPECT_EQ(copy->type, original.type);

    EXPECT_EQ(copy->alignment, original.alignment);

    EXPECT_EQ(copy->direction, original.direction);

    EXPECT_EQ(copy->scale, original.scale);

    EXPECT_EQ(copy->rectangular, original.rectangular);

    EXPECT_EQ(copy->duration_real, original.duration_real);



    // Clean up

    free(copy);

}



TEST(PopplerPageTransitionTest_2490, CopyPreservesBoundaryValues_2490) {

    PopplerPageTransition original;

    original.type = POPPLER_PAGE_TRANSITION_TYPE_REPLACE; // Assuming this is the minimum type value

    original.alignment = POPPLER_PAGE_TRANSITION_ALIGNMENT_HORIZONTAL;

    original.direction = POPPLER_PAGE_TRANSITION_DIRECTION_INWARD;

    original.scale = 0; // Assuming scale can be zero as a boundary condition

    original.rectangular = 0; // Assuming rectangular can be zero as a boundary condition

    original.duration_real = 0.0;



    PopplerPageTransition* copy = poppler_page_transition_copy(&original);



    EXPECT_EQ(copy->type, original.type);

    EXPECT_EQ(copy->alignment, original.alignment);

    EXPECT_EQ(copy->direction, original.direction);

    EXPECT_EQ(copy->scale, original.scale);

    EXPECT_EQ(copy->rectangular, original.rectangular);

    EXPECT_EQ(copy->duration_real, original.duration_real);



    // Clean up

    free(copy);

}



TEST(PopplerPageTransitionTest_2490, CopyPreservesMaxValues_2490) {

    PopplerPageTransition original;

    original.type = POPPLER_PAGE_TRANSITION_TYPE_BOX; // Assuming this is the maximum type value

    original.alignment = POPPLER_PAGE_TRANSITION_ALIGNMENT_VERTICAL;

    original.direction = POPPLER_PAGE_TRANSITION_DIRECTION_OUTWARD;

    original.scale = 1000; // Assuming scale can be as large as 1000 for testing

    original.rectangular = 1; // Assuming rectangular can be one as a boundary condition

    original.duration_real = 5.0;



    PopplerPageTransition* copy = poppler_page_transition_copy(&original);



    EXPECT_EQ(copy->type, original.type);

    EXPECT_EQ(copy->alignment, original.alignment);

    EXPECT_EQ(copy->direction, original.direction);

    EXPECT_EQ(copy->scale, original.scale);

    EXPECT_EQ(copy->rectangular, original.rectangular);

    EXPECT_EQ(copy->duration_real, original.duration_real);



    // Clean up

    free(copy);

}



TEST(PopplerPageTransitionTest_2490, CopyNullPointerHandling_2490) {

    PopplerPageTransition* copy = poppler_page_transition_copy(nullptr);



    EXPECT_EQ(copy, nullptr);

}
