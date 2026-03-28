#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLDocumentNewElementTest_272 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// =============================================================================
// Normal Operation Tests
// =============================================================================

TEST_F(XMLDocumentNewElementTest_272, NewElementReturnsNonNull_272) {
    XMLElement* ele = doc.NewElement("test");
    ASSERT_NE(nullptr, ele);
}

TEST_F(XMLDocumentNewElementTest_272, NewElementHasCorrectName_272) {
    XMLElement* ele = doc.NewElement("myElement");
    ASSERT_NE(nullptr, ele);
    EXPECT_STREQ("myElement", ele->Name());
}

TEST_F(XMLDocumentNewElementTest_272, NewElementWithSimpleName_272) {
    XMLElement* ele = doc.NewElement("root");
    ASSERT_NE(nullptr, ele);
    EXPECT_STREQ("root", ele->Name());
}

TEST_F(XMLDocumentNewElementTest_272, NewElementCanBeInsertedAsRoot_272) {
    XMLElement* ele = doc.NewElement("root");
    doc.InsertFirstChild(ele);
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("root", doc.RootElement()->Name());
}

TEST_F(XMLDocumentNewElementTest_272, NewElementToElementReturnsItself_272) {
    XMLElement* ele = doc.NewElement("item");
    EXPECT_EQ(ele, ele->ToElement());
}

TEST_F(XMLDocumentNewElementTest_272, NewElementHasNoChildren_272) {
    XMLElement* ele = doc.NewElement("empty");
    EXPECT_EQ(nullptr, ele->FirstChild());
    EXPECT_EQ(nullptr, ele->LastChild());
}

TEST_F(XMLDocumentNewElementTest_272, NewElementHasNoAttributes_272) {
    XMLElement* ele = doc.NewElement("noattr");
    EXPECT_EQ(nullptr, ele->FirstAttribute());
}

TEST_F(XMLDocumentNewElementTest_272, NewElementGetTextReturnsNull_272) {
    XMLElement* ele = doc.NewElement("notext");
    EXPECT_EQ(nullptr, ele->GetText());
}

TEST_F(XMLDocumentNewElementTest_272, NewElementHasNoSiblings_272) {
    XMLElement* ele = doc.NewElement("alone");
    EXPECT_EQ(nullptr, ele->NextSibling());
    EXPECT_EQ(nullptr, ele->PreviousSibling());
}

TEST_F(XMLDocumentNewElementTest_272, MultipleNewElementsAreDistinct_272) {
    XMLElement* ele1 = doc.NewElement("first");
    XMLElement* ele2 = doc.NewElement("second");
    ASSERT_NE(nullptr, ele1);
    ASSERT_NE(nullptr, ele2);
    EXPECT_NE(ele1, ele2);
    EXPECT_STREQ("first", ele1->Name());
    EXPECT_STREQ("second", ele2->Name());
}

TEST_F(XMLDocumentNewElementTest_272, NewElementCanSetAttributes_272) {
    XMLElement* ele = doc.NewElement("item");
    ele->SetAttribute("key", "value");
    EXPECT_STREQ("value", ele->Attribute("key"));
}

TEST_F(XMLDocumentNewElementTest_272, NewElementCanSetIntAttribute_272) {
    XMLElement* ele = doc.NewElement("item");
    ele->SetAttribute("count", 42);
    EXPECT_EQ(42, ele->IntAttribute("count", 0));
}

TEST_F(XMLDocumentNewElementTest_272, NewElementCanSetText_272) {
    XMLElement* ele = doc.NewElement("item");
    ele->SetText("hello");
    EXPECT_STREQ("hello", ele->GetText());
}

TEST_F(XMLDocumentNewElementTest_272, NewElementCanBeNestedAsChild_272) {
    XMLElement* parent = doc.NewElement("parent");
    XMLElement* child = doc.NewElement("child");
    doc.InsertFirstChild(parent);
    parent->InsertFirstChild(child);
    ASSERT_NE(nullptr, parent->FirstChildElement("child"));
    EXPECT_STREQ("child", parent->FirstChildElement("child")->Name());
}

