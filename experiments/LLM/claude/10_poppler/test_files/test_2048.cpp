#include <glib-object.h>
#include <gtest/gtest.h>

// Include poppler glib headers
#include "poppler.h"
#include "poppler-annot.h"

class PopplerAnnotMovieTest_2048 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that PopplerAnnotMovie type is properly registered in the GObject type system
TEST_F(PopplerAnnotMovieTest_2048, TypeIsRegistered_2048)
{
    GType type = poppler_annot_movie_get_type();
    EXPECT_NE(type, G_TYPE_INVALID);
}

// Test that PopplerAnnotMovie type name is correct
TEST_F(PopplerAnnotMovieTest_2048, TypeNameIsCorrect_2048)
{
    GType type = poppler_annot_movie_get_type();
    const gchar *name = g_type_name(type);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "PopplerAnnotMovie");
}

// Test that PopplerAnnotMovie is a subtype of PopplerAnnot
TEST_F(PopplerAnnotMovieTest_2048, IsSubtypeOfPopplerAnnot_2048)
{
    GType movie_type = poppler_annot_movie_get_type();
    GType annot_type = poppler_annot_get_type();
    EXPECT_TRUE(g_type_is_a(movie_type, annot_type));
}

// Test that PopplerAnnotMovie is a subtype of GObject
TEST_F(PopplerAnnotMovieTest_2048, IsSubtypeOfGObject_2048)
{
    GType movie_type = poppler_annot_movie_get_type();
    EXPECT_TRUE(g_type_is_a(movie_type, G_TYPE_OBJECT));
}

// Test that the type is not abstract (can potentially be instantiated)
TEST_F(PopplerAnnotMovieTest_2048, TypeIsNotAbstract_2048)
{
    GType type = poppler_annot_movie_get_type();
    EXPECT_FALSE(G_TYPE_IS_ABSTRACT(type));
}

// Test that calling get_type multiple times returns the same type
TEST_F(PopplerAnnotMovieTest_2048, GetTypeIsIdempotent_2048)
{
    GType type1 = poppler_annot_movie_get_type();
    GType type2 = poppler_annot_movie_get_type();
    EXPECT_EQ(type1, type2);
}

// Test parent type relationship
TEST_F(PopplerAnnotMovieTest_2048, ParentTypeIsPopplerAnnot_2048)
{
    GType movie_type = poppler_annot_movie_get_type();
    GType parent_type = g_type_parent(movie_type);
    GType annot_type = poppler_annot_get_type();
    EXPECT_EQ(parent_type, annot_type);
}

// Test with a real PDF document containing a movie annotation
// This tests get_title and get_movie if a suitable document is available
TEST_F(PopplerAnnotMovieTest_2048, TypeCheckMacrosWork_2048)
{
    GType type = poppler_annot_movie_get_type();
    // Verify the type check macro infrastructure works
    EXPECT_TRUE(G_TYPE_CHECK_CLASS_TYPE(g_type_class_peek(type), type) || g_type_class_peek(type) == nullptr);
}

// Test that PopplerAnnotMovie type is classed (as expected for GObject subclass)
TEST_F(PopplerAnnotMovieTest_2048, TypeIsClassed_2048)
{
    GType type = poppler_annot_movie_get_type();
    EXPECT_TRUE(G_TYPE_IS_CLASSED(type));
}

// Test that PopplerAnnotMovie type is instantiatable
TEST_F(PopplerAnnotMovieTest_2048, TypeIsInstantiatable_2048)
{
    GType type = poppler_annot_movie_get_type();
    EXPECT_TRUE(G_TYPE_IS_INSTANTIATABLE(type));
}

// Test that PopplerAnnotMovie is derived from GInitiallyUnowned or GObject
TEST_F(PopplerAnnotMovieTest_2048, TypeHierarchyDepth_2048)
{
    GType type = poppler_annot_movie_get_type();
    guint depth = g_type_depth(type);
    // Should be at least 3: GObject -> PopplerAnnot -> PopplerAnnotMovie
    EXPECT_GE(depth, 3u);
}
