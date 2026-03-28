#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// TEST_ID: 111
class XMLDocumentTest_111 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a fresh document for each test
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Normal operation: Setting BOM to true should make HasBOM() return true
TEST_F(XMLDocumentTest_111, SetBOMTrue_111) {
    doc->SetBOM(true);
    EXPECT_TRUE(doc->HasBOM());
}

// Normal operation: Setting BOM to false should make HasBOM() return false
TEST_F(XMLDocumentTest_111, SetBOMFalse_111) {
    doc->SetBOM(false);
    EXPECT_FALSE(doc->HasBOM());
}

// Boundary / idempotence: Setting BOM to true twice should still return true
TEST_F(XMLDocumentTest_111, SetBOMTrueTwice_111) {
    doc->SetBOM(true);
    doc->SetBOM(true);
    EXPECT_TRUE(doc->HasBOM());
}

// Boundary / idempotence: Setting BOM to false twice should still return false
TEST_F(XMLDocumentTest_111, SetBOMFalseTwice_111) {
    doc->SetBOM(false);
    doc->SetBOM(false);
    EXPECT_FALSE(doc->HasBOM());
}

// Switching BOM from false to true
TEST_F(XMLDocumentTest_111, ToggleBOMFalseToTrue_111) {
    doc->SetBOM(false);
    EXPECT_FALSE(doc->HasBOM());
    doc->SetBOM(true);
    EXPECT_TRUE(doc->HasBOM());
}

// Switching BOM from true to false
TEST_F(XMLDocumentTest_111, ToggleBOMTrueToFalse_111) {
    doc->SetBOM(true);
    EXPECT_TRUE(doc->HasBOM());
    doc->SetBOM(false);
    EXPECT_FALSE(doc->HasBOM());
}
