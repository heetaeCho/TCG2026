// FormFieldText_isRichText_910_test.cc
#include <gtest/gtest.h>

#include <cstddef>
#include <cstring>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "GlobalParams.h"
#include "PDFDoc.h"
#include "Catalog.h"
#include "Form.h"
#include "Object.h"
#include "Stream.h"

namespace {

class FormFieldTextRichTextTest_910 : public ::testing::Test {
protected:
  void SetUp() override {
    // Poppler typically requires globalParams to be initialized for many operations.
    // If the test runner already initialized it, don't overwrite it.
    if (globalParams == nullptr) {
      globalParams = new GlobalParams();
      ownsGlobalParams_ = true;
    }
  }

  void TearDown() override {
    doc_.reset();
    if (ownsGlobalParams_) {
      delete globalParams;
      globalParams = nullptr;
      ownsGlobalParams_ = false;
    }
  }

  static std::string BuildMinimalPdfWithTextField(bool includeFf,
                                                  const std::string &ffObjectValue /* e.g. "33554432" or "(oops)" */) {
    // Objects:
    // 1: Catalog
    // 2: Pages
    // 3: Page (with Annots)
    // 4: AcroForm
    // 5: Widget annotation (Parent = 6)
    // 6: Field dict (FT=Tx, Kids=[5], optional Ff)
    const std::string obj1 =
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R /AcroForm 4 0 R >>\n"
        "endobj\n";

    const std::string obj2 =
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n";

    const std::string obj3 =
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 100 100]\n"
        "   /Resources << >>\n"
        "   /Annots [5 0 R]\n"
        ">>\n"
        "endobj\n";

    const std::string obj4 =
        "4 0 obj\n"
        "<< /Fields [6 0 R] >>\n"
        "endobj\n";

    const std::string obj5 =
        "5 0 obj\n"
        "<< /Type /Annot /Subtype /Widget /Rect [0 0 10 10] /P 3 0 R /Parent 6 0 R >>\n"
        "endobj\n";

    std::string obj6 =
        "6 0 obj\n"
        "<< /FT /Tx /T (field1) /Kids [5 0 R]";
    if (includeFf) {
      obj6 += " /Ff " + ffObjectValue;
    }
    obj6 += " >>\nendobj\n";

    const std::string header = "%PDF-1.4\n";
    const std::string body = obj1 + obj2 + obj3 + obj4 + obj5 + obj6;

    // Build xref with correct byte offsets.
    // xref table includes object 0..6
    std::vector<long long> offsets(7, 0);

    std::string pdf = header;
    auto appendObj = [&](int objNum, const std::string &objText) {
      offsets[objNum] = static_cast<long long>(pdf.size());
      pdf += objText;
    };

    appendObj(1, obj1);
    appendObj(2, obj2);
    appendObj(3, obj3);
    appendObj(4, obj4);
    appendObj(5, obj5);
    appendObj(6, obj6);

    const long long xrefOffset = static_cast<long long>(pdf.size());

    auto pad10 = [](long long v) {
      std::string s = std::to_string(v);
      if (s.size() < 10) s = std::string(10 - s.size(), '0') + s;
      return s;
    };

    pdf += "xref\n";
    pdf += "0 7\n";
    pdf += "0000000000 65535 f \n";
    for (int i = 1; i <= 6; ++i) {
      pdf += pad10(offsets[i]) + " 00000 n \n";
    }
    pdf += "trailer\n";
    pdf += "<< /Size 7 /Root 1 0 R >>\n";
    pdf += "startxref\n";
    pdf += std::to_string(xrefOffset) + "\n";
    pdf += "%%EOF\n";
    return pdf;
  }

  FormFieldText *LoadAndGetFirstTextField(const std::string &pdfBytes) {
    // MemStream expects a non-owning buffer; keep it alive by storing it.
    buffer_.assign(pdfBytes.begin(), pdfBytes.end());

    // Poppler's MemStream ctor commonly takes (char*, start, length, Object)
    // and PDFDoc accepts unique_ptr<BaseStream>.
    auto stream = std::unique_ptr<BaseStream>(
        new MemStream(reinterpret_cast<char *>(buffer_.data()),
                      0,
                      static_cast<Guint>(buffer_.size()),
                      Object(objNull)));

    doc_ = std::make_unique<PDFDoc>(std::move(stream));
    if (!doc_ || !doc_->isOk()) {
      return nullptr;
    }

    Catalog *catalog = doc_->getCatalog();
    if (!catalog) {
      return nullptr;
    }

    Form *form = catalog->getForm();
    if (!form) {
      return nullptr;
    }

    if (form->getNumFields() < 1) {
      return nullptr;
    }

    FormField *root = form->getRootField(0);
    if (!root) {
      return nullptr;
    }

    // FormField is polymorphic; FormFieldText is derived.
    return dynamic_cast<FormFieldText *>(root);
  }

private:
  std::unique_ptr<PDFDoc> doc_;
  std::vector<unsigned char> buffer_;
  bool ownsGlobalParams_ = false;
};

} // namespace

TEST_F(FormFieldTextRichTextTest_910, RichTextFlagSet_MakesIsRichTextTrue_910) {
  // PDF spec (and Poppler) use bit position 26 for RichText => 0x2000000 (33554432).
  const std::string pdf = BuildMinimalPdfWithTextField(/*includeFf=*/true, "33554432");
  FormFieldText *field = LoadAndGetFirstTextField(pdf);
  ASSERT_NE(field, nullptr);

  EXPECT_TRUE(field->isRichText());
}

TEST_F(FormFieldTextRichTextTest_910, RichTextFlagNotSet_MakesIsRichTextFalse_910) {
  const std::string pdf = BuildMinimalPdfWithTextField(/*includeFf=*/true, "0");
  FormFieldText *field = LoadAndGetFirstTextField(pdf);
  ASSERT_NE(field, nullptr);

  EXPECT_FALSE(field->isRichText());
}

TEST_F(FormFieldTextRichTextTest_910, MissingFfEntry_DefaultsToNotRichText_910) {
  const std::string pdf = BuildMinimalPdfWithTextField(/*includeFf=*/false, "");
  FormFieldText *field = LoadAndGetFirstTextField(pdf);
  ASSERT_NE(field, nullptr);

  EXPECT_FALSE(field->isRichText());
}

TEST_F(FormFieldTextRichTextTest_910, NonIntegerFfEntry_DoesNotCrash_AndNotRichText_910) {
  // Boundary/error-ish: wrong type for /Ff. Behavior should remain observable through isRichText().
  const std::string pdf = BuildMinimalPdfWithTextField(/*includeFf=*/true, "(notAnInt)");
  FormFieldText *field = LoadAndGetFirstTextField(pdf);
  ASSERT_NE(field, nullptr);

  EXPECT_FALSE(field->isRichText());
}

TEST_F(FormFieldTextRichTextTest_910, IsRichText_IsCallableThroughConstReference_910) {
  const std::string pdf = BuildMinimalPdfWithTextField(/*includeFf=*/true, "33554432");
  FormFieldText *field = LoadAndGetFirstTextField(pdf);
  ASSERT_NE(field, nullptr);

  const FormFieldText &cfield = *field;
  EXPECT_TRUE(cfield.isRichText());
}