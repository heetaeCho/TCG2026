#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementSetAttributeTest_99 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem;

    void SetUp() override {
        elem = doc.NewElement("TestElement");
        doc.InsertEndChild(elem);
    }
};

// Test setting an unsigned attribute and retrieving it
TEST_F(XMLElementSetAttributeTest_99, SetUnsignedAttribute_Basic_99) {
    elem->SetAttribute("count", (unsigned)42);
    unsigned val = 0;
    XMLError err = elem->QueryUnsignedAttribute("count", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 42u);
}

// Test setting an unsigned attribute with value 0
TEST_F(XMLElementSetAttributeTest_99, SetUnsignedAttribute_Zero_99) {
    elem->SetAttribute("count", (unsigned)0);
    EXPECT_EQ(elem->UnsignedAttribute("count", 999), 0u);
}

// Test setting an unsigned attribute with max value
TEST_F(XMLElementSetAttributeTest_99, SetUnsignedAttribute_MaxValue_99) {
    unsigned maxVal = UINT_MAX;
    elem->SetAttribute("big", maxVal);
    unsigned result = 0;
    XMLError err = elem->QueryUnsignedAttribute("big", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, maxVal);
}

// Test overwriting an existing attribute with a new unsigned value
TEST_F(XMLElementSetAttributeTest_99, SetUnsignedAttribute_Overwrite_99) {
    elem->SetAttribute("val", (unsigned)10);
    EXPECT_EQ(elem->UnsignedAttribute("val", 0), 10u);

    elem->SetAttribute("val", (unsigned)20);
    EXPECT_EQ(elem->UnsignedAttribute("val", 0), 20u);
}

// Test setting multiple unsigned attributes
TEST_F(XMLElementSetAttributeTest_99, SetUnsignedAttribute_Multiple_99) {
    elem->SetAttribute("a", (unsigned)1);
    elem->SetAttribute("b", (unsigned)2);
    elem->SetAttribute("c", (unsigned)3);

    EXPECT_EQ(elem->UnsignedAttribute("a", 0), 1u);
    EXPECT_EQ(elem->UnsignedAttribute("b", 0), 2u);
    EXPECT_EQ(elem->UnsignedAttribute("c", 0), 3u);
}

// Test that the attribute name is correctly stored
TEST_F(XMLElementSetAttributeTest_99, SetUnsignedAttribute_NameCorrect_99) {
    elem->SetAttribute("myAttr", (unsigned)100);
    const XMLAttribute* attr = elem->FindAttribute("myAttr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "myAttr");
}

// Test that FindAttribute returns nullptr for non-existent attribute
TEST_F(XMLElementSetAttributeTest_99, FindAttribute_NonExistent_99) {
    elem->SetAttribute("exists", (unsigned)1);
    const XMLAttribute* attr = elem->FindAttribute("doesNotExist");
    EXPECT_EQ(attr, nullptr);
}

// Test querying unsigned attribute that doesn't exist returns error
TEST_F(XMLElementSetAttributeTest_99, QueryUnsignedAttribute_NotFound_99) {
    unsigned val = 0;
    XMLError err = elem->QueryUnsignedAttribute("missing", &val);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

// Test setting unsigned attribute then reading as int
TEST_F(XMLElementSetAttributeTest_99, SetUnsignedAttribute_ReadAsInt_99) {
    elem->SetAttribute("val", (unsigned)50);
    int intVal = 0;
    XMLError err = elem->QueryIntAttribute("val", &intVal);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(intVal, 50);
}

// Test setting unsigned attribute then reading the string value
TEST_F(XMLElementSetAttributeTest_99, SetUnsignedAttribute_ReadAsString_99) {
    elem->SetAttribute("val", (unsigned)123);
    const char* strVal = elem->Attribute("val");
    ASSERT_NE(strVal, nullptr);
    EXPECT_STREQ(strVal, "123");
}

// Test that setting a string attribute and then unsigned overwrites correctly
TEST_F(XMLElementSetAttributeTest_99, SetAttribute_StringThenUnsigned_99) {
    elem->SetAttribute("mixed", "hello");
    EXPECT_STREQ(elem->Attribute("mixed"), "hello");

    elem->SetAttribute("mixed", (unsigned)42);
    EXPECT_EQ(elem->UnsignedAttribute("mixed", 0), 42u);
}

// Test setting unsigned attribute then deleting it
TEST_F(XMLElementSetAttributeTest_99, SetUnsignedAttribute_ThenDelete_99) {
    elem->SetAttribute("temp", (unsigned)99);
    EXPECT_NE(elem->FindAttribute("temp"), nullptr);

    elem->DeleteAttribute("temp");
    EXPECT_EQ(elem->FindAttribute("temp"), nullptr);
}

// Test UnsignedAttribute default value when attribute missing
TEST_F(XMLElementSetAttributeTest_99, UnsignedAttribute_DefaultValue_99) {
    unsigned result = elem->UnsignedAttribute("nonexistent", 777);
    EXPECT_EQ(result, 777u);
}

// Test setting unsigned then reading via Value() on XMLAttribute
TEST_F(XMLElementSetAttributeTest_99, SetUnsignedAttribute_ValueString_99) {
    elem->SetAttribute("num", (unsigned)256);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "256");
}

// Test setting unsigned attribute with value 1
TEST_F(XMLElementSetAttributeTest_99, SetUnsignedAttribute_One_99) {
    elem->SetAttribute("one", (unsigned)1);
    EXPECT_EQ(elem->UnsignedAttribute("one", 0), 1u);
}

// Test that UnsignedValue on XMLAttribute works correctly
TEST_F(XMLElementSetAttributeTest_99, XMLAttribute_UnsignedValue_99) {
    elem->SetAttribute("attr", (unsigned)12345);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 12345u);
}

