// File: ./TestProjects/tinyxml2/tests/XMLElementSetAttributeIntTest_98.cpp

#include <climits>
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLElementSetAttributeIntTest_98 : public ::testing::Test {
protected:
    XMLDocument doc_;
    XMLElement* elem_ = nullptr;

    void SetUp() override {
        elem_ = doc_.NewElement("root");
        ASSERT_NE(elem_, nullptr);
        doc_.InsertFirstChild(elem_);
    }
};

TEST_F(XMLElementSetAttributeIntTest_98, SetAndQueryIntAttribute_Succeeds_98) {
    elem_->SetAttribute("count", 42);

    int out = 0;
    const XMLError err = elem_->QueryIntAttribute("count", &out);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(out, 42);
}

TEST_F(XMLElementSetAttributeIntTest_98, OverwriteExistingAttribute_UpdatesValue_98) {
    elem_->SetAttribute("level", 1);
    elem_->SetAttribute("level", 7);

    int out = 0;
    ASSERT_EQ(elem_->QueryIntAttribute("level", &out), XML_SUCCESS);
    EXPECT_EQ(out, 7);
}

TEST_F(XMLElementSetAttributeIntTest_98, DoesNotAffectOtherAttributes_98) {
    elem_->SetAttribute("a", 10);
    elem_->SetAttribute("b", 20);
    elem_->SetAttribute("a", 99);  // overwrite only "a"

    int a = 0, b = 0;
    ASSERT_EQ(elem_->QueryIntAttribute("a", &a), XML_SUCCESS);
    ASSERT_EQ(elem_->QueryIntAttribute("b", &b), XML_SUCCESS);
    EXPECT_EQ(a, 99);
    EXPECT_EQ(b, 20);
}

TEST_F(XMLElementSetAttributeIntTest_98, IntAttributeReturnsDefaultWhenMissing_98) {
    // Attribute doesn't exist.
    const int v = elem_->IntAttribute("missing", -123);
    EXPECT_EQ(v, -123);
}

TEST_F(XMLElementSetAttributeIntTest_98, QueryIntAttributeMissing_ReturnsError_98) {
    int out = 0;
    const XMLError err = elem_->QueryIntAttribute("missing", &out);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementSetAttributeIntTest_98, BoundaryValues_IntMinAndIntMax_98) {
    elem_->SetAttribute("minv", INT_MIN);
    elem_->SetAttribute("maxv", INT_MAX);

    int minOut = 0, maxOut = 0;
    ASSERT_EQ(elem_->QueryIntAttribute("minv", &minOut), XML_SUCCESS);
    ASSERT_EQ(elem_->QueryIntAttribute("maxv", &maxOut), XML_SUCCESS);
    EXPECT_EQ(minOut, INT_MIN);
    EXPECT_EQ(maxOut, INT_MAX);
}

TEST_F(XMLElementSetAttributeIntTest_98, NegativeValue_Preserved_98) {
    elem_->SetAttribute("neg", -5);

    int out = 0;
    ASSERT_EQ(elem_->QueryIntAttribute("neg", &out), XML_SUCCESS);
    EXPECT_EQ(out, -5);
}

TEST_F(XMLElementSetAttributeIntTest_98, EmptyName_DoesNotCrashAndIsObservableIfSupported_98) {
    // We avoid assuming whether empty names are allowed; we only verify the call is safe
    // and that querying either succeeds (and matches) or returns a non-success error.
    elem_->SetAttribute("", 123);

    int out = 0;
    const XMLError err = elem_->QueryIntAttribute("", &out);
    if (err == XML_SUCCESS) {
        EXPECT_EQ(out, 123);
    } else {
        EXPECT_NE(err, XML_SUCCESS);
    }
}

TEST_F(XMLElementSetAttributeIntTest_98, FindAttributeReflectsSetValue_WhenPresent_98) {
    elem_->SetAttribute("score", 77);

    const XMLAttribute* a = elem_->FindAttribute("score");
    ASSERT_NE(a, nullptr);

    int out = 0;
    // Prefer observable numeric API rather than assuming formatting in Value().
    ASSERT_EQ(a->QueryIntValue(&out), XML_SUCCESS);
    EXPECT_EQ(out, 77);
}
