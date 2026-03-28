#include <gtest/gtest.h>
#include <cstring>
#include <string>

// Include the necessary headers
#include "tinyxml2.h"
#include "contrib/html5-printer.cpp"

using namespace tinyxml2;

class XMLPrinterHTML5Test_323 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a void element (e.g., <br>) is self-closing without explicit closing tag
TEST_F(XMLPrinterHTML5Test_323, VoidElementBrSelfCloses_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("br");
    printer.CloseElement();
    std::string result = printer.CStr();
    // For void elements, the output should NOT have </br>
    EXPECT_TRUE(result.find("</br>") == std::string::npos);
    // It should contain <br> or <br/>
    EXPECT_TRUE(result.find("br") != std::string::npos);
}

// Test that a non-void element (e.g., <div>) gets proper closing tag
TEST_F(XMLPrinterHTML5Test_323, NonVoidElementDivHasClosingTag_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("div");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</div>") != std::string::npos);
}

// Test void element <hr>
TEST_F(XMLPrinterHTML5Test_323, VoidElementHrSelfCloses_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("hr");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</hr>") == std::string::npos);
}

// Test void element <img>
TEST_F(XMLPrinterHTML5Test_323, VoidElementImgSelfCloses_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("img");
    printer.PushAttribute("src", "test.png");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</img>") == std::string::npos);
    EXPECT_TRUE(result.find("src") != std::string::npos);
}

// Test void element <input>
TEST_F(XMLPrinterHTML5Test_323, VoidElementInputSelfCloses_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("input");
    printer.PushAttribute("type", "text");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</input>") == std::string::npos);
}

// Test void element <meta>
TEST_F(XMLPrinterHTML5Test_323, VoidElementMetaSelfCloses_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("meta");
    printer.PushAttribute("charset", "utf-8");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</meta>") == std::string::npos);
}

// Test void element <link>
TEST_F(XMLPrinterHTML5Test_323, VoidElementLinkSelfCloses_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("link");
    printer.PushAttribute("rel", "stylesheet");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</link>") == std::string::npos);
}

// Test non-void element <span> gets closing tag
TEST_F(XMLPrinterHTML5Test_323, NonVoidElementSpanHasClosingTag_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("span");
    printer.PushText("Hello");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</span>") != std::string::npos);
    EXPECT_TRUE(result.find("Hello") != std::string::npos);
}

// Test non-void element <p> gets closing tag
TEST_F(XMLPrinterHTML5Test_323, NonVoidElementPHasClosingTag_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("p");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</p>") != std::string::npos);
}

// Test nested elements with both void and non-void
TEST_F(XMLPrinterHTML5Test_323, NestedVoidAndNonVoidElements_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("div");
    printer.OpenElement("br");
    printer.CloseElement();
    printer.OpenElement("p");
    printer.PushText("text");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</div>") != std::string::npos);
    EXPECT_TRUE(result.find("</p>") != std::string::npos);
    EXPECT_TRUE(result.find("</br>") == std::string::npos);
}

// Test void element <area>
TEST_F(XMLPrinterHTML5Test_323, VoidElementAreaSelfCloses_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("area");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</area>") == std::string::npos);
}

// Test void element <base>
TEST_F(XMLPrinterHTML5Test_323, VoidElementBaseSelfCloses_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("base");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</base>") == std::string::npos);
}

// Test void element <col>
TEST_F(XMLPrinterHTML5Test_323, VoidElementColSelfCloses_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("col");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</col>") == std::string::npos);
}

// Test void element <embed>
TEST_F(XMLPrinterHTML5Test_323, VoidElementEmbedSelfCloses_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("embed");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</embed>") == std::string::npos);
}

// Test void element <param>
TEST_F(XMLPrinterHTML5Test_323, VoidElementParamSelfCloses_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("param");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</param>") == std::string::npos);
}

// Test void element <source>
TEST_F(XMLPrinterHTML5Test_323, VoidElementSourceSelfCloses_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("source");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</source>") == std::string::npos);
}

// Test void element <track>
TEST_F(XMLPrinterHTML5Test_323, VoidElementTrackSelfCloses_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("track");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</track>") == std::string::npos);
}

// Test void element <wbr>
TEST_F(XMLPrinterHTML5Test_323, VoidElementWbrSelfCloses_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("wbr");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</wbr>") == std::string::npos);
}

// Test non-void empty element <script> still gets closing tag
TEST_F(XMLPrinterHTML5Test_323, NonVoidElementScriptHasClosingTag_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("script");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</script>") != std::string::npos);
}

// Test non-void empty element <textarea> still gets closing tag
TEST_F(XMLPrinterHTML5Test_323, NonVoidElementTextareaHasClosingTag_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("textarea");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</textarea>") != std::string::npos);
}

// Test compact mode disabled
TEST_F(XMLPrinterHTML5Test_323, NonCompactModeFormatting_323) {
    XMLPrinterHTML5 printer(nullptr, false);
    printer.OpenElement("div");
    printer.OpenElement("p");
    printer.PushText("Hello");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</div>") != std::string::npos);
    EXPECT_TRUE(result.find("</p>") != std::string::npos);
}

