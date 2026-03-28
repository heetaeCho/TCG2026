#include <gtest/gtest.h>

extern "C" {
#include <glib.h>

typedef struct _PopplerPageTransition PopplerPageTransition;

struct _PopplerPageTransition
{
    int type;
    int alignment;
    int direction;
    int duration;
    int angle;
    double scale;
    gboolean rectangular;
};

PopplerPageTransition *poppler_page_transition_new(void);
}

class PopplerPageTransitionTest_2489 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any allocated transitions
    }
};

TEST_F(PopplerPageTransitionTest_2489, NewReturnsNonNull_2489) {
    PopplerPageTransition *transition = poppler_page_transition_new();
    ASSERT_NE(transition, nullptr);
    g_free(transition);
}

TEST_F(PopplerPageTransitionTest_2489, NewReturnsZeroInitializedMemory_2489) {
    PopplerPageTransition *transition = poppler_page_transition_new();
    ASSERT_NE(transition, nullptr);

    // g_new0 should zero-initialize all fields
    EXPECT_EQ(transition->type, 0);
    EXPECT_EQ(transition->alignment, 0);
    EXPECT_EQ(transition->direction, 0);
    EXPECT_EQ(transition->duration, 0);
    EXPECT_EQ(transition->angle, 0);
    EXPECT_DOUBLE_EQ(transition->scale, 0.0);
    EXPECT_EQ(transition->rectangular, FALSE);

    g_free(transition);
}

TEST_F(PopplerPageTransitionTest_2489, MultipleAllocationsReturnDistinctPointers_2489) {
    PopplerPageTransition *t1 = poppler_page_transition_new();
    PopplerPageTransition *t2 = poppler_page_transition_new();

    ASSERT_NE(t1, nullptr);
    ASSERT_NE(t2, nullptr);
    EXPECT_NE(t1, t2);

    g_free(t1);
    g_free(t2);
}

TEST_F(PopplerPageTransitionTest_2489, AllocatedMemoryIsWritable_2489) {
    PopplerPageTransition *transition = poppler_page_transition_new();
    ASSERT_NE(transition, nullptr);

    // Verify we can write to the allocated memory without issues
    transition->type = 5;
    transition->alignment = 1;
    transition->direction = 2;
    transition->duration = 3000;
    transition->angle = 90;
    transition->scale = 1.5;
    transition->rectangular = TRUE;

    EXPECT_EQ(transition->type, 5);
    EXPECT_EQ(transition->alignment, 1);
    EXPECT_EQ(transition->direction, 2);
    EXPECT_EQ(transition->duration, 3000);
    EXPECT_EQ(transition->angle, 90);
    EXPECT_DOUBLE_EQ(transition->scale, 1.5);
    EXPECT_EQ(transition->rectangular, TRUE);

    g_free(transition);
}

TEST_F(PopplerPageTransitionTest_2489, ManyAllocationsSucceed_2489) {
    const int count = 100;
    PopplerPageTransition *transitions[count];

    for (int i = 0; i < count; i++) {
        transitions[i] = poppler_page_transition_new();
        ASSERT_NE(transitions[i], nullptr) << "Allocation failed at index " << i;
    }

    // All should be zero-initialized
    for (int i = 0; i < count; i++) {
        EXPECT_EQ(transitions[i]->type, 0);
        EXPECT_EQ(transitions[i]->duration, 0);
    }

    for (int i = 0; i < count; i++) {
        g_free(transitions[i]);
    }
}
