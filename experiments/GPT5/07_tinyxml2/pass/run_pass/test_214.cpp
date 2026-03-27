// File: test_xmlattribute_queryunsigned64value_214.cpp

#include <gtest/gtest.h>
#include <cstdint>
#include <string>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace tinyxml2 {

class QueryUnsigned64ValueTest_214 : public ::testing::Test {
protected:
    static const XMLAttribute* FindAttrByName(const XMLElement* elem, const char* name) {
        if (!elem || !name) return nullptr;
        for (const XMLAttribute* a = elem->FirstAttribute(); a; a = a->Next()) {
            const char* n = a->Name();
            if (n && std::string(n) == name) {
                return a;
            }
        }
        return nullptr;
    }

    static const XMLAttribute* ParseAndGetAttr(const char* xml, const char* attrName,
                                              XMLDocument& doc, const XMLElement*& elemOut) {
        elemOut = nullptr;
        if (!xml) return nullptr;

        const XMLError err = doc.Parse(xml);
        if (err != XML_SUCCESS) return nullptr;

        const XMLElement* root = doc.FirstChildElement("root");
        elemOut = root;
        if (!root) return nullptr;

        return FindAttrByName(root, attrName);
    }
};

TEST_F(QueryUnsigned64ValueTest_214, ParsesZero_214) {
    XMLDocument doc;
    const XMLElement* elem = nullptr;
    const XMLAttribute* attr = ParseAndGetAttr(R"(<root a="0"/>)", "a", doc, elem);
    ASSERT_NE(attr, nullptr);

    uint64_t value = 123u;
    const XMLError err = attr->QueryUnsigned64Value(&value);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 0u);
}

TEST_F(QueryUnsigned64ValueTest_214, ParsesTypicalValue_214) {
    XMLDocument doc;
    const XMLElement* elem = nullptr;
    const XMLAttribute* attr = ParseAndGetAttr(R"(<root a="42"/>)", "a", doc, elem);
    ASSERT_NE(attr, nullptr);

    uint64_t value = 0u;
    const XMLError err = attr->QueryUnsigned64Value(&value);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 42u);
}

TEST_F(QueryUnsigned64ValueTest_214, ParsesLeadingZeros_214) {
    XMLDocument doc;
    const XMLElement* elem = nullptr;
    const XMLAttribute* attr = ParseAndGetAttr(R"(<root a="00000000123"/>)", "a", doc, elem);
    ASSERT_NE(attr, nullptr);

    uint64_t value = 0u;
    const XMLError err = attr->QueryUnsigned64Value(&value);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 123u);
}

TEST_F(QueryUnsigned64ValueTest_214, ParsesMaxUint64_214) {
    XMLDocument doc;
    const XMLElement* elem = nullptr;
    const XMLAttribute* attr =
        ParseAndGetAttr(R"(<root a="18446744073709551615"/>)", "a", doc, elem);
    ASSERT_NE(attr, nullptr);

    uint64_t value = 0u;
    const XMLError err = attr->QueryUnsigned64Value(&value);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, UINT64_MAX);
}

TEST_F(QueryUnsigned64ValueTest_214, AcceptsSurroundingWhitespaceIfSupported_214) {
    XMLDocument doc;
    const XMLElement* elem = nullptr;
    const XMLAttribute* attr = ParseAndGetAttr(R"(<root a="  77  "/>)", "a", doc, elem);
    ASSERT_NE(attr, nullptr);

    uint64_t value = 0u;
    const XMLError err = attr->QueryUnsigned64Value(&value);

    // Black-box friendly: only assert strongly if it succeeds.
    if (err == XML_SUCCESS) {
        EXPECT_EQ(value, 77u);
    } else {
        EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
    }
}

TEST_F(QueryUnsigned64ValueTest_214, RejectsNegativeNumber_214) {
    XMLDocument doc;
    const XMLElement* elem = nullptr;
    const XMLAttribute* attr = ParseAndGetAttr(R"(<root a="-1"/>)", "a", doc, elem);
    ASSERT_NE(attr, nullptr);

    uint64_t value = 0u;
    const XMLError err = attr->QueryUnsigned64Value(&value);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(QueryUnsigned64ValueTest_214, RejectsNonNumericText_214) {
    XMLDocument doc;
    const XMLElement* elem = nullptr;
    const XMLAttribute* attr = ParseAndGetAttr(R"(<root a="not_a_number"/>)", "a", doc, elem);
    ASSERT_NE(attr, nullptr);

    uint64_t value = 0u;
    const XMLError err = attr->QueryUnsigned64Value(&value);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(QueryUnsigned64ValueTest_214, RejectsFloatingPointText_214) {
    XMLDocument doc;
    const XMLElement* elem = nullptr;
    const XMLAttribute* attr = ParseAndGetAttr(R"(<root a="12.5"/>)", "a", doc, elem);
    ASSERT_NE(attr, nullptr);

    uint64_t value = 0u;
    const XMLError err = attr->QueryUnsigned64Value(&value);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(QueryUnsigned64ValueTest_214, RejectsEmptyString_214) {
    XMLDocument doc;
    const XMLElement* elem = nullptr;
    const XMLAttribute* attr = ParseAndGetAttr(R"(<root a=""/>)", "a", doc, elem);
    ASSERT_NE(attr, nullptr);

    uint64_t value = 0u;
    const XMLError err = attr->QueryUnsigned64Value(&value);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(QueryUnsigned64ValueTest_214, RejectsOverflowBeyondUint64Max_214) {
    XMLDocument doc;
    const XMLElement* elem = nullptr;
    const XMLAttribute* attr =
        ParseAndGetAttr(R"(<root a="18446744073709551616"/>)", "a", doc, elem);
    ASSERT_NE(attr, nullptr);

    uint64_t value = 0u;
    const XMLError err = attr->QueryUnsigned64Value(&value);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

}  // namespace tinyxml2
