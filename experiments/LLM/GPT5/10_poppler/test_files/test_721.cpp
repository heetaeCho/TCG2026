// File: page_getref_test.cpp
// Unit tests for Page::getRef()
// The TEST_ID is 721

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

// Poppler headers (paths may vary slightly depending on your build setup)
#include "PDFDoc.h"
#include "Catalog.h"
#include "XRef.h"
#include "Object.h"
#include "Stream.h"
#include "GlobalParams.h"
#include "goo/GooString.h"

// -----------------------
// Helpers (test-only)
// -----------------------

namespace {

// Some Poppler builds require globalParams to exist for PDFDoc parsing/rendering.
// We keep it minimal and only ensure it's initialized once.
class GlobalParamsGuard {
public:
    GlobalParamsGuard()
    {
        // In many Poppler versions, globalParams is a global pointer.
        // If your tree uses std::unique_ptr or a different mechanism, adjust here.
        if (!globalParams) {
            globalParams = new GlobalParams(nullptr);
        }
    }
    ~GlobalParamsGuard() = default;
};

// Build a minimal PDF with N pages, where each page has a specified (objNum, objGen).
// We generate a classic xref table with correct byte offsets.
// This is purely to create controlled, parseable inputs for black-box testing.
struct PdfObjectSpec {
    int objNum;
    int objGen;
    std::string body; // without surrounding "obj/endobj"
};

static std::string BuildPdfWithObjectsAndXref(const std::vector<PdfObjectSpec> &objs, int rootObjNum, int rootObjGen)
{
    std::string pdf;
    pdf.reserve(8192);

    auto append = [&](const std::string &s) { pdf += s; };
    auto appendLine = [&](const std::string &s) {
        pdf += s;
        pdf += "\n";
    };

    appendLine("%PDF-1.4");
    // Binary comment line (helps some parsers, but not strictly required)
    appendLine("%\xE2\xE3\xCF\xD3");

    // Track offsets for xref
    // xref table size is maxObjNum+1 (including object 0)
    int maxObjNum = 0;
    for (const auto &o : objs) {
        if (o.objNum > maxObjNum)
            maxObjNum = o.objNum;
    }

    std::vector<long long> offsets(maxObjNum + 1, -1);

    // Write objects in the given order (caller should ensure all referenced objects exist)
    for (const auto &o : objs) {
        offsets[o.objNum] = static_cast<long long>(pdf.size());
        append(std::to_string(o.objNum));
        append(" ");
        append(std::to_string(o.objGen));
        appendLine(" obj");
        appendLine(o.body);
        appendLine("endobj");
    }

    const long long xrefOffset = static_cast<long long>(pdf.size());
    appendLine("xref");
    append("0 ");
    appendLine(std::to_string(maxObjNum + 1));

    // Object 0: free
    appendLine("0000000000 65535 f ");

    // For objects 1..maxObjNum, fill either real entries (n) or free entries (f)
    for (int i = 1; i <= maxObjNum; ++i) {
        if (offsets[i] >= 0) {
            // 10-digit, zero-padded offset; 5-digit gen; in-use
            char buf[32];
            std::snprintf(buf, sizeof(buf), "%010lld %05d n \n", offsets[i], 0);
            // NOTE: xref gen is usually 0 for in-use objects; for our tests, we keep it 0.
            // The Page Ref's generation is determined by the "N G obj" header / reference.
            append(buf);
        } else {
            appendLine("0000000000 00000 f ");
        }
    }

    appendLine("trailer");
    append("<< /Size ");
    append(std::to_string(maxObjNum + 1));
    append(" /Root ");
    append(std::to_string(rootObjNum));
    append(" ");
    append(std::to_string(rootObjGen));
    appendLine(" R >>");

    appendLine("startxref");
    appendLine(std::to_string(xrefOffset));
    appendLine("%%EOF");

    return pdf;
}

// A minimal 1-page PDF where:
// 1 0 = Catalog
// 2 0 = Pages
// 3 G = Page (generation controlled)
// 4 0 = Contents stream
static std::string MakeOnePagePdfWithPageRef(int pageObjNum, int pageObjGen)
{
    // We keep object numbers consistent and simple; ensure pageObjNum == 3 for the default layout,
    // but the function allows other numbers (with matching references).
    const int catalogNum = 1, catalogGen = 0;
    const int pagesNum = 2, pagesGen = 0;
    const int contentsNum = 4, contentsGen = 0;

    const int pageNum = pageObjNum;
    const int pageGen = pageObjGen;

    // If caller chooses a pageObjNum other than 3, still reference it correctly.
    const std::string pageRef = std::to_string(pageNum) + " " + std::to_string(pageGen) + " R";

    std::vector<PdfObjectSpec> objs;

    // Catalog
    objs.push_back(PdfObjectSpec{
        catalogNum,
        catalogGen,
        "<< /Type /Catalog /Pages 2 0 R >>",
    });

    // Pages
    objs.push_back(PdfObjectSpec{
        pagesNum,
        pagesGen,
        std::string("<< /Type /Pages /Count 1 /Kids [ ") + pageRef + " ] >>",
    });

    // Page
    objs.push_back(PdfObjectSpec{
        pageNum,
        pageGen,
        std::string("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>"),
    });

    // Contents stream (empty)
    objs.push_back(PdfObjectSpec{
        contentsNum,
        contentsGen,
        "<<" "\n"
        "  /Length 0\n"
        ">>\n"
        "stream\n"
        "endstream",
    });

    return BuildPdfWithObjectsAndXref(objs, catalogNum, catalogGen);
}

// A minimal 2-page PDF with known page refs (page1Num/page1Gen) and (page2Num/page2Gen).
static std::string MakeTwoPagePdfWithPageRefs(int page1Num, int page1Gen, int page2Num, int page2Gen)
{
    const int catalogNum = 1, catalogGen = 0;
    const int pagesNum = 2, pagesGen = 0;
    const int contents1Num = 5, contents1Gen = 0;
    const int contents2Num = 6, contents2Gen = 0;

    const std::string page1Ref = std::to_string(page1Num) + " " + std::to_string(page1Gen) + " R";
    const std::string page2Ref = std::to_string(page2Num) + " " + std::to_string(page2Gen) + " R";

    std::vector<PdfObjectSpec> objs;

    objs.push_back(PdfObjectSpec{catalogNum, catalogGen, "<< /Type /Catalog /Pages 2 0 R >>"});

    objs.push_back(PdfObjectSpec{
        pagesNum,
        pagesGen,
        std::string("<< /Type /Pages /Count 2 /Kids [ ") + page1Ref + " " + page2Ref + " ] >>",
    });

    objs.push_back(PdfObjectSpec{
        page1Num,
        page1Gen,
        std::string("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents ") +
            std::to_string(contents1Num) + " " + std::to_string(contents1Gen) + " R >>",
    });

    objs.push_back(PdfObjectSpec{
        page2Num,
        page2Gen,
        std::string("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 300 300] /Contents ") +
            std::to_string(contents2Num) + " " + std::to_string(contents2Gen) + " R >>",
    });

    objs.push_back(PdfObjectSpec{
        contents1Num,
        contents1Gen,
        "<<" "\n"
        "  /Length 0\n"
        ">>\n"
        "stream\n"
        "endstream",
    });

    objs.push_back(PdfObjectSpec{
        contents2Num,
        contents2Gen,
        "<<" "\n"
        "  /Length 0\n"
        ">>\n"
        "stream\n"
        "endstream",
    });

    return BuildPdfWithObjectsAndXref(objs, catalogNum, catalogGen);
}

static std::unique_ptr<PDFDoc> OpenPdfFromString(const std::string &pdfBytes)
{
    // MemStream takes ownership of buffer in some versions; in others it does not.
    // We allocate a copy and let the stream/doc manage it for the duration of the test.
    auto *buf = static_cast<char *>(gmalloc(pdfBytes.size()));
    std::memcpy(buf, pdfBytes.data(), pdfBytes.size());

    // Common Poppler ctor: MemStream(char *buf, Guint start, Guint length, Object &&dict)
    // Some versions use different signatures. Adjust if needed for your tree.
    Object dictObj;
    dictObj.setNull();

    auto *stream = new MemStream(buf, 0, static_cast<Guint>(pdfBytes.size()), std::move(dictObj));
    auto doc = std::make_unique<PDFDoc>(stream);

    return doc;
}

static bool RefEquals(const Ref &a, const Ref &b)
{
    return a.num == b.num && a.gen == b.gen;
}

} // namespace

