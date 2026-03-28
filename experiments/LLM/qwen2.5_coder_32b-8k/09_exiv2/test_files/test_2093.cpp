#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMLParserAdapter.hpp"

#include "XMP_Const.h"



using namespace ::testing;



class ExpatAdapterTest : public Test {

protected:

    XMLParserAdapter* parser;

    XMP_StringPtr name = "testElement";

    XMP_StringPtr attrs[] = {"attr1", "value1", nullptr};



    void SetUp() override {

        parser = new XMLParserAdapter();

    }



    void TearDown() override {

        delete parser;

    }

};



TEST_F(ExpatAdapterTest_NormalOperation_2093, StartElementHandler_AddsNodeToParseStack_2093) {

    EXPECT_EQ(parser->parseStack.size(), 1u); // Initial root node

    StartElementHandler(parser, name, attrs);

    EXPECT_EQ(parser->parseStack.size(), 2u); // Root + new element

}



TEST_F(ExpatAdapterTest_NormalOperation_2093, StartElementHandler_SetsRootNodeIfRDF_2093) {

    XMP_StringPtr rdfName = "rdf:RDF";

    EXPECT_EQ(parser->rootCount, 0u);

    StartElementHandler(parser, rdfName, attrs);

    EXPECT_NE(parser->rootNode, nullptr);

    EXPECT_EQ(parser->rootCount, 1u);

}



TEST_F(ExpatAdapterTest_BoundaryConditions_2093, StartElementHandler_NoAttributes_2093) {

    XMP_StringPtr noAttrs[] = {nullptr};

    EXPECT_EQ(parser->parseStack.size(), 1u); // Initial root node

    StartElementHandler(parser, name, noAttrs);

    EXPECT_EQ(parser->parseStack.size(), 2u); // Root + new element

}



TEST_F(ExpatAdapterTest_ExceptionalCases_2093, StartElementHandler_OddAttributesCountThrows_2093) {

    XMP_StringPtr oddAttrs[] = {"attr1", "value1", "attr2", nullptr};

    EXPECT_THROW(StartElementHandler(parser, name, oddAttrs), XMP_Error);

}



TEST_F(ExpatAdapterTest_NormalOperation_2093, StartElementHandler_AddsAttributesToNode_2093) {

    EXPECT_EQ(parser->parseStack.size(), 1u); // Initial root node

    StartElementHandler(parser, name, attrs);

    XML_Node* newNode = parser->parseStack.back();

    EXPECT_EQ(newNode->attrs.size(), 1u);

    EXPECT_STREQ(newNode->attrs[0]->name.c_str(), "attr1");

    EXPECT_STREQ(newNode->attrs[0]->value.c_str(), "value1");

}



TEST_F(ExpatAdapterTest_NormalOperation_2093, StartElementHandler_NormalizesLangValue_2093) {

    XMP_StringPtr langAttrs[] = {"xml:lang", "en-US", nullptr};

    EXPECT_EQ(parser->parseStack.size(), 1u); // Initial root node

    StartElementHandler(parser, name, langAttrs);

    XML_Node* newNode = parser->parseStack.back();

    EXPECT_STREQ(newNode->attrs[0]->name.c_str(), "xml:lang");

    EXPECT_STREQ(newNode->attrs[0]->value.c_str(), "en-US"); // Assuming normalization does not change value in this test

}



TEST_F(ExpatAdapterTest_ExceptionalCases_2093, StartElementHandler_NullNameThrows_2093) {

    XMP_StringPtr nullName = nullptr;

    EXPECT_THROW(StartElementHandler(parser, nullName, attrs), XMP_AssertFailed);

}



TEST_F(ExpatAdapterTest_BoundaryConditions_2093, StartElementHandler_EmptyAttributesArray_2093) {

    XMP_StringPtr emptyAttrs[] = {nullptr};

    EXPECT_EQ(parser->parseStack.size(), 1u); // Initial root node

    StartElementHandler(parser, name, emptyAttrs);

    XML_Node* newNode = parser->parseStack.back();

    EXPECT_EQ(newNode->attrs.size(), 0u);

}



TEST_F(ExpatAdapterTest_NormalOperation_2093, StartElementHandler_ParentChildRelationship_2093) {

    EXPECT_EQ(parser->parseStack.size(), 1u); // Initial root node

    StartElementHandler(parser, name, attrs);

    XML_Node* newNode = parser->parseStack.back();

    EXPECT_EQ(newNode->parent, &parser->tree);

}
