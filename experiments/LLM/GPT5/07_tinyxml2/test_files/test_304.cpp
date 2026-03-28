#include "tinyxml2.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace tinyxml2;
using ::testing::_;

class XMLPrinterTest_304 : public ::testing::Test {
protected:
    // Mock subclass to capture Putc calls
    class MockXMLPrinter : public XMLPrinter {
    public:
        MockXMLPrinter() : XMLPrinter(nullptr, false, 0, EscapeAposCharsInAttributes::NO) {}

        MOCK_METHOD(void, Putc, (char ch), (override));

        // Expose protected _elementJustOpened for testing
        void SetElementJustOpened(bool value) { _elementJustOpened = value; }
        bool GetElementJustOpened() const { return _elementJustOpened; }
    };
};

// Normal operation: _elementJustOpened is true, SealElementIfJustOpened should call Putc and reset flag
TEST_F(XMLPrinterTest_304, SealElement_CallsPutcAndResetsFlag_304) {
    MockXMLPrinter printer;
    printer.SetElementJustOpened(true);

    EXPECT_CALL(printer, Putc('>')).Times(1);

    printer.SealElementIfJustOpened();

    EXPECT_FALSE(printer.GetElementJustOpened());
}

// Boundary: _elementJustOpened is false, SealElementIfJustOpened should do nothing
TEST_F(XMLPrinterTest_304, SealElement_WhenNotJustOpened_DoesNothing_304) {
    MockXMLPrinter printer;
    printer.SetElementJustOpened(false);

    EXPECT_CALL(printer, Putc(_)).Times(0);

    printer.SealElementIfJustOpened();

    EXPECT_FALSE(printer.GetElementJustOpened());
}

// Repeated calls: ensure _elementJustOpened is reset only once
TEST_F(XMLPrinterTest_304, SealElement_CalledTwice_OnlyFirstCallWrites_304) {
    MockXMLPrinter printer;
    printer.SetElementJustOpened(true);

    EXPECT_CALL(printer, Putc('>')).Times(1);

    printer.SealElementIfJustOpened();  // first call
    printer.SealElementIfJustOpened();  // second call, should do nothing
}
