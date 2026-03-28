#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp"

#include "./TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"

#include "./TestProjects/exiv2/xmpsdk/src/XMLParserAdapter.hpp"



using namespace ::testing;



TEST(RDF_ParseTypeCollectionPropertyElement_2135, ThrowsExceptionOnNormalOperation_2135) {

    XMP_Node xmpParent(nullptr, "parentName", 0);

    XML_Node xmlNode(nullptr, "nodeName", 0);



    EXPECT_THROW({

        RDF_ParseTypeCollectionPropertyElement(&xmpParent, xmlNode, true);

    }, XMP_Error);

}



TEST(RDF_ParseTypeCollectionPropertyElement_2135, ExceptionMessageContainsExpectedText_2135) {

    XMP_Node xmpParent(nullptr, "parentName", 0);

    XML_Node xmlNode(nullptr, "nodeName", 0);



    try {

        RDF_ParseTypeCollectionPropertyElement(&xmpParent, xmlNode, true);

        FAIL() << "Expected exception not thrown";

    } catch (const XMP_Error& e) {

        EXPECT_STREQ(e.what(), "ParseTypeCollection property element not allowed");

    }

}



TEST(RDF_ParseTypeCollectionPropertyElement_2135, ExceptionCodeIsCorrect_2135) {

    XMP_Node xmpParent(nullptr, "parentName", 0);

    XML_Node xmlNode(nullptr, "nodeName", 0);



    try {

        RDF_ParseTypeCollectionPropertyElement(&xmpParent, xmlNode, true);

        FAIL() << "Expected exception not thrown";

    } catch (const XMP_Error& e) {

        EXPECT_EQ(e.GetID(), kXMPErr_BadXMP);

    }

}



TEST(RDF_ParseTypeCollectionPropertyElement_2135, DoesNotThrowForDifferentIsTopLevelValue_2135) {

    XMP_Node xmpParent(nullptr, "parentName", 0);

    XML_Node xmlNode(nullptr, "nodeName", 0);



    EXPECT_THROW({

        RDF_ParseTypeCollectionPropertyElement(&xmpParent, xmlNode, false);

    }, XMP_Error);

}



TEST(RDF_ParseTypeCollectionPropertyElement_2135, ThrowsExceptionForEmptyXMPNodeName_2135) {

    XMP_Node xmpParent(nullptr, "", 0);

    XML_Node xmlNode(nullptr, "nodeName", 0);



    EXPECT_THROW({

        RDF_ParseTypeCollectionPropertyElement(&xmpParent, xmlNode, true);

    }, XMP_Error);

}



TEST(RDF_ParseTypeCollectionPropertyElement_2135, ThrowsExceptionForEmptyXMLNodeName_2135) {

    XMP_Node xmpParent(nullptr, "parentName", 0);

    XML_Node xmlNode(nullptr, "", 0);



    EXPECT_THROW({

        RDF_ParseTypeCollectionPropertyElement(&xmpParent, xmlNode, true);

    }, XMP_Error);

}



TEST(RDF_ParseTypeCollectionPropertyElement_2135, ThrowsExceptionForNullXMPNodePointer_2135) {

    XML_Node xmlNode(nullptr, "nodeName", 0);



    EXPECT_THROW({

        RDF_ParseTypeCollectionPropertyElement(nullptr, xmlNode, true);

    }, XMP_Error);

}
