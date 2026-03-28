// File: ./TestProjects/tinyxml2/tests/XMLElementQueryAttributeBoolTest_93.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementQueryAttributeBoolTest_93 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        elem = doc.NewElement("root");
        ASSERT_NE(elem, nullptr);
        doc.InsertEndChild(elem);
    }
};

TEST_F(XMLElementQueryAttributeBoolTest_93, QueryAttributeBool_ReadsTrueWrittenBySetAttribute_93) {
    elem->SetAttribute("flag", true);

    bool v = false;
    const XMLError err = elem->QueryAttribute("flag", &v);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(v);
}

TEST_F(XMLElementQueryAttributeBoolTest_93, QueryAttributeBool_ReadsFalseWrittenBySetAttribute_93) {
    elem->SetAttribute("flag", false);

    bool v = true;
    const XMLError err = elem->QueryAttribute("flag", &v);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(v);
}

TEST_F(XMLElementQueryAttributeBoolTest_93, QueryAttributeBool_MissingAttributeMatchesQueryBoolAttribute_ErrorCodeAndOutput_93) {
    // Compare observable behavior of QueryAttribute(bool*) vs QueryBoolAttribute on a missing attribute,
    // without assuming whether the out-param is modified or not on failure.
    bool v1 = true;
    bool v2 = true;

    const XMLError err1 = elem->QueryAttribute("missing", &v1);
    const XMLError err2 = elem->QueryBoolAttribute("missing", &v2);

    EXPECT_EQ(err1, err2);
    EXPECT_EQ(v1, v2);
}

TEST_F(XMLElementQueryAttributeBoolTest_93, QueryAttributeBool_ExistingAttributeMatchesQueryBoolAttribute_ValueAndErrorCode_93) {
    elem->SetAttribute("flag", true);

    bool v1 = false;
    bool v2 = false;

    const XMLError err1 = elem->QueryAttribute("flag", &v1);
    const XMLError err2 = elem->QueryBoolAttribute("flag", &v2);

    EXPECT_EQ(err1, err2);
    EXPECT_EQ(v1, v2);
}

TEST_F(XMLElementQueryAttributeBoolTest_93, QueryAttributeBool_WhenAttributeChangesMatchesQueryBoolAttribute_AfterUpdate_93) {
    elem->SetAttribute("flag", true);

    bool v1 = false, v2 = false;
    EXPECT_EQ(elem->QueryAttribute("flag", &v1), XML_SUCCESS);
    EXPECT_EQ(elem->QueryBoolAttribute("flag", &v2), XML_SUCCESS);
    EXPECT_EQ(v1, v2);

    // Update attribute and verify both query paths still match.
    elem->SetAttribute("flag", false);

    v1 = true;
    v2 = true;
    const XMLError err1 = elem->QueryAttribute("flag", &v1);
    const XMLError err2 = elem->QueryBoolAttribute("flag", &v2);

    EXPECT_EQ(err1, err2);
    EXPECT_EQ(v1, v2);
}
