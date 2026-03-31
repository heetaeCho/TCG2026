#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementAttributeTest_227 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test: Attribute returns the value when the attribute exists and no value filter is provided
TEST_F(XMLElementAttributeTest_227, AttributeReturnsValueWhenExists_227) {
    const char* xml = "<root name=\"hello\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* result = root->Attribute("name");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello");
}

// Test: Attribute returns null when the attribute does not exist
TEST_F(XMLElementAttributeTest_227, AttributeReturnsNullWhenNotExists_227) {
    const char* xml = "<root name=\"hello\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* result = root->Attribute("nonexistent");
    EXPECT_EQ(result, nullptr);
}

// Test: Attribute returns value when value parameter is null (default)
TEST_F(XMLElementAttributeTest_227, AttributeReturnsValueWhenValueParamNull_227) {
    const char* xml = "<root attr=\"world\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* result = root->Attribute("attr", nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "world");
}

// Test: Attribute returns value when value parameter matches the attribute value
TEST_F(XMLElementAttributeTest_227, AttributeReturnsValueWhenValueMatches_227) {
    const char* xml = "<root color=\"red\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* result = root->Attribute("color", "red");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "red");
}

// Test: Attribute returns null when value parameter does not match
TEST_F(XMLElementAttributeTest_227, AttributeReturnsNullWhenValueMismatch_227) {
    const char* xml = "<root color=\"red\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* result = root->Attribute("color", "blue");
    EXPECT_EQ(result, nullptr);
}

// Test: Attribute with empty string value
TEST_F(XMLElementAttributeTest_227, AttributeWithEmptyStringValue_227) {
    const char* xml = "<root attr=\"\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* result = root->Attribute("attr");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test: Attribute with empty string value matching empty filter
TEST_F(XMLElementAttributeTest_227, AttributeEmptyValueMatchesEmptyFilter_227) {
    const char* xml = "<root attr=\"\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* result = root->Attribute("attr", "");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test: Attribute with empty string value not matching non-empty filter
TEST_F(XMLElementAttributeTest_227, AttributeEmptyValueDoesNotMatchNonEmptyFilter_227) {
    const char* xml = "<root attr=\"\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* result = root->Attribute("attr", "something");
    EXPECT_EQ(result, nullptr);
}

// Test: Multiple attributes - find specific one
TEST_F(XMLElementAttributeTest_227, AttributeMultipleAttributesFindSpecific_227) {
    const char* xml = "<root a=\"1\" b=\"2\" c=\"3\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* result = root->Attribute("b");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "2");
}

// Test: Multiple attributes - non-existent among existing
TEST_F(XMLElementAttributeTest_227, AttributeNonExistentAmongMultiple_227) {
    const char* xml = "<root a=\"1\" b=\"2\" c=\"3\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* result = root->Attribute("d");
    EXPECT_EQ(result, nullptr);
}

// Test: Element with no attributes
TEST_F(XMLElementAttributeTest_227, AttributeOnElementWithNoAttributes_227) {
    const char* xml = "<root/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* result = root->Attribute("anything");
    EXPECT_EQ(result, nullptr);
}

// Test: Attribute with special characters in value
TEST_F(XMLElementAttributeTest_227, AttributeWithSpecialCharacters_227) {
    const char* xml = "<root attr=\"hello &amp; world\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* result = root->Attribute("attr");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello & world");
}

// Test: Attribute match with special characters value filter
TEST_F(XMLElementAttributeTest_227, AttributeMatchWithSpecialCharactersFilter_227) {
    const char* xml = "<root attr=\"hello &amp; world\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* result = root->Attribute("attr", "hello & world");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello & world");
}

// Test: Attribute with numeric string value
TEST_F(XMLElementAttributeTest_227, AttributeWithNumericValue_227) {
    const char* xml = "<root count=\"42\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* result = root->Attribute("count", "42");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "42");
}

// Test: Attribute value filter with partial match should return null
TEST_F(XMLElementAttributeTest_227, AttributePartialMatchReturnsNull_227) {
    const char* xml = "<root name=\"hello\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* result = root->Attribute("name", "hell");
    EXPECT_EQ(result, nullptr);
}

// Test: Attribute is case-sensitive for name
TEST_F(XMLElementAttributeTest_227, AttributeNameIsCaseSensitive_227) {
    const char* xml = "<root Name=\"hello\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* result = root->Attribute("name");
    EXPECT_EQ(result, nullptr);
    
    const char* result2 = root->Attribute("Name");
    ASSERT_NE(result2, nullptr);
    EXPECT_STREQ(result2, "hello");
}

// Test: Attribute value filter is case-sensitive
TEST_F(XMLElementAttributeTest_227, AttributeValueFilterIsCaseSensitive_227) {
    const char* xml = "<root name=\"Hello\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* result = root->Attribute("name", "hello");
    EXPECT_EQ(result, nullptr);
    
    const char* result2 = root->Attribute("name", "Hello");
    ASSERT_NE(result2, nullptr);
    EXPECT_STREQ(result2, "Hello");
}

// Test: Attribute on child element
TEST_F(XMLElementAttributeTest_227, AttributeOnChildElement_227) {
    const char* xml = "<root><child attr=\"value\"/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    
    const char* result = child->Attribute("attr");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "value");
}

// Test: Attribute after SetAttribute
TEST_F(XMLElementAttributeTest_227, AttributeAfterSetAttribute_227) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    root->SetAttribute("key", "val");
    
    const char* result = root->Attribute("key");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "val");
}

// Test: Attribute after SetAttribute with value filter match
TEST_F(XMLElementAttributeTest_227, AttributeAfterSetAttributeWithMatchingFilter_227) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    root->SetAttribute("key", "val");
    
    const char* result = root->Attribute("key", "val");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "val");
}

// Test: Attribute after SetAttribute with value filter mismatch
TEST_F(XMLElementAttributeTest_227, AttributeAfterSetAttributeWithMismatchFilter_227) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    root->SetAttribute("key", "val");
    
    const char* result = root->Attribute("key", "other");
    EXPECT_EQ(result, nullptr);
}

// Test: Attribute after DeleteAttribute
TEST_F(XMLElementAttributeTest_227, AttributeAfterDeleteAttribute_227) {
    const char* xml = "<root attr=\"value\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    root->DeleteAttribute("attr");
    const char* result = root->Attribute("attr");
    EXPECT_EQ(result, nullptr);
}

// Test: Attribute with long value
TEST_F(XMLElementAttributeTest_227, AttributeWithLongValue_227) {
    std::string longValue(1000, 'x');
    std::string xml = "<root attr=\"" + longValue + "\"/>";
    doc.Parse(xml.c_str());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* result = root->Attribute("attr");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, longValue.c_str());
}

// Test: Attribute with spaces in value
TEST_F(XMLElementAttributeTest_227, AttributeWithSpacesInValue_227) {
    const char* xml = "<root attr=\"hello world\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* result = root->Attribute("attr", "hello world");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello world");
}
