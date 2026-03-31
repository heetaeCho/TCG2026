#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLCommentTest_199 : public ::testing::Test {
protected:
    XMLDocument doc1;
    XMLDocument doc2;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test ShallowEqual with two comments having the same value
TEST_F(XMLCommentTest_199, ShallowEqual_SameValue_ReturnsTrue_199) {
    doc1.Parse("<root><!-- Hello World --></root>");
    doc2.Parse("<root><!-- Hello World --></root>");

    const XMLComment* comment1 = doc1.FirstChild()->FirstChild()->ToComment();
    const XMLComment* comment2 = doc2.FirstChild()->FirstChild()->ToComment();

    ASSERT_NE(comment1, nullptr);
    ASSERT_NE(comment2, nullptr);
    EXPECT_TRUE(comment1->ShallowEqual(comment2));
}

// Test ShallowEqual with two comments having different values
TEST_F(XMLCommentTest_199, ShallowEqual_DifferentValue_ReturnsFalse_199) {
    doc1.Parse("<root><!-- Hello --></root>");
    doc2.Parse("<root><!-- World --></root>");

    const XMLComment* comment1 = doc1.FirstChild()->FirstChild()->ToComment();
    const XMLComment* comment2 = doc2.FirstChild()->FirstChild()->ToComment();

    ASSERT_NE(comment1, nullptr);
    ASSERT_NE(comment2, nullptr);
    EXPECT_FALSE(comment1->ShallowEqual(comment2));
}

// Test ShallowEqual comparing a comment with a non-comment node (element)
TEST_F(XMLCommentTest_199, ShallowEqual_CompareWithElement_ReturnsFalse_199) {
    doc1.Parse("<root><!-- Hello --></root>");
    doc2.Parse("<root><child/></root>");

    const XMLComment* comment1 = doc1.FirstChild()->FirstChild()->ToComment();
    const XMLNode* element = doc2.FirstChild()->FirstChild();

    ASSERT_NE(comment1, nullptr);
    ASSERT_NE(element, nullptr);
    ASSERT_EQ(element->ToComment(), nullptr); // It's not a comment
    EXPECT_FALSE(comment1->ShallowEqual(element));
}

// Test ShallowEqual with empty comment values
TEST_F(XMLCommentTest_199, ShallowEqual_EmptyComments_ReturnsTrue_199) {
    doc1.Parse("<root><!----></root>");
    doc2.Parse("<root><!----></root>");

    const XMLComment* comment1 = doc1.FirstChild()->FirstChild()->ToComment();
    const XMLComment* comment2 = doc2.FirstChild()->FirstChild()->ToComment();

    ASSERT_NE(comment1, nullptr);
    ASSERT_NE(comment2, nullptr);
    EXPECT_TRUE(comment1->ShallowEqual(comment2));
}

// Test ShallowEqual with same comment node (self-comparison)
TEST_F(XMLCommentTest_199, ShallowEqual_SelfComparison_ReturnsTrue_199) {
    doc1.Parse("<root><!-- Test --></root>");

    const XMLComment* comment1 = doc1.FirstChild()->FirstChild()->ToComment();
    ASSERT_NE(comment1, nullptr);
    EXPECT_TRUE(comment1->ShallowEqual(comment1));
}

// Test ShallowEqual comparing comment with text node
TEST_F(XMLCommentTest_199, ShallowEqual_CompareWithTextNode_ReturnsFalse_199) {
    doc1.Parse("<root><!-- some text --></root>");
    doc2.Parse("<root>some text</root>");

    const XMLComment* comment1 = doc1.FirstChild()->FirstChild()->ToComment();
    const XMLNode* textNode = doc2.FirstChild()->FirstChild();

    ASSERT_NE(comment1, nullptr);
    ASSERT_NE(textNode, nullptr);
    EXPECT_FALSE(comment1->ShallowEqual(textNode));
}

// Test ShallowEqual with comments having whitespace differences
TEST_F(XMLCommentTest_199, ShallowEqual_WhitespaceDifference_ReturnsFalse_199) {
    doc1.Parse("<root><!-- Hello --></root>");
    doc2.Parse("<root><!--Hello--></root>");

    const XMLComment* comment1 = doc1.FirstChild()->FirstChild()->ToComment();
    const XMLComment* comment2 = doc2.FirstChild()->FirstChild()->ToComment();

    ASSERT_NE(comment1, nullptr);
    ASSERT_NE(comment2, nullptr);
    // The values include the whitespace around the comment text
    // They might or might not be equal depending on how tinyxml2 stores them
    // This tests observable behavior
    if (XMLUtil::StringEqual(comment1->Value(), comment2->Value())) {
        EXPECT_TRUE(comment1->ShallowEqual(comment2));
    } else {
        EXPECT_FALSE(comment1->ShallowEqual(comment2));
    }
}

// Test ToComment returns non-null for comment nodes
TEST_F(XMLCommentTest_199, ToComment_ReturnsNonNull_199) {
    doc1.Parse("<root><!-- A comment --></root>");

    XMLNode* node = doc1.FirstChild()->FirstChild();
    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->ToComment(), nullptr);
}

