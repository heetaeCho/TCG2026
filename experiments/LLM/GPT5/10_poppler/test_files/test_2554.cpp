// poppler_structure_element_get_border_style_test_2554.cc
#include <gtest/gtest.h>

#include <glib-object.h>
#include <glib.h>

#include <poppler.h>

#include <array>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

namespace {

class ScopedCriticalLogCounter {
public:
  ScopedCriticalLogCounter()
      : handler_id_default_(0), handler_id_poppler_(0), handler_id_poppler_glib_(0) {
    // Capture CRITICAL logs from common domains. Some builds log under NULL (default),
    // some under "Poppler" or "poppler-glib".
    handler_id_default_ =
        g_log_set_handler(nullptr, (GLogLevelFlags)(G_LOG_LEVEL_CRITICAL), &ScopedCriticalLogCounter::Handler, this);
    handler_id_poppler_ =
        g_log_set_handler("Poppler", (GLogLevelFlags)(G_LOG_LEVEL_CRITICAL), &ScopedCriticalLogCounter::Handler, this);
    handler_id_poppler_glib_ = g_log_set_handler(
        "poppler-glib", (GLogLevelFlags)(G_LOG_LEVEL_CRITICAL), &ScopedCriticalLogCounter::Handler, this);
  }

  ~ScopedCriticalLogCounter() {
    if (handler_id_default_)
      g_log_remove_handler(nullptr, handler_id_default_);
    if (handler_id_poppler_)
      g_log_remove_handler("Poppler", handler_id_poppler_);
    if (handler_id_poppler_glib_)
      g_log_remove_handler("poppler-glib", handler_id_poppler_glib_);
  }

  int critical_count() const { return critical_count_; }

private:
  static void Handler(const gchar* /*log_domain*/,
                      GLogLevelFlags /*log_level*/,
                      const gchar* /*message*/,
                      gpointer user_data) {
    auto* self = static_cast<ScopedCriticalLogCounter*>(user_data);
    self->critical_count_++;
  }

  guint handler_id_default_;
  guint handler_id_poppler_;
  guint handler_id_poppler_glib_;
  int critical_count_ = 0;
};

// Build a tiny Tagged PDF with a minimal structure tree so that
// poppler_structure_element_iter_new() returns a valid iterator.
static std::string BuildMinimalTaggedPdf() {
  struct Obj {
    int num;
    std::string body; // must include "obj".."endobj"
  };

  std::vector<Obj> objs;

  // 1 0: Catalog with StructTreeRoot and MarkInfo to mark document as tagged.
  objs.push_back({1,
                  "1 0 obj\n"
                  "<< /Type /Catalog\n"
                  "   /Pages 2 0 R\n"
                  "   /MarkInfo << /Marked true >>\n"
                  "   /StructTreeRoot 5 0 R\n"
                  ">>\n"
                  "endobj\n"});

  // 2 0: Pages
  objs.push_back({2,
                  "2 0 obj\n"
                  "<< /Type /Pages /Count 1 /Kids [3 0 R] >>\n"
                  "endobj\n"});

  // 3 0: Page (empty content stream)
  objs.push_back({3,
                  "3 0 obj\n"
                  "<< /Type /Page\n"
                  "   /Parent 2 0 R\n"
                  "   /MediaBox [0 0 100 100]\n"
                  "   /Contents 4 0 R\n"
                  ">>\n"
                  "endobj\n"});

  // 4 0: Empty content stream
  objs.push_back({4,
                  "4 0 obj\n"
                  "<< /Length 0 >>\n"
                  "stream\n"
                  "\n"
                  "endstream\n"
                  "endobj\n"});

  // 5 0: StructTreeRoot
  objs.push_back({5,
                  "5 0 obj\n"
                  "<< /Type /StructTreeRoot\n"
                  "   /K [6 0 R]\n"
                  ">>\n"
                  "endobj\n"});

  // 6 0: StructElem (Document)
  objs.push_back({6,
                  "6 0 obj\n"
                  "<< /Type /StructElem\n"
                  "   /S /Document\n"
                  "   /P 5 0 R\n"
                  ">>\n"
                  "endobj\n"});

  std::string out;
  out += "%PDF-1.5\n";
  // Binary marker line (recommended)
  out += "%\xE2\xE3\xCF\xD3\n";

  // Track offsets (byte positions) for xref.
  // xref entry 0 is the free object.
  std::vector<long> offsets(7, 0);

  for (const auto& o : objs) {
    offsets[o.num] = static_cast<long>(out.size());
    out += o.body;
  }

  const long xref_offset = static_cast<long>(out.size());
  out += "xref\n";
  out += "0 7\n";
  out += "0000000000 65535 f \n";
  for (int i = 1; i <= 6; ++i) {
    char buf[64];
    // 10-digit zero-padded offset, generation 00000, in-use 'n'
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    out += buf;
  }
  out += "trailer\n";
  out += "<< /Size 7 /Root 1 0 R >>\n";
  out += "startxref\n";
  out += std::to_string(xref_offset);
  out += "\n%%EOF\n";
  return out;
}

static PopplerDocument* LoadDocFromDataOrNull(const std::string& pdf_data, GError** error) {
  // poppler_document_new_from_data takes a char* buffer and length; it copies data internally.
  return poppler_document_new_from_data(pdf_data.c_str(), static_cast<int>(pdf_data.size()), nullptr, error);
}

static PopplerStructureElement* GetFirstStructureElementOrNull(PopplerDocument* doc) {
  if (!doc)
    return nullptr;

  PopplerStructureElementIter* iter = poppler_structure_element_iter_new(doc);
  if (!iter)
    return nullptr;

  PopplerStructureElement* elem = poppler_structure_element_iter_get_element(iter);
  poppler_structure_element_iter_free(iter);
  return elem; // borrowed/refcounted? GLib API returns (transfer none) in docs for many getters.
}

class PopplerStructureElementGetBorderStyleTest_2554 : public ::testing::Test {
protected:
  void TearDown() override {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
    if (error_) {
      g_error_free(error_);
      error_ = nullptr;
    }
  }

