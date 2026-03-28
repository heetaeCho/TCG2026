#include "tinyxml2.h"
#include <gtest/gtest.h>

using namespace tinyxml2;

// TEST_ID: 315
class XMLPrinterTest_315 : public ::testing::Test {
protected:
    void SetUp() override {
        // Using nullptr for FILE* since we will use in-memory buffer.
        printer = new XMLPrinter(nullptr, false, 0, XMLPrinter::EscapeAposCharsInAttributes::NO);
    }

    void TearDown() override {
        delete printer;
    }

    XMLPrinter* printer;
};

// Normal operation: simple unknown node
TEST_F(XMLPrinterTest_315, PushUnknown_SimpleValue_315) {
    const char* unknown = "UNKNOWN_NODE";
    printer->PushUnknown(unknown);

    std::string expected = "<!UNKNOWN_NODE>";
    ASSERT_EQ(printer->CStrSize(), expected.size() + 1); // +1 for null terminator
    ASSERT_STREQ(printer->CStr(), expected.c_str());
}

// Boundary condition: empty string
TEST_F(XMLPrinterTest_315, PushUnknown_EmptyString_315) {
    printer->PushUnknown("");

    std::string expected = "<!>";
    ASSERT_EQ(printer->CStrSize(), expected.size() + 1);
    ASSERT_STREQ(printer->CStr(), expected.c_str());
}

// Exceptional / edge case: very long string
TEST_F(XMLPrinterTest_315, PushUnknown_LongString_315) {
    std::string longValue(1024, 'A'); // 1024 'A's
    printer->PushUnknown(longValue.c_str());

    std::string expected = "<!" + longValue + ">";
    ASSERT_EQ(printer->CStrSize(), expected.size() + 1);
    ASSERT_STREQ(printer->CStr(), expected.c_str());
}

// Multiple consecutive unknown nodes
TEST_F(XMLPrinterTest_315, PushUnknown_MultipleNodes_315) {
    printer->PushUnknown("NODE1");
    printer->PushUnknown("NODE2");

    std::string expected = "<!NODE1><!NODE2>";
    ASSERT_EQ(printer->CStrSize(), expected.size() + 1);
    ASSERT_STREQ(printer->CStr(), expected.c_str());
}

// Special characters in unknown node
TEST_F(XMLPrinterTest_315, PushUnknown_SpecialChars_315) {
    const char* unknown = "NODE & < > \" '";
    printer->PushUnknown(unknown);

    std::string expected = "<!NODE & < > \" '>";
    ASSERT_EQ(printer->CStrSize(), expected.size() + 1);
    ASSERT_STREQ(printer->CStr(), expected.c_str());
}
