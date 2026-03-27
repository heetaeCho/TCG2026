// FormFieldText_isFileSelect_906_test.cpp
//
// Unit tests for FormFieldText::isFileSelect()
// Constraints honored:
// - Treat implementation as black box
// - No access to private/protected internal state
// - Verify observable behavior via real PDF parsing + public APIs only
//
// NOTE: These tests create minimal PDFs on-the-fly and rely on Poppler core
// parsing to produce FormFieldText instances with/without the FileSelect flag.

#include <gtest/gtest.h>

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "GlobalParams.h"
#include "GooString.h"
#include "PDFDoc.h"
#include "Catalog.h"
#include "Form.h"

namespace {

class FormFieldTextTest_906 : public ::testing::Test {
protected:
  void SetUp() override
  {
    // Poppler typically requires globalParams to be initialized.
    // Some builds already initialize it; creating it twice can be problematic.
    // So only create if needed.
    if (globalParams == nullptr) {
      globalParams = new GlobalParams(nullptr);
      ownsGlobalParams_ = true;
    }
  }

  void TearDown() override
  {
    if (ownsGlobalParams_) {
      delete globalParams;
      globalParams = nullptr;
      ownsGlobalParams_ = false;
    }
  }

  static std::string WriteTempPdf(const std::string &fileName, const std::string &pdfBytes)
  {
    std::ofstream ofs(fileName, std::ios::binary);
    ofs.write(pdfBytes.data(), static_cast<std::streamsize>(pdfBytes.size()));
    ofs.close();
    return fileName;
  }

  static std::unique_ptr<PDFDoc> OpenPdf(const std::string &path)
  {
    auto gs = std::make_unique<GooString>(path.c_str());
    // Common Poppler ctor: PDFDoc(GooString *fileNameA, GooString *ownerPassword,
    // GooString *userPassword, void *guiDataA = nullptr)
    // We pass null passwords.
    return std::make_unique<PDFDoc>(gs.get(), nullptr, nullptr, nullptr);
  }

  // Helper: find a form field by fully qualified name.
  // Uses only public traversal APIs available on Poppler Form.
  static FormField *FindFieldByName(Form *form, const std::string &name)
  {
    if (!form) {
      return nullptr;
    }

    const int n = form->getNumFields();
    for (int i = 0; i < n; ++i) {
      FormField *f = form->getField(i);
      if (!f) {
        continue;
      }
      const GooString *partialName = f->getPartialName();
      const GooString *fullyName = f->getFullyQualifiedName();

      if (fullyName && fullyName->toStr() == name) {
        return f;
      }
      if (partialName && partialName->toStr() == name) {
        return f;
      }
    }
    return nullptr;
  }

