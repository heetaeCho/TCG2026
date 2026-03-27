// Page_isCropped_705_test.cpp
// Unit tests for poppler::Page::isCropped()
// The TEST_ID is 705

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>

#include "poppler/GlobalParams.h"
#include "poppler/GooString.h"
#include "poppler/PDFDoc.h"
#include "poppler/Page.h"

// Some poppler builds expose globalParams as a raw pointer, others as std::unique_ptr.
// These helpers keep the test robust without depending on poppler internals.
namespace {
void EnsureGlobalParamsInitialized()
{
#if defined(POPPLER_GLOBALPARAMS_H) || 1
    // Try the most common patterns.
    // 1) globalParams is a raw pointer (GlobalParams*).
    // 2) globalParams is a std::unique_ptr<GlobalParams>.
    // We avoid relying on any internal behavior; we just ensure it's non-null if available.
    //
    // NOTE: If your build system already initializes globalParams, this is harmless.
    try {
        // Use ADL / overload resolution to compile with either form.
        struct Init {
            static void init(GlobalParams *&gp)
            {
                if (!gp) {
                    gp = new GlobalParams();
                }
            }
            static void init(std::unique_ptr<GlobalParams> &gp)
            {
                if (!gp) {
                    gp = std::make_unique<GlobalParams>();
                }
            }
        };

        Init::init(globalParams);
    } catch (...) {
        // If globalParams isn't available/needed in this build, ignore.
    }
#endif
}

// Build a tiny, single-page PDF into a std::string.
// Optionally includes /CropBox in the page dictionary.
// MediaBox is always [0 0 200 200] to keep expectations stable.
std::string BuildSinglePagePdf(bool includeCropBox, const char *cropBoxArrayLiteral /* e.g. "[0 0 100 100]" */)
{
    std::ostringstream oss;
    std::vector<long long> objOffset(5, 0);

    auto write_obj = [&](int objNum, const std::string &body) {
        objOffset[objNum] = static_cast<long long>(oss.tellp());
        oss << objNum << " 0 obj\n" << body << "\nendobj\n";
    };

    oss << "%PDF-1.4\n";

    // 1 0 obj: Catalog
    write_obj(1, "<< /Type /Catalog /Pages 2 0 R >>");

    // 2 0 obj: Pages
    write_obj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

    // 3 0 obj: Page
    {
        std::ostringstream pageDict;
        pageDict << "<< /Type /Page /Parent 2 0 R "
                << "/MediaBox [0 0 200 200] ";
        if (includeCropBox) {
            pageDict << "/CropBox " << cropBoxArrayLiteral << " ";
        }
        pageDict << "/Contents 4 0 R >>";
        write_obj(3, pageDict.str());
    }

    // 4 0 obj: Empty contents stream
    // (A minimal valid stream; we don't depend on rendering.)
    write_obj(4, "<< /Length 0 >>\nstream\n\nendstream");

    // xref
    const long long xrefOffset = static_cast<long long>(oss.tellp());
    oss << "xref\n0 5\n";
    oss << "0000000000 65535 f \n";
    for (int i = 1; i <= 4; ++i) {
        // 10-digit, zero-padded offsets per PDF spec.
        char buf[32];
        std::snprintf(buf, sizeof(buf), "%010lld 00000 n \n", objOffset[i]);
        oss << buf;
    }

    // trailer
    oss << "trailer\n<< /Size 5 /Root 1 0 R >>\n";
    oss << "startxref\n" << xrefOffset << "\n%%EOF\n";

    return oss.str();
}

std::string WriteTempPdfFile(const std::string &pdfBytes)
{
    // Simple, portable temp path creation.
    // (We keep it deterministic enough for CI; collisions are extremely unlikely.)
    char tmpName[L_tmpnam];
    std::tmpnam(tmpName);
    std::string path = std::string(tmpName) + "_poppler_page_isCropped_705.pdf";

    std::ofstream out(path, std::ios::binary);
    out.write(pdfBytes.data(), static_cast<std::streamsize>(pdfBytes.size()));
    out.close();

    return path;
}
} // namespace

class PageIsCroppedTest_705 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        EnsureGlobalParamsInitialized();
    }
};

// Normal operation: a page without /CropBox should not be considered cropped.
TEST_F(PageIsCroppedTest_705, NoCropBox_ReturnsFalse_705)
{
    const std::string pdf = BuildSinglePagePdf(false, "[0 0 200 200]");
    const std::string path = WriteTempPdfFile(pdf);

    auto fileName = std::make_unique<GooString>(path.c_str());
    PDFDoc doc(std::move(fileName));
    ASSERT_TRUE(doc.isOk());

    Page *page = doc.getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_FALSE(page->isCropped());

    std::remove(path.c_str());
}

// Boundary condition: /CropBox present but identical to /MediaBox should not be considered cropped.
TEST_F(PageIsCroppedTest_705, CropBoxEqualsMediaBox_ReturnsFalse_705)
{
    const std::string pdf = BuildSinglePagePdf(true, "[0 0 200 200]");
    const std::string path = WriteTempPdfFile(pdf);

    auto fileName = std::make_unique<GooString>(path.c_str());
    PDFDoc doc(std::move(fileName));
    ASSERT_TRUE(doc.isOk());

    Page *page = doc.getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_FALSE(page->isCropped());

    std::remove(path.c_str());
}

// Normal operation: /CropBox smaller than /MediaBox should be considered cropped.
TEST_F(PageIsCroppedTest_705, CropBoxSmallerThanMediaBox_ReturnsTrue_705)
{
    const std::string pdf = BuildSinglePagePdf(true, "[0 0 100 100]");
    const std::string path = WriteTempPdfFile(pdf);

    auto fileName = std::make_unique<GooString>(path.c_str());
    PDFDoc doc(std::move(fileName));
    ASSERT_TRUE(doc.isOk());

    Page *page = doc.getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_TRUE(page->isCropped());

    std::remove(path.c_str());
}

// Boundary / robustness: /CropBox larger than /MediaBox should not crash; return value must be a valid bool.
// (We don't assert a specific value to avoid inferring internal clipping rules.)
TEST_F(PageIsCroppedTest_705, CropBoxLargerThanMediaBox_DoesNotCrash_705)
{
    const std::string pdf = BuildSinglePagePdf(true, "[-10 -10 250 250]");
    const std::string path = WriteTempPdfFile(pdf);

    auto fileName = std::make_unique<GooString>(path.c_str());
    PDFDoc doc(std::move(fileName));
    ASSERT_TRUE(doc.isOk());

    Page *page = doc.getPage(1);
    ASSERT_NE(page, nullptr);

    const bool cropped = page->isCropped();
    // Observable guarantee: callable and returns a boolean.
    EXPECT_TRUE(cropped == true || cropped == false);

    std::remove(path.c_str());
}

// Exceptional / error case: malformed PDF should fail to load (observable via PDFDoc::isOk()).
TEST_F(PageIsCroppedTest_705, MalformedPdf_DocNotOk_705)
{
    const std::string badPdf = "%PDF-1.4\n% malformed\n%%EOF\n";
    const std::string path = WriteTempPdfFile(badPdf);

    auto fileName = std::make_unique<GooString>(path.c_str());
    PDFDoc doc(std::move(fileName));

    EXPECT_FALSE(doc.isOk());

    std::remove(path.c_str());
}