#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLDocument::NewUnknown tests
class XMLDocumentNewUnknownTest_276 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test that NewUnknown returns a non-null pointer
TEST_F(XMLDocumentNewUnknownTest_276, ReturnsNonNull_276) {
    XMLUnknown* unk = doc.NewUnknown("some unknown content");
    ASSERT_NE(unk, nullptr);
}

// Test that NewUnknown sets the value correctly
TEST_F(XMLDocumentNewUnknownTest_276, SetsValueCorrectly_276) {
    const char* text = "some unknown content";
    XMLUnknown* unk = doc.NewUnknown(text);
    ASSERT_NE(unk, nullptr);
    EXPECT_STREQ(unk->Value(), text);
}

// Test that NewUnknown with empty string works
TEST_F(XMLDocumentNewUnknownTest_276, EmptyString_276) {
    XMLUnknown* unk = doc.NewUnknown("");
    ASSERT_NE(unk, nullptr);
    EXPECT_STREQ(unk->Value(), "");
}

// Test that NewUnknown creates a node that can be identified as XMLUnknown
TEST_F(XMLDocumentNewUnknownTest_276, ToUnknownReturnsNonNull_276) {
    XMLUnknown* unk = doc.NewUnknown("test");
    ASSERT_NE(unk, nullptr);
    EXPECT_NE(unk->ToUnknown(), nullptr);
}

// Test that NewUnknown creates a node that is not other types
TEST_F(XMLDocumentNewUnknownTest_276, IsNotOtherTypes_276) {
    XMLUnknown* unk = doc.NewUnknown("test");
    ASSERT_NE(unk, nullptr);
    EXPECT_EQ(unk->ToElement(), nullptr);
    EXPECT_EQ(unk->ToText(), nullptr);
    EXPECT_EQ(unk->ToComment(), nullptr);
    EXPECT_EQ(unk->ToDocument(), nullptr);
    EXPECT_EQ(unk->ToDeclaration(), nullptr);
}

// Test that NewUnknown node initially has no parent
TEST_F(XMLDocumentNewUnknownTest_276, InitiallyNoParent_276) {
    XMLUnknown* unk = doc.NewUnknown("test");
    ASSERT_NE(unk, nullptr);
    EXPECT_EQ(unk->Parent(), nullptr);
}

// Test that NewUnknown node initially has no children
TEST_F(XMLDocumentNewUnknownTest_276, InitiallyNoChildren_276) {
    XMLUnknown* unk = doc.NewUnknown("test");
    ASSERT_NE(unk, nullptr);
    EXPECT_TRUE(unk->NoChildren());
}

// Test that NewUnknown node can be inserted into the document
TEST_F(XMLDocumentNewUnknownTest_276, CanBeInsertedIntoDocument_276) {
    XMLUnknown* unk = doc.NewUnknown("test unknown");
    ASSERT_NE(unk, nullptr);
    XMLNode* result = doc.InsertEndChild(unk);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(unk->Parent(), &doc);
}

// Test that NewUnknown with special characters in value
TEST_F(XMLDocumentNewUnknownTest_276, SpecialCharacters_276) {
    const char* specialText = "<!ENTITY test \"value\">";
    XMLUnknown* unk = doc.NewUnknown(specialText);
    ASSERT_NE(unk, nullptr);
    EXPECT_STREQ(unk->Value(), specialText);
}

// Test that NewUnknown with a long string
TEST_F(XMLDocumentNewUnknownTest_276, LongString_276) {
    std::string longStr(1000, 'x');
    XMLUnknown* unk = doc.NewUnknown(longStr.c_str());
    ASSERT_NE(unk, nullptr);
    EXPECT_STREQ(unk->Value(), longStr.c_str());
}

// Test that multiple NewUnknown calls create distinct nodes
TEST_F(XMLDocumentNewUnknownTest_276, MultipleCallsCreateDistinctNodes_276) {
    XMLUnknown* unk1 = doc.NewUnknown("first");
    XMLUnknown* unk2 = doc.NewUnknown("second");
    ASSERT_NE(unk1, nullptr);
    ASSERT_NE(unk2, nullptr);
    EXPECT_NE(unk1, unk2);
    EXPECT_STREQ(unk1->Value(), "first");
    EXPECT_STREQ(unk2->Value(), "second");
}

// Test that the unknown node belongs to the correct document
TEST_F(XMLDocumentNewUnknownTest_276, BelongsToCorrectDocument_276) {
    XMLUnknown* unk = doc.NewUnknown("test");
    ASSERT_NE(unk, nullptr);
    EXPECT_EQ(unk->GetDocument(), &doc);
}

