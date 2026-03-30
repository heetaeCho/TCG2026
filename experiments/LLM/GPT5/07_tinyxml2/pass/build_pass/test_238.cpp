// TEST_ID: 238
#include <gtest/gtest.h>

#include <limits>
#include <string>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLElementSetTextUnsignedTest_238 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        elem = doc.NewElement("root");
        ASSERT_NE(elem, nullptr);
        doc.InsertFirstChild(elem);
    }
};

TEST_F(XMLElementSetTextUnsignedTest_238, SetTextZeroMakesGetTextReturnZero_238) {
    const unsigned v = 0u;

    elem->SetText(v);

    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "0");

    unsigned parsed = 999u;
    EXPECT_EQ(elem->QueryUnsignedText(&parsed), XML_SUCCESS);
    EXPECT_EQ(parsed, v);
    EXPECT_EQ(elem->UnsignedText(123u), v);
}

TEST_F(XMLElementSetTextUnsignedTest_238, SetTextTypicalValueMatchesDecimalString_238) {
    const unsigned v = 12345u;

    elem->SetText(v);

    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_EQ(std::string(text), std::to_string(v));

    unsigned parsed = 0u;
    EXPECT_EQ(elem->QueryUnsignedText(&parsed), XML_SUCCESS);
    EXPECT_EQ(parsed, v);
}

TEST_F(XMLElementSetTextUnsignedTest_238, SetTextMaxUnsignedRoundTripsViaQueryUnsignedText_238) {
    const unsigned v = std::numeric_limits<unsigned>::max();

    elem->SetText(v);

    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_EQ(std::string(text), std::to_string(v));

    unsigned parsed = 0u;
    EXPECT_EQ(elem->QueryUnsignedText(&parsed), XML_SUCCESS);
    EXPECT_EQ(parsed, v);
}

TEST_F(XMLElementSetTextUnsignedTest_238, SetTextOverwritesPreviousText_238) {
    elem->SetText(1u);
    ASSERT_NE(elem->GetText(), nullptr);
    EXPECT_STREQ(elem->GetText(), "1");

    elem->SetText(42u);

    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "42");

    unsigned parsed = 0u;
    EXPECT_EQ(elem->QueryUnsignedText(&parsed), XML_SUCCESS);
    EXPECT_EQ(parsed, 42u);
}

TEST_F(XMLElementSetTextUnsignedTest_238, SetTextDoesNotCreateAttributes_238) {
    ASSERT_EQ(elem->FirstAttribute(), nullptr);

    elem->SetText(7u);

    // Observable behavior: setting element text should not add attributes.
    EXPECT_EQ(elem->FirstAttribute(), nullptr);
    ASSERT_NE(elem->GetText(), nullptr);
    EXPECT_STREQ(elem->GetText(), "7");
}

TEST_F(XMLElementSetTextUnsignedTest_238, QueryUnsignedTextReportsErrorWhenNoTextPresent_238) {
    // Before any SetText call, element has no text node.
    EXPECT_EQ(elem->GetText(), nullptr);

    unsigned out = 0u;
    const XMLError err = elem->QueryUnsignedText(&out);

    // Don't assume the exact error code value beyond "not success".
    EXPECT_NE(err, XML_SUCCESS);

    // UnsignedText should return the provided default when no text is present.
    EXPECT_EQ(elem->UnsignedText(99u), 99u);
}