// -----------------------
// Tests
// -----------------------

class PageGetRefTest_721 : public ::testing::Test {
protected:
    GlobalParamsGuard gp_;
};

TEST_F(PageGetRefTest_721, ReturnsExpectedRefForKnownSinglePagePdf_721)
{
    // Page object is "3 0 obj" and referenced as "3 0 R".
    const std::string pdf = MakeOnePagePdfWithPageRef(/*pageObjNum=*/3, /*pageObjGen=*/0);
    auto doc = OpenPdfFromString(pdf);
    ASSERT_TRUE(doc);
    ASSERT_TRUE(doc->isOk());

    Page *page1 = doc->getCatalog()->getPage(1);
    ASSERT_NE(page1, nullptr);

    const Ref r = page1->getRef();
    EXPECT_EQ(r.num, 3);
    EXPECT_EQ(r.gen, 0);
}

TEST_F(PageGetRefTest_721, GetRefIsStableAcrossMultipleCalls_721)
{
    const std::string pdf = MakeOnePagePdfWithPageRef(/*pageObjNum=*/3, /*pageObjGen=*/0);
    auto doc = OpenPdfFromString(pdf);
    ASSERT_TRUE(doc);
    ASSERT_TRUE(doc->isOk());

    Page *page1 = doc->getCatalog()->getPage(1);
    ASSERT_NE(page1, nullptr);

    const Ref r1 = page1->getRef();
    const Ref r2 = page1->getRef();
    EXPECT_TRUE(RefEquals(r1, r2));
}

