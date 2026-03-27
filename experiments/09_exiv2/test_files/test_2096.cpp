#include <gtest/gtest.h>

#include "ExpatAdapter.cpp"

#include "XMLParserAdapter.hpp"



using namespace std;



class ExpatAdapterTest_2096 : public ::testing::Test {

protected:

    XMLParserAdapter parser;

    ExpatAdapter expatAdapter;

};



TEST_F(ExpatAdapterTest_2096, ProcessingInstructionHandler_IgnoresNonXPacketTarget_2096) {

    XMP_StringPtr target = "other";

    XMP_StringPtr data = "data";



    XML_Node parentNode(&parser.tree, "parent", kElemNode);

    parser.parseStack.push_back(&parentNode);



    size_t initialContentSize = parentNode.content.size();

    ProcessingInstructionHandler(&expatAdapter, target, data);

    EXPECT_EQ(parentNode.content.size(), initialContentSize);

}



TEST_F(ExpatAdapterTest_2096, ProcessingInstructionHandler_HandlesXPacketTargetWithNonNullData_2096) {

    XMP_StringPtr target = "xpacket";

    XMP_StringPtr data = "data";



    XML_Node parentNode(&parser.tree, "parent", kElemNode);

    parser.parseStack.push_back(&parentNode);



    size_t initialContentSize = parentNode.content.size();

    ProcessingInstructionHandler(&expatAdapter, target, data);

    EXPECT_EQ(parentNode.content.size(), initialContentSize + 1);



    XML_Node* piNode = parentNode.content.back();

    EXPECT_EQ(piNode->kind, kPINode);

    EXPECT_STREQ(piNode->name.c_str(), "xpacket");

    EXPECT_STREQ(piNode->value.c_str(), data);

}



TEST_F(ExpatAdapterTest_2096, ProcessingInstructionHandler_HandlesXPacketTargetWithNullData_2096) {

    XMP_StringPtr target = "xpacket";

    XMP_StringPtr data = nullptr;



    XML_Node parentNode(&parser.tree, "parent", kElemNode);

    parser.parseStack.push_back(&parentNode);



    size_t initialContentSize = parentNode.content.size();

    ProcessingInstructionHandler(&expatAdapter, target, data);

    EXPECT_EQ(parentNode.content.size(), initialContentSize + 1);



    XML_Node* piNode = parentNode.content.back();

    EXPECT_EQ(piNode->kind, kPINode);

    EXPECT_STREQ(piNode->name.c_str(), "xpacket");

    EXPECT_STREQ(piNode->value.c_str(), "");

}



TEST_F(ExpatAdapterTest_2096, ProcessingInstructionHandler_HandlesEmptyParseStack_2096) {

    XMP_StringPtr target = "xpacket";

    XMP_StringPtr data = "data";



    // No parent node in parseStack

    size_t initialContentSize = parser.tree.content.size();

    ProcessingInstructionHandler(&expatAdapter, target, data);

    EXPECT_EQ(parser.tree.content.size(), initialContentSize); // Should not add anything as there's no parent node

}



TEST_F(ExpatAdapterTest_2096, ProcessingInstructionHandler_HandlesXPacketTargetWithEmptyData_2096) {

    XMP_StringPtr target = "xpacket";

    XMP_StringPtr data = "";



    XML_Node parentNode(&parser.tree, "parent", kElemNode);

    parser.parseStack.push_back(&parentNode);



    size_t initialContentSize = parentNode.content.size();

    ProcessingInstructionHandler(&expatAdapter, target, data);

    EXPECT_EQ(parentNode.content.size(), initialContentSize + 1);



    XML_Node* piNode = parentNode.content.back();

    EXPECT_EQ(piNode->kind, kPINode);

    EXPECT_STREQ(piNode->name.c_str(), "xpacket");

    EXPECT_STREQ(piNode->value.c_str(), "");

}
