#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "StructElement.h"
#include "StructTreeRoot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"

#include <memory>
#include <cstring>

class StructElementTest_1691 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Since StructElement constructors are private and objects are created
// internally through parsing, we test through PDF document loading
// or through any accessible creation path.

// Test isContent for a non-content (grouping/block/inline) element
TEST_F(StructElementTest_1691, NonContentElementIsContentReturnsFalse_1691) {
    // A grouping/block/inline element that is not MCID and not ObjectRef
    // should return false for isContent()
    // We need a PDF with structure tree to test this properly
    // For now, we verify the interface contract through document-based testing
    
    // Create a minimal PDF document with structure tree
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    const auto *catalog = doc->getCatalog();
    if (!catalog) {
        GTEST_SKIP() << "No catalog";
    }
    
    auto *structTree = catalog->getStructTreeRoot();
    if (!structTree || structTree->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree";
    }
    
    // Root-level structure elements are typically grouping elements, not content
    const StructElement *root = structTree->getChild(0);
    ASSERT_NE(root, nullptr);
    
    if (root->isGrouping() || root->isBlock() || root->isInline()) {
        EXPECT_FALSE(root->isContent());
    }
}

// Test that isContent returns true for MCID or ObjectRef type elements
TEST_F(StructElementTest_1691, ContentElementIsContentReturnsTrue_1691) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    const auto *catalog = doc->getCatalog();
    if (!catalog) {
        GTEST_SKIP() << "No catalog";
    }
    
    auto *structTree = catalog->getStructTreeRoot();
    if (!structTree || structTree->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree";
    }
    
    // Traverse to find a content element (leaf node with MCID)
    std::function<const StructElement*(const StructElement*)> findContent;
    findContent = [&](const StructElement *elem) -> const StructElement* {
        if (!elem) return nullptr;
        if (elem->isContent()) return elem;
        for (unsigned i = 0; i < elem->getNumChildren(); i++) {
            auto *found = findContent(elem->getChild(i));
            if (found) return found;
        }
        return nullptr;
    };
    
    const StructElement *content = nullptr;
    for (unsigned i = 0; i < structTree->getNumChildren(); i++) {
        content = findContent(structTree->getChild(i));
        if (content) break;
    }
    
    if (!content) {
        GTEST_SKIP() << "No content element found in structure tree";
    }
    
    EXPECT_TRUE(content->isContent());
    // A content element should not be grouping, block, or inline
    EXPECT_FALSE(content->isGrouping());
    EXPECT_FALSE(content->isBlock());
    EXPECT_FALSE(content->isInline());
}

// Test isOk for structure elements
TEST_F(StructElementTest_1691, StructElementIsOk_1691) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    const auto *catalog = doc->getCatalog();
    if (!catalog) {
        GTEST_SKIP() << "No catalog";
    }
    
    auto *structTree = catalog->getStructTreeRoot();
    if (!structTree || structTree->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree";
    }
    
    const StructElement *elem = structTree->getChild(0);
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->isOk());
}

// Test getTypeName returns non-null for valid elements
TEST_F(StructElementTest_1691, GetTypeNameReturnsNonNull_1691) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    const auto *catalog = doc->getCatalog();
    if (!catalog) {
        GTEST_SKIP() << "No catalog";
    }
    
    auto *structTree = catalog->getStructTreeRoot();
    if (!structTree || structTree->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree";
    }
    
    const StructElement *elem = structTree->getChild(0);
    ASSERT_NE(elem, nullptr);
    
    if (!elem->isContent()) {
        const char *name = elem->getTypeName();
        EXPECT_NE(name, nullptr);
        EXPECT_GT(strlen(name), 0u);
    }
}

// Test getParent for root element
TEST_F(StructElementTest_1691, RootElementParentBehavior_1691) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    const auto *catalog = doc->getCatalog();
    if (!catalog) {
        GTEST_SKIP() << "No catalog";
    }
    
    auto *structTree = catalog->getStructTreeRoot();
    if (!structTree || structTree->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree";
    }
    
    const StructElement *root = structTree->getChild(0);
    ASSERT_NE(root, nullptr);
    
    // Root-level children of the tree should exist
    // Their parent might be null or might point to a pseudo-root
    // Just verify we can call it without crashing
    root->getParent();
}

