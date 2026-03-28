// poppler_layers_iter_copy_test_2246.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <fstream>
#include <string>
#include <vector>

#include <poppler.h>

// Function under test (implemented in poppler-document.cc)
extern "C" PopplerLayersIter *poppler_layers_iter_copy(PopplerLayersIter *iter);

namespace {

static void Append(std::string &out, const std::string &s) { out += s; }

static std::string BuildMinimalPdfWithOneLayer()
{
  // Build a minimal PDF that includes one Optional Content Group (layer).
  //
  // Objects:
  // 1: Catalog with /OCProperties
  // 2: Pages
  // 3: Page with /Properties mapping /OC1 -> 4 0 R and /Contents 6 0 R
  // 4: OCG (Layer 1)
  // 5: OCProperties dictionary
  // 6: Content stream with marked-content for the layer (/OC /OC1 BDC ... EMC)
  //
  // NOTE: This is just a small PDF fixture generator for the tests.

  struct Obj {
    int num;
    std::string body; // includes "<< >>" / stream etc, but not "n 0 obj" wrapper
  };

  const std::string stream_data = "/OC /OC1 BDC\nEMC\n";

  std::vector<Obj> objs;
  objs.push_back(
      {1,
       "<< /Type /Catalog /Pages 2 0 R /OCProperties 5 0 R >>\n"});
  objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"});
  objs.push_back(
      {3,
       "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
       "   /Resources << /Properties << /OC1 4 0 R >> >>\n"
       "   /Contents 6 0 R >>\n"});
  objs.push_back({4, "<< /Type /OCG /Name (Layer 1) >>\n"});
  objs.push_back(
      {5,
       "<< /OCGs [4 0 R]\n"
       "   /D << /Order [4 0 R] >> >>\n"});
  {
    std::string body;
    Append(body, "<< /Length ");
    Append(body, std::to_string(stream_data.size()));
    Append(body, " >>\nstream\n");
    Append(body, stream_data);
    Append(body, "endstream\n");
    objs.push_back({6, body});
  }

  std::string pdf;
  Append(pdf, "%PDF-1.5\n");
  Append(pdf, "%\xE2\xE3\xCF\xD3\n"); // binary comment

  // Offsets: xref requires byte offsets for each object starting at "n 0 obj"
  std::vector<size_t> offsets;
  offsets.resize(7, 0); // 0..6 (0 is special)

  for (const auto &o : objs) {
    offsets[o.num] = pdf.size();
    Append(pdf, std::to_string(o.num));
    Append(pdf, " 0 obj\n");
    Append(pdf, o.body);
    Append(pdf, "endobj\n");
  }

  const size_t xref_offset = pdf.size();

  Append(pdf, "xref\n");
  Append(pdf, "0 7\n");
  Append(pdf, "0000000000 65535 f \n");
  for (int i = 1; i <= 6; ++i) {
    char buf[32];
    // 10-digit, zero-padded offset
    g_snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offsets[i]);
    Append(pdf, buf);
  }

  Append(pdf, "trailer\n");
  Append(pdf, "<< /Size 7 /Root 1 0 R >>\n");
  Append(pdf, "startxref\n");
  Append(pdf, std::to_string(xref_offset));
  Append(pdf, "\n%%EOF\n");

  return pdf;
}

static std::string WritePdfToTempFileAndGetFileUri()
{
  const std::string pdf = BuildMinimalPdfWithOneLayer();

  gchar *tmp_dir = g_dir_make_tmp("poppler-layer-iter-XXXXXX", nullptr);
  EXPECT_NE(tmp_dir, nullptr);

  gchar *path = g_build_filename(tmp_dir, "layer.pdf", nullptr);

  {
    std::ofstream ofs(path, std::ios::binary);
    EXPECT_TRUE(ofs.good());
    ofs.write(pdf.data(), static_cast<std::streamsize>(pdf.size()));
    EXPECT_TRUE(ofs.good());
  }

  gchar *uri = g_filename_to_uri(path, nullptr, nullptr);
  EXPECT_NE(uri, nullptr);

  std::string out_uri(uri);

  g_free(uri);
  g_free(path);
  g_rmdir(tmp_dir); // directory will only be removed if empty; fine either way
  g_free(tmp_dir);

  return out_uri;
}

struct WeakNotifyState {
  bool finalized = false;
};

static void OnWeakNotify(gpointer data, GObject * /*where_the_object_was*/)
{
  auto *state = static_cast<WeakNotifyState *>(data);
  state->finalized = true;
}

