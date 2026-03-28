#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Forward declarations and minimal type definitions needed for testing
// Based on the known/inferred dependencies

// We need to define the structures as they appear in the codebase
// PopplerAction is typically a union/struct in poppler's glib bindings

extern "C" {

// Minimal type definitions based on the interface
typedef struct _PopplerAction PopplerAction;
typedef struct _PopplerAnnotScreen PopplerAnnotScreen;

// The struct definition from the known dependencies, extended with the action field
// that the function accesses
struct _PopplerAnnotScreen {
    PopplerAction *action;
};

// Function under test
PopplerAction *poppler_annot_screen_get_action(PopplerAnnotScreen *poppler_annot);

} // extern "C"

class PopplerAnnotScreenTest_2111 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that get_action returns the action that was set in the struct
TEST_F(PopplerAnnotScreenTest_2111, ReturnsActionWhenActionIsSet_2111) {
    PopplerAnnotScreen annot;
    // Create a dummy PopplerAction pointer (we just need a non-null address)
    PopplerAction *dummy_action = reinterpret_cast<PopplerAction *>(0xDEADBEEF);
    annot.action = dummy_action;

    PopplerAction *result = poppler_annot_screen_get_action(&annot);
    EXPECT_EQ(result, dummy_action);
}

// Test that get_action returns NULL when the action field is NULL
TEST_F(PopplerAnnotScreenTest_2111, ReturnsNullWhenActionIsNull_2111) {
    PopplerAnnotScreen annot;
    annot.action = nullptr;

    PopplerAction *result = poppler_annot_screen_get_action(&annot);
    EXPECT_EQ(result, nullptr);
}

// Test that the function returns the exact pointer stored, verifying no copy is made
TEST_F(PopplerAnnotScreenTest_2111, ReturnsSamePointerAsStored_2111) {
    PopplerAnnotScreen annot;
    // Use a stack-allocated dummy to get a real address
    int dummy_storage;
    PopplerAction *action_ptr = reinterpret_cast<PopplerAction *>(&dummy_storage);
    annot.action = action_ptr;

    PopplerAction *result = poppler_annot_screen_get_action(&annot);
    EXPECT_EQ(result, action_ptr);
}

// Test that changing the action field and calling again returns the updated value
TEST_F(PopplerAnnotScreenTest_2111, ReturnsUpdatedActionAfterChange_2111) {
    PopplerAnnotScreen annot;
    PopplerAction *first_action = reinterpret_cast<PopplerAction *>(0x1000);
    PopplerAction *second_action = reinterpret_cast<PopplerAction *>(0x2000);

    annot.action = first_action;
    EXPECT_EQ(poppler_annot_screen_get_action(&annot), first_action);

    annot.action = second_action;
    EXPECT_EQ(poppler_annot_screen_get_action(&annot), second_action);
}

// Test multiple calls return the same result (idempotent)
TEST_F(PopplerAnnotScreenTest_2111, MultipleCallsReturnSameResult_2111) {
    PopplerAnnotScreen annot;
    PopplerAction *action = reinterpret_cast<PopplerAction *>(0xCAFEBABE);
    annot.action = action;

    PopplerAction *result1 = poppler_annot_screen_get_action(&annot);
    PopplerAction *result2 = poppler_annot_screen_get_action(&annot);
    PopplerAction *result3 = poppler_annot_screen_get_action(&annot);

    EXPECT_EQ(result1, action);
    EXPECT_EQ(result2, action);
    EXPECT_EQ(result3, action);
}

// Test with action set to null then to a valid pointer
TEST_F(PopplerAnnotScreenTest_2111, TransitionFromNullToValidAction_2111) {
    PopplerAnnotScreen annot;
    annot.action = nullptr;

    EXPECT_EQ(poppler_annot_screen_get_action(&annot), nullptr);

    PopplerAction *valid_action = reinterpret_cast<PopplerAction *>(0xBEEF);
    annot.action = valid_action;

    EXPECT_EQ(poppler_annot_screen_get_action(&annot), valid_action);
}

// Test with different PopplerAnnotScreen instances
TEST_F(PopplerAnnotScreenTest_2111, DifferentAnnotsReturnDifferentActions_2111) {
    PopplerAnnotScreen annot1;
    PopplerAnnotScreen annot2;

    PopplerAction *action1 = reinterpret_cast<PopplerAction *>(0x1111);
    PopplerAction *action2 = reinterpret_cast<PopplerAction *>(0x2222);

    annot1.action = action1;
    annot2.action = action2;

    EXPECT_EQ(poppler_annot_screen_get_action(&annot1), action1);
    EXPECT_EQ(poppler_annot_screen_get_action(&annot2), action2);
    EXPECT_NE(poppler_annot_screen_get_action(&annot1), poppler_annot_screen_get_action(&annot2));
}