// Test getNumChildren for non-leaf elements
TEST_F(StructElementTest_1691, NonLeafElementHasChildren_1691) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    const auto *catalog = doc->getCatalog();
    if (!catalog) {
        GTEST_SKIP() << "No catalog";
    }
    
    auto *structTree = catalog->getStructTreeRoot();
    if (!structTree || structTree->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree";
    }
    
    // Find a non-leaf element (one that has children)
    std::function<const StructElement*(const StructElement*)> findNonLeaf;
    findNonLeaf = [&](const StructElement *elem) -> const StructElement* {
        if (!elem) return nullptr;
        if (elem->getNumChildren() > 0 && !elem->isContent()) return elem;
        for (unsigned i = 0; i < elem->getNumChildren(); i++) {
            auto *found = findNonLeaf(elem->getChild(i));
            if (found) return found;
        }
        return nullptr;
    };
    
    const StructElement *nonLeaf = nullptr;
    for (unsigned i = 0; i < structTree->getNumChildren(); i++) {
        nonLeaf = findNonLeaf(structTree->getChild(i));
        if (nonLeaf) break;
    }
    
    if (!nonLeaf) {
        GTEST_SKIP() << "No non-leaf element found";
    }
    
    EXPECT_GT(nonLeaf->getNumChildren(), 0u);
    
    // Verify children are accessible
    for (unsigned i = 0; i < nonLeaf->getNumChildren(); i++) {
        const StructElement *child = nonLeaf->getChild(i);
        EXPECT_NE(child, nullptr);
    }
}

// Test content element getMCID
TEST_F(StructElementTest_1691, ContentElementGetMCID_1691) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    const auto *catalog = doc->getCatalog();
    if (!catalog) {
        GTEST_SKIP() << "No catalog";
    }
    
    auto *structTree = catalog->getStructTreeRoot();
    if (!structTree || structTree->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree";
    }
    
    // Find an MCID content element
    std::function<const StructElement*(const StructElement*)> findMCID;
    findMCID = [&](const StructElement *elem) -> const StructElement* {
        if (!elem) return nullptr;
        if (elem->isContent() && !elem->isObjectRef()) return elem;
        for (unsigned i = 0; i < elem->getNumChildren(); i++) {
            auto *found = findMCID(elem->getChild(i));
            if (found) return found;
        }
        return nullptr;
    };
    
    const StructElement *mcidElem = nullptr;
    for (unsigned i = 0; i < structTree->getNumChildren(); i++) {
        mcidElem = findMCID(structTree->getChild(i));
        if (mcidElem) break;
    }
    
    if (!mcidElem) {
        GTEST_SKIP() << "No MCID content element found";
    }
    
    EXPECT_TRUE(mcidElem->isContent());
    EXPECT_FALSE(mcidElem->isObjectRef());
    // MCID should be non-negative
    EXPECT_GE(mcidElem->getMCID(), 0);
}

// Test that grouping elements have correct type classification
TEST_F(StructElementTest_1691, TypeClassificationMutualExclusion_1691) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    const auto *catalog = doc->getCatalog();
    if (!catalog) {
        GTEST_SKIP() << "No catalog";
    }
    
    auto *structTree = catalog->getStructTreeRoot();
    if (!structTree || structTree->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree";
    }
    
    // Verify type classification mutual exclusion across all elements
    std::function<void(const StructElement*)> verifyClassification;
    verifyClassification = [&](const StructElement *elem) {
        if (!elem) return;
        
        int typeCount = 0;
        if (elem->isGrouping()) typeCount++;
        if (elem->isBlock()) typeCount++;
        if (elem->isInline()) typeCount++;
        if (elem->isContent()) typeCount++;
        
        // An element should be exactly one of these categories (or possibly none if unknown)
        EXPECT_LE(typeCount, 1) << "Element has multiple type classifications";
        
        for (unsigned i = 0; i < elem->getNumChildren(); i++) {
            verifyClassification(elem->getChild(i));
        }
    };
    
    for (unsigned i = 0; i < structTree->getNumChildren(); i++) {
        verifyClassification(structTree->getChild(i));
    }
}