TEST_F(XMLDocumentNewElementTest_272, NewElementSetNameChangesName_272) {
    XMLElement* ele = doc.NewElement("original");
    EXPECT_STREQ("original", ele->Name());
    ele->SetName("renamed");
    EXPECT_STREQ("renamed", ele->Name());
}

// =============================================================================
// Boundary Condition Tests
// =============================================================================

TEST_F(XMLDocumentNewElementTest_272, NewElementWithEmptyName_272) {
    XMLElement* ele = doc.NewElement("");
    ASSERT_NE(nullptr, ele);
    EXPECT_STREQ("", ele->Name());
}

TEST_F(XMLDocumentNewElementTest_272, NewElementWithLongName_272) {
    std::string longName(1000, 'a');
    XMLElement* ele = doc.NewElement(longName.c_str());
    ASSERT_NE(nullptr, ele);
    EXPECT_STREQ(longName.c_str(), ele->Name());
}

TEST_F(XMLDocumentNewElementTest_272, NewElementWithSpecialCharactersInName_272) {
    XMLElement* ele = doc.NewElement("my-element_123");
    ASSERT_NE(nullptr, ele);
    EXPECT_STREQ("my-element_123", ele->Name());
}

TEST_F(XMLDocumentNewElementTest_272, NewElementWithSingleCharName_272) {
    XMLElement* ele = doc.NewElement("x");
    ASSERT_NE(nullptr, ele);
    EXPECT_STREQ("x", ele->Name());
}

TEST_F(XMLDocumentNewElementTest_272, CreateManyElements_272) {
    const int count = 100;
    std::vector<XMLElement*> elements;
    for (int i = 0; i < count; ++i) {
        std::string name = "element" + std::to_string(i);
        XMLElement* ele = doc.NewElement(name.c_str());
        ASSERT_NE(nullptr, ele);
        elements.push_back(ele);
    }
    for (int i = 0; i < count; ++i) {
        std::string expectedName = "element" + std::to_string(i);
        EXPECT_STREQ(expectedName.c_str(), elements[i]->Name());
    }
}

// =============================================================================
// Attribute-related tests on NewElement
// =============================================================================

TEST_F(XMLDocumentNewElementTest_272, NewElementQueryMissingAttributeReturnsDefault_272) {
    XMLElement* ele = doc.NewElement("item");
    EXPECT_EQ(99, ele->IntAttribute("missing", 99));
    EXPECT_EQ(100u, ele->UnsignedAttribute("missing", 100u));
    EXPECT_EQ(true, ele->BoolAttribute("missing", true));
    EXPECT_DOUBLE_EQ(3.14, ele->DoubleAttribute("missing", 3.14));
    EXPECT_FLOAT_EQ(2.5f, ele->FloatAttribute("missing", 2.5f));
}

TEST_F(XMLDocumentNewElementTest_272, NewElementFindAttributeReturnsNullForMissing_272) {
    XMLElement* ele = doc.NewElement("item");
    EXPECT_EQ(nullptr, ele->FindAttribute("nonexistent"));
}

TEST_F(XMLDocumentNewElementTest_272, NewElementSetAndQueryInt64Attribute_272) {
    XMLElement* ele = doc.NewElement("item");
    int64_t bigVal = 9223372036854775807LL;
    ele->SetAttribute("big", bigVal);
    EXPECT_EQ(bigVal, ele->Int64Attribute("big", 0));
}

TEST_F(XMLDocumentNewElementTest_272, NewElementSetAndQueryUnsigned64Attribute_272) {
    XMLElement* ele = doc.NewElement("item");
    uint64_t bigVal = 18446744073709551615ULL;
    ele->SetAttribute("ubig", bigVal);
    EXPECT_EQ(bigVal, ele->Unsigned64Attribute("ubig", 0));
}

