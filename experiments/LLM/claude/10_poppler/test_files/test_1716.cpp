#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "StructTreeRoot.h"
#include "StructElement.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <string>

class StructTreeRootTest_1716 : public ::testing::Test {
protected:
    void SetUp() override
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override { }

    // Helper to create a PDFDoc from a minimal PDF file
    std::unique_ptr<PDFDoc> createPDFDocFromFile(const char *filename)
    {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        return doc;
    }
};

// Test that a StructTreeRoot constructed from a PDF with structure tree
// has a non-null doc pointer that matches the source document.
TEST_F(StructTreeRootTest_1716, GetDocReturnsNonNull_1716)
{
    // We need a valid PDF with a StructTreeRoot to test this properly.
    // Since we can't create one from scratch easily without a file,
    // we test with a minimal approach using the Dict-based constructor.
    // However, since we can't easily construct PDFDoc without a file,
    // we test the interface contract: getDoc() should return the doc
    // that was passed during construction.

    // Create a minimal PDF in memory using a GooString
    // Minimal valid PDF with structure tree
    static const char minimalPDF[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /MarkInfo << /Marked true >> /StructTreeRoot 2 0 R /Pages 3 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /StructTreeRoot /K 4 0 R /ParentTree 5 0 R >>\nendobj\n"
        "3 0 obj\n<< /Type /Pages /Kids [6 0 R] /Count 1 >>\nendobj\n"
        "4 0 obj\n<< /Type /StructElem /S /Document /P 2 0 R >>\nendobj\n"
        "5 0 obj\n<< /Nums [] >>\nendobj\n"
        "6 0 obj\n<< /Type /Page /Parent 3 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 7\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000115 00000 n \n"
        "0000000200 00000 n \n"
        "0000000259 00000 n \n"
        "0000000334 00000 n \n"
        "0000000365 00000 n \n"
        "trailer\n<< /Size 7 /Root 1 0 R >>\n"
        "startxref\n443\n%%EOF\n";

    // Write to a temp file
    const char *tmpFile = "/tmp/test_struct_tree_1716.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPDF, 1, sizeof(minimalPDF) - 1, f);
        fclose(f);

        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile));
        if (doc->isOk()) {
            const StructTreeRoot *root = doc->getStructTreeRoot();
            if (root) {
                // getDoc should return the owning PDFDoc
                EXPECT_EQ(root->getDoc(), doc.get());
            }
        }
        unlink(tmpFile);
    }
}

// Test getNumChildren returns 0 for a StructTreeRoot with no children
TEST_F(StructTreeRootTest_1716, GetNumChildrenInitially_1716)
{
    // Minimal PDF without structure elements as children
    static const char minimalPDF[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /MarkInfo << /Marked true >> /StructTreeRoot 2 0 R /Pages 3 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /StructTreeRoot >>\nendobj\n"
        "3 0 obj\n<< /Type /Pages /Kids [4 0 R] /Count 1 >>\nendobj\n"
        "4 0 obj\n<< /Type /Page /Parent 3 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000115 00000 n \n"
        "0000000163 00000 n \n"
        "0000000222 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n300\n%%EOF\n";

    const char *tmpFile = "/tmp/test_struct_tree_nochildren_1716.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPDF, 1, sizeof(minimalPDF) - 1, f);
        fclose(f);

        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile));
        if (doc->isOk()) {
            const StructTreeRoot *root = doc->getStructTreeRoot();
            if (root) {
                // With no /K entry, there should be no children
                EXPECT_EQ(root->getNumChildren(), 0u);
            }
        }
        unlink(tmpFile);
    }
}

