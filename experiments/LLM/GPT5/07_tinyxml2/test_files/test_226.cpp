// File: test_xmlelement_findattribute_226.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

namespace {

class FindAttributeTest_226 : public ::testing::Test {
protected:
    XMLDocument doc_;
    XMLElement* elem_ = nullptr;

    void SetUp() override {
        elem_ = doc_.NewElement("root");
        ASSERT_NE(elem_, nullptr);
        doc_.InsertEndChild(elem_);
    }
};

TEST_F(FindAttributeTest_226, ReturnsNullWhenNoAttributes_226) {
    const XMLAttribute* a = elem_->FindAttribute("missing");
    EXPECT_EQ(a, nullptr);
}

TEST_F(FindAttributeTest_226, ReturnsNullWhenNameNotPresent_226) {
    elem_->SetAttribute("id", 7);
    elem_->SetAttribute("name", "alice");

    const XMLAttribute* a = elem_->FindAttribute("missing");
    EXPECT_EQ(a, nullptr);
}

TEST_F(FindAttributeTest_226, FindsSingleAttributeByName_226) {
    elem_->SetAttribute("id", 7);

    const XMLAttribute* a = elem_->FindAttribute("id");
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Name(), "id");
    EXPECT_STREQ(a->Value(), "7");
}

TEST_F(FindAttributeTest_226, FindsFirstAttributeAmongMultiple_226) {
    elem_->SetAttribute("first", "A");
    elem_->SetAttribute("second", "B");
    elem_->SetAttribute("third", "C");

    const XMLAttribute* a = elem_->FindAttribute("first");
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Name(), "first");
    EXPECT_STREQ(a->Value(), "A");
}

TEST_F(FindAttributeTest_226, FindsMiddleAttributeAmongMultiple_226) {
    elem_->SetAttribute("first", "A");
    elem_->SetAttribute("second", "B");
    elem_->SetAttribute("third", "C");

    const XMLAttribute* a = elem_->FindAttribute("second");
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Name(), "second");
    EXPECT_STREQ(a->Value(), "B");
}

TEST_F(FindAttributeTest_226, FindsLastAttributeAmongMultiple_226) {
    elem_->SetAttribute("first", "A");
    elem_->SetAttribute("second", "B");
    elem_->SetAttribute("third", "C");

    const XMLAttribute* a = elem_->FindAttribute("third");
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Name(), "third");
    EXPECT_STREQ(a->Value(), "C");
}

TEST_F(FindAttributeTest_226, ReturnsSamePointerAsTraversalFromFirstAttribute_226) {
    elem_->SetAttribute("a", 1);
    elem_->SetAttribute("b", 2);
    elem_->SetAttribute("c", 3);

    const XMLAttribute* viaFind = elem_->FindAttribute("b");
    ASSERT_NE(viaFind, nullptr);

    const XMLAttribute* cur = elem_->FirstAttribute();
    ASSERT_NE(cur, nullptr);

    const XMLAttribute* viaWalk = nullptr;
    for (; cur; cur = cur->Next()) {
        if (std::strcmp(cur->Name(), "b") == 0) {
            viaWalk = cur;
            break;
        }
    }

    ASSERT_NE(viaWalk, nullptr);
    EXPECT_EQ(viaFind, viaWalk);
}

TEST_F(FindAttributeTest_226, DoesNotMatchDifferentCaseName_226) {
    elem_->SetAttribute("CaseSensitive", "yes");

    EXPECT_NE(elem_->FindAttribute("CaseSensitive"), nullptr);
    EXPECT_EQ(elem_->FindAttribute("casesensitive"), nullptr);
    EXPECT_EQ(elem_->FindAttribute("CASESENSITIVE"), nullptr);
}

TEST_F(FindAttributeTest_226, EmptyStringNameNotFoundUnlessPresent_226) {
    // No empty-name attribute created here; verify it doesn't "accidentally" match.
    elem_->SetAttribute("x", "1");
    EXPECT_EQ(elem_->FindAttribute(""), nullptr);
}

TEST_F(FindAttributeTest_226, ReflectsDeletionOfAttribute_226) {
    elem_->SetAttribute("temp", "123");
    ASSERT_NE(elem_->FindAttribute("temp"), nullptr);

    elem_->DeleteAttribute("temp");
    EXPECT_EQ(elem_->FindAttribute("temp"), nullptr);
}

TEST_F(FindAttributeTest_226, ReflectsOverwritingAttributeValue_226) {
    elem_->SetAttribute("id", 1);
    const XMLAttribute* a1 = elem_->FindAttribute("id");
    ASSERT_NE(a1, nullptr);
    EXPECT_STREQ(a1->Value(), "1");

    // Overwrite via SetAttribute on the element (observable behavior: Value changes).
    elem_->SetAttribute("id", 999);

    const XMLAttribute* a2 = elem_->FindAttribute("id");
    ASSERT_NE(a2, nullptr);
    EXPECT_STREQ(a2->Name(), "id");
    EXPECT_STREQ(a2->Value(), "999");

    // Pointer stability is not guaranteed by the interface; do not assert a1 == a2.
}

} // namespace
