#include <gtest/gtest.h>
#include "tinyxml2.h"
#include <string>
#include <cstdint>
#include <climits>

using namespace tinyxml2;

class XMLElementSetTextUint64Test_240 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* createElement(const char* name = "test") {
        XMLElement* elem = doc.NewElement(name);
        doc.InsertEndChild(elem);
        return elem;
    }
};

// Test SetText with uint64_t value zero
TEST_F(XMLElementSetTextUint64Test_240, SetTextUint64Zero_240) {
    XMLElement* elem = createElement();
    elem->SetText(static_cast<uint64_t>(0));
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "0");
}

// Test SetText with uint64_t value one
TEST_F(XMLElementSetTextUint64Test_240, SetTextUint64One_240) {
    XMLElement* elem = createElement();
    elem->SetText(static_cast<uint64_t>(1));
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "1");
}

// Test SetText with a typical uint64_t value
TEST_F(XMLElementSetTextUint64Test_240, SetTextUint64Typical_240) {
    XMLElement* elem = createElement();
    elem->SetText(static_cast<uint64_t>(123456789));
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "123456789");
}

// Test SetText with uint64_t max value
TEST_F(XMLElementSetTextUint64Test_240, SetTextUint64Max_240) {
    XMLElement* elem = createElement();
    uint64_t maxVal = UINT64_MAX; // 18446744073709551615
    elem->SetText(maxVal);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "18446744073709551615");
}

// Test SetText with uint64_t large value just below max
TEST_F(XMLElementSetTextUint64Test_240, SetTextUint64NearMax_240) {
    XMLElement* elem = createElement();
    uint64_t val = UINT64_MAX - 1; // 18446744073709551614
    elem->SetText(val);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "18446744073709551614");
}

// Test that SetText with uint64_t overwrites previous text
TEST_F(XMLElementSetTextUint64Test_240, SetTextUint64OverwritesPreviousText_240) {
    XMLElement* elem = createElement();
    elem->SetText("original text");
    EXPECT_STREQ(elem->GetText(), "original text");
    
    elem->SetText(static_cast<uint64_t>(42));
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "42");
}

// Test that SetText with uint64_t overwrites previous uint64_t text
TEST_F(XMLElementSetTextUint64Test_240, SetTextUint64OverwritesPreviousUint64_240) {
    XMLElement* elem = createElement();
    elem->SetText(static_cast<uint64_t>(100));
    EXPECT_STREQ(elem->GetText(), "100");
    
    elem->SetText(static_cast<uint64_t>(200));
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "200");
}

// Test QueryUnsigned64Text after SetText with uint64_t
TEST_F(XMLElementSetTextUint64Test_240, QueryUnsigned64TextAfterSetText_240) {
    XMLElement* elem = createElement();
    elem->SetText(static_cast<uint64_t>(9876543210ULL));
    
    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Text(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 9876543210ULL);
}

// Test Unsigned64Text after SetText with uint64_t
TEST_F(XMLElementSetTextUint64Test_240, Unsigned64TextAfterSetText_240) {
    XMLElement* elem = createElement();
    elem->SetText(static_cast<uint64_t>(555));
    
    uint64_t result = elem->Unsigned64Text(0);
    EXPECT_EQ(result, 555ULL);
}

// Test SetText with uint64_t value that fits in uint32 range
TEST_F(XMLElementSetTextUint64Test_240, SetTextUint64InUint32Range_240) {
    XMLElement* elem = createElement();
    elem->SetText(static_cast<uint64_t>(4294967295ULL)); // UINT32_MAX
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "4294967295");
}

// Test SetText with uint64_t value just above uint32 range
TEST_F(XMLElementSetTextUint64Test_240, SetTextUint64AboveUint32Range_240) {
    XMLElement* elem = createElement();
    elem->SetText(static_cast<uint64_t>(4294967296ULL)); // UINT32_MAX + 1
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "4294967296");
}

// Test SetText with uint64_t and then reading as int64 text
TEST_F(XMLElementSetTextUint64Test_240, SetTextUint64ReadAsInt64_240) {
    XMLElement* elem = createElement();
    elem->SetText(static_cast<uint64_t>(12345));
    
    int64_t result = 0;
    XMLError err = elem->QueryInt64Text(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 12345);
}

// Test SetText with uint64_t on element that already has child elements
TEST_F(XMLElementSetTextUint64Test_240, SetTextUint64OnElementWithChildren_240) {
    XMLElement* parent = createElement("parent");
    XMLElement* child = doc.NewElement("child");
    parent->InsertEndChild(child);
    
    parent->SetText(static_cast<uint64_t>(999));
    const char* text = parent->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "999");
}

// Test multiple elements with different uint64_t values
TEST_F(XMLElementSetTextUint64Test_240, MultipleElementsWithDifferentUint64Values_240) {
    XMLElement* elem1 = doc.NewElement("elem1");
    XMLElement* elem2 = doc.NewElement("elem2");
    doc.InsertEndChild(elem1);
    elem1->InsertAfterChild(nullptr, elem2);
    
    elem1->SetText(static_cast<uint64_t>(111));
    elem2->SetText(static_cast<uint64_t>(222));
    
    EXPECT_STREQ(elem1->GetText(), "111");
    EXPECT_STREQ(elem2->GetText(), "222");
}

// Test SetText uint64_t with power of 2
TEST_F(XMLElementSetTextUint64Test_240, SetTextUint64PowerOfTwo_240) {
    XMLElement* elem = createElement();
    elem->SetText(static_cast<uint64_t>(1ULL << 63)); // 9223372036854775808
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "9223372036854775808");
}

// Test round-trip: SetText uint64_t then QueryUnsigned64Text with max value
TEST_F(XMLElementSetTextUint64Test_240, RoundTripMaxValue_240) {
    XMLElement* elem = createElement();
    uint64_t original = UINT64_MAX;
    elem->SetText(original);
    
    uint64_t retrieved = 0;
    XMLError err = elem->QueryUnsigned64Text(&retrieved);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(retrieved, original);
}
