#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp"

#include "./TestProjects/exiv2/xmpsdk/include/XMP_Const.h"



using namespace testing;



// Mock XMP_Node for testing purposes

class MockXMP_Node : public XMP_Node {

public:

    MOCK_METHOD(void, RemoveChildren, (), (override));

    MOCK_METHOD(void, RemoveQualifiers, (), (override));

    MOCK_METHOD(void, ClearNode, (), (override));



    using XMP_Node::XMP_Node;

};



// Mock XML_Node for testing purposes

class MockXML_Node : public XML_Node {

public:

    MOCK_CONST_METHOD0(IsWhitespaceNode, bool());

    MOCK_CONST_METHOD0(IsLeafContentNode, bool());

    MOCK_CONST_METHOD0(IsEmptyLeafNode, bool());

    MOCK_CONST_METHOD1(GetAttrValue, XMP_StringPtr(XMP_StringPtr attrName));

    MOCK_METHOD2(SetAttrValue, void(XMP_StringPtr attrName, XMP_StringPtr attrValue));

    MOCK_CONST_METHOD0(GetLeafContentValue, XMP_StringPtr());

    MOCK_METHOD1(SetLeafContentValue, void(XMP_StringPtr value));

    MOCK_CONST_METHOD3(CountNamedElements, size_t(XMP_StringPtr nsURI, XMP_StringPtr localName, size_t which));

    MOCK_METHOD2(GetNamedElement, XML_NodePtr(XMP_StringPtr nsURI, XMP_StringPtr localName, size_t which));

    MOCK_METHOD0(RemoveAttrs, void());

    MOCK_METHOD0(RemoveContent, void());

    MOCK_METHOD0(ClearNode, void());



    using XML_Node::XML_Node;

};



// Test Fixture

class RDF_NodeElementTest_2127 : public ::testing::Test {

protected:

    std::unique_ptr<MockXMP_Node> xmpParent;

    std::unique_ptr<MockXML_Node> xmlNode;



    void SetUp() override {

        xmpParent = std::make_unique<MockXMP_Node>(nullptr, "parent", 0);

        xmlNode = std::make_unique<MockXML_Node>(nullptr, "node", 1);

    }

};



// Test Normal Operation

TEST_F(RDF_NodeElementTest_2127, NodeIsRdfDescription_TopLevel_2127) {

    xmlNode->name = "rdf:Description";

    EXPECT_CALL(*xmpParent.get(), RemoveChildren()).Times(0);

    EXPECT_CALL(*xmpParent.get(), RemoveQualifiers()).Times(0);

    EXPECT_CALL(*xmpParent.get(), ClearNode()).Times(0);



    EXPECT_NO_THROW(RDF_NodeElement(xmpParent.get(), *xmlNode, true));

}



TEST_F(RDF_NodeElementTest_2127, NodeIsTypedNode_TopLevelFalse_2127) {

    xmlNode->name = "typedNode";

    EXPECT_CALL(*xmpParent.get(), RemoveChildren()).Times(0);

    EXPECT_CALL(*xmpParent.get(), RemoveQualifiers()).Times(0);

    EXPECT_CALL(*xmpParent.get(), ClearNode()).Times(0);



    EXPECT_NO_THROW(RDF_NodeElement(xmpParent.get(), *xmlNode, false));

}



// Test Boundary Conditions

TEST_F(RDF_NodeElementTest_2127, NodeIsTypedNode_TopLevelTrue_2127) {

    xmlNode->name = "typedNode";

    EXPECT_CALL(*xmpParent.get(), RemoveChildren()).Times(0);

    EXPECT_CALL(*xmpParent.get(), RemoveQualifiers()).Times(0);

    EXPECT_CALL(*xmpParent.get(), ClearNode()).Times(0);



    EXPECT_THROW(RDF_NodeElement(xmpParent.get(), *xmlNode, true), XMP_Error);

}



// Test Exceptional or Error Cases

TEST_F(RDF_NodeElementTest_2127, NodeIsUnknown_TopLevelTrue_2127) {

    xmlNode->name = "unknownNode";

    EXPECT_CALL(*xmpParent.get(), RemoveChildren()).Times(0);

    EXPECT_CALL(*xmpParent.get(), RemoveQualifiers()).Times(0);

    EXPECT_CALL(*xmpParent.get(), ClearNode()).Times(0);



    EXPECT_THROW(RDF_NodeElement(xmpParent.get(), *xmlNode, true), XMP_Error);

}



TEST_F(RDF_NodeElementTest_2127, NodeIsUnknown_TopLevelFalse_2127) {

    xmlNode->name = "unknownNode";

    EXPECT_CALL(*xmpParent.get(), RemoveChildren()).Times(0);

    EXPECT_CALL(*xmpParent.get(), RemoveQualifiers()).Times(0);

    EXPECT_CALL(*xmpParent.get(), ClearNode()).Times(0);



    EXPECT_THROW(RDF_NodeElement(xmpParent.get(), *xmlNode, false), XMP_Error);

}



// Mock GetRDFTermKind function for testing

XMP_Uns8 GetRDFTermKind(const std::string& name) {

    if (name == "rdf:Description") return kRDFTerm_Description;

    else if (name == "typedNode") return kRDFTerm_Other;

    else return static_cast<XMP_Uns8>(-1);

}