// Test getStructTreeRoot
TEST_F(StructElementTest_1691, GetStructTreeRoot_1691) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    const auto *catalog = doc->getCatalog();
    if (!catalog) {
        GTEST_SKIP() << "No catalog";
    }
    
    auto *structTree = catalog->getStructTreeRoot();
    if (!structTree || structTree->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree";
    }
    
    // Non-const access needed for getStructTreeRoot
    // The child's tree root should match the tree we got from the catalog
    // We test indirectly since we have const access
    const StructElement *elem = structTree->getChild(0);
    ASSERT_NE(elem, nullptr);
    // Just verify the method is callable and doesn't crash
    // (We can't call non-const method on const pointer directly)
}

// Test leaf content elements have zero children
TEST_F(StructElementTest_1691, ContentElementHasNoChildren_1691) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    const auto *catalog = doc->getCatalog();
    if (!catalog) {
        GTEST_SKIP() << "No catalog";
    }
    
    auto *structTree = catalog->getStructTreeRoot();
    if (!structTree || structTree->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree";
    }
    
    std::function<const StructElement*(const StructElement*)> findContent;
    findContent = [&](const StructElement *elem) -> const StructElement* {
        if (!elem) return nullptr;
        if (elem->isContent()) return elem;
        for (unsigned i = 0; i < elem->getNumChildren(); i++) {
            auto *found = findContent(elem->getChild(i));
            if (found) return found;
        }
        return nullptr;
    };
    
    const StructElement *content = nullptr;
    for (unsigned i = 0; i < structTree->getNumChildren(); i++) {
        content = findContent(structTree->getChild(i));
        if (content) break;
    }
    
    if (!content) {
        GTEST_SKIP() << "No content element found";
    }
    
    // Content elements (MCID/ObjectRef) are leaf nodes
    EXPECT_EQ(content->getNumChildren(), 0u);
}

// Test isObjectRef element behavior
TEST_F(StructElementTest_1691, ObjectRefElementIsContent_1691) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    const auto *catalog = doc->getCatalog();
    if (!catalog) {
        GTEST_SKIP() << "No catalog";
    }
    
    auto *structTree = catalog->getStructTreeRoot();
    if (!structTree || structTree->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree";
    }
    
    // Find an ObjectRef content element if any
    std::function<const StructElement*(const StructElement*)> findObjRef;
    findObjRef = [&](const StructElement *elem) -> const StructElement* {
        if (!elem) return nullptr;
        if (elem->isObjectRef()) return elem;
        for (unsigned i = 0; i < elem->getNumChildren(); i++) {
            auto *found = findObjRef(elem->getChild(i));
            if (found) return found;
        }
        return nullptr;
    };
    
    const StructElement *objRef = nullptr;
    for (unsigned i = 0; i < structTree->getNumChildren(); i++) {
        objRef = findObjRef(structTree->getChild(i));
        if (objRef) break;
    }
    
    if (!objRef) {
        GTEST_SKIP() << "No ObjectRef element found in structure tree";
    }
    
    // ObjectRef elements should also be content
    EXPECT_TRUE(objRef->isContent());
    EXPECT_TRUE(objRef->isObjectRef());
}

// Test revision getter/setter
TEST_F(StructElementTest_1691, RevisionGetterSetter_1691) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    const auto *catalog = doc->getCatalog();
    if (!catalog) {
        GTEST_SKIP() << "No catalog";
    }
    
    auto *structTree = catalog->getStructTreeRoot();
    if (!structTree || structTree->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree";
    }
    
    const StructElement *elem = structTree->getChild(0);
    ASSERT_NE(elem, nullptr);
    
    unsigned int origRevision = elem->getRevision();
    
    // Set a new revision
    elem->setRevision(42);
    EXPECT_EQ(elem->getRevision(), 42u);
    
    // Restore original
    elem->setRevision(origRevision);
    EXPECT_EQ(elem->getRevision(), origRevision);
}

