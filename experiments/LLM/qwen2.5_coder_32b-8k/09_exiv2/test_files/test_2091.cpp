#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMLParserAdapter.hpp"

#include "XMPMeta.hpp"



using namespace ::testing;



// Mock XMPMeta for external interactions

class MockXMPMeta : public XMPMeta {

public:

    MOCK_STATIC_METHOD3(GetNamespacePrefix, bool(XMP_StringPtr, XMP_StringPtr*, XMP_StringLen*));

};



TEST_F(XMLParserAdapterTest_2091, SetQualName_NamespacedURI_2091) {

    XML_Node node(nullptr, "", 0);

    const char* fullName = "http://purl.org/dc/1.1/title";

    MockXMPMeta::GetNamespacePrefix(fullName, nullptr, nullptr);



    EXPECT_CALL(MockXMPMeta, GetNamespacePrefix(StrEq("http://purl.org/dc/1.1/"), _, _))

        .WillOnce(DoAll(SetArgReferee<1>("dc"), SetArgReferee<2>(3), Return(true)));



    SetQualName(fullName, &node);



    EXPECT_EQ(node.ns, "http://purl.org/dc/elements/1.1/");

    EXPECT_EQ(node.name, "dc:title");

    EXPECT_EQ(node.nsPrefixLen, 4);

}



TEST_F(XMLParserAdapterTest_2091, SetQualName_NamespacedURIWithKnownPrefix_2091) {

    XML_Node node(nullptr, "", 0);

    const char* fullName = "http://purl.org/dc/elements/1.1/title";

    MockXMPMeta::GetNamespacePrefix(fullName, nullptr, nullptr);



    EXPECT_CALL(MockXMPMeta, GetNamespacePrefix(StrEq("http://purl.org/dc/elements/1.1/"), _, _))

        .WillOnce(DoAll(SetArgReferee<1>("dc"), SetArgReferee<2>(3), Return(true)));



    SetQualName(fullName, &node);



    EXPECT_EQ(node.ns, "http://purl.org/dc/elements/1.1/");

    EXPECT_EQ(node.name, "dc:title");

    EXPECT_EQ(node.nsPrefixLen, 4);

}



TEST_F(XMLParserAdapterTest_2091, SetQualName_UnregisteredNamespaceURI_2091) {

    XML_Node node(nullptr, "", 0);

    const char* fullName = "http://unknown.namespace/title";

    MockXMPMeta::GetNamespacePrefix(fullName, nullptr, nullptr);



    EXPECT_CALL(MockXMPMeta, GetNamespacePrefix(StrEq("http://unknown.namespace/"), _, _))

        .WillOnce(Return(false));



    EXPECT_THROW(SetQualName(fullName, &node), XMP_Error);



    EXPECT_EQ(node.ns, "");

    EXPECT_EQ(node.name, fullName);

}



TEST_F(XMLParserAdapterTest_2091, SetQualName_NoNamespaceURI_2091) {

    XML_Node node(nullptr, "", 0);

    const char* fullName = "title";

    MockXMPMeta::GetNamespacePrefix(fullName, nullptr, nullptr);



    EXPECT_CALL(MockXMPMeta, GetNamespacePrefix(_, _, _)).Times(0);



    SetQualName(fullName, &node);



    EXPECT_EQ(node.ns, "");

    EXPECT_EQ(node.name, fullName);

}



TEST_F(XMLParserAdapterTest_2091, SetQualName_RDFDescriptionAbout_2091) {

    XML_Node node(nullptr, "rdf:Description", 0);

    const char* fullName = "about";

    MockXMPMeta::GetNamespacePrefix(fullName, nullptr, nullptr);



    EXPECT_CALL(MockXMPMeta, GetNamespacePrefix(_, _, _)).Times(0);



    SetQualName(fullName, &node);



    EXPECT_EQ(node.ns, kXMP_NS_RDF);

    EXPECT_EQ(node.name, "rdf:about");

    EXPECT_EQ(node.nsPrefixLen, 4);

}



TEST_F(XMLParserAdapterTest_2091, SetQualName_RDFDescriptionID_2091) {

    XML_Node node(nullptr, "rdf:Description", 0);

    const char* fullName = "ID";

    MockXMPMeta::GetNamespacePrefix(fullName, nullptr, nullptr);



    EXPECT_CALL(MockXMPMeta, GetNamespacePrefix(_, _, _)).Times(0);



    SetQualName(fullName, &node);



    EXPECT_EQ(node.ns, kXMP_NS_RDF);

    EXPECT_EQ(node.name, "rdf:ID");

    EXPECT_EQ(node.nsPrefixLen, 4);

}