// Test ToComment returns null for non-comment nodes
TEST_F(XMLCommentTest_199, ToComment_ReturnsNullForElement_199) {
    doc1.Parse("<root><child/></root>");

    XMLNode* node = doc1.FirstChild()->FirstChild();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->ToComment(), nullptr);
}

// Test ShallowClone creates an equivalent comment in another document
TEST_F(XMLCommentTest_199, ShallowClone_CreatesEquivalentComment_199) {
    doc1.Parse("<root><!-- Clone me --></root>");

    const XMLComment* comment1 = doc1.FirstChild()->FirstChild()->ToComment();
    ASSERT_NE(comment1, nullptr);

    XMLNode* cloned = comment1->ShallowClone(&doc2);
    ASSERT_NE(cloned, nullptr);

    XMLComment* clonedComment = cloned->ToComment();
    ASSERT_NE(clonedComment, nullptr);

    EXPECT_TRUE(comment1->ShallowEqual(clonedComment));

    // Clean up the cloned node by inserting it into doc2
    doc2.InsertEndChild(cloned);
}

// Test ShallowEqual with comment compared to XMLDeclaration
TEST_F(XMLCommentTest_199, ShallowEqual_CompareWithDeclaration_ReturnsFalse_199) {
    doc1.Parse("<!-- comment --><root/>");
    doc2.Parse("<?xml version=\"1.0\"?><root/>");

    const XMLNode* node1 = doc1.FirstChild();
    const XMLComment* comment = node1->ToComment();

    const XMLNode* node2 = doc2.FirstChild();

    if (comment != nullptr && node2 != nullptr) {
        EXPECT_FALSE(comment->ShallowEqual(node2));
    }
}

// Test Accept with a visitor
TEST_F(XMLCommentTest_199, Accept_CallsVisitor_199) {
    doc1.Parse("<root><!-- Visited --></root>");

    const XMLComment* comment = doc1.FirstChild()->FirstChild()->ToComment();
    ASSERT_NE(comment, nullptr);

    XMLPrinter printer;
    bool result = comment->Accept(&printer);
    EXPECT_TRUE(result);

    // The printer should have produced some output containing the comment
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("Visited"), std::string::npos);
}

// Test Value of a comment node
TEST_F(XMLCommentTest_199, Value_ReturnsCommentText_199) {
    doc1.Parse("<root><!-- My Comment --></root>");

    const XMLComment* comment = doc1.FirstChild()->FirstChild()->ToComment();
    ASSERT_NE(comment, nullptr);

    const char* val = comment->Value();
    ASSERT_NE(val, nullptr);
    EXPECT_NE(std::string(val).find("My Comment"), std::string::npos);
}

// Test ShallowEqual with comments in different document structures
TEST_F(XMLCommentTest_199, ShallowEqual_DifferentStructureSameComment_ReturnsTrue_199) {
    doc1.Parse("<a><b><!-- same --></b></a>");
    doc2.Parse("<x><!-- same --></x>");

    const XMLComment* comment1 = doc1.FirstChild()->FirstChild()->FirstChild()->ToComment();
    const XMLComment* comment2 = doc2.FirstChild()->FirstChild()->ToComment();

    ASSERT_NE(comment1, nullptr);
    ASSERT_NE(comment2, nullptr);
    EXPECT_TRUE(comment1->ShallowEqual(comment2));
}

// Test ShallowEqual with one empty and one non-empty comment
TEST_F(XMLCommentTest_199, ShallowEqual_EmptyVsNonEmpty_ReturnsFalse_199) {
    doc1.Parse("<root><!----></root>");
    doc2.Parse("<root><!-- not empty --></root>");

    const XMLComment* comment1 = doc1.FirstChild()->FirstChild()->ToComment();
    const XMLComment* comment2 = doc2.FirstChild()->FirstChild()->ToComment();

    ASSERT_NE(comment1, nullptr);
    ASSERT_NE(comment2, nullptr);
    EXPECT_FALSE(comment1->ShallowEqual(comment2));
}

// Test multiple comments - ShallowEqual between first and second
TEST_F(XMLCommentTest_199, ShallowEqual_MultipleComments_199) {
    doc1.Parse("<root><!-- first --><!-- second --></root>");

    const XMLNode* firstChild = doc1.FirstChild()->FirstChild();
    const XMLNode* secondChild = firstChild->NextSibling();

    const XMLComment* comment1 = firstChild->ToComment();
    const XMLComment* comment2 = secondChild->ToComment();

    ASSERT_NE(comment1, nullptr);
    ASSERT_NE(comment2, nullptr);
    EXPECT_FALSE(comment1->ShallowEqual(comment2));
}

// Test ShallowClone and then ShallowEqual
TEST_F(XMLCommentTest_199, ShallowClone_ThenShallowEqual_199) {
    doc1.Parse("<root><!-- original --></root>");

    const XMLComment* original = doc1.FirstChild()->FirstChild()->ToComment();
    ASSERT_NE(original, nullptr);

    XMLNode* clone = original->ShallowClone(&doc2);
    ASSERT_NE(clone, nullptr);

    EXPECT_TRUE(original->ShallowEqual(clone));
    EXPECT_TRUE(clone->ToComment()->ShallowEqual(original));

    doc2.InsertEndChild(clone);
}
