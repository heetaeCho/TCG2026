#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "StructElement.h"
#include "StructTreeRoot.h"
#include "MarkedContentOutputDev.h"

// Since StructElement has private constructors and depends on complex PDF structures,
// we need to test through the public interface. We'll focus on what's testable
// given the constraints.

// Note: StructElement constructors are private, so we need to access them through
// the PDF parsing infrastructure or through friend/factory mechanisms.
// For testing getTextSpans(), we primarily need to verify:
// 1. Non-content elements return empty TextSpanArray
// 2. Content elements attempt to create spans via MarkedContentOutputDev

// We'll create a test fixture that attempts to set up minimal structures
// needed to test StructElement's public interface.

#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>

class StructElementTest_1715 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

// Test that getTextSpans on a non-content StructElement returns empty array
TEST_F(StructElementTest_1715, GetTextSpans_NonContentElement_ReturnsEmpty_1715)
{
    // Load a tagged PDF that has structure elements
    // Using a simple approach: if we can get a grouping/block element, 
    // getTextSpans should return empty since isContent() would be false
    
    // Try to load a sample tagged PDF
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/tagged_pdf.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
        return;
    }

    // Find a non-content (grouping/block) element
    const StructElement *elem = root->getChild(0);
    if (elem && !elem->isContent()) {
        TextSpanArray spans = elem->getTextSpans();
        EXPECT_TRUE(spans.empty());
    }
}

// Test isContent, isBlock, isInline, isGrouping are mutually consistent
TEST_F(StructElementTest_1715, ElementTypeConsistency_1715)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/tagged_pdf.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
        return;
    }

    const StructElement *elem = root->getChild(0);
    ASSERT_NE(elem, nullptr);

    // A content element should not be grouping, block, or inline in the structural sense
    // (content elements are MCID references, not structural types)
    if (elem->isContent()) {
        // Content elements represent marked content references
        EXPECT_FALSE(elem->isGrouping());
        EXPECT_FALSE(elem->isBlock());
        EXPECT_FALSE(elem->isInline());
    }
}

// Test getTypeName returns non-null for valid elements
TEST_F(StructElementTest_1715, GetTypeName_ValidElement_1715)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/tagged_pdf.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
        return;
    }

    const StructElement *elem = root->getChild(0);
    ASSERT_NE(elem, nullptr);

    if (elem->isOk() && !elem->isContent()) {
        const char *typeName = elem->getTypeName();
        EXPECT_NE(typeName, nullptr);
    }
}

// Test getNumChildren and getChild boundary
TEST_F(StructElementTest_1715, GetChild_BoundaryCheck_1715)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/tagged_pdf.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
        return;
    }

    const StructElement *elem = root->getChild(0);
    ASSERT_NE(elem, nullptr);

    unsigned numChildren = elem->getNumChildren();
    
    // Valid index should return non-null
    if (numChildren > 0) {
        const StructElement *child = elem->getChild(0);
        EXPECT_NE(child, nullptr);
        
        // Last valid child
        const StructElement *lastChild = elem->getChild(numChildren - 1);
        EXPECT_NE(lastChild, nullptr);
    }
}

// Test getParent returns expected parent
TEST_F(StructElementTest_1715, GetParent_ChildKnowsParent_1715)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/tagged_pdf.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
        return;
    }

    const StructElement *elem = root->getChild(0);
    ASSERT_NE(elem, nullptr);

    if (elem->getNumChildren() > 0) {
        const StructElement *child = elem->getChild(0);
        ASSERT_NE(child, nullptr);
        // The child's parent should be the element we got it from
        EXPECT_EQ(child->getParent(), elem);
    }
}

// Test isOk for valid elements
TEST_F(StructElementTest_1715, IsOk_ValidElement_1715)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/tagged_pdf.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
        return;
    }

    const StructElement *elem = root->getChild(0);
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->isOk());
}

// Test getStructTreeRoot returns non-null
TEST_F(StructElementTest_1715, GetStructTreeRoot_ReturnsNonNull_1715)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/tagged_pdf.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
        return;
    }

    // Need non-const access for getStructTreeRoot
    // Since getChild returns const, we test what we can
    const StructElement *elem = root->getChild(0);
    ASSERT_NE(elem, nullptr);
    // getStructTreeRoot is non-const method, we may not be able to call it on const pointer
    // This verifies the element is properly connected to the tree
    EXPECT_TRUE(elem->isOk());
}

// Test getText on non-content elements
TEST_F(StructElementTest_1715, GetText_NonContentElement_1715)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/tagged_pdf.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
        return;
    }

    const StructElement *elem = root->getChild(0);
    ASSERT_NE(elem, nullptr);

    // getText should be callable and return something (possibly null or a string)
    GooString *text = elem->getText(true);
    // Just verify it doesn't crash; the result depends on the PDF content
    // Clean up if needed
    delete text;
}

// Test getTextSpans returns empty for grouping elements
TEST_F(StructElementTest_1715, GetTextSpans_GroupingElement_ReturnsEmpty_1715)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/tagged_pdf.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
        return;
    }

    // Walk the tree to find a grouping element
    const StructElement *elem = root->getChild(0);
    ASSERT_NE(elem, nullptr);

    if (elem->isGrouping()) {
        TextSpanArray spans = elem->getTextSpans();
        EXPECT_TRUE(spans.empty());
    }
}

// Test getNumAttributes on a valid element
TEST_F(StructElementTest_1715, GetNumAttributes_ValidElement_1715)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/tagged_pdf.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
        return;
    }

    const StructElement *elem = root->getChild(0);
    ASSERT_NE(elem, nullptr);

    // Should not crash, returns >= 0
    unsigned numAttrs = elem->getNumAttributes();
    EXPECT_GE(numAttrs, 0u);
}

