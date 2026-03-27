#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMLParserAdapter.hpp"

#include "XMPCore_Impl.hpp"



// Mocking RDF functions to verify calls without re-implementing logic.

class MockRDFFunctions {

public:

    MOCK_STATIC_METHOD3(RDF_EmptyPropertyElement, void(XMP_Node*, const XML_Node&, bool));

    MOCK_STATIC_METHOD3(RDF_LiteralPropertyElement, void(XMP_Node*, const XML_Node&, bool));

    MOCK_STATIC_METHOD3(RDF_ParseTypeLiteralPropertyElement, void(XMP_Node*, const XML_Node&, bool));

    MOCK_STATIC_METHOD3(RDF_ParseTypeResourcePropertyElement, void(XMP_Node*, const XML_Node&, bool));

    MOCK_STATIC_METHOD3(RDF_ParseTypeCollectionPropertyElement, void(XMP_Node*, const XML_Node&, bool));

    MOCK_STATIC_METHOD3(RDF_ParseTypeOtherPropertyElement, void(XMP_Node*, const XML_Node&, bool));

    MOCK_STATIC_METHOD3(RDF_ResourcePropertyElement, void(XMP_Node*, const XML_Node&, bool));

};



// Mocking IsPropertyElementName to control its behavior in tests.

bool mock_IsPropertyElementName(RDFTermKind term) {

    return testing::MockFunction<bool(RDFTermKind)>().Call(term);

}



// Mocking GetRDFTermKind to control its behavior in tests.

RDFTermKind mock_GetRDFTermKind(const std::string& name) {

    return testing::MockFunction<RDFTermKind(const std::string&)>().Call(name);

}



TEST_F(ParseRDFFunctionTest_2130, InvalidPropertyElementNameThrowsException_2130) {

    XMP_Node xmpParent(nullptr, "parent", 0);

    XML_Node xmlNode(nullptr, "invalid_name", kElemNode);



    EXPECT_CALL(testing::MockFunction<bool(RDFTermKind)>(), Call(::testing::_))

        .WillOnce(::testing::Return(false));



    EXPECT_THROW(RDF_PropertyElement(&xmpParent, xmlNode, true), XMP_Error);

}



TEST_F(ParseRDFFunctionTest_2130, MoreThanThreeAttributesCallsEmptyPropertyElement_2130) {

    XMP_Node xmpParent(nullptr, "parent", 0);

    XML_Node xmlNode(nullptr, "valid_name", kElemNode);



    // Adding more than three attributes.

    xmlNode.attrs.push_back(std::make_shared<XML_Node>(nullptr, "attr1", kAttrNode));

    xmlNode.attrs.push_back(std::make_shared<XML_Node>(nullptr, "attr2", kAttrNode));

    xmlNode.attrs.push_back(std::make_shared<XML_Node>(nullptr, "attr3", kAttrNode));

    xmlNode.attrs.push_back(std::make_shared<XML_Node>(nullptr, "attr4", kAttrNode));



    EXPECT_CALL(testing::MockFunction<bool(RDFTermKind)>(), Call(::testing::_))

        .WillOnce(::testing::Return(true));



    EXPECT_CALL(MockRDFFunctions::RDF_EmptyPropertyElement, 

                Testing::(_, ::testing::Ref(xmlNode), true));



    RDF_PropertyElement(&xmpParent, xmlNode, true);

}



TEST_F(ParseRDFFunctionTest_2130, ValidAttributesCallsCorrectMethod_2130) {

    XMP_Node xmpParent(nullptr, "parent", 0);

    XML_Node xmlNode(nullptr, "valid_name", kElemNode);



    // Adding valid attributes.

    xmlNode.attrs.push_back(std::make_shared<XML_Node>(nullptr, "xml:lang", kAttrNode));

    xmlNode.attrs.push_back(std::make_shared<XML_Node>(nullptr, "rdf:ID", kAttrNode));



    EXPECT_CALL(testing::MockFunction<bool(RDFTermKind)>(), Call(::testing::_))

        .WillOnce(::testing::Return(true));



    EXPECT_CALL(MockRDFFunctions::RDF_EmptyPropertyElement, 

                Testing::(_, ::testing::Ref(xmlNode), true));



    RDF_PropertyElement(&xmpParent, xmlNode, true);

}



TEST_F(ParseRDFFunctionTest_2130, RDFTermKindCallsCorrectMethodBasedOnAttrValue_2130) {

    XMP_Node xmpParent(nullptr, "parent", 0);

    XML_Node xmlNode(nullptr, "valid_name", kElemNode);



    // Adding attribute with valid rdf:datatype.

    xmlNode.attrs.push_back(std::make_shared<XML_Node>(nullptr, "rdf:datatype", kAttrNode));

    xmlNode.attrs.back()->SetAttrValue("rdf:datatype", "some_type");



    EXPECT_CALL(testing::MockFunction<bool(RDFTermKind)>(), Call(::testing::_))

        .WillOnce(::testing::Return(true));



    EXPECT_CALL(MockRDFFunctions::RDF_LiteralPropertyElement, 

                Testing::(_, ::testing::Ref(xmlNode), true));



    RDF_PropertyElement(&xmpParent, xmlNode, true);

}



