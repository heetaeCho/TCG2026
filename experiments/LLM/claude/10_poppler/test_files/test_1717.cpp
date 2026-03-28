#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "StructTreeRoot.h"
#include "PDFDoc.h"
#include "Object.h"
#include "Dict.h"
#include "GlobalParams.h"

#include <memory>
#include <string>

class StructTreeRootTest_1717 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test getRoleMap returns nullptr when roleMap is not a dict (empty/minimal PDF)
TEST_F(StructTreeRootTest_1717, GetRoleMapReturnsNullWhenNotDict_1717) {
    // Create a minimal Dict that represents a StructTreeRoot without a RoleMap
    XRef xref;
    Dict rootDict(&xref);
    
    // Add minimal required Type entry
    rootDict.add("Type", Object(objName, "StructTreeRoot"));
    
    // Create a minimal PDFDoc from a simple PDF file
    // Since we can't easily create a PDFDoc without a file, we test via 
    // a constructed object if possible. 
    // We need to try constructing with a minimal setup.
    
    // Create a GooString with a minimal PDF in memory
    const char *minimalPdf = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [] /Count 0 >>\nendobj\n"
        "xref\n0 3\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "trailer\n<< /Size 3 /Root 1 0 R >>\n"
        "startxref\n110\n%%EOF\n";

    auto stream = std::make_unique<GooString>(minimalPdf);
    auto doc = std::make_unique<PDFDoc>(stream.release());
    
    if (doc->isOk()) {
        Dict emptyRoot(doc->getXRef());
        emptyRoot.add("Type", Object(objName, "StructTreeRoot"));
        
        StructTreeRoot root(doc.get(), emptyRoot);
        
        // Without a RoleMap entry, getRoleMap should return nullptr
        EXPECT_EQ(root.getRoleMap(), nullptr);
    }
}

// Test getRoleMap returns a valid Dict pointer when roleMap is a dict
TEST_F(StructTreeRootTest_1717, GetRoleMapReturnsDictWhenPresent_1717) {
    const char *minimalPdf = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [] /Count 0 >>\nendobj\n"
        "xref\n0 3\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "trailer\n<< /Size 3 /Root 1 0 R >>\n"
        "startxref\n110\n%%EOF\n";

    auto stream = std::make_unique<GooString>(minimalPdf);
    auto doc = std::make_unique<PDFDoc>(stream.release());
    
    if (doc->isOk()) {
        Dict *roleMapDict = new Dict(doc->getXRef());
        roleMapDict->add("Sect", Object(objName, "Div"));
        
        Dict rootDict(doc->getXRef());
        rootDict.add("Type", Object(objName, "StructTreeRoot"));
        rootDict.add("RoleMap", Object(roleMapDict));
        
        StructTreeRoot root(doc.get(), rootDict);
        
        Dict *result = root.getRoleMap();
        EXPECT_NE(result, nullptr);
    }
}

// Test getClassMap returns nullptr when classMap is not present
TEST_F(StructTreeRootTest_1717, GetClassMapReturnsNullWhenNotPresent_1717) {
    const char *minimalPdf = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [] /Count 0 >>\nendobj\n"
        "xref\n0 3\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "trailer\n<< /Size 3 /Root 1 0 R >>\n"
        "startxref\n110\n%%EOF\n";

    auto stream = std::make_unique<GooString>(minimalPdf);
    auto doc = std::make_unique<PDFDoc>(stream.release());
    
    if (doc->isOk()) {
        Dict emptyRoot(doc->getXRef());
        emptyRoot.add("Type", Object(objName, "StructTreeRoot"));
        
        StructTreeRoot root(doc.get(), emptyRoot);
        
        EXPECT_EQ(root.getClassMap(), nullptr);
    }
}

// Test getNumChildren returns 0 for empty tree
TEST_F(StructTreeRootTest_1717, GetNumChildrenReturnsZeroForEmptyTree_1717) {
    const char *minimalPdf = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [] /Count 0 >>\nendobj\n"
        "xref\n0 3\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "trailer\n<< /Size 3 /Root 1 0 R >>\n"
        "startxref\n110\n%%EOF\n";

    auto stream = std::make_unique<GooString>(minimalPdf);
    auto doc = std::make_unique<PDFDoc>(stream.release());
    
    if (doc->isOk()) {
        Dict emptyRoot(doc->getXRef());
        emptyRoot.add("Type", Object(objName, "StructTreeRoot"));
        
        StructTreeRoot root(doc.get(), emptyRoot);
        
        EXPECT_EQ(root.getNumChildren(), 0u);
    }
}

// Test getDoc returns the correct PDFDoc pointer
TEST_F(StructTreeRootTest_1717, GetDocReturnsCorrectPointer_1717) {
    const char *minimalPdf = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [] /Count 0 >>\nendobj\n"
        "xref\n0 3\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "trailer\n<< /Size 3 /Root 1 0 R >>\n"
        "startxref\n110\n%%EOF\n";

    auto stream = std::make_unique<GooString>(minimalPdf);
    auto doc = std::make_unique<PDFDoc>(stream.release());
    
    if (doc->isOk()) {
        Dict emptyRoot(doc->getXRef());
        emptyRoot.add("Type", Object(objName, "StructTreeRoot"));
        
        StructTreeRoot root(doc.get(), emptyRoot);
        
        EXPECT_EQ(root.getDoc(), doc.get());
    }
}

// Test findParentElement returns nullptr when tree is empty
TEST_F(StructTreeRootTest_1717, FindParentElementReturnsNullForEmptyTree_1717) {
    const char *minimalPdf = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [] /Count 0 >>\nendobj\n"
        "xref\n0 3\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "trailer\n<< /Size 3 /Root 1 0 R >>\n"
        "startxref\n110\n%%EOF\n";

    auto stream = std::make_unique<GooString>(minimalPdf);
    auto doc = std::make_unique<PDFDoc>(stream.release());
    
    if (doc->isOk()) {
        Dict emptyRoot(doc->getXRef());
        emptyRoot.add("Type", Object(objName, "StructTreeRoot"));
        
        StructTreeRoot root(doc.get(), emptyRoot);
        
        EXPECT_EQ(root.findParentElement(0), nullptr);
        EXPECT_EQ(root.findParentElement(42), nullptr);
        EXPECT_EQ(root.findParentElement(-1), nullptr);
    }
}

// Test copy constructor is deleted
TEST_F(StructTreeRootTest_1717, CopyConstructorIsDeleted_1717) {
    EXPECT_FALSE(std::is_copy_constructible<StructTreeRoot>::value);
}

// Test copy assignment is deleted
TEST_F(StructTreeRootTest_1717, CopyAssignmentIsDeleted_1717) {
    EXPECT_FALSE(std::is_copy_assignable<StructTreeRoot>::value);
}
