#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementInsertNewChildElementTest_259 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test that InsertNewChildElement returns a non-null pointer for a valid name
TEST_F(XMLElementInsertNewChildElementTest_259, ReturnsNonNullElement_259) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = root->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
}

// Test that the returned element has the correct name
TEST_F(XMLElementInsertNewChildElementTest_259, ChildHasCorrectName_259) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = root->InsertNewChildElement("myChild");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "myChild");
}

// Test that the child is actually a child of the parent element
TEST_F(XMLElementInsertNewChildElementTest_259, ChildIsAddedAsChild_259) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertNewChildElement("child1");

    const XMLElement* found = root->FirstChildElement("child1");
    ASSERT_NE(found, nullptr);
    EXPECT_STREQ(found->Name(), "child1");
}

// Test inserting multiple children and verifying they are all present
TEST_F(XMLElementInsertNewChildElementTest_259, MultipleChildrenInserted_259) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertNewChildElement("child1");
    root->InsertNewChildElement("child2");
    root->InsertNewChildElement("child3");

    EXPECT_EQ(root->ChildElementCount(), 3);

    EXPECT_NE(root->FirstChildElement("child1"), nullptr);
    EXPECT_NE(root->FirstChildElement("child2"), nullptr);
    EXPECT_NE(root->FirstChildElement("child3"), nullptr);
}

// Test that InsertNewChildElement appends at the end
TEST_F(XMLElementInsertNewChildElementTest_259, ChildrenAppendedAtEnd_259) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertNewChildElement("first");
    root->InsertNewChildElement("second");
    root->InsertNewChildElement("third");

    const XMLElement* firstChild = root->FirstChildElement();
    ASSERT_NE(firstChild, nullptr);
    EXPECT_STREQ(firstChild->Name(), "first");

    const XMLElement* lastChild = root->LastChildElement();
    ASSERT_NE(lastChild, nullptr);
    EXPECT_STREQ(lastChild->Name(), "third");
}

// Test that InsertNewChildElement works on a deeply nested element
TEST_F(XMLElementInsertNewChildElementTest_259, DeepNesting_259) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* level1 = root->InsertNewChildElement("level1");
    ASSERT_NE(level1, nullptr);

    XMLElement* level2 = level1->InsertNewChildElement("level2");
    ASSERT_NE(level2, nullptr);

    XMLElement* level3 = level2->InsertNewChildElement("level3");
    ASSERT_NE(level3, nullptr);

    EXPECT_STREQ(level3->Name(), "level3");
    EXPECT_NE(root->FirstChildElement("level1"), nullptr);
    EXPECT_NE(level1->FirstChildElement("level2"), nullptr);
    EXPECT_NE(level2->FirstChildElement("level3"), nullptr);
}

// Test that the parent of the inserted child is correct
TEST_F(XMLElementInsertNewChildElementTest_259, ChildParentIsCorrect_259) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = root->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);

    const XMLNode* parent = child->Parent();
    ASSERT_NE(parent, nullptr);
    EXPECT_EQ(parent, root);
}

// Test that NoChildren returns false after inserting a child
TEST_F(XMLElementInsertNewChildElementTest_259, NoChildrenReturnsFalseAfterInsert_259) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_TRUE(root->NoChildren());

    root->InsertNewChildElement("child");

    EXPECT_FALSE(root->NoChildren());
}

// Test inserting a child element with an empty string name
TEST_F(XMLElementInsertNewChildElementTest_259, EmptyStringName_259) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = root->InsertNewChildElement("");
    // Should still create the element (tinyxml2 doesn't reject empty names)
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "");
}

// Test that the inserted child belongs to the same document
TEST_F(XMLElementInsertNewChildElementTest_259, ChildBelongsToSameDocument_259) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = root->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);

    EXPECT_EQ(child->GetDocument(), root->GetDocument());
    EXPECT_EQ(child->GetDocument(), &doc);
}

// Test that inserted child can be converted to XMLElement
TEST_F(XMLElementInsertNewChildElementTest_259, ChildIsXMLElement_259) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = root->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);

    EXPECT_NE(child->ToElement(), nullptr);
}

// Test inserting children with the same name
TEST_F(XMLElementInsertNewChildElementTest_259, DuplicateChildNames_259) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertNewChildElement("item");
    root->InsertNewChildElement("item");
    root->InsertNewChildElement("item");

    EXPECT_EQ(root->ChildElementCount(), 3);

    // First one should be retrievable
    const XMLElement* first = root->FirstChildElement("item");
    ASSERT_NE(first, nullptr);

    // There should be a next sibling with the same name
    const XMLElement* second = first->NextSiblingElement("item");
    ASSERT_NE(second, nullptr);

    const XMLElement* third = second->NextSiblingElement("item");
    ASSERT_NE(third, nullptr);

    // No more after that
    EXPECT_EQ(third->NextSiblingElement("item"), nullptr);
}

// Test inserting a child with a long name
TEST_F(XMLElementInsertNewChildElementTest_259, LongElementName_259) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    std::string longName(1000, 'a');
    XMLElement* child = root->InsertNewChildElement(longName.c_str());
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), longName.c_str());
}

// Test that we can set attributes on the newly inserted child
TEST_F(XMLElementInsertNewChildElementTest_259, CanSetAttributesOnChild_259) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = root->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);

    child->SetAttribute("key", "value");
    EXPECT_STREQ(child->Attribute("key"), "value");
}

// Test that we can set text on the newly inserted child
TEST_F(XMLElementInsertNewChildElementTest_259, CanSetTextOnChild_259) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = root->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);

    child->SetText("Hello World");
    EXPECT_STREQ(child->GetText(), "Hello World");
}

// Test that deleting children after InsertNewChildElement works
TEST_F(XMLElementInsertNewChildElementTest_259, DeleteChildrenAfterInsert_259) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertNewChildElement("child1");
    root->InsertNewChildElement("child2");

    EXPECT_EQ(root->ChildElementCount(), 2);

    root->DeleteChildren();

    EXPECT_TRUE(root->NoChildren());
    EXPECT_EQ(root->ChildElementCount(), 0);
}

// Test serialization after InsertNewChildElement
TEST_F(XMLElementInsertNewChildElementTest_259, SerializationAfterInsert_259) {
    doc.InsertEndChild(doc.NewElement("root"));
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->InsertNewChildElement("child");

    XMLPrinter printer;
    doc.Print(&printer);

    const char* output = printer.CStr();
    EXPECT_NE(output, nullptr);
    // The output should contain both "root" and "child"
    EXPECT_NE(std::string(output).find("root"), std::string::npos);
    EXPECT_NE(std::string(output).find("child"), std::string::npos);
}

// Test that special characters in element names are preserved
TEST_F(XMLElementInsertNewChildElementTest_259, SpecialCharactersInName_259) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = root->InsertNewChildElement("my-child_element.v2");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "my-child_element.v2");
}
