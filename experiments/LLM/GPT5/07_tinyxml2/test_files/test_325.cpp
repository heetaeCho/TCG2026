#include "tinyxml2.h"
#include "gtest/gtest.h"
#include <string>

using namespace tinyxml2;

// TEST FIXTURE
class XMLPrinterHTML5Test_325 : public ::testing::Test {
protected:
    void SetUp() override {
        // No internal state setup required
    }

    void TearDown() override {
        // No cleanup required
    }

    const char* sampleHTML_ = "<html><body><p style='a'></p><br/>&copy;<col a='1' b='2'/><div a='1'></div></body></html>";
};

// Normal operation: Parse document and print with XMLPrinterHTML5
TEST_F(XMLPrinterHTML5Test_325, PrintHTML5DocumentProducesOutput_325) {
    XMLDocument doc(false);
    XMLError err = doc.Parse(sampleHTML_);
    EXPECT_EQ(err, XML_SUCCESS);  // Parsing succeeds

    XMLPrinterHTML5 html5(nullptr, true);
    doc.Print(&html5);

    const char* output = html5.CStr();
    EXPECT_NE(output, nullptr);
    std::string outStr(output);

    // Basic checks on the output
    EXPECT_NE(outStr.find("<html"), std::string::npos);
    EXPECT_NE(outStr.find("<body"), std::string::npos);
    EXPECT_NE(outStr.find("<p"), std::string::npos);
    EXPECT_NE(outStr.find("<br"), std::string::npos);
}

// Boundary condition: Empty document
TEST_F(XMLPrinterHTML5Test_325, PrintEmptyDocumentProducesEmptyOutput_325) {
    XMLDocument doc(false);
    XMLPrinterHTML5 html5(nullptr, true);
    doc.Print(&html5);

    const char* output = html5.CStr();
    EXPECT_NE(output, nullptr);
    std::string outStr(output);
    EXPECT_EQ(outStr, "");  // Expect empty string for empty document
}

// Exceptional / error case: Invalid XML
TEST_F(XMLPrinterHTML5Test_325, ParseInvalidXMLReturnsError_325) {
    XMLDocument doc(false);
    const char* invalidXML = "<html><body><unclosedTag></body></html>";
    XMLError err = doc.Parse(invalidXML);
    EXPECT_NE(err, XML_SUCCESS);  // Parsing should fail
    EXPECT_TRUE(doc.Error());
    EXPECT_GT(doc.ErrorLineNum(), 0);
    EXPECT_NE(doc.ErrorStr(), nullptr);
}

// Verify external interaction: CStr() after multiple prints
TEST_F(XMLPrinterHTML5Test_325, CStrReflectsLatestPrint_325) {
    XMLDocument doc(false);
    doc.Parse(sampleHTML_);

    XMLPrinterHTML5 html5(nullptr, true);
    doc.Print(&html5);

    const char* firstOutput = html5.CStr();
    EXPECT_NE(firstOutput, nullptr);

    XMLDocument doc2(false);
    doc2.Parse("<div>Test</div>");
    doc2.Print(&html5);

    const char* secondOutput = html5.CStr();
    EXPECT_NE(secondOutput, nullptr);
    EXPECT_NE(std::string(firstOutput), std::string(secondOutput));
}

// Normal operation: CloseElement and void element behavior
TEST_F(XMLPrinterHTML5Test_325, CloseElementDoesNotCrash_325) {
    XMLPrinterHTML5 html5(nullptr, true);
    
    // Open a normal element
    html5.OpenElement("div", true);
    html5.CloseElement();  // Should not crash

    // Open a void element
    html5.OpenElement("br", true);
    html5.CloseElement();  // Should handle void element
}

// Verify output size after printing
TEST_F(XMLPrinterHTML5Test_325, CStrSizeReflectsBuffer_325) {
    XMLDocument doc(false);
    doc.Parse(sampleHTML_);
    
    XMLPrinterHTML5 html5(nullptr, true);
    doc.Print(&html5);

    size_t size = html5.CStrSize();
    EXPECT_GT(size, 0);
    EXPECT_EQ(size, strlen(html5.CStr()) + 1);  // CStrSize includes null terminator
}