// Test QueryUnsignedValue on XMLAttribute
TEST_F(XMLElementSetAttributeTest_99, XMLAttribute_QueryUnsignedValue_99) {
    elem->SetAttribute("attr", (unsigned)54321);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    unsigned val = 0;
    XMLError err = attr->QueryUnsignedValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 54321u);
}

// Test setting other types of attributes alongside unsigned
TEST_F(XMLElementSetAttributeTest_99, SetMixedAttributes_99) {
    elem->SetAttribute("uval", (unsigned)100);
    elem->SetAttribute("ival", (int)-50);
    elem->SetAttribute("bval", true);
    elem->SetAttribute("dval", 3.14);
    elem->SetAttribute("sval", "text");

    EXPECT_EQ(elem->UnsignedAttribute("uval", 0), 100u);
    EXPECT_EQ(elem->IntAttribute("ival", 0), -50);
    EXPECT_EQ(elem->BoolAttribute("bval", false), true);
    EXPECT_NEAR(elem->DoubleAttribute("dval", 0.0), 3.14, 0.001);
    EXPECT_STREQ(elem->Attribute("sval"), "text");
}

// Test that FirstAttribute returns the first attribute set
TEST_F(XMLElementSetAttributeTest_99, FirstAttribute_AfterSetUnsigned_99) {
    elem->SetAttribute("first", (unsigned)1);
    elem->SetAttribute("second", (unsigned)2);
    const XMLAttribute* first = elem->FirstAttribute();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Name(), "first");
    EXPECT_EQ(first->UnsignedValue(), 1u);
}

// Test Next() on attribute to traverse attributes
TEST_F(XMLElementSetAttributeTest_99, AttributeTraversal_99) {
    elem->SetAttribute("a", (unsigned)10);
    elem->SetAttribute("b", (unsigned)20);
    elem->SetAttribute("c", (unsigned)30);

    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");

    attr = attr->Next();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "b");

    attr = attr->Next();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "c");

    attr = attr->Next();
    EXPECT_EQ(attr, nullptr);
}

// Test setting int64_t attribute
TEST_F(XMLElementSetAttributeTest_99, SetInt64Attribute_99) {
    int64_t bigVal = 9223372036854775807LL;
    elem->SetAttribute("big64", bigVal);
    int64_t result = 0;
    XMLError err = elem->QueryInt64Attribute("big64", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, bigVal);
}

// Test setting uint64_t attribute
TEST_F(XMLElementSetAttributeTest_99, SetUnsigned64Attribute_99) {
    uint64_t bigVal = 18446744073709551615ULL;
    elem->SetAttribute("ubig64", bigVal);
    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Attribute("ubig64", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, bigVal);
}

