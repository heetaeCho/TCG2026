#include <gtest/gtest.h>
#include <glib-object.h>

// Include the poppler glib headers
extern "C" {
#include "poppler.h"
#include "poppler-document.h"
#include "poppler-page.h"
#include "poppler-annot.h"
}

class PopplerAnnotScreenTest_2051 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that PopplerAnnotScreen type is properly registered in the GObject type system
TEST_F(PopplerAnnotScreenTest_2051, TypeIsRegistered_2051)
{
    GType type = poppler_annot_screen_get_type();
    EXPECT_NE(type, G_TYPE_INVALID);
}

// Test that PopplerAnnotScreen type name is correct
TEST_F(PopplerAnnotScreenTest_2051, TypeNameIsCorrect_2051)
{
    GType type = poppler_annot_screen_get_type();
    const gchar *name = g_type_name(type);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "PopplerAnnotScreen");
}

// Test that PopplerAnnotScreen is a subtype of PopplerAnnot
TEST_F(PopplerAnnotScreenTest_2051, IsSubtypeOfPopplerAnnot_2051)
{
    GType screen_type = poppler_annot_screen_get_type();
    GType annot_type = poppler_annot_get_type();
    EXPECT_TRUE(g_type_is_a(screen_type, annot_type));
}

// Test that PopplerAnnotScreen is a subtype of GObject
TEST_F(PopplerAnnotScreenTest_2051, IsSubtypeOfGObject_2051)
{
    GType screen_type = poppler_annot_screen_get_type();
    EXPECT_TRUE(g_type_is_a(screen_type, G_TYPE_OBJECT));
}

// Test that the parent type of PopplerAnnotScreen is PopplerAnnot
TEST_F(PopplerAnnotScreenTest_2051, ParentTypeIsPopplerAnnot_2051)
{
    GType screen_type = poppler_annot_screen_get_type();
    GType parent_type = g_type_parent(screen_type);
    GType annot_type = poppler_annot_get_type();
    EXPECT_EQ(parent_type, annot_type);
}

// Test that calling get_type multiple times returns the same type
TEST_F(PopplerAnnotScreenTest_2051, GetTypeIsIdempotent_2051)
{
    GType type1 = poppler_annot_screen_get_type();
    GType type2 = poppler_annot_screen_get_type();
    EXPECT_EQ(type1, type2);
}

// Test that PopplerAnnotScreen class can be referenced and unreferenced
TEST_F(PopplerAnnotScreenTest_2051, ClassRefUnref_2051)
{
    GType type = poppler_annot_screen_get_type();
    gpointer klass = g_type_class_ref(type);
    ASSERT_NE(klass, nullptr);
    g_type_class_unref(klass);
}

// Test that PopplerAnnotScreen type is not abstract (it's instantiatable in principle)
TEST_F(PopplerAnnotScreenTest_2051, TypeIsNotAbstract_2051)
{
    GType type = poppler_annot_screen_get_type();
    EXPECT_FALSE(G_TYPE_IS_ABSTRACT(type));
}

// Test basic annotation functionality through a real PDF document with screen annotations
// Since we can't easily create a PopplerAnnotScreen without a PDF, we test the type system aspects
TEST_F(PopplerAnnotScreenTest_2051, TypeFundamentalIsGObject_2051)
{
    GType type = poppler_annot_screen_get_type();
    GType fundamental = G_TYPE_FUNDAMENTAL(type);
    EXPECT_EQ(fundamental, G_TYPE_OBJECT);
}

// Test that the class has a finalize function set (indirectly by checking class structure integrity)
TEST_F(PopplerAnnotScreenTest_2051, ClassInitializationIntegrity_2051)
{
    GType type = poppler_annot_screen_get_type();
    GObjectClass *klass = static_cast<GObjectClass *>(g_type_class_ref(type));
    ASSERT_NE(klass, nullptr);
    // The finalize function should be set by class_init
    EXPECT_NE(klass->finalize, nullptr);
    g_type_class_unref(klass);
}

// Test that PopplerAnnotScreen's finalize differs from base GObject finalize
TEST_F(PopplerAnnotScreenTest_2051, FinalizeIsOverridden_2051)
{
    GType screen_type = poppler_annot_screen_get_type();
    GObjectClass *screen_klass = static_cast<GObjectClass *>(g_type_class_ref(screen_type));
    
    GObjectClass *gobject_klass = static_cast<GObjectClass *>(g_type_class_ref(G_TYPE_OBJECT));
    
    ASSERT_NE(screen_klass, nullptr);
    ASSERT_NE(gobject_klass, nullptr);
    
    // The screen class should have its own finalize, different from the base GObject
    EXPECT_NE(screen_klass->finalize, gobject_klass->finalize);
    
    g_type_class_unref(screen_klass);
    g_type_class_unref(gobject_klass);
}
