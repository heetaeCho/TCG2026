#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming necessary headers and namespaces are included for XMP_Node, XML_Node, etc.



class RDF_ResourcePropertyElementTest : public ::testing::Test {

protected:

    XMP_Node xmpParent{nullptr, "parent", 0};

    XML_Node xmlNode{nullptr, "testName", kElemNode};



    void SetUp() override {

        // Setup common state before each test

        xmlNode.attrs.clear();

        xmlNode.content.clear();

    }

};



TEST_F(RDF_ResourcePropertyElementTest_2131, NormalOperation_RDF_Description_Child_2131) {

    XML_Node child{&xmlNode, "rdf:Description", kElemNode};

    child.ns = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";

    xmlNode.content.push_back(&child);



    RDF_ResourcePropertyElement(&xmpParent, xmlNode, true);

    

    EXPECT_EQ(xmpParent.children.size(), 1);

    XMP_Node* newCompound = xmpParent.children[0];

    EXPECT_EQ(newCompound->name, "testName");

    EXPECT_EQ(newCompound->options & kXMP_PropValueIsStruct, kXMP_PropValueIsStruct);

}



TEST_F(RDF_ResourcePropertyElementTest_2131, NormalOperation_RDF_Bag_Child_2131) {

    XML_Node child{&xmlNode, "rdf:Bag", kElemNode};

    child.ns = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";

    xmlNode.content.push_back(&child);



    RDF_ResourcePropertyElement(&xmpParent, xmlNode, true);

    

    EXPECT_EQ(xmpParent.children.size(), 1);

    XMP_Node* newCompound = xmpParent.children[0];

    EXPECT_EQ(newCompound->name, "testName");

    EXPECT_EQ(newCompound->options & kXMP_PropValueIsArray, kXMP_PropValueIsArray);

}



TEST_F(RDF_ResourcePropertyElementTest_2131, NormalOperation_RDF_Sequence_Child_2131) {

    XML_Node child{&xmlNode, "rdf:Seq", kElemNode};

    child.ns = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";

    xmlNode.content.push_back(&child);



    RDF_ResourcePropertyElement(&xmpParent, xmlNode, true);

    

    EXPECT_EQ(xmpParent.children.size(), 1);

    XMP_Node* newCompound = xmpParent.children[0];

    EXPECT_EQ(newCompound->name, "testName");

    EXPECT_EQ(newCompound->options & kXMP_PropArrayIsOrdered, kXMP_PropArrayIsOrdered);

}



TEST_F(RDF_ResourcePropertyElementTest_2131, NormalOperation_RDF_Alt_Child_2131) {

    XML_Node child{&xmlNode, "rdf:Alt", kElemNode};

    child.ns = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";

    xmlNode.content.push_back(&child);



    RDF_ResourcePropertyElement(&xmpParent, xmlNode, true);

    

    EXPECT_EQ(xmpParent.children.size(), 1);

    XMP_Node* newCompound = xmpParent.children[0];

    EXPECT_EQ(newCompound->name, "testName");

    EXPECT_EQ(newCompound->options & kXMP_PropArrayIsAlternate, kXMP_PropArrayIsAlternate);

}



TEST_F(RDF_ResourcePropertyElementTest_2131, NormalOperation_RDF_Child_With_Type_2131) {

    XML_Node child{&xmlNode, "customType", kElemNode};

    child.ns = "http://example.com/ns#";

    xmlNode.content.push_back(&child);



    RDF_ResourcePropertyElement(&xmpParent, xmlNode, true);

    

    EXPECT_EQ(xmpParent.children.size(), 1);

    XMP_Node* newCompound = xmpParent.children[0];

    EXPECT_EQ(newCompound->name, "testName");

    EXPECT_EQ(newCompound->options & kXMP_PropValueIsStruct, kXMP_PropValueIsStruct);

    EXPECT_EQ(newCompound->qualifiers.size(), 1);

    XMP_Node* qualifier = newCompound->qualifiers[0];

    EXPECT_EQ(qualifier->name, "rdf:type");

    EXPECT_EQ(qualifier->value, "http://example.com/ns#customType");

}



TEST_F(RDF_ResourcePropertyElementTest_2131, Exception_TopLevel_iX_Changes_2131) {

    xmlNode.name = "iX:changes";



    EXPECT_THROW({

        RDF_ResourcePropertyElement(&xmpParent, xmlNode, true);

    }, XMP_Error);



    // Assuming XMP_Error is thrown with code kXMPErr_BadRDF

}



TEST_F(RDF_ResourcePropertyElementTest_2131, Exception_Missing_Child_2131) {

    EXPECT_THROW({

        RDF_ResourcePropertyElement(&xmpParent, xmlNode, true);

    }, XMP_Error);



    // Assuming XMP_Error is thrown with code kXMPErr_BadRDF

}



TEST_F(RDF_ResourcePropertyElementTest_2131, Exception_Non_Element_Child_2131) {

    XML_Node child{&xmlNode, "text", kCDataNode};

    xmlNode.content.push_back(&child);



    EXPECT_THROW({

        RDF_ResourcePropertyElement(&xmpParent, xmlNode, true);

    }, XMP_Error);



    // Assuming XMP_Error is thrown with code kXMPErr_BadRDF

}



TEST_F(RDF_ResourcePropertyElementTest_2131, Exception_Non_Namespace_Element_Child_2131) {

    XML_Node child{&xmlNode, "customType", kElemNode};

    xmlNode.content.push_back(&child);



    EXPECT_THROW({

        RDF_ResourcePropertyElement(&xmpParent, xmlNode, true);

    }, XMP_Error);



    // Assuming XMP_Error is thrown with code kXMPErr_BadXMP

}



TEST_F(RDF_ResourcePropertyElementTest_2131, Exception_Invalid_Attribute_2131) {

    XML_Node attr{nullptr, "invalidAttr", kAttrNode};

    xmlNode.attrs.push_back(&attr);



    EXPECT_THROW({

        RDF_ResourcePropertyElement(&xmpParent, xmlNode, true);

    }, XMP_Error);



    // Assuming XMP_Error is thrown with code kXMPErr_BadRDF

}
