// extractPages_test_2736.cc
//
// Unit tests for extractPages() in utils/pdfseparate.cc
// NOTE: extractPages is a static function in the .cc, so we include the .cc directly
// (common technique for testing internal-static helpers in CLI utilities).

#include <gtest/gtest.h>

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

// pdfseparate.cc uses these globals (declared elsewhere in the utils tree).
// Provide definitions here for the test translation unit.
int firstPage = 1;
int lastPage = 0;

// Avoid colliding with gtest main if pdfseparate.cc defines a program main().
#define main pdfseparate_main_2736
#include "TestProjects/poppler/utils/pdfseparate.cc"
#undef main

// ---------------------------
// Test helper: minimal PDF writer
// ---------------------------
//
// This creates a simple, valid PDF with N pages, each with an empty content stream.
// It is intentionally tiny but structured enough for Poppler's PDFDoc to open and
// for savePageAs() to work (as used by extractPages()).
//
// This helper is only test-data generation, not re-implementing extractPages logic.
static void WriteMinimalPdf(const fs::path &path, int numPages)
{
    ASSERT_GE(numPages, 1);

    struct Obj {
        int id;
        std::string body; // without "id 0 obj" and "endobj"
    };

    // Object IDs:
    // 1: Catalog
    // 2: Pages
    // 3..(3+numPages-1): Page objects
    // next: content streams (one per page)
    // last: font object (optional but harmless)
    const int catalogId = 1;
    const int pagesId = 2;
    const int firstPageId = 3;
    const int firstContentId = firstPageId + numPages;
    const int fontId = firstContentId + numPages;

    std::vector<Obj> objs;
    objs.reserve(2 + 2 * numPages + 1);

    // Font object (standard built-in Helvetica).
    objs.push_back(Obj{
        fontId,
        "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>"
    });

    // Content streams (empty but valid).
    for (int i = 0; i < numPages; ++i) {
        const int contentId = firstContentId + i;
        // Empty stream: length 0.
        objs.push_back(Obj{
            contentId,
            "<< /Length 0 >>\nstream\n\nendstream"
        });
    }

    // Page objects
    for (int i = 0; i < numPages; ++i) {
        const int pageId = firstPageId + i;
        const int contentId = firstContentId + i;
        std::ostringstream page;
        page
            << "<< /Type /Page\n"
            << "   /Parent " << pagesId << " 0 R\n"
            << "   /MediaBox [0 0 200 200]\n"
            << "   /Resources << /Font << /F1 " << fontId << " 0 R >> >>\n"
            << "   /Contents " << contentId << " 0 R\n"
            << ">>";
        objs.push_back(Obj{pageId, page.str()});
    }

    // Pages object: Kids array
    {
        std::ostringstream kids;
        kids << "[ ";
        for (int i = 0; i < numPages; ++i) {
            kids << (firstPageId + i) << " 0 R ";
        }
        kids << "]";
        std::ostringstream pages;
        pages
            << "<< /Type /Pages\n"
            << "   /Count " << numPages << "\n"
            << "   /Kids " << kids.str() << "\n"
            << ">>";
        objs.push_back(Obj{pagesId, pages.str()});
    }

    // Catalog object
    objs.push_back(Obj{
        catalogId,
        "<< /Type /Catalog /Pages 2 0 R >>"
    });

    // Sort objects by id to build xref consistently.
    std::sort(objs.begin(), objs.end(), [](const Obj &a, const Obj &b) { return a.id < b.id; });

    std::ostringstream out;
    out << "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

    // Track offsets (byte positions from start).
    // xref requires 0..maxObj; include obj 0 entry.
    int maxObj = 0;
    for (const auto &o : objs) maxObj = std::max(maxObj, o.id);

    std::vector<long long> offsets(maxObj + 1, 0);
    offsets[0] = 0;

    auto tell = [&out]() -> long long {
        const std::string s = out.str();
        return static_cast<long long>(s.size());
    };

    for (const auto &o : objs) {
        offsets[o.id] = tell();
        out << o.id << " 0 obj\n" << o.body << "\nendobj\n";
    }

    const long long xrefPos = tell();
    out << "xref\n";
    out << "0 " << (maxObj + 1) << "\n";
    out << "0000000000 65535 f \n";
    for (int i = 1; i <= maxObj; ++i) {
        // Some ids may be unused; mark them free if offset is 0.
        if (offsets[i] == 0) {
            out << "0000000000 65535 f \n";
        } else {
            char buf[64];
            std::snprintf(buf, sizeof(buf), "%010lld 00000 n \n", offsets[i]);
            out << buf;
        }
    }

    out << "trailer\n";
    out << "<< /Size " << (maxObj + 1) << " /Root " << catalogId << " 0 R >>\n";
    out << "startxref\n" << xrefPos << "\n%%EOF\n";

    std::ofstream f(path, std::ios::binary);
    ASSERT_TRUE(f.is_open());
    const std::string pdf = out.str();
    f.write(pdf.data(), static_cast<std::streamsize>(pdf.size()));
    ASSERT_TRUE(f.good());
}

static fs::path MakeTempDir_2736()
{
    fs::path base = fs::temp_directory_path();
    fs::path dir = base / ("extractPages_test_2736_" + std::to_string(::getpid()) + "_" + std::to_string(std::rand()));
    fs::create_directories(dir);
    return dir;
}