TEST_F(XMLDocumentNewElementTest_272, NewElementDeleteAttribute_272) {
    XMLElement* ele = doc.NewElement("item");
    ele->SetAttribute("key", "value");
    EXPECT_NE(nullptr, ele->FindAttribute("key"));
    ele->DeleteAttribute("key");
    EXPECT_EQ(nullptr, ele->FindAttribute("key"));
}

TEST_F(XMLDocumentNewElementTest_272, NewElementSetMultipleAttributes_272) {
    XMLElement* ele = doc.NewElement("item");
    ele->SetAttribute("a", "1");
    ele->SetAttribute("b", "2");
    ele->SetAttribute("c", "3");
    EXPECT_STREQ("1", ele->Attribute("a"));
    EXPECT_STREQ("2", ele->Attribute("b"));
    EXPECT_STREQ("3", ele->Attribute("c"));
}

// =============================================================================
// Text-related tests on NewElement
// =============================================================================

TEST_F(XMLDocumentNewElementTest_272, NewElementSetTextInt_272) {
    XMLElement* ele = doc.NewElement("num");
    doc.InsertFirstChild(ele);
    ele->SetText(42);
    EXPECT_EQ(42, ele->IntText(0));
}

TEST_F(XMLDocumentNewElementTest_272, NewElementSetTextUnsigned_272) {
    XMLElement* ele = doc.NewElement("num");
    doc.InsertFirstChild(ele);
    ele->SetText(42u);
    EXPECT_EQ(42u, ele->UnsignedText(0u));
}

TEST_F(XMLDocumentNewElementTest_272, NewElementSetTextBool_272) {
    XMLElement* ele = doc.NewElement("flag");
    doc.InsertFirstChild(ele);
    ele->SetText(true);
    EXPECT_EQ(true, ele->BoolText(false));
}

TEST_F(XMLDocumentNewElementTest_272, NewElementSetTextDouble_272) {
    XMLElement* ele = doc.NewElement("val");
    doc.InsertFirstChild(ele);
    ele->SetText(3.14);
    EXPECT_NEAR(3.14, ele->DoubleText(0.0), 0.001);
}

TEST_F(XMLDocumentNewElementTest_272, NewElementSetTextFloat_272) {
    XMLElement* ele = doc.NewElement("val");
    doc.InsertFirstChild(ele);
    ele->SetText(2.5f);
    EXPECT_NEAR(2.5f, ele->FloatText(0.0f), 0.001f);
}

TEST_F(XMLDocumentNewElementTest_272, NewElementSetTextInt64_272) {
    XMLElement* ele = doc.NewElement("val");
    doc.InsertFirstChild(ele);
    int64_t v = 1234567890123LL;
    ele->SetText(v);
    EXPECT_EQ(v, ele->Int64Text(0));
}

TEST_F(XMLDocumentNewElementTest_272, NewElementSetTextUint64_272) {
    XMLElement* ele = doc.NewElement("val");
    doc.InsertFirstChild(ele);
    uint64_t v = 9876543210ULL;
    ele->SetText(v);
    EXPECT_EQ(v, ele->Unsigned64Text(0));
}

// =============================================================================
// InsertNew* child element tests
// =============================================================================

TEST_F(XMLDocumentNewElementTest_272, NewElementInsertNewChildElement_272) {
    XMLElement* ele = doc.NewElement("parent");
    doc.InsertFirstChild(ele);
    XMLElement* child = ele->InsertNewChildElement("child");
    ASSERT_NE(nullptr, child);
    EXPECT_STREQ("child", child->Name());
    EXPECT_EQ(child, ele->FirstChildElement("child"));
}

TEST_F(XMLDocumentNewElementTest_272, NewElementInsertNewComment_272) {
    XMLElement* ele = doc.NewElement("parent");
    doc.InsertFirstChild(ele);
    XMLComment* comment = ele->InsertNewComment("a comment");
    ASSERT_NE(nullptr, comment);
}

TEST_F(XMLDocumentNewElementTest_272, NewElementInsertNewText_272) {
    XMLElement* ele = doc.NewElement("parent");
    doc.InsertFirstChild(ele);
    XMLText* text = ele->InsertNewText("some text");
    ASSERT_NE(nullptr, text);
}

