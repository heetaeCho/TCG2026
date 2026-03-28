#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib-object.h>

// Mocked structures and functions
struct PopplerAnnotStampClass {
    GObjectClass parent_class;
};

void poppler_annot_stamp_finalize(GObject *object) {
    // Mocked finalize behavior, assuming it does something in your actual implementation
}

// The function under test
static void poppler_annot_stamp_class_init(PopplerAnnotStampClass *klass) {
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    gobject_class->finalize = poppler_annot_stamp_finalize;
}

// Test Suite for poppler_annot_stamp_class_init
TEST_F(PopplerAnnotStampClassInitTest_2059, TestFinalizeAssignedCorrectly_2059) {
    // Setup a PopplerAnnotStampClass mock object
    PopplerAnnotStampClass klass;

    // Invoke the method under test
    poppler_annot_stamp_class_init(&klass);

    // Verify that the finalize function was assigned correctly
    ASSERT_EQ(klass.parent_class.finalize, poppler_annot_stamp_finalize);
}

TEST_F(PopplerAnnotStampClassInitTest_2059, TestFinalizeNotNull_2059) {
    // Setup a PopplerAnnotStampClass mock object
    PopplerAnnotStampClass klass;

    // Invoke the method under test
    poppler_annot_stamp_class_init(&klass);

    // Check that finalize is not a null pointer after initialization
    ASSERT_NE(klass.parent_class.finalize, nullptr);
}

TEST_F(PopplerAnnotStampClassInitTest_2059, TestFinalizeIsOverwritten_2059) {
    // Setup a PopplerAnnotStampClass mock object with a non-null finalize
    PopplerAnnotStampClass klass;
    klass.parent_class.finalize = reinterpret_cast<GFinalizeFunc>(0x12345678);

    // Invoke the method under test
    poppler_annot_stamp_class_init(&klass);

    // Verify that the finalize function has been overwritten
    ASSERT_EQ(klass.parent_class.finalize, poppler_annot_stamp_finalize);
}

TEST_F(PopplerAnnotStampClassInitTest_2059, TestClassInitWithNull_2059) {
    // Handle exceptional case where class is null (if applicable)
    PopplerAnnotStampClass* klass = nullptr;

    // Just call it with nullptr to test that no crash occurs (assuming it's safe)
    ASSERT_NO_THROW(poppler_annot_stamp_class_init(klass));
}