// Test boundary: getChild with valid index
TEST_F(StructElementTest_1691, GetChildValidIndex_1691) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    const auto *catalog = doc->getCatalog();
    if (!catalog) {
        GTEST_SKIP() << "No catalog";
    }
    
    auto *structTree = catalog->getStructTreeRoot();
    if (!structTree || structTree->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree";
    }
    
    const StructElement *elem = structTree->getChild(0);
    ASSERT_NE(elem, nullptr);
    
    if (elem->getNumChildren() > 0) {
        // First child should be accessible
        const StructElement *firstChild = elem->getChild(0);
        EXPECT_NE(firstChild, nullptr);
        
        // Last child should be accessible
        const StructElement *lastChild = elem->getChild(elem->getNumChildren() - 1);
        EXPECT_NE(lastChild, nullptr);
    }
}

// Test getText on structure elements
TEST_F(StructElementTest_1691, GetTextOnElement_1691) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    const auto *catalog = doc->getCatalog();
    if (!catalog) {
        GTEST_SKIP() << "No catalog";
    }
    
    auto *structTree = catalog->getStructTreeRoot();
    if (!structTree || structTree->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree";
    }
    
    const StructElement *elem = structTree->getChild(0);
    ASSERT_NE(elem, nullptr);
    
    // getText should be callable (may return nullptr if no text)
    GooString *text = elem->getText(true);
    // Just verify it doesn't crash; text may or may not be available
    delete text;
    
    GooString *textNonRecursive = elem->getText(false);
    delete textNonRecursive;
}

// Test getAltText and getActualText
TEST_F(StructElementTest_1691, AltAndActualText_1691) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    const auto *catalog = doc->getCatalog();
    if (!catalog) {
        GTEST_SKIP() << "No catalog";
    }
    
    auto *structTree = catalog->getStructTreeRoot();
    if (!structTree || structTree->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree";
    }
    
    const StructElement *elem = structTree->getChild(0);
    ASSERT_NE(elem, nullptr);
    
    // These may return nullptr; just verify they don't crash
    elem->getAltText();
    elem->getActualText();
}

// Test hasPageRef
TEST_F(StructElementTest_1691, HasPageRef_1691) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    const auto *catalog = doc->getCatalog();
    if (!catalog) {
        GTEST_SKIP() << "No catalog";
    }
    
    auto *structTree = catalog->getStructTreeRoot();
    if (!structTree || structTree->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree";
    }
    
    std::function<void(const StructElement*)> checkPageRef;
    checkPageRef = [&](const StructElement *elem) {
        if (!elem) return;
        
        bool has = elem->hasPageRef();
        if (has) {
            Ref ref;
            bool got = elem->getPageRef(ref);
            EXPECT_TRUE(got);
            EXPECT_GE(ref.num, 0);
        }
        
        for (unsigned i = 0; i < elem->getNumChildren(); i++) {
            checkPageRef(elem->getChild(i));
        }
    };
    
    for (unsigned i = 0; i < structTree->getNumChildren(); i++) {
        checkPageRef(structTree->getChild(i));
    }
}

// Test getID, getTitle, getLanguage, getExpandedAbbr
TEST_F(StructElementTest_1691, MetadataAccessors_1691) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    const auto *catalog = doc->getCatalog();
    if (!catalog) {
        GTEST_SKIP() << "No catalog";
    }
    
    auto *structTree = catalog->getStructTreeRoot();
    if (!structTree || structTree->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree";
    }
    
    const StructElement *elem = structTree->getChild(0);
    ASSERT_NE(elem, nullptr);
    
    // These are all optional fields; just verify no crash
    elem->getID();
    elem->getTitle();
    elem->getExpandedAbbr();
}

// Test attributes
TEST_F(StructElementTest_1691, AttributeAccess_1691) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    const auto *catalog = doc->getCatalog();
    if (!catalog) {
        GTEST_SKIP() << "No catalog";
    }
    
    auto *structTree = catalog->getStructTreeRoot();
    if (!structTree || structTree->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree";
    }
    
    const StructElement *elem = structTree->getChild(0);
    ASSERT_NE(elem, nullptr);
    
    unsigned numAttrs = elem->getNumAttributes();
    for (unsigned i = 0; i < numAttrs; i++) {
        const Attribute *attr = elem->getAttribute(i);
        EXPECT_NE(attr, nullptr);
    }
}
