#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementShallowCloneTest_265 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test: ShallowClone creates a clone with the same element name
TEST_F(XMLElementShallowCloneTest_265, ClonePreservesElementName_265) {
    doc->Parse("<root/>");
    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLNode* clone = root->ShallowClone(doc);
    ASSERT_NE(clone, nullptr);

    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "root");

    doc->DeleteNode(clone);
}

// Test: ShallowClone copies attributes
TEST_F(XMLElementShallowCloneTest_265, CloneCopiesAttributes_265) {
    doc->Parse(R"(<item id="42" name="test" flag="true"/>)");
    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLNode* clone = root->ShallowClone(doc);
    ASSERT_NE(clone, nullptr);

    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);

    EXPECT_STREQ(cloneElem->Attribute("id"), "42");
    EXPECT_STREQ(cloneElem->Attribute("name"), "test");
    EXPECT_STREQ(cloneElem->Attribute("flag"), "true");

    doc->DeleteNode(clone);
}

// Test: ShallowClone does NOT copy children
TEST_F(XMLElementShallowCloneTest_265, CloneDoesNotCopyChildren_265) {
    doc->Parse("<parent><child1/><child2/></parent>");
    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLNode* clone = root->ShallowClone(doc);
    ASSERT_NE(clone, nullptr);

    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_TRUE(cloneElem->NoChildren());

    doc->DeleteNode(clone);
}

// Test: ShallowClone with null document uses the element's own document
TEST_F(XMLElementShallowCloneTest_265, CloneWithNullDocUsesOwnDocument_265) {
    doc->Parse("<element attr=\"value\"/>");
    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLNode* clone = root->ShallowClone(nullptr);
    ASSERT_NE(clone, nullptr);

    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "element");
    EXPECT_STREQ(cloneElem->Attribute("attr"), "value");

    // The clone should belong to the same document
    EXPECT_EQ(cloneElem->GetDocument(), doc);

    doc->DeleteNode(clone);
}

// Test: ShallowClone into a different document
TEST_F(XMLElementShallowCloneTest_265, CloneIntoDifferentDocument_265) {
    doc->Parse(R"(<source x="1" y="2"/>)");
    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLDocument targetDoc;
    XMLNode* clone = root->ShallowClone(&targetDoc);
    ASSERT_NE(clone, nullptr);

    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "source");
    EXPECT_STREQ(cloneElem->Attribute("x"), "1");
    EXPECT_STREQ(cloneElem->Attribute("y"), "2");
    EXPECT_EQ(cloneElem->GetDocument(), &targetDoc);

    targetDoc.DeleteNode(clone);
}

// Test: ShallowClone of element with no attributes
TEST_F(XMLElementShallowCloneTest_265, CloneElementWithNoAttributes_265) {
    doc->Parse("<empty/>");
    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLNode* clone = root->ShallowClone(doc);
    ASSERT_NE(clone, nullptr);

    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "empty");
    EXPECT_EQ(cloneElem->FirstAttribute(), nullptr);

    doc->DeleteNode(clone);
}

// Test: ShallowClone produces a distinct object (not same pointer)
TEST_F(XMLElementShallowCloneTest_265, CloneIsDistinctObject_265) {
    doc->Parse("<node/>");
    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLNode* clone = root->ShallowClone(doc);
    ASSERT_NE(clone, nullptr);
    EXPECT_NE(clone, static_cast<XMLNode*>(root));

    doc->DeleteNode(clone);
}

// Test: ShallowClone does not copy text content (text is a child node, not attribute)
TEST_F(XMLElementShallowCloneTest_265, CloneDoesNotCopyTextContent_265) {
    doc->Parse("<message>Hello World</message>");
    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLNode* clone = root->ShallowClone(doc);
    ASSERT_NE(clone, nullptr);

    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "message");
    // Text is a child node, ShallowClone should not copy it
    EXPECT_EQ(cloneElem->GetText(), nullptr);
    EXPECT_TRUE(cloneElem->NoChildren());

    doc->DeleteNode(clone);
}

// Test: ShallowClone preserves attribute order (check all attributes present)
TEST_F(XMLElementShallowCloneTest_265, ClonePreservesMultipleAttributes_265) {
    doc->Parse(R"(<data a="1" b="2" c="3" d="4"/>)");
    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLNode* clone = root->ShallowClone(doc);
    ASSERT_NE(clone, nullptr);

    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);

    // Count attributes
    int attrCount = 0;
    for (const XMLAttribute* a = cloneElem->FirstAttribute(); a; a = a->Next()) {
        attrCount++;
    }
    EXPECT_EQ(attrCount, 4);

    EXPECT_STREQ(cloneElem->Attribute("a"), "1");
    EXPECT_STREQ(cloneElem->Attribute("b"), "2");
    EXPECT_STREQ(cloneElem->Attribute("c"), "3");
    EXPECT_STREQ(cloneElem->Attribute("d"), "4");

    doc->DeleteNode(clone);
}

// Test: Modifying the clone's attributes does not affect the original
TEST_F(XMLElementShallowCloneTest_265, ModifyingCloneDoesNotAffectOriginal_265) {
    doc->Parse(R"(<config key="original"/>)");
    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLNode* clone = root->ShallowClone(doc);
    ASSERT_NE(clone, nullptr);

    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    cloneElem->SetAttribute("key", "modified");

    EXPECT_STREQ(root->Attribute("key"), "original");
    EXPECT_STREQ(cloneElem->Attribute("key"), "modified");

    doc->DeleteNode(clone);
}

// Test: ShallowClone of element with special characters in attribute values
TEST_F(XMLElementShallowCloneTest_265, CloneWithSpecialCharactersInAttributes_265) {
    doc->Parse(R"(<tag attr="value with &amp; special &lt;chars&gt;"/>)");
    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLNode* clone = root->ShallowClone(doc);
    ASSERT_NE(clone, nullptr);

    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Attribute("attr"), root->Attribute("attr"));

    doc->DeleteNode(clone);
}

// Test: ShallowClone of nested element (only clones the element itself)
TEST_F(XMLElementShallowCloneTest_265, CloneNestedElementOnlyClonesTarget_265) {
    doc->Parse("<root><child nested=\"yes\"><grandchild/></child></root>");
    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);

    XMLNode* clone = child->ShallowClone(doc);
    ASSERT_NE(clone, nullptr);

    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "child");
    EXPECT_STREQ(cloneElem->Attribute("nested"), "yes");
    EXPECT_TRUE(cloneElem->NoChildren());

    doc->DeleteNode(clone);
}

// Test: ShallowClone with empty string attribute value
TEST_F(XMLElementShallowCloneTest_265, CloneWithEmptyAttributeValue_265) {
    doc->Parse(R"(<elem attr=""/>)");
    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLNode* clone = root->ShallowClone(doc);
    ASSERT_NE(clone, nullptr);

    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Attribute("attr"), "");

    doc->DeleteNode(clone);
}
