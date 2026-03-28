#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <glib-object.h>

// Forward declarations for poppler types and functions used in tests
typedef struct _PopplerDocument PopplerDocument;
typedef struct _PopplerLayersIter PopplerLayersIter;

// Functions under test
void poppler_layers_iter_free(PopplerLayersIter *iter);

// Functions needed for setup
PopplerDocument *poppler_document_new_from_file(const char *uri, const char *password, GError **error);
PopplerLayersIter *poppler_layers_iter_new(PopplerDocument *document);
PopplerLayersIter *poppler_layers_iter_copy(PopplerLayersIter *iter);
}

class PopplerLayersIterFreeTest_2247 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing nullptr to poppler_layers_iter_free does not crash
TEST_F(PopplerLayersIterFreeTest_2247, FreeNullIterDoesNotCrash_2247)
{
    // Passing NULL should be a no-op and not crash
    EXPECT_NO_FATAL_FAILURE(poppler_layers_iter_free(nullptr));
}

// Test that passing NULL (C-style) also does not crash
TEST_F(PopplerLayersIterFreeTest_2247, FreeNULLMacroDoesNotCrash_2247)
{
    PopplerLayersIter *iter = NULL;
    EXPECT_NO_FATAL_FAILURE(poppler_layers_iter_free(iter));
}

// Test that calling free with nullptr multiple times does not crash
TEST_F(PopplerLayersIterFreeTest_2247, FreeNullMultipleTimesDoesNotCrash_2247)
{
    EXPECT_NO_FATAL_FAILURE({
        poppler_layers_iter_free(nullptr);
        poppler_layers_iter_free(nullptr);
        poppler_layers_iter_free(nullptr);
    });
}