  bool ownsGlobalParams_ = false;
};

// Minimal PDF generator.
// We generate two text fields:
// - "NormalText" with /Ff 0
// - "FileSelectText" with /Ff flag that corresponds to FileSelect in the PDF spec.
// In the PDF 1.7 spec, "FileSelect" is bit position 21 (1-based), i.e. 1 << 20.
static std::string MinimalPdfWithTwoTextFields()
{
  // Keep it simple: 1 page, AcroForm, two widget annotations as fields.
  // Offsets are not computed precisely; we use a basic xref with placeholder offsets.
  // Poppler is generally tolerant if xref offsets are correct; so we provide correct offsets.
  //
  // We'll build the PDF with computed offsets for robustness.

  struct Obj {
    int num;
    std::string body;
    size_t offset = 0;
  };

  const int kFileSelectFlag = (1 << 20); // PDF spec: FileSelect for Tx fields.

  std::vector<Obj> objs;

  // 1: Catalog
  objs.push_back({1,
                  "1 0 obj\n"
                  "<< /Type /Catalog /Pages 2 0 R /AcroForm 6 0 R >>\n"
                  "endobj\n"});

  // 2: Pages
  objs.push_back({2,
                  "2 0 obj\n"
                  "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
                  "endobj\n"});

  // 3: Page with Annots
  objs.push_back({3,
                  "3 0 obj\n"
                  "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
                  "   /Resources << >>\n"
                  "   /Annots [4 0 R 5 0 R]\n"
                  ">>\n"
                  "endobj\n"});

  // 4: Normal text field widget + field dictionary
  objs.push_back({4,
                  "4 0 obj\n"
                  "<< /Type /Annot /Subtype /Widget\n"
                  "   /Rect [50 700 300 730]\n"
                  "   /FT /Tx\n"
                  "   /T (NormalText)\n"
                  "   /Ff 0\n"
                  "   /P 3 0 R\n"
                  ">>\n"
                  "endobj\n"});

  // 5: FileSelect text field widget + field dictionary
  objs.push_back({5,
                  "5 0 obj\n"
                  "<< /Type /Annot /Subtype /Widget\n"
                  "   /Rect [50 650 300 680]\n"
                  "   /FT /Tx\n"
                  "   /T (FileSelectText)\n"
                  "   /Ff " + std::to_string(kFileSelectFlag) + "\n"
                  "   /P 3 0 R\n"
                  ">>\n"
                  "endobj\n"});

  // 6: AcroForm references both fields
  objs.push_back({6,
                  "6 0 obj\n"
                  "<< /Fields [4 0 R 5 0 R] >>\n"
                  "endobj\n"});

  std::string pdf;
  pdf += "%PDF-1.7\n";
  pdf += "%\xE2\xE3\xCF\xD3\n";

  // Compute offsets.
  for (auto &o : objs) {
    o.offset = pdf.size();
    pdf += o.body;
  }

  const size_t xrefOffset = pdf.size();

  // xref table: 0..6
  pdf += "xref\n";
  pdf += "0 7\n";
  pdf += "0000000000 65535 f \n";
  for (const auto &o : objs) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010zu 00000 n \n", o.offset);
    pdf += buf;
  }

  // trailer
  pdf += "trailer\n";
  pdf += "<< /Size 7 /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xrefOffset) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

static std::string MinimalPdfMissingFfForTextField()
{
  // Single field without /Ff entry (boundary).
  struct Obj {
    int num;
    std::string body;
    size_t offset = 0;
  };
  std::vector<Obj> objs;

  objs.push_back({1,
                  "1 0 obj\n"
                  "<< /Type /Catalog /Pages 2 0 R /AcroForm 5 0 R >>\n"
                  "endobj\n"});
  objs.push_back({2,
                  "2 0 obj\n"
                  "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
                  "endobj\n"});
  objs.push_back({3,
                  "3 0 obj\n"
                  "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
                  "   /Resources << >>\n"
                  "   /Annots [4 0 R]\n"
                  ">>\n"
                  "endobj\n"});
  objs.push_back({4,
                  "4 0 obj\n"
                  "<< /Type /Annot /Subtype /Widget\n"
                  "   /Rect [50 700 300 730]\n"
                  "   /FT /Tx\n"
                  "   /T (NoFfText)\n"
                  "   /P 3 0 R\n"
                  ">>\n"
                  "endobj\n"});
  objs.push_back({5,
                  "5 0 obj\n"
                  "<< /Fields [4 0 R] >>\n"
                  "endobj\n"});

  std::string pdf;
  pdf += "%PDF-1.7\n";
  pdf += "%\xE2\xE3\xCF\xD3\n";

  for (auto &o : objs) {
    o.offset = pdf.size();
    pdf += o.body;
  }

  const size_t xrefOffset = pdf.size();
  pdf += "xref\n";
  pdf += "0 6\n";
  pdf += "0000000000 65535 f \n";
  for (const auto &o : objs) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010zu 00000 n \n", o.offset);
    pdf += buf;
  }
  pdf += "trailer\n";
  pdf += "<< /Size 6 /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xrefOffset) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

} // namespace