// Test setting float attribute
TEST_F(XMLElementSetAttributeTest_99, SetFloatAttribute_99) {
    elem->SetAttribute("fval", 1.5f);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("fval", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(result, 1.5f);
}

// Test setting bool attribute
TEST_F(XMLElementSetAttributeTest_99, SetBoolAttribute_True_99) {
    elem->SetAttribute("flag", true);
    bool result = false;
    XMLError err = elem->QueryBoolAttribute("flag", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(result);
}

TEST_F(XMLElementSetAttributeTest_99, SetBoolAttribute_False_99) {
    elem->SetAttribute("flag", false);
    bool result = true;
    XMLError err = elem->QueryBoolAttribute("flag", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(result);
}

// Test setting double attribute
TEST_F(XMLElementSetAttributeTest_99, SetDoubleAttribute_99) {
    elem->SetAttribute("dbl", 2.718281828);
    double result = 0.0;
    XMLError err = elem->QueryDoubleAttribute("dbl", &result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(result, 2.718281828, 1e-6);
}

// Test setting int attribute (negative)
TEST_F(XMLElementSetAttributeTest_99, SetIntAttribute_Negative_99) {
    elem->SetAttribute("neg", (int)-100);
    EXPECT_EQ(elem->IntAttribute("neg", 0), -100);
}

// Test setting string attribute
TEST_F(XMLElementSetAttributeTest_99, SetStringAttribute_99) {
    elem->SetAttribute("name", "tinyxml2");
    EXPECT_STREQ(elem->Attribute("name"), "tinyxml2");
}

// Test Attribute with matching value parameter
TEST_F(XMLElementSetAttributeTest_99, Attribute_WithValueMatch_99) {
    elem->SetAttribute("key", "expected");
    const char* result = elem->Attribute("key", "expected");
    EXPECT_STREQ(result, "expected");
}

// Test Attribute with non-matching value parameter returns nullptr
TEST_F(XMLElementSetAttributeTest_99, Attribute_WithValueMismatch_99) {
    elem->SetAttribute("key", "actual");
    const char* result = elem->Attribute("key", "different");
    EXPECT_EQ(result, nullptr);
}

// Test setting and querying text values
TEST_F(XMLElementSetAttributeTest_99, SetText_String_99) {
    elem->SetText("Hello World");
    EXPECT_STREQ(elem->GetText(), "Hello World");
}

TEST_F(XMLElementSetAttributeTest_99, SetText_Int_99) {
    elem->SetText(42);
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementSetAttributeTest_99, SetText_Unsigned_99) {
    elem->SetText((unsigned)100);
    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 100u);
}

// Test GetText returns nullptr when no text child
TEST_F(XMLElementSetAttributeTest_99, GetText_NoChild_99) {
    EXPECT_EQ(elem->GetText(), nullptr);
}

// Test QueryIntText with no text returns error
TEST_F(XMLElementSetAttributeTest_99, QueryIntText_NoText_99) {
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test InsertNewChildElement
TEST_F(XMLElementSetAttributeTest_99, InsertNewChildElement_99) {
    XMLElement* child = elem->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
}

// Test InsertNewComment
TEST_F(XMLElementSetAttributeTest_99, InsertNewComment_99) {
    XMLComment* comment = elem->InsertNewComment("a comment");
    ASSERT_NE(comment, nullptr);
}

// Test InsertNewText
TEST_F(XMLElementSetAttributeTest_99, InsertNewText_99) {
    XMLText* text = elem->InsertNewText("some text");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(elem->GetText(), "some text");
}

// Test element Name
TEST_F(XMLElementSetAttributeTest_99, ElementName_99) {
    EXPECT_STREQ(elem->Name(), "TestElement");
}

// Test SetName
TEST_F(XMLElementSetAttributeTest_99, SetName_99) {
    elem->SetName("NewName");
    EXPECT_STREQ(elem->Name(), "NewName");
}

// Test ToElement
TEST_F(XMLElementSetAttributeTest_99, ToElement_99) {
    XMLElement* asElem = elem->ToElement();
    EXPECT_EQ(asElem, elem);
}

// Test ShallowClone
TEST_F(XMLElementSetAttributeTest_99, ShallowClone_99) {
    elem->SetAttribute("x", (unsigned)5);
    XMLNode* clone = elem->ShallowClone(&doc);
    ASSERT_NE(clone, nullptr);
    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "TestElement");
    EXPECT_EQ(cloneElem->UnsignedAttribute("x", 0), 5u);
    // Clean up clone
    doc.DeleteNode(clone);
}

// Test ShallowEqual
TEST_F(XMLElementSetAttributeTest_99, ShallowEqual_SameAttributes_99) {
    elem->SetAttribute("x", (unsigned)10);
    XMLElement* other = doc.NewElement("TestElement");
    other->SetAttribute("x", (unsigned)10);
    EXPECT_TRUE(elem->ShallowEqual(other));
    doc.DeleteNode(other);
}

TEST_F(XMLElementSetAttributeTest_99, ShallowEqual_DifferentAttributes_99) {
    elem->SetAttribute("x", (unsigned)10);
    XMLElement* other = doc.NewElement("TestElement");
    other->SetAttribute("x", (unsigned)20);
    EXPECT_FALSE(elem->ShallowEqual(other));
    doc.DeleteNode(other);
}

// Test parsing a document and querying unsigned attribute
TEST_F(XMLElementSetAttributeTest_99, ParseAndQueryUnsigned_99) {
    const char* xml = "<root count=\"42\"/>";
    XMLDocument parseDoc;
    XMLError err = parseDoc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = parseDoc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->UnsignedAttribute("count", 0), 42u);
}

// Test QueryStringAttribute
TEST_F(XMLElementSetAttributeTest_99, QueryStringAttribute_99) {
    elem->SetAttribute("name", "value");
    const char* val = nullptr;
    XMLError err = elem->QueryStringAttribute("name", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_STREQ(val, "value");
}

// Test QueryStringAttribute for non-existent attribute
TEST_F(XMLElementSetAttributeTest_99, QueryStringAttribute_NotFound_99) {
    const char* val = nullptr;
    XMLError err = elem->QueryStringAttribute("nope", &val);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

// Test default values for various types when attribute is missing
TEST_F(XMLElementSetAttributeTest_99, DefaultValues_WhenMissing_99) {
    EXPECT_EQ(elem->IntAttribute("missing", -1), -1);
    EXPECT_EQ(elem->UnsignedAttribute("missing", 99u), 99u);
    EXPECT_EQ(elem->Int64Attribute("missing", -1LL), -1LL);
    EXPECT_EQ(elem->Unsigned64Attribute("missing", 99ULL), 99ULL);
    EXPECT_EQ(elem->BoolAttribute("missing", true), true);
    EXPECT_NEAR(elem->DoubleAttribute("missing", 1.23), 1.23, 1e-9);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("missing", 4.56f), 4.56f);
}

// Test text default values when no text
TEST_F(XMLElementSetAttributeTest_99, TextDefaultValues_WhenNoText_99) {
    EXPECT_EQ(elem->IntText(-1), -1);
    EXPECT_EQ(elem->UnsignedText(99u), 99u);
    EXPECT_EQ(elem->Int64Text(-1LL), -1LL);
    EXPECT_EQ(elem->Unsigned64Text(99ULL), 99ULL);
    EXPECT_EQ(elem->BoolText(true), true);
    EXPECT_NEAR(elem->DoubleText(1.23), 1.23, 1e-9);
    EXPECT_FLOAT_EQ(elem->FloatText(4.56f), 4.56f);
}

// Test SetText with various types and querying back
TEST_F(XMLElementSetAttributeTest_99, SetText_Bool_99) {
    elem->SetText(true);
    bool bval = false;
    XMLError err = elem->QueryBoolText(&bval);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(bval);
}

TEST_F(XMLElementSetAttributeTest_99, SetText_Double_99) {
    elem->SetText(3.14159);
    double dval = 0.0;
    XMLError err = elem->QueryDoubleText(&dval);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(dval, 3.14159, 1e-4);
}

TEST_F(XMLElementSetAttributeTest_99, SetText_Float_99) {
    elem->SetText(2.5f);
    float fval = 0.0f;
    XMLError err = elem->QueryFloatText(&fval);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(fval, 2.5f);
}

TEST_F(XMLElementSetAttributeTest_99, SetText_Int64_99) {
    elem->SetText((int64_t)1234567890123LL);
    int64_t val = 0;
    XMLError err = elem->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 1234567890123LL);
}

TEST_F(XMLElementSetAttributeTest_99, SetText_Uint64_99) {
    elem->SetText((uint64_t)9876543210ULL);
    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 9876543210ULL);
}

// Test DeleteAttribute for non-existent attribute (should not crash)
TEST_F(XMLElementSetAttributeTest_99, DeleteAttribute_NonExistent_99) {
    elem->SetAttribute("keep", (unsigned)1);
    elem->DeleteAttribute("nonexistent");
    EXPECT_EQ(elem->UnsignedAttribute("keep", 0), 1u);
}

// Test that setting same attribute multiple times doesn't create duplicates
TEST_F(XMLElementSetAttributeTest_99, SetAttribute_NoDuplicates_99) {
    elem->SetAttribute("x", (unsigned)1);
    elem->SetAttribute("x", (unsigned)2);
    elem->SetAttribute("x", (unsigned)3);

    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "x");
    EXPECT_EQ(attr->UnsignedValue(), 3u);
    // Should be only one attribute
    EXPECT_EQ(attr->Next(), nullptr);
}