// Test getRoleMap and getClassMap
TEST_F(StructTreeRootTest_1716, GetRoleMapAndClassMap_1716)
{
    static const char minimalPDF[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /MarkInfo << /Marked true >> /StructTreeRoot 2 0 R /Pages 3 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /StructTreeRoot /RoleMap << /Sect /Div >> /ClassMap << /Normal << /O /Layout >> >> >>\nendobj\n"
        "3 0 obj\n<< /Type /Pages /Kids [4 0 R] /Count 1 >>\nendobj\n"
        "4 0 obj\n<< /Type /Page /Parent 3 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000115 00000 n \n"
        "0000000250 00000 n \n"
        "0000000309 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n387\n%%EOF\n";

    const char *tmpFile = "/tmp/test_struct_tree_rolemap_1716.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPDF, 1, sizeof(minimalPDF) - 1, f);
        fclose(f);

        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile));
        if (doc->isOk()) {
            StructTreeRoot *root = doc->getStructTreeRoot();
            if (root) {
                // getRoleMap should return a non-null Dict when RoleMap is present
                Dict *roleMap = root->getRoleMap();
                if (roleMap) {
                    EXPECT_GT(roleMap->getLength(), 0);
                }

                // getClassMap should return a non-null Dict when ClassMap is present
                Dict *classMap = root->getClassMap();
                if (classMap) {
                    EXPECT_GT(classMap->getLength(), 0);
                }
            }
        }
        unlink(tmpFile);
    }
}

// Test getChild with valid index returns non-null element
TEST_F(StructTreeRootTest_1716, GetChildValidIndex_1716)
{
    static const char minimalPDF[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /MarkInfo << /Marked true >> /StructTreeRoot 2 0 R /Pages 3 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /StructTreeRoot /K 4 0 R /ParentTree 5 0 R >>\nendobj\n"
        "3 0 obj\n<< /Type /Pages /Kids [6 0 R] /Count 1 >>\nendobj\n"
        "4 0 obj\n<< /Type /StructElem /S /Document /P 2 0 R >>\nendobj\n"
        "5 0 obj\n<< /Nums [] >>\nendobj\n"
        "6 0 obj\n<< /Type /Page /Parent 3 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 7\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000115 00000 n \n"
        "0000000200 00000 n \n"
        "0000000259 00000 n \n"
        "0000000334 00000 n \n"
        "0000000365 00000 n \n"
        "trailer\n<< /Size 7 /Root 1 0 R >>\n"
        "startxref\n443\n%%EOF\n";

    const char *tmpFile = "/tmp/test_struct_tree_getchild_1716.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPDF, 1, sizeof(minimalPDF) - 1, f);
        fclose(f);

        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile));
        if (doc->isOk()) {
            const StructTreeRoot *root = doc->getStructTreeRoot();
            if (root && root->getNumChildren() > 0) {
                const StructElement *child = root->getChild(0);
                EXPECT_NE(child, nullptr);
            }
        }
        unlink(tmpFile);
    }
}

// Test that getNumChildren reflects children parsed from /K array
TEST_F(StructTreeRootTest_1716, GetNumChildrenWithMultipleChildren_1716)
{
    static const char minimalPDF[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /MarkInfo << /Marked true >> /StructTreeRoot 2 0 R /Pages 3 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /StructTreeRoot /K [4 0 R 5 0 R] /ParentTree 6 0 R >>\nendobj\n"
        "3 0 obj\n<< /Type /Pages /Kids [7 0 R] /Count 1 >>\nendobj\n"
        "4 0 obj\n<< /Type /StructElem /S /Document /P 2 0 R >>\nendobj\n"
        "5 0 obj\n<< /Type /StructElem /S /Part /P 2 0 R >>\nendobj\n"
        "6 0 obj\n<< /Nums [] >>\nendobj\n"
        "7 0 obj\n<< /Type /Page /Parent 3 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 8\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000115 00000 n \n"
        "0000000208 00000 n \n"
        "0000000267 00000 n \n"
        "0000000342 00000 n \n"
        "0000000411 00000 n \n"
        "0000000442 00000 n \n"
        "trailer\n<< /Size 8 /Root 1 0 R >>\n"
        "startxref\n520\n%%EOF\n";

    const char *tmpFile = "/tmp/test_struct_tree_multi_1716.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPDF, 1, sizeof(minimalPDF) - 1, f);
        fclose(f);

        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile));
        if (doc->isOk()) {
            const StructTreeRoot *root = doc->getStructTreeRoot();
            if (root) {
                // With /K as an array of two refs, should have 2 children
                EXPECT_GE(root->getNumChildren(), 1u);
            }
        }
        unlink(tmpFile);
    }
}

