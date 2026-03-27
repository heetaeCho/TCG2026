// File: ./TestProjects/tinyxml2/tests/xml_document_new_unknown_test_276.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

namespace tinyxml2 {

class XMLDocumentNewUnknownTest_276 : public ::testing::Test {
protected:
    // Use explicit constructor args from the public interface.
    XMLDocumentNewUnknownTest_276()
        : doc_(/*processEntities=*/true, /*whitespaceMode=*/PRESERVE_WHITESPACE) {}

    XMLDocument doc_;
};

TEST_F(XMLDocumentNewUnknownTest_276, CreatesUnknownAndSetsValue_276) {
    const char* kText = "some-unknown";

    XMLUnknown* unk = doc_.NewUnknown(kText);

    ASSERT_NE(unk, nullptr);
    EXPECT_EQ(unk->GetDocument(), &doc_);

    // Observable type behavior via public virtual conversions.
    EXPECT_EQ(unk->ToUnknown(), unk);
    EXPECT_EQ(unk->ToElement(), nullptr);
    EXPECT_EQ(unk->ToText(), nullptr);
    EXPECT_EQ(unk->ToComment(), nullptr);
    EXPECT_EQ(unk->ToDeclaration(), nullptr);
    EXPECT_EQ(unk->ToDocument(), nullptr);

    // Observable stored value.
    ASSERT_NE(unk->Value(), nullptr);
    EXPECT_STREQ(unk->Value(), kText);
}

TEST_F(XMLDocumentNewUnknownTest_276, NewUnknownDoesNotLinkIntoDocumentTree_276) {
    // Before: a fresh doc should have no children via public API.
    EXPECT_TRUE(doc_.NoChildren());
    EXPECT_EQ(doc_.FirstChild(), nullptr);
    EXPECT_EQ(doc_.LastChild(), nullptr);

    XMLUnknown* unk = doc_.NewUnknown("u1");
    ASSERT_NE(unk, nullptr);

    // Returned node is expected to be unlinked: parent remains null, and doc still has no children.
    EXPECT_EQ(unk->Parent(), nullptr);
    EXPECT_TRUE(doc_.NoChildren());
    EXPECT_EQ(doc_.FirstChild(), nullptr);
    EXPECT_EQ(doc_.LastChild(), nullptr);
}

TEST_F(XMLDocumentNewUnknownTest_276, AcceptsEmptyString_276) {
    XMLUnknown* unk = doc_.NewUnknown("");
    ASSERT_NE(unk, nullptr);
    ASSERT_NE(unk->Value(), nullptr);
    EXPECT_STREQ(unk->Value(), "");
}

TEST_F(XMLDocumentNewUnknownTest_276, StoresLargeString_276) {
    std::string large(4096, 'x');
    XMLUnknown* unk = doc_.NewUnknown(large.c_str());

    ASSERT_NE(unk, nullptr);
    ASSERT_NE(unk->Value(), nullptr);
    EXPECT_STREQ(unk->Value(), large.c_str());
}

TEST_F(XMLDocumentNewUnknownTest_276, MultipleCallsReturnDistinctNodesWithIndependentValues_276) {
    XMLUnknown* u1 = doc_.NewUnknown("first");
    XMLUnknown* u2 = doc_.NewUnknown("second");

    ASSERT_NE(u1, nullptr);
    ASSERT_NE(u2, nullptr);
    EXPECT_NE(u1, u2);

    EXPECT_STREQ(u1->Value(), "first");
    EXPECT_STREQ(u2->Value(), "second");

    EXPECT_EQ(u1->GetDocument(), &doc_);
    EXPECT_EQ(u2->GetDocument(), &doc_);
}

TEST_F(XMLDocumentNewUnknownTest_276, DocumentDestructionWithManyUnlinkedUnknownNodesDoesNotCrash_276) {
    // Create and destroy a separate document in a nested scope.
    // This test verifies observable safety (no crash) on teardown with many allocations.
    {
        XMLDocument localDoc(/*processEntities=*/true, /*whitespaceMode=*/PRESERVE_WHITESPACE);
        for (int i = 0; i < 1000; ++i) {
            std::string text = "unk-" + std::to_string(i);
            XMLUnknown* unk = localDoc.NewUnknown(text.c_str());
            ASSERT_NE(unk, nullptr);
            EXPECT_STREQ(unk->Value(), text.c_str());
            EXPECT_EQ(unk->GetDocument(), &localDoc);
        }
        // localDoc goes out of scope here; test passes if no crash occurs.
    }
    SUCCEED();
}

}  // namespace tinyxml2
