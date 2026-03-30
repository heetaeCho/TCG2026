#include "tinyxml2.h"
#include <gtest/gtest.h>

using namespace tinyxml2;

// Test fixture for XMLDocument
class XMLDocumentTest_109 : public ::testing::Test {
protected:
    // We can initialize documents with different whitespace modes
    XMLDocument docDefault{true, Whitespace::PRESERVE};
    XMLDocument docTrim{false, Whitespace::COLLAPSE};
};

// Test that the WhitespaceMode returns the correct mode set in constructor
TEST_F(XMLDocumentTest_109, WhitespaceModePreserve_109) {
    EXPECT_EQ(docDefault.WhitespaceMode(), Whitespace::PRESERVE);
}

TEST_F(XMLDocumentTest_109, WhitespaceModeCollapse_109) {
    EXPECT_EQ(docTrim.WhitespaceMode(), Whitespace::COLLAPSE);
}

// Test that multiple instances maintain independent whitespace modes
TEST_F(XMLDocumentTest_109, MultipleInstancesIndependent_109) {
    XMLDocument doc1{true, Whitespace::PRESERVE};
    XMLDocument doc2{false, Whitespace::COLLAPSE};
    EXPECT_EQ(doc1.WhitespaceMode(), Whitespace::PRESERVE);
    EXPECT_EQ(doc2.WhitespaceMode(), Whitespace::COLLAPSE);
}

// Boundary check: using an invalid enum value (if any, hypothetical)
TEST_F(XMLDocumentTest_109, InvalidWhitespaceModeBehavior_109) {
    // Assuming the constructor can technically accept an int casted to Whitespace
    XMLDocument docInvalid{true, static_cast<Whitespace>(999)};
    EXPECT_EQ(docInvalid.WhitespaceMode(), static_cast<Whitespace>(999));
}
