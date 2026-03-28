// File: ./TestProjects/tinyxml2/tests/xmlnode_previous_sibling_element_test_57.cpp

#include <gtest/gtest.h>
#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLNodePreviousSiblingElementTest_57 : public ::testing::Test {
protected:
    void SetUp() override {
        root = doc.NewElement("root");
        doc.InsertEndChild(root);

        a = doc.NewElement("a");
        b = doc.NewElement("b");
        c = doc.NewElement("c");
        d = doc.NewElement("d");

        root->InsertEndChild(a);
        root->InsertEndChild(b);
        root->InsertEndChild(c);
        root->InsertEndChild(d);
    }

    XMLDocument doc;
    XMLElement* root = nullptr;
    XMLElement* a = nullptr;
    XMLElement* b = nullptr;
    XMLElement* c = nullptr;
    XMLElement* d = nullptr;
};

TEST_F(XMLNodePreviousSiblingElementTest_57, ReturnsImmediatePreviousElementWhenNameNull_57) {
    ASSERT_NE(c, nullptr);
    XMLElement* prev = c->PreviousSiblingElement();  // name defaults to 0
    EXPECT_EQ(prev, b);
}

TEST_F(XMLNodePreviousSiblingElementTest_57, ReturnsNullWhenNoPreviousSiblingElement_57) {
    ASSERT_NE(a, nullptr);
    XMLElement* prev = a->PreviousSiblingElement();
    EXPECT_EQ(prev, nullptr);
}

TEST_F(XMLNodePreviousSiblingElementTest_57, FiltersByNameFindsNearestMatchingPrevious_57) {
    ASSERT_NE(d, nullptr);

    // Immediate previous element is <c>, so searching for "c" should find it.
    XMLElement* prevC = d->PreviousSiblingElement("c");
    EXPECT_EQ(prevC, c);
}

TEST_F(XMLNodePreviousSiblingElementTest_57, FiltersByNameCanSkipNonMatchingSiblings_57) {
    ASSERT_NE(d, nullptr);

    // Between <d> and <a>, there are <c> and <b>; searching for "a" should find <a>.
    XMLElement* prevA = d->PreviousSiblingElement("a");
    EXPECT_EQ(prevA, a);
}

TEST_F(XMLNodePreviousSiblingElementTest_57, FiltersByNameReturnsNullWhenNoMatch_57) {
    ASSERT_NE(d, nullptr);
    XMLElement* prevNope = d->PreviousSiblingElement("no_such_name");
    EXPECT_EQ(prevNope, nullptr);
}

TEST_F(XMLNodePreviousSiblingElementTest_57, NonConstOverloadMatchesConstOverloadResult_57) {
    ASSERT_NE(d, nullptr);

    // Call the const overload via a const-qualified pointer.
    const XMLNode* constNode = d;
    const XMLElement* constPrev = constNode->PreviousSiblingElement(); // const overload

    // Call the non-const overload (wrapper under test).
    XMLElement* nonConstPrev = d->PreviousSiblingElement();

    // They should refer to the same underlying node.
    EXPECT_EQ(nonConstPrev, const_cast<XMLElement*>(constPrev));
}

TEST_F(XMLNodePreviousSiblingElementTest_57, ReturnedPointerIsMutableThroughNonConstOverload_57) {
    ASSERT_NE(c, nullptr);

    // Get previous sibling element (<b>) from <c> using the non-const overload.
    XMLElement* prev = c->PreviousSiblingElement();
    ASSERT_NE(prev, nullptr);
    ASSERT_EQ(prev, b);

    // Mutate via returned non-const pointer and observe via normal TinyXML2 API.
    prev->SetAttribute("k", "v");
    const char* attr = b->Attribute("k");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr, "v");
}

}  // namespace
