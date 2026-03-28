// File: ./TestProjects/tinyxml2/tests/XMLElement_QueryAttributeConstCharPtrPtr_Test_96.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace tinyxml2 {

class XMLElementQueryAttributeConstCharPtrPtrTest_96 : public ::testing::Test {
protected:
    XMLDocument doc_;

    XMLElement* ParseAndGetRoot(const char* xml) {
        doc_.Clear();
        const XMLError err = doc_.Parse(xml);
        EXPECT_EQ(err, XML_SUCCESS);
        return doc_.RootElement();
    }
};

TEST_F(XMLElementQueryAttributeConstCharPtrPtrTest_96, ExistingAttributeReturnsSuccessAndOutputsValue_96) {
    XMLElement* root = ParseAndGetRoot(R"(<root a="hello"/>)");
    ASSERT_NE(root, nullptr);

    const char* out = nullptr;
    const XMLError err = root->QueryAttribute("a", &out);

    EXPECT_EQ(err, XML_SUCCESS);
    ASSERT_NE(out, nullptr);
    EXPECT_STREQ(out, "hello");
}

TEST_F(XMLElementQueryAttributeConstCharPtrPtrTest_96, EmptyStringAttributeReturnsSuccessAndOutputsEmpty_96) {
    XMLElement* root = ParseAndGetRoot(R"(<root a=""/>)");
    ASSERT_NE(root, nullptr);

    const char* out = nullptr;
    const XMLError err = root->QueryAttribute("a", &out);

    EXPECT_EQ(err, XML_SUCCESS);
    ASSERT_NE(out, nullptr);
    EXPECT_STREQ(out, "");
}

TEST_F(XMLElementQueryAttributeConstCharPtrPtrTest_96, MissingAttributeDoesNotReturnSuccess_96) {
    XMLElement* root = ParseAndGetRoot(R"(<root a="x"/>)");
    ASSERT_NE(root, nullptr);

    const char* out = "sentinel";
    const XMLError err = root->QueryAttribute("missing", &out);

    // Black-box friendly: only require "not success" for a missing attribute.
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementQueryAttributeConstCharPtrPtrTest_96, EmptyNameDoesNotReturnSuccess_96) {
    XMLElement* root = ParseAndGetRoot(R"(<root a="x"/>)");
    ASSERT_NE(root, nullptr);

    const char* out = "sentinel";
    const XMLError err = root->QueryAttribute("", &out);

    // Avoid assuming exact error code; just verify it isn't reported as success.
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementQueryAttributeConstCharPtrPtrTest_96, DelegatesToQueryStringAttributeSameResultAndOutput_96) {
    XMLElement* root = ParseAndGetRoot(R"(<root a="value123"/>)");
    ASSERT_NE(root, nullptr);

    const char* out1 = nullptr;
    const char* out2 = nullptr;

    const XMLError err1 = root->QueryAttribute("a", &out1);
    const XMLError err2 = root->QueryStringAttribute("a", &out2);

    EXPECT_EQ(err1, err2);

    if (err1 == XML_SUCCESS) {
        ASSERT_NE(out1, nullptr);
        ASSERT_NE(out2, nullptr);
        EXPECT_STREQ(out1, out2);
        EXPECT_STREQ(out1, "value123");
    }
}

TEST_F(XMLElementQueryAttributeConstCharPtrPtrTest_96, WorksWithMultipleAttributesSelectsRequestedOne_96) {
    XMLElement* root = ParseAndGetRoot(R"(<root a="first" b="second" c="third"/>)");
    ASSERT_NE(root, nullptr);

    const char* outB = nullptr;
    const XMLError err = root->QueryAttribute("b", &outB);

    EXPECT_EQ(err, XML_SUCCESS);
    ASSERT_NE(outB, nullptr);
    EXPECT_STREQ(outB, "second");
}

}  // namespace tinyxml2
