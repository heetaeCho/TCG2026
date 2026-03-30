// poppler_structure_element_get_table_border_style_test_2574.cc
#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
#include <poppler.h>
}

// We only rely on the public/installed Poppler GLib headers. No private state access.

namespace {

struct LogCapture {
  guint handler_id = 0;
  int critical_count = 0;
  GLogLevelFlags last_level = static_cast<GLogLevelFlags>(0);
  gchar *last_domain = nullptr;
  gchar *last_message = nullptr;

  static void Handler(const gchar *log_domain,
                      GLogLevelFlags log_level,
                      const gchar *message,
                      gpointer user_data) {
    auto *self = static_cast<LogCapture *>(user_data);
    self->last_level = log_level;

    g_free(self->last_domain);
    g_free(self->last_message);
    self->last_domain = g_strdup(log_domain ? log_domain : "");
    self->last_message = g_strdup(message ? message : "");

    if (log_level & G_LOG_LEVEL_CRITICAL) {
      self->critical_count++;
    }
  }

  void Install(const char *domain) {
    // Capture criticals (and warnings) so g_return_if_fail does not abort.
    handler_id = g_log_set_handler(domain,
                                   static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL |
                                                               G_LOG_LEVEL_WARNING |
                                                               G_LOG_LEVEL_MESSAGE |
                                                               G_LOG_LEVEL_INFO |
                                                               G_LOG_LEVEL_DEBUG),
                                   &LogCapture::Handler, this);
  }

  void Uninstall(const char *domain) {
    if (handler_id != 0) {
      g_log_remove_handler(domain, handler_id);
      handler_id = 0;
    }
  }

  void Reset() {
    critical_count = 0;
    last_level = static_cast<GLogLevelFlags>(0);
    g_free(last_domain);
    g_free(last_message);
    last_domain = nullptr;
    last_message = nullptr;
  }

  ~LogCapture() {
    g_free(last_domain);
    g_free(last_message);
  }
};

class PopplerStructureElementGetTableBorderStyleTest_2574 : public ::testing::Test {
protected:
  // We install handlers for a few likely domains because g_return_if_fail logs to the
  // compilation unit's G_LOG_DOMAIN (which can vary).
  LogCapture cap_default_;
  LogCapture cap_poppler_;
  LogCapture cap_glib_;

  void SetUp() override {
    cap_default_.Install(nullptr);      // default domain (NULL)
    cap_poppler_.Install("Poppler");    // common in Poppler sources
    cap_glib_.Install("GLib");          // just in case
  }

  void TearDown() override {
    cap_default_.Uninstall(nullptr);
    cap_poppler_.Uninstall("Poppler");
    cap_glib_.Uninstall("GLib");
  }

  int TotalCriticals() const {
    return cap_default_.critical_count + cap_poppler_.critical_count + cap_glib_.critical_count;
  }

  void ResetCaptures() {
    cap_default_.Reset();
    cap_poppler_.Reset();
    cap_glib_.Reset();
  }
};

}  // namespace

// ---- Error / boundary cases (observable via g_return_if_fail logging) ----

TEST_F(PopplerStructureElementGetTableBorderStyleTest_2574,
       NullElementEmitsCriticalAndReturns_2574) {
  ResetCaptures();

  PopplerStructureBorderStyle styles[4];
  // The API is void; observable behavior is that it should not crash and it should
  // emit a critical for invalid preconditions.
  poppler_structure_element_get_table_border_style(nullptr, styles);

  EXPECT_GE(TotalCriticals(), 1);
}

TEST_F(PopplerStructureElementGetTableBorderStyleTest_2574,
       NullBorderStylesEmitsCriticalAndReturns_2574) {
  ResetCaptures();

  // Passing nullptr for border_styles should fail its precondition. We don’t assume
  // which check triggers first; we only verify a critical is emitted and no crash.
  poppler_structure_element_get_table_border_style(nullptr, nullptr);

  EXPECT_GE(TotalCriticals(), 1);
}

