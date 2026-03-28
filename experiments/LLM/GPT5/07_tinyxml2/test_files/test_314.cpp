// File: ./TestProjects/tinyxml2/tests/XMLPrinterPushDeclarationTest_314.cpp

#include <gtest/gtest.h>
#include <cstring>

#include "tinyxml2.h"

namespace {

class XMLPrinterPushDeclarationTest_314 : public ::testing::Test {
protected:
    static tinyxml2::XMLPrinter MakePrinter(bool compact) {
        // Avoid depending on enum value names; just use a well-defined cast.
        return tinyxml2::XMLPrinter(/*file*/ nullptr,
                                   /*compact*/ compact,
                                   /*depth*/ 0,
                                   static_cast<tinyxml2::EscapeAposCharsInAttributes>(0));
    }

    static bool Contains(const char* haystack, const char* needle) {
        if (!haystack || !needle) return false;
        return std::strstr(haystack, needle) != nullptr;
    }
};

}  // namespace

TEST_F(XMLPrinterPushDeclarationTest_314, PushDeclarationWritesWrappingTokens_314) {
    auto printer = MakePrinter(/*compact*/ false);

    printer.PushDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");

    const char* out = printer.CStr();
    ASSERT_NE(out, nullptr);
    EXPECT_TRUE(Contains(out, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"));
}

TEST_F(XMLPrinterPushDeclarationTest_314, PushDeclarationWithEmptyStringProducesEmptyDeclaration_314) {
    auto printer = MakePrinter(/*compact*/ false);

    printer.PushDeclaration("");

    const char* out = printer.CStr();
    ASSERT_NE(out, nullptr);
    // Based only on the observable concatenation in the provided implementation snippet:
    // "<?" + value + "?>" where value == "".
    EXPECT_TRUE(Contains(out, "<??>"));
}

TEST_F(XMLPrinterPushDeclarationTest_314, PushDeclarationAppendsToExistingBuffer_314) {
    auto printer = MakePrinter(/*compact*/ false);

    const size_t beforeSize = printer.CStrSize();
    printer.PushDeclaration("xml version=\"1.0\"");
    const size_t afterFirst = printer.CStrSize();
    printer.PushDeclaration("xml-stylesheet type=\"text/xsl\" href=\"style.xsl\"");
    const size_t afterSecond = printer.CStrSize();

    EXPECT_GE(afterFirst, beforeSize);
    EXPECT_GE(afterSecond, afterFirst);

    const char* out = printer.CStr();
    ASSERT_NE(out, nullptr);

    const char* first = std::strstr(out, "<?xml version=\"1.0\"?>");
    const char* second = std::strstr(out, "<?xml-stylesheet type=\"text/xsl\" href=\"style.xsl\"?>");
    ASSERT_NE(first, nullptr);
    ASSERT_NE(second, nullptr);
    EXPECT_LT(first, second);  // order should be preserved
}

TEST_F(XMLPrinterPushDeclarationTest_314, PushDeclarationWorksInCompactMode_314) {
    auto printer = MakePrinter(/*compact*/ true);

    printer.PushDeclaration("xml version=\"1.0\"");

    const char* out = printer.CStr();
    ASSERT_NE(out, nullptr);
    EXPECT_TRUE(Contains(out, "<?xml version=\"1.0\"?>"));
}

TEST_F(XMLPrinterPushDeclarationTest_314, PushDeclarationAfterClearBufferStartsFresh_314) {
    auto printer = MakePrinter(/*compact*/ false);

    printer.PushDeclaration("xml version=\"1.0\"");
    ASSERT_TRUE(Contains(printer.CStr(), "<?xml version=\"1.0\"?>"));

    printer.ClearBuffer(/*resetToFirstElement*/ true);
    printer.PushDeclaration("xml version=\"1.1\"");

    const char* out = printer.CStr();
    ASSERT_NE(out, nullptr);
    EXPECT_FALSE(Contains(out, "<?xml version=\"1.0\"?>"));
    EXPECT_TRUE(Contains(out, "<?xml version=\"1.1\"?>"));
}