TEST_F(PageGetRefTest_721, DifferentPagesHaveDifferentRefs_721)
{
    // Page1: 3 0 R, Page2: 4 0 R
    const std::string pdf = MakeTwoPagePdfWithPageRefs(/*page1Num=*/3, /*page1Gen=*/0, /*page2Num=*/4, /*page2Gen=*/0);
    auto doc = OpenPdfFromString(pdf);
    ASSERT_TRUE(doc);
    ASSERT_TRUE(doc->isOk());

    Page *p1 = doc->getCatalog()->getPage(1);
    Page *p2 = doc->getCatalog()->getPage(2);
    ASSERT_NE(p1, nullptr);
    ASSERT_NE(p2, nullptr);

    const Ref r1 = p1->getRef();
    const Ref r2 = p2->getRef();

    EXPECT_FALSE(RefEquals(r1, r2));
    EXPECT_EQ(r1.num, 3);
    EXPECT_EQ(r2.num, 4);
}

TEST_F(PageGetRefTest_721, PreservesNonZeroGenerationNumber_721)
{
    // Boundary-ish: generation number is non-zero. We expect getRef() to return that generation.
    // Page object is "3 7 obj" and referenced as "3 7 R".
    const std::string pdf = MakeOnePagePdfWithPageRef(/*pageObjNum=*/3, /*pageObjGen=*/7);
    auto doc = OpenPdfFromString(pdf);
    ASSERT_TRUE(doc);
    ASSERT_TRUE(doc->isOk());

    Page *page1 = doc->getCatalog()->getPage(1);
    ASSERT_NE(page1, nullptr);

    const Ref r = page1->getRef();
    EXPECT_EQ(r.num, 3);
    EXPECT_EQ(r.gen, 7);
}

TEST_F(PageGetRefTest_721, InvalidPdfLeadsToDocNotOk_721)
{
    // Exceptional case: malformed PDF input. Observable behavior: PDFDoc::isOk() becomes false.
    // We do not call Page::getRef() here because no valid Page is expected.
    const std::string badPdf = "%PDF-1.4\n1 0 obj\n<<>>\nendobj\n%%EOF\n";
    auto doc = OpenPdfFromString(badPdf);
    ASSERT_TRUE(doc);
    EXPECT_FALSE(doc->isOk());
}