TEST_F(XMLDocumentNewElementTest_272, NewElementInsertNewDeclaration_272) {
    XMLElement* ele = doc.NewElement("parent");
    doc.InsertFirstChild(ele);
    XMLDeclaration* decl = ele->InsertNewDeclaration("version=\"1.0\"");
    ASSERT_NE(nullptr, decl);
}

TEST_F(XMLDocumentNewElementTest_272, NewElementInsertNewUnknown_272) {
    XMLElement* ele = doc.NewElement("parent");
    doc.InsertFirstChild(ele);
    XMLUnknown* unknown = ele->InsertNewUnknown("!DOCTYPE html");
    ASSERT_NE(nullptr, unknown);
}

// =============================================================================
// ShallowClone and ShallowEqual tests
// =============================================================================

TEST_F(XMLDocumentNewElementTest_272, NewElementShallowClone_272) {
    XMLElement* ele = doc.NewElement("original");
    ele->SetAttribute("attr", "value");
    XMLNode* clone = ele->ShallowClone(&doc);
    ASSERT_NE(nullptr, clone);
    XMLElement* cloneEle = clone->ToElement();
    ASSERT_NE(nullptr, cloneEle);
    EXPECT_STREQ("original", cloneEle->Name());
    EXPECT_STREQ("value", cloneEle->Attribute("attr"));
}

TEST_F(XMLDocumentNewElementTest_272, NewElementShallowEqualSameElement_272) {
    XMLElement* ele1 = doc.NewElement("same");
    ele1->SetAttribute("a", "1");
    XMLElement* ele2 = doc.NewElement("same");
    ele2->SetAttribute("a", "1");
    EXPECT_TRUE(ele1->ShallowEqual(ele2));
}

TEST_F(XMLDocumentNewElementTest_272, NewElementShallowEqualDifferentName_272) {
    XMLElement* ele1 = doc.NewElement("name1");
    XMLElement* ele2 = doc.NewElement("name2");
    EXPECT_FALSE(ele1->ShallowEqual(ele2));
}

TEST_F(XMLDocumentNewElementTest_272, NewElementShallowEqualDifferentAttributes_272) {
    XMLElement* ele1 = doc.NewElement("item");
    ele1->SetAttribute("a", "1");
    XMLElement* ele2 = doc.NewElement("item");
    ele2->SetAttribute("a", "2");
    EXPECT_FALSE(ele1->ShallowEqual(ele2));
}

// =============================================================================
// DeleteNode test
// =============================================================================

TEST_F(XMLDocumentNewElementTest_272, DeleteNodeOnNewElement_272) {
    XMLElement* ele = doc.NewElement("todelete");
    doc.InsertFirstChild(ele);
    ASSERT_NE(nullptr, doc.RootElement());
    doc.DeleteNode(ele);
    EXPECT_EQ(nullptr, doc.RootElement());
}

// =============================================================================
// QueryAttribute error tests
// =============================================================================

TEST_F(XMLDocumentNewElementTest_272, QueryIntAttributeNoAttribute_272) {
    XMLElement* ele = doc.NewElement("item");
    int value = 0;
    XMLError err = ele->QueryIntAttribute("missing", &value);
    EXPECT_NE(XML_SUCCESS, err);
}

TEST_F(XMLDocumentNewElementTest_272, QueryStringAttributeNoAttribute_272) {
    XMLElement* ele = doc.NewElement("item");
    const char* value = nullptr;
    XMLError err = ele->QueryStringAttribute("missing", &value);
    EXPECT_NE(XML_SUCCESS, err);
}

// =============================================================================
// QueryText error tests
// =============================================================================

TEST_F(XMLDocumentNewElementTest_272, QueryIntTextNoText_272) {
    XMLElement* ele = doc.NewElement("empty");
    int value = 0;
    XMLError err = ele->QueryIntText(&value);
    EXPECT_NE(XML_SUCCESS, err);
}

