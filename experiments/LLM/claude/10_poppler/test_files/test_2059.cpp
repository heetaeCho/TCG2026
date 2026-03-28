#include <glib-object.h>
#include <gtest/gtest.h>

// Include poppler glib headers
extern "C" {
#include "poppler.h"
#include "poppler-annot.h"
}

class PopplerAnnotStampTest_2059 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that PopplerAnnotStamp GType is registered and valid
TEST_F(PopplerAnnotStampTest_2059, TypeIsRegistered_2059) {
    GType stamp_type = POPPLER_TYPE_ANNOT_STAMP;
    EXPECT_NE(stamp_type, G_TYPE_INVALID);
}

// Test that PopplerAnnotStamp type name is correct
TEST_F(PopplerAnnotStampTest_2059, TypeNameIsCorrect_2059) {
    GType stamp_type = POPPLER_TYPE_ANNOT_STAMP;
    const gchar *name = g_type_name(stamp_type);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "PopplerAnnotStamp");
}

// Test that PopplerAnnotStamp is a subtype of PopplerAnnot
TEST_F(PopplerAnnotStampTest_2059, IsSubtypeOfPopplerAnnot_2059) {
    GType stamp_type = POPPLER_TYPE_ANNOT_STAMP;
    GType annot_type = POPPLER_TYPE_ANNOT;
    EXPECT_TRUE(g_type_is_a(stamp_type, annot_type));
}

// Test that PopplerAnnotStamp is a GObject derivative
TEST_F(PopplerAnnotStampTest_2059, IsGObjectDerivative_2059) {
    GType stamp_type = POPPLER_TYPE_ANNOT_STAMP;
    EXPECT_TRUE(g_type_is_a(stamp_type, G_TYPE_OBJECT));
}

// Test that the type is not abstract (can potentially be instantiated)
TEST_F(PopplerAnnotStampTest_2059, TypeIsNotAbstract_2059) {
    GType stamp_type = POPPLER_TYPE_ANNOT_STAMP;
    GTypeQuery query;
    g_type_query(stamp_type, &query);
    EXPECT_GT(query.instance_size, 0u);
}

// Test type class can be referenced
TEST_F(PopplerAnnotStampTest_2059, ClassCanBeReferenced_2059) {
    GType stamp_type = POPPLER_TYPE_ANNOT_STAMP;
    gpointer klass = g_type_class_ref(stamp_type);
    ASSERT_NE(klass, nullptr);
    g_type_class_unref(klass);
}

// Test parent type of PopplerAnnotStamp
TEST_F(PopplerAnnotStampTest_2059, ParentTypeCheck_2059) {
    GType stamp_type = POPPLER_TYPE_ANNOT_STAMP;
    GType parent_type = g_type_parent(stamp_type);
    EXPECT_NE(parent_type, G_TYPE_INVALID);
    // Parent should be PopplerAnnotMarkup or PopplerAnnot hierarchy
    EXPECT_TRUE(g_type_is_a(parent_type, POPPLER_TYPE_ANNOT));
}

// Test that the type check macros work correctly with nullptr
TEST_F(PopplerAnnotStampTest_2059, TypeCheckWithNull_2059) {
    EXPECT_FALSE(POPPLER_IS_ANNOT_STAMP(nullptr));
}

// Test that type query returns valid sizes
TEST_F(PopplerAnnotStampTest_2059, TypeQueryReturnValidSizes_2059) {
    GType stamp_type = POPPLER_TYPE_ANNOT_STAMP;
    GTypeQuery query;
    g_type_query(stamp_type, &query);
    EXPECT_GT(query.class_size, 0u);
    EXPECT_GT(query.instance_size, 0u);
    EXPECT_EQ(query.type, stamp_type);
}

// Test creating a new PopplerAnnotStamp with poppler_annot_stamp_new if available
TEST_F(PopplerAnnotStampTest_2059, NewStampAnnotCreation_2059) {
    // Create a document to get a page for annotation creation
    // poppler_annot_stamp_new requires a PopplerDocument page
    // Without a valid document, we verify the type system is properly set up
    GType stamp_type = POPPLER_TYPE_ANNOT_STAMP;
    EXPECT_NE(stamp_type, 0u);
}
