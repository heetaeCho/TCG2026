#include <gtest/gtest.h>
#include <glib.h>

// Include the necessary headers
extern "C" {
#include "poppler-page.h"
}

// If poppler-page.h doesn't provide the full declarations, we need minimal forward declarations
// Based on the known structure and function signature

// The function under test
extern "C" void poppler_page_transition_free(PopplerPageTransition *transition);

class PopplerPageTransitionFreeTest_2491 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that freeing a valid allocated PopplerPageTransition does not crash
TEST_F(PopplerPageTransitionFreeTest_2491, FreeValidTransition_2491)
{
    PopplerPageTransition *transition = (PopplerPageTransition *)g_malloc0(sizeof(PopplerPageTransition));
    ASSERT_NE(transition, nullptr);

    // Should not crash or cause issues
    EXPECT_NO_FATAL_FAILURE(poppler_page_transition_free(transition));
}

// Test that freeing a NULL pointer does not crash (g_free handles NULL gracefully)
TEST_F(PopplerPageTransitionFreeTest_2491, FreeNullTransition_2491)
{
    EXPECT_NO_FATAL_FAILURE(poppler_page_transition_free(nullptr));
}

// Test that freeing a transition with initialized fields does not crash
TEST_F(PopplerPageTransitionFreeTest_2491, FreeTransitionWithInitializedFields_2491)
{
    PopplerPageTransition *transition = (PopplerPageTransition *)g_malloc0(sizeof(PopplerPageTransition));
    ASSERT_NE(transition, nullptr);

    transition->duration_real = 500;
    transition->scale = 1;
    transition->rectangular = 0;

    EXPECT_NO_FATAL_FAILURE(poppler_page_transition_free(transition));
}

// Test freeing multiple transitions sequentially
TEST_F(PopplerPageTransitionFreeTest_2491, FreeMultipleTransitions_2491)
{
    PopplerPageTransition *t1 = (PopplerPageTransition *)g_malloc0(sizeof(PopplerPageTransition));
    PopplerPageTransition *t2 = (PopplerPageTransition *)g_malloc0(sizeof(PopplerPageTransition));
    PopplerPageTransition *t3 = (PopplerPageTransition *)g_malloc0(sizeof(PopplerPageTransition));

    ASSERT_NE(t1, nullptr);
    ASSERT_NE(t2, nullptr);
    ASSERT_NE(t3, nullptr);

    EXPECT_NO_FATAL_FAILURE(poppler_page_transition_free(t1));
    EXPECT_NO_FATAL_FAILURE(poppler_page_transition_free(t2));
    EXPECT_NO_FATAL_FAILURE(poppler_page_transition_free(t3));
}

// Test that g_new allocated transition can be freed
TEST_F(PopplerPageTransitionFreeTest_2491, FreeGNewAllocatedTransition_2491)
{
    PopplerPageTransition *transition = g_new0(PopplerPageTransition, 1);
    ASSERT_NE(transition, nullptr);

    EXPECT_NO_FATAL_FAILURE(poppler_page_transition_free(transition));
}
