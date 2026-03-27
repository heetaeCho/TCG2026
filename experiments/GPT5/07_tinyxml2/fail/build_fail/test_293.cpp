// File: ./TestProjects/tinyxml2/test_XMLPrinter_PrintSpace_293.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tinyxml2.h"

using ::testing::_;
using ::testing::InSequence;
using ::testing::StrEq;
using ::testing::Exactly;

namespace {

class MockPrinter_293 : public tinyxml2::XMLPrinter {
public:
    using tinyxml2::XMLPrinter::XMLPrinter;   // inherit ctor
    using tinyxml2::XMLPrinter::PrintSpace;   // expose protected method for testing

    MOCK_METHOD(void, Write, (const char* data, size_t size), (override));
};

static tinyxml2::EscapeAposCharsInAttributes DefaultAposMode_293() {
    // Avoid assuming specific enum values; 0 is typically a valid default in this codebase.
    return static_cast<tinyxml2::EscapeAposCharsInAttributes>(0);
}

}  // namespace

class XMLPrinterPrintSpaceTest_293 : public ::testing::Test {
protected:
    XMLPrinterPrintSpaceTest_293()
        : printer(nullptr, /*compact=*/false, /*depth=*/0, DefaultAposMode_293()) {}

    MockPrinter_293 printer;
};

TEST_F(XMLPrinterPrintSpaceTest_293, PrintSpaceDepthZeroWritesNothing_293) {
    EXPECT_CALL(printer, Write(_, _)).Times(0);
    printer.PrintSpace(0);
}

TEST_F(XMLPrinterPrintSpaceTest_293, PrintSpaceDepthOneWritesSingleSpace_293) {
    EXPECT_CALL(printer, Write(StrEq(" "), 1)).Times(1);
    printer.PrintSpace(1);
}

TEST_F(XMLPrinterPrintSpaceTest_293, PrintSpaceDepthFiveWritesFiveSpaces_293) {
    InSequence seq;
    EXPECT_CALL(printer, Write(StrEq(" "), 1)).Times(5);
    printer.PrintSpace(5);
}

TEST_F(XMLPrinterPrintSpaceTest_293, PrintSpaceNegativeDepthWritesNothing_293) {
    EXPECT_CALL(printer, Write(_, _)).Times(0);
    printer.PrintSpace(-3);
}

TEST_F(XMLPrinterPrintSpaceTest_293, PrintSpaceLargerDepthWritesThatManySpaces_293) {
    constexpr int kDepth = 64;
    EXPECT_CALL(printer, Write(StrEq(" "), 1)).Times(Exactly(kDepth));
    printer.PrintSpace(kDepth);
}
