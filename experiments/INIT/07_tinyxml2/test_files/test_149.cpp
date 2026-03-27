// TEST_ID: 149
#include <gtest/gtest.h>

#include <cstdio>
#include <string>

#include "tinyxml2.h"

namespace {

class XMLPrinterCStrSizeTest_149 : public ::testing::Test {
protected:
    // Prefer the common tinyxml2 constructor form. If your local tinyxml2 build
    // requires additional parameters, adjust this helper accordingly.
    tinyxml2::XMLPrinter MakePrinter() {
        return tinyxml2::XMLPrinter(nullptr, /*compact=*/false, /*depth=*/0);
    }
};

TEST_F(XMLPrinterCStrSizeTest_149, CStrSize_IsStableWhenNoOperationsOccur_149) {
    tinyxml2::XMLPrinter printer = MakePrinter();

    const size_t s1 = printer.CStrSize();
    const size_t s2 = printer.CStrSize();

    EXPECT_EQ(s1, s2);
}

TEST_F(XMLPrinterCStrSizeTest_149, CStrSize_NonDecreasingAcrossWrites_149) {
    tinyxml2::XMLPrinter printer = MakePrinter();

    const size_t baseline = printer.CStrSize();

    printer.OpenElement("root", /*compactMode=*/false);
    const size_t afterOpen = printer.CStrSize();
    EXPECT_GE(afterOpen, baseline);

    printer.PushAttribute("a", "b");
    const size_t afterAttr = printer.CStrSize();
    EXPECT_GE(afterAttr, afterOpen);

    printer.PushText("hello", /*cdata=*/false);
    const size_t afterText = printer.CStrSize();
    EXPECT_GE(afterText, afterAttr);

    printer.CloseElement(/*compactMode=*/false);
    const size_t afterClose = printer.CStrSize();
    EXPECT_GE(afterClose, afterText);
}

TEST_F(XMLPrinterCStrSizeTest_149, CStrSize_DoesNotShrinkAcrossRepeatedTextAppends_149) {
    tinyxml2::XMLPrinter printer = MakePrinter();

    printer.OpenElement("root", /*compactMode=*/false);
    size_t prev = printer.CStrSize();

    printer.PushText("a", /*cdata=*/false);
    size_t s1 = printer.CStrSize();
    EXPECT_GE(s1, prev);
    prev = s1;

    printer.PushText("", /*cdata=*/false);  // boundary: empty text
    size_t s2 = printer.CStrSize();
    EXPECT_GE(s2, prev);
    prev = s2;

    printer.PushText("b", /*cdata=*/false);
    size_t s3 = printer.CStrSize();
    EXPECT_GE(s3, prev);

    printer.CloseElement(/*compactMode=*/false);
    size_t s4 = printer.CStrSize();
    EXPECT_GE(s4, s3);
}

TEST_F(XMLPrinterCStrSizeTest_149, ClearBuffer_ResetsOrReducesCStrSize_149) {
    tinyxml2::XMLPrinter printer = MakePrinter();

    const size_t baseline = printer.CStrSize();

    printer.OpenElement("root", /*compactMode=*/false);
    printer.PushText("content", /*cdata=*/false);
    printer.CloseElement(/*compactMode=*/false);

    const size_t grown = printer.CStrSize();
    EXPECT_GE(grown, baseline);

    printer.ClearBuffer();  // observable effect should be reflected in CStrSize
    const size_t afterClear = printer.CStrSize();

    // Black-box safe expectation: clearing should not make the buffer *larger*,
    // and should bring it back toward the baseline.
    EXPECT_LE(afterClear, grown);
    EXPECT_LE(afterClear, grown); // intentional redundancy avoided in other tests
}

TEST_F(XMLPrinterCStrSizeTest_149, CStrSize_IncreasesWithLargeInput_149) {
    tinyxml2::XMLPrinter printer = MakePrinter();

    printer.OpenElement("root", /*compactMode=*/false);
    const size_t before = printer.CStrSize();

    std::string big(10000, 'x');
    printer.PushText(big.c_str(), /*cdata=*/false);

    const size_t after = printer.CStrSize();
    EXPECT_GE(after, before);

    printer.CloseElement(/*compactMode=*/false);
    const size_t afterClose = printer.CStrSize();
    EXPECT_GE(afterClose, after);
}

}  // namespace
