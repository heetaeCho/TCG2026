// Page_getAnnotsObject_723_test.cpp
#include <gtest/gtest.h>

#include <cstdio>
#include <cstring>
#include <fstream>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "poppler/GlobalParams.h"
#include "poppler/PDFDoc.h"
#include "poppler/Page.h"
#include "poppler/Object.h"
#include "poppler/XRef.h"

namespace {

class PageGetAnnotsObjectTest_723 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Poppler typically requires globalParams to be initialized.
    if (!globalParams) {
      globalParams = std::make_unique<GlobalParams>();
    }
  }

  static std::string BuildMinimalPdf(bool withAnnot) {
    // Build a tiny valid PDF with correct xref offsets.
    // Objects:
    // 1 0: Catalog
    // 2 0: Pages
    // 3 0: Page (optionally with /Annots [5 0 R])
    // 4 0: Contents (empty stream)
    // 5 0: Annotation dict (optional)
    struct Obj {
      int num;
      std::string body;
    };

    std::vector<Obj> objs;
    objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R >>"});
    objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"});

    std::string pageDict = "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 100 100] /Contents 4 0 R";
    if (withAnnot) {
      pageDict += " /Annots [5 0 R]";
    }
    pageDict += " >>";
    objs.push_back({3, pageDict});

    // Empty content stream
    objs.push_back({4, "<< /Length 0 >>\nstream\n\nendstream"});

    if (withAnnot) {
      // Simple text annotation
      objs.push_back(
          {5, "<< /Type /Annot /Subtype /Text /Rect [10 10 20 20] /Contents (Hi) >>"});
    }

    std::string pdf;
    pdf += "%PDF-1.4\n";

    // Track offsets (byte positions) for xref
    // xref needs an entry for object 0 as free, then 1..maxObj.
    int maxObj = 0;
    for (const auto &o : objs) maxObj = std::max(maxObj, o.num);

    std::vector<long long> offsets(static_cast<size_t>(maxObj + 1), 0);
    offsets[0] = 0;

    for (const auto &o : objs) {
      offsets[static_cast<size_t>(o.num)] = static_cast<long long>(pdf.size());
      pdf += std::to_string(o.num) + " 0 obj\n";
      pdf += o.body + "\n";
      pdf += "endobj\n";
    }

    const long long xrefPos = static_cast<long long>(pdf.size());
    pdf += "xref\n";
    pdf += "0 " + std::to_string(maxObj + 1) + "\n";
    pdf += "0000000000 65535 f \n";
    for (int i = 1; i <= maxObj; ++i) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010lld", offsets[static_cast<size_t>(i)]);
      pdf += std::string(buf) + " 00000 n \n";
    }

    pdf += "trailer\n";
    pdf += "<< /Size " + std::to_string(maxObj + 1) + " /Root 1 0 R >>\n";
    pdf += "startxref\n";
    pdf += std::to_string(xrefPos) + "\n";
    pdf += "%%EOF\n";

    return pdf;
  }

  static std::string WriteTempPdf(const std::string &bytes, const char *tag) {
    // Write to a temp file path.
    // Use a semi-unique name per process.
    std::string path = std::string("poppler_page_annots_") + tag + "_723.pdf";
    std::ofstream out(path, std::ios::binary);
    out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    out.close();
    return path;
  }

  // -------- PDFDoc factory with SFINAE to survive minor API differences --------
  template <typename... Args>
  static auto MakeDocImpl(int, Args &&...args)
      -> decltype(std::make_unique<PDFDoc>(std::forward<Args>(args)...)) {
    return std::make_unique<PDFDoc>(std::forward<Args>(args)...);
  }

  template <typename... Args>
  static std::unique_ptr<PDFDoc> MakeDocImpl(long, Args &&...) {
    return nullptr;
  }

  static std::unique_ptr<PDFDoc> OpenDocFromFile(const std::string &path) {
    // Try common Poppler PDFDoc constructors.
    // 1) PDFDoc(std::unique_ptr<GooString>)
    {
      auto gs = std::make_unique<GooString>(path.c_str());
      if (auto doc = MakeDocImpl(0, std::move(gs))) return doc;
    }
    // 2) PDFDoc(std::unique_ptr<GooString>, GooString*, GooString*)
    {
      auto gs = std::make_unique<GooString>(path.c_str());
      if (auto doc = MakeDocImpl(0, std::move(gs), (GooString *)nullptr, (GooString *)nullptr))
        return doc;
    }
    // 3) PDFDoc(GooString*, GooString*, GooString*)
    {
      auto *gs = new GooString(path.c_str());
      if (auto doc = MakeDocImpl(0, gs, (GooString *)nullptr, (GooString *)nullptr)) {
        return doc;
      }
      delete gs;
    }
    // 4) PDFDoc(const GooString*, const GooString*, const GooString*)
    {
      auto *gs = new GooString(path.c_str());
      if (auto doc =
              MakeDocImpl(0, static_cast<const GooString *>(gs),
                          static_cast<const GooString *>(nullptr),
                          static_cast<const GooString *>(nullptr))) {
        delete gs; // doc likely copied/owned internally in this signature
        return doc;
      }
      delete gs;
    }

    return nullptr;
  }

  template <class T>
  static auto HasGetXRef(int) -> decltype(std::declval<T *>()->getXRef(), std::true_type{});
  template <class T>
  static std::false_type HasGetXRef(long);

  static XRef *TryGetDocXRef(PDFDoc *doc) {
    if constexpr (decltype(HasGetXRef<PDFDoc>(0))::value) {
      return doc->getXRef();
    } else {
      return nullptr;
    }
  }

  static std::string PrintObjectToString(const Object &obj) {
#if defined(__GLIBC__) || defined(__APPLE__)
    // Prefer open_memstream when available.
    char *buf = nullptr;
    size_t size = 0;
    FILE *f = open_memstream(&buf, &size);
    if (!f) return {};
    obj.print(f);
    std::fflush(f);
    std::fclose(f);
    std::string s;
    if (buf && size) s.assign(buf, buf + size);
    if (buf) std::free(buf);
    return s;
#else
    // Fallback: tmpfile-based capture.
    FILE *f = std::tmpfile();
    if (!f) return {};
    obj.print(f);
    std::fflush(f);
    std::fseek(f, 0, SEEK_END);
    long len = std::ftell(f);
    std::fseek(f, 0, SEEK_SET);
    std::string s;
    if (len > 0) {
      s.resize(static_cast<size_t>(len));
      std::fread(&s[0], 1, static_cast<size_t>(len), f);
    }
    std::fclose(f);
    return s;
#endif
  }
};

