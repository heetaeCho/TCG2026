// File: ./TestProjects/tinyxml2/tests/XMLDeclaration_ParseDeep_test_201.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLDeclarationParseDeepTest_201 : public ::testing::Test {
protected:
    static const XMLDeclaration* FirstDeclaration(const XMLDocument& doc) {
        const XMLNode* n = doc.FirstChild();
        while (n) {
            if (n->ToDeclaration()) {
                return n->ToDeclaration();
            }
            n = n->NextSibling();
        }
        return nullptr;
    }
};

}  // namespace

TEST_F(XMLDeclarationParseDeepTest_201, ParsesValidDeclarationAndCreatesDeclarationNode_201) {
    XMLDocument doc;
    const char* xml = "<?xml version=\"1.0\"?>\n<root/>";

    doc.Parse(xml);

    ASSERT_FALSE(doc.Error()) << "Parse should succeed for a valid XML declaration.";
    const XMLDeclaration* decl = FirstDeclaration(doc);
    ASSERT_NE(decl, nullptr) << "A declaration node should be present as a child of the document.";

    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr) << "Root element should be parsed after the declaration.";
}

TEST_F(XMLDeclarationParseDeepTest_201, MissingDeclarationTerminatorSetsParsingDeclarationError_201) {
    XMLDocument doc;
    // Missing "?>"
    const char* xml = "<?xml version=\"1.0\"\n<root/>";

    doc.Parse(xml);

    ASSERT_TRUE(doc.Error()) << "Parse should fail when the declaration is not terminated with '?>'.";
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_PARSING_DECLARATION)
        << "ErrorID should indicate a declaration parsing error for an unterminated declaration.";
}

TEST_F(XMLDeclarationParseDeepTest_201, MinimalDeclarationWithTerminatorParses_201) {
    XMLDocument doc;
    // Minimal-but-terminated declaration; behavior should be observable via overall parse success.
    const char* xml = "<?xml?>\n<root/>";

    doc.Parse(xml);

    ASSERT_FALSE(doc.Error()) << "Parse should succeed for a terminated declaration.";
    const XMLDeclaration* decl = FirstDeclaration(doc);
    EXPECT_NE(decl, nullptr) << "Declaration node should be present for a terminated declaration.";
    EXPECT_NE(doc.FirstChildElement("root"), nullptr) << "Root element should still parse.";
}

TEST_F(XMLDeclarationParseDeepTest_201, DeclarationNewlinesAdvanceLineNumbersForFollowingElements_201) {
    XMLDocument doc;
    // Declaration spans two lines; root should start on line 3.
    const char* xml =
        "<?xml version=\"1.0\"\n"
        "encoding=\"UTF-8\"?>\n"
        "<root/>\n";

    doc.Parse(xml);

    ASSERT_FALSE(doc.Error()) << "Parse should succeed for a multi-line declaration with terminator.";
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    // Observable outcome of ParseDeep's newline handling: following node line numbers.
    EXPECT_EQ(root->GetLineNum(), 3);
}

TEST_F(XMLDeclarationParseDeepTest_201, GarbageAfterDeclarationWithoutProperCloseReportsDeclarationError_201) {
    XMLDocument doc;
    // Starts like a declaration but never closes properly (no "?>").
    const char* xml = "<?xml version=\"1.0\" garbage\n<root/>";

    doc.Parse(xml);

    ASSERT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_PARSING_DECLARATION);
}
