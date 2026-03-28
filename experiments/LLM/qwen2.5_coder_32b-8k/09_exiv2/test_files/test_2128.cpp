#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "XMPCore_Impl.hpp"

#include "XMLParserAdapter.hpp"



using namespace XMP_NAMESPACE;



class RDF_NodeElementAttrsTest : public ::testing::Test {

protected:

    void SetUp() override {

        xmpParent = new XMP_Node(nullptr, "parentName", 0);

        xmlNode = XML_Node(nullptr, "nodeName", 0);

    }



    void TearDown() override {

        delete xmpParent;

    }



    XMP_Node* xmpParent;

    XML_Node xmlNode;

};



TEST_F(RDF_NodeElementAttrsTest_2128, NormalOperationWithValidAttributes_2128) {

    xmlNode.attrs.push_back(new XML_Node(nullptr, "about", 0));

    xmlNode.attrs.push_back(new XML_Node(nullptr, "otherAttr", 0));



    EXPECT_NO_THROW(RDF_NodeElementAttrs(xmpParent, xmlNode, true));



    // Check if the xmpParent's name is set correctly

    EXPECT_EQ(xmpParent->name, "nodeName");

}



TEST_F(RDF_NodeElementAttrsTest_2128, BoundaryConditionWithNoAttributes_2128) {

    EXPECT_NO_THROW(RDF_NodeElementAttrs(xmpParent, xmlNode, true));

}



TEST_F(RDF_NodeElementAttrsTest_2128, ExceptionalCaseWithMutuallyExclusiveAttributes_2128) {

    xmlNode.attrs.push_back(new XML_Node(nullptr, "about", 0));

    xmlNode.attrs.push_back(new XML_Node(nullptr, "ID", 0));



    EXPECT_THROW({

        try {

            RDF_NodeElementAttrs(xmpParent, xmlNode, true);

        } catch (const XMP_Error& e) {

            EXPECT_EQ(e.GetID(), kXMPErr_BadRDF);

            throw;

        }

    }, XMP_Error);

}



TEST_F(RDF_NodeElementAttrsTest_2128, ExceptionalCaseWithMismatchedTopLevelAboutValues_2128) {

    xmpParent->name = "existingName";

    xmlNode.attrs.push_back(new XML_Node(nullptr, "about", 0));

    xmlNode.GetNamedElement("", "about", 0)->SetAttrValue("about", "differentName");



    EXPECT_THROW({

        try {

            RDF_NodeElementAttrs(xmpParent, xmlNode, true);

        } catch (const XMP_Error& e) {

            EXPECT_EQ(e.GetID(), kXMPErr_BadXMP);

            throw;

        }

    }, XMP_Error);

}



TEST_F(RDF_NodeElementAttrsTest_2128, ExceptionalCaseWithInvalidNodeElementAttribute_2128) {

    xmlNode.attrs.push_back(new XML_Node(nullptr, "invalidAttr", 0));



    EXPECT_THROW({

        try {

            RDF_NodeElementAttrs(xmpParent, xmlNode, true);

        } catch (const XMP_Error& e) {

            EXPECT_EQ(e.GetID(), kXMPErr_BadRDF);

            throw;

        }

    }, XMP_Error);

}
