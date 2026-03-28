// AnnotStampImageHelper_733_test.cpp
// Unit tests for poppler::AnnotStampImageHelper (black-box tests)
// TEST_ID: 733

#include <gtest/gtest.h>

#include <climits>
#include <cstdint>
#include <fstream>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include "AnnotStampImageHelper.h"

// Poppler dependencies (expected to exist in the codebase)
#include "GooString.h"
#include "PDFDoc.h"
#include "Ref.h"

namespace {

std::string BuildMinimalPdfBytes() {
  // Build a tiny valid PDF with proper xref offsets.
  // Objects: 1=Catalog, 2=Pages, 3=Page
  std::string pdf;
  pdf += "%PDF-1.4\n";

  struct Obj {
    int num;
    std::string body;
    std::size_t offset = 0;
  };

  std::vector<Obj> objs;
  objs.push_back({1, "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"});
  objs.push_back({2, "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"});
  objs.push_back(
      {3, "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 10 10] >>\nendobj\n"});

  // Compute offsets.
  for (auto &o : objs) {
    o.offset = pdf.size();
    pdf += o.body;
  }

  const std::size_t xrefOffset = pdf.size();

  // xref: include object 0 plus 1..3
  pdf += "xref\n";
  pdf += "0 4\n";
  pdf += "0000000000 65535 f \n";

  auto fmt10 = [](std::size_t v) {
    char buf[32] = {0};
    std::snprintf(buf, sizeof(buf), "%010zu", v);
    return std::string(buf);
  };

  for (const auto &o : objs) {
    pdf += fmt10(o.offset);
    pdf += " 00000 n \n";
  }

  pdf += "trailer\n";
  pdf += "<< /Size 4 /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xrefOffset);
  pdf += "\n%%EOF\n";

  return pdf;
}

std::string WriteTempPdfFile(const std::string &bytes) {
  // Write into a deterministic-ish temp file name.
  // (Good enough for unit tests; collisions are unlikely.)
  const std::string path = "annot_stamp_image_helper_733_minimal.pdf";
  std::ofstream out(path, std::ios::binary | std::ios::trunc);
  out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  out.close();
  return path;
}

std::unique_ptr<PDFDoc> OpenPdfDocFromPath(const std::string &path) {
  // Support multiple Poppler API variants via std::is_constructible checks.
  using Doc = PDFDoc;

  // Variant A: PDFDoc(GooString* fileName, GooString* owner, GooString* user, void* gui, bool quiet)
  if constexpr (std::is_constructible_v<Doc, GooString *, GooString *, GooString *, void *, bool>) {
    auto *fileName = new GooString(path.c_str());  // PDFDoc typically takes ownership.
    return std::make_unique<Doc>(fileName, nullptr, nullptr, nullptr, true);
  }

  // Variant B: PDFDoc(std::unique_ptr<GooString> fileName, GooString* owner, GooString* user, void* gui, bool quiet)
  if constexpr (std::is_constructible_v<Doc, std::unique_ptr<GooString>, GooString *, GooString *, void *, bool>) {
    auto fileName = std::make_unique<GooString>(path.c_str());
    return std::make_unique<Doc>(std::move(fileName), nullptr, nullptr, nullptr, true);
  }

  // Variant C: PDFDoc(const std::string& fileName, ...)
  if constexpr (std::is_constructible_v<Doc, std::string, GooString *, GooString *, void *, bool>) {
    return std::make_unique<Doc>(path, nullptr, nullptr, nullptr, true);
  }

  // If Poppler API differs from all of the above, fail loudly at compile time.
  static_assert(
      std::is_constructible_v<Doc, GooString *, GooString *, GooString *, void *, bool> ||
          std::is_constructible_v<Doc, std::unique_ptr<GooString>, GooString *, GooString *, void *, bool> ||
          std::is_constructible_v<Doc, std::string, GooString *, GooString *, void *, bool>,
      "Unsupported PDFDoc constructor signature for this test.");
  return nullptr;
}

PDFDoc *MakeOkDocOrSkip() {
  static std::unique_ptr<PDFDoc> doc;
  if (!doc) {
    const std::string pdfBytes = BuildMinimalPdfBytes();
    const std::string path = WriteTempPdfFile(pdfBytes);
    doc = OpenPdfDocFromPath(path);
  }

  if (!doc) {
    GTEST_SKIP() << "Failed to create PDFDoc (nullptr).";
  }

  // If isOk() exists, ensure it's OK; otherwise just proceed.
  if constexpr (requires(PDFDoc *d) { d->isOk(); }) {
    if (!doc->isOk()) {
      GTEST_SKIP() << "PDFDoc is not OK; cannot test AnnotStampImageHelper reliably.";
    }
  }

  return doc.get();
}

// Helper to build a reasonably-sized buffer to avoid dataLength underflow.
std::vector<char> MakeImageDataBuffer(std::size_t n) {
  std::vector<char> buf(n);
  for (std::size_t i = 0; i < n; ++i) {
    buf[i] = static_cast<char>(i & 0x7f);
  }
  return buf;
}

class AnnotStampImageHelperTest_733 : public ::testing::Test {};

}  // namespace

