// TEST_ID: 272
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLDocumentNewElementTest_272 : public ::testing::Test {
protected:
    // Avoid depending on specific Whitespace enum names (not guaranteed in the prompt snippet).
    XMLDocumentNewElementTest_272()
        : doc_(/*processEntities=*/true, static_cast<Whitespace>(0)) {}

    XMLDocument doc_;
};

TEST_F(XMLDocumentNewElementTest_272, NewElementReturnsNonNull_272) {
    XMLElement* e = doc_.NewElement("root");
    ASSERT_NE(e, nullptr);
    // Basic sanity that the returned node is an element.
    EXPECT_NE(e->ToElement(), nullptr);
}

TEST_F(XMLDocumentNewElementTest_272, NewElementSetsProvidedName_272) {
    const char* kName = "myElement";
    XMLElement* e = doc_.NewElement(kName);
    ASSERT_NE(e, nullptr);

    const char* actual = e->Name();
    ASSERT_NE(actual, nullptr);
    EXPECT_STREQ(actual, kName);
}

TEST_F(XMLDocumentNewElementTest_272, NewElementAcceptsEmptyName_272) {
    XMLElement* e = doc_.NewElement("");
    ASSERT_NE(e, nullptr);

    const char* actual = e->Name();
    ASSERT_NE(actual, nullptr);
    EXPECT_STREQ(actual, "");
}

TEST_F(XMLDocumentNewElementTest_272, NewElementHandlesLongName_272) {
    std::string longName(1024, 'a');
    XMLElement* e = doc_.NewElement(longName.c_str());
    ASSERT_NE(e, nullptr);

    const char* actual = e->Name();
    ASSERT_NE(actual, nullptr);
    EXPECT_STREQ(actual, longName.c_str());
}

TEST_F(XMLDocumentNewElementTest_272, MultipleCallsReturnDistinctElementsWithIndependentNames_272) {
    XMLElement* a = doc_.NewElement("A");
    XMLElement* b = doc_.NewElement("B");

    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);

    EXPECT_NE(a, b);
    ASSERT_NE(a->Name(), nullptr);
    ASSERT_NE(b->Name(), nullptr);
    EXPECT_STREQ(a->Name(), "A");
    EXPECT_STREQ(b->Name(), "B");
}

}  // namespace
