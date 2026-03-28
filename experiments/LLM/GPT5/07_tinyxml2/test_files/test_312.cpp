// File: ./TestProjects/tinyxml2/tests/XMLPrinterPushTextDouble_312_test.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "tinyxml2.h"

namespace {

class XMLPrinterPushTextDoubleTest_312 : public ::testing::Test {
protected:
    static tinyxml2::XMLPrinter MakePrinter() {
        // Avoid depending on specific enum values for EscapeAposCharsInAttributes.
        return tinyxml2::XMLPrinter(
            /*file*/ nullptr,
            /*compact*/ false,
            /*depth*/ 0,
            static_cast<tinyxml2::EscapeAposCharsInAttributes>(0));
    }

    static const char* PrinterStrOrEmpty(const tinyxml2::XMLPrinter& p) {
        const char* s = p.CStr();
        return s ? s : "";
    }
};

TEST_F(XMLPrinterPushTextDoubleTest_312, PushTextDoubleMatchesPushTextCStringFalse_312) {
    const double value = 123.456;

    // Expected: convert using the public dependency, then call PushText(const char*, false).
    char buf[1024] = {};
    tinyxml2::XMLUtil::ToStr(value, buf, static_cast<int>(sizeof(buf)));

    tinyxml2::XMLPrinter pExpected = MakePrinter();
    pExpected.ClearBuffer();
    pExpected.PushText(buf, /*cdata*/ false);

    tinyxml2::XMLPrinter pActual = MakePrinter();
    pActual.ClearBuffer();
    pActual.PushText(value);

    EXPECT_STREQ(PrinterStrOrEmpty(pExpected), PrinterStrOrEmpty(pActual));
    EXPECT_EQ(pExpected.CStrSize(), pActual.CStrSize());
}

TEST_F(XMLPrinterPushTextDoubleTest_312, PushTextDoubleWorksForZero_312) {
    const double value = 0.0;

    char buf[1024] = {};
    tinyxml2::XMLUtil::ToStr(value, buf, static_cast<int>(sizeof(buf)));

    tinyxml2::XMLPrinter p1 = MakePrinter();
    p1.ClearBuffer();
    p1.PushText(value);

    tinyxml2::XMLPrinter p2 = MakePrinter();
    p2.ClearBuffer();
    p2.PushText(buf, /*cdata*/ false);

    EXPECT_STREQ(PrinterStrOrEmpty(p2), PrinterStrOrEmpty(p1));
}

TEST_F(XMLPrinterPushTextDoubleTest_312, PushTextDoubleWorksForNegative_312) {
    const double value = -42.25;

    char buf[1024] = {};
    tinyxml2::XMLUtil::ToStr(value, buf, static_cast<int>(sizeof(buf)));

    tinyxml2::XMLPrinter p1 = MakePrinter();
    p1.ClearBuffer();
    p1.PushText(value);

    tinyxml2::XMLPrinter p2 = MakePrinter();
    p2.ClearBuffer();
    p2.PushText(buf, /*cdata*/ false);

    EXPECT_STREQ(PrinterStrOrEmpty(p2), PrinterStrOrEmpty(p1));
}

TEST_F(XMLPrinterPushTextDoubleTest_312, PushTextDoubleAppendsOnMultipleCalls_312) {
    const double v1 = 1.5;
    const double v2 = 2.75;

    char b1[1024] = {};
    char b2[1024] = {};
    tinyxml2::XMLUtil::ToStr(v1, b1, static_cast<int>(sizeof(b1)));
    tinyxml2::XMLUtil::ToStr(v2, b2, static_cast<int>(sizeof(b2)));

    tinyxml2::XMLPrinter pExpected = MakePrinter();
    pExpected.ClearBuffer();
    pExpected.PushText(b1, /*cdata*/ false);
    pExpected.PushText(b2, /*cdata*/ false);

    tinyxml2::XMLPrinter pActual = MakePrinter();
    pActual.ClearBuffer();
    pActual.PushText(v1);
    pActual.PushText(v2);

    EXPECT_STREQ(PrinterStrOrEmpty(pExpected), PrinterStrOrEmpty(pActual));
    EXPECT_EQ(pExpected.CStrSize(), pActual.CStrSize());
}

TEST_F(XMLPrinterPushTextDoubleTest_312, PushTextDoubleHandlesInfinity_312) {
    const double value = std::numeric_limits<double>::infinity();

    char buf[1024] = {};
    tinyxml2::XMLUtil::ToStr(value, buf, static_cast<int>(sizeof(buf)));

    tinyxml2::XMLPrinter p1 = MakePrinter();
    p1.ClearBuffer();
    p1.PushText(value);

    tinyxml2::XMLPrinter p2 = MakePrinter();
    p2.ClearBuffer();
    p2.PushText(buf, /*cdata*/ false);

    EXPECT_STREQ(PrinterStrOrEmpty(p2), PrinterStrOrEmpty(p1));
}

TEST_F(XMLPrinterPushTextDoubleTest_312, PushTextDoubleHandlesNaN_312) {
    const double value = std::numeric_limits<double>::quiet_NaN();

    char buf[1024] = {};
    tinyxml2::XMLUtil::ToStr(value, buf, static_cast<int>(sizeof(buf)));

    tinyxml2::XMLPrinter p1 = MakePrinter();
    p1.ClearBuffer();
    p1.PushText(value);

    tinyxml2::XMLPrinter p2 = MakePrinter();
    p2.ClearBuffer();
    p2.PushText(buf, /*cdata*/ false);

    EXPECT_STREQ(PrinterStrOrEmpty(p2), PrinterStrOrEmpty(p1));
}

}  // namespace
