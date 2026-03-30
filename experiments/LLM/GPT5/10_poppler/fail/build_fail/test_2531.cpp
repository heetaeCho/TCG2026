// poppler-structure-element-get-language-test.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdint>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace {

struct GObjectUnrefDeleter {
  void operator()(gpointer p) const {
    if (p) {
      g_object_unref(p);
    }
  }
};

struct GBytesUnrefDeleter {
  void operator()(GBytes *b) const {
    if (b) {
      g_bytes_unref(b);
    }
  }
};

struct GErrorDeleter {
  void operator()(GError *e) const {
    if (e) {
      g_error_free(e);
    }
  }
};

struct StructIterFreeDeleter {
  void operator()(PopplerStructureElementIter *it) const {
    if (it) {
      poppler_structure_element_iter_free(it);
    }
  }
};

using UniqueDocument = std::unique_ptr<PopplerDocument, GObjectUnrefDeleter>;
using UniqueBytes = std::unique_ptr<GBytes, GBytesUnrefDeleter>;
using UniqueGError = std::unique_ptr<GError, GErrorDeleter>;
using UniqueStructIter = std::unique_ptr<PopplerStructureElementIter, StructIterFreeDeleter>;

static std::string BuildMinimalPdfWithStructTreeRoot(bool include_lang) {
  // Build a small, valid PDF with:
  // - Catalog + one page
  // - StructTreeRoot containing a single StructElem (/S /Document)
  // - Optional /Lang (en_US) on that StructElem
  //
  // We keep it minimal; correctness is validated by PopplerDocument creation and iter access.

  std::vector<std::string> objs;
  objs.resize(8); // index by object number; we will use 1..7

  objs[1] =
      "<< /Type /Catalog\n"
      "   /Pages 2 0 R\n"
      "   /MarkInfo << /Marked true >>\n"
      "   /StructTreeRoot 5 0 R\n"
      ">>";

  objs[2] =
      "<< /Type /Pages\n"
      "   /Kids [3 0 R]\n"
      "   /Count 1\n"
      ">>";

  objs[3] =
      "<< /Type /Page\n"
      "   /Parent 2 0 R\n"
      "   /MediaBox [0 0 200 200]\n"
      "   /Contents 4 0 R\n"
      "   /Resources << /Font << /F1 6 0 R >> >>\n"
      ">>";

  // Simple content stream that references the font.
  const std::string content = "BT /F1 12 Tf 10 10 Td (Hello) Tj ET\n";
  {
    std::ostringstream ss;
    ss << "<< /Length " << content.size() << " >>\n"
       << "stream\n"
       << content
       << "endstream";
    objs[4] = ss.str();
  }

  objs[5] =
      "<< /Type /StructTreeRoot\n"
      "   /K 7 0 R\n"
      ">>";

  objs[6] =
      "<< /Type /Font\n"
      "   /Subtype /Type1\n"
      "   /BaseFont /Helvetica\n"
      ">>";

  {
    std::ostringstream ss;
    ss << "<< /Type /StructElem\n"
       << "   /S /Document\n"
       << "   /P 5 0 R\n";
    if (include_lang) {
      ss << "   /Lang (en_US)\n";
    }
    ss << ">>";
    objs[7] = ss.str();
  }

  std::string pdf;
  pdf += "%PDF-1.4\n";
  pdf += "%\xE2\xE3\xCF\xD3\n"; // binary marker

  std::vector<size_t> offsets;
  offsets.resize(8, 0);

  for (int i = 1; i <= 7; ++i) {
    offsets[i] = pdf.size();
    pdf += std::to_string(i) + " 0 obj\n";
    pdf += objs[i];
    pdf += "\nendobj\n";
  }

  const size_t xref_offset = pdf.size();
  pdf += "xref\n";
  pdf += "0 8\n";
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i <= 7; ++i) {
    std::ostringstream line;
    line << std::setw(10) << std::setfill('0') << static_cast<unsigned long>(offsets[i])
         << " 00000 n \n";
    pdf += line.str();
  }

  pdf += "trailer\n";
  pdf += "<< /Size 8\n";
  pdf += "   /Root 1 0 R\n";
  pdf += ">>\n";
  pdf += "startxref\n";
  pdf += std::to_string(static_cast<unsigned long>(xref_offset)) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

