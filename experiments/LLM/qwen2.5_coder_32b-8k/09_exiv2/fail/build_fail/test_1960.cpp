#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMLParserAdapter.hpp"

#include "XMPMeta.hpp"



using namespace testing;



class MockXMLParserAdapter : public XMLParserAdapter {

public:

    MOCK_CONST_METHOD0(rootNode, const XML_Node*());

    MOCK_CONST_METHOD0(rootCount, size_t());

};



class XMPMetaTest_1960 : public Test {

protected:

    XMPMeta xmpMeta;

    std::shared_ptr<MockXMLParserAdapter> mockXmlParser;



    void SetUp() override {

        mockXmlParser = std::make_shared<MockXMLParserAdapter>();

        xmpMeta.xmlParser = mockXmlParser.get();

    }



    void TearDown() override {

        xmpMeta.xmlParser = nullptr;

    }

};



TEST_F(XMPMetaTest_1960, FindRootNode_NormalOperation_ReturnsRootNode_1960) {

    XMP_OptionBits options = 0;

    XML_Node rootNode("parent", "rdf:RDF", kRootNode);

    EXPECT_CALL(*mockXmlParser, rootCount()).WillOnce(Return(1));

    EXPECT_CALL(*mockXmlParser, rootNode()).WillOnce(Return(&rootNode));



    const XML_Node* result = FindRootNode(&xmpMeta, *mockXmlParser, options);



    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->name, "rdf:RDF");

}



TEST_F(XMPMetaTest_1960, FindRootNode_NoRootNodes_ReturnsNull_1960) {

    XMP_OptionBits options = 0;

    EXPECT_CALL(*mockXmlParser, rootCount()).WillOnce(Return(0));



    const XML_Node* result = FindRootNode(&xmpMeta, *mockXmlParser, options);



    EXPECT_EQ(result, nullptr);

}



TEST_F(XMPMetaTest_1960, FindRootNode_MultipleRootNodes_ReturnsBestRoot_1960) {

    XMP_OptionBits options = 0;

    XML_Node rootNode("parent", "rdf:RDF", kRootNode);

    EXPECT_CALL(*mockXmlParser, rootCount()).WillOnce(Return(2));

    EXPECT_CALL(*mockXmlParser, rootNode()).WillOnce(Return(&rootNode));



    const XML_Node* result = FindRootNode(&xmpMeta, *mockXmlParser, options);



    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->name, "rdf:RDF");

}



TEST_F(XMPMetaTest_1960, FindRootNode_RequireXMPMeta_NoXMPMeta_ReturnsNull_1960) {

    XMP_OptionBits options = kXMP_RequireXMPMeta;

    XML_Node rootNode("parent", "rdf:RDF", kRootNode);

    EXPECT_CALL(*mockXmlParser, rootCount()).WillOnce(Return(1));

    EXPECT_CALL(*mockXmlParser, rootNode()).WillOnce(Return(&rootNode));



    const XML_Node* result = FindRootNode(&xmpMeta, *mockXmlParser, options);



    EXPECT_EQ(result, nullptr);

}



TEST_F(XMPMetaTest_1960, FindRootNode_XMPTKVersionParsing_NormalOperation_SetsPrevTkVer_1960) {

    XMP_OptionBits options = 0;

    XML_Node parent(nullptr, "x:xmpmeta", kRootNode);

    XML_Node rootNode(&parent, "rdf:RDF", kRootNode);

    XML_Node attrNode(&rootNode, "x:xmptk", kAttrNode);

    attrNode.value = "1.2.3";

    rootNode.parent->attrs.push_back(&attrNode);



    EXPECT_CALL(*mockXmlParser, rootCount()).WillOnce(Return(1));

    EXPECT_CALL(*mockXmlParser, rootNode()).WillOnce(Return(&rootNode));



    const XML_Node* result = FindRootNode(&xmpMeta, *mockXmlParser, options);



    ASSERT_NE(result, nullptr);

    EXPECT_EQ(xmpMeta.prevTkVer, 10203000);

}



TEST_F(XMPMetaTest_1960, FindRootNode_XMPTKVersionParsing_TruncatedValue_SetsPrevTkVer_1960) {

    XMP_OptionBits options = 0;

    XML_Node parent(nullptr, "x:xmpmeta", kRootNode);

    XML_Node rootNode(&parent, "rdf:RDF", kRootNode);

    XML_Node attrNode(&rootNode, "x:xmptk", kAttrNode);

    attrNode.value = "1.2";

    rootNode.parent->attrs.push_back(&attrNode);



    EXPECT_CALL(*mockXmlParser, rootCount()).WillOnce(Return(1));

    EXPECT_CALL(*mockXmlParser, rootNode()).WillOnce(Return(&rootNode));



    const XML_Node* result = FindRootNode(&xmpMeta, *mockXmlParser, options);



    ASSERT_NE(result, nullptr);

    EXPECT_EQ(xmpMeta.prevTkVer, 10200000);

}



TEST_F(XMPMetaTest_1960, FindRootNode_XMPTKVersionParsing_InvalidValue_SetsPrevTkVerToZero_1960) {

    XMP_OptionBits options = 0;

    XML_Node parent(nullptr, "x:xmpmeta", kRootNode);

    XML_Node rootNode(&parent, "rdf:RDF", kRootNode);

    XML_Node attrNode(&rootNode, "x:xmptk", kAttrNode);

    attrNode.value = "abc";

    rootNode.parent->attrs.push_back(&attrNode);



    EXPECT_CALL(*mockXmlParser, rootCount()).WillOnce(Return(1));

    EXPECT_CALL(*mockXmlParser, rootNode()).WillOnce(Return(&rootNode));



    const XML_Node* result = FindRootNode(&xmpMeta, *mockXmlParser, options);



    ASSERT_NE(result, nullptr);

    EXPECT_EQ(xmpMeta.prevTkVer, 0);

}
