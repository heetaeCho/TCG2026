// File: test_xmlelement_deleteattribute_258.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class DeleteAttributeTest_258 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* ParseRoot(const char* xml) {
        EXPECT_NE(xml, nullptr);
        const XMLError err = doc.Parse(xml);
        EXPECT_EQ(err, XML_SUCCESS);
        XMLElement* root = doc.RootElement();
        EXPECT_NE(root, nullptr);
        return root;
    }

    static int CountAttributes(const XMLElement* elem) {
        int count = 0;
        for (const XMLAttribute* a = elem->FirstAttribute(); a; a = a->Next()) {
            ++count;
        }
        return count;
    }
};

} // namespace

TEST_F(DeleteAttributeTest_258, DeleteExistingAttributeRemovesIt_258) {
    XMLElement* root = ParseRoot("<root a='1' b='2' c='3'/>");
    ASSERT_NE(root->FindAttribute("b"), nullptr);
    ASSERT_STREQ(root->Attribute("b"), "2");

    root->DeleteAttribute("b");

    EXPECT_EQ(root->FindAttribute("b"), nullptr);
    EXPECT_EQ(root->Attribute("b"), nullptr);

    // Other attributes remain.
    EXPECT_NE(root->FindAttribute("a"), nullptr);
    EXPECT_NE(root->FindAttribute("c"), nullptr);
    EXPECT_STREQ(root->Attribute("a"), "1");
    EXPECT_STREQ(root->Attribute("c"), "3");
}

TEST_F(DeleteAttributeTest_258, DeleteFirstAttributeUpdatesFirstAttribute_258) {
    XMLElement* root = ParseRoot("<root a='1' b='2' c='3'/>");

    const XMLAttribute* first = root->FirstAttribute();
    ASSERT_NE(first, nullptr);
    ASSERT_STREQ(first->Name(), "a");

    root->DeleteAttribute("a");

    const XMLAttribute* newFirst = root->FirstAttribute();
    ASSERT_NE(newFirst, nullptr);
    EXPECT_STREQ(newFirst->Name(), "b");
    EXPECT_EQ(root->FindAttribute("a"), nullptr);
    EXPECT_EQ(CountAttributes(root), 2);
}

TEST_F(DeleteAttributeTest_258, DeleteMiddleAttributePreservesLinksAndOrder_258) {
    XMLElement* root = ParseRoot("<root a='1' b='2' c='3'/>");
    ASSERT_EQ(CountAttributes(root), 3);

    root->DeleteAttribute("b");

    EXPECT_EQ(root->FindAttribute("b"), nullptr);
    EXPECT_EQ(CountAttributes(root), 2);

    // Verify the remaining iteration order is a -> c.
    const XMLAttribute* a = root->FirstAttribute();
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Name(), "a");

    const XMLAttribute* c = a->Next();
    ASSERT_NE(c, nullptr);
    EXPECT_STREQ(c->Name(), "c");

    EXPECT_EQ(c->Next(), nullptr);
}

TEST_F(DeleteAttributeTest_258, DeleteLastAttributeRemovesLast_258) {
    XMLElement* root = ParseRoot("<root a='1' b='2' c='3'/>");
    ASSERT_EQ(CountAttributes(root), 3);

    root->DeleteAttribute("c");

    EXPECT_EQ(root->FindAttribute("c"), nullptr);
    EXPECT_EQ(CountAttributes(root), 2);

    // Verify last is now "b".
    const XMLAttribute* a = root->FirstAttribute();
    ASSERT_NE(a, nullptr);
    ASSERT_STREQ(a->Name(), "a");

    const XMLAttribute* b = a->Next();
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Name(), "b");
    EXPECT_EQ(b->Next(), nullptr);
}

TEST_F(DeleteAttributeTest_258, DeleteNonExistentAttributeNoChange_258) {
    XMLElement* root = ParseRoot("<root a='1' b='2' c='3'/>");
    const int beforeCount = CountAttributes(root);
    ASSERT_EQ(beforeCount, 3);

    root->DeleteAttribute("does_not_exist");

    EXPECT_EQ(CountAttributes(root), beforeCount);
    EXPECT_NE(root->FindAttribute("a"), nullptr);
    EXPECT_NE(root->FindAttribute("b"), nullptr);
    EXPECT_NE(root->FindAttribute("c"), nullptr);

    // Order unchanged: a -> b -> c
    const XMLAttribute* a = root->FirstAttribute();
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Name(), "a");
    const XMLAttribute* b = a->Next();
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Name(), "b");
    const XMLAttribute* c = b->Next();
    ASSERT_NE(c, nullptr);
    EXPECT_STREQ(c->Name(), "c");
    EXPECT_EQ(c->Next(), nullptr);
}

TEST_F(DeleteAttributeTest_258, DeleteAttributeOnElementWithNoAttributesNoCrash_258) {
    XMLElement* root = ParseRoot("<root/>");
    ASSERT_EQ(root->FirstAttribute(), nullptr);
    ASSERT_EQ(CountAttributes(root), 0);

    root->DeleteAttribute("a");  // should be a no-op

    EXPECT_EQ(root->FirstAttribute(), nullptr);
    EXPECT_EQ(CountAttributes(root), 0);
}

TEST_F(DeleteAttributeTest_258, DeleteAttributeTwiceIsIdempotent_258) {
    XMLElement* root = ParseRoot("<root a='1' b='2'/>");
    ASSERT_NE(root->FindAttribute("a"), nullptr);
    ASSERT_EQ(CountAttributes(root), 2);

    root->DeleteAttribute("a");
    EXPECT_EQ(root->FindAttribute("a"), nullptr);
    EXPECT_EQ(CountAttributes(root), 1);

    // Deleting again should not change anything observable / should not crash.
    root->DeleteAttribute("a");
    EXPECT_EQ(root->FindAttribute("a"), nullptr);
    EXPECT_EQ(CountAttributes(root), 1);

    // Remaining attribute still present.
    EXPECT_NE(root->FindAttribute("b"), nullptr);
    EXPECT_STREQ(root->Attribute("b"), "2");
}
