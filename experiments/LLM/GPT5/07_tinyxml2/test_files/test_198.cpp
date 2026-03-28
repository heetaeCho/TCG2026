// File: ./TestProjects/tinyxml2/tests/xmlcomment_shallowclone_test_198.cpp

#include <gtest/gtest.h>
#include <cstring>
#include "tinyxml2.h"

namespace tinyxml2 {

class XMLCommentShallowCloneTest_198 : public ::testing::Test {
protected:
    // Use the same ctor signature shown in the provided header snippet.
    // (If your project exposes a different XMLDocument constructor, adjust here.)
    XMLDocument doc_{true, PRESERVE_WHITESPACE};

    XMLComment* NewCommentInDoc(XMLDocument& d, const char* text) {
        return d.NewComment(text);
    }
};

TEST_F(XMLCommentShallowCloneTest_198, CloneWithNullDocUsesOwningDocument_198) {
    XMLComment* original = NewCommentInDoc(doc_, "hello");
    ASSERT_NE(original, nullptr);

    XMLNode* cloned = original->ShallowClone(nullptr);
    ASSERT_NE(cloned, nullptr);
    EXPECT_NE(cloned, original);

    // Should be a comment node.
    EXPECT_NE(cloned->ToComment(), nullptr);

    // Value should match.
    ASSERT_NE(cloned->Value(), nullptr);
    EXPECT_STREQ(cloned->Value(), original->Value());

    // When passing nullptr, it should use the owning document (observable via GetDocument()).
    EXPECT_EQ(cloned->GetDocument(), original->GetDocument());
}

TEST_F(XMLCommentShallowCloneTest_198, CloneWithExplicitTargetDocumentBelongsToThatDocument_198) {
    XMLComment* original = NewCommentInDoc(doc_, "world");
    ASSERT_NE(original, nullptr);

    XMLDocument otherDoc(true, PRESERVE_WHITESPACE);

    XMLNode* cloned = original->ShallowClone(&otherDoc);
    ASSERT_NE(cloned, nullptr);
    EXPECT_NE(cloned, original);
    EXPECT_NE(cloned->ToComment(), nullptr);

    ASSERT_NE(cloned->Value(), nullptr);
    EXPECT_STREQ(cloned->Value(), original->Value());

    // Should now be associated with the provided document.
    EXPECT_EQ(cloned->GetDocument(), &otherDoc);
    EXPECT_NE(cloned->GetDocument(), original->GetDocument());
}

TEST_F(XMLCommentShallowCloneTest_198, ClonePreservesEmptyCommentValue_198) {
    XMLComment* original = NewCommentInDoc(doc_, "");
    ASSERT_NE(original, nullptr);

    XMLNode* cloned = original->ShallowClone(nullptr);
    ASSERT_NE(cloned, nullptr);
    EXPECT_NE(cloned->ToComment(), nullptr);

    ASSERT_NE(original->Value(), nullptr);
    ASSERT_NE(cloned->Value(), nullptr);
    EXPECT_STREQ(cloned->Value(), original->Value());
    EXPECT_STREQ(cloned->Value(), "");
}

TEST_F(XMLCommentShallowCloneTest_198, ClonePreservesWhitespaceAndPunctuation_198) {
    const char* text = "  a comment, with punctuation!  ";
    XMLComment* original = NewCommentInDoc(doc_, text);
    ASSERT_NE(original, nullptr);

    XMLNode* cloned = original->ShallowClone(nullptr);
    ASSERT_NE(cloned, nullptr);

    ASSERT_NE(cloned->Value(), nullptr);
    EXPECT_STREQ(cloned->Value(), original->Value());
    EXPECT_STREQ(cloned->Value(), text);
}

TEST_F(XMLCommentShallowCloneTest_198, CloneHandlesLongCommentText_198) {
    // Build a long string deterministically.
    std::string longText;
    longText.reserve(8192);
    for (int i = 0; i < 4096; ++i) {
        longText.push_back(static_cast<char>('a' + (i % 26)));
    }

    XMLComment* original = NewCommentInDoc(doc_, longText.c_str());
    ASSERT_NE(original, nullptr);

    XMLNode* cloned = original->ShallowClone(nullptr);
    ASSERT_NE(cloned, nullptr);
    EXPECT_NE(cloned->ToComment(), nullptr);

    ASSERT_NE(cloned->Value(), nullptr);
    EXPECT_STREQ(cloned->Value(), original->Value());
    EXPECT_EQ(std::strlen(cloned->Value()), longText.size());
}

TEST_F(XMLCommentShallowCloneTest_198, CloneDoesNotModifyOriginal_198) {
    XMLComment* original = NewCommentInDoc(doc_, "original");
    ASSERT_NE(original, nullptr);

    const std::string before = original->Value() ? original->Value() : "";

    XMLNode* cloned = original->ShallowClone(nullptr);
    ASSERT_NE(cloned, nullptr);

    const std::string after = original->Value() ? original->Value() : "";
    EXPECT_EQ(after, before);

    // Also ensure cloned is independent by pointer identity.
    EXPECT_NE(cloned, original);
    EXPECT_STREQ(cloned->Value(), before.c_str());
}

}  // namespace tinyxml2
