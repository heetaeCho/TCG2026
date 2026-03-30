// File: poppler-layers-iter-new-test_2248.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

// Forward declarations to match the production signatures/types.
typedef struct _PopplerDocument PopplerDocument;
typedef struct _PopplerLayersIter PopplerLayersIter;

extern "C" {
// Function under test (implemented in poppler-document.cc in the real codebase).
PopplerLayersIter *poppler_layers_iter_new(PopplerDocument *document);

// External collaborator used by poppler_layers_iter_new(). We provide a test double.
GList *_poppler_document_get_layers(PopplerDocument *document);
}  // extern "C"

// ------------------------
// Test double / stub state
// ------------------------
static int g_get_layers_call_count = 0;
static PopplerDocument *g_get_layers_last_doc = nullptr;
static GList *g_get_layers_return_value = nullptr;

extern "C" GList *_poppler_document_get_layers(PopplerDocument *document) {
  ++g_get_layers_call_count;
  g_get_layers_last_doc = document;
  return g_get_layers_return_value;
}

class PopplerLayersIterNewTest_2248 : public ::testing::Test {
protected:
  void SetUp() override {
    g_get_layers_call_count = 0;
    g_get_layers_last_doc = nullptr;
    g_get_layers_return_value = nullptr;
  }

  // Create a valid GObject instance and treat it as a PopplerDocument* for testing purposes.
  // This is sufficient for g_object_ref() usage inside the function under test.
  PopplerDocument *NewDummyDocument() {
    GObject *obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    return reinterpret_cast<PopplerDocument *>(obj);
  }

  void UnrefDummyDocument(PopplerDocument *doc) {
    GObject *obj = reinterpret_cast<GObject *>(doc);
    g_object_unref(obj);
  }
};

TEST_F(PopplerLayersIterNewTest_2248, ReturnsNullWhenGetLayersReturnsNull_2248) {
  PopplerDocument *doc = NewDummyDocument();

  g_get_layers_return_value = nullptr;

  PopplerLayersIter *iter = poppler_layers_iter_new(doc);

  EXPECT_EQ(iter, nullptr);
  EXPECT_EQ(g_get_layers_call_count, 1);
  EXPECT_EQ(g_get_layers_last_doc, doc);

  UnrefDummyDocument(doc);
}

TEST_F(PopplerLayersIterNewTest_2248, ReturnsNonNullWhenGetLayersReturnsNonNull_2248) {
  PopplerDocument *doc = NewDummyDocument();

  // Create a non-empty GList to simulate having layers.
  // We intentionally do not free this list in the test because the iterator may
  // take ownership or expect it to remain valid; that behavior is not exposed
  // via the provided interface.
  GList *layers = nullptr;
  layers = g_list_append(layers, GUINT_TO_POINTER(1));

  g_get_layers_return_value = layers;

  PopplerLayersIter *iter = poppler_layers_iter_new(doc);

  ASSERT_NE(iter, nullptr);
  EXPECT_EQ(g_get_layers_call_count, 1);
  EXPECT_EQ(g_get_layers_last_doc, doc);

  UnrefDummyDocument(doc);
}

TEST_F(PopplerLayersIterNewTest_2248, PassesNullDocumentThroughToGetLayersAndReturnsNullIfNoItems_2248) {
  // Error/boundary case: nullptr document. Behavior is only asserted for the
  // observable path where _poppler_document_get_layers returns nullptr.
  g_get_layers_return_value = nullptr;

  PopplerLayersIter *iter = poppler_layers_iter_new(nullptr);

  EXPECT_EQ(iter, nullptr);
  EXPECT_EQ(g_get_layers_call_count, 1);
  EXPECT_EQ(g_get_layers_last_doc, static_cast<PopplerDocument *>(nullptr));
}

TEST_F(PopplerLayersIterNewTest_2248, CallsGetLayersExactlyOncePerInvocation_2248) {
  PopplerDocument *doc = NewDummyDocument();

  g_get_layers_return_value = nullptr;
  EXPECT_EQ(poppler_layers_iter_new(doc), nullptr);
  EXPECT_EQ(g_get_layers_call_count, 1);

  g_get_layers_return_value = nullptr;
  EXPECT_EQ(poppler_layers_iter_new(doc), nullptr);
  EXPECT_EQ(g_get_layers_call_count, 2);

  UnrefDummyDocument(doc);
}