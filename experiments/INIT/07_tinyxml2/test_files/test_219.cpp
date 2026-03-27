// TEST_ID: 219
// File: tinyxml2_xmlattribute_setattribute_int_test_219.cpp

#include <gtest/gtest.h>
#include <climits>
#include <cstring>
#include <string>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLAttributeSetAttributeIntTest_219 : public ::testing::Test {
protected:
    XMLDocument doc_;
    XMLElement* elem_ = nullptr;

    void SetUp() override {
        elem_ = doc_.NewElement("root");
        ASSERT_NE(elem_, nullptr);
        doc_.InsertEndChild(elem_);
        // Ensure the attribute exists so we can retrieve the underlying XMLAttribute object.
        elem_->SetAttribute("a", 0);
    }

    XMLAttribute* GetMutableAttribute(const char* name) {
        ASSERT_NE(elem_, nullptr);
        const XMLAttribute* attr = elem_->FindAttribute(name);
        ASSERT_NE(attr, nullptr);
        // We only use non-const access to call the non-const SetAttribute overload under test.
        return const_cast<XMLAttribute*>(attr);
    }

    static std::string ToStdStringSafe(const char* s) {
        return s ? std::string(s) : std::string();
    }
};

TEST_F(XMLAttributeSetAttributeIntTest_219, SetAttributeZero_219) {
    XMLAttribute* attr = GetMutableAttribute("a");
    attr->SetAttribute(0);

    const char* value = attr->Value();
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value, "0");

    int parsed = 12345;
    EXPECT_EQ(attr->QueryIntValue(&parsed), XML_SUCCESS);
    EXPECT_EQ(parsed, 0);
    EXPECT_EQ(attr->IntValue(), 0);
}

TEST_F(XMLAttributeSetAttributeIntTest_219, SetAttributePositive_219) {
    XMLAttribute* attr = GetMutableAttribute("a");
    attr->SetAttribute(42);

    const char* value = attr->Value();
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value, "42");

    int parsed = 0;
    EXPECT_EQ(attr->QueryIntValue(&parsed), XML_SUCCESS);
    EXPECT_EQ(parsed, 42);
    EXPECT_EQ(attr->IntValue(), 42);
}

TEST_F(XMLAttributeSetAttributeIntTest_219, SetAttributeNegative_219) {
    XMLAttribute* attr = GetMutableAttribute("a");
    attr->SetAttribute(-7);

    const char* value = attr->Value();
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value, "-7");

    int parsed = 0;
    EXPECT_EQ(attr->QueryIntValue(&parsed), XML_SUCCESS);
    EXPECT_EQ(parsed, -7);
    EXPECT_EQ(attr->IntValue(), -7);
}

TEST_F(XMLAttributeSetAttributeIntTest_219, SetAttributeIntMax_219) {
    XMLAttribute* attr = GetMutableAttribute("a");
    attr->SetAttribute(INT_MAX);

    const char* value = attr->Value();
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value, std::to_string(INT_MAX).c_str());

    int parsed = 0;
    EXPECT_EQ(attr->QueryIntValue(&parsed), XML_SUCCESS);
    EXPECT_EQ(parsed, INT_MAX);
    EXPECT_EQ(attr->IntValue(), INT_MAX);
}

TEST_F(XMLAttributeSetAttributeIntTest_219, SetAttributeIntMin_219) {
    XMLAttribute* attr = GetMutableAttribute("a");
    attr->SetAttribute(INT_MIN);

    const char* value = attr->Value();
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value, std::to_string(INT_MIN).c_str());

    int parsed = 0;
    EXPECT_EQ(attr->QueryIntValue(&parsed), XML_SUCCESS);
    EXPECT_EQ(parsed, INT_MIN);
    EXPECT_EQ(attr->IntValue(), INT_MIN);
}

TEST_F(XMLAttributeSetAttributeIntTest_219, SetAttributeOverwritesPreviousValue_219) {
    XMLAttribute* attr = GetMutableAttribute("a");

    attr->SetAttribute(1);
    std::string first = ToStdStringSafe(attr->Value());
    ASSERT_FALSE(first.empty());

    attr->SetAttribute(999);
    std::string second = ToStdStringSafe(attr->Value());
    ASSERT_FALSE(second.empty());

    EXPECT_NE(first, second);
    EXPECT_EQ(second, "999");

    int parsed = 0;
    EXPECT_EQ(attr->QueryIntValue(&parsed), XML_SUCCESS);
    EXPECT_EQ(parsed, 999);
    EXPECT_EQ(attr->IntValue(), 999);
}

TEST_F(XMLAttributeSetAttributeIntTest_219, SetAttributeDoesNotAffectAttributeName_219) {
    XMLAttribute* attr = GetMutableAttribute("a");

    const char* name_before = attr->Name();
    ASSERT_NE(name_before, nullptr);
    EXPECT_STREQ(name_before, "a");

    attr->SetAttribute(123);

    const char* name_after = attr->Name();
    ASSERT_NE(name_after, nullptr);
    EXPECT_STREQ(name_after, "a");
}

}  // namespace
