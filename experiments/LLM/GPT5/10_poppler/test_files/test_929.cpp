// Form_getNumFields_929_test.cc
// Unit tests for poppler::Form (partial interface) - TEST_ID 929

#include <gtest/gtest.h>

#include <cstdio>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "poppler/Form.h"
#include "poppler/PDFDoc.h"
#include "poppler/GooString.h"

namespace {

class FormTest_929 : public ::testing::Test {
protected:
  static std::string buildPdfWithAcroFormFields_929(int nFields, bool includeAcroForm) {
    // Minimal valid PDF with:
    //  - Catalog (1 0) referencing Pages (3 0) and optional AcroForm (2 0)
    //  - AcroForm (2 0) with /Fields array containing nFields terminal field dicts
    //  - One Page (6 0) and an empty content stream (7 0)
    //
    // Each field is a terminal widget annotation dict (commonly valid):
    //   << /FT /Tx /T (F#) /Subtype /Widget /Rect [...] /P 6 0 R >>
    //
    // This generator computes xref offsets so PDFDoc can open it.

    struct Obj {
      int num;
      std::string body; // includes "n 0 obj\n...\nendobj\n"
      size_t offset;
    };

    std::vector<Obj> objs;
    objs.reserve(static_cast<size_t>(8 + std::max(0, nFields)));

    auto addObj = [&](int num, std::string dictOrStream) {
      Obj o;
      o.num = num;
      o.offset = 0; // filled later
      o.body = std::to_string(num) + " 0 obj\n" + std::move(dictOrStream) + "\nendobj\n";
      objs.push_back(std::move(o));
    };

    // 7 0: empty contents stream
    addObj(7, "<< /Length 0 >>\nstream\n\nendstream");

    // 6 0: single page
    addObj(6,
           "<< /Type /Page\n"
           "   /Parent 3 0 R\n"
           "   /MediaBox [0 0 100 100]\n"
           "   /Resources << >>\n"
           "   /Contents 7 0 R\n"
           ">>");

    // 3 0: pages
    addObj(3,
           "<< /Type /Pages\n"
           "   /Kids [6 0 R]\n"
           "   /Count 1\n"
           ">>");

    // 2 0: AcroForm (optional)
    if (includeAcroForm) {
      std::string fields = "[";
      for (int i = 0; i < nFields; ++i) {
        // Field objects will start at 8 0
        fields += " " + std::to_string(8 + i) + " 0 R";
      }
      fields += " ]";

      addObj(2,
             "<< /Fields " + fields + "\n"
             "   /NeedAppearances true\n"
             ">>");
    }

    // 1 0: catalog
    if (includeAcroForm) {
      addObj(1,
             "<< /Type /Catalog\n"
             "   /Pages 3 0 R\n"
             "   /AcroForm 2 0 R\n"
             ">>");
    } else {
      addObj(1,
             "<< /Type /Catalog\n"
             "   /Pages 3 0 R\n"
             ">>");
    }

    // Field objects: 8..(8+nFields-1)
    for (int i = 0; i < nFields; ++i) {
      // Terminal field widget dict
      // Keep the /Rect simple and distinct.
      const int x0 = 10 + i;
      const int y0 = 10 + i;
      const int x1 = 20 + i;
      const int y1 = 20 + i;

      addObj(8 + i,
             "<< /FT /Tx\n"
             "   /T (F" + std::to_string(i) + ")\n"
             "   /Subtype /Widget\n"
             "   /Rect [" + std::to_string(x0) + " " + std::to_string(y0) + " " +
                 std::to_string(x1) + " " + std::to_string(y1) + "]\n"
             "   /P 6 0 R\n"
             ">>");
    }

    // Build full PDF
    std::string pdf;
    pdf.reserve(4096);

    pdf += "%PDF-1.4\n";
    // Binary marker line (common in PDFs)
    pdf += "%\xE2\xE3\xCF\xD3\n";

    // Compute offsets as we append objects in ascending object number order.
    // Ensure objects are sorted by obj number.
    std::sort(objs.begin(), objs.end(), [](const Obj &a, const Obj &b) { return a.num < b.num; });

    // Offsets need to include current pdf size in bytes.
    for (auto &o : objs) {
      o.offset = pdf.size();
      pdf += o.body;
    }

    const size_t xrefOffset = pdf.size();

    // xref table: needs entries from 0..maxObj
    int maxObjNum = 0;
    for (const auto &o : objs) maxObjNum = std::max(maxObjNum, o.num);

    pdf += "xref\n";
    pdf += "0 " + std::to_string(maxObjNum + 1) + "\n";
    pdf += "0000000000 65535 f \n";

    // Build map from obj num to offset
    std::vector<size_t> offsets(static_cast<size_t>(maxObjNum + 1), 0);
    for (const auto &o : objs) offsets[static_cast<size_t>(o.num)] = o.offset;

    auto fmt10 = [](size_t v) {
      std::string s = std::to_string(v);
      if (s.size() < 10) s = std::string(10 - s.size(), '0') + s;
      return s;
    };

    for (int i = 1; i <= maxObjNum; ++i) {
      pdf += fmt10(offsets[static_cast<size_t>(i)]) + " 00000 n \n";
    }

    pdf += "trailer\n";
    pdf += "<< /Size " + std::to_string(maxObjNum + 1) + "\n";
    pdf += "   /Root 1 0 R\n";
    pdf += ">>\n";
    pdf += "startxref\n";
    pdf += std::to_string(xrefOffset) + "\n";
    pdf += "%%EOF\n";

    return pdf;
  }