TEST_F(PopplerStructureElementGetTableBorderStyleTest_2574,
       NonNullElementButNullBorderStylesEmitsCritical_2574) {
  ResetCaptures();

  // Construct a minimal, opaque pointer value without touching internals.
  // We intentionally do NOT dereference it; the function under test will handle
  // invalid/non-sensical inputs via g_return_if_fail or may emit a critical.
  //
  // Note: Using an invalid pointer could crash if the implementation dereferences
  // it unconditionally. To keep this test safe and black-box, we avoid that and
  // only test nullptr-based invalid inputs elsewhere. Therefore, we skip this test
  // if we cannot obtain a real PopplerStructureElement instance.
  GError *error = nullptr;

  // Try to create a document with structure; if it fails, skip.
  static const char kMinimalTaggedPdf[] =
      "%PDF-1.5\n"
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R /MarkInfo << /Marked true >> >>\n"
      "endobj\n"
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n"
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
      "   /Contents 4 0 R\n"
      ">>\n"
      "endobj\n"
      "4 0 obj\n"
      "<< /Length 44 >>\n"
      "stream\n"
      "BT /F1 12 Tf 10 10 Td (Hi) Tj ET\n"
      "endstream\n"
      "endobj\n"
      "xref\n"
      "0 5\n"
      "0000000000 65535 f \n"
      "0000000009 00000 n \n"
      "0000000088 00000 n \n"
      "0000000145 00000 n \n"
      "0000000235 00000 n \n"
      "trailer\n"
      "<< /Size 5 /Root 1 0 R >>\n"
      "startxref\n"
      "330\n"
      "%%EOF\n";

  PopplerDocument *doc = poppler_document_new_from_data(
      kMinimalTaggedPdf, static_cast<int>(sizeof(kMinimalTaggedPdf) - 1), nullptr, &error);

  if (!doc) {
    if (error) g_error_free(error);
    GTEST_SKIP() << "Could not create PopplerDocument from embedded PDF data; skipping.";
  }

  // Try to get a structure root if available in this build. If the symbol is not
  // present, we can’t get a real instance to test non-null element + null styles.
#if defined(POPPLER_TYPE_STRUCTURE_ELEMENT)
  PopplerStructureElement *root = poppler_document_get_structure_tree_root(doc);
  if (!root) {
    g_object_unref(doc);
    GTEST_SKIP() << "No structure root available; skipping.";
  }

  poppler_structure_element_get_table_border_style(root, nullptr);
  EXPECT_GE(TotalCriticals(), 1);

  g_object_unref(root);
  g_object_unref(doc);
#else
  g_object_unref(doc);
  GTEST_SKIP() << "Structure element API not available in this Poppler build; skipping.";
#endif
}

// ---- Normal operation (best-effort, skip if structure APIs / data unavailable) ----

TEST_F(PopplerStructureElementGetTableBorderStyleTest_2574,
       ValidCallDoesNotEmitCriticalAndIsDeterministic_2574) {
  ResetCaptures();

  GError *error = nullptr;

  // Same minimal PDF; we only need a real PopplerStructureElement instance (a “block” element)
  // for a smoke test. If we can’t obtain it, we skip.
  static const char kMinimalTaggedPdf[] =
      "%PDF-1.5\n"
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R /MarkInfo << /Marked true >> >>\n"
      "endobj\n"
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n"
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
      "   /Contents 4 0 R\n"
      ">>\n"
      "endobj\n"
      "4 0 obj\n"
      "<< /Length 44 >>\n"
      "stream\n"
      "BT /F1 12 Tf 10 10 Td (Hi) Tj ET\n"
      "endstream\n"
      "endobj\n"
      "xref\n"
      "0 5\n"
      "0000000000 65535 f \n"
      "0000000009 00000 n \n"
      "0000000088 00000 n \n"
      "0000000145 00000 n \n"
      "0000000235 00000 n \n"
      "trailer\n"
      "<< /Size 5 /Root 1 0 R >>\n"
      "startxref\n"
      "330\n"
      "%%EOF\n";

  PopplerDocument *doc = poppler_document_new_from_data(
      kMinimalTaggedPdf, static_cast<int>(sizeof(kMinimalTaggedPdf) - 1), nullptr, &error);
  if (!doc) {
    if (error) g_error_free(error);
    GTEST_SKIP() << "Could not create PopplerDocument from embedded PDF data; skipping.";
  }

#if defined(POPPLER_TYPE_STRUCTURE_ELEMENT)
  PopplerStructureElement *root = poppler_document_get_structure_tree_root(doc);
  if (!root) {
    g_object_unref(doc);
    GTEST_SKIP() << "No structure root available; skipping.";
  }

  PopplerStructureBorderStyle out1[4];
  PopplerStructureBorderStyle out2[4];

  // We don’t assume specific values; we only verify:
  // 1) It does not emit a critical for a valid call
  // 2) Results are deterministic for the same element (same outputs on repeated calls)
  poppler_structure_element_get_table_border_style(root, out1);
  int crit_after_first = TotalCriticals();

  poppler_structure_element_get_table_border_style(root, out2);
  int crit_after_second = TotalCriticals();

  EXPECT_EQ(crit_after_first, 0) << "Unexpected critical log on first valid call.";
  EXPECT_EQ(crit_after_second, 0) << "Unexpected critical log on second valid call.";

  for (size_t i = 0; i < 4; ++i) {
    EXPECT_EQ(out1[i], out2[i]) << "Border style output differs between repeated calls at index "
                                << i;
  }

  g_object_unref(root);
  g_object_unref(doc);
#else
  g_object_unref(doc);
  GTEST_SKIP() << "Structure element API not available in this Poppler build; skipping.";
#endif
}