static std::string PathStr(const fs::path &p)
{
#ifdef _WIN32
    return p.u8string();
#else
    return p.string();
#endif
}

// ---------------------------
// Tests
// ---------------------------

class ExtractPagesTest_2736 : public ::testing::Test {
protected:
    void SetUp() override
    {
        tmpDir = MakeTempDir_2736();
        // Reset globals to a safe baseline for each test.
        firstPage = 1;
        lastPage = 0;
    }

    void TearDown() override
    {
        std::error_code ec;
        fs::remove_all(tmpDir, ec);
    }

    fs::path tmpDir;
};

TEST_F(ExtractPagesTest_2736, ReturnsFalseForDamagedOrMissingInput_2736)
{
    const fs::path missing = tmpDir / "does_not_exist.pdf";
    const fs::path out = tmpDir / "out-%d.pdf";

    // Any missing/invalid source should lead to PDFDoc::isOk() == false and extractPages returning false.
    EXPECT_FALSE(extractPages(PathStr(missing).c_str(), PathStr(out).c_str()));
}

TEST_F(ExtractPagesTest_2736, MultiPageRequiresPrintfPatternInDestination_2736)
{
    // Create a 2-page PDF.
    const fs::path src = tmpDir / "two_pages.pdf";
    WriteMinimalPdf(src, 2);

    // When firstPage==0 && lastPage==0, extractPages uses the doc page count.
    firstPage = 0;
    lastPage = 0;

    // Destination without %d should fail if more than one page is extracted.
    const fs::path destNoPattern = tmpDir / "page.pdf";
    EXPECT_FALSE(extractPages(PathStr(src).c_str(), PathStr(destNoPattern).c_str()));
}

TEST_F(ExtractPagesTest_2736, SinglePageAllowsDestinationWithoutPatternAndCreatesFile_2736)
{
    const fs::path src = tmpDir / "two_pages.pdf";
    WriteMinimalPdf(src, 2);

    // Extract exactly one page: should not require %d in dest.
    firstPage = 1;
    lastPage = 1;

    const fs::path dest = tmpDir / "only_one.pdf";
    ASSERT_TRUE(extractPages(PathStr(src).c_str(), PathStr(dest).c_str()));

    EXPECT_TRUE(fs::exists(dest));
    EXPECT_GT(fs::file_size(dest), 0u);
}

TEST_F(ExtractPagesTest_2736, RejectsWhenLastPageBeforeFirstPage_2736)
{
    const fs::path src = tmpDir / "two_pages.pdf";
    WriteMinimalPdf(src, 2);

    firstPage = 2;
    lastPage = 1;

    const fs::path dest = tmpDir / "out-%d.pdf";
    EXPECT_FALSE(extractPages(PathStr(src).c_str(), PathStr(dest).c_str()));
}

TEST_F(ExtractPagesTest_2736, RejectsDestinationWithMoreThanOnePrintfPattern_2736)
{
    const fs::path src = tmpDir / "two_pages.pdf";
    WriteMinimalPdf(src, 2);

    firstPage = 1;
    lastPage = 2;

    // Two %d patterns should be rejected before any page saving occurs.
    // (Important: this avoids calling snprintf with mismatched arguments.)
    const fs::path dest = tmpDir / "out-%d-%d.pdf";
    EXPECT_FALSE(extractPages(PathStr(src).c_str(), PathStr(dest).c_str()));
}

TEST_F(ExtractPagesTest_2736, ExtractsRangeWithZeroPaddedPatternAndCreatesAllFiles_2736)
{
    const fs::path src = tmpDir / "three_pages.pdf";
    WriteMinimalPdf(src, 3);

    firstPage = 1;
    lastPage = 3;

    const fs::path destPattern = tmpDir / "page-%03d.pdf";
    ASSERT_TRUE(extractPages(PathStr(src).c_str(), PathStr(destPattern).c_str()));

    EXPECT_TRUE(fs::exists(tmpDir / "page-001.pdf"));
    EXPECT_TRUE(fs::exists(tmpDir / "page-002.pdf"));
    EXPECT_TRUE(fs::exists(tmpDir / "page-003.pdf"));
}

TEST_F(ExtractPagesTest_2736, ReturnsFalseIfSavingFailsDueToUnwritableDirectory_2736)
{
    const fs::path src = tmpDir / "two_pages.pdf";
    WriteMinimalPdf(src, 2);

    firstPage = 1;
    lastPage = 1;

    // Create a directory and remove write permissions (POSIX). If chmod isn't supported,
    // we still try writing into a non-existent subdir to force an error.
    fs::path noWriteDir = tmpDir / "no_write_dir";
    fs::create_directories(noWriteDir);

#ifndef _WIN32
    // Remove all permissions to maximize chance savePageAs fails.
    std::error_code ec;
    fs::permissions(noWriteDir,
                    fs::perms::none,
                    fs::perm_options::replace,
                    ec);
#endif

    // Attempt to save into that directory.
    const fs::path dest = noWriteDir / "out.pdf";

    // Behavior under test: if PDFDoc::savePageAs() returns non-errNone, extractPages returns false.
    EXPECT_FALSE(extractPages(PathStr(src).c_str(), PathStr(dest).c_str()));
}