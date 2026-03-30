#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeLastChildElementTest_55 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* MakeDocWithRootAndChildren() {
        XMLElement* root = doc.NewElement("root");
        ASSERT_NE(root, nullptr);
        doc.InsertEndChild(root);

        // root children: <a/>, <b/>, <a id="last-a"/>
        XMLElement* a1 = doc.NewElement("a");
        ASSERT_NE(a1, nullptr);
        root->InsertEndChild(a1);

        XMLElement* b = doc.NewElement("b");
        ASSERT_NE(b, nullptr);
        root->InsertEndChild(b);

        XMLElement* a2 = doc.NewElement("a");
        ASSERT_NE(a2, nullptr);
        a2->SetAttribute("id", "last-a");
        root->InsertEndChild(a2);

        return root;
    }

    XMLElement* MakeDocWithNoChildren() {
        XMLElement* root = doc.NewElement("root");
        ASSERT_NE(root, nullptr);
        doc.InsertEndChild(root);
        return root;
    }
};

// Normal operation: name == nullptr returns the last child element.
TEST_F(XMLNodeLastChildElementTest_55, ReturnsLastChildElementWhenNameNull_55) {
    XMLElement* root = MakeDocWithRootAndChildren();
    ASSERT_NE(root, nullptr);

    XMLElement* last = root->LastChildElement(nullptr);
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Name(), "a");
    EXPECT_STREQ(last->Attribute("id"), "last-a");
}

// Normal operation: default argument behaves like nullptr.
TEST_F(XMLNodeLastChildElementTest_55, DefaultArgumentReturnsLastChildElement_55) {
    XMLElement* root = MakeDocWithRootAndChildren();
    ASSERT_NE(root, nullptr);

    XMLElement* last = root->LastChildElement();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Name(), "a");
    EXPECT_STREQ(last->Attribute("id"), "last-a");
}

// Name filter: returns the last child element matching the given name.
TEST_F(XMLNodeLastChildElementTest_55, ReturnsLastMatchingChildElementByName_55) {
    XMLElement* root = MakeDocWithRootAndChildren();
    ASSERT_NE(root, nullptr);

    XMLElement* lastA = root->LastChildElement("a");
    ASSERT_NE(lastA, nullptr);
    EXPECT_STREQ(lastA->Name(), "a");
    EXPECT_STREQ(lastA->Attribute("id"), "last-a");

    XMLElement* lastB = root->LastChildElement("b");
    ASSERT_NE(lastB, nullptr);
    EXPECT_STREQ(lastB->Name(), "b");
    EXPECT_EQ(lastB->Attribute("id"), nullptr);
}

// Boundary / error-like: no children => nullptr.
TEST_F(XMLNodeLastChildElementTest_55, ReturnsNullptrWhenNoChildren_55) {
    XMLElement* root = MakeDocWithNoChildren();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->LastChildElement(), nullptr);
    EXPECT_EQ(root->LastChildElement(nullptr), nullptr);
    EXPECT_EQ(root->LastChildElement("a"), nullptr);
}

// Boundary: name does not exist => nullptr.
TEST_F(XMLNodeLastChildElementTest_55, ReturnsNullptrWhenNameNotFound_55) {
    XMLElement* root = MakeDocWithRootAndChildren();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->LastChildElement("does-not-exist"), nullptr);
}

// Observable behavior of wrapper: non-const overload returns same address as const overload.
TEST_F(XMLNodeLastChildElementTest_55, NonConstOverloadMatchesConstOverloadPointer_55) {
    XMLElement* root = MakeDocWithRootAndChildren();
    ASSERT_NE(root, nullptr);

    const XMLNode* constRootNode = root; // upcast
    const XMLElement* constLastA = constRootNode->LastChildElement("a");
    ASSERT_NE(constLastA, nullptr);

    XMLElement* nonConstLastA = root->LastChildElement("a");
    ASSERT_NE(nonConstLastA, nullptr);

    EXPECT_EQ(nonConstLastA, constLastA);
}

// Non-const return can be used as XMLElement* (observable via attribute set/get).
TEST_F(XMLNodeLastChildElementTest_55, ReturnedPointerIsMutableXMLElementPointer_55) {
    XMLElement* root = MakeDocWithRootAndChildren();
    ASSERT_NE(root, nullptr);

    XMLElement* last = root->LastChildElement("a");
    ASSERT_NE(last, nullptr);

    last->SetAttribute("mutated", "yes");
    EXPECT_STREQ(last->Attribute("mutated"), "yes");

    // Ensure we're still referring to the last matching element after mutation.
    XMLElement* lastAgain = root->LastChildElement("a");
    ASSERT_NE(lastAgain, nullptr);
    EXPECT_EQ(lastAgain, last);
    EXPECT_STREQ(lastAgain->Attribute("mutated"), "yes");
}
