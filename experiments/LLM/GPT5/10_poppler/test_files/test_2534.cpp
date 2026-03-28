// poppler_structure_element_get_text_test_2534.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <string>
#include <vector>

namespace {

class GErrorPtr {
public:
  GErrorPtr() = default;
  ~GErrorPtr() { reset(); }

  GError **out() { return &err_; }
  GError *get() const { return err_; }

  std::string message_or_empty() const {
    return err_ ? std::string(err_->message ? err_->message : "") : std::string();
  }

  void reset() {
    if (err_) {
      g_error_free(err_);
      err_ = nullptr;
    }
  }

private:
  GError *err_ = nullptr;
};

// Build a minimal *Tagged PDF* with a structure tree and one marked-content span "Hello".
// The goal is to obtain a real PopplerStructureElement from Poppler, without relying on
// any private Poppler internals.
static std::string BuildTaggedHelloPdfBytes() {
  struct Obj {
    int num;
    std::string body; // includes "obj ... endobj" OR "obj ... stream ... endstream ... endobj"
  };

  // Content stream with marked content (MCID 0) so Poppler can map structure element to text.
  const std::string contents_stream =
      "BT\n"
      "/F1 12 Tf\n"
      "10 100 Td\n"
      "/P <</MCID 0>> BDC\n"
      "(Hello) Tj\n"
      "EMC\n"
      "ET\n";

  std::vector<Obj> objs;

  // 1: Catalog (links StructTreeRoot and MarkInfo)
  objs.push_back({1,
                  "<< /Type /Catalog\n"
                  "   /Pages 2 0 R\n"
                  "   /StructTreeRoot 6 0 R\n"
                  "   /MarkInfo << /Marked true >>\n"
                  ">>"});

  // 2: Pages
  objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"});

  // 3: Page (with StructParents so ParentTree can map MCID content)
  objs.push_back({3,
                  "<< /Type /Page\n"
                  "   /Parent 2 0 R\n"
                  "   /MediaBox [0 0 200 200]\n"
                  "   /Contents 4 0 R\n"
                  "   /Resources << /Font << /F1 5 0 R >> >>\n"
                  "   /StructParents 0\n"
                  ">>"});

  // 4: Contents stream
  {
    std::string body;
    body += "<< /Length " + std::to_string(contents_stream.size()) + " >>\n";
    body += "stream\n";
    body += contents_stream;
    body += "endstream";
    objs.push_back({4, body});
  }

  // 5: Font
  objs.push_back({5, "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>"});

  // 6: StructTreeRoot with /K pointing to a StructElem and ParentTree mapping 0 -> [MCR]
  objs.push_back({6,
                  "<< /Type /StructTreeRoot\n"
                  "   /K 7 0 R\n"
                  "   /ParentTree 8 0 R\n"
                  ">>"});

  // 7: StructElem (Paragraph) containing one marked-content reference (9 0 R)
  objs.push_back({7,
                  "<< /Type /StructElem\n"
                  "   /S /P\n"
                  "   /P 6 0 R\n"
                  "   /Pg 3 0 R\n"
                  "   /K 9 0 R\n"
                  ">>"});

  // 8: ParentTree number tree: StructParents(0) -> array [ 9 0 R ]
  objs.push_back({8, "<< /Nums [ 0 [ 9 0 R ] ] >>"});

  // 9: Marked-content reference for MCID 0 on page 3
  objs.push_back({9, "<< /Type /MCR /Pg 3 0 R /MCID 0 >>"});

  // Build PDF with xref.
  std::string pdf;
  pdf += "%PDF-1.7\n";
  pdf += "%\xE2\xE3\xCF\xD3\n"; // binary comment

  std::vector<long> offsets(10, 0); // index by obj num

  for (const auto &o : objs) {
    offsets[o.num] = static_cast<long>(pdf.size());
    pdf += std::to_string(o.num) + " 0 obj\n";
    pdf += o.body + "\n";
    pdf += "endobj\n";
  }

  const long xref_offset = static_cast<long>(pdf.size());
  pdf += "xref\n";
  pdf += "0 10\n";
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i <= 9; ++i) {
    char buf[32];
    // 10-digit, zero-padded byte offset
    g_snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    pdf += buf;
  }

  pdf += "trailer\n";
  pdf += "<< /Size 10 /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_offset) + "\n";
  pdf += "%%EOF\n";
  return pdf;
}

static std::string WriteTempFileOrDie(const std::string &bytes) {
  gchar *path = nullptr;
  gint fd = g_file_open_tmp("poppler-structure-element-2534-XXXXXX.pdf", &path, nullptr);
  if (fd < 0 || !path) {
    if (path)
      g_free(path);
    ADD_FAILURE() << "Failed to create temporary file via g_file_open_tmp";
    return std::string();
  }

  // Close fd and use g_file_set_contents for simplicity.
  close(fd);

  if (!g_file_set_contents(path, bytes.data(), static_cast<gssize>(bytes.size()), nullptr)) {
    std::string p = path;
    g_free(path);
    ADD_FAILURE() << "Failed to write PDF bytes to temp file: " << p;
    return std::string();
  }

  std::string result = path;
  g_free(path);
  return result;
}