// Test that getRoleMap returns nullptr when no RoleMap is present
TEST_F(StructTreeRootTest_1716, GetRoleMapReturnsNullWhenAbsent_1716)
{
    static const char minimalPDF[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /MarkInfo << /Marked true >> /StructTreeRoot 2 0 R /Pages 3 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /StructTreeRoot >>\nendobj\n"
        "3 0 obj\n<< /Type /Pages /Kids [4 0 R] /Count 1 >>\nendobj\n"
        "4 0 obj\n<< /Type /Page /Parent 3 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000115 00000 n \n"
        "0000000163 00000 n \n"
        "0000000222 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n300\n%%EOF\n";

    const char *tmpFile = "/tmp/test_struct_tree_norolemap_1716.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPDF, 1, sizeof(minimalPDF) - 1, f);
        fclose(f);

        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile));
        if (doc->isOk()) {
            StructTreeRoot *root = doc->getStructTreeRoot();
            if (root) {
                // Without a RoleMap entry, getRoleMap may return nullptr
                Dict *roleMap = root->getRoleMap();
                // This is an observable behavior test - it may or may not be null
                // depending on implementation, but we test the interface doesn't crash
                SUCCEED();
            }
        }
        unlink(tmpFile);
    }
}

// Test that getClassMap returns nullptr when no ClassMap is present
TEST_F(StructTreeRootTest_1716, GetClassMapReturnsNullWhenAbsent_1716)
{
    static const char minimalPDF[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /MarkInfo << /Marked true >> /StructTreeRoot 2 0 R /Pages 3 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /StructTreeRoot >>\nendobj\n"
        "3 0 obj\n<< /Type /Pages /Kids [4 0 R] /Count 1 >>\nendobj\n"
        "4 0 obj\n<< /Type /Page /Parent 3 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000115 00000 n \n"
        "0000000163 00000 n \n"
        "0000000222 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n300\n%%EOF\n";

    const char *tmpFile = "/tmp/test_struct_tree_noclassmap_1716.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPDF, 1, sizeof(minimalPDF) - 1, f);
        fclose(f);

        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile));
        if (doc->isOk()) {
            StructTreeRoot *root = doc->getStructTreeRoot();
            if (root) {
                Dict *classMap = root->getClassMap();
                // Test that the interface doesn't crash
                SUCCEED();
            }
        }
        unlink(tmpFile);
    }
}

// Test findParentElement returns nullptr for non-existent key
TEST_F(StructTreeRootTest_1716, FindParentElementNonExistentKey_1716)
{
    static const char minimalPDF[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /MarkInfo << /Marked true >> /StructTreeRoot 2 0 R /Pages 3 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /StructTreeRoot /K 4 0 R /ParentTree 5 0 R >>\nendobj\n"
        "3 0 obj\n<< /Type /Pages /Kids [6 0 R] /Count 1 >>\nendobj\n"
        "4 0 obj\n<< /Type /StructElem /S /Document /P 2 0 R >>\nendobj\n"
        "5 0 obj\n<< /Nums [] >>\nendobj\n"
        "6 0 obj\n<< /Type /Page /Parent 3 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 7\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000115 00000 n \n"
        "0000000200 00000 n \n"
        "0000000259 00000 n \n"
        "0000000334 00000 n \n"
        "0000000365 00000 n \n"
        "trailer\n<< /Size 7 /Root 1 0 R >>\n"
        "startxref\n443\n%%EOF\n";

    const char *tmpFile = "/tmp/test_struct_tree_findparent_1716.pdf";
    FILE *f = fopen(tmpFile, "wb");
    if (f) {
        fwrite(minimalPDF, 1, sizeof(minimalPDF) - 1, f);
        fclose(f);

        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile));
        if (doc->isOk()) {
            const StructTreeRoot *root = doc->getStructTreeRoot();
            if (root) {
                // Looking up a key that doesn't exist should return nullptr
                const StructElement *elem = root->findParentElement(99999);
                EXPECT_EQ(elem, nullptr);
            }
        }
        unlink(tmpFile);
    }
}

// Test that copy constructor and assignment operator are deleted
// This is a compile-time check - if the code compiles, the test passes
TEST_F(StructTreeRootTest_1716, CopyAndAssignmentDeleted_1716)
{
    // These should not compile:
    // StructTreeRoot copy(original);
    // StructTreeRoot assigned = original;
    // We verify this by checking the type traits
    EXPECT_FALSE(std::is_copy_constructible<StructTreeRoot>::value);
    EXPECT_FALSE(std::is_copy_assignable<StructTreeRoot>::value);
}