// Normal operation: without annots, should return something representing "no annots".
TEST_F(PageGetAnnotsObjectTest_723, NoAnnots_ReturnsNullOrEmptyArray_723) {
  const std::string pdf = BuildMinimalPdf(/*withAnnot=*/false);
  const std::string path = WriteTempPdf(pdf, "noannots");

  auto doc = OpenDocFromFile(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  Object annots = page->getAnnotsObject(nullptr);

  // Be tolerant: Poppler may represent missing Annots as null or empty array depending on version.
  if (annots.isNull()) {
    SUCCEED();
  } else if (annots.isArray()) {
    EXPECT_EQ(annots.arrayGetLength(), 0);
  } else {
    // Observable error case: if implementation yields an error/none, accept only explicit "none/error".
    EXPECT_TRUE(annots.isNone() || annots.isError())
        << "Unexpected annots object type: " << annots.getTypeName();
  }
}

// Normal operation: with one annotation, returned annots object should be an array with at least 1 element.
TEST_F(PageGetAnnotsObjectTest_723, WithAnnots_ReturnsArrayWithAtLeastOneElement_723) {
  const std::string pdf = BuildMinimalPdf(/*withAnnot=*/true);
  const std::string path = WriteTempPdf(pdf, "withannots");

  auto doc = OpenDocFromFile(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  Object annots = page->getAnnotsObject(nullptr);

  ASSERT_TRUE(annots.isArray()) << "Expected /Annots to fetch to an array, got: "
                                << annots.getTypeName();

  EXPECT_GE(annots.arrayGetLength(), 1);

  // Boundary-ish: fetching first element should not crash; it may be a dict, ref, or something version-specific.
  Object first = annots.arrayGet(0, /*recursion=*/0);
  EXPECT_FALSE(first.isNone());
}

// Boundary: calling multiple times should be stable (doesn't crash, and type is consistent).
TEST_F(PageGetAnnotsObjectTest_723, RepeatedCalls_AreStableAndConsistent_723) {
  const std::string pdf = BuildMinimalPdf(/*withAnnot=*/true);
  const std::string path = WriteTempPdf(pdf, "repeat");

  auto doc = OpenDocFromFile(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  Object a1 = page->getAnnotsObject(nullptr);
  Object a2 = page->getAnnotsObject(nullptr);

  // Compare printable representations to avoid relying on internal equality.
  const std::string s1 = PrintObjectToString(a1);
  const std::string s2 = PrintObjectToString(a2);
  EXPECT_EQ(s1, s2);
}

// Verification of external interaction selection: if PDFDoc exposes getXRef(), passing it explicitly
// should match passing nullptr (because nullptr implies using the page's own xref).
TEST_F(PageGetAnnotsObjectTest_723, ExplicitDocXRef_MatchesNullptrBehavior_WhenAvailable_723) {
  const std::string pdf = BuildMinimalPdf(/*withAnnot=*/true);
  const std::string path = WriteTempPdf(pdf, "xrefmatch");

  auto doc = OpenDocFromFile(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  XRef *xref = TryGetDocXRef(doc.get());
  if (!xref) {
    GTEST_SKIP() << "PDFDoc::getXRef() not available in this build.";
  }

  Object viaNull = page->getAnnotsObject(nullptr);
  Object viaXref = page->getAnnotsObject(xref);

  EXPECT_EQ(PrintObjectToString(viaNull), PrintObjectToString(viaXref));
}

} // namespace