// TEST_ID: 268
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

#include <memory>
#include <string>

using namespace tinyxml2;

namespace {

class XMLDocumentDestructorTest_268 : public ::testing::Test {
protected:
    static constexpr bool kProcessEntities = true;

    // tinyxml2 exposes Whitespace enum; pick a stable default.
    static constexpr Whitespace kWs = COLLAPSE_WHITESPACE;

    static std::unique_ptr<XMLDocument> MakeDoc() {
        return std::make_unique<XMLDocument>(kProcessEntities, kWs);
    }
};

}  // namespace

TEST_F(XMLDocumentDestructorTest_268, DeleteEmptyDocument_NoCrash_268) {
    // The observable requirement for the destructor here is that it is safe to call
    // on a freshly created document (no crashes / no exceptions).
    auto doc = MakeDoc();
    ASSERT_NE(doc, nullptr);
    EXPECT_NO_THROW(doc.reset());  // invokes ~XMLDocument()
}

TEST_F(XMLDocumentDestructorTest_268, DeleteAfterClearCalledExplicitly_Idempotent_268) {
    auto doc = MakeDoc();
    ASSERT_NE(doc, nullptr);

    // Clear() is public and should be safe to call even if the destructor also calls Clear().
    EXPECT_NO_THROW(doc->Clear());
    EXPECT_NO_THROW(doc.reset());  // destructor calls Clear() again
}

TEST_F(XMLDocumentDestructorTest_268, DeleteAfterSuccessfulParse_NoCrash_268) {
    auto doc = MakeDoc();
    ASSERT_NE(doc, nullptr);

    const char* xml = "<root><child id=\"1\">text</child></root>";
    XMLError err = doc->Parse(xml, strlen(xml));
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc->Error());
    EXPECT_NE(doc->RootElement(), nullptr);

    EXPECT_NO_THROW(doc.reset());  // destructor clears internal state
}

TEST_F(XMLDocumentDestructorTest_268, DeleteAfterParseErrorState_NoCrash_268) {
    auto doc = MakeDoc();
    ASSERT_NE(doc, nullptr);

    // Intentionally malformed XML to set an error state.
    const char* badXml = "<root><unclosed></root>";
    XMLError err = doc->Parse(badXml, strlen(badXml));
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc->Error());

    // Destructor should still be safe when an error has been recorded.
    EXPECT_NO_THROW(doc.reset());
}

TEST_F(XMLDocumentDestructorTest_268, DeleteWithUnlinkedNewNodes_NoCrash_268) {
    auto doc = MakeDoc();
    ASSERT_NE(doc, nullptr);

    // Create nodes via the public factory methods, but do NOT link them into the tree.
    // This exercises destructor cleanup of any unlinked allocations managed by the document.
    XMLElement* e = doc->NewElement("unlinked");
    ASSERT_NE(e, nullptr);

    XMLText* t = doc->NewText("also unlinked");
    ASSERT_NE(t, nullptr);

    XMLComment* c = doc->NewComment("comment");
    ASSERT_NE(c, nullptr);

    XMLDeclaration* d = doc->NewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(d, nullptr);

    XMLUnknown* u = doc->NewUnknown("<?something?>");
    ASSERT_NE(u, nullptr);

    // No further observable behavior required other than safe destruction.
    EXPECT_NO_THROW(doc.reset());
}

TEST_F(XMLDocumentDestructorTest_268, DeleteAfterDeepCopyTargetCleanup_NoCrash_268) {
    auto src = MakeDoc();
    auto dst = MakeDoc();
    ASSERT_NE(src, nullptr);
    ASSERT_NE(dst, nullptr);

    const char* xml = "<r><a/><b>v</b></r>";
    ASSERT_EQ(src->Parse(xml, strlen(xml)), XML_SUCCESS);
    ASSERT_FALSE(src->Error());
    ASSERT_NE(src->RootElement(), nullptr);

    // DeepCopy is public; even without inspecting internals, we can ensure both
    // documents remain safely destructible after copy operations.
    EXPECT_NO_THROW(src->DeepCopy(dst.get()));
    EXPECT_NO_THROW(src.reset());
    EXPECT_NO_THROW(dst.reset());
}
