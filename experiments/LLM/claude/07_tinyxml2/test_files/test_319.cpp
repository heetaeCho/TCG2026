#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// ============================================================
// Test Fixture
// ============================================================
class XMLPrinterVisitTextTest_319 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }
    void TearDown() override {
        delete doc;
    }
    XMLDocument* doc;
};

// ------------------------------------------------------------
// Normal operation: Visit XMLText node with plain text
// ------------------------------------------------------------
TEST_F(XMLPrinterVisitTextTest_319, VisitPlainText_ReturnsTrue_319) {
    doc->Parse("<root>Hello World</root>");
    ASSERT_FALSE(doc->Error());

    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLText* textNode = root->FirstChild()->ToText();
    ASSERT_NE(textNode, nullptr);

    XMLPrinter printer(nullptr, true);
    bool result = printer.Visit(*textNode);
    EXPECT_TRUE(result);
}

TEST_F(XMLPrinterVisitTextTest_319, VisitPlainText_OutputContainsText_319) {
    doc->Parse("<root>Hello World</root>");
    ASSERT_FALSE(doc->Error());

    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLText* textNode = root->FirstChild()->ToText();
    ASSERT_NE(textNode, nullptr);

    XMLPrinter printer(nullptr, true);
    printer.Visit(*textNode);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_STRNE(output, "");
    EXPECT_NE(std::string(output).find("Hello World"), std::string::npos);
}

// ------------------------------------------------------------
// Normal operation: Visit XMLText node with CDATA
// ------------------------------------------------------------
TEST_F(XMLPrinterVisitTextTest_319, VisitCDataText_ReturnsTrue_319) {
    doc->Parse("<root><![CDATA[Some <CDATA> content]]></root>");
    ASSERT_FALSE(doc->Error());

    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLText* textNode = root->FirstChild()->ToText();
    ASSERT_NE(textNode, nullptr);
    EXPECT_TRUE(textNode->CData());

    XMLPrinter printer(nullptr, true);
    bool result = printer.Visit(*textNode);
    EXPECT_TRUE(result);
}

TEST_F(XMLPrinterVisitTextTest_319, VisitCDataText_OutputContainsCData_319) {
    doc->Parse("<root><![CDATA[Some <CDATA> content]]></root>");
    ASSERT_FALSE(doc->Error());

    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLText* textNode = root->FirstChild()->ToText();
    ASSERT_NE(textNode, nullptr);

    XMLPrinter printer(nullptr, true);
    printer.Visit(*textNode);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    // CDATA sections should be wrapped in <![CDATA[ ... ]]>
    EXPECT_NE(std::string(output).find("<![CDATA["), std::string::npos);
    EXPECT_NE(std::string(output).find("]]>"), std::string::npos);
    EXPECT_NE(std::string(output).find("Some <CDATA> content"), std::string::npos);
}

// ------------------------------------------------------------
// Boundary: Empty text node
// ------------------------------------------------------------
TEST_F(XMLPrinterVisitTextTest_319, VisitEmptyText_ReturnsTrue_319) {
    doc->Parse("<root></root>");
    ASSERT_FALSE(doc->Error());

    // Manually create a text node with empty content
    XMLText* textNode = doc->NewText("");
    ASSERT_NE(textNode, nullptr);

    XMLPrinter printer(nullptr, true);
    bool result = printer.Visit(*textNode);
    EXPECT_TRUE(result);
}

// ------------------------------------------------------------
// Normal: Text with special XML characters (entities)
// ------------------------------------------------------------
TEST_F(XMLPrinterVisitTextTest_319, VisitTextWithEntities_OutputEscapesEntities_319) {
    doc->Parse("<root>a &amp; b &lt; c</root>");
    ASSERT_FALSE(doc->Error());

    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLText* textNode = root->FirstChild()->ToText();
    ASSERT_NE(textNode, nullptr);

    XMLPrinter printer(nullptr, true);
    printer.Visit(*textNode);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    // The printer should output escaped entities
    std::string str(output);
    EXPECT_NE(str.find("&amp;"), std::string::npos);
    EXPECT_NE(str.find("&lt;"), std::string::npos);
}

// ------------------------------------------------------------
// Normal: Non-compact mode printer visiting text
// ------------------------------------------------------------
TEST_F(XMLPrinterVisitTextTest_319, VisitTextNonCompactMode_ReturnsTrue_319) {
    doc->Parse("<root>Some text</root>");
    ASSERT_FALSE(doc->Error());

    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLText* textNode = root->FirstChild()->ToText();
    ASSERT_NE(textNode, nullptr);

    XMLPrinter printer(nullptr, false);
    bool result = printer.Visit(*textNode);
    EXPECT_TRUE(result);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("Some text"), std::string::npos);
}

