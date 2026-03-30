#include "tinyxml2.h"
#include <gtest/gtest.h>
#include <sstream>
#include <memory>

using namespace tinyxml2;

class XMLPrinterTest_303 : public ::testing::Test {
protected:
    void SetUp() override {
        // Redirect output to memory file
        memFile = std::tmpfile();
        ASSERT_NE(memFile, nullptr);
        printer = std::make_unique<XMLPrinter>(memFile, false, 0, XMLPrinter::EscapeAposCharsInAttributes::NO);
    }

    void TearDown() override {
        if (memFile) std::fclose(memFile);
    }

    std::unique_ptr<XMLPrinter> printer;
    FILE* memFile;
};

// Helper to read back FILE contents
std::string ReadFile(FILE* f) {
    std::fseek(f, 0, SEEK_SET);
    std::string content;
    char buf[1024];
    size_t n = 0;
    while ((n = std::fread(buf, 1, sizeof(buf), f)) > 0) {
        content.append(buf, n);
    }
    return content;
}

// Test: CloseElement after OpenElement writes expected closing tag (normal case)
TEST_F(XMLPrinterTest_303, CloseElementNormal_303) {
    printer->OpenElement("test", false);
    printer->CloseElement(false);

    std::string output = ReadFile(memFile);
    EXPECT_NE(output.find("<test>"), std::string::npos);
    EXPECT_NE(output.find("</test>"), std::string::npos);
}

// Test: CloseElement with compactMode = true suppresses newlines/indent
TEST_F(XMLPrinterTest_303, CloseElementCompactMode_303) {
    printer->OpenElement("compact", true);
    printer->CloseElement(true);

    std::string output = ReadFile(memFile);
    EXPECT_NE(output.find("<compact>"), std::string::npos);
    EXPECT_NE(output.find("</compact>"), std::string::npos);
    // In compact mode, we should not see newlines
    EXPECT_EQ(output.find("\n"), std::string::npos);
}

// Test: CloseElement on an element that was just opened (empty element) writes "/>"
TEST_F(XMLPrinterTest_303, CloseElementJustOpened_303) {
    printer->OpenElement("empty", false);
    // Without adding text or attributes, element is "just opened"
    printer->CloseElement(false);

    std::string output = ReadFile(memFile);
    EXPECT_NE(output.find("<empty/>"), std::string::npos);
}

// Test: Multiple nested elements
TEST_F(XMLPrinterTest_303, CloseElementNested_303) {
    printer->OpenElement("parent", false);
    printer->OpenElement("child", false);
    printer->CloseElement(false); // child
    printer->CloseElement(false); // parent

    std::string output = ReadFile(memFile);
    EXPECT_NE(output.find("<parent>"), std::string::npos);
    EXPECT_NE(output.find("<child>"), std::string::npos);
    EXPECT_NE(output.find("</child>"), std::string::npos);
    EXPECT_NE(output.find("</parent>"), std::string::npos);
}

// Test: CloseElement called when _textDepth equals _depth resets _textDepth
TEST_F(XMLPrinterTest_303, CloseElementResetsTextDepth_303) {
    printer->PushText("text", false);  // sets _textDepth = _depth internally
    printer->OpenElement("elem", false);
    printer->CloseElement(false);

    // Behavior observable: output contains both text and closing tag
    std::string output = ReadFile(memFile);
    EXPECT_NE(output.find("text"), std::string::npos);
    EXPECT_NE(output.find("</elem>"), std::string::npos);
}

// Boundary: Closing root element (depth 0) with newlines
TEST_F(XMLPrinterTest_303, CloseElementRoot_303) {
    printer->OpenElement("root", false);
    printer->CloseElement(false); // depth becomes 0

    std::string output = ReadFile(memFile);
    EXPECT_NE(output.find("<root>"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
    // Newline at end should be present
    EXPECT_EQ(output.back(), '\n');
}

// Exceptional: Calling CloseElement without any OpenElement should not crash
TEST_F(XMLPrinterTest_303, CloseElementWithoutOpen_303) {
    // We just call CloseElement directly; internal Pop might return nullptr
    EXPECT_NO_THROW(printer->CloseElement(false));
    std::string output = ReadFile(memFile);
    // Output may be empty
    EXPECT_TRUE(output.empty() || output.find("</") == std::string::npos);
}
