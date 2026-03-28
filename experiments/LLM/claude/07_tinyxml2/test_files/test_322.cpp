#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLPrinter Visit(XMLUnknown) tests
class XMLPrinterVisitUnknownTest_322 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that Visit(XMLUnknown) returns true
TEST_F(XMLPrinterVisitUnknownTest_322, VisitUnknownReturnsTrue_322) {
    XMLDocument doc;
    // Parse a document containing an unknown node
    doc.Parse("<!UNKNOWN some unknown content>");
    
    // We can also create unknown via the document parsing
    XMLDocument doc2;
    const char* xml = "<root><!UNKNOWN test></root>";
    // Unknown nodes are created by the parser for <! ... > constructs that aren't comments or declarations
    // Let's use a simpler approach
    doc2.Parse("<?xml version=\"1.0\"?><root/>");
    
    XMLPrinter printer(nullptr, false);
    
    // Create an unknown node by parsing XML with unknown markup
    XMLDocument doc3;
    // In tinyxml2, unknown nodes are parsed from <!...> that don't match comment or declaration
    const char* xmlWithUnknown = "<root/>";
    doc3.Parse(xmlWithUnknown);
    
    // Use the printer's Visit method through Accept
    // First, let's directly test using a document with unknown content
    XMLDocument doc4;
    doc4.Parse("<!DOCTYPE html>");
    
    // The DOCTYPE should be parsed as an XMLUnknown node
    const XMLNode* child = doc4.FirstChild();
    ASSERT_NE(child, nullptr);
    
    const XMLUnknown* unknown = child->ToUnknown();
    if (unknown != nullptr) {
        XMLPrinter printer2(nullptr, false);
        bool result = printer2.Visit(*unknown);
        EXPECT_TRUE(result);
    }
}

// Test that Visit(XMLUnknown) outputs the unknown content correctly
TEST_F(XMLPrinterVisitUnknownTest_322, VisitUnknownOutputsCorrectContent_322) {
    XMLDocument doc;
    doc.Parse("<!DOCTYPE html>");
    
    const XMLNode* child = doc.FirstChild();
    ASSERT_NE(child, nullptr);
    
    const XMLUnknown* unknown = child->ToUnknown();
    ASSERT_NE(unknown, nullptr);
    
    XMLPrinter printer(nullptr, false);
    bool result = printer.Visit(*unknown);
    EXPECT_TRUE(result);
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    // The output should contain the unknown content wrapped in <! ... >
    EXPECT_STRNE(output, "");
    // Check that the output contains "DOCTYPE html"
    std::string outputStr(output);
    EXPECT_NE(outputStr.find("DOCTYPE html"), std::string::npos);
}

// Test that Visit(XMLUnknown) via Accept produces correct output
TEST_F(XMLPrinterVisitUnknownTest_322, AcceptOnUnknownCallsVisit_322) {
    XMLDocument doc;
    doc.Parse("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\">");
    
    const XMLNode* child = doc.FirstChild();
    ASSERT_NE(child, nullptr);
    
    const XMLUnknown* unknown = child->ToUnknown();
    ASSERT_NE(unknown, nullptr);
    
    XMLPrinter printer(nullptr, false);
    unknown->Accept(&printer);
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    EXPECT_NE(outputStr.find("DOCTYPE"), std::string::npos);
}

// Test that Visit(XMLUnknown) works with compact mode printer
TEST_F(XMLPrinterVisitUnknownTest_322, VisitUnknownCompactMode_322) {
    XMLDocument doc;
    doc.Parse("<!DOCTYPE html>");
    
    const XMLNode* child = doc.FirstChild();
    ASSERT_NE(child, nullptr);
    
    const XMLUnknown* unknown = child->ToUnknown();
    ASSERT_NE(unknown, nullptr);
    
    XMLPrinter printer(nullptr, true); // compact mode
    bool result = printer.Visit(*unknown);
    EXPECT_TRUE(result);
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    EXPECT_NE(outputStr.find("DOCTYPE html"), std::string::npos);
}

// Test Visit(XMLUnknown) with minimal unknown content
TEST_F(XMLPrinterVisitUnknownTest_322, VisitUnknownMinimalContent_322) {
    XMLDocument doc;
    doc.Parse("<!X>");
    
    const XMLNode* child = doc.FirstChild();
    ASSERT_NE(child, nullptr);
    
    const XMLUnknown* unknown = child->ToUnknown();
    if (unknown != nullptr) {
        XMLPrinter printer(nullptr, false);
        bool result = printer.Visit(*unknown);
        EXPECT_TRUE(result);
        
        const char* output = printer.CStr();
        ASSERT_NE(output, nullptr);
        EXPECT_STRNE(output, "");
    }
}

