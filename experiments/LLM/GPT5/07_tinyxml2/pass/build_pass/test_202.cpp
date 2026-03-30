// TEST_ID: 202
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

#include <cstring>

namespace tinyxml2 {

namespace {

void ExpectSameCStr(const char* a, const char* b) {
    if (a == nullptr || b == nullptr) {
        EXPECT_EQ(a, b);
        return;
    }
    EXPECT_STREQ(a, b);
}

}  // namespace

class XMLDeclarationShallowCloneTest_202 : public ::testing::Test {
protected:
    // The tinyxml2 XMLDocument constructor in this codebase takes (processEntities, whitespaceMode).
    XMLDocument doc1{true, PRESERVE_WHITESPACE};
    XMLDocument doc2{true, PRESERVE_WHITESPACE};
};

TEST_F(XMLDeclarationShallowCloneTest_202, CloneWithExplicitDoc_CreatesDeclarationInTargetDoc_202) {
    XMLDeclaration* dec = doc1.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    ASSERT_NE(dec, nullptr);

    XMLNode* cloned = dec->ShallowClone(&doc2);
    ASSERT_NE(cloned, nullptr);
    EXPECT_NE(cloned, dec);

    // Returned node should be a declaration and belong to the target document.
    XMLDeclaration* clonedDec = cloned->ToDeclaration();
    ASSERT_NE(clonedDec, nullptr);
    EXPECT_EQ(clonedDec->GetDocument(), &doc2);

    // Value should be preserved.
    ExpectSameCStr(dec->Value(), clonedDec->Value());
}

TEST_F(XMLDeclarationShallowCloneTest_202, CloneWithNullDoc_UsesOriginalDocument_202) {
    XMLDeclaration* dec = doc1.NewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(dec, nullptr);

    XMLNode* cloned = dec->ShallowClone(nullptr);
    ASSERT_NE(cloned, nullptr);

    XMLDeclaration* clonedDec = cloned->ToDeclaration();
    ASSERT_NE(clonedDec, nullptr);

    // When nullptr is passed, the clone should be created in the original document.
    EXPECT_EQ(clonedDec->GetDocument(), &doc1);

    // Value should be preserved.
    ExpectSameCStr(dec->Value(), clonedDec->Value());
}

TEST_F(XMLDeclarationShallowCloneTest_202, ClonePreservesEmptyValue_202) {
    XMLDeclaration* dec = doc1.NewDeclaration("");
    ASSERT_NE(dec, nullptr);

    XMLNode* cloned = dec->ShallowClone(&doc1);
    ASSERT_NE(cloned, nullptr);

    XMLDeclaration* clonedDec = cloned->ToDeclaration();
    ASSERT_NE(clonedDec, nullptr);
    EXPECT_EQ(clonedDec->GetDocument(), &doc1);

    ExpectSameCStr(dec->Value(), clonedDec->Value());
}

TEST_F(XMLDeclarationShallowCloneTest_202, CloneWhenDeclarationCreatedWithNullText_DoesNotCrash_202) {
    // Some tinyxml2 builds accept nullptr text; if so, cloning should still be safe/observable.
    XMLDeclaration* dec = doc1.NewDeclaration(nullptr);
    ASSERT_NE(dec, nullptr);

    XMLNode* cloned = dec->ShallowClone(nullptr);
    ASSERT_NE(cloned, nullptr);

    XMLDeclaration* clonedDec = cloned->ToDeclaration();
    ASSERT_NE(clonedDec, nullptr);
    EXPECT_EQ(clonedDec->GetDocument(), &doc1);

    // Compare safely even if Value() can be nullptr or an empty string depending on implementation.
    ExpectSameCStr(dec->Value(), clonedDec->Value());
}

}  // namespace tinyxml2