TEST_F(ParseRDFFunctionTest_2130, RDFTermKindCallsCorrectMethodBasedOnParseTypeLiteral_2130) {

    XMP_Node xmpParent(nullptr, "parent", 0);

    XML_Node xmlNode(nullptr, "valid_name", kElemNode);



    // Adding attribute with rdf:parseType = Literal.

    xmlNode.attrs.push_back(std::make_shared<XML_Node>(nullptr, "rdf:parseType", kAttrNode));

    xmlNode.attrs.back()->SetAttrValue("rdf:parseType", "Literal");



    EXPECT_CALL(testing::MockFunction<bool(RDFTermKind)>(), Call(::testing::_))

        .WillOnce(::testing::Return(true));



    EXPECT_CALL(MockRDFFunctions::RDF_ParseTypeLiteralPropertyElement, 

                Testing::(_, ::testing::Ref(xmlNode), true));



    RDF_PropertyElement(&xmpParent, xmlNode, true);

}



TEST_F(ParseRDFFunctionTest_2130, RDFTermKindCallsCorrectMethodBasedOnParseTypeResource_2130) {

    XMP_Node xmpParent(nullptr, "parent", 0);

    XML_Node xmlNode(nullptr, "valid_name", kElemNode);



    // Adding attribute with rdf:parseType = Resource.

    xmlNode.attrs.push_back(std::make_shared<XML_Node>(nullptr, "rdf:parseType", kAttrNode));

    xmlNode.attrs.back()->SetAttrValue("rdf:parseType", "Resource");



    EXPECT_CALL(testing::MockFunction<bool(RDFTermKind)>(), Call(::testing::_))

        .WillOnce(::testing::Return(true));



    EXPECT_CALL(MockRDFFunctions::RDF_ParseTypeResourcePropertyElement, 

                Testing::(_, ::testing::Ref(xmlNode), true));



    RDF_PropertyElement(&xmpParent, xmlNode, true);

}



TEST_F(ParseRDFFunctionTest_2130, RDFTermKindCallsCorrectMethodBasedOnParseTypeCollection_2130) {

    XMP_Node xmpParent(nullptr, "parent", 0);

    XML_Node xmlNode(nullptr, "valid_name", kElemNode);



    // Adding attribute with rdf:parseType = Collection.

    xmlNode.attrs.push_back(std::make_shared<XML_Node>(nullptr, "rdf:parseType", kAttrNode));

    xmlNode.attrs.back()->SetAttrValue("rdf:parseType", "Collection");



    EXPECT_CALL(testing::MockFunction<bool(RDFTermKind)>(), Call(::testing::_))

        .WillOnce(::testing::Return(true));



    EXPECT_CALL(MockRDFFunctions::RDF_ParseTypeCollectionPropertyElement, 

                Testing::(_, ::testing::Ref(xmlNode), true));



    RDF_PropertyElement(&xmpParent, xmlNode, true);

}



TEST_F(ParseRDFFunctionTest_2130, RDFTermKindCallsCorrectMethodBasedOnParseTypeOther_2130) {

    XMP_Node xmpParent(nullptr, "parent", 0);

    XML_Node xmlNode(nullptr, "valid_name", kElemNode);



    // Adding attribute with rdf:parseType = Other.

    xmlNode.attrs.push_back(std::make_shared<XML_Node>(nullptr, "rdf:parseType", kAttrNode));

    xmlNode.attrs.back()->SetAttrValue("rdf:parseType", "Other");



    EXPECT_CALL(testing::MockFunction<bool(RDFTermKind)>(), Call(::testing::_))

        .WillOnce(::testing::Return(true));



    EXPECT_CALL(MockRDFFunctions::RDF_ParseTypeOtherPropertyElement, 

                Testing::(_, ::testing::Ref(xmlNode), true));



    RDF_PropertyElement(&xmpParent, xmlNode, true);

}



TEST_F(ParseRDFFunctionTest_2130, NoAttributesAndEmptyContentCallsEmptyPropertyElement_2130) {

    XMP_Node xmpParent(nullptr, "parent", 0);

    XML_Node xmlNode(nullptr, "valid_name", kElemNode);



    EXPECT_CALL(testing::MockFunction<bool(RDFTermKind)>(), Call(::testing::_))

        .WillOnce(::testing::Return(true));



    EXPECT_CALL(MockRDFFunctions::RDF_EmptyPropertyElement, 

                Testing::(_, ::testing::Ref(xmlNode), true));



    RDF_PropertyElement(&xmpParent, xmlNode, true);

}



TEST_F(ParseRDFFunctionTest_2130, NoAttributesAndCDataContentCallsLiteralPropertyElement_2130) {

    XMP_Node xmpParent(nullptr, "parent", 0);

    XML_Node xmlNode(nullptr, "valid_name", kElemNode);



    // Adding CData node as content.

    xmlNode.content.push_back(std::make_shared<XML_Node>(nullptr, "", kCDataNode));



    EXPECT_CALL(testing::MockFunction<bool(RDFTermKind)>(), Call(::testing::_))

        .WillOnce(::testing::Return(true));



    EXPECT_CALL(MockRDFFunctions::RDF_LiteralPropertyElement, 

                Testing::(_, ::testing::Ref(xmlNode), true));



    RDF_PropertyElement(&xmpParent, xmlNode, true);

}



TEST_F(ParseRDFFunctionTest_2130, NoAttributesAndNonCDataContentCallsResourcePropertyElement_2130) {

    XMP_Node xmpParent(nullptr, "parent", 0);

    XML_Node xmlNode(nullptr, "valid_name", kElemNode);



    // Adding non-CData node as content.

    xmlNode.content.push_back(std::make_shared<XML_Node>(nullptr, "", kElemNode));



    EXPECT_CALL(testing::MockFunction<bool(RDFTermKind)>(), Call(::testing::_))

        .WillOnce(::testing::Return(true));



    EXPECT_CALL(MockRDFFunctions::RDF_ResourcePropertyElement, 

                Testing::(_, ::testing::Ref(xmlNode), true));



    RDF_PropertyElement(&xmpParent, xmlNode, true);

}
