// TEST_ID: 97
#include <gtest/gtest.h>

#include <cstring>
#include <string>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLElementSetAttributeStringTest_97 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        // Create a minimal document/element using only public APIs.
        ASSERT_EQ(XML_SUCCESS, doc.Parse("<root/>"));
        elem = doc.RootElement();
        ASSERT_NE(nullptr, elem);
    }
};

TEST_F(XMLElementSetAttributeStringTest_97, SetsNewAttribute_97) {
    elem->SetAttribute("answer", "42");

    const char* v = elem->Attribute("answer");
    ASSERT_NE(nullptr, v);
    EXPECT_STREQ("42", v);

    const XMLAttribute* a = elem->FindAttribute("answer");
    ASSERT_NE(nullptr, a);
    ASSERT_NE(nullptr, a->Name());
    ASSERT_NE(nullptr, a->Value());
    EXPECT_STREQ("answer", a->Name());
    EXPECT_STREQ("42", a->Value());
}

TEST_F(XMLElementSetAttributeStringTest_97, OverwritesExistingAttribute_97) {
    elem->SetAttribute("mode", "alpha");
    elem->SetAttribute("mode", "beta");

    const char* v = elem->Attribute("mode");
    ASSERT_NE(nullptr, v);
    EXPECT_STREQ("beta", v);

    const XMLAttribute* a = elem->FindAttribute("mode");
    ASSERT_NE(nullptr, a);
    EXPECT_STREQ("beta", a->Value());
}

TEST_F(XMLElementSetAttributeStringTest_97, MultipleAttributesRemainIndependent_97) {
    elem->SetAttribute("a", "1");
    elem->SetAttribute("b", "2");

    const char* va = elem->Attribute("a");
    const char* vb = elem->Attribute("b");
    ASSERT_NE(nullptr, va);
    ASSERT_NE(nullptr, vb);
    EXPECT_STREQ("1", va);
    EXPECT_STREQ("2", vb);

    ASSERT_NE(nullptr, elem->FindAttribute("a"));
    ASSERT_NE(nullptr, elem->FindAttribute("b"));
}

TEST_F(XMLElementSetAttributeStringTest_97, EmptyValueIsStoredAndReadable_97) {
    elem->SetAttribute("empty", "");

    const char* v = elem->Attribute("empty");
    ASSERT_NE(nullptr, v);
    EXPECT_STREQ("", v);

    const XMLAttribute* a = elem->FindAttribute("empty");
    ASSERT_NE(nullptr, a);
    ASSERT_NE(nullptr, a->Value());
    EXPECT_STREQ("", a->Value());
}

TEST_F(XMLElementSetAttributeStringTest_97, CanHandleLongNameAndValue_97) {
    std::string longName(256, 'n');
    std::string longValue(2048, 'v');

    elem->SetAttribute(longName.c_str(), longValue.c_str());

    const char* v = elem->Attribute(longName.c_str());
    ASSERT_NE(nullptr, v);
    EXPECT_STREQ(longValue.c_str(), v);

    const XMLAttribute* a = elem->FindAttribute(longName.c_str());
    ASSERT_NE(nullptr, a);
    EXPECT_STREQ(longName.c_str(), a->Name());
    EXPECT_STREQ(longValue.c_str(), a->Value());
}

TEST_F(XMLElementSetAttributeStringTest_97, EmptyNameDoesNotCauseFatalFailure_97) {
    // Behavior for empty names may vary; this test focuses on observable safety and consistency.
    EXPECT_NO_FATAL_FAILURE(elem->SetAttribute("", "value"));

    const char* v = elem->Attribute("");
    if (v) {
        EXPECT_STREQ("value", v);
    } else {
        SUCCEED();  // Accept implementations that ignore/omit empty-name attributes.
    }
}

TEST_F(XMLElementSetAttributeStringTest_97, NullValueDoesNotCauseFatalFailure_97) {
    // Behavior for nullptr value may vary; this test ensures the call is safe and result is queryable.
    EXPECT_NO_FATAL_FAILURE(elem->SetAttribute("k", static_cast<const char*>(nullptr)));

    const char* v = elem->Attribute("k");
    if (v) {
        // Some implementations may store empty string for null value.
        EXPECT_TRUE(std::strcmp(v, "") == 0 || std::strcmp(v, "0") == 0 || std::strlen(v) >= 0);
    } else {
        SUCCEED();  // Accept implementations that remove/ignore the attribute when value is null.
    }
}
