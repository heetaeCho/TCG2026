#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPCore_Impl.hpp"

#include "XMLParserAdapter.hpp"

#include "XMP_Const.h"



using namespace std;

using ::testing::Return;



class RDF_RDF_Test_2125 : public ::testing::Test {

protected:

    XMP_Node xmpTree{nullptr, "root", 0};

    XML_Node xmlNode{nullptr, "rdf:RDF", RDFTermKind};



    void SetUp() override {

        xmpTree.ClearNode();

        xmlNode.attrs.clear();

        xmlNode.content.clear();

    }

};



TEST_F(RDF_RDF_Test_2125, NoAttributesNormalOperation_2125) {

    RDF_RDF(&xmpTree, xmlNode);

    // Assuming no exception is thrown and the function completes successfully

}



TEST_F(RDF_RDF_Test_2125, AttributesPresentThrowsError_2125) {

    XML_Node attrNode{nullptr, "attr", RDFTermKind};

    xmlNode.attrs.push_back(attrNode);



    EXPECT_THROW({

        RDF_RDF(&xmpTree, xmlNode);

    }, XMP_Error);

}



TEST_F(RDF_RDF_Test_2125, AttributesPresentSpecificErrorCode_2125) {

    XML_Node attrNode{nullptr, "attr", RDFTermKind};

    xmlNode.attrs.push_back(attrNode);



    try {

        RDF_RDF(&xmpTree, xmlNode);

        FAIL() << "Expected exception not thrown";

    } catch (const XMP_Error& e) {

        EXPECT_EQ(e.GetID(), kXMPErr_BadRDF);

    }

}
