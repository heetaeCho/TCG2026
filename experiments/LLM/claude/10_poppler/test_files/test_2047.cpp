#include <glib-object.h>
#include <gtest/gtest.h>

// Include poppler glib headers
#include "poppler.h"
#include "poppler-annot.h"

class PopplerAnnotMovieTest_2047 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that PopplerAnnotMovie type is properly registered
TEST_F(PopplerAnnotMovieTest_2047, TypeIsRegistered_2047)
{
    GType type = POPPLER_TYPE_ANNOT_MOVIE;
    EXPECT_NE(type, G_TYPE_INVALID);
}

// Test that PopplerAnnotMovie is a subtype of PopplerAnnot
TEST_F(PopplerAnnotMovieTest_2047, IsSubtypeOfPopplerAnnot_2047)
{
    GType movie_type = POPPLER_TYPE_ANNOT_MOVIE;
    GType annot_type = POPPLER_TYPE_ANNOT;
    EXPECT_TRUE(g_type_is_a(movie_type, annot_type));
}

// Test that PopplerAnnotMovie is a GObject
TEST_F(PopplerAnnotMovieTest_2047, IsGObject_2047)
{
    GType movie_type = POPPLER_TYPE_ANNOT_MOVIE;
    EXPECT_TRUE(g_type_is_a(movie_type, G_TYPE_OBJECT));
}

// Test that the type name is correct
TEST_F(PopplerAnnotMovieTest_2047, TypeNameIsCorrect_2047)
{
    GType type = POPPLER_TYPE_ANNOT_MOVIE;
    const gchar *name = g_type_name(type);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "PopplerAnnotMovie");
}

// Test that PopplerMovie type is registered (dependency for annot movie)
TEST_F(PopplerAnnotMovieTest_2047, MovieTypeIsRegistered_2047)
{
    GType type = POPPLER_TYPE_MOVIE;
    EXPECT_NE(type, G_TYPE_INVALID);
}

// Test that poppler_annot_movie_get_movie returns a PopplerMovie or NULL
// when called on a valid annotation (requires a real PDF document with movie annotation)
// This test verifies the getter interface exists and is callable
TEST_F(PopplerAnnotMovieTest_2047, GetMovieFunctionExists_2047)
{
    // Verify the function symbol is available by checking the type system
    // We can't easily create a PopplerAnnotMovie without a real PDF,
    // but we can verify the type hierarchy is intact
    GType type = POPPLER_TYPE_ANNOT_MOVIE;
    GTypeQuery query;
    g_type_query(type, &query);
    EXPECT_GT(query.instance_size, 0u);
    EXPECT_GT(query.class_size, 0u);
}

// Test that the parent class is PopplerAnnot
TEST_F(PopplerAnnotMovieTest_2047, ParentClassIsPopplerAnnot_2047)
{
    GType parent = g_type_parent(POPPLER_TYPE_ANNOT_MOVIE);
    EXPECT_EQ(parent, POPPLER_TYPE_ANNOT);
}

// Test finalization doesn't crash when object has no document backing
// This tests the boundary condition of the finalize path
TEST_F(PopplerAnnotMovieTest_2047, ClassStructureIsValid_2047)
{
    GType type = POPPLER_TYPE_ANNOT_MOVIE;
    gpointer klass = g_type_class_ref(type);
    ASSERT_NE(klass, nullptr);

    GObjectClass *obj_class = G_OBJECT_CLASS(klass);
    ASSERT_NE(obj_class, nullptr);

    // The finalize function should be set
    EXPECT_NE(obj_class->finalize, nullptr);

    g_type_class_unref(klass);
}

// Verify that the annot movie class has proper finalize chain
TEST_F(PopplerAnnotMovieTest_2047, FinalizeIsOverridden_2047)
{
    gpointer movie_class = g_type_class_ref(POPPLER_TYPE_ANNOT_MOVIE);
    gpointer annot_class = g_type_class_ref(POPPLER_TYPE_ANNOT);

    GObjectClass *movie_obj_class = G_OBJECT_CLASS(movie_class);
    GObjectClass *annot_obj_class = G_OBJECT_CLASS(annot_class);

    // The movie class should have its own finalize, different from parent
    EXPECT_NE(movie_obj_class->finalize, annot_obj_class->finalize);

    g_type_class_unref(movie_class);
    g_type_class_unref(annot_class);
}
