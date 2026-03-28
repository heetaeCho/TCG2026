// File: ./TestProjects/tinyxml2/tests/test_xmlelement_settext_uint64_240.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementSetTextUInt64Test_240 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        elem = doc.NewElement("e");
        ASSERT_NE(elem, nullptr);
        doc.InsertEndChild(elem);
    }
};

TEST_F(XMLElementSetTextUInt64Test_240, SetTextZero_RoundTripsViaQueryUnsigned64Text_240) {
    const uint64_t value = 0;

    elem->SetText(value);

    uint64_t out = 123; // sentinel
    const XMLError err = elem->QueryUnsigned64Text(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, value);

    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    // Avoid assuming exact formatting; just ensure something reasonable is present.
    EXPECT_NE(text[0], '\0');
}

TEST_F(XMLElementSetTextUInt64Test_240, SetTextSmallValue_RoundTripsViaQueryUnsigned64Text_240) {
    const uint64_t value = 42;

    elem->SetText(value);

    uint64_t out = 0;
    const XMLError err = elem->QueryUnsigned64Text(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, value);
}

TEST_F(XMLElementSetTextUInt64Test_240, SetTextMaxValue_RoundTripsViaQueryUnsigned64Text_240) {
    const uint64_t value = (std::numeric_limits<uint64_t>::max)();

    elem->SetText(value);

    uint64_t out = 0;
    const XMLError err = elem->QueryUnsigned64Text(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, value);

    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_NE(text[0], '\0');
}

TEST_F(XMLElementSetTextUInt64Test_240, SetTextOverwritesPreviousText_240) {
    elem->SetText(static_cast<uint64_t>(1));

    uint64_t out1 = 0;
    ASSERT_EQ(elem->QueryUnsigned64Text(&out1), XML_SUCCESS);
    ASSERT_EQ(out1, 1u);

    elem->SetText(static_cast<uint64_t>(2));

    uint64_t out2 = 0;
    const XMLError err = elem->QueryUnsigned64Text(&out2);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out2, 2u);
}

TEST_F(XMLElementSetTextUInt64Test_240, SetTextUInt64WorksAfterCStringText_240) {
    // Start with a string-based text value.
    elem->SetText("123");

    uint64_t initial = 0;
    // Not all strings are guaranteed parseable as uint64, but "123" should be.
    ASSERT_EQ(elem->QueryUnsigned64Text(&initial), XML_SUCCESS);
    ASSERT_EQ(initial, 123u);

    // Now overwrite via uint64_t overload and ensure round-trip.
    const uint64_t value = 456;
    elem->SetText(value);

    uint64_t out = 0;
    const XMLError err = elem->QueryUnsigned64Text(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, value);
}
