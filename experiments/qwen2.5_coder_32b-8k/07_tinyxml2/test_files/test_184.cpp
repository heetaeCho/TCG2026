#include <gtest/gtest.h>

#include <tinyxml2.h>



using namespace tinyxml2;



class XMLNodeTest : public ::testing::Test {

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



TEST_F(XMLNodeTest_184, ValueReturnsNullIfToDocumentIsTrue_184) {

    EXPECT_TRUE(node->ToDocument());

    EXPECT_EQ(node->Value(), nullptr);

}



TEST_F(XMLNodeTest_184, ValueReturnsStrFromStrPair_184) {

    node = new XMLElement(&doc); // Assuming XMLElement inherits from XMLNode

    const char* testValue = "testValue";

    node->SetValue(testValue);

    EXPECT_STREQ(node->Value(), testValue);

}



TEST_F(XMLNodeTest_184, ChildElementCountReturnsZeroForNewNode_184) {

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_184, ChildElementCountWithNameReturnsZeroForNewNode_184) {

    const char* name = "testName";

    EXPECT_EQ(node->ChildElementCount(name), 0);

}
