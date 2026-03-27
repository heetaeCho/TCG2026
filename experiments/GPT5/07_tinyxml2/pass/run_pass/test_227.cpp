// File: test_xmlelement_attribute_227.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementAttributeTest_227 : public ::testing::Test {
protected:
    XMLDocument doc_;
    XMLElement* elem_ = nullptr;

    void SetUp() override {
        elem_ = doc_.NewElement("root");
        ASSERT_NE(elem_, nullptr);
        // Keep element owned by doc to avoid lifetime surprises in some implementations.
        doc_.InsertEndChild(elem_);
    }
};

TEST_F(XMLElementAttributeTest_227, ReturnsNullptrWhenAttributeDoesNotExist_227) {
    const char* result = elem_->Attribute("missing", nullptr);
    EXPECT_EQ(result, nullptr);

    result = elem_->Attribute("missing", "anything");
    EXPECT_EQ(result, nullptr);
}

TEST_F(XMLElementAttributeTest_227, ReturnsValueWhenAttributeExistsAndValueParamIsNull_227) {
    elem_->SetAttribute("a", "1");

    const char* result = elem_->Attribute("a", nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "1");
}

TEST_F(XMLElementAttributeTest_227, ReturnsValueWhenAttributeExistsAndValueMatches_227) {
    elem_->SetAttribute("color", "blue");

    const char* result = elem_->Attribute("color", "blue");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "blue");
}

TEST_F(XMLElementAttributeTest_227, ReturnsNullptrWhenAttributeExistsButValueDoesNotMatch_227) {
    elem_->SetAttribute("color", "blue");

    const char* result = elem_->Attribute("color", "red");
    EXPECT_EQ(result, nullptr);
}

TEST_F(XMLElementAttributeTest_227, WorksWithEmptyAttributeValue_227) {
    elem_->SetAttribute("empty", "");

    // value == nullptr should return stored value (even if empty)
    const char* result = elem_->Attribute("empty", nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");

    // matching empty string should return stored value
    result = elem_->Attribute("empty", "");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");

    // non-matching should return nullptr
    result = elem_->Attribute("empty", "not-empty");
    EXPECT_EQ(result, nullptr);
}

TEST_F(XMLElementAttributeTest_227, DoesNotConfuseDifferentAttributes_227) {
    elem_->SetAttribute("a", "1");
    elem_->SetAttribute("b", "2");

    const char* ra = elem_->Attribute("a", nullptr);
    const char* rb = elem_->Attribute("b", nullptr);

    ASSERT_NE(ra, nullptr);
    ASSERT_NE(rb, nullptr);
    EXPECT_STREQ(ra, "1");
    EXPECT_STREQ(rb, "2");

    EXPECT_EQ(elem_->Attribute("a", "2"), nullptr);
    EXPECT_EQ(elem_->Attribute("b", "1"), nullptr);
    EXPECT_STREQ(elem_->Attribute("a", "1"), "1");
    EXPECT_STREQ(elem_->Attribute("b", "2"), "2");
}

TEST_F(XMLElementAttributeTest_227, HandlesEmptyAttributeNameAsNotFoundOrEquivalentBehavior_227) {
    // This is a boundary case. Observable behavior should be: either not found (nullptr),
    // or if the library allows empty-named attributes via SetAttribute, it should behave consistently.
    // We only assert it does not crash and returns nullptr in the common case.
    const char* result = elem_->Attribute("", nullptr);
    EXPECT_EQ(result, nullptr);
}
