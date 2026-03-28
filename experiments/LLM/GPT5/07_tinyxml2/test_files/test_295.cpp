#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tinyxml2.h"
#include <sstream>

using namespace tinyxml2;

// Helper class to capture Write calls by redirecting to a stringstream
class TestXMLPrinter : public XMLPrinter {
public:
    std::stringstream output;

    TestXMLPrinter() : XMLPrinter(nullptr, false, 0, EscapeAposCharsInAttributes::NO) {}

protected:
    void Write(const char* data, size_t size) override {
        output.write(data, size);
    }

    void Putc(char ch) override {
        output.put(ch);
    }
};

// TEST_ID = 295
class XMLPrinterTest_295 : public ::testing::Test {
protected:
    TestXMLPrinter printer;
};

// Normal operation: open a single element
TEST_F(XMLPrinterTest_295, OpenElementWritesTag_295) {
    printer.OpenElement("TestElement", false);
    std::string written = printer.output.str();

    // The observable behavior: the opening tag is written
    EXPECT_NE(written.find("<TestElement>"), std::string::npos);
}

// Boundary: open an element with an empty name
TEST_F(XMLPrinterTest_295, OpenElementEmptyName_295) {
    printer.OpenElement("", false);
    std::string written = printer.output.str();

    // Expect at least the angle brackets to be written
    EXPECT_NE(written.find("<>"), std::string::npos);
}

// Multiple elements: nested OpenElement calls
TEST_F(XMLPrinterTest_295, OpenElementNested_295) {
    printer.OpenElement("Parent", false);
    printer.OpenElement("Child", false);

    std::string written = printer.output.str();
    EXPECT_NE(written.find("<Parent>"), std::string::npos);
    EXPECT_NE(written.find("<Child>"), std::string::npos);
}

// Compact mode: ensure OpenElement sets _elementJustOpened and handles compactMode
TEST_F(XMLPrinterTest_295, OpenElementCompactMode_295) {
    printer.OpenElement("CompactElement", true);

    // Observable effect: tag is written
    std::string written = printer.output.str();
    EXPECT_NE(written.find("<CompactElement>"), std::string::npos);
}

// Exceptional/edge: element name is very long
TEST_F(XMLPrinterTest_295, OpenElementLongName_295) {
    std::string longName(1024, 'A'); // 1024 'A's
    printer.OpenElement(longName.c_str(), false);

    std::string written = printer.output.str();
    EXPECT_NE(written.find("<" + longName + ">"), std::string::npos);
}
