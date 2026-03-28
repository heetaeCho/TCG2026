#include "tinyxml2.h"
#include <gtest/gtest.h>

using namespace tinyxml2;

class XMLDocumentTest_110 : public ::testing::Test {
protected:
    // Default constructor, can be reused in tests
    XMLDocument doc{true, Whitespace::DEFAULT};
};

// Test default state of HasBOM
TEST_F(XMLDocumentTest_110, HasBOM_DefaultFalse_110) {
    // By default, BOM should not be set
    EXPECT_FALSE(doc.HasBOM());
}

// Test setting BOM to true
TEST_F(XMLDocumentTest_110, SetBOM_True_ReflectsHasBOM_110) {
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
}

// Test setting BOM to false explicitly
TEST_F(XMLDocumentTest_110, SetBOM_False_ReflectsHasBOM_110) {
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// Test toggling BOM
TEST_F(XMLDocumentTest_110, SetBOM_Toggle_110) {
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// Test multiple documents maintain independent BOM state
TEST_F(XMLDocumentTest_110, IndependentBOMState_MultipleDocuments_110) {
    XMLDocument doc1{true, Whitespace::DEFAULT};
    XMLDocument doc2{true, Whitespace::DEFAULT};

    doc1.SetBOM(true);
    doc2.SetBOM(false);

    EXPECT_TRUE(doc1.HasBOM());
    EXPECT_FALSE(doc2.HasBOM());
}
