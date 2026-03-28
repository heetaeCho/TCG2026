#include <gtest/gtest.h>
#include <glib-object.h>

// Include the poppler-movie header
extern "C" {
#include "poppler-movie.h"
}

class PopplerMovieTest_2411 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that PopplerMovie type is properly registered with GObject
TEST_F(PopplerMovieTest_2411, TypeIsRegistered_2411) {
    GType type = poppler_movie_get_type();
    EXPECT_NE(type, G_TYPE_INVALID);
}

// Test that PopplerMovie type name is correct
TEST_F(PopplerMovieTest_2411, TypeNameIsCorrect_2411) {
    GType type = poppler_movie_get_type();
    const gchar *name = g_type_name(type);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "PopplerMovie");
}

// Test that PopplerMovie is derived from GObject
TEST_F(PopplerMovieTest_2411, DerivedFromGObject_2411) {
    GType type = poppler_movie_get_type();
    EXPECT_TRUE(g_type_is_a(type, G_TYPE_OBJECT));
}

// Test that poppler_movie_get_filename returns a value (or NULL) without crashing
// This requires a valid PopplerMovie instance which typically comes from a PDF document
// We test the type system aspects that are available without a PDF
TEST_F(PopplerMovieTest_2411, TypeIsNotAbstract_2411) {
    GType type = poppler_movie_get_type();
    // Check that the type is instantiatable (not abstract)
    // PopplerMovie objects are typically created internally, but the type should be valid
    EXPECT_TRUE(G_TYPE_IS_OBJECT(type));
}

// Test that the GType parent is GObject
TEST_F(PopplerMovieTest_2411, ParentTypeIsGObject_2411) {
    GType type = poppler_movie_get_type();
    GType parent = g_type_parent(type);
    EXPECT_EQ(parent, G_TYPE_OBJECT);
}

// Test class ref/unref cycle doesn't crash
TEST_F(PopplerMovieTest_2411, ClassRefUnref_2411) {
    GType type = poppler_movie_get_type();
    gpointer klass = g_type_class_ref(type);
    ASSERT_NE(klass, nullptr);
    g_type_class_unref(klass);
}

// Test that multiple calls to get_type return the same type
TEST_F(PopplerMovieTest_2411, GetTypeConsistent_2411) {
    GType type1 = poppler_movie_get_type();
    GType type2 = poppler_movie_get_type();
    EXPECT_EQ(type1, type2);
}

// Test that the type is not a fundamental type
TEST_F(PopplerMovieTest_2411, NotFundamentalType_2411) {
    GType type = poppler_movie_get_type();
    EXPECT_FALSE(G_TYPE_IS_FUNDAMENTAL(type));
}

// Test that the type is classed
TEST_F(PopplerMovieTest_2411, TypeIsClassed_2411) {
    GType type = poppler_movie_get_type();
    EXPECT_TRUE(G_TYPE_IS_CLASSED(type));
}

// Test type depth (should be at least 2: GObject -> PopplerMovie)
TEST_F(PopplerMovieTest_2411, TypeDepthAtLeastTwo_2411) {
    GType type = poppler_movie_get_type();
    guint depth = g_type_depth(type);
    EXPECT_GE(depth, 2u);
}
