// TEST_ID: 930
// File: form_getRootField_ut_930.cpp

#include <gtest/gtest.h>

#include <fstream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "Form.h"

// Poppler core types
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "goo/GooString.h"

extern GlobalParams *globalParams;

namespace {

// Builds a minimal PDF with N AcroForm text fields (each is also a Widget annotation on page 1).
// This is just a test fixture generator (black-box w.r.t. Form).
std::string BuildMinimalPdfWithTextFields(int fieldCount, bool includeAcroForm) {
  // Object numbers:
  // 1 0 obj: Catalog
  // 2 0 obj: Pages
  // 3 0 obj: Page
  // 4.. : Field/Widget dicts (fieldCount objects)
  // last: AcroForm dict (if includeAcroForm)

  struct Obj {
    int num;
    std::string body;
  };

  std::vector<Obj> objs;

  // Pages tree
  objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"});

  // Page with Annots referencing widgets (fields)
  // We'll fill Annots after we know field object numbers.
  // For now place a placeholder, then patch.
  objs.push_back({3,
                  "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Annots "
                  "[__ANNOTS__] >>"});

  // Fields / widgets
  const int firstFieldObj = 4;
  for (int i = 0; i < fieldCount; ++i) {
    const int objNum = firstFieldObj + i;
    const std::string t = "field" + std::to_string(i + 1);
    // Simple text field widget dict.
    // /P points to page 3 0 R, /Subtype /Widget makes it an annotation.
    // Rects vary slightly by index.
    const int y0 = 700 - i * 40;
    const int y1 = y0 + 20;
    std::string body =
        "<< /FT /Tx /Subtype /Widget /T (" + t + ") /V (value) /F 4 "
        "/Rect [72 " +
        std::to_string(y0) + " 300 " + std::to_string(y1) + "] /P 3 0 R >>";
    objs.push_back({objNum, std::move(body)});
  }

  // AcroForm dict (optional)
  int acroFormObjNum = firstFieldObj + fieldCount;  // next object id
  if (includeAcroForm) {
    std::string fieldsArray = "[";
    for (int i = 0; i < fieldCount; ++i) {
      fieldsArray += std::to_string(firstFieldObj + i) + " 0 R ";
    }
    fieldsArray += "]";
    objs.push_back({acroFormObjNum, "<< /Fields " + fieldsArray + " >>"});
  }

  // Catalog with /AcroForm if requested
  if (includeAcroForm) {
    objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R /AcroForm " +
                           std::to_string(acroFormObjNum) + " 0 R >>"});
  } else {
    objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R >>"});
  }

  // Patch Annots array in page obj (3 0) to reference field widgets.
  std::string annotsArray = "";
  for (int i = 0; i < fieldCount; ++i) {
    annotsArray += std::to_string(firstFieldObj + i) + " 0 R ";
  }
  // Replace placeholder in object 3 body.
  for (auto &o : objs) {
    if (o.num == 3) {
      const std::string needle = "[__ANNOTS__]";
      auto pos = o.body.find(needle);
      if (pos != std::string::npos) {
        o.body.replace(pos, needle.size(), "[" + annotsArray + "]");
      }
      break;
    }
  }

  // Sort objects by object number (xref requires sequential offsets, but order can be any;
  // we'll keep 1..N for clarity).
  std::sort(objs.begin(), objs.end(), [](const Obj &a, const Obj &b) { return a.num < b.num; });

  // Emit PDF with xref
  std::string pdf;
  pdf += "%PDF-1.4\n";

  // Track offsets for xref (index by object number)
  const int maxObjNum = objs.back().num;
  std::vector<long> offsets(maxObjNum + 1, 0);

  for (const auto &o : objs) {
    offsets[o.num] = static_cast<long>(pdf.size());
    pdf += std::to_string(o.num) + " 0 obj\n";
    pdf += o.body + "\n";
    pdf += "endobj\n";
  }

  const long xrefOffset = static_cast<long>(pdf.size());
  pdf += "xref\n";
  pdf += "0 " + std::to_string(maxObjNum + 1) + "\n";
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i <= maxObjNum; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    pdf += buf;
  }

  pdf += "trailer\n";
  pdf += "<< /Size " + std::to_string(maxObjNum + 1) + " /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xrefOffset) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

std::string WriteTempPdf(const std::string &bytes, const std::string &baseName) {
  // Use a predictable filename pattern under the test working directory.
  const std::string path = baseName + ".pdf";
  std::ofstream os(path, std::ios::binary | std::ios::trunc);
  os.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  os.close();
  return path;
}