TEST_F(FormFieldTextTest_906, NormalTextField_FileSelectIsFalse_906)
{
  const std::string path = WriteTempPdf("FormFieldText_906_normal_vs_fileselect.pdf",
                                        MinimalPdfWithTwoTextFields());
  auto doc = OpenPdf(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Catalog *catalog = doc->getCatalog();
  ASSERT_NE(catalog, nullptr);

  Form *form = catalog->getForm();
  ASSERT_NE(form, nullptr);

  FormField *field = FindFieldByName(form, "NormalText");
  ASSERT_NE(field, nullptr);

  auto *textField = dynamic_cast<FormFieldText *>(field);
  ASSERT_NE(textField, nullptr);

  const bool v1 = textField->isFileSelect();
  const bool v2 = textField->isFileSelect(); // stable across repeated calls
  EXPECT_EQ(v1, v2);

  // For a field explicitly marked /Ff 0 in the PDF, FileSelect should not be enabled.
  EXPECT_FALSE(v1);
}

TEST_F(FormFieldTextTest_906, FileSelectTextField_FileSelectIsTrue_906)
{
  const std::string path = WriteTempPdf("FormFieldText_906_normal_vs_fileselect.pdf",
                                        MinimalPdfWithTwoTextFields());
  auto doc = OpenPdf(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Catalog *catalog = doc->getCatalog();
  ASSERT_NE(catalog, nullptr);

  Form *form = catalog->getForm();
  ASSERT_NE(form, nullptr);

  FormField *field = FindFieldByName(form, "FileSelectText");
  ASSERT_NE(field, nullptr);

  auto *textField = dynamic_cast<FormFieldText *>(field);
  ASSERT_NE(textField, nullptr);

  const bool v1 = textField->isFileSelect();
  const bool v2 = textField->isFileSelect(); // stable across repeated calls
  EXPECT_EQ(v1, v2);

  // For a field explicitly marked with the FileSelect bit in /Ff, isFileSelect() should be true.
  EXPECT_TRUE(v1);
}

TEST_F(FormFieldTextTest_906, IsFileSelect_IsCallableOnConstInstance_906)
{
  const std::string path = WriteTempPdf("FormFieldText_906_const.pdf", MinimalPdfWithTwoTextFields());
  auto doc = OpenPdf(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Catalog *catalog = doc->getCatalog();
  ASSERT_NE(catalog, nullptr);

  Form *form = catalog->getForm();
  ASSERT_NE(form, nullptr);

  FormField *field = FindFieldByName(form, "FileSelectText");
  ASSERT_NE(field, nullptr);

  auto *textField = dynamic_cast<FormFieldText *>(field);
  ASSERT_NE(textField, nullptr);

  const FormFieldText &asConst = *textField;
  const bool v1 = asConst.isFileSelect();
  const bool v2 = asConst.isFileSelect();
  EXPECT_EQ(v1, v2);
  EXPECT_TRUE(v1);
}

TEST_F(FormFieldTextTest_906, MissingFfEntry_DoesNotCrash_AndIsStable_906)
{
  const std::string path =
      WriteTempPdf("FormFieldText_906_missing_ff.pdf", MinimalPdfMissingFfForTextField());
  auto doc = OpenPdf(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Catalog *catalog = doc->getCatalog();
  ASSERT_NE(catalog, nullptr);

  Form *form = catalog->getForm();
  ASSERT_NE(form, nullptr);

  FormField *field = FindFieldByName(form, "NoFfText");
  ASSERT_NE(field, nullptr);

  auto *textField = dynamic_cast<FormFieldText *>(field);
  ASSERT_NE(textField, nullptr);

  const bool v1 = textField->isFileSelect();
  const bool v2 = textField->isFileSelect();
  EXPECT_EQ(v1, v2);

  // We don't assume Poppler's default mapping beyond stability; however,
  // in typical PDF semantics, absence of /Ff implies flag not set.
  // This expectation is aligned with the document we constructed.
  EXPECT_FALSE(v1);
}

TEST_F(FormFieldTextTest_906, InvalidPdf_DocumentNotOk_906)
{
  const std::string badPdf = "%PDF-1.7\n1 0 obj <<>> endobj\n%%EOF\n"; // malformed (no xref/root)
  const std::string path = WriteTempPdf("FormFieldText_906_invalid.pdf", badPdf);

  auto doc = OpenPdf(path);
  ASSERT_TRUE(doc);

  // Observable error case: parser indicates failure via isOk().
  EXPECT_FALSE(doc->isOk());
}