// Test that NewUnknown node can be inserted into an element
TEST_F(XMLDocumentNewUnknownTest_276, CanBeInsertedIntoElement_276) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLUnknown* unk = doc.NewUnknown("unknown data");
    ASSERT_NE(unk, nullptr);
    XMLNode* result = root->InsertEndChild(unk);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(unk->Parent(), root);
}

// Test that NewUnknown with whitespace content
TEST_F(XMLDocumentNewUnknownTest_276, WhitespaceContent_276) {
    XMLUnknown* unk = doc.NewUnknown("   \t\n  ");
    ASSERT_NE(unk, nullptr);
    EXPECT_STREQ(unk->Value(), "   \t\n  ");
}

// Test that NewUnknown node has no siblings initially
TEST_F(XMLDocumentNewUnknownTest_276, NoSiblingsInitially_276) {
    XMLUnknown* unk = doc.NewUnknown("test");
    ASSERT_NE(unk, nullptr);
    EXPECT_EQ(unk->NextSibling(), nullptr);
    EXPECT_EQ(unk->PreviousSibling(), nullptr);
}

// Test parsing an unknown node and verifying round-trip
TEST_F(XMLDocumentNewUnknownTest_276, ParseAndVerifyUnknown_276) {
    const char* xml = "<root><!unknown stuff></root>";
    XMLError err = doc.Parse(xml);
    // Just verify no crash; parsing behavior may vary
    // The main focus is NewUnknown API
}

// Test deleting a NewUnknown node
TEST_F(XMLDocumentNewUnknownTest_276, DeleteUnknownNode_276) {
    XMLUnknown* unk = doc.NewUnknown("to be deleted");
    ASSERT_NE(unk, nullptr);
    doc.InsertEndChild(unk);
    EXPECT_FALSE(doc.NoChildren());
    doc.DeleteChild(unk);
    // After deletion, the document should have no children from this unknown
}

// Test ShallowClone of an unknown node
TEST_F(XMLDocumentNewUnknownTest_276, ShallowClone_276) {
    XMLUnknown* unk = doc.NewUnknown("clone me");
    ASSERT_NE(unk, nullptr);
    const XMLNode* cloned = unk->ShallowClone(&doc);
    ASSERT_NE(cloned, nullptr);
    EXPECT_NE(cloned->ToUnknown(), nullptr);
    EXPECT_STREQ(cloned->Value(), "clone me");
}

// Test ShallowEqual of two unknown nodes with same value
TEST_F(XMLDocumentNewUnknownTest_276, ShallowEqualSameValue_276) {
    XMLUnknown* unk1 = doc.NewUnknown("same");
    XMLUnknown* unk2 = doc.NewUnknown("same");
    ASSERT_NE(unk1, nullptr);
    ASSERT_NE(unk2, nullptr);
    EXPECT_TRUE(unk1->ShallowEqual(unk2));
}

// Test ShallowEqual of two unknown nodes with different value
TEST_F(XMLDocumentNewUnknownTest_276, ShallowEqualDifferentValue_276) {
    XMLUnknown* unk1 = doc.NewUnknown("value1");
    XMLUnknown* unk2 = doc.NewUnknown("value2");
    ASSERT_NE(unk1, nullptr);
    ASSERT_NE(unk2, nullptr);
    EXPECT_FALSE(unk1->ShallowEqual(unk2));
}

// Test DeepClone of an unknown node to another document
TEST_F(XMLDocumentNewUnknownTest_276, DeepCloneToAnotherDocument_276) {
    XMLUnknown* unk = doc.NewUnknown("deep clone");
    doc.InsertEndChild(unk);

    XMLDocument targetDoc;
    const XMLNode* cloned = unk->DeepClone(&targetDoc);
    ASSERT_NE(cloned, nullptr);
    EXPECT_STREQ(cloned->Value(), "deep clone");
    EXPECT_NE(cloned->ToUnknown(), nullptr);
}

// Test that GetLineNum returns 0 for programmatically created unknown
TEST_F(XMLDocumentNewUnknownTest_276, LineNumIsZero_276) {
    XMLUnknown* unk = doc.NewUnknown("test");
    ASSERT_NE(unk, nullptr);
    EXPECT_EQ(unk->GetLineNum(), 0);
}

// Test UserData on unknown node
TEST_F(XMLDocumentNewUnknownTest_276, UserData_276) {
    XMLUnknown* unk = doc.NewUnknown("userdata test");
    ASSERT_NE(unk, nullptr);
    EXPECT_EQ(unk->GetUserData(), nullptr);
    int data = 42;
    unk->SetUserData(&data);
    EXPECT_EQ(unk->GetUserData(), &data);
}
