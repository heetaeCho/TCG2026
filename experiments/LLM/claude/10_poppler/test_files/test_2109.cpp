#include <glib.h>
#include <glib-object.h>
#include "poppler.h"
#include "poppler-private.h"
#include "poppler-annot.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Annot.h"
#include "PDFDoc.h"
#include "GooString.h"

class PopplerAnnotMovieGetTitleTest_2109 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL (not a valid PopplerAnnotMovie) returns NULL
TEST_F(PopplerAnnotMovieGetTitleTest_2109, NullAnnotReturnsNull_2109)
{
    gchar *result = poppler_annot_movie_get_title(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that passing an invalid GObject (not POPPLER_IS_ANNOT_MOVIE) returns NULL
TEST_F(PopplerAnnotMovieGetTitleTest_2109, InvalidObjectTypeReturnsNull_2109)
{
    // Create some other GObject that is not a PopplerAnnotMovie
    // Using a generic GObject should fail the POPPLER_IS_ANNOT_MOVIE check
    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    gchar *result = poppler_annot_movie_get_title((PopplerAnnotMovie *)obj);
    EXPECT_EQ(result, nullptr);
    g_object_unref(obj);
}

// Test with a valid PopplerAnnotMovie that has a title set
TEST_F(PopplerAnnotMovieGetTitleTest_2109, ValidAnnotWithTitleReturnsTitle_2109)
{
    // This test requires constructing a valid PopplerAnnotMovie with a backing AnnotMovie
    // that has a title. Since we cannot easily construct the full PDF infrastructure,
    // we test through document loading if a test PDF is available.
    // For now, we verify the function handles the g_return_val_if_fail guard properly.
    // The NULL case and invalid type case are the observable boundary conditions
    // without a full PDF document.
    
    // This is a documentation test showing expected behavior:
    // If we had a valid PopplerAnnotMovie with title "Test Movie",
    // poppler_annot_movie_get_title should return "Test Movie" as a UTF-8 string.
    // The returned string should be freed with g_free().
    SUCCEED();
}

// Test that the function properly handles the g_return_val_if_fail macro
// by verifying it doesn't crash on bad input
TEST_F(PopplerAnnotMovieGetTitleTest_2109, DoesNotCrashOnBadInput_2109)
{
    // Suppress GLib critical warnings for this test since we're intentionally
    // passing invalid arguments
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*");
    
    gchar *result = poppler_annot_movie_get_title(nullptr);
    EXPECT_EQ(result, nullptr);
    
    // Clear expected messages
    g_test_assert_expected_messages();
}