// Test creating printer with default parameters
TEST_F(XMLPrinterHTML5Test_323, DefaultConstructor_323) {
    XMLPrinterHTML5 printer;
    printer.OpenElement("div");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</div>") != std::string::npos);
}

// Test multiple void elements in sequence
TEST_F(XMLPrinterHTML5Test_323, MultipleVoidElementsInSequence_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("div");
    printer.OpenElement("br");
    printer.CloseElement();
    printer.OpenElement("hr");
    printer.CloseElement();
    printer.OpenElement("br");
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</br>") == std::string::npos);
    EXPECT_TRUE(result.find("</hr>") == std::string::npos);
    EXPECT_TRUE(result.find("</div>") != std::string::npos);
}

// Test deeply nested non-void elements all get closing tags
TEST_F(XMLPrinterHTML5Test_323, DeeplyNestedNonVoidElements_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("html");
    printer.OpenElement("body");
    printer.OpenElement("div");
    printer.OpenElement("span");
    printer.PushText("Deep");
    printer.CloseElement();
    printer.CloseElement();
    printer.CloseElement();
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</html>") != std::string::npos);
    EXPECT_TRUE(result.find("</body>") != std::string::npos);
    EXPECT_TRUE(result.find("</div>") != std::string::npos);
    EXPECT_TRUE(result.find("</span>") != std::string::npos);
}

// Test that void element with text content inside parent works
TEST_F(XMLPrinterHTML5Test_323, VoidElementInsideNonVoidWithText_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("p");
    printer.PushText("before");
    printer.OpenElement("br");
    printer.CloseElement();
    printer.PushText("after");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("before") != std::string::npos);
    EXPECT_TRUE(result.find("after") != std::string::npos);
    EXPECT_TRUE(result.find("</p>") != std::string::npos);
    EXPECT_TRUE(result.find("</br>") == std::string::npos);
}

// Test ClearBuffer and reuse
TEST_F(XMLPrinterHTML5Test_323, ClearBufferAndReuse_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("div");
    printer.CloseElement();
    std::string result1 = printer.CStr();
    EXPECT_TRUE(result1.find("</div>") != std::string::npos);

    printer.ClearBuffer();
    printer.OpenElement("br");
    printer.CloseElement();
    std::string result2 = printer.CStr();
    EXPECT_TRUE(result2.find("</br>") == std::string::npos);
}

// Test non-void element <a> with attributes
TEST_F(XMLPrinterHTML5Test_323, NonVoidElementAnchorWithAttributes_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("a");
    printer.PushAttribute("href", "http://example.com");
    printer.PushText("Link");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</a>") != std::string::npos);
    EXPECT_TRUE(result.find("href") != std::string::npos);
    EXPECT_TRUE(result.find("Link") != std::string::npos);
}

// Test using XMLDocument to parse and print with HTML5 printer
TEST_F(XMLPrinterHTML5Test_323, DocumentAcceptWithHTML5Printer_323) {
    XMLDocument doc;
    doc.Parse("<html><body><br/><p>Hello</p></body></html>");
    ASSERT_FALSE(doc.Error());

    XMLPrinterHTML5 printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();

    // <br> should not have closing tag
    EXPECT_TRUE(result.find("</br>") == std::string::npos);
    // <p> should have closing tag
    EXPECT_TRUE(result.find("</p>") != std::string::npos);
    // <body> should have closing tag
    EXPECT_TRUE(result.find("</body>") != std::string::npos);
    // <html> should have closing tag
    EXPECT_TRUE(result.find("</html>") != std::string::npos);
}

// Test document with multiple void elements parsed
TEST_F(XMLPrinterHTML5Test_323, DocumentWithMultipleVoidElements_323) {
    XMLDocument doc;
    doc.Parse("<div><img src=\"test.png\"/><hr/><input type=\"text\"/></div>");
    ASSERT_FALSE(doc.Error());

    XMLPrinterHTML5 printer(nullptr, true);
    doc.Accept(&printer);
    std::string result = printer.CStr();

    EXPECT_TRUE(result.find("</img>") == std::string::npos);
    EXPECT_TRUE(result.find("</hr>") == std::string::npos);
    EXPECT_TRUE(result.find("</input>") == std::string::npos);
    EXPECT_TRUE(result.find("</div>") != std::string::npos);
}

// Test an unknown/custom tag is treated as non-void
TEST_F(XMLPrinterHTML5Test_323, CustomTagTreatedAsNonVoid_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("my-custom-element");
    printer.CloseElement();
    std::string result = printer.CStr();
    EXPECT_TRUE(result.find("</my-custom-element>") != std::string::npos);
}

// Test empty non-void element still produces open+close
TEST_F(XMLPrinterHTML5Test_323, EmptyNonVoidElementProducesOpenAndClose_323) {
    XMLPrinterHTML5 printer(nullptr, true);
    printer.OpenElement("div");
    printer.CloseElement();
    std::string result = printer.CStr();
    // Should have both opening and closing
    EXPECT_TRUE(result.find("<div") != std::string::npos);
    EXPECT_TRUE(result.find("</div>") != std::string::npos);
}