// Create a PDFDoc across Poppler versions by selecting a constructible overload.
std::unique_ptr<PDFDoc> CreatePDFDocFromPath(const std::string &path) {
  auto fn = std::make_unique<GooString>(path.c_str());

  // Try: PDFDoc(std::unique_ptr<GooString>&&)
  if constexpr (std::is_constructible_v<PDFDoc, std::unique_ptr<GooString> &&>) {
    return std::make_unique<PDFDoc>(std::move(fn));
  }

  // Try: PDFDoc(std::unique_ptr<GooString>&&, GooString*, GooString*)
  if constexpr (std::is_constructible_v<PDFDoc, std::unique_ptr<GooString> &&, GooString *,
                                       GooString *>) {
    return std::make_unique<PDFDoc>(std::move(fn), nullptr, nullptr);
  }

  // Try: PDFDoc(GooString*)
  if constexpr (std::is_constructible_v<PDFDoc, GooString *>) {
    return std::make_unique<PDFDoc>(fn.release());  // transfer ownership if expected
  }

  // Try: PDFDoc(GooString*, GooString*, GooString*)
  if constexpr (std::is_constructible_v<PDFDoc, GooString *, GooString *, GooString *>) {
    return std::make_unique<PDFDoc>(fn.release(), nullptr, nullptr);
  }

  // Try: PDFDoc(const GooString*)
  if constexpr (std::is_constructible_v<PDFDoc, const GooString *>) {
    // Keep storage alive: allocate a second GooString with static lifetime (best effort).
    // (This path should be rare; most builds have owning constructors.)
    static std::vector<std::unique_ptr<GooString>> keepAlive;
    keepAlive.push_back(std::move(fn));
    return std::make_unique<PDFDoc>(keepAlive.back().get());
  }

  // If none matched, fail loudly.
  return nullptr;
}

class FormTest_930 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    if (!globalParams) {
      globalParams = new GlobalParams();
    }
  }
  static void TearDownTestSuite() {
    // Leaving globalParams allocated is common in Poppler unit tests; avoid UAF across tests.
  }
};

}  // namespace

TEST_F(FormTest_930, EmptyDocumentHasZeroFields_930) {
  const std::string pdf = BuildMinimalPdfWithTextFields(/*fieldCount=*/0, /*includeAcroForm=*/false);
  const std::string path = WriteTempPdf(pdf, "form_empty_930");

  auto doc = CreatePDFDocFromPath(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Form form(doc.get());
  EXPECT_EQ(form.getNumFields(), 0);
}

TEST_F(FormTest_930, OneFieldDocumentAllowsAccessToIndexZero_930) {
  const std::string pdf = BuildMinimalPdfWithTextFields(/*fieldCount=*/1, /*includeAcroForm=*/true);
  const std::string path = WriteTempPdf(pdf, "form_onefield_930");

  auto doc = CreatePDFDocFromPath(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Form form(doc.get());
  ASSERT_GE(form.getNumFields(), 1);

  FormField *f0 = form.getRootField(0);
  EXPECT_NE(f0, nullptr);

  // Repeated calls should be stable for the same index (observable behavior).
  EXPECT_EQ(form.getRootField(0), f0);
}

TEST_F(FormTest_930, TwoFieldDocumentProvidesDistinctRootFields_930) {
  const std::string pdf = BuildMinimalPdfWithTextFields(/*fieldCount=*/2, /*includeAcroForm=*/true);
  const std::string path = WriteTempPdf(pdf, "form_twofields_930");

  auto doc = CreatePDFDocFromPath(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Form form(doc.get());
  ASSERT_GE(form.getNumFields(), 2);

  FormField *f0 = form.getRootField(0);
  FormField *f1 = form.getRootField(1);

  EXPECT_NE(f0, nullptr);
  EXPECT_NE(f1, nullptr);

  // With two fields, observable expectation: indices refer to (potentially) different fields.
  // If implementation ever deduplicates, this still allows equality, but in typical PDFs they differ.
  EXPECT_NE(f0, f1);

  // Boundary within range: last valid index should be retrievable.
  const int last = form.getNumFields() - 1;
  EXPECT_NE(form.getRootField(last), nullptr);
}

TEST_F(FormTest_930, NullDocConstructorDiesOrIsRejected_930) {
  // Exceptional/error case: behavior depends on implementation; if it asserts, we verify it.
  // If it doesn't, EXPECT_DEATH_IF_SUPPORTED will be skipped on platforms without death tests.
  EXPECT_DEATH_IF_SUPPORTED(
      {
        Form f(nullptr);
        (void)f.getNumFields();
      },
      ".*");
}