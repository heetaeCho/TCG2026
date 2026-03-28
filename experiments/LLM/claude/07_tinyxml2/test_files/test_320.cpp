#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLPrinter Visit(XMLComment) tests
class XMLPrinterVisitCommentTest_320 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test that Visit(XMLComment) returns true
TEST_F(XMLPrinterVisitCommentTest_320, VisitCommentReturnsTrue_320) {
    doc->Parse("<!-- This is a comment --><root/>");
    const XMLComment* comment = doc->FirstChild()->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLPrinter printer(nullptr, false);
    bool result = printer.Visit(*comment);
    EXPECT_TRUE(result);
}

// Test that Visit(XMLComment) pushes the comment text into the printer output
TEST_F(XMLPrinterVisitCommentTest_320, VisitCommentOutputsCommentText_320) {
    doc->Parse("<!-- Hello World --><root/>");
    const XMLComment* comment = doc->FirstChild()->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLPrinter printer(nullptr, false);
    printer.Visit(*comment);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("Hello World"), std::string::npos);
    EXPECT_NE(std::string(output).find("<!--"), std::string::npos);
    EXPECT_NE(std::string(output).find("-->"), std::string::npos);
}

// Test Visit with an empty comment
TEST_F(XMLPrinterVisitCommentTest_320, VisitEmptyComment_320) {
    doc->Parse("<!----><root/>");
    const XMLComment* comment = doc->FirstChild()->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLPrinter printer(nullptr, false);
    bool result = printer.Visit(*comment);
    EXPECT_TRUE(result);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("<!--"), std::string::npos);
    EXPECT_NE(std::string(output).find("-->"), std::string::npos);
}

// Test Visit with a comment containing special characters
TEST_F(XMLPrinterVisitCommentTest_320, VisitCommentWithSpecialChars_320) {
    doc->Parse("<!-- <special> & \"chars\" --><root/>");
    const XMLComment* comment = doc->FirstChild()->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLPrinter printer(nullptr, false);
    bool result = printer.Visit(*comment);
    EXPECT_TRUE(result);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("<!--"), std::string::npos);
    EXPECT_NE(std::string(output).find("-->"), std::string::npos);
}

// Test Visit with a comment in compact mode
TEST_F(XMLPrinterVisitCommentTest_320, VisitCommentCompactMode_320) {
    doc->Parse("<!-- compact comment --><root/>");
    const XMLComment* comment = doc->FirstChild()->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLPrinter printer(nullptr, true);  // compact mode
    bool result = printer.Visit(*comment);
    EXPECT_TRUE(result);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("compact comment"), std::string::npos);
}

// Test Visit with a comment containing multiline text
TEST_F(XMLPrinterVisitCommentTest_320, VisitMultilineComment_320) {
    doc->Parse("<!-- line1\nline2\nline3 --><root/>");
    const XMLComment* comment = doc->FirstChild()->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLPrinter printer(nullptr, false);
    bool result = printer.Visit(*comment);
    EXPECT_TRUE(result);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("line1"), std::string::npos);
    EXPECT_NE(std::string(output).find("line2"), std::string::npos);
    EXPECT_NE(std::string(output).find("line3"), std::string::npos);
}

// Test that CStrSize is non-zero after visiting a comment
TEST_F(XMLPrinterVisitCommentTest_320, VisitCommentCStrSizeNonZero_320) {
    doc->Parse("<!-- test --><root/>");
    const XMLComment* comment = doc->FirstChild()->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLPrinter printer(nullptr, false);
    printer.Visit(*comment);

    EXPECT_GT(printer.CStrSize(), 0u);
}

// Test Visit comment via Accept (which internally calls Visit on the printer)
TEST_F(XMLPrinterVisitCommentTest_320, AcceptCommentCallsVisit_320) {
    doc->Parse("<!-- accepted comment --><root/>");
    const XMLNode* comment = doc->FirstChild();
    ASSERT_NE(comment, nullptr);
    ASSERT_NE(comment->ToComment(), nullptr);

    XMLPrinter printer(nullptr, false);
    comment->Accept(&printer);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("accepted comment"), std::string::npos);
}

// Test multiple comments visited sequentially
TEST_F(XMLPrinterVisitCommentTest_320, VisitMultipleComments_320) {
    doc->Parse("<!-- first --><!-- second --><root/>");

    XMLPrinter printer(nullptr, false);

    const XMLNode* node = doc->FirstChild();
    ASSERT_NE(node, nullptr);
    const XMLComment* comment1 = node->ToComment();
    ASSERT_NE(comment1, nullptr);
    printer.Visit(*comment1);

    node = node->NextSibling();
    ASSERT_NE(node, nullptr);
    const XMLComment* comment2 = node->ToComment();
    ASSERT_NE(comment2, nullptr);
    printer.Visit(*comment2);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string out(output);
    EXPECT_NE(out.find("first"), std::string::npos);
    EXPECT_NE(out.find("second"), std::string::npos);
}

// Test that ClearBuffer resets the output after visiting a comment
TEST_F(XMLPrinterVisitCommentTest_320, ClearBufferAfterVisitComment_320) {
    doc->Parse("<!-- clear me --><root/>");
    const XMLComment* comment = doc->FirstChild()->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLPrinter printer(nullptr, false);
    printer.Visit(*comment);

    EXPECT_GT(printer.CStrSize(), 1u);  // more than just null terminator

    printer.ClearBuffer();

    // After clearing, CStrSize should be minimal (just null terminator or 0)
    EXPECT_LE(printer.CStrSize(), 1u);
}

// Test comment with whitespace only content
TEST_F(XMLPrinterVisitCommentTest_320, VisitWhitespaceOnlyComment_320) {
    doc->Parse("<!--    --><root/>");
    const XMLComment* comment = doc->FirstChild()->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLPrinter printer(nullptr, false);
    bool result = printer.Visit(*comment);
    EXPECT_TRUE(result);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("<!--"), std::string::npos);
    EXPECT_NE(std::string(output).find("-->"), std::string::npos);
}

// Test comment nested inside an element
TEST_F(XMLPrinterVisitCommentTest_320, VisitCommentInsideElement_320) {
    doc->Parse("<root><!-- nested comment --></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLComment* comment = root->FirstChild()->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLPrinter printer(nullptr, false);
    bool result = printer.Visit(*comment);
    EXPECT_TRUE(result);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("nested comment"), std::string::npos);
}

// Test full document with comment using Accept on document
TEST_F(XMLPrinterVisitCommentTest_320, FullDocumentWithCommentAccept_320) {
    doc->Parse("<root><!-- doc comment --><child/></root>");

    XMLPrinter printer(nullptr, false);
    doc->Accept(&printer);

    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string out(output);
    EXPECT_NE(out.find("doc comment"), std::string::npos);
    EXPECT_NE(out.find("<root>"), std::string::npos);
    EXPECT_NE(out.find("</root>"), std::string::npos);
}
