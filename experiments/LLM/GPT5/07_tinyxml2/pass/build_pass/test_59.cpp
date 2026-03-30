// TEST_ID: 59
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLNodeNextSiblingElementTest_59 : public ::testing::Test {
protected:
    XMLDocument doc_;

    void ParseOrFail_59(const char* xml) {
        ASSERT_EQ(doc_.Parse(xml), XML_SUCCESS);
    }
};

// Verifies the non-const wrapper forwards to the const overload and returns the expected next sibling element.
TEST_F(XMLNodeNextSiblingElementTest_59, NextSiblingElementFindsNextElement_59) {
    ParseOrFail_59(R"xml(
        <root>
            <a id="1"/>
            <!-- comment -->
            <b id="2"/>
            <a id="3"/>
        </root>
    )xml");

    XMLElement* root = doc_.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* a1 = root->FirstChildElement("a");
    ASSERT_NE(a1, nullptr);
    EXPECT_STREQ(a1->Name(), "a");

    // Next sibling element should skip non-element nodes and find <b>.
    XMLElement* nextElem = a1->NextSiblingElement();
    ASSERT_NE(nextElem, nullptr);
    EXPECT_STREQ(nextElem->Name(), "b");
    EXPECT_STREQ(nextElem->Attribute("id"), "2");
}

// Verifies name-filtered search finds the next sibling element with the given name.
TEST_F(XMLNodeNextSiblingElementTest_59, NextSiblingElementWithNameFindsMatchingSibling_59) {
    ParseOrFail_59(R"xml(
        <root>
            <a id="1"/>
            <b id="2"/>
            <a id="3"/>
        </root>
    )xml");

    XMLElement* root = doc_.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* a1 = root->FirstChildElement("a");
    ASSERT_NE(a1, nullptr);

    // Next sibling element named "a" should be the later <a id="3"/>.
    XMLElement* nextA = a1->NextSiblingElement("a");
    ASSERT_NE(nextA, nullptr);
    EXPECT_STREQ(nextA->Name(), "a");
    EXPECT_STREQ(nextA->Attribute("id"), "3");
}

// Verifies a non-existing name filter returns nullptr (observable error case).
TEST_F(XMLNodeNextSiblingElementTest_59, NextSiblingElementWithNonExistingNameReturnsNull_59) {
    ParseOrFail_59(R"xml(
        <root>
            <a/>
            <b/>
        </root>
    )xml");

    XMLElement* root = doc_.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    EXPECT_EQ(a->NextSiblingElement("does_not_exist"), nullptr);
}

// Verifies boundary: last sibling element returns nullptr (no next sibling element).
TEST_F(XMLNodeNextSiblingElementTest_59, NextSiblingElementOnLastElementReturnsNull_59) {
    ParseOrFail_59(R"xml(
        <root>
            <a/>
            <b/>
        </root>
    )xml");

    XMLElement* root = doc_.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    EXPECT_EQ(b->NextSiblingElement(), nullptr);
    EXPECT_EQ(b->NextSiblingElement("b"), nullptr);
}

// Verifies the returned pointer is non-const and can be used for observable mutation via public API.
TEST_F(XMLNodeNextSiblingElementTest_59, NextSiblingElementReturnsNonConstPointerThatCanMutateElement_59) {
    ParseOrFail_59(R"xml(
        <root>
            <a/>
            <b/>
        </root>
    )xml");

    XMLElement* root = doc_.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);

    XMLElement* b = a->NextSiblingElement();
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Name(), "b");

    // Mutate through the non-const XMLElement* (observable via subsequent reads).
    b->SetAttribute("k", "v");
    EXPECT_STREQ(b->Attribute("k"), "v");

    // Also observable through a const view of the same node.
    const XMLNode* aConst = a;
    const XMLElement* bConst = aConst->NextSiblingElement(); // const overload
    ASSERT_NE(bConst, nullptr);
    EXPECT_STREQ(bConst->Name(), "b");
    EXPECT_STREQ(bConst->Attribute("k"), "v");
}
