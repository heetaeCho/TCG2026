#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementFindAttributeTest_226 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test FindAttribute returns correct attribute when it exists
TEST_F(XMLElementFindAttributeTest_226, FindExistingAttribute_226) {
    const char* xml = "<root attr1=\"value1\" attr2=\"value2\" attr3=\"value3\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLAttribute* attr = root->FindAttribute("attr2");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "attr2");
    EXPECT_STREQ(attr->Value(), "value2");
}

// Test FindAttribute returns nullptr when attribute does not exist
TEST_F(XMLElementFindAttributeTest_226, FindNonExistingAttribute_226) {
    const char* xml = "<root attr1=\"value1\" attr2=\"value2\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLAttribute* attr = root->FindAttribute("nonexistent");
    EXPECT_EQ(attr, nullptr);
}

// Test FindAttribute on element with no attributes
TEST_F(XMLElementFindAttributeTest_226, FindAttributeOnElementWithNoAttributes_226) {
    const char* xml = "<root/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLAttribute* attr = root->FindAttribute("anyattr");
    EXPECT_EQ(attr, nullptr);
}

// Test FindAttribute returns first attribute
TEST_F(XMLElementFindAttributeTest_226, FindFirstAttribute_226) {
    const char* xml = "<root first=\"1\" second=\"2\" third=\"3\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLAttribute* attr = root->FindAttribute("first");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "first");
    EXPECT_STREQ(attr->Value(), "1");
}

// Test FindAttribute returns last attribute
TEST_F(XMLElementFindAttributeTest_226, FindLastAttribute_226) {
    const char* xml = "<root first=\"1\" second=\"2\" third=\"3\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLAttribute* attr = root->FindAttribute("third");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "third");
    EXPECT_STREQ(attr->Value(), "3");
}

// Test FindAttribute is case-sensitive
TEST_F(XMLElementFindAttributeTest_226, FindAttributeCaseSensitive_226) {
    const char* xml = "<root MyAttr=\"value\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLAttribute* attr = root->FindAttribute("myattr");
    EXPECT_EQ(attr, nullptr);
    
    const XMLAttribute* attr2 = root->FindAttribute("MyAttr");
    ASSERT_NE(attr2, nullptr);
    EXPECT_STREQ(attr2->Value(), "value");
}

// Test FindAttribute with single attribute element
TEST_F(XMLElementFindAttributeTest_226, FindAttributeSingleAttribute_226) {
    const char* xml = "<root only=\"lonely\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLAttribute* attr = root->FindAttribute("only");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "only");
    EXPECT_STREQ(attr->Value(), "lonely");
}

// Test FindAttribute with empty string name
TEST_F(XMLElementFindAttributeTest_226, FindAttributeEmptyName_226) {
    const char* xml = "<root attr=\"value\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLAttribute* attr = root->FindAttribute("");
    EXPECT_EQ(attr, nullptr);
}

// Test FindAttribute after SetAttribute creates the attribute
TEST_F(XMLElementFindAttributeTest_226, FindAttributeAfterSetAttribute_226) {
    const char* xml = "<root/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    root->SetAttribute("dynamic", "added");
    
    const XMLAttribute* attr = root->FindAttribute("dynamic");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "dynamic");
    EXPECT_STREQ(attr->Value(), "added");
}

// Test FindAttribute after DeleteAttribute
TEST_F(XMLElementFindAttributeTest_226, FindAttributeAfterDeleteAttribute_226) {
    const char* xml = "<root attr1=\"v1\" attr2=\"v2\" attr3=\"v3\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    root->DeleteAttribute("attr2");
    
    const XMLAttribute* attr = root->FindAttribute("attr2");
    EXPECT_EQ(attr, nullptr);
    
    // Other attributes should still be found
    const XMLAttribute* attr1 = root->FindAttribute("attr1");
    ASSERT_NE(attr1, nullptr);
    EXPECT_STREQ(attr1->Value(), "v1");
    
    const XMLAttribute* attr3 = root->FindAttribute("attr3");
    ASSERT_NE(attr3, nullptr);
    EXPECT_STREQ(attr3->Value(), "v3");
}

// Test FindAttribute with attribute that has special characters in value
TEST_F(XMLElementFindAttributeTest_226, FindAttributeSpecialCharValue_226) {
    const char* xml = "<root special=\"a&amp;b\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLAttribute* attr = root->FindAttribute("special");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "special");
    EXPECT_STREQ(attr->Value(), "a&b");
}

// Test FindAttribute with many attributes
TEST_F(XMLElementFindAttributeTest_226, FindAttributeWithManyAttributes_226) {
    const char* xml = "<root a1=\"1\" a2=\"2\" a3=\"3\" a4=\"4\" a5=\"5\" "
                       "a6=\"6\" a7=\"7\" a8=\"8\" a9=\"9\" a10=\"10\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLAttribute* attr = root->FindAttribute("a10");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "10");
    
    const XMLAttribute* attr5 = root->FindAttribute("a5");
    ASSERT_NE(attr5, nullptr);
    EXPECT_STREQ(attr5->Value(), "5");
}

// Test FindAttribute with numeric attribute name
TEST_F(XMLElementFindAttributeTest_226, FindAttributePartialNameMatch_226) {
    const char* xml = "<root attribute=\"full\" attr=\"partial\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "partial");
    
    const XMLAttribute* attr2 = root->FindAttribute("attribute");
    ASSERT_NE(attr2, nullptr);
    EXPECT_STREQ(attr2->Value(), "full");
}

// Test FindAttribute on a child element
TEST_F(XMLElementFindAttributeTest_226, FindAttributeOnChildElement_226) {
    const char* xml = "<root><child myattr=\"childvalue\"/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    
    const XMLAttribute* attr = child->FindAttribute("myattr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "childvalue");
    
    // Root should not have the child's attribute
    const XMLAttribute* rootAttr = root->FindAttribute("myattr");
    EXPECT_EQ(rootAttr, nullptr);
}

// Test FindAttribute with attribute value updated via SetAttribute
TEST_F(XMLElementFindAttributeTest_226, FindAttributeAfterValueUpdate_226) {
    const char* xml = "<root attr=\"original\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    root->SetAttribute("attr", "updated");
    
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "updated");
}

// Test FindAttribute with integer attribute
TEST_F(XMLElementFindAttributeTest_226, FindAttributeIntegerValue_226) {
    const char* xml = "<root/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    root->SetAttribute("intattr", 42);
    
    const XMLAttribute* attr = root->FindAttribute("intattr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 42);
}

// Test FindAttribute with boolean attribute
TEST_F(XMLElementFindAttributeTest_226, FindAttributeBooleanValue_226) {
    const char* xml = "<root flag=\"true\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLAttribute* attr = root->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->BoolValue(), true);
}

// Test FindAttribute with empty attribute value
TEST_F(XMLElementFindAttributeTest_226, FindAttributeEmptyValue_226) {
    const char* xml = "<root emptyattr=\"\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLAttribute* attr = root->FindAttribute("emptyattr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "");
}
