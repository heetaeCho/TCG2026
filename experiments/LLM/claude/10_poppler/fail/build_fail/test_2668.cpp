#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <memory>
#include <sstream>

// Include necessary headers
#include "poppler/StructElement.h"
#include "poppler/Object.h"

// We need to capture stdout output for testing
class CaptureStdout {
public:
    void start() {
        testing::internal::CaptureStdout();
    }
    std::string stop() {
        return testing::internal::GetCapturedStdout();
    }
};

// Forward declare the function under test
static void printAttribute(const Attribute *attribute, unsigned indent);
static void printIndent(unsigned indent);

// Include the source file to get access to the static functions
// This is necessary because printAttribute is static
#include "utils/pdfinfo.cc"

class PrintAttributeTest_2668 : public ::testing::Test {
protected:
    CaptureStdout capture;
};

TEST_F(PrintAttributeTest_2668, PrintsTypeName_2668) {
    // Create a simple attribute with a known type
    Object value(1); // integer object
    Attribute attr(Attribute::BBox, &value);
    
    capture.start();
    printAttribute(&attr, 0);
    std::string output = capture.stop();
    
    // Should contain the type name
    EXPECT_NE(output.find(attr.getTypeName()), std::string::npos);
}

TEST_F(PrintAttributeTest_2668, PrintsUserPropertyName_2668) {
    // Create a UserProperty attribute with a name
    Object value(1);
    GooString name("TestProperty");
    Attribute attr(std::move(name), &value);
    
    capture.start();
    printAttribute(&attr, 0);
    std::string output = capture.stop();
    
    // UserProperty should print the name in parentheses
    EXPECT_NE(output.find("(TestProperty)"), std::string::npos);
}

TEST_F(PrintAttributeTest_2668, PrintsFormattedValue_2668) {
    Object value(42);
    Attribute attr(Attribute::BBox, &value);
    GooString formatted("formatted_text");
    attr.setFormattedValue(&formatted);
    
    capture.start();
    printAttribute(&attr, 0);
    std::string output = capture.stop();
    
    // Should contain the formatted value in quotes
    EXPECT_NE(output.find("\"formatted_text\""), std::string::npos);
}

TEST_F(PrintAttributeTest_2668, PrintsHiddenTag_2668) {
    Object value(42);
    Attribute attr(Attribute::BBox, &value);
    attr.setHidden(true);
    
    capture.start();
    printAttribute(&attr, 0);
    std::string output = capture.stop();
    
    // Should contain [hidden]
    EXPECT_NE(output.find("[hidden]"), std::string::npos);
}

TEST_F(PrintAttributeTest_2668, DoesNotPrintHiddenWhenNotHidden_2668) {
    Object value(42);
    Attribute attr(Attribute::BBox, &value);
    attr.setHidden(false);
    
    capture.start();
    printAttribute(&attr, 0);
    std::string output = capture.stop();
    
    // Should NOT contain [hidden]
    EXPECT_EQ(output.find("[hidden]"), std::string::npos);
}

TEST_F(PrintAttributeTest_2668, DoesNotPrintFormattedWhenNull_2668) {
    Object value(42);
    Attribute attr(Attribute::BBox, &value);
    // Don't set formatted value
    
    capture.start();
    printAttribute(&attr, 0);
    std::string output = capture.stop();
    
    // Count occurrences of quotes - should not have formatted value quotes
    size_t quoteCount = 0;
    for (char c : output) {
        if (c == '"') quoteCount++;
    }
    EXPECT_EQ(quoteCount, 0u);
}

TEST_F(PrintAttributeTest_2668, IndentAffectsOutput_2668) {
    Object value(42);
    Attribute attr(Attribute::BBox, &value);
    
    capture.start();
    printAttribute(&attr, 0);
    std::string output0 = capture.stop();
    
    capture.start();
    printAttribute(&attr, 4);
    std::string output4 = capture.stop();
    
    // Output with indent 4 should be longer due to indentation
    EXPECT_GT(output4.length(), output0.length());
}

TEST_F(PrintAttributeTest_2668, NonUserPropertyDoesNotPrintName_2668) {
    Object value(42);
    Attribute attr(Attribute::BBox, &value);
    
    capture.start();
    printAttribute(&attr, 0);
    std::string output = capture.stop();
    
    // Non-UserProperty should not have parenthesized name
    // Check there's no pattern like "(somename)"
    // The output should have the type name with slashes but no parens for name
    size_t parenCount = 0;
    for (char c : output) {
        if (c == '(') parenCount++;
    }
    EXPECT_EQ(parenCount, 0u);
}

TEST_F(PrintAttributeTest_2668, HiddenAndFormattedTogether_2668) {
    Object value(42);
    Attribute attr(Attribute::BBox, &value);
    GooString formatted("test_fmt");
    attr.setFormattedValue(&formatted);
    attr.setHidden(true);
    
    capture.start();
    printAttribute(&attr, 0);
    std::string output = capture.stop();
    
    // Should contain both formatted value and hidden tag
    EXPECT_NE(output.find("\"test_fmt\""), std::string::npos);
    EXPECT_NE(output.find("[hidden]"), std::string::npos);
    
    // [hidden] should come after the formatted value
    size_t fmtPos = output.find("\"test_fmt\"");
    size_t hiddenPos = output.find("[hidden]");
    EXPECT_GT(hiddenPos, fmtPos);
}

TEST_F(PrintAttributeTest_2668, SlashBeforeTypeName_2668) {
    Object value(42);
    Attribute attr(Attribute::BBox, &value);
    
    capture.start();
    printAttribute(&attr, 0);
    std::string output = capture.stop();
    
    // Should contain "/<TypeName>" pattern
    std::string typeName = attr.getTypeName();
    std::string expected = "/" + typeName;
    EXPECT_NE(output.find(expected), std::string::npos);
}

TEST_F(PrintAttributeTest_2668, ZeroIndent_2668) {
    Object value(42);
    Attribute attr(Attribute::BBox, &value);
    
    capture.start();
    printAttribute(&attr, 0);
    std::string output = capture.stop();
    
    // Should produce valid output even with zero indent
    EXPECT_FALSE(output.empty());
}

TEST_F(PrintAttributeTest_2668, LargeIndent_2668) {
    Object value(42);
    Attribute attr(Attribute::BBox, &value);
    
    capture.start();
    printAttribute(&attr, 20);
    std::string output = capture.stop();
    
    // Should produce valid output with large indent
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find(attr.getTypeName()), std::string::npos);
}
