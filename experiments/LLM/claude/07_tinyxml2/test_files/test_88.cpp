#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementQueryStringAttribute_88 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }
};

// Test QueryStringAttribute returns XML_SUCCESS when attribute exists
TEST_F(XMLElementQueryStringAttribute_88, ReturnsSuccessWhenAttributeExists_88) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    const char* value = nullptr;
    XMLError result = element->QueryStringAttribute("name", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_STREQ(value, "hello");
}

// Test QueryStringAttribute returns XML_NO_ATTRIBUTE when attribute does not exist
TEST_F(XMLElementQueryStringAttribute_88, ReturnsNoAttributeWhenMissing_88) {
    doc.Parse("<root name=\"hello\"/>");
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    const char* value = nullptr;
    XMLError result = element->QueryStringAttribute("nonexistent", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
    EXPECT_EQ(value, nullptr);
}

// Test QueryStringAttribute with empty string attribute value
TEST_F(XMLElementQueryStringAttribute_88, ReturnsEmptyStringValue_88) {
    doc.Parse("<root attr=\"\"/>");
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    const char* value = nullptr;
    XMLError result = element->QueryStringAttribute("attr", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_STREQ(value, "");
}

// Test QueryStringAttribute with multiple attributes, querying the first
TEST_F(XMLElementQueryStringAttribute_88, FindsFirstAttribute_88) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    const char* value = nullptr;
    XMLError result = element->QueryStringAttribute("a", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_STREQ(value, "1");
}

// Test QueryStringAttribute with multiple attributes, querying the last
TEST_F(XMLElementQueryStringAttribute_88, FindsLastAttribute_88) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    const char* value = nullptr;
    XMLError result = element->QueryStringAttribute("c", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_STREQ(value, "3");
}

// Test QueryStringAttribute with multiple attributes, querying a middle one
TEST_F(XMLElementQueryStringAttribute_88, FindsMiddleAttribute_88) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    const char* value = nullptr;
    XMLError result = element->QueryStringAttribute("b", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_STREQ(value, "2");
}

// Test QueryStringAttribute on element with no attributes
TEST_F(XMLElementQueryStringAttribute_88, NoAttributesReturnsNoAttribute_88) {
    doc.Parse("<root/>");
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    const char* value = nullptr;
    XMLError result = element->QueryStringAttribute("anything", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
}

// Test QueryStringAttribute with attribute value containing spaces
TEST_F(XMLElementQueryStringAttribute_88, AttributeValueWithSpaces_88) {
    doc.Parse("<root desc=\"hello world\"/>");
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    const char* value = nullptr;
    XMLError result = element->QueryStringAttribute("desc", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_STREQ(value, "hello world");
}

// Test QueryStringAttribute with attribute value containing special characters
TEST_F(XMLElementQueryStringAttribute_88, AttributeValueWithSpecialChars_88) {
    doc.Parse("<root data=\"&amp;&lt;&gt;\"/>");
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    const char* value = nullptr;
    XMLError result = element->QueryStringAttribute("data", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_STREQ(value, "&<>");
}

// Test QueryStringAttribute with numeric attribute value (still retrieved as string)
TEST_F(XMLElementQueryStringAttribute_88, NumericValueReturnedAsString_88) {
    doc.Parse("<root count=\"42\"/>");
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    const char* value = nullptr;
    XMLError result = element->QueryStringAttribute("count", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_STREQ(value, "42");
}

// Test QueryStringAttribute is case-sensitive
TEST_F(XMLElementQueryStringAttribute_88, CaseSensitiveAttributeName_88) {
    doc.Parse("<root Name=\"upper\" name=\"lower\"/>");
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    const char* value = nullptr;
    XMLError result = element->QueryStringAttribute("Name", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_STREQ(value, "upper");

    result = element->QueryStringAttribute("name", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_STREQ(value, "lower");

    result = element->QueryStringAttribute("NAME", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
}

// Test QueryStringAttribute after setting attribute programmatically
TEST_F(XMLElementQueryStringAttribute_88, AfterSetAttribute_88) {
    doc.Parse("<root/>");
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    element->SetAttribute("key", "value");

    const char* value = nullptr;
    XMLError result = element->QueryStringAttribute("key", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_STREQ(value, "value");
}

// Test QueryStringAttribute after deleting attribute
TEST_F(XMLElementQueryStringAttribute_88, AfterDeleteAttribute_88) {
    doc.Parse("<root key=\"value\"/>");
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    element->DeleteAttribute("key");

    const char* value = nullptr;
    XMLError result = element->QueryStringAttribute("key", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
}

// Test QueryStringAttribute after modifying attribute value
TEST_F(XMLElementQueryStringAttribute_88, AfterModifyAttribute_88) {
    doc.Parse("<root key=\"old\"/>");
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    element->SetAttribute("key", "new");

    const char* value = nullptr;
    XMLError result = element->QueryStringAttribute("key", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_STREQ(value, "new");
}

// Test QueryStringAttribute with attribute containing Unicode-like content
TEST_F(XMLElementQueryStringAttribute_88, AttributeWithUTF8Content_88) {
    doc.Parse("<root text=\"café\"/>");
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    const char* value = nullptr;
    XMLError result = element->QueryStringAttribute("text", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_STREQ(value, "café");
}

// Test QueryStringAttribute on child element
TEST_F(XMLElementQueryStringAttribute_88, ChildElementAttribute_88) {
    doc.Parse("<root><child attr=\"childval\"/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);

    const char* value = nullptr;
    XMLError result = child->QueryStringAttribute("attr", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_STREQ(value, "childval");

    // Root should not have the child's attribute
    result = root->QueryStringAttribute("attr", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
}

// Test QueryStringAttribute with attribute set to integer value (via SetAttribute(int))
TEST_F(XMLElementQueryStringAttribute_88, IntAttributeQueriedAsString_88) {
    doc.Parse("<root/>");
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    element->SetAttribute("num", 123);

    const char* value = nullptr;
    XMLError result = element->QueryStringAttribute("num", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_STREQ(value, "123");
}

// Test QueryStringAttribute with boolean attribute set via SetAttribute(bool)
TEST_F(XMLElementQueryStringAttribute_88, BoolAttributeQueriedAsString_88) {
    doc.Parse("<root/>");
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    element->SetAttribute("flag", true);

    const char* value = nullptr;
    XMLError result = element->QueryStringAttribute("flag", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    // tinyxml2 typically outputs "true" for bool
    EXPECT_STREQ(value, "true");
}

// Test QueryStringAttribute with very long attribute value
TEST_F(XMLElementQueryStringAttribute_88, LongAttributeValue_88) {
    std::string longVal(1000, 'x');
    std::string xml = "<root longattr=\"" + longVal + "\"/>";
    doc.Parse(xml.c_str());
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    const char* value = nullptr;
    XMLError result = element->QueryStringAttribute("longattr", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_STREQ(value, longVal.c_str());
}
