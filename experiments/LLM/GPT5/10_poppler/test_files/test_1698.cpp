// StructElement_getStructTreeRoot_1698_test.cc
#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#if __has_include(<filesystem>)
#  include <filesystem>
namespace fs = std::filesystem;
#endif

#include "PDFDoc.h"
#include "GooString.h"
#include "StructTreeRoot.h"
#include "StructElement.h"

namespace {

// Write a minimal PDF with a deterministic xref table.
// This is test data generation (not re-implementing Poppler logic).
bool writePdfWithObjects(const std::string &path, const std::vector<std::string> &objects)
{
    std::ofstream out(path, std::ios::binary);
    if (!out.is_open()) {
        return false;
    }

    out << "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

    std::vector<long> offsets;
    offsets.reserve(objects.size() + 1);
    offsets.push_back(0); // object 0 is free

    for (size_t i = 0; i < objects.size(); ++i) {
        offsets.push_back(static_cast<long>(out.tellp()));
        out << (i + 1) << " 0 obj\n" << objects[i] << "\nendobj\n";
    }

    const long xrefPos = static_cast<long>(out.tellp());
    out << "xref\n";
    out << "0 " << (objects.size() + 1) << "\n";
    out << "0000000000 65535 f \n";
    for (size_t i = 1; i < offsets.size(); ++i) {
        char buf[32];
        std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
        out << buf;
    }

    out << "trailer\n";
    out << "<< /Size " << (objects.size() + 1) << " /Root 1 0 R >>\n";
    out << "startxref\n";
    out << xrefPos << "\n";
    out << "%%EOF\n";

    out.flush();
    return out.good();
}

std::string makeTempPath(const std::string &fileName)
{
#if defined(__cpp_lib_filesystem)
    const fs::path p = fs::temp_directory_path() / fs::path(fileName);
    return p.string();
#else
    // Fallback: current directory.
    return fileName;
#endif
}

// Create PDFDoc in a way that compiles across Poppler versions that differ
// in constructor signatures.
std::unique_ptr<PDFDoc> createDocForPath(const std::string &path)
{
    // Newer Poppler: PDFDoc(std::unique_ptr<GooString>&&, optional<GooString>, optional<GooString>, ...)
    if constexpr (std::is_constructible_v<PDFDoc, std::unique_ptr<GooString> &&>) {
        auto fn = std::make_unique<GooString>(path.c_str());
        return std::make_unique<PDFDoc>(std::move(fn));
    } else if constexpr (std::is_constructible_v<PDFDoc, GooString *>) {
        // Older Poppler: PDFDoc(GooString* fileNameA, GooString* ownerPassword, GooString* userPassword, ...)
        auto *fn = new GooString(path.c_str());
        // PDFDoc takes ownership of fileNameA in older versions.
        return std::make_unique<PDFDoc>(fn);
    } else {
        return nullptr;
    }
}

} // namespace

class StructElementGetStructTreeRootTest_1698 : public ::testing::Test {
protected:
    std::string taggedPath = makeTempPath("poppler_structelement_tagged_1698.pdf");
    std::string untaggedPath = makeTempPath("poppler_structelement_untagged_1698.pdf");

    void SetUp() override
    {
        // Tagged-ish PDF: includes a StructTreeRoot with one StructElem child.
        // 1: Catalog
        // 2: Pages (empty tree, Count 0)
        // 3: StructTreeRoot
        // 4: StructElem (Document), /K [] (no children)
        ASSERT_TRUE(writePdfWithObjects(taggedPath, {
            "<< /Type /Catalog /Pages 2 0 R /StructTreeRoot 3 0 R /MarkInfo << /Marked true >> >>",
            "<< /Type /Pages /Count 0 >>",
            "<< /Type /StructTreeRoot /K [4 0 R] >>",
            "<< /Type /StructElem /S /Document /P 3 0 R /K [] >>",
        }));

        // Untagged PDF: no /StructTreeRoot entry.
        ASSERT_TRUE(writePdfWithObjects(untaggedPath, {
            "<< /Type /Catalog /Pages 2 0 R >>",
            "<< /Type /Pages /Count 0 >>",
        }));
    }
};

TEST_F(StructElementGetStructTreeRootTest_1698, ReturnsOwningRootPointerForChildElement_1698)
{
    auto doc = createDocForPath(taggedPath);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    const StructTreeRoot *rootConst = doc->getStructTreeRoot();
    ASSERT_NE(rootConst, nullptr);

    ASSERT_GE(rootConst->getNumChildren(), 1u);
    const StructElement *childConst = rootConst->getChild(0);
    ASSERT_NE(childConst, nullptr);

    // getStructTreeRoot() returns non-const pointer; compare addresses safely.
    StructElement *child = const_cast<StructElement *>(childConst);
    StructTreeRoot *rootFromElem = child->getStructTreeRoot();

    ASSERT_NE(rootFromElem, nullptr);
    EXPECT_EQ(rootFromElem, const_cast<StructTreeRoot *>(rootConst));
}

TEST_F(StructElementGetStructTreeRootTest_1698, WorksWhenElementHasNoChildren_Boundary_1698)
{
    auto doc = createDocForPath(taggedPath);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    const StructTreeRoot *rootConst = doc->getStructTreeRoot();
    ASSERT_NE(rootConst, nullptr);
    ASSERT_GE(rootConst->getNumChildren(), 1u);

    const StructElement *childConst = rootConst->getChild(0);
    ASSERT_NE(childConst, nullptr);

    // Boundary: the element in our test PDF is created with /K [].
    // We only assert what is observable via public API.
    EXPECT_EQ(childConst->getNumChildren(), 0u);

    StructElement *child = const_cast<StructElement *>(childConst);
    EXPECT_EQ(child->getStructTreeRoot(), const_cast<StructTreeRoot *>(rootConst));
}

TEST_F(StructElementGetStructTreeRootTest_1698, UntaggedPdfHasNoStructTreeRoot_ErrorObservable_1698)
{
    auto doc = createDocForPath(untaggedPath);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    // Observable "error" / absence case: no structure tree available.
    const StructTreeRoot *rootConst = doc->getStructTreeRoot();
    EXPECT_EQ(rootConst, nullptr);
}