class PopplerLayersIterCopyTest_2246 : public ::testing::Test {
protected:
  void SetUp() override
  {
    uri_ = WritePdfToTempFileAndGetFileUri();

    GError *error = nullptr;
    doc_ = poppler_document_new_from_file(uri_.c_str(), /*password*/ nullptr, &error);
    ASSERT_NE(doc_, nullptr) << (error ? error->message : "unknown error");
    if (error) {
      g_error_free(error);
      error = nullptr;
    }
  }

  void TearDown() override
  {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
  }

  std::string uri_;
  PopplerDocument *doc_ = nullptr;
};

} // namespace

TEST_F(PopplerLayersIterCopyTest_2246, NullIterReturnsNull_2246)
{
  EXPECT_EQ(poppler_layers_iter_copy(nullptr), nullptr);
}

TEST_F(PopplerLayersIterCopyTest_2246, CopyProducesDistinctIteratorPointer_2246)
{
  // Obtain an iterator through the public API (no direct struct access).
  PopplerLayersIter *iter = poppler_layers_iter_new(doc_);
  ASSERT_NE(iter, nullptr);

  PopplerLayersIter *copy = poppler_layers_iter_copy(iter);
  ASSERT_NE(copy, nullptr);

  // Observable behavior: returned iterator pointer should be a distinct allocation.
  EXPECT_NE(copy, iter);

  // Cleanup
  poppler_layers_iter_free(copy);
  poppler_layers_iter_free(iter);
}

TEST_F(PopplerLayersIterCopyTest_2246, CopyPreservesCurrentLayerAtTimeOfCopy_2246)
{
  PopplerLayersIter *iter = poppler_layers_iter_new(doc_);
  ASSERT_NE(iter, nullptr);

  // Capture the current layer from the original iterator.
  PopplerLayer *layer_before = poppler_layers_iter_get_layer(iter);
  ASSERT_NE(layer_before, nullptr);

  PopplerLayersIter *copy = poppler_layers_iter_copy(iter);
  ASSERT_NE(copy, nullptr);

  PopplerLayer *layer_copy = poppler_layers_iter_get_layer(copy);
  ASSERT_NE(layer_copy, nullptr);

  // We don't assume internal identity semantics; compare a stable observable property if available.
  // Title is a public getter on PopplerLayer.
  gchar *title_before = poppler_layer_get_title(layer_before);
  gchar *title_copy = poppler_layer_get_title(layer_copy);

  ASSERT_NE(title_before, nullptr);
  ASSERT_NE(title_copy, nullptr);
  EXPECT_STREQ(title_before, title_copy);

  g_free(title_before);
  g_free(title_copy);

  poppler_layers_iter_free(copy);
  poppler_layers_iter_free(iter);
}

TEST_F(PopplerLayersIterCopyTest_2246, CopyHoldsAdditionalReferenceToDocument_2246)
{
  // This verifies the externally observable effect of g_object_ref(new_iter->document):
  // the PopplerDocument should remain alive after freeing the original iterator,
  // and only be finalized after freeing the copied iterator too (once we drop our own ref).

  WeakNotifyState state;
  g_object_weak_ref(G_OBJECT(doc_), OnWeakNotify, &state);

  PopplerLayersIter *iter = poppler_layers_iter_new(doc_);
  ASSERT_NE(iter, nullptr);

  PopplerLayersIter *copy = poppler_layers_iter_copy(iter);
  ASSERT_NE(copy, nullptr);

  // Drop our direct ref; now only iter/copy should keep the document alive.
  g_object_unref(doc_);
  doc_ = nullptr;

  EXPECT_FALSE(state.finalized);

  // Free original iterator. If copy did NOT take an extra ref, doc could finalize here.
  poppler_layers_iter_free(iter);
  EXPECT_FALSE(state.finalized);

  // Now free the copy; doc should be allowed to finalize (weak notify flips the flag).
  poppler_layers_iter_free(copy);
  EXPECT_TRUE(state.finalized);
}

TEST_F(PopplerLayersIterCopyTest_2246, CopyAndAdvanceOriginalDoNotCrash_2246)
{
  // Boundary-ish: basic independence/robustness check without assuming exact iteration semantics.
  PopplerLayersIter *iter = poppler_layers_iter_new(doc_);
  ASSERT_NE(iter, nullptr);

  PopplerLayersIter *copy = poppler_layers_iter_copy(iter);
  ASSERT_NE(copy, nullptr);

  // Advance original (whether it returns TRUE/FALSE depends on content; we only assert no crash).
  (void)poppler_layers_iter_next(iter);

  // Both iterators should still be usable for simple calls.
  (void)poppler_layers_iter_get_layer(iter);
  (void)poppler_layers_iter_get_layer(copy);

  poppler_layers_iter_free(copy);
  poppler_layers_iter_free(iter);
}