// File: ./TestProjects/tinyxml2/tests/xmlprinter_compactmode_151_test.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLPrinterCompactModeTest_151 : public ::testing::Test {
protected:
    static XMLElement* ParseAndRoot(XMLDocument& doc, const char* xml) {
        const XMLError err = doc.Parse(xml);
        EXPECT_EQ(err, XML_SUCCESS) << "Failed to parse XML for test setup";
        XMLElement* root = doc.RootElement();
        EXPECT_NE(root, nullptr) << "RootElement() returned nullptr for test setup";
        return root;
    }
};

TEST_F(XMLPrinterCompactModeTest_151, ReturnsFalseByDefault_151) {
    XMLDocument doc;
    XMLElement* root = ParseAndRoot(doc, "<root/>");

    XMLPrinter printer; // default construction

    EXPECT_FALSE(printer.CompactMode(*root));
}

TEST_F(XMLPrinterCompactModeTest_151, ReturnsTrueWhenConstructedCompactTrue_151) {
    XMLDocument doc;
    XMLElement* root = ParseAndRoot(doc, "<root/>");

    XMLPrinter printer(/*file*/ nullptr, /*compact*/ true);

    EXPECT_TRUE(printer.CompactMode(*root));
}

TEST_F(XMLPrinterCompactModeTest_151, ReturnsFalseWhenConstructedCompactFalse_151) {
    XMLDocument doc;
    XMLElement* root = ParseAndRoot(doc, "<root/>");

    XMLPrinter printer(/*file*/ nullptr, /*compact*/ false);

    EXPECT_FALSE(printer.CompactMode(*root));
}

TEST_F(XMLPrinterCompactModeTest_151, CompactModeIsConsistentAcrossElementsInSameDocument_151) {
    XMLDocument doc;
    XMLElement* a = ParseAndRoot(doc, "<a><b/><c/></a>");
    XMLElement* b = a->FirstChildElement("b");
    XMLElement* c = a->FirstChildElement("c");
    ASSERT_NE(b, nullptr);
    ASSERT_NE(c, nullptr);

    XMLPrinter printerTrue(/*file*/ nullptr, /*compact*/ true);
    EXPECT_TRUE(printerTrue.CompactMode(*a));
    EXPECT_TRUE(printerTrue.CompactMode(*b));
    EXPECT_TRUE(printerTrue.CompactMode(*c));

    XMLPrinter printerFalse(/*file*/ nullptr, /*compact*/ false);
    EXPECT_FALSE(printerFalse.CompactMode(*a));
    EXPECT_FALSE(printerFalse.CompactMode(*b));
    EXPECT_FALSE(printerFalse.CompactMode(*c));
}

TEST_F(XMLPrinterCompactModeTest_151, DoesNotThrowForElementsFromDifferentDocuments_151) {
    XMLDocument doc1;
    XMLDocument doc2;
    XMLElement* r1 = ParseAndRoot(doc1, "<r1><child/></r1>");
    XMLElement* r2 = ParseAndRoot(doc2, "<r2/>");

    XMLPrinter printer(/*file*/ nullptr, /*compact*/ true);

    EXPECT_NO_THROW({
        (void)printer.CompactMode(*r1);
        (void)printer.CompactMode(*r2);
    });

    // Also verify observable behavior remains stable across documents.
    EXPECT_TRUE(printer.CompactMode(*r1));
    EXPECT_TRUE(printer.CompactMode(*r2));
}

} // namespace
