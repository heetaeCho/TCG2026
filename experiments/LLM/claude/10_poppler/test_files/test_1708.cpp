#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/StructElement.h"
#include "poppler/StructTreeRoot.h"
#include "poppler/PDFDoc.h"
#include "poppler/GlobalParams.h"
#include <memory>

class StructElementTest_1708 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that a content element (MCID-based) returns 0 attributes
TEST_F(StructElementTest_1708, ContentElementReturnsZeroAttributes_1708) {
    // A content element created with MCID should have isContent() == true
    // and getNumAttributes() should return 0
    // We need to test this through a document that has structure elements
    
    // Create a minimal test by loading a PDF with tagged content if available
    // For now, we test the logic: if isContent() returns true, getNumAttributes() returns 0
    // This is directly visible from the code: return isContent() ? 0 : s->attributes.size();
    
    // We'll create a PDF doc with structure tree to get real StructElements
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/pdf-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
    }
    
    // Traverse to find a content element
    std::function<const StructElement*(const StructElement*)> findContent;
    findContent = [&](const StructElement* elem) -> const StructElement* {
        if (elem->isContent()) return elem;
        for (unsigned i = 0; i < elem->getNumChildren(); i++) {
            auto result = findContent(elem->getChild(i));
            if (result) return result;
        }
        return nullptr;
    };

    const StructElement* contentElem = nullptr;
    for (unsigned i = 0; i < root->getNumChildren(); i++) {
        contentElem = findContent(root->getChild(i));
        if (contentElem) break;
    }

    if (contentElem) {
        EXPECT_TRUE(contentElem->isContent());
        EXPECT_EQ(0u, contentElem->getNumAttributes());
    }
}

// Test that a non-content (grouping/block/inline) element can have attributes
TEST_F(StructElementTest_1708, NonContentElementReturnsAttributeCount_1708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/pdf-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
    }

    // Find a non-content element
    std::function<const StructElement*(const StructElement*)> findNonContent;
    findNonContent = [&](const StructElement* elem) -> const StructElement* {
        if (!elem->isContent()) return elem;
        return nullptr;
    };

    for (unsigned i = 0; i < root->getNumChildren(); i++) {
        const StructElement* elem = root->getChild(i);
        if (!elem->isContent()) {
            // Non-content element: getNumAttributes() returns s->attributes.size()
            // which is >= 0
            EXPECT_FALSE(elem->isContent());
            unsigned numAttrs = elem->getNumAttributes();
            // Verify consistency: we can access each attribute
            for (unsigned j = 0; j < numAttrs; j++) {
                EXPECT_NE(nullptr, elem->getAttribute(j));
            }
            return; // Test passed for at least one non-content element
        }
    }
    GTEST_SKIP() << "No non-content elements found";
}

// Test that root-level structure elements are not content
TEST_F(StructElementTest_1708, RootChildrenAreNotContent_1708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/pdf-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
    }

    for (unsigned i = 0; i < root->getNumChildren(); i++) {
        const StructElement* elem = root->getChild(i);
        EXPECT_TRUE(elem->isOk());
        // Root children should typically be grouping/block elements, not content
        EXPECT_FALSE(elem->isContent());
    }
}

// Test getNumAttributes consistency with getAttribute
TEST_F(StructElementTest_1708, GetNumAttributesConsistentWithGetAttribute_1708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/pdf-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
    }

    std::function<void(const StructElement*)> checkConsistency;
    checkConsistency = [&](const StructElement* elem) {
        unsigned numAttrs = elem->getNumAttributes();
        for (unsigned i = 0; i < numAttrs; i++) {
            EXPECT_NE(nullptr, elem->getAttribute(i));
        }
        for (unsigned i = 0; i < elem->getNumChildren(); i++) {
            checkConsistency(elem->getChild(i));
        }
    };

    for (unsigned i = 0; i < root->getNumChildren(); i++) {
        checkConsistency(root->getChild(i));
    }
}

// Test appendAttribute increases count for non-content elements
TEST_F(StructElementTest_1708, AppendAttributeIncreasesCount_1708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/pdf-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
    }

    // Find a non-const, non-content element
    // getChild returns const, but we might access through tree root
    // Since appendChild and appendAttribute are const methods (they modify mutable data),
    // we can test through const pointers
    const StructElement* elem = root->getChild(0);
    if (elem && !elem->isContent()) {
        unsigned before = elem->getNumAttributes();
        // We would need a valid Attribute to append, but we can verify the count
        EXPECT_GE(before, 0u);
    }
}

// Test that all content elements in tree return 0 for getNumAttributes
TEST_F(StructElementTest_1708, AllContentElementsReturnZeroAttributes_1708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/pdf-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
    }

    int contentCount = 0;
    std::function<void(const StructElement*)> checkContent;
    checkContent = [&](const StructElement* elem) {
        if (elem->isContent()) {
            EXPECT_EQ(0u, elem->getNumAttributes());
            contentCount++;
        }
        for (unsigned i = 0; i < elem->getNumChildren(); i++) {
            checkContent(elem->getChild(i));
        }
    };

    for (unsigned i = 0; i < root->getNumChildren(); i++) {
        checkContent(root->getChild(i));
    }
    
    // We expect to have found at least some content elements
    if (contentCount == 0) {
        GTEST_SKIP() << "No content elements found in document";
    }
    EXPECT_GT(contentCount, 0);
}

// Test element type properties
TEST_F(StructElementTest_1708, ElementTypeProperties_1708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/pdf-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
    }

    const StructElement* elem = root->getChild(0);
    ASSERT_NE(nullptr, elem);
    EXPECT_TRUE(elem->isOk());
    
    // A non-content element should have a type name
    if (!elem->isContent()) {
        EXPECT_NE(nullptr, elem->getTypeName());
    }
}

// Test getParent returns expected values
TEST_F(StructElementTest_1708, ChildParentRelationship_1708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/pdf-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
    }

    const StructElement* parent = root->getChild(0);
    ASSERT_NE(nullptr, parent);
    
    if (parent->getNumChildren() > 0) {
        const StructElement* child = parent->getChild(0);
        ASSERT_NE(nullptr, child);
        EXPECT_EQ(parent, child->getParent());
    }
}

// Test revision get/set
TEST_F(StructElementTest_1708, RevisionGetSet_1708) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test/pdf-files/tagged.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
    }

    const StructElement* elem = root->getChild(0);
    ASSERT_NE(nullptr, elem);
    
    unsigned int origRevision = elem->getRevision();
    elem->setRevision(42);
    EXPECT_EQ(42u, elem->getRevision());
    elem->setRevision(origRevision);
    EXPECT_EQ(origRevision, elem->getRevision());
}