static PopplerDocument *OpenDocumentFromPathOrDie(const std::string &path) {
  GErrorPtr err;
  gchar *uri = g_filename_to_uri(path.c_str(), nullptr, err.out());
  if (!uri) {
    ADD_FAILURE() << "g_filename_to_uri failed: " << err.message_or_empty();
    return nullptr;
  }

  PopplerDocument *doc = poppler_document_new_from_file(uri, /*password=*/nullptr, err.out());
  g_free(uri);

  if (!doc) {
    ADD_FAILURE() << "poppler_document_new_from_file failed: " << err.message_or_empty();
  }
  return doc;
}

static PopplerStructureElement *FindFirstElementWithText(PopplerStructureElementIter *iter) {
  if (!iter)
    return nullptr;

  do {
    // Current element at this iterator position.
    PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
    if (elem) {
      // Try recursive text; if it yields something non-empty, keep it.
      gchar *txt = poppler_structure_element_get_text(elem, POPPLER_STRUCTURE_GET_TEXT_RECURSIVE);
      const bool has_text = (txt && *txt);
      if (txt)
        g_free(txt);
      if (has_text) {
        return elem; // transfer full from get_element()
      }
      g_object_unref(elem);
    }

    // Recurse into children.
    PopplerStructureElementIter *child = poppler_structure_element_iter_get_child(iter);
    if (child) {
      PopplerStructureElement *found = FindFirstElementWithText(child);
      poppler_structure_element_iter_free(child);
      if (found)
        return found;
    }
  } while (poppler_structure_element_iter_next(iter));

  return nullptr;
}

class PopplerStructureElementGetTextTest_2534 : public ::testing::Test {};

TEST_F(PopplerStructureElementGetTextTest_2534, NullElementReturnsNull_2534) {
  gchar *text = poppler_structure_element_get_text(nullptr, POPPLER_STRUCTURE_GET_TEXT_NONE);
  EXPECT_EQ(text, nullptr);
}

TEST_F(PopplerStructureElementGetTextTest_2534, NonStructureGObjectReturnsNull_2534) {
  // Pass a non-PopplerStructureElement instance to trigger the type check.
  GObject *obj = static_cast<GObject *>(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  PopplerStructureElement *bad = reinterpret_cast<PopplerStructureElement *>(obj);
  gchar *text = poppler_structure_element_get_text(bad, POPPLER_STRUCTURE_GET_TEXT_NONE);
  EXPECT_EQ(text, nullptr);

  g_object_unref(obj);
}

TEST_F(PopplerStructureElementGetTextTest_2534, NewStructureElementWithNoBackendReturnsNullIfConstructible_2534) {
  // Some Poppler GObject types may be non-constructible/abstract; if so, skip.
  GObject *obj = static_cast<GObject *>(g_object_new(poppler_structure_element_get_type(), nullptr));
  if (!obj) {
    GTEST_SKIP() << "PopplerStructureElement type is not directly constructible in this build";
  }

  PopplerStructureElement *elem = reinterpret_cast<PopplerStructureElement *>(obj);
  gchar *text = poppler_structure_element_get_text(elem, POPPLER_STRUCTURE_GET_TEXT_RECURSIVE);
  EXPECT_EQ(text, nullptr);

  g_object_unref(obj);
}

TEST_F(PopplerStructureElementGetTextTest_2534, TaggedPdfElementRecursiveTextContainsHello_2534) {
  const std::string pdf = BuildTaggedHelloPdfBytes();
  const std::string path = WriteTempFileOrDie(pdf);
  ASSERT_FALSE(path.empty());

  PopplerDocument *doc = OpenDocumentFromPathOrDie(path);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
  ASSERT_NE(iter, nullptr) << "Document should have a structure tree";

  PopplerStructureElement *elem_with_text = FindFirstElementWithText(iter);
  ASSERT_NE(elem_with_text, nullptr) << "Expected to find a structure element with text in the tagged PDF";

  // Primary behavior under test: get_text returns allocated UTF-8 text for a real element.
  gchar *text = poppler_structure_element_get_text(elem_with_text, POPPLER_STRUCTURE_GET_TEXT_RECURSIVE);
  ASSERT_NE(text, nullptr);
  EXPECT_NE(std::string(text).find("Hello"), std::string::npos);

  g_free(text);
  g_object_unref(elem_with_text);

  poppler_structure_element_iter_free(iter);
  g_object_unref(doc);

  // Cleanup temp file.
  g_remove(path.c_str());
}

TEST_F(PopplerStructureElementGetTextTest_2534, FlagsWithExtraBitsDoNotPreventRecursiveText_2534) {
  const std::string pdf = BuildTaggedHelloPdfBytes();
  const std::string path = WriteTempFileOrDie(pdf);
  ASSERT_FALSE(path.empty());

  PopplerDocument *doc = OpenDocumentFromPathOrDie(path);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
  ASSERT_NE(iter, nullptr);

  PopplerStructureElement *elem_with_text = FindFirstElementWithText(iter);
  ASSERT_NE(elem_with_text, nullptr);

  // Provide a flags value that includes RECURSIVE plus unrelated high bits.
  const auto weird_flags = static_cast<PopplerStructureGetTextFlags>(
      POPPLER_STRUCTURE_GET_TEXT_RECURSIVE | 0xFFFF0000u);

  gchar *text = poppler_structure_element_get_text(elem_with_text, weird_flags);
  ASSERT_NE(text, nullptr);
  EXPECT_NE(std::string(text).find("Hello"), std::string::npos);

  g_free(text);
  g_object_unref(elem_with_text);

  poppler_structure_element_iter_free(iter);
  g_object_unref(doc);
  g_remove(path.c_str());
}

} // namespace