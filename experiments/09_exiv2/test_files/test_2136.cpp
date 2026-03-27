#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "XMPCore_Impl.hpp"

#include "XMLParserAdapter.hpp"



using namespace std;



class ParseRDFTest_2136 : public ::testing::Test {

protected:

    XMP_Node xmpParent;

    XML_Node xmlNode;

    

    void SetUp() override {

        xmpParent = XMP_Node(nullptr, "parent", 0);

        xmlNode = XML_Node(nullptr, "child", 0);

    }

};



TEST_F(ParseRDFTest_2136, RDF_ParseTypeOtherPropertyElement_ThrowsException_2136) {

    EXPECT_THROW(RDF_ParseTypeOtherPropertyElement(&xmpParent, xmlNode, true), XMP_Error);

}



TEST_F(ParseRDFTest_2136, RDF_ParseTypeOtherPropertyElement_ExceptionMessage_2136) {

    try {

        RDF_ParseTypeOtherPropertyElement(&xmpParent, xmlNode, true);

    } catch (const XMP_Error& err) {

        EXPECT_STREQ(err.GetErrMsg(), "ParseTypeOther property element not allowed");

    }

}



TEST_F(ParseRDFTest_2136, RDF_ParseTypeOtherPropertyElement_ExceptionCode_2136) {

    try {

        RDF_ParseTypeOtherPropertyElement(&xmpParent, xmlNode, true);

    } catch (const XMP_Error& err) {

        EXPECT_EQ(err.GetID(), kXMPErr_BadXMP);

    }

}



TEST_F(ParseRDFTest_2136, RDF_ParseTypeOtherPropertyElement_TopLevelTrue_2136) {

    EXPECT_THROW(RDF_ParseTypeOtherPropertyElement(&xmpParent, xmlNode, true), XMP_Error);

}



TEST_F(ParseRDFTest_2136, RDF_ParseTypeOtherPropertyElement_TopLevelFalse_2136) {

    EXPECT_THROW(RDF_ParseTypeOtherPropertyElement(&xmpParent, xmlNode, false), XMP_Error);

}