TEST_F(XMLDocumentNewElementTest_272, QueryBoolTextNoText_272) {
    XMLElement* ele = doc.NewElement("empty");
    bool value = false;
    XMLError err = ele->QueryBoolText(&value);
    EXPECT_NE(XML_SUCCESS, err);
}

// =============================================================================
// ClosingType test
// =============================================================================

TEST_F(XMLDocumentNewElementTest_272, NewElementClosingTypeIsOpen_272) {
    XMLElement* ele = doc.NewElement("item");
    // Newly created elements should have OPEN closing type
    EXPECT_EQ(XMLElement::OPEN, ele->ClosingType());
}

// =============================================================================
// Document-level tests related to NewElement
// =============================================================================

TEST_F(XMLDocumentNewElementTest_272, NewElementBelongsToDocument_272) {
    XMLElement* ele = doc.NewElement("item");
    EXPECT_EQ(&doc, ele->GetDocument());
}

TEST_F(XMLDocumentNewElementTest_272, ParseThenNewElement_272) {
    const char* xml = "<root><child/></root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    XMLElement* newEle = doc.NewElement("newChild");
    ASSERT_NE(nullptr, newEle);
    doc.RootElement()->InsertEndChild(newEle);
    ASSERT_NE(nullptr, doc.RootElement()->FirstChildElement("newChild"));
}

TEST_F(XMLDocumentNewElementTest_272, NewElementAttributeOverwrite_272) {
    XMLElement* ele = doc.NewElement("item");
    ele->SetAttribute("key", "first");
    EXPECT_STREQ("first", ele->Attribute("key"));
    ele->SetAttribute("key", "second");
    EXPECT_STREQ("second", ele->Attribute("key"));
}

TEST_F(XMLDocumentNewElementTest_272, NewElementDeleteNonexistentAttribute_272) {
    XMLElement* ele = doc.NewElement("item");
    // Should not crash when deleting non-existent attribute
    ele->DeleteAttribute("nonexistent");
    EXPECT_EQ(nullptr, ele->FindAttribute("nonexistent"));
}

TEST_F(XMLDocumentNewElementTest_272, NewElementAttributeWithNullValue_272) {
    XMLElement* ele = doc.NewElement("item");
    ele->SetAttribute("key", "val");
    // Attribute with nullptr value should return the attribute value regardless
    const char* result = ele->Attribute("key", nullptr);
    EXPECT_STREQ("val", result);
}

TEST_F(XMLDocumentNewElementTest_272, NewElementAttributeWithMatchingValue_272) {
    XMLElement* ele = doc.NewElement("item");
    ele->SetAttribute("key", "val");
    const char* result = ele->Attribute("key", "val");
    EXPECT_STREQ("val", result);
}

TEST_F(XMLDocumentNewElementTest_272, NewElementAttributeWithNonMatchingValue_272) {
    XMLElement* ele = doc.NewElement("item");
    ele->SetAttribute("key", "val");
    const char* result = ele->Attribute("key", "other");
    EXPECT_EQ(nullptr, result);
}

TEST_F(XMLDocumentNewElementTest_272, NewElementQueryBoolAttribute_272) {
    XMLElement* ele = doc.NewElement("item");
    ele->SetAttribute("flag", true);
    bool val = false;
    XMLError err = ele->QueryBoolAttribute("flag", &val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_TRUE(val);
}

TEST_F(XMLDocumentNewElementTest_272, NewElementQueryDoubleAttribute_272) {
    XMLElement* ele = doc.NewElement("item");
    ele->SetAttribute("pi", 3.14159);
    double val = 0.0;
    XMLError err = ele->QueryDoubleAttribute("pi", &val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(3.14159, val, 0.0001);
}

TEST_F(XMLDocumentNewElementTest_272, NewElementQueryFloatAttribute_272) {
    XMLElement* ele = doc.NewElement("item");
    ele->SetAttribute("f", 1.5f);
    float val = 0.0f;
    XMLError err = ele->QueryFloatAttribute("f", &val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(1.5f, val, 0.001f);
}
