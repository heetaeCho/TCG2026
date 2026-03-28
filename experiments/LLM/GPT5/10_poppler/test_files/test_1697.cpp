// StructElement_hasStmRef_1697_test.cc
#include <gtest/gtest.h>

#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "PDFDoc.h"
#include "Catalog.h"
#include "StructTreeRoot.h"
#include "StructElement.h"
#include "goo/GooString.h"

namespace {

static std::string Pad10(long long v)
{
    std::ostringstream oss;
    oss.width(10);
    oss.fill('0');
    oss << v;
    return oss.str();
}

static std::string MakeStreamObject(const std::string &streamContent, const std::string &extraDict = "")
{
    std::ostringstream oss;
    oss << "<< /Length " << streamContent.size();
    if (!extraDict.empty()) {
        oss << " " << extraDict;
    }
    oss << " >>\n"
        << "stream\n"
        << streamContent
        << "\nendstream";
    return oss.str();
}

static std::string BuildPdfWithObjects(const std::vector<std::string> &objects)
{
    // objects are 1..N, trailer Root is 1 0 R
    std::string pdf = "%PDF-1.7\n";
    std::vector<long long> offsets(objects.size() + 1, 0);

    for (size_t i = 0; i < objects.size(); ++i) {
        const int objNum = static_cast<int>(i) + 1;
        offsets[objNum] = static_cast<long long>(pdf.size());
        pdf += std::to_string(objNum) + " 0 obj\n";
        pdf += objects[i];
        pdf += "\nendobj\n";
    }

    const long long xrefOff = static_cast<long long>(pdf.size());
    pdf += "xref\n0 " + std::to_string(objects.size() + 1) + "\n";
    pdf += "0000000000 65535 f \n";
    for (size_t i = 1; i <= objects.size(); ++i) {
        pdf += Pad10(offsets[i]) + " 00000 n \n";
    }
    pdf += "trailer\n<< /Size " + std::to_string(objects.size() + 1) + " /Root 1 0 R >>\n";
    pdf += "startxref\n" + std::to_string(xrefOff) + "\n%%EOF\n";
    return pdf;
}

static std::string WriteTempPdf(const std::string &pdfBytes, const std::string &basename)
{
    const std::string dir = testing::TempDir();
    const std::string path = dir + "/" + basename;

    std::ofstream out(path, std::ios::binary);
    out.write(pdfBytes.data(), static_cast<std::streamsize>(pdfBytes.size()));
    out.close();

    return path;
}

static std::unique_ptr<PDFDoc> LoadPdf(const std::string &path)
{
    GooString fileName(path.c_str());
    auto doc = std::make_unique<PDFDoc>(&fileName);
    return doc;
}

static StructTreeRoot *GetStructTreeRootOrNull(PDFDoc *doc)
{
    if (!doc) {
        return nullptr;
    }
    Catalog *cat = doc->getCatalog();
    if (!cat) {
        return nullptr;
    }
    return cat->getStructTreeRoot();
}

static const StructElement *GetFirstContentChildOrNull(const StructTreeRoot *root)
{
    if (!root || root->getNumChildren() == 0) {
        return nullptr;
    }
    const StructElement *top = root->getChild(0);
    if (!top || top->getNumChildren() == 0) {
        return nullptr;
    }
    return top->getChild(0);
}

static std::string BuildTaggedPdfWithMcr(bool includeStm)
{
    // Object numbers:
    // 1: Catalog
    // 2: Pages
    // 3: Page
    // 4: Contents stream (also referenced by /Stm when includeStm=true)
    // 5: StructTreeRoot
    // 6: StructElem
    // 7: MCR dict (with /Stm optionally)
    //
    // Minimal marked-content sequence in the stream with MCID 0.
    const std::string streamContent = "/P <</MCID 0>> BDC\nEMC\n";

    std::vector<std::string> objs;

    objs.push_back("<< /Type /Catalog /Pages 2 0 R /StructTreeRoot 5 0 R /MarkInfo << /Marked true >> >>");
    objs.push_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
    objs.push_back("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R /Resources << >> >>");
    objs.push_back(MakeStreamObject(streamContent));
    objs.push_back("<< /Type /StructTreeRoot /K [6 0 R] >>");
    objs.push_back("<< /Type /StructElem /S /P /P 5 0 R /K 7 0 R >>");

    std::ostringstream mcr;
    mcr << "<< /Type /MCR /Pg 3 0 R /MCID 0";
    if (includeStm) {
        mcr << " /Stm 4 0 R";
    }
    mcr << " >>";
    objs.push_back(mcr.str());

    return BuildPdfWithObjects(objs);
}

class StructElementHasStmRefTest_1697 : public ::testing::Test {
protected:
    static const StructElement *FindFirstContent(const std::unique_ptr<PDFDoc> &doc)
    {
        StructTreeRoot *root = GetStructTreeRootOrNull(doc.get());
        return GetFirstContentChildOrNull(root);
    }
};

TEST_F(StructElementHasStmRefTest_1697, ContentWithStmRef_ReturnsTrue_1697)
{
    const std::string pdf = BuildTaggedPdfWithMcr(true);
    const std::string path = WriteTempPdf(pdf, "structelement_hasstmref_true_1697.pdf");

    auto doc = LoadPdf(path);
    ASSERT_TRUE(doc);
    ASSERT_TRUE(doc->isOk());

    StructTreeRoot *root = GetStructTreeRootOrNull(doc.get());
    ASSERT_NE(root, nullptr);
    ASSERT_GT(root->getNumChildren(), 0u);

    const StructElement *content = GetFirstContentChildOrNull(root);
    ASSERT_NE(content, nullptr);
    ASSERT_TRUE(content->isContent());

    EXPECT_TRUE(content->hasStmRef());

    Ref stmRef{};
    const bool got = content->getStmRef(stmRef);
    EXPECT_TRUE(got);
    if (got) {
        EXPECT_EQ(stmRef.num, 4);
        EXPECT_EQ(stmRef.gen, 0);
    }
}

TEST_F(StructElementHasStmRefTest_1697, ContentWithoutStmRef_ReturnsFalse_1697)
{
    const std::string pdf = BuildTaggedPdfWithMcr(false);
    const std::string path = WriteTempPdf(pdf, "structelement_hasstmref_false_1697.pdf");

    auto doc = LoadPdf(path);
    ASSERT_TRUE(doc);
    ASSERT_TRUE(doc->isOk());

    StructTreeRoot *root = GetStructTreeRootOrNull(doc.get());
    ASSERT_NE(root, nullptr);

    const StructElement *content = GetFirstContentChildOrNull(root);
    ASSERT_NE(content, nullptr);
    ASSERT_TRUE(content->isContent());

    EXPECT_FALSE(content->hasStmRef());

    Ref stmRef{};
    const bool got = content->getStmRef(stmRef);
    EXPECT_FALSE(got);
}

TEST_F(StructElementHasStmRefTest_1697, NonContentElement_HasStmRefConsistentWithGetStmRef_1697)
{
    const std::string pdf = BuildTaggedPdfWithMcr(true);
    const std::string path = WriteTempPdf(pdf, "structelement_noncontent_consistency_1697.pdf");

    auto doc = LoadPdf(path);
    ASSERT_TRUE(doc);
    ASSERT_TRUE(doc->isOk());

    StructTreeRoot *root = GetStructTreeRootOrNull(doc.get());
    ASSERT_NE(root, nullptr);
    ASSERT_GT(root->getNumChildren(), 0u);

    // Top-level StructElem is not a content element (in this PDF).
    const StructElement *top = root->getChild(0);
    ASSERT_NE(top, nullptr);

    Ref stmRef{};
    const bool got = top->getStmRef(stmRef);
    EXPECT_EQ(top->hasStmRef(), got);
}

TEST_F(StructElementHasStmRefTest_1697, Boundary_InvalidChildIndexThrows_1697)
{
    const std::string pdf = BuildTaggedPdfWithMcr(true);
    const std::string path = WriteTempPdf(pdf, "structelement_boundary_child_1697.pdf");

    auto doc = LoadPdf(path);
    ASSERT_TRUE(doc);
    ASSERT_TRUE(doc->isOk());

    StructTreeRoot *root = GetStructTreeRootOrNull(doc.get());
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(root->getNumChildren(), 1u);

    // getChild uses bounds-checked access in common Poppler implementations (vector::at).
    EXPECT_ANY_THROW((void)root->getChild(1));

    const StructElement *top = root->getChild(0);
    ASSERT_NE(top, nullptr);
    ASSERT_EQ(top->getNumChildren(), 1u);

    EXPECT_ANY_THROW((void)top->getChild(1));
    EXPECT_ANY_THROW((void)top->getChild(-1));
}

} // namespace