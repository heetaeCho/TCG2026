#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "poppler/StructElement.h"
#include "poppler/StructTreeRoot.h"
#include "poppler/PDFDoc.h"
#include "poppler/GlobalParams.h"

#include <memory>

class StructElementTest_1704 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getExpandedAbbr returns nullptr for content elements (MCID-based)
// Since we cannot easily construct StructElement objects due to private constructors
// and complex dependencies, we test through document loading if possible.
// However, we can verify the interface contract through the method signature.

// We test with a known PDF that has structure elements if available,
// otherwise we verify the basic contract.

TEST_F(StructElementTest_1704, GetExpandedAbbrReturnsNullForContentElement_1704) {
    // Content elements should return nullptr from getExpandedAbbr
    // This tests the documented behavior: isContent() ? nullptr : s->expandedAbbr.get()
    // We need a real PDF with tagged content to properly test this.
    // For now, we verify the interface exists and compiles correctly.
    
    // Create a minimal PDF document with structure tree
    // Try loading a simple tagged PDF
    GooString filename("../test/unittestcases/tagged_pdf.pdf");
    auto doc = std::make_unique<PDFDoc>(&filename);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping";
    }
    
    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF, skipping";
    }
    
    // Walk the tree to find content and non-content elements
    bool foundContent = false;
    bool foundNonContent = false;
    
    std::function<void(const StructElement*)> walkTree = [&](const StructElement* elem) {
        if (!elem || !elem->isOk()) return;
        
        if (elem->isContent()) {
            // Content elements must return nullptr
            EXPECT_EQ(nullptr, elem->getExpandedAbbr()) 
                << "Content element should return nullptr for getExpandedAbbr";
            foundContent = true;
        } else {
            // Non-content elements may or may not have expanded abbreviation
            // but the call should not crash
            const GooString* abbr = elem->getExpandedAbbr();
            (void)abbr; // Just verify it doesn't crash
            foundNonContent = true;
        }
        
        for (unsigned i = 0; i < elem->getNumChildren(); i++) {
            walkTree(elem->getChild(i));
        }
    };
    
    for (unsigned i = 0; i < root->getNumChildren(); i++) {
        walkTree(root->getChild(i));
    }
    
    // We should have found at least some elements
    EXPECT_TRUE(foundContent || foundNonContent) 
        << "Should have found at least one element in the structure tree";
}

TEST_F(StructElementTest_1704, NonContentElementExpandedAbbrCanBeNull_1704) {
    // Non-content elements without an expanded abbreviation set should
    // return nullptr (since expandedAbbr unique_ptr is default null)
    
    GooString filename("../test/unittestcases/tagged_pdf.pdf");
    auto doc = std::make_unique<PDFDoc>(&filename);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping";
    }
    
    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF, skipping";
    }
    
    // Most standard structure elements won't have expandedAbbr set
    const StructElement* child = root->getChild(0);
    if (child && child->isOk() && !child->isContent()) {
        // This should not crash regardless of whether expandedAbbr is set
        const GooString* result = child->getExpandedAbbr();
        // Result may be nullptr if no abbreviation was set in the PDF
        // We just verify the call succeeds without crashing
        (void)result;
        SUCCEED();
    } else {
        GTEST_SKIP() << "First child is not a suitable non-content element";
    }
}

TEST_F(StructElementTest_1704, IsContentConsistentWithGetExpandedAbbr_1704) {
    // Verify that when isContent() returns true, getExpandedAbbr() always returns nullptr
    
    GooString filename("../test/unittestcases/tagged_pdf.pdf");
    auto doc = std::make_unique<PDFDoc>(&filename);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping";
    }
    
    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF, skipping";
    }
    
    int contentCount = 0;
    
    std::function<void(const StructElement*)> verifyConsistency = [&](const StructElement* elem) {
        if (!elem || !elem->isOk()) return;
        
        if (elem->isContent()) {
            EXPECT_EQ(nullptr, elem->getExpandedAbbr());
            contentCount++;
        }
        
        for (unsigned i = 0; i < elem->getNumChildren(); i++) {
            verifyConsistency(elem->getChild(i));
        }
    };
    
    for (unsigned i = 0; i < root->getNumChildren(); i++) {
        verifyConsistency(root->getChild(i));
    }
    
    if (contentCount == 0) {
        GTEST_SKIP() << "No content elements found to verify";
    }
}

TEST_F(StructElementTest_1704, StructElementBasicProperties_1704) {
    // Test various basic properties of StructElement through a real document
    
    GooString filename("../test/unittestcases/tagged_pdf.pdf");
    auto doc = std::make_unique<PDFDoc>(&filename);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping";
    }
    
    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF, skipping";
    }
    
    const StructElement* elem = root->getChild(0);
    ASSERT_NE(nullptr, elem);
    EXPECT_TRUE(elem->isOk());
    
    // Type name should not be null for valid elements
    if (!elem->isContent()) {
        EXPECT_NE(nullptr, elem->getTypeName());
    }
    
    // Test revision get/set
    unsigned int rev = elem->getRevision();
    elem->setRevision(rev + 1);
    EXPECT_EQ(rev + 1, elem->getRevision());
    elem->setRevision(rev); // restore
    
    // Test tree navigation
    EXPECT_EQ(root, elem->getStructTreeRoot());
}

TEST_F(StructElementTest_1704, ContentElementProperties_1704) {
    // Find a content element and verify its properties
    
    GooString filename("../test/unittestcases/tagged_pdf.pdf");
    auto doc = std::make_unique<PDFDoc>(&filename);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping";
    }
    
    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF, skipping";
    }
    
    const StructElement* contentElem = nullptr;
    
    std::function<void(const StructElement*)> findContent = [&](const StructElement* elem) {
        if (!elem || !elem->isOk() || contentElem) return;
        if (elem->isContent()) {
            contentElem = elem;
            return;
        }
        for (unsigned i = 0; i < elem->getNumChildren(); i++) {
            findContent(elem->getChild(i));
        }
    };
    
    for (unsigned i = 0; i < root->getNumChildren(); i++) {
        findContent(root->getChild(i));
    }
    
    if (!contentElem) {
        GTEST_SKIP() << "No content element found";
    }
    
    EXPECT_TRUE(contentElem->isContent());
    EXPECT_EQ(nullptr, contentElem->getExpandedAbbr());
    EXPECT_EQ(nullptr, contentElem->getTitle());
    EXPECT_EQ(nullptr, contentElem->getID());
    
    // Content element should have a valid MCID or be an object ref
    if (!contentElem->isObjectRef()) {
        int mcid = contentElem->getMCID();
        EXPECT_GE(mcid, 0);
    }
}