TEST_F(AnnotStampImageHelperTest_733, GetHeightReflectsConstructorHeight_733) {
  PDFDoc *doc = MakeOkDocOrSkip();

  const int width = 10;
  const int height = 42;
  const int bitsPerComponent = 8;

  // Avoid relying on specific enumerators; use a value that compiles for the ColorSpace type.
  const auto cs = static_cast<ColorSpace>(0);

  auto data = MakeImageDataBuffer(4096);

  AnnotStampImageHelper helper(doc, width, height, cs, bitsPerComponent, data.data(),
                               static_cast<int>(data.size()));

  EXPECT_EQ(helper.getHeight(), height);

  const AnnotStampImageHelper &cref = helper;
  EXPECT_EQ(cref.getHeight(), height);
}

TEST_F(AnnotStampImageHelperTest_733, GetWidthReflectsConstructorWidth_733) {
  PDFDoc *doc = MakeOkDocOrSkip();

  const int width = 77;
  const int height = 3;
  const int bitsPerComponent = 8;
  const auto cs = static_cast<ColorSpace>(0);

  auto data = MakeImageDataBuffer(4096);

  AnnotStampImageHelper helper(doc, width, height, cs, bitsPerComponent, data.data(),
                               static_cast<int>(data.size()));

  EXPECT_EQ(helper.getWidth(), width);
}

TEST_F(AnnotStampImageHelperTest_733, SoftMaskConstructorPreservesDimensions_733) {
  PDFDoc *doc = MakeOkDocOrSkip();

  const int width = 5;
  const int height = 6;
  const int bitsPerComponent = 8;
  const auto cs = static_cast<ColorSpace>(0);

  auto data = MakeImageDataBuffer(4096);

  // Use a default/zero Ref as a boundary-ish input (do not assume meaning).
  Ref softMaskRef{};
  AnnotStampImageHelper helper(doc, width, height, cs, bitsPerComponent, data.data(),
                               static_cast<int>(data.size()), softMaskRef);

  EXPECT_EQ(helper.getWidth(), width);
  EXPECT_EQ(helper.getHeight(), height);
}

TEST_F(AnnotStampImageHelperTest_733, GetRefIsStableAcrossCalls_733) {
  PDFDoc *doc = MakeOkDocOrSkip();

  const int width = 2;
  const int height = 2;
  const int bitsPerComponent = 8;
  const auto cs = static_cast<ColorSpace>(0);

  auto data = MakeImageDataBuffer(4096);

  AnnotStampImageHelper helper(doc, width, height, cs, bitsPerComponent, data.data(),
                               static_cast<int>(data.size()));

  const Ref r1 = helper.getRef();
  const Ref r2 = helper.getRef();

  // Black-box invariant we can safely assert: repeated calls should return the same Ref value.
  EXPECT_EQ(r1.num, r2.num);
  EXPECT_EQ(r1.gen, r2.gen);
}

TEST_F(AnnotStampImageHelperTest_733, RemoveAnnotStampImageObjectIsCallableAndIdempotent_733) {
  PDFDoc *doc = MakeOkDocOrSkip();

  const int width = 1;
  const int height = 1;
  const int bitsPerComponent = 8;
  const auto cs = static_cast<ColorSpace>(0);

  auto data = MakeImageDataBuffer(4096);

  AnnotStampImageHelper helper(doc, width, height, cs, bitsPerComponent, data.data(),
                               static_cast<int>(data.size()));

  // Observable behavior: method should be callable; call twice to exercise idempotence-like behavior.
  EXPECT_NO_THROW(helper.removeAnnotStampImageObject());
  EXPECT_NO_THROW(helper.removeAnnotStampImageObject());

  // After removal, getters should remain callable (no assumptions on returned values changing).
  EXPECT_NO_THROW((void)helper.getRef());
  EXPECT_NO_THROW((void)helper.getWidth());
  EXPECT_NO_THROW((void)helper.getHeight());
}

TEST_F(AnnotStampImageHelperTest_733, BoundaryZeroDimensionsIfAccepted_733) {
  PDFDoc *doc = MakeOkDocOrSkip();

  const int width = 0;
  const int height = 0;
  const int bitsPerComponent = 8;
  const auto cs = static_cast<ColorSpace>(0);

  auto data = MakeImageDataBuffer(4096);

  // Some implementations may reject zero sizes (assert/throw). We only check observable outcomes
  // if construction succeeds. (No inference about internal validation rules.)
  try {
    AnnotStampImageHelper helper(doc, width, height, cs, bitsPerComponent, data.data(),
                                 static_cast<int>(data.size()));
    EXPECT_EQ(helper.getWidth(), width);
    EXPECT_EQ(helper.getHeight(), height);
  } catch (...) {
    SUCCEED() << "Constructor rejected zero dimensions (acceptable boundary behavior).";
  }
}

TEST_F(AnnotStampImageHelperTest_733, LargeButReasonableDimensionsRoundTrip_733) {
  PDFDoc *doc = MakeOkDocOrSkip();

  const int width = 1024;
  const int height = 768;
  const int bitsPerComponent = 8;
  const auto cs = static_cast<ColorSpace>(0);

  // Provide a sizable buffer; do not assume exact required size.
  auto data = MakeImageDataBuffer(1024 * 8);

  AnnotStampImageHelper helper(doc, width, height, cs, bitsPerComponent, data.data(),
                               static_cast<int>(data.size()));

  EXPECT_EQ(helper.getWidth(), width);
  EXPECT_EQ(helper.getHeight(), height);
}