// Test that PushUnknown directly produces correct output
TEST_F(XMLPrinterVisitUnknownTest_322, PushUnknownDirectly_322) {
    XMLPrinter printer(nullptr, false);
    printer.PushUnknown("DOCTYPE html");
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    // Should produce something like <!DOCTYPE html>
    EXPECT_NE(outputStr.find("<!DOCTYPE html>"), std::string::npos);
}

// Test that PushUnknown with empty string works
TEST_F(XMLPrinterVisitUnknownTest_322, PushUnknownEmptyString_322) {
    XMLPrinter printer(nullptr, false);
    printer.PushUnknown("");
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    // Should still produce <! and >
    EXPECT_NE(outputStr.find("<!"), std::string::npos);
    EXPECT_NE(outputStr.find(">"), std::string::npos);
}

// Test that multiple unknown nodes can be visited sequentially
TEST_F(XMLPrinterVisitUnknownTest_322, MultipleVisitUnknown_322) {
    XMLPrinter printer(nullptr, false);
    printer.PushUnknown("DOCTYPE html");
    printer.PushUnknown("ENTITY foo");
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    EXPECT_NE(outputStr.find("DOCTYPE html"), std::string::npos);
    EXPECT_NE(outputStr.find("ENTITY foo"), std::string::npos);
}

// Test Visit(XMLUnknown) round-trip through document parsing and printing
TEST_F(XMLPrinterVisitUnknownTest_322, RoundTripUnknown_322) {
    const char* originalXml = "<!DOCTYPE html>";
    
    XMLDocument doc;
    doc.Parse(originalXml);
    ASSERT_FALSE(doc.Error());
    
    XMLPrinter printer(nullptr, true);
    doc.Accept(&printer);
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    EXPECT_NE(outputStr.find("DOCTYPE html"), std::string::npos);
}

// Test that CStrSize is non-zero after Visit(XMLUnknown)
TEST_F(XMLPrinterVisitUnknownTest_322, CStrSizeAfterVisitUnknown_322) {
    XMLDocument doc;
    doc.Parse("<!DOCTYPE html>");
    
    const XMLNode* child = doc.FirstChild();
    ASSERT_NE(child, nullptr);
    
    const XMLUnknown* unknown = child->ToUnknown();
    ASSERT_NE(unknown, nullptr);
    
    XMLPrinter printer(nullptr, false);
    printer.Visit(*unknown);
    
    EXPECT_GT(printer.CStrSize(), 0u);
}

// Test that ClearBuffer works after Visit(XMLUnknown)
TEST_F(XMLPrinterVisitUnknownTest_322, ClearBufferAfterVisitUnknown_322) {
    XMLDocument doc;
    doc.Parse("<!DOCTYPE html>");
    
    const XMLNode* child = doc.FirstChild();
    ASSERT_NE(child, nullptr);
    
    const XMLUnknown* unknown = child->ToUnknown();
    ASSERT_NE(unknown, nullptr);
    
    XMLPrinter printer(nullptr, false);
    printer.Visit(*unknown);
    
    EXPECT_GT(printer.CStrSize(), 0u);
    
    printer.ClearBuffer();
    // After clearing, the buffer should be minimal
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    // CStr should return at least an empty null-terminated string
    EXPECT_EQ(std::string(output), "");
}

// Test unknown value content is preserved through Visit
TEST_F(XMLPrinterVisitUnknownTest_322, UnknownValuePreserved_322) {
    XMLDocument doc;
    const char* xml = "<!DOCTYPE note SYSTEM \"note.dtd\">";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    
    const XMLNode* child = doc.FirstChild();
    ASSERT_NE(child, nullptr);
    
    const XMLUnknown* unknown = child->ToUnknown();
    if (unknown != nullptr) {
        // Verify the value
        ASSERT_NE(unknown->Value(), nullptr);
        
        XMLPrinter printer(nullptr, false);
        bool result = printer.Visit(*unknown);
        EXPECT_TRUE(result);
        
        const char* output = printer.CStr();
        ASSERT_NE(output, nullptr);
        std::string outputStr(output);
        // The value of the unknown should be in the output
        EXPECT_NE(outputStr.find(unknown->Value()), std::string::npos);
    }
}
