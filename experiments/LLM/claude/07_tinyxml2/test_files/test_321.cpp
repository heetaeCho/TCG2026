#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLPrinter Visit(XMLDeclaration) tests
class XMLPrinterVisitDeclarationTest_321 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that Visit(XMLDeclaration) returns true
TEST_F(XMLPrinterVisitDeclarationTest_321, VisitDeclarationReturnsTrue_321) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>");
    
    XMLPrinter printer(nullptr, false);
    
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    bool result = printer.Visit(*decl);
    EXPECT_TRUE(result);
}

// Test that Visit(XMLDeclaration) produces the correct output with standard declaration
TEST_F(XMLPrinterVisitDeclarationTest_321, VisitDeclarationProducesCorrectOutput_321) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>");
    
    XMLPrinter printer(nullptr, false);
    
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    printer.Visit(*decl);
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    // The output should contain the declaration
    EXPECT_NE(std::string(output).find("xml"), std::string::npos);
    EXPECT_NE(std::string(output).find("version"), std::string::npos);
}

// Test that Visit(XMLDeclaration) works with minimal declaration
TEST_F(XMLPrinterVisitDeclarationTest_321, VisitMinimalDeclaration_321) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    
    XMLPrinter printer(nullptr, false);
    
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    bool result = printer.Visit(*decl);
    EXPECT_TRUE(result);
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("version"), std::string::npos);
}

// Test that Visit(XMLDeclaration) in compact mode
TEST_F(XMLPrinterVisitDeclarationTest_321, VisitDeclarationCompactMode_321) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    
    XMLPrinter printer(nullptr, true);  // compact mode
    
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    bool result = printer.Visit(*decl);
    EXPECT_TRUE(result);
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_GT(printer.CStrSize(), (size_t)0);
}

// Test that PushDeclaration directly produces expected output
TEST_F(XMLPrinterVisitDeclarationTest_321, PushDeclarationDirectly_321) {
    XMLPrinter printer(nullptr, false);
    
    printer.PushDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    EXPECT_NE(outputStr.find("<?"), std::string::npos);
    EXPECT_NE(outputStr.find("?>"), std::string::npos);
    EXPECT_NE(outputStr.find("xml version"), std::string::npos);
}

// Test that Visit(XMLDeclaration) output matches PushDeclaration output
TEST_F(XMLPrinterVisitDeclarationTest_321, VisitMatchesPushDeclaration_321) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    // Use Visit
    XMLPrinter printer1(nullptr, false);
    printer1.Visit(*decl);
    std::string visitOutput(printer1.CStr());
    
    // Use PushDeclaration with the same value
    XMLPrinter printer2(nullptr, false);
    printer2.PushDeclaration(decl->Value());
    std::string pushOutput(printer2.CStr());
    
    EXPECT_EQ(visitOutput, pushOutput);
}

// Test Visit with a declaration that has multiple attributes
TEST_F(XMLPrinterVisitDeclarationTest_321, VisitDeclarationWithMultipleAttributes_321) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?><root/>");
    
    XMLPrinter printer(nullptr, false);
    
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    bool result = printer.Visit(*decl);
    EXPECT_TRUE(result);
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    EXPECT_NE(outputStr.find("encoding"), std::string::npos);
    EXPECT_NE(outputStr.find("standalone"), std::string::npos);
}

// Test ClearBuffer after Visit
TEST_F(XMLPrinterVisitDeclarationTest_321, ClearBufferAfterVisit_321) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    
    XMLPrinter printer(nullptr, false);
    
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    printer.Visit(*decl);
    EXPECT_GT(printer.CStrSize(), (size_t)1);
    
    printer.ClearBuffer();
    // After clearing, the buffer should be minimal (just null terminator or empty)
    EXPECT_LE(printer.CStrSize(), (size_t)1);
}

// Test multiple declarations visited sequentially
TEST_F(XMLPrinterVisitDeclarationTest_321, MultipleDeclarationsVisited_321) {
    XMLDocument doc1;
    doc1.Parse("<?xml version=\"1.0\"?><root/>");
    
    XMLDocument doc2;
    doc2.Parse("<?xml version=\"1.1\"?><root/>");
    
    XMLPrinter printer(nullptr, false);
    
    const XMLDeclaration* decl1 = doc1.FirstChild()->ToDeclaration();
    const XMLDeclaration* decl2 = doc2.FirstChild()->ToDeclaration();
    ASSERT_NE(decl1, nullptr);
    ASSERT_NE(decl2, nullptr);
    
    bool result1 = printer.Visit(*decl1);
    bool result2 = printer.Visit(*decl2);
    
    EXPECT_TRUE(result1);
    EXPECT_TRUE(result2);
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    // Both declarations should appear in the output
    std::string outputStr(output);
    EXPECT_NE(outputStr.find("1.0"), std::string::npos);
    EXPECT_NE(outputStr.find("1.1"), std::string::npos);
}

// Test that Accept on a declaration invokes Visit on the printer
TEST_F(XMLPrinterVisitDeclarationTest_321, AcceptCallsVisitOnPrinter_321) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>");
    
    XMLPrinter printer(nullptr, false);
    
    const XMLNode* decl = doc.FirstChild();
    ASSERT_NE(decl, nullptr);
    ASSERT_NE(decl->ToDeclaration(), nullptr);
    
    bool result = decl->Accept(&printer);
    EXPECT_TRUE(result);
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    EXPECT_NE(outputStr.find("xml"), std::string::npos);
}

// Test full document round-trip through printer preserves declaration
TEST_F(XMLPrinterVisitDeclarationTest_321, FullDocumentRoundTrip_321) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<root><child/></root>";
    
    XMLDocument doc;
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    
    XMLPrinter printer(nullptr, false);
    doc.Accept(&printer);
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    
    // Declaration should be present
    EXPECT_NE(outputStr.find("<?xml"), std::string::npos);
    EXPECT_NE(outputStr.find("?>"), std::string::npos);
    // Elements should be present too
    EXPECT_NE(outputStr.find("<root>"), std::string::npos);
    EXPECT_NE(outputStr.find("<child/>"), std::string::npos);
}

// Test PushDeclaration with empty string
TEST_F(XMLPrinterVisitDeclarationTest_321, PushDeclarationEmptyString_321) {
    XMLPrinter printer(nullptr, false);
    
    printer.PushDeclaration("");
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    // Should still have the declaration markers
    EXPECT_NE(outputStr.find("<?"), std::string::npos);
    EXPECT_NE(outputStr.find("?>"), std::string::npos);
}

// Test CStrSize is reasonable after Visit
TEST_F(XMLPrinterVisitDeclarationTest_321, CStrSizeAfterVisit_321) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    
    XMLPrinter printer(nullptr, false);
    
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    printer.Visit(*decl);
    
    size_t size = printer.CStrSize();
    const char* output = printer.CStr();
    // CStrSize should include the null terminator
    EXPECT_EQ(size, strlen(output) + 1);
}
