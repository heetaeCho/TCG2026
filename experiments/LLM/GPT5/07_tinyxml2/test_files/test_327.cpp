// TEST_ID: 327
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLDocumentConstructorTest_327 : public ::testing::Test {};

TEST_F(XMLDocumentConstructorTest_327, ProcessEntitiesReflectsConstructorArgument_327) {
    XMLDocument docTrue(/*processEntities=*/true, PRESERVE_WHITESPACE);
    EXPECT_TRUE(docTrue.ProcessEntities());

    XMLDocument docFalse(/*processEntities=*/false, PRESERVE_WHITESPACE);
    EXPECT_FALSE(docFalse.ProcessEntities());
}

TEST_F(XMLDocumentConstructorTest_327, WhitespaceModeReflectsConstructorArgument_327) {
    XMLDocument docPreserve(/*processEntities=*/true, PRESERVE_WHITESPACE);
    EXPECT_EQ(PRESERVE_WHITESPACE, docPreserve.WhitespaceMode());

    XMLDocument docCollapse(/*processEntities=*/true, COLLAPSE_WHITESPACE);
    EXPECT_EQ(COLLAPSE_WHITESPACE, docCollapse.WhitespaceMode());
}

TEST_F(XMLDocumentConstructorTest_327, DefaultBOMIsDisabledAndCanBeToggled_327) {
    XMLDocument doc(/*processEntities=*/true, PRESERVE_WHITESPACE);

    // Default state should be observable via HasBOM().
    EXPECT_FALSE(doc.HasBOM());

    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());

    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

TEST_F(XMLDocumentConstructorTest_327, DefaultErrorStateIsClear_327) {
    XMLDocument doc(/*processEntities=*/true, PRESERVE_WHITESPACE);

    // These are observable defaults (no parsing done yet).
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());

    // Constructor initializes error line number; ensure it's a stable observable value.
    EXPECT_EQ(0, doc.ErrorLineNum());

    // ErrorName() should be non-null in a valid constructed document.
    EXPECT_NE(nullptr, doc.ErrorName());
}

TEST_F(XMLDocumentConstructorTest_327, ToDocumentAndGetDocumentPointToSelf_327) {
    XMLDocument doc(/*processEntities=*/true, PRESERVE_WHITESPACE);

    // ToDocument() should identify the node as a document.
    EXPECT_EQ(&doc, doc.ToDocument());

    // As a document node, GetDocument() should return itself.
    EXPECT_EQ(&doc, doc.GetDocument());
}

TEST_F(XMLDocumentConstructorTest_327, InstancesAreIndependentForBOMSetting_327) {
    XMLDocument a(/*processEntities=*/true, PRESERVE_WHITESPACE);
    XMLDocument b(/*processEntities=*/true, PRESERVE_WHITESPACE);

    EXPECT_FALSE(a.HasBOM());
    EXPECT_FALSE(b.HasBOM());

    a.SetBOM(true);
    EXPECT_TRUE(a.HasBOM());
    EXPECT_FALSE(b.HasBOM());

    b.SetBOM(true);
    EXPECT_TRUE(a.HasBOM());
    EXPECT_TRUE(b.HasBOM());

    a.SetBOM(false);
    EXPECT_FALSE(a.HasBOM());
    EXPECT_TRUE(b.HasBOM());
}

}  // namespace