// ------------------------------------------------------------
// Normal: Full document round-trip through Accept with printer
// ------------------------------------------------------------
TEST_F(XMLPrinterVisitTextTest_319, AcceptVisitText_ProducesCorrectOutput_319) {
    const char* xml = "<root>Hello</root>";
    doc->Parse(xml);
    ASSERT_FALSE(doc->Error());

    XMLPrinter printer(nullptr, true);
    doc->Accept(&printer);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("Hello"), std::string::npos);
    EXPECT_NE(std::string(output).find("<root>"), std::string::npos);
    EXPECT_NE(std::string(output).find("</root>"), std::string::npos);
}

// ------------------------------------------------------------
// Boundary: Text node with only whitespace
// ------------------------------------------------------------
TEST_F(XMLPrinterVisitTextTest_319, VisitWhitespaceOnlyText_ReturnsTrue_319) {
    // Need to preserve whitespace
    XMLText* textNode = doc->NewText("   ");
    ASSERT_NE(textNode, nullptr);

    XMLPrinter printer(nullptr, true);
    bool result = printer.Visit(*textNode);
    EXPECT_TRUE(result);
}

// ------------------------------------------------------------
// Normal: CDATA text that is not CDATA (SetCData false)
// ------------------------------------------------------------
TEST_F(XMLPrinterVisitTextTest_319, VisitNonCDataText_NoCDataInOutput_319) {
    XMLText* textNode = doc->NewText("plain text");
    ASSERT_NE(textNode, nullptr);
    textNode->SetCData(false);

    XMLPrinter printer(nullptr, true);
    printer.Visit(*textNode);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string str(output);
    EXPECT_EQ(str.find("<![CDATA["), std::string::npos);
    EXPECT_NE(str.find("plain text"), std::string::npos);
}

// ------------------------------------------------------------
// Normal: Multiple text visits accumulate output
// ------------------------------------------------------------
TEST_F(XMLPrinterVisitTextTest_319, VisitMultipleTexts_AccumulatesOutput_319) {
    XMLText* text1 = doc->NewText("First");
    XMLText* text2 = doc->NewText("Second");
    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);

    XMLPrinter printer(nullptr, true);
    EXPECT_TRUE(printer.Visit(*text1));
    EXPECT_TRUE(printer.Visit(*text2));

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string str(output);
    EXPECT_NE(str.find("First"), std::string::npos);
    EXPECT_NE(str.find("Second"), std::string::npos);
}

// ------------------------------------------------------------
// Boundary: Very long text
// ------------------------------------------------------------
TEST_F(XMLPrinterVisitTextTest_319, VisitLongText_ReturnsTrue_319) {
    std::string longText(10000, 'A');
    XMLText* textNode = doc->NewText(longText.c_str());
    ASSERT_NE(textNode, nullptr);

    XMLPrinter printer(nullptr, true);
    bool result = printer.Visit(*textNode);
    EXPECT_TRUE(result);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find(std::string(100, 'A')), std::string::npos);
}

// ------------------------------------------------------------
// Normal: CStr size is non-zero after visiting text
// ------------------------------------------------------------
TEST_F(XMLPrinterVisitTextTest_319, VisitText_CStrSizeNonZero_319) {
    XMLText* textNode = doc->NewText("test");
    ASSERT_NE(textNode, nullptr);

    XMLPrinter printer(nullptr, true);
    printer.Visit(*textNode);

    EXPECT_GT(printer.CStrSize(), static_cast<size_t>(0));
}

// ------------------------------------------------------------
// Boundary: ClearBuffer then visit again
// ------------------------------------------------------------
TEST_F(XMLPrinterVisitTextTest_319, ClearBufferThenVisitAgain_319) {
    XMLText* textNode = doc->NewText("data");
    ASSERT_NE(textNode, nullptr);

    XMLPrinter printer(nullptr, true);
    printer.Visit(*textNode);

    const char* output1 = printer.CStr();
    ASSERT_NE(output1, nullptr);
    EXPECT_NE(std::string(output1).find("data"), std::string::npos);

    printer.ClearBuffer();

    XMLText* textNode2 = doc->NewText("newdata");
    printer.Visit(*textNode2);

    const char* output2 = printer.CStr();
    ASSERT_NE(output2, nullptr);
    EXPECT_NE(std::string(output2).find("newdata"), std::string::npos);
}
