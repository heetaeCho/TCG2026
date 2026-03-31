#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementQueryBoolAttributeTest_85 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test QueryBoolAttribute returns XML_NO_ATTRIBUTE when attribute doesn't exist
TEST_F(XMLElementQueryBoolAttributeTest_85, NonExistentAttribute_ReturnsNoAttribute_85) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    bool value = false;
    XMLError result = root->QueryBoolAttribute("nonexistent", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
}

// Test QueryBoolAttribute with "true" string value
TEST_F(XMLElementQueryBoolAttributeTest_85, TrueStringAttribute_ReturnsSuccess_85) {
    doc.Parse("<root flag=\"true\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    bool value = false;
    XMLError result = root->QueryBoolAttribute("flag", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_TRUE(value);
}

// Test QueryBoolAttribute with "false" string value
TEST_F(XMLElementQueryBoolAttributeTest_85, FalseStringAttribute_ReturnsSuccess_85) {
    doc.Parse("<root flag=\"false\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    bool value = true;
    XMLError result = root->QueryBoolAttribute("flag", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FALSE(value);
}

// Test QueryBoolAttribute with "1" value (should be true)
TEST_F(XMLElementQueryBoolAttributeTest_85, OneValue_ReturnsTrueSuccess_85) {
    doc.Parse("<root flag=\"1\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    bool value = false;
    XMLError result = root->QueryBoolAttribute("flag", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_TRUE(value);
}

// Test QueryBoolAttribute with "0" value (should be false)
TEST_F(XMLElementQueryBoolAttributeTest_85, ZeroValue_ReturnsFalseSuccess_85) {
    doc.Parse("<root flag=\"0\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    bool value = true;
    XMLError result = root->QueryBoolAttribute("flag", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FALSE(value);
}

// Test QueryBoolAttribute with non-boolean string returns wrong attribute type
TEST_F(XMLElementQueryBoolAttributeTest_85, NonBooleanString_ReturnsWrongType_85) {
    doc.Parse("<root flag=\"notabool\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    bool value = false;
    XMLError result = root->QueryBoolAttribute("flag", &value);
    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test QueryBoolAttribute with numeric non-bool value
TEST_F(XMLElementQueryBoolAttributeTest_85, NumericNonBoolValue_ReturnsWrongType_85) {
    doc.Parse("<root flag=\"42\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    bool value = false;
    XMLError result = root->QueryBoolAttribute("flag", &value);
    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test QueryBoolAttribute with empty attribute value
TEST_F(XMLElementQueryBoolAttributeTest_85, EmptyAttributeValue_ReturnsWrongType_85) {
    doc.Parse("<root flag=\"\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    bool value = false;
    XMLError result = root->QueryBoolAttribute("flag", &value);
    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test QueryBoolAttribute with multiple attributes, querying existing one
TEST_F(XMLElementQueryBoolAttributeTest_85, MultipleAttributes_QueryExisting_85) {
    doc.Parse("<root a=\"hello\" flag=\"true\" b=\"world\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    bool value = false;
    XMLError result = root->QueryBoolAttribute("flag", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_TRUE(value);
}

// Test QueryBoolAttribute with multiple attributes, querying non-existing one
TEST_F(XMLElementQueryBoolAttributeTest_85, MultipleAttributes_QueryNonExisting_85) {
    doc.Parse("<root a=\"hello\" b=\"world\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    bool value = false;
    XMLError result = root->QueryBoolAttribute("flag", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
}

// Test QueryBoolAttribute on element with no attributes at all
TEST_F(XMLElementQueryBoolAttributeTest_85, NoAttributes_ReturnsNoAttribute_85) {
    doc.Parse("<root></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    bool value = true;
    XMLError result = root->QueryBoolAttribute("flag", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
}

// Test QueryBoolAttribute after setting attribute to true via SetAttribute
TEST_F(XMLElementQueryBoolAttributeTest_85, SetAttributeTrueThenQuery_85) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    root->SetAttribute("flag", true);
    
    bool value = false;
    XMLError result = root->QueryBoolAttribute("flag", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_TRUE(value);
}

// Test QueryBoolAttribute after setting attribute to false via SetAttribute
TEST_F(XMLElementQueryBoolAttributeTest_85, SetAttributeFalseThenQuery_85) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    root->SetAttribute("flag", false);
    
    bool value = true;
    XMLError result = root->QueryBoolAttribute("flag", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FALSE(value);
}

// Test that attribute name matching is case-sensitive
TEST_F(XMLElementQueryBoolAttributeTest_85, CaseSensitiveAttributeName_85) {
    doc.Parse("<root Flag=\"true\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    bool value = false;
    // Querying with lowercase "flag" should not find "Flag"
    XMLError result = root->QueryBoolAttribute("flag", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
    
    // Querying with correct case should work
    result = root->QueryBoolAttribute("Flag", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_TRUE(value);
}

// Test QueryBoolAttribute with float value in attribute (wrong type)
TEST_F(XMLElementQueryBoolAttributeTest_85, FloatValue_ReturnsWrongType_85) {
    doc.Parse("<root flag=\"3.14\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    bool value = false;
    XMLError result = root->QueryBoolAttribute("flag", &value);
    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test BoolAttribute convenience function with default value when attribute exists
TEST_F(XMLElementQueryBoolAttributeTest_85, BoolAttributeConvenience_Exists_85) {
    doc.Parse("<root flag=\"true\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    bool value = root->BoolAttribute("flag", false);
    EXPECT_TRUE(value);
}

// Test BoolAttribute convenience function with default value when attribute doesn't exist
TEST_F(XMLElementQueryBoolAttributeTest_85, BoolAttributeConvenience_NotExists_85) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    bool value = root->BoolAttribute("flag", true);
    EXPECT_TRUE(value);
    
    value = root->BoolAttribute("flag", false);
    EXPECT_FALSE(value);
}

// Test QueryBoolAttribute on a child element
TEST_F(XMLElementQueryBoolAttributeTest_85, ChildElement_QueryBoolAttribute_85) {
    doc.Parse("<root><child active=\"false\"/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    
    bool value = true;
    XMLError result = child->QueryBoolAttribute("active", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FALSE(value);
}

// Test QueryBoolAttribute after deleting the attribute
TEST_F(XMLElementQueryBoolAttributeTest_85, DeletedAttribute_ReturnsNoAttribute_85) {
    doc.Parse("<root flag=\"true\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    // First verify it exists
    bool value = false;
    XMLError result = root->QueryBoolAttribute("flag", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_TRUE(value);
    
    // Delete and verify it's gone
    root->DeleteAttribute("flag");
    result = root->QueryBoolAttribute("flag", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
}
