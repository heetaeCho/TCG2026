// TEST_ID: 221
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

namespace {

const XMLAttribute* FindAttrByName(const XMLElement* elem, const char* name) {
    if (!elem || !name) return nullptr;
    for (const XMLAttribute* a = elem->FirstAttribute(); a; a = a->Next()) {
        const char* n = a->Name();
        if (n && std::strcmp(n, name) == 0) {
            return a;
        }
    }
    return nullptr;
}

class XMLAttributeSetAttributeInt64Test_221 : public ::testing::Test {
protected:
    XMLDocument doc_;
    XMLElement* elem_ = nullptr;

    void SetUp() override {
        elem_ = doc_.NewElement("root");
        ASSERT_NE(elem_, nullptr);
        doc_.InsertEndChild(elem_);
    }
};

}  // namespace

TEST_F(XMLAttributeSetAttributeInt64Test_221, SetZero_221) {
    ASSERT_NE(elem_, nullptr);

    elem_->SetAttribute("a", static_cast<int64_t>(0));

    const XMLAttribute* a = FindAttrByName(elem_, "a");
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Name(), "a");
    EXPECT_STREQ(a->Value(), "0");

    int64_t out = 123;
    EXPECT_EQ(a->QueryInt64Value(&out), XML_SUCCESS);
    EXPECT_EQ(out, 0);
}

TEST_F(XMLAttributeSetAttributeInt64Test_221, SetNegativeValue_221) {
    ASSERT_NE(elem_, nullptr);

    elem_->SetAttribute("neg", static_cast<int64_t>(-42));

    const XMLAttribute* a = FindAttrByName(elem_, "neg");
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Value(), "-42");

    int64_t out = 0;
    EXPECT_EQ(a->QueryInt64Value(&out), XML_SUCCESS);
    EXPECT_EQ(out, -42);
}

TEST_F(XMLAttributeSetAttributeInt64Test_221, SetInt64Max_221) {
    ASSERT_NE(elem_, nullptr);

    const int64_t v = INT64_C(9223372036854775807);
    elem_->SetAttribute("max", v);

    const XMLAttribute* a = FindAttrByName(elem_, "max");
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Value(), "9223372036854775807");

    int64_t out = 0;
    EXPECT_EQ(a->QueryInt64Value(&out), XML_SUCCESS);
    EXPECT_EQ(out, v);
}

TEST_F(XMLAttributeSetAttributeInt64Test_221, SetInt64Min_221) {
    ASSERT_NE(elem_, nullptr);

    const int64_t v = (INT64_C(-9223372036854775807) - INT64_C(1));
    elem_->SetAttribute("min", v);

    const XMLAttribute* a = FindAttrByName(elem_, "min");
    ASSERT_NE(a, nullptr);
    // Most implementations serialize int64 min as "-9223372036854775808".
    EXPECT_STREQ(a->Value(), "-9223372036854775808");

    int64_t out = 0;
    EXPECT_EQ(a->QueryInt64Value(&out), XML_SUCCESS);
    EXPECT_EQ(out, v);
}

TEST_F(XMLAttributeSetAttributeInt64Test_221, OverwritesExistingAttribute_221) {
    ASSERT_NE(elem_, nullptr);

    elem_->SetAttribute("a", static_cast<int64_t>(1));
    elem_->SetAttribute("a", static_cast<int64_t>(999));

    const XMLAttribute* a = FindAttrByName(elem_, "a");
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Value(), "999");

    int64_t out = 0;
    EXPECT_EQ(a->QueryInt64Value(&out), XML_SUCCESS);
    EXPECT_EQ(out, 999);
}

TEST_F(XMLAttributeSetAttributeInt64Test_221, QueryInt64WithNullOutParamReturnsError_221) {
    ASSERT_NE(elem_, nullptr);

    elem_->SetAttribute("a", static_cast<int64_t>(7));
    const XMLAttribute* a = FindAttrByName(elem_, "a");
    ASSERT_NE(a, nullptr);

    // Observable error behavior: must not report success when output pointer is null.
    EXPECT_NE(a->QueryInt64Value(nullptr), XML_SUCCESS);
}
