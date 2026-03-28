#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Mock class to capture calls to XMLPrinter
class XMLPrinterMock : public XMLPrinter {
public:
    std::string lastText;
    bool lastCData = false;

    XMLPrinterMock() : XMLPrinter(nullptr, true, 0, EscapeAposCharsInAttributes::YES) {}

    void PushText(const char* text, bool cdata) override {
        lastText = text ? text : "";
        lastCData = cdata;
    }
};

class XMLPrinterTest_319 : public ::testing::Test {
protected:
    XMLPrinterMock printer;
};

// Normal operation: Visit should call PushText with correct value and CData flag
TEST_F(XMLPrinterTest_319, VisitCallsPushTextWithCorrectValue_319) {
    XMLText text(nullptr);
    text.SetCData(false);
    text.SetValue("Hello World", true);

    bool result = printer.Visit(text);

    EXPECT_TRUE(result);
    EXPECT_EQ(printer.lastText, std::string("Hello World"));
    EXPECT_FALSE(printer.lastCData);
}

// Boundary: Empty text string
TEST_F(XMLPrinterTest_319, VisitEmptyText_319) {
    XMLText text(nullptr);
    text.SetCData(false);
    text.SetValue("", true);

    bool result = printer.Visit(text);

    EXPECT_TRUE(result);
    EXPECT_EQ(printer.lastText, std::string(""));
    EXPECT_FALSE(printer.lastCData);
}

// Exceptional / Edge: CData true
TEST_F(XMLPrinterTest_319, VisitCDataTrue_319) {
    XMLText text(nullptr);
    text.SetCData(true);
    text.SetValue("Some <CDATA> content", true);

    bool result = printer.Visit(text);

    EXPECT_TRUE(result);
    EXPECT_EQ(printer.lastText, std::string("Some <CDATA> content"));
    EXPECT_TRUE(printer.lastCData);
}

// Edge: null text value (simulated by not setting value)
TEST_F(XMLPrinterTest_319, VisitNullText_319) {
    XMLText text(nullptr);
    text.SetCData(false);

    bool result = printer.Visit(text);

    EXPECT_TRUE(result);
    EXPECT_EQ(printer.lastText, std::string(""));
    EXPECT_FALSE(printer.lastCData);
}
