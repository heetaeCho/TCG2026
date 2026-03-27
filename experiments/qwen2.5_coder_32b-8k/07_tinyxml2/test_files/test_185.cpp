#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_185 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLNode* node;



    void SetUp() override {

        node = new XMLNode(&doc);

    }



    void TearDown() override {

        delete node;

    }

};



TEST_F(XMLNodeTest_185, SetValue_StaticMemory_185) {

    const char* value = "StaticValue";

    node->SetValue(value, true);

    EXPECT_STREQ(node->Value(), value);

}



TEST_F(XMLNodeTest_185, SetValue_DynamicMemory_185) {

    const char* value = "DynamicValue";

    node->SetValue(value, false);

    EXPECT_STREQ(node->Value(), value);

}



TEST_F(XMLNodeTest_185, SetValue_EmptyString_185) {

    const char* value = "";

    node->SetValue(value, true);

    EXPECT_STREQ(node->Value(), value);

}



TEST_F(XMLNodeTest_185, SetValue_NullPointer_185) {

    const char* value = nullptr;

    node->SetValue(value, false);

    EXPECT_STREQ(node->Value(), "");

}
