#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"



// Mock class to extend XMP_Node for testing purposes

class XMP_NodeTest : public XMP_Node {

public:

    using XMP_Node::XMP_Node;

};



// Test fixture for SetNodeValue tests

class SetNodeValueTest_1924 : public ::testing::Test {

protected:

    void SetUp() override {

        node = new XMP_Node(nullptr, "test:property", 0);

    }



    void TearDown() override {

        delete node;

    }



    XMP_Node* node;

};



// Test normal operation with a valid string

TEST_F(SetNodeValueTest_1924, SetValidString_1924) {

    const char* testValue = "valid value";

    SetNodeValue(node, testValue);

    EXPECT_STREQ(node->value.c_str(), testValue);

}



// Test setting an empty string

TEST_F(SetNodeValueTest_1924, SetEmptyString_1924) {

    const char* testValue = "";

    SetNodeValue(node, testValue);

    EXPECT_STREQ(node->value.c_str(), testValue);

}



// Test setting a string with ASCII control characters

TEST_F(SetNodeValueTest_1924, SetStringWithControlChars_1924) {

    const char* testValue = "control\x01chars";

    SetNodeValue(node, testValue);

    EXPECT_STREQ(node->value.c_str(), "control chars");

}



// Test setting a string with valid UTF-8 characters

TEST_F(SetNodeValueTest_1924, SetValidUTF8String_1924) {

    const char* testValue = "valid utf8 \xC3\xA9";

    SetNodeValue(node, testValue);

    EXPECT_STREQ(node->value.c_str(), testValue);

}



// Test setting a string with invalid UTF-8 characters

TEST_F(SetNodeValueTest_1924, SetInvalidUTF8String_1924) {

    const char* testValue = "invalid utf8 \xC3\xA9\xFF";

    EXPECT_THROW(SetNodeValue(node, testValue), XMP_Error);

}



// Test setting a string with xml:lang qualifier

TEST_F(SetNodeValueTest_1924, SetLangQualifier_1924) {

    node = new XMP_Node(nullptr, "xml:lang", kXMP_PropIsQualifier);

    const char* testValue = "en-US";

    SetNodeValue(node, testValue);

    EXPECT_STREQ(node->value.c_str(), "en-us");

}



// Test the debug assert condition

TEST_F(SetNodeValueTest_1924, DebugAssertCondition_1924) {

    node = new XMP_Node(nullptr, "xmp:TestAssertNotify", 0);

    const char* testValue = "DoIt!";

#ifdef XMP_DebugBuild

    EXPECT_DEATH(SetNodeValue(node, testValue), "");

#else

    SetNodeValue(node, testValue);

    EXPECT_STREQ(node->value.c_str(), testValue);

#endif

}