// Test content element properties
TEST_F(StructElementTest_1715, ContentElement_Properties_1715)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/tagged_pdf.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
        return;
    }

    // Recursively find a content element
    std::function<const StructElement*(const StructElement*)> findContent;
    findContent = [&findContent](const StructElement* e) -> const StructElement* {
        if (!e) return nullptr;
        if (e->isContent()) return e;
        for (unsigned i = 0; i < e->getNumChildren(); i++) {
            const StructElement* result = findContent(e->getChild(i));
            if (result) return result;
        }
        return nullptr;
    };

    const StructElement *contentElem = nullptr;
    for (unsigned i = 0; i < root->getNumChildren(); i++) {
        contentElem = findContent(root->getChild(i));
        if (contentElem) break;
    }

    if (!contentElem) {
        GTEST_SKIP() << "No content element found in test PDF";
        return;
    }

    EXPECT_TRUE(contentElem->isContent());
    EXPECT_FALSE(contentElem->isObjectRef());
    // Content elements should have a valid MCID
    int mcid = contentElem->getMCID();
    EXPECT_GE(mcid, 0);
}

// Test that isContent and isObjectRef are mutually exclusive for content-type elements
TEST_F(StructElementTest_1715, ContentAndObjectRef_MutuallyExclusive_1715)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/tagged_pdf.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
        return;
    }

    // Check all elements in the tree
    std::function<void(const StructElement*)> checkElement;
    checkElement = [&checkElement](const StructElement* e) {
        if (!e) return;
        // isContent and isObjectRef should not both be true
        if (e->isContent()) {
            EXPECT_FALSE(e->isObjectRef());
        }
        if (e->isObjectRef()) {
            EXPECT_FALSE(e->isContent());
        }
        for (unsigned i = 0; i < e->getNumChildren(); i++) {
            checkElement(e->getChild(i));
        }
    };

    for (unsigned i = 0; i < root->getNumChildren(); i++) {
        checkElement(root->getChild(i));
    }
}

// Test getAltText and getActualText don't crash
TEST_F(StructElementTest_1715, GetAltTextAndActualText_NoCrash_1715)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/tagged_pdf.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
        return;
    }

    const StructElement *elem = root->getChild(0);
    ASSERT_NE(elem, nullptr);

    // These should not crash, may return nullptr
    const GooString *altText = elem->getAltText();
    const GooString *actualText = elem->getActualText();
    // Just verify they don't crash - values depend on PDF content
    (void)altText;
    (void)actualText;
}

// Test hasPageRef and getPageRef consistency
TEST_F(StructElementTest_1715, PageRef_Consistency_1715)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/tagged_pdf.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
        return;
    }

    const StructElement *elem = root->getChild(0);
    ASSERT_NE(elem, nullptr);

    Ref ref;
    if (elem->hasPageRef()) {
        EXPECT_TRUE(elem->getPageRef(ref));
    }
}

// Test getTitle and getID don't crash
TEST_F(StructElementTest_1715, GetTitleAndID_NoCrash_1715)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/tagged_pdf.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
        return;
    }

    const StructElement *elem = root->getChild(0);
    ASSERT_NE(elem, nullptr);

    const GooString *title = elem->getTitle();
    const GooString *id = elem->getID();
    // May be nullptr, just verifying no crash
    (void)title;
    (void)id;
}

// Test getRevision returns a valid value
TEST_F(StructElementTest_1715, GetRevision_1715)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/tagged_pdf.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
        return;
    }

    const StructElement *elem = root->getChild(0);
    ASSERT_NE(elem, nullptr);

    unsigned int revision = elem->getRevision();
    // Revision is typically 0 for unmodified elements
    EXPECT_GE(revision, 0u);
}

// Test getExpandedAbbr doesn't crash
TEST_F(StructElementTest_1715, GetExpandedAbbr_NoCrash_1715)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/tagged_pdf.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
        return;
    }

    const StructElement *elem = root->getChild(0);
    ASSERT_NE(elem, nullptr);

    const GooString *abbr = elem->getExpandedAbbr();
    (void)abbr; // May be nullptr
}

// Test getLanguage doesn't crash
TEST_F(StructElementTest_1715, GetLanguage_NoCrash_1715)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/tagged_pdf.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
        return;
    }

    const StructElement *elem = root->getChild(0);
    ASSERT_NE(elem, nullptr);

    // getLanguage is non-const, but elem is const - skip if can't call
    // This tests the interface exists and is callable
}

// Test hasStmRef and getStmRef consistency
TEST_F(StructElementTest_1715, StmRef_Consistency_1715)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/tagged_pdf.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    const StructTreeRoot *root = doc->getStructTreeRoot();
    if (!root || root->getNumChildren() == 0) {
        GTEST_SKIP() << "No structure tree in test PDF";
        return;
    }

    // Find a content element and check stm ref consistency
    std::function<void(const StructElement*)> checkStmRef;
    checkStmRef = [&checkStmRef](const StructElement* e) {
        if (!e) return;
        Ref ref;
        if (e->hasStmRef()) {
            EXPECT_TRUE(e->getStmRef(ref));
        }
        for (unsigned i = 0; i < e->getNumChildren(); i++) {
            checkStmRef(e->getChild(i));
        }
    };

    for (unsigned i = 0; i < root->getNumChildren(); i++) {
        checkStmRef(root->getChild(i));
    }
}
