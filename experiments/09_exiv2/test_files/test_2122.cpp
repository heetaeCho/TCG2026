#include <gtest/gtest.h>

#include "XMLParserAdapter.hpp"

#include "XMPCore_Impl.hpp"



// Assuming AddQualifierNode is part of a class or namespace, we'll assume it's in a global scope for this example.

// If it's part of a specific class, the TEST_F macro should be used with the appropriate fixture.



TEST(AddQualifierNodeTest_2122, NormalOperationWithValidNamespace_2122) {

    XMP_Node parent(nullptr, "parentNode", 0);

    XML_Node attr(nullptr, "attrName", RDFTermKind);

    attr.ns = "http://example.com";

    attr.value = "attrValue";



    XMP_Node* result = AddQualifierNode(&parent, attr);



    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->name, "attrName");

    EXPECT_EQ(result->value, "attrValue");

    EXPECT_EQ(result->parent, &parent);

}



TEST(AddQualifierNodeTest_2122, EmptyNamespaceThrowsException_2122) {

    XMP_Node parent(nullptr, "parentNode", 0);

    XML_Node attr(nullptr, "attrName", RDFTermKind);

    attr.ns = ""; // Empty namespace

    attr.value = "attrValue";



    EXPECT_THROW(AddQualifierNode(&parent, attr), XMP_Error);

}



TEST(AddQualifierNodeTest_2122, ValidNamespaceAndEmptyValue_2122) {

    XMP_Node parent(nullptr, "parentNode", 0);

    XML_Node attr(nullptr, "attrName", RDFTermKind);

    attr.ns = "http://example.com";

    attr.value = ""; // Empty value



    XMP_Node* result = AddQualifierNode(&parent, attr);



    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->name, "attrName");

    EXPECT_EQ(result->value, "");

    EXPECT_EQ(result->parent, &parent);

}



TEST(AddQualifierNodeTest_2122, ValidNamespaceAndNullValue_2122) {

    XMP_Node parent(nullptr, "parentNode", 0);

    XML_Node attr(nullptr, "attrName", RDFTermKind);

    attr.ns = "http://example.com";

    attr.value = nullptr; // Null value



    XMP_Node* result = AddQualifierNode(&parent, attr);



    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->name, "attrName");

    EXPECT_EQ(result->value, "");

    EXPECT_EQ(result->parent, &parent);

}



TEST(AddQualifierNodeTest_2122, ValidNamespaceAndLongValue_2122) {

    XMP_Node parent(nullptr, "parentNode", 0);

    XML_Node attr(nullptr, "attrName", RDFTermKind);

    attr.ns = "http://example.com";

    attr.value = std::string(1000, 'a'); // Long value



    XMP_Node* result = AddQualifierNode(&parent, attr);



    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->name, "attrName");

    EXPECT_EQ(result->value, attr.value);

    EXPECT_EQ(result->parent, &parent);

}
