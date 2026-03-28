#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementInsertNewUnknownTest_263 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* root;

    void SetUp() override {
        doc.Parse("<root></root>");
        root = doc.RootElement();
        ASSERT_NE(root, nullptr);
    }
};

// Test that InsertNewUnknown returns a non-null pointer for valid text
TEST_F(XMLElementInsertNewUnknownTest_263, ReturnsNonNullForValidText_263) {
    XMLUnknown* unknown = root->InsertNewUnknown("some unknown content");
    ASSERT_NE(unknown, nullptr);
}

// Test that the inserted unknown node has the correct value
TEST_F(XMLElementInsertNewUnknownTest_263, InsertedUnknownHasCorrectValue_263) {
    const char* text = "some unknown content";
    XMLUnknown* unknown = root->InsertNewUnknown(text);
    ASSERT_NE(unknown, nullptr);
    EXPECT_STREQ(unknown->Value(), text);
}

// Test that InsertNewUnknown adds the node as the last child
TEST_F(XMLElementInsertNewUnknownTest_263, InsertsAsLastChild_263) {
    root->InsertNewChildElement("child1");
    XMLUnknown* unknown = root->InsertNewUnknown("unknown text");
    ASSERT_NE(unknown, nullptr);

    const XMLNode* lastChild = root->LastChild();
    ASSERT_NE(lastChild, nullptr);
    EXPECT_EQ(lastChild->ToUnknown(), unknown);
}

// Test that InsertNewUnknown with empty string works
TEST_F(XMLElementInsertNewUnknownTest_263, EmptyStringText_263) {
    XMLUnknown* unknown = root->InsertNewUnknown("");
    ASSERT_NE(unknown, nullptr);
    EXPECT_STREQ(unknown->Value(), "");
}

// Test that multiple InsertNewUnknown calls add multiple children
TEST_F(XMLElementInsertNewUnknownTest_263, MultipleInsertions_263) {
    XMLUnknown* u1 = root->InsertNewUnknown("first");
    XMLUnknown* u2 = root->InsertNewUnknown("second");
    XMLUnknown* u3 = root->InsertNewUnknown("third");

    ASSERT_NE(u1, nullptr);
    ASSERT_NE(u2, nullptr);
    ASSERT_NE(u3, nullptr);

    // Verify ordering: first child should be u1, last should be u3
    const XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    EXPECT_EQ(firstChild->ToUnknown(), u1);

    const XMLNode* lastChild = root->LastChild();
    ASSERT_NE(lastChild, nullptr);
    EXPECT_EQ(lastChild->ToUnknown(), u3);
}

// Test that the unknown node is a child of the element
TEST_F(XMLElementInsertNewUnknownTest_263, ParentIsCorrect_263) {
    XMLUnknown* unknown = root->InsertNewUnknown("test");
    ASSERT_NE(unknown, nullptr);
    EXPECT_EQ(unknown->Parent(), root);
}

// Test that the inserted unknown node is of XMLUnknown type
TEST_F(XMLElementInsertNewUnknownTest_263, NodeIsUnknownType_263) {
    XMLUnknown* unknown = root->InsertNewUnknown("type check");
    ASSERT_NE(unknown, nullptr);
    EXPECT_NE(unknown->ToUnknown(), nullptr);
    EXPECT_EQ(unknown->ToElement(), nullptr);
    EXPECT_EQ(unknown->ToText(), nullptr);
    EXPECT_EQ(unknown->ToComment(), nullptr);
    EXPECT_EQ(unknown->ToDeclaration(), nullptr);
    EXPECT_EQ(unknown->ToDocument(), nullptr);
}

// Test that the element is no longer empty after inserting unknown
TEST_F(XMLElementInsertNewUnknownTest_263, ElementNoLongerEmpty_263) {
    EXPECT_TRUE(root->NoChildren());
    root->InsertNewUnknown("content");
    EXPECT_FALSE(root->NoChildren());
}

// Test InsertNewUnknown with special characters in text
TEST_F(XMLElementInsertNewUnknownTest_263, SpecialCharactersInText_263) {
    const char* specialText = "<!DOCTYPE html>";
    XMLUnknown* unknown = root->InsertNewUnknown(specialText);
    ASSERT_NE(unknown, nullptr);
    EXPECT_STREQ(unknown->Value(), specialText);
}

// Test that InsertNewUnknown works alongside other child types
TEST_F(XMLElementInsertNewUnknownTest_263, MixedChildTypes_263) {
    root->InsertNewChildElement("elem");
    root->InsertNewComment("a comment");
    root->InsertNewText("some text");
    XMLUnknown* unknown = root->InsertNewUnknown("unknown data");
    root->InsertNewDeclaration("xml version=\"1.0\"");

    ASSERT_NE(unknown, nullptr);
    EXPECT_STREQ(unknown->Value(), "unknown data");

    // The element should have 5 children total
    int count = 0;
    for (const XMLNode* child = root->FirstChild(); child; child = child->NextSibling()) {
        count++;
    }
    EXPECT_EQ(count, 5);
}

// Test that the document can be printed after inserting unknown
TEST_F(XMLElementInsertNewUnknownTest_263, PrintAfterInsert_263) {
    root->InsertNewUnknown("some unknown");
    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    // The output should contain the unknown markup
    EXPECT_NE(std::string(result).find("some unknown"), std::string::npos);
}

// Test InsertNewUnknown on a deeply nested element
TEST_F(XMLElementInsertNewUnknownTest_263, DeeplyNestedElement_263) {
    XMLDocument doc2;
    doc2.Parse("<a><b><c></c></b></a>");
    XMLElement* c = doc2.RootElement()->FirstChildElement("b")->FirstChildElement("c");
    ASSERT_NE(c, nullptr);

    XMLUnknown* unknown = c->InsertNewUnknown("deep unknown");
    ASSERT_NE(unknown, nullptr);
    EXPECT_STREQ(unknown->Value(), "deep unknown");
    EXPECT_EQ(unknown->Parent(), c);
}

// Test that InsertNewUnknown with long text works
TEST_F(XMLElementInsertNewUnknownTest_263, LongText_263) {
    std::string longText(1000, 'x');
    XMLUnknown* unknown = root->InsertNewUnknown(longText.c_str());
    ASSERT_NE(unknown, nullptr);
    EXPECT_STREQ(unknown->Value(), longText.c_str());
}

// Test InsertNewUnknown preserves existing children order
TEST_F(XMLElementInsertNewUnknownTest_263, PreservesExistingChildrenOrder_263) {
    XMLElement* child1 = root->InsertNewChildElement("first");
    XMLElement* child2 = root->InsertNewChildElement("second");
    XMLUnknown* unknown = root->InsertNewUnknown("appended");

    ASSERT_NE(unknown, nullptr);

    const XMLNode* node = root->FirstChild();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->ToElement(), child1);

    node = node->NextSibling();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->ToElement(), child2);

    node = node->NextSibling();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->ToUnknown(), unknown);

    EXPECT_EQ(node->NextSibling(), nullptr);
}