static std::string BuildMinimalPdfWithoutStructTree() {
  // Same as above but without /StructTreeRoot and /MarkInfo; iter_new() should return NULL.
  std::vector<std::string> objs;
  objs.resize(7); // 1..6

  objs[1] =
      "<< /Type /Catalog\n"
      "   /Pages 2 0 R\n"
      ">>";

  objs[2] =
      "<< /Type /Pages\n"
      "   /Kids [3 0 R]\n"
      "   /Count 1\n"
      ">>";

  objs[3] =
      "<< /Type /Page\n"
      "   /Parent 2 0 R\n"
      "   /MediaBox [0 0 200 200]\n"
      "   /Contents 4 0 R\n"
      "   /Resources << /Font << /F1 6 0 R >> >>\n"
      ">>";

  const std::string content = "BT /F1 12 Tf 10 10 Td (Hello) Tj ET\n";
  {
    std::ostringstream ss;
    ss << "<< /Length " << content.size() << " >>\n"
       << "stream\n"
       << content
       << "endstream";
    objs[4] = ss.str();
  }

  objs[6] =
      "<< /Type /Font\n"
      "   /Subtype /Type1\n"
      "   /BaseFont /Helvetica\n"
      ">>";

  std::string pdf;
  pdf += "%PDF-1.4\n";
  pdf += "%\xE2\xE3\xCF\xD3\n";

  std::vector<size_t> offsets;
  offsets.resize(7, 0);

  for (int i = 1; i <= 6; ++i) {
    if (i == 5) continue; // unused
    offsets[i] = pdf.size();
    pdf += std::to_string(i) + " 0 obj\n";
    pdf += objs[i];
    pdf += "\nendobj\n";
  }

  const size_t xref_offset = pdf.size();
  pdf += "xref\n";
  pdf += "0 7\n";
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i <= 6; ++i) {
    if (i == 5) {
      pdf += "0000000000 00000 f \n";
      continue;
    }
    std::ostringstream line;
    line << std::setw(10) << std::setfill('0') << static_cast<unsigned long>(offsets[i])
         << " 00000 n \n";
    pdf += line.str();
  }

  pdf += "trailer\n";
  pdf += "<< /Size 7\n";
  pdf += "   /Root 1 0 R\n";
  pdf += ">>\n";
  pdf += "startxref\n";
  pdf += std::to_string(static_cast<unsigned long>(xref_offset)) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

static UniqueDocument LoadDocFromPdfBytes(const std::string &pdf) {
  UniqueGError err;
  GError *raw_err = nullptr;

  UniqueBytes bytes(g_bytes_new(pdf.data(), pdf.size()));
  PopplerDocument *doc = poppler_document_new_from_bytes(bytes.get(), /*password=*/nullptr, &raw_err);
  err.reset(raw_err);

  // Keep bytes alive at least through document construction. The document holds a ref to bytes.
  (void)bytes.release(); // doc owns a reference; avoid premature unref in this helper.

  if (!doc) {
    return UniqueDocument(nullptr);
  }
  return UniqueDocument(doc);
}

class PopplerStructureElementGetLanguageTest_2531 : public ::testing::Test {
protected:
  static UniqueStructIter NewIter(PopplerDocument *doc) {
    return UniqueStructIter(poppler_structure_element_iter_new(doc));
  }

  static PopplerStructureElement *GetElement(PopplerStructureElementIter *iter) {
    return poppler_structure_element_iter_get_element(iter);
  }
};

} // namespace

TEST_F(PopplerStructureElementGetLanguageTest_2531, NullInputReturnsNull_2531) {
  // Error/exceptional case (guard): passing NULL should return NULL.
  gchar *lang = poppler_structure_element_get_language(nullptr);
  EXPECT_EQ(lang, nullptr);
}

TEST_F(PopplerStructureElementGetLanguageTest_2531, ReturnsLanguageWhenDefined_2531) {
  const std::string pdf = BuildMinimalPdfWithStructTreeRoot(/*include_lang=*/true);
  UniqueDocument doc = LoadDocFromPdfBytes(pdf);
  ASSERT_NE(doc.get(), nullptr);

  UniqueStructIter iter = NewIter(doc.get());
  ASSERT_NE(iter.get(), nullptr);

  PopplerStructureElement *elem = GetElement(iter.get());
  ASSERT_NE(elem, nullptr);

  gchar *lang = poppler_structure_element_get_language(elem);
  ASSERT_NE(lang, nullptr);
  EXPECT_STREQ(lang, "en_US");

  g_free(lang);
}

TEST_F(PopplerStructureElementGetLanguageTest_2531, ReturnsNullWhenLanguageNotDefined_2531) {
  const std::string pdf = BuildMinimalPdfWithStructTreeRoot(/*include_lang=*/false);
  UniqueDocument doc = LoadDocFromPdfBytes(pdf);
  ASSERT_NE(doc.get(), nullptr);

  UniqueStructIter iter = NewIter(doc.get());
  ASSERT_NE(iter.get(), nullptr);

  PopplerStructureElement *elem = GetElement(iter.get());
  ASSERT_NE(elem, nullptr);

  gchar *lang = poppler_structure_element_get_language(elem);
  EXPECT_EQ(lang, nullptr);
}

TEST_F(PopplerStructureElementGetLanguageTest_2531, IterIsNullWhenNoStructureTree_2531) {
  const std::string pdf = BuildMinimalPdfWithoutStructTree();
  UniqueDocument doc = LoadDocFromPdfBytes(pdf);
  ASSERT_NE(doc.get(), nullptr);

  UniqueStructIter iter = NewIter(doc.get());
  EXPECT_EQ(iter.get(), nullptr);
}