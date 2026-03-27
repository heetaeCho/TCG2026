// TEST_ID: 911
// File: form_field_text_getmaxlen_test_911.cpp

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

#include "Form.h"

// Poppler headers for PDF loading / catalog access.
#include "Catalog.h"
#include "PDFDoc.h"
#include "GooString.h"

namespace {

std::string WriteTempPdfWithSingleTextField(std::optional<int> maxLen) {
  auto buildPdf = [&](std::optional<int> ml) -> std::string {
    std::ostringstream obj1, obj2, obj3, obj4;

    // 1: Catalog
    obj1 << "1 0 obj\n"
         << "<< /Type /Catalog /Pages 2 0 R /AcroForm 3 0 R >>\n"
         << "endobj\n";

    // 2: Pages (empty)
    obj2 << "2 0 obj\n"
         << "<< /Type /Pages /Kids [] /Count 0 >>\n"
         << "endobj\n";

    // 3: AcroForm
    obj3 << "3 0 obj\n"
         << "<< /Fields [4 0 R] >>\n"
         << "endobj\n";

    // 4: Field (text)
    obj4 << "4 0 obj\n"
         << "<< /FT /Tx /T (field1) /V (hello)";
    if (ml.has_value()) {
      obj4 << " /MaxLen " << *ml;
    }
    obj4 << " >>\n"
         << "endobj\n";

    const std::string header = "%PDF-1.4\n";
    const std::string body1 = obj1.str();
    const std::string body2 = obj2.str();
    const std::string body3 = obj3.str();
    const std::string body4 = obj4.str();

    // Compute byte offsets for xref.
    // xref entry 0 is the free object; entries 1..4 point to the objects above.
    const long off0 = 0;
    const long off1 = static_cast<long>(header.size());
    const long off2 = off1 + static_cast<long>(body1.size());
    const long off3 = off2 + static_cast<long>(body2.size());
    const long off4 = off3 + static_cast<long>(body3.size());

    std::ostringstream xref;
    xref << "xref\n"
         << "0 5\n"
         << "0000000000 65535 f \n";

    auto xrefLine = [&](long off) {
      std::ostringstream line;
      line.width(10);
      line.fill('0');
      line << off;
      line << " 00000 n \n";
      return line.str();
    };

    xref << xrefLine(off1);
    xref << xrefLine(off2);
    xref << xrefLine(off3);
    xref << xrefLine(off4);

    std::ostringstream trailer;
    trailer << "trailer\n"
            << "<< /Size 5 /Root 1 0 R >>\n"
            << "startxref\n";

    const std::string xrefStr = xref.str();
    const long startXref = off4 + static_cast<long>(body4.size());

    trailer << startXref << "\n"
            << "%%EOF\n";

    std::ostringstream full;
    full << header << body1 << body2 << body3 << body4 << xrefStr << trailer.str();
    return full.str();
  };

  // Create a temp filename (portable enough for test environments).
  // Use a predictable pattern and let std::tmpnam generate a unique name.
  char buf[L_tmpnam];
  const char *name = std::tmpnam(buf);
  std::string path = name ? std::string(name) : std::string("poppler_formfieldtext_911.pdf");

  std::ofstream out(path, std::ios::binary);
  out << buildPdf(maxLen);
  out.close();

  return path;
}

std::unique_ptr<PDFDoc> OpenPdfDoc(const std::string &path) {
  // Try a couple of common PDFDoc constructor shapes across Poppler versions.
  // We only use public/available APIs; if one isn't available in a given build,
  // the corresponding branch is discarded at compile time.

  // 1) PDFDoc(std::unique_ptr<GooString> fileNameA, ...)
  if constexpr (std::is_constructible_v<PDFDoc, std::unique_ptr<GooString>>) {
    auto gs = std::make_unique<GooString>(path.c_str());
    return std::make_unique<PDFDoc>(std::move(gs));
  }
  // 2) PDFDoc(GooString *fileNameA, ...)
  else if constexpr (std::is_constructible_v<PDFDoc, GooString *>) {
    auto *gs = new GooString(path.c_str());
    return std::unique_ptr<PDFDoc>(new PDFDoc(gs));
  } else {
    return nullptr;
  }
}

FormFieldText *GetFirstTextField(PDFDoc *doc) {
  if (!doc) return nullptr;
  Catalog *cat = doc->getCatalog();
  if (!cat) return nullptr;

  Form *form = cat->getForm();
  if (!form) return nullptr;

  // These APIs exist in Poppler's Form interface; if your build differs,
  // compilation will fail here (indicating the access path should be updated).
  const int n = form->getNumFields();
  for (int i = 0; i < n; ++i) {
    FormField *ff = form->getField(i);
    if (!ff) continue;
    if (auto *txt = dynamic_cast<FormFieldText *>(ff)) {
      return txt;
    }
  }
  return nullptr;
}

}  // namespace

class FormFieldTextTest_911 : public ::testing::Test {};

TEST_F(FormFieldTextTest_911, ReadsMaxLenWhenPresent_911) {
  const std::string path = WriteTempPdfWithSingleTextField(10);
  auto doc = OpenPdfDoc(path);
  ASSERT_NE(doc, nullptr);

  // Many Poppler builds expose isOk(); if not available, this line can be removed.
  if constexpr (requires(PDFDoc *d) { d->isOk(); }) {
    ASSERT_TRUE(doc->isOk());
  }

  FormFieldText *txt = GetFirstTextField(doc.get());
  ASSERT_NE(txt, nullptr);

  // Observable behavior: getMaxLen() returns an int.
  // When /MaxLen is present, it should be reflected in the observable value.
  EXPECT_EQ(txt->getMaxLen(), 10);
}

TEST_F(FormFieldTextTest_911, MaxLenZeroIsHandled_911) {
  const std::string path = WriteTempPdfWithSingleTextField(0);
  auto doc = OpenPdfDoc(path);
  ASSERT_NE(doc, nullptr);

  FormFieldText *txt = GetFirstTextField(doc.get());
  ASSERT_NE(txt, nullptr);

  EXPECT_EQ(txt->getMaxLen(), 0);
}

TEST_F(FormFieldTextTest_911, MissingMaxLenDoesNotCrashAndIsNonNegative_911) {
  const std::string path = WriteTempPdfWithSingleTextField(std::nullopt);
  auto doc = OpenPdfDoc(path);
  ASSERT_NE(doc, nullptr);

  FormFieldText *txt = GetFirstTextField(doc.get());
  ASSERT_NE(txt, nullptr);

  // Without assuming a specific default, we at least verify it is a valid int
  // value for a length constraint (non-negative) and is callable.
  EXPECT_GE(txt->getMaxLen(), 0);
}

TEST_F(FormFieldTextTest_911, DifferentMaxLenValuesProduceDifferentResults_911) {
  const std::string path10 = WriteTempPdfWithSingleTextField(10);
  const std::string path20 = WriteTempPdfWithSingleTextField(20);

  auto doc10 = OpenPdfDoc(path10);
  auto doc20 = OpenPdfDoc(path20);
  ASSERT_NE(doc10, nullptr);
  ASSERT_NE(doc20, nullptr);

  FormFieldText *txt10 = GetFirstTextField(doc10.get());
  FormFieldText *txt20 = GetFirstTextField(doc20.get());
  ASSERT_NE(txt10, nullptr);
  ASSERT_NE(txt20, nullptr);

  EXPECT_NE(txt10->getMaxLen(), txt20->getMaxLen());
}

TEST_F(FormFieldTextTest_911, NegativeMaxLenIsHandledGracefully_911) {
  const std::string path = WriteTempPdfWithSingleTextField(-5);
  auto doc = OpenPdfDoc(path);
  ASSERT_NE(doc, nullptr);

  FormFieldText *txt = GetFirstTextField(doc.get());
  ASSERT_NE(txt, nullptr);

  // Don’t assume clamping behavior; just ensure it’s callable and not absurd
  // for a "max length" contract (should not be negative in observable result).
  EXPECT_GE(txt->getMaxLen(), 0);
}