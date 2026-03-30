// File: test_xmlattribute_setattribute_uint64_222.cpp
#include <gtest/gtest.h>

#include <cinttypes>
#include <cstdint>
#include <limits>
#include <string>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLAttributeSetAttributeUint64Test_222 : public ::testing::Test {
protected:
    XMLDocument doc_;
    XMLElement* elem_ = nullptr;
    XMLAttribute* attr_ = nullptr;

    void SetUp() override {
        // Create an element with an attribute so we can obtain a real XMLAttribute instance.
        // (XMLAttribute ctor/dtor are not publicly accessible.)
        elem_ = doc_.NewElement("root");
        ASSERT_NE(elem_, nullptr);
        doc_.InsertEndChild(elem_);

        // Seed attribute; value will be overwritten in each test.
        elem_->SetAttribute("u", static_cast<uint64_t>(0));

        attr_ = elem_->FindAttribute("u");
        ASSERT_NE(attr_, nullptr);
        ASSERT_STREQ(attr_->Name(), "u");
        ASSERT_NE(attr_->Value(), nullptr);
    }

    static std::string ToDec(uint64_t v) {
        char buf[64] = {};
        std::snprintf(buf, sizeof(buf), "%" PRIu64, v);
        return std::string(buf);
    }
};

}  // namespace

TEST_F(XMLAttributeSetAttributeUint64Test_222, SetZero_222) {
    const uint64_t v = 0;
    attr_->SetAttribute(v);

    EXPECT_STREQ(attr_->Value(), ToDec(v).c_str());

    uint64_t out = 123;
    EXPECT_EQ(attr_->QueryUnsigned64Value(&out), XML_SUCCESS);
    EXPECT_EQ(out, v);

    EXPECT_EQ(attr_->Unsigned64Value(), v);
}

TEST_F(XMLAttributeSetAttributeUint64Test_222, SetOne_222) {
    const uint64_t v = 1;
    attr_->SetAttribute(v);

    EXPECT_STREQ(attr_->Value(), ToDec(v).c_str());

    uint64_t out = 0;
    EXPECT_EQ(attr_->QueryUnsigned64Value(&out), XML_SUCCESS);
    EXPECT_EQ(out, v);

    EXPECT_EQ(attr_->Unsigned64Value(), v);
}

TEST_F(XMLAttributeSetAttributeUint64Test_222, SetLargeValue_222) {
    const uint64_t v = 4294967296ULL;  // 2^32, beyond 32-bit unsigned.
    attr_->SetAttribute(v);

    EXPECT_STREQ(attr_->Value(), ToDec(v).c_str());

    uint64_t out = 0;
    EXPECT_EQ(attr_->QueryUnsigned64Value(&out), XML_SUCCESS);
    EXPECT_EQ(out, v);

    EXPECT_EQ(attr_->Unsigned64Value(), v);
}

TEST_F(XMLAttributeSetAttributeUint64Test_222, SetMaxUint64_222) {
    const uint64_t v = std::numeric_limits<uint64_t>::max();
    attr_->SetAttribute(v);

    EXPECT_STREQ(attr_->Value(), ToDec(v).c_str());

    uint64_t out = 0;
    EXPECT_EQ(attr_->QueryUnsigned64Value(&out), XML_SUCCESS);
    EXPECT_EQ(out, v);

    EXPECT_EQ(attr_->Unsigned64Value(), v);
}

TEST_F(XMLAttributeSetAttributeUint64Test_222, RepeatedSetUpdatesValue_222) {
    const uint64_t first = 42;
    const uint64_t second = 999999999999ULL;

    attr_->SetAttribute(first);
    EXPECT_STREQ(attr_->Value(), ToDec(first).c_str());
    EXPECT_EQ(attr_->Unsigned64Value(), first);

    attr_->SetAttribute(second);
    EXPECT_STREQ(attr_->Value(), ToDec(second).c_str());
    EXPECT_EQ(attr_->Unsigned64Value(), second);

    // Name should remain unchanged.
    EXPECT_STREQ(attr_->Name(), "u");
}

TEST_F(XMLAttributeSetAttributeUint64Test_222, QueryInt64DetectsOverflowForUint64Max_222) {
    // Observable error case through the public conversion API:
    // A too-large unsigned value should not convert to int64 successfully.
    const uint64_t v = std::numeric_limits<uint64_t>::max();
    attr_->SetAttribute(v);

    int64_t out = 0;
    const XMLError err = attr_->QueryInt64Value(&out);

    // We only assert "not success" to avoid guessing the exact error enum.
    EXPECT_NE(err, XML_SUCCESS);
}