  static std::filesystem::path writeTempPdf_929(const std::string &bytes) {
    const auto dir = std::filesystem::temp_directory_path();
    const auto path = dir / ("poppler_form_test_929_" + std::to_string(std::rand()) + ".pdf");

    std::ofstream out(path, std::ios::binary);
    out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    out.close();
    return path;
  }

  static std::unique_ptr<PDFDoc> openPdfDoc_929(const std::filesystem::path &path) {
    const std::string p = path.string();

    // Try a few common PDFDoc constructor signatures across Poppler versions.
    if constexpr (std::is_constructible_v<PDFDoc, std::unique_ptr<GooString>, GooString *, GooString *, void *>) {
      auto gs = std::make_unique<GooString>(p.c_str());
      return std::make_unique<PDFDoc>(std::move(gs), nullptr, nullptr, nullptr);
    } else if constexpr (std::is_constructible_v<PDFDoc, std::unique_ptr<GooString>, GooString *, GooString *>) {
      auto gs = std::make_unique<GooString>(p.c_str());
      return std::make_unique<PDFDoc>(std::move(gs), nullptr, nullptr);
    } else if constexpr (std::is_constructible_v<PDFDoc, const GooString *, GooString *, GooString *, void *>) {
      GooString gs(p.c_str());
      return std::make_unique<PDFDoc>(&gs, nullptr, nullptr, nullptr);
    } else if constexpr (std::is_constructible_v<PDFDoc, const GooString *, GooString *, GooString *>) {
      GooString gs(p.c_str());
      return std::make_unique<PDFDoc>(&gs, nullptr, nullptr);
    } else if constexpr (std::is_constructible_v<PDFDoc, const char *, GooString *, GooString *, void *>) {
      return std::make_unique<PDFDoc>(p.c_str(), nullptr, nullptr, nullptr);
    } else if constexpr (std::is_constructible_v<PDFDoc, const char *, GooString *, GooString *>) {
      return std::make_unique<PDFDoc>(p.c_str(), nullptr, nullptr);
    } else {
      // If none match, fail clearly at compile time.
      static_assert(sizeof(PDFDoc) == 0, "Unsupported PDFDoc constructor signature for this Poppler version");
      return nullptr;
    }
  }
};

TEST_F(FormTest_929, NoAcroForm_ReturnsZero_929) {
  const std::string pdf = buildPdfWithAcroFormFields_929(/*nFields=*/0, /*includeAcroForm=*/false);
  const auto path = writeTempPdf_929(pdf);

  auto doc = openPdfDoc_929(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Form form(doc.get());
  EXPECT_EQ(form.getNumFields(), 0);

  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(FormTest_929, EmptyFieldsArray_ReturnsZero_929) {
  const std::string pdf = buildPdfWithAcroFormFields_929(/*nFields=*/0, /*includeAcroForm=*/true);
  const auto path = writeTempPdf_929(pdf);

  auto doc = openPdfDoc_929(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Form form(doc.get());
  EXPECT_EQ(form.getNumFields(), 0);

  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(FormTest_929, TwoRootFields_ReturnsTwo_929) {
  const std::string pdf = buildPdfWithAcroFormFields_929(/*nFields=*/2, /*includeAcroForm=*/true);
  const auto path = writeTempPdf_929(pdf);

  auto doc = openPdfDoc_929(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Form form(doc.get());
  EXPECT_EQ(form.getNumFields(), 2);

  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(FormTest_929, MultipleRootFields_ReturnsCount_929) {
  // Boundary-ish case: more than a couple of fields to ensure size accounting holds.
  const int kCount = 10;
  const std::string pdf = buildPdfWithAcroFormFields_929(/*nFields=*/kCount, /*includeAcroForm=*/true);
  const auto path = writeTempPdf_929(pdf);

  auto doc = openPdfDoc_929(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Form form(doc.get());
  EXPECT_EQ(form.getNumFields(), kCount);

  std::error_code ec;
  std::filesystem::remove(path, ec);
}

} // namespace