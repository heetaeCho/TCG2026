#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementDeleteAttributeTest_258 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test deleting an attribute that exists (single attribute)
TEST_F(XMLElementDeleteAttributeTest_258, DeleteSingleAttribute_258) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("attr1", "value1");

    ASSERT_NE(nullptr, elem->FindAttribute("attr1"));

    elem->DeleteAttribute("attr1");

    EXPECT_EQ(nullptr, elem->FindAttribute("attr1"));
    EXPECT_EQ(nullptr, elem->FirstAttribute());
}

// Test deleting the first attribute when multiple exist
TEST_F(XMLElementDeleteAttributeTest_258, DeleteFirstOfMultipleAttributes_258) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("attr1", "value1");
    elem->SetAttribute("attr2", "value2");
    elem->SetAttribute("attr3", "value3");

    elem->DeleteAttribute("attr1");

    EXPECT_EQ(nullptr, elem->FindAttribute("attr1"));
    EXPECT_NE(nullptr, elem->FindAttribute("attr2"));
    EXPECT_NE(nullptr, elem->FindAttribute("attr3"));
}

// Test deleting a middle attribute when multiple exist
TEST_F(XMLElementDeleteAttributeTest_258, DeleteMiddleAttribute_258) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("attr1", "value1");
    elem->SetAttribute("attr2", "value2");
    elem->SetAttribute("attr3", "value3");

    elem->DeleteAttribute("attr2");

    EXPECT_NE(nullptr, elem->FindAttribute("attr1"));
    EXPECT_EQ(nullptr, elem->FindAttribute("attr2"));
    EXPECT_NE(nullptr, elem->FindAttribute("attr3"));
}

// Test deleting the last attribute when multiple exist
TEST_F(XMLElementDeleteAttributeTest_258, DeleteLastAttribute_258) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("attr1", "value1");
    elem->SetAttribute("attr2", "value2");
    elem->SetAttribute("attr3", "value3");

    elem->DeleteAttribute("attr3");

    EXPECT_NE(nullptr, elem->FindAttribute("attr1"));
    EXPECT_NE(nullptr, elem->FindAttribute("attr2"));
    EXPECT_EQ(nullptr, elem->FindAttribute("attr3"));
}

// Test deleting an attribute that does not exist
TEST_F(XMLElementDeleteAttributeTest_258, DeleteNonExistentAttribute_258) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("attr1", "value1");

    // Should not crash or have side effects
    elem->DeleteAttribute("nonexistent");

    EXPECT_NE(nullptr, elem->FindAttribute("attr1"));
}

// Test deleting from element with no attributes
TEST_F(XMLElementDeleteAttributeTest_258, DeleteFromEmptyAttributes_258) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);

    // Should not crash
    elem->DeleteAttribute("anything");

    EXPECT_EQ(nullptr, elem->FirstAttribute());
}

// Test deleting all attributes one by one
TEST_F(XMLElementDeleteAttributeTest_258, DeleteAllAttributesOneByOne_258) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("a", "1");
    elem->SetAttribute("b", "2");
    elem->SetAttribute("c", "3");

    elem->DeleteAttribute("a");
    elem->DeleteAttribute("b");
    elem->DeleteAttribute("c");

    EXPECT_EQ(nullptr, elem->FirstAttribute());
    EXPECT_EQ(nullptr, elem->FindAttribute("a"));
    EXPECT_EQ(nullptr, elem->FindAttribute("b"));
    EXPECT_EQ(nullptr, elem->FindAttribute("c"));
}

// Test deleting attribute and verifying remaining attribute values
TEST_F(XMLElementDeleteAttributeTest_258, DeleteAttributePreservesOtherValues_258) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("name", "hello");
    elem->SetAttribute("count", 42);
    elem->SetAttribute("flag", true);

    elem->DeleteAttribute("count");

    EXPECT_STREQ("hello", elem->Attribute("name"));
    EXPECT_EQ(nullptr, elem->FindAttribute("count"));
    EXPECT_EQ(true, elem->BoolAttribute("flag"));
}

// Test deleting same attribute twice (second time is a no-op)
TEST_F(XMLElementDeleteAttributeTest_258, DeleteSameAttributeTwice_258) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("attr1", "value1");
    elem->SetAttribute("attr2", "value2");

    elem->DeleteAttribute("attr1");
    EXPECT_EQ(nullptr, elem->FindAttribute("attr1"));

    // Should not crash
    elem->DeleteAttribute("attr1");
    EXPECT_EQ(nullptr, elem->FindAttribute("attr1"));
    EXPECT_NE(nullptr, elem->FindAttribute("attr2"));
}

// Test that deleting attribute works with parsed XML
TEST_F(XMLElementDeleteAttributeTest_258, DeleteAttributeFromParsedXML_258) {
    const char* xml = "<root attr1=\"val1\" attr2=\"val2\" attr3=\"val3\"/>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);

    root->DeleteAttribute("attr2");

    EXPECT_STREQ("val1", root->Attribute("attr1"));
    EXPECT_EQ(nullptr, root->FindAttribute("attr2"));
    EXPECT_STREQ("val3", root->Attribute("attr3"));
}

// Test deleting attribute with similar names (case sensitivity)
TEST_F(XMLElementDeleteAttributeTest_258, DeleteAttributeCaseSensitive_258) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("Name", "upper");
    elem->SetAttribute("name", "lower");

    elem->DeleteAttribute("Name");

    EXPECT_EQ(nullptr, elem->FindAttribute("Name"));
    EXPECT_NE(nullptr, elem->FindAttribute("name"));
    EXPECT_STREQ("lower", elem->Attribute("name"));
}

// Test deleting attributes and then adding new ones
TEST_F(XMLElementDeleteAttributeTest_258, DeleteThenAddAttribute_258) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("attr1", "value1");

    elem->DeleteAttribute("attr1");
    EXPECT_EQ(nullptr, elem->FindAttribute("attr1"));

    elem->SetAttribute("attr1", "newvalue");
    EXPECT_STREQ("newvalue", elem->Attribute("attr1"));
}

// Test with integer attribute values
TEST_F(XMLElementDeleteAttributeTest_258, DeleteIntAttribute_258) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("count", 100);
    elem->SetAttribute("size", 200);

    EXPECT_EQ(100, elem->IntAttribute("count"));

    elem->DeleteAttribute("count");

    EXPECT_EQ(nullptr, elem->FindAttribute("count"));
    EXPECT_EQ(200, elem->IntAttribute("size"));
}

// Test deleting from element with only two attributes (delete first)
TEST_F(XMLElementDeleteAttributeTest_258, DeleteFirstOfTwoAttributes_258) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("first", "1");
    elem->SetAttribute("second", "2");

    elem->DeleteAttribute("first");

    EXPECT_EQ(nullptr, elem->FindAttribute("first"));
    EXPECT_NE(nullptr, elem->FirstAttribute());
    EXPECT_STREQ("second", elem->FirstAttribute()->Name());
}

// Test deleting from element with only two attributes (delete second)
TEST_F(XMLElementDeleteAttributeTest_258, DeleteSecondOfTwoAttributes_258) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("first", "1");
    elem->SetAttribute("second", "2");

    elem->DeleteAttribute("second");

    EXPECT_EQ(nullptr, elem->FindAttribute("second"));
    EXPECT_NE(nullptr, elem->FirstAttribute());
    EXPECT_STREQ("first", elem->FirstAttribute()->Name());
    EXPECT_EQ(nullptr, elem->FirstAttribute()->Next());
}
