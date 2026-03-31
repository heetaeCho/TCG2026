#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLDocument::NewText tests
class NewTextTest_274 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Normal operation: NewText returns a non-null pointer
TEST_F(NewTextTest_274, ReturnsNonNull_274) {
    XMLText* text = doc.NewText("Hello World");
    ASSERT_NE(text, nullptr);
}

// Normal operation: NewText sets the value correctly
TEST_F(NewTextTest_274, SetsValueCorrectly_274) {
    XMLText* text = doc.NewText("Hello World");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "Hello World");
}

// Normal operation: NewText with empty string
TEST_F(NewTextTest_274, EmptyString_274) {
    XMLText* text = doc.NewText("");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "");
}

// Normal operation: NewText with special characters
TEST_F(NewTextTest_274, SpecialCharacters_274) {
    XMLText* text = doc.NewText("<>&\"'");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "<>&\"'");
}

// Normal operation: NewText with whitespace content
TEST_F(NewTextTest_274, WhitespaceContent_274) {
    XMLText* text = doc.NewText("   \t\n  ");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "   \t\n  ");
}

// Normal operation: NewText with long string
TEST_F(NewTextTest_274, LongString_274) {
    std::string longStr(10000, 'A');
    XMLText* text = doc.NewText(longStr.c_str());
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), longStr.c_str());
}

// Verify the returned text is of type XMLText (ToText should return non-null)
TEST_F(NewTextTest_274, IsTextNode_274) {
    XMLText* text = doc.NewText("test");
    ASSERT_NE(text, nullptr);
    EXPECT_NE(text->ToText(), nullptr);
}

// Verify the returned text is not an element
TEST_F(NewTextTest_274, IsNotElement_274) {
    XMLText* text = doc.NewText("test");
    ASSERT_NE(text, nullptr);
    EXPECT_EQ(text->ToElement(), nullptr);
}

// Verify the returned text is not a comment
TEST_F(NewTextTest_274, IsNotComment_274) {
    XMLText* text = doc.NewText("test");
    ASSERT_NE(text, nullptr);
    EXPECT_EQ(text->ToComment(), nullptr);
}

// Verify the text node belongs to the same document
TEST_F(NewTextTest_274, BelongsToDocument_274) {
    XMLText* text = doc.NewText("test");
    ASSERT_NE(text, nullptr);
    EXPECT_EQ(text->GetDocument(), &doc);
}

// Verify the text node has no parent initially (unlinked)
TEST_F(NewTextTest_274, NoParentInitially_274) {
    XMLText* text = doc.NewText("test");
    ASSERT_NE(text, nullptr);
    EXPECT_EQ(text->Parent(), nullptr);
}

// Verify the text node has no children
TEST_F(NewTextTest_274, NoChildren_274) {
    XMLText* text = doc.NewText("test");
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->NoChildren());
}

// Multiple NewText calls return distinct nodes
TEST_F(NewTextTest_274, MultipleCallsReturnDistinctNodes_274) {
    XMLText* text1 = doc.NewText("first");
    XMLText* text2 = doc.NewText("second");
    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    EXPECT_NE(text1, text2);
    EXPECT_STREQ(text1->Value(), "first");
    EXPECT_STREQ(text2->Value(), "second");
}

// NewText node can be inserted into an element
TEST_F(NewTextTest_274, CanBeInsertedIntoElement_274) {
    XMLElement* elem = doc.NewElement("root");
    doc.InsertFirstChild(elem);
    XMLText* text = doc.NewText("content");
    ASSERT_NE(text, nullptr);
    XMLNode* inserted = elem->InsertEndChild(text);
    EXPECT_NE(inserted, nullptr);
    EXPECT_STREQ(elem->GetText(), "content");
}

// NewText with unicode/multibyte content
TEST_F(NewTextTest_274, UnicodeContent_274) {
    XMLText* text = doc.NewText("こんにちは世界");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "こんにちは世界");
}

// NewText with newline characters
TEST_F(NewTextTest_274, NewlineCharacters_274) {
    XMLText* text = doc.NewText("line1\nline2\nline3");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "line1\nline2\nline3");
}

// NewText node can be deleted via document
TEST_F(NewTextTest_274, CanBeDeletedViaDocument_274) {
    XMLText* text = doc.NewText("to delete");
    ASSERT_NE(text, nullptr);
    // Inserting into document so it gets managed, then deleting
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    root->InsertEndChild(text);
    doc.DeleteNode(text);
    // After deletion, root should have no children
    EXPECT_TRUE(root->NoChildren());
}

// NewText with XML-like content (should be treated as text, not parsed)
TEST_F(NewTextTest_274, XMLLikeContent_274) {
    XMLText* text = doc.NewText("<element attr=\"val\"/>");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "<element attr=\"val\"/>");
}

// Verify text node has no siblings when standalone
TEST_F(NewTextTest_274, NoSiblingsWhenStandalone_274) {
    XMLText* text = doc.NewText("alone");
    ASSERT_NE(text, nullptr);
    EXPECT_EQ(text->NextSibling(), nullptr);
    EXPECT_EQ(text->PreviousSibling(), nullptr);
}

// NewText with single character
TEST_F(NewTextTest_274, SingleCharacter_274) {
    XMLText* text = doc.NewText("X");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "X");
}

// DeepClone of a text node preserves value
TEST_F(NewTextTest_274, DeepClonePreservesValue_274) {
    XMLText* text = doc.NewText("cloneable");
    ASSERT_NE(text, nullptr);

    XMLDocument targetDoc;
    const XMLNode* clone = text->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);
    EXPECT_STREQ(clone->Value(), "cloneable");
    EXPECT_NE(clone->ToText(), nullptr);
}
