#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMLParserAdapter.hpp"



using ::testing::_;

using namespace Exiv2;



class XML_NodeTest_1974 : public ::testing::Test {

protected:

    void SetUp() override {

        root = std::make_shared<XML_Node>(nullptr, "root", 0);

        elem = std::make_shared<XML_Node>(root, "element", 1);

        attr = std::make_shared<XML_Node>(elem, "attribute", 2);

        cdata = std::make_shared<XML_Node>(elem, "#cdata-section", 3);

        pi = std::make_shared<XML_Node>(elem, "?processing-instruction", 4);



        elem->attrs.push_back(attr);

        elem->content.push_back(cdata);

        elem->content.push_back(pi);

        root->content.push_back(elem);

    }



    XML_NodePtr root;

    XML_NodePtr elem;

    XML_NodePtr attr;

    XML_NodePtr cdata;

    XML_NodePtr pi;

};



TEST_F(XML_NodeTest_1974, DumpNodeList_RootElement_1974) {

    std::string buffer;

    DumpNodeList(&buffer, {root}, 0);

    EXPECT_EQ(buffer, "root - root\n    element - elem\n        attrs:\n            attribute - attr\n        #cdata-section - cdata\n        ?processing-instruction - pi\n");

}



TEST_F(XML_NodeTest_1974, DumpNodeList_EmptyList_1974) {

    std::string buffer;

    DumpNodeList(&buffer, {}, 0);

    EXPECT_EQ(buffer, "");

}



TEST_F(XML_NodeTest_1974, DumpNodeList_ElementWithWhitespace_1974) {

    auto whitespace = std::make_shared<XML_Node>(elem, "", 0);

    elem->content.push_back(whitespace);



    std::string buffer;

    DumpNodeList(&buffer, {root}, 0);

    EXPECT_EQ(buffer, "root - root\n    element - elem\n        attrs:\n            attribute - attr\n        #cdata-section - cdata\n        ?processing-instruction - pi\n        -- whitespace --\n");

}



TEST_F(XML_NodeTest_1974, DumpNodeList_ElementWithNamespace_1974) {

    elem->ns = "http://example.com";

    std::string buffer;

    DumpNodeList(&buffer, {root}, 0);

    EXPECT_EQ(buffer, "root - root\n    element - elem, ns=\"http://example.com\"\n        attrs:\n            attribute - attr\n        #cdata-section - cdata\n        ?processing-instruction - pi\n");

}



TEST_F(XML_NodeTest_1974, DumpNodeList_ElementWithNamespacePrefixLength_1974) {

    elem->nsPrefixLen = 3;

    std::string buffer;

    DumpNodeList(&buffer, {root}, 0);

    EXPECT_EQ(buffer, "root - root\n    element - elem, prefixLen=3\n        attrs:\n            attribute - attr\n        #cdata-section - cdata\n        ?processing-instruction - pi\n");

}



TEST_F(XML_NodeTest_1974, DumpNodeList_ElementWithValue_1974) {

    elem->value = "some value";

    std::string buffer;

    DumpNodeList(&buffer, {root}, 0);

    EXPECT_EQ(buffer, "root - root\n    element - elem, value=\"some value\"\n        attrs:\n            attribute - attr\n        #cdata-section - cdata\n        ?processing-instruction - pi\n");

}