  PopplerDocument* doc_ = nullptr;
  GError* error_ = nullptr;
};

TEST_F(PopplerStructureElementGetBorderStyleTest_2554, NullElementEmitsCriticalAndDoesNotWrite_2554) {
  ScopedCriticalLogCounter logs;

  std::array<PopplerStructureBorderStyle, 4> styles;
  std::memset(styles.data(), 0xA5, sizeof(styles));

  poppler_structure_element_get_border_style(nullptr, styles.data());

  EXPECT_GE(logs.critical_count(), 1);

  // Since g_return_if_fail() should return before writing, buffer should remain unchanged.
  std::array<PopplerStructureBorderStyle, 4> expected;
  std::memset(expected.data(), 0xA5, sizeof(expected));
  EXPECT_EQ(0, std::memcmp(styles.data(), expected.data(), sizeof(styles)));
}

TEST_F(PopplerStructureElementGetBorderStyleTest_2554, NullOutArrayEmitsCritical_2554) {
  ScopedCriticalLogCounter logs;

  // Use a non-null but invalid pointer for the element; it should fail the type check first OR
  // if it passes (unlikely), it must still fail on nullptr out-parameter. Either way, critical.
  PopplerStructureElement* bogus = reinterpret_cast<PopplerStructureElement*>(g_object_new(G_TYPE_OBJECT, nullptr));

  poppler_structure_element_get_border_style(bogus, nullptr);

  EXPECT_GE(logs.critical_count(), 1);

  g_object_unref(reinterpret_cast<GObject*>(bogus));
}

TEST_F(PopplerStructureElementGetBorderStyleTest_2554, WrongTypeElementEmitsCriticalAndDoesNotWrite_2554) {
  ScopedCriticalLogCounter logs;

  std::array<PopplerStructureBorderStyle, 4> styles;
  std::memset(styles.data(), 0x5A, sizeof(styles));

  // Create a plain GObject and pass it as if it were a PopplerStructureElement*.
  GObject* wrong = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  poppler_structure_element_get_border_style(reinterpret_cast<PopplerStructureElement*>(wrong), styles.data());

  EXPECT_GE(logs.critical_count(), 1);

  std::array<PopplerStructureBorderStyle, 4> expected;
  std::memset(expected.data(), 0x5A, sizeof(expected));
  EXPECT_EQ(0, std::memcmp(styles.data(), expected.data(), sizeof(styles)));

  g_object_unref(wrong);
}

TEST_F(PopplerStructureElementGetBorderStyleTest_2554, TaggedPdfElementNoCriticalAndDeterministicOutput_2554) {
  const std::string pdf = BuildMinimalTaggedPdf();
  doc_ = LoadDocFromDataOrNull(pdf, &error_);
  ASSERT_NE(doc_, nullptr) << (error_ ? error_->message : "Unknown error");

  PopplerStructureElement* elem = GetFirstStructureElementOrNull(doc_);
  ASSERT_NE(elem, nullptr);

  ScopedCriticalLogCounter logs;

  std::array<PopplerStructureBorderStyle, 4> out1;
  std::array<PopplerStructureBorderStyle, 4> out2;
  std::memset(out1.data(), 0x11, sizeof(out1));
  std::memset(out2.data(), 0x22, sizeof(out2));

  poppler_structure_element_get_border_style(elem, out1.data());
  poppler_structure_element_get_border_style(elem, out2.data());

  EXPECT_EQ(logs.critical_count(), 0);

  // Black-box determinism check: same input element should yield identical outputs.
  EXPECT_EQ(0, std::memcmp(out1.data(), out2.data(), sizeof(out1)));
}

TEST_F(PopplerStructureElementGetBorderStyleTest_2554, TaggedPdfElementDoesNotCrashWhenCalled_2554) {
  const std::string pdf = BuildMinimalTaggedPdf();
  doc_ = LoadDocFromDataOrNull(pdf, &error_);
  ASSERT_NE(doc_, nullptr) << (error_ ? error_->message : "Unknown error");

  PopplerStructureElement* elem = GetFirstStructureElementOrNull(doc_);
  ASSERT_NE(elem, nullptr);

  ScopedCriticalLogCounter logs;

  std::array<PopplerStructureBorderStyle, 4> styles;
  std::memset(styles.data(), 0xCC, sizeof(styles));

  // Main observable requirement: should not crash, and should not emit g_return_if_fail criticals
  // for valid inputs.
  poppler_structure_element_get_border_style(elem, styles.data());

  EXPECT_EQ(logs.critical_count(), 0);
}

} // namespace