#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementSetAttributeBoolTest_102 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* element;

    void SetUp() override {
        element = doc.NewElement("TestElement");
        doc.InsertFirstChild(element);
    }
};

// Test setting a bool attribute to true
TEST_F(XMLElementSetAttributeBoolTest_102, SetAttributeBoolTrue_102) {
    element->SetAttribute("flag", true);
    bool value = false;
    XMLError err = element->QueryBoolAttribute("flag", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

// Test setting a bool attribute to false
TEST_F(XMLElementSetAttributeBoolTest_102, SetAttributeBoolFalse_102) {
    element->SetAttribute("flag", false);
    bool value = true;
    XMLError err = element->QueryBoolAttribute("flag", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(value);
}

// Test that BoolAttribute returns the correct value for true
TEST_F(XMLElementSetAttributeBoolTest_102, BoolAttributeReturnsTrue_102) {
    element->SetAttribute("enabled", true);
    bool result = element->BoolAttribute("enabled", false);
    EXPECT_TRUE(result);
}

// Test that BoolAttribute returns the correct value for false
TEST_F(XMLElementSetAttributeBoolTest_102, BoolAttributeReturnsFalse_102) {
    element->SetAttribute("enabled", false);
    bool result = element->BoolAttribute("enabled", true);
    EXPECT_FALSE(result);
}

// Test that BoolAttribute returns default when attribute does not exist
TEST_F(XMLElementSetAttributeBoolTest_102, BoolAttributeReturnsDefaultWhenMissing_102) {
    bool result = element->BoolAttribute("nonexistent", true);
    EXPECT_TRUE(result);
    result = element->BoolAttribute("nonexistent", false);
    EXPECT_FALSE(result);
}

// Test overwriting a bool attribute with a new bool value
TEST_F(XMLElementSetAttributeBoolTest_102, OverwriteBoolAttribute_102) {
    element->SetAttribute("toggle", true);
    EXPECT_TRUE(element->BoolAttribute("toggle", false));
    
    element->SetAttribute("toggle", false);
    EXPECT_FALSE(element->BoolAttribute("toggle", true));
}

// Test that the attribute value string is correct for true
TEST_F(XMLElementSetAttributeBoolTest_102, AttributeStringValueTrue_102) {
    element->SetAttribute("flag", true);
    const char* val = element->Attribute("flag");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "true");
}

// Test that the attribute value string is correct for false
TEST_F(XMLElementSetAttributeBoolTest_102, AttributeStringValueFalse_102) {
    element->SetAttribute("flag", false);
    const char* val = element->Attribute("flag");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "false");
}

// Test setting multiple bool attributes on the same element
TEST_F(XMLElementSetAttributeBoolTest_102, SetMultipleBoolAttributes_102) {
    element->SetAttribute("a", true);
    element->SetAttribute("b", false);
    element->SetAttribute("c", true);
    
    EXPECT_TRUE(element->BoolAttribute("a", false));
    EXPECT_FALSE(element->BoolAttribute("b", true));
    EXPECT_TRUE(element->BoolAttribute("c", false));
}

// Test that FindAttribute returns non-null after setting a bool attribute
TEST_F(XMLElementSetAttributeBoolTest_102, FindAttributeAfterSetBool_102) {
    element->SetAttribute("exists", true);
    const XMLAttribute* attr = element->FindAttribute("exists");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "exists");
    EXPECT_TRUE(attr->BoolValue());
}

// Test FindAttribute returns null for nonexistent attribute
TEST_F(XMLElementSetAttributeBoolTest_102, FindAttributeNonExistent_102) {
    const XMLAttribute* attr = element->FindAttribute("doesnotexist");
    EXPECT_EQ(attr, nullptr);
}

// Test overwriting a string attribute with a bool attribute
TEST_F(XMLElementSetAttributeBoolTest_102, OverwriteStringWithBool_102) {
    element->SetAttribute("attr", "hello");
    EXPECT_STREQ(element->Attribute("attr"), "hello");
    
    element->SetAttribute("attr", true);
    EXPECT_STREQ(element->Attribute("attr"), "true");
    EXPECT_TRUE(element->BoolAttribute("attr", false));
}

// Test overwriting an int attribute with a bool attribute
TEST_F(XMLElementSetAttributeBoolTest_102, OverwriteIntWithBool_102) {
    element->SetAttribute("attr", 42);
    EXPECT_EQ(element->IntAttribute("attr", 0), 42);
    
    element->SetAttribute("attr", false);
    EXPECT_FALSE(element->BoolAttribute("attr", true));
}

// Test QueryBoolAttribute returns error for non-bool string
TEST_F(XMLElementSetAttributeBoolTest_102, QueryBoolAttributeWithNonBoolValue_102) {
    element->SetAttribute("attr", "notabool");
    bool value = false;
    XMLError err = element->QueryBoolAttribute("attr", &value);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test QueryBoolAttribute returns NO_ATTRIBUTE for missing attribute
TEST_F(XMLElementSetAttributeBoolTest_102, QueryBoolAttributeMissing_102) {
    bool value = false;
    XMLError err = element->QueryBoolAttribute("missing", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

// Test that the attribute can be serialized and re-parsed with bool value
TEST_F(XMLElementSetAttributeBoolTest_102, SerializeAndReparseBool_102) {
    element->SetAttribute("check", true);
    
    XMLPrinter printer;
    doc.Print(&printer);
    
    XMLDocument doc2;
    XMLError err = doc2.Parse(printer.CStr());
    EXPECT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc2.FirstChildElement("TestElement");
    ASSERT_NE(root, nullptr);
    EXPECT_TRUE(root->BoolAttribute("check", false));
}

// Test setting bool attribute and then deleting it
TEST_F(XMLElementSetAttributeBoolTest_102, DeleteBoolAttribute_102) {
    element->SetAttribute("toDelete", true);
    EXPECT_NE(element->FindAttribute("toDelete"), nullptr);
    
    element->DeleteAttribute("toDelete");
    EXPECT_EQ(element->FindAttribute("toDelete"), nullptr);
}

// Test FirstAttribute after setting a bool attribute
TEST_F(XMLElementSetAttributeBoolTest_102, FirstAttributeAfterSetBool_102) {
    element->SetAttribute("first", true);
    const XMLAttribute* attr = element->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "first");
    EXPECT_TRUE(attr->BoolValue());
}

// Test QueryBoolValue on the XMLAttribute directly
TEST_F(XMLElementSetAttributeBoolTest_102, QueryBoolValueOnAttribute_102) {
    element->SetAttribute("directQuery", false);
    const XMLAttribute* attr = element->FindAttribute("directQuery");
    ASSERT_NE(attr, nullptr);
    
    bool val = true;
    XMLError err = attr->QueryBoolValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(val);
}

// Test that setting bool attribute with empty name still creates attribute
TEST_F(XMLElementSetAttributeBoolTest_102, SetBoolAttributeEmptyName_102) {
    element->SetAttribute("", true);
    const XMLAttribute* attr = element->FindAttribute("");
    ASSERT_NE(attr, nullptr);
    EXPECT_TRUE(attr->BoolValue());
}

// Test attribute iteration with Next() after setting multiple attributes including bool
TEST_F(XMLElementSetAttributeBoolTest_102, AttributeIterationWithBool_102) {
    element->SetAttribute("x", 10);
    element->SetAttribute("y", true);
    element->SetAttribute("z", "hello");
    
    int count = 0;
    for (const XMLAttribute* attr = element->FirstAttribute(); attr; attr = attr->Next()) {
        count++;
    }
    EXPECT_EQ(count, 3);
}
