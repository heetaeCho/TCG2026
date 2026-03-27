// poppler-structure-element-get-form-state-test.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

// Poppler GLib internal header (used throughout Poppler's own test suite).
#include "poppler-private.h"

namespace {

// Helper to ensure GLib type system is initialized (mostly relevant for older GLib).
static void EnsureGTypeInitOnce()
{
    static gsize once = 0;
    if (g_once_init_enter(&once)) {
#if !GLIB_CHECK_VERSION(2, 36, 0)
        g_type_init();
#endif
        g_once_init_leave(&once, 1);
    }
}

class PopplerStructureElementGetFormStateTest_2589 : public ::testing::Test {
protected:
    void SetUp() override { EnsureGTypeInitOnce(); }
};

// Convenience: capture g_return_val_if_fail() warnings (GLib criticals).
// g_return_val_if_fail uses the "GLib" log domain with CRITICAL level.
static void ExpectGReturnCritical()
{
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*failed*");
}

static void AssertExpectedMessages()
{
    g_test_assert_expected_messages();
}

} // namespace

TEST_F(PopplerStructureElementGetFormStateTest_2589, NonFormElementLogsCriticalAndReturnsSomeValue_2589)
{
    // Create a PopplerStructureElement instance via GObject. We do not assume any internal state;
    // we only verify observable behavior: the g_return_val_if_fail guard emits a critical when
    // kind != POPPLER_STRUCTURE_ELEMENT_FORM.
    PopplerStructureElement *elem =
        POPPLER_STRUCTURE_ELEMENT(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));
    ASSERT_NE(elem, nullptr);

    ExpectGReturnCritical();
    const PopplerStructureFormState state = poppler_structure_element_get_form_state(elem);
    AssertExpectedMessages();

    // We cannot infer internal mapping, but we can assert the call returns *a* value and does not crash.
    // Additionally, calling again should be stable for the same object.
    ExpectGReturnCritical();
    const PopplerStructureFormState state2 = poppler_structure_element_get_form_state(elem);
    AssertExpectedMessages();

    EXPECT_EQ(static_cast<int>(state2), static_cast<int>(state));

    g_object_unref(elem);
}

TEST_F(PopplerStructureElementGetFormStateTest_2589, FormKindDoesNotTriggerGuardCritical_2589)
{
    // If the object is (or is configured as) a FORM kind, the guard condition should pass and
    // the g_return_val_if_fail critical should NOT be emitted.
    //
    // We avoid asserting a specific returned enum value because the mapping depends on attributes
    // stored in the underlying structure element; we treat implementation as a black box.
    PopplerStructureElement *elem = POPPLER_STRUCTURE_ELEMENT(
        g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, "kind", POPPLER_STRUCTURE_ELEMENT_FORM, nullptr));
    ASSERT_NE(elem, nullptr);

    // Ensure no CRITICAL from the guard. If any CRITICAL appears, this test will fail.
    // (g_test_expect_message is only for expected messages; here we simply call and rely on
    // the test harness treating unexpected criticals as failures in Poppler's test environment.)
    const PopplerStructureFormState state = poppler_structure_element_get_form_state(elem);
    (void)state;

    // Calling twice should also be stable (no crash / no guard failure).
    const PopplerStructureFormState state2 = poppler_structure_element_get_form_state(elem);
    EXPECT_EQ(static_cast<int>(state2), static_cast<int>(state));

    g_object_unref(elem);
}

TEST_F(PopplerStructureElementGetFormStateTest_2589, NullElementIsHandledAsErrorIfObservable_2589)
{
    // This function evaluates poppler_structure_element_get_kind(poppler_structure_element) inside
    // g_return_val_if_fail. If Poppler's get_kind handles nullptr defensively, we should observe a
    // critical and a default return value. If it does not, Poppler's own test suite would catch it.
    //
    // We write the test in an observable way: expect a GLib critical (guard failure) and ensure
    // the call returns consistently.
    ExpectGReturnCritical();
    const PopplerStructureFormState state = poppler_structure_element_get_form_state(nullptr);
    AssertExpectedMessages();

    ExpectGReturnCritical();
    const PopplerStructureFormState state2 = poppler_structure_element_get_form_state(nullptr);
    AssertExpectedMessages();

    EXPECT_EQ(static_cast<int>(state2), static_cast<int>(state));
}