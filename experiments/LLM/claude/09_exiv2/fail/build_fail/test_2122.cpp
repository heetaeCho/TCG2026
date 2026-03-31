#include <gtest/gtest.h>
#include <string>
#include <stdexcept>

// Include necessary headers
#include "XMPCore_Impl.hpp"
#include "XMLParserAdapter.hpp"

// We need access to AddQualifierNode - it's a static function in ParseRDF.cpp
// For testing purposes, we may need to declare it or include the relevant header
// Since it's file-static, we might need to include the source or use a test helper

// Forward declaration if available through headers
extern XMP_Node * AddQualifierNode(XMP_Node * xmpParent, const XML_Node & attr);
extern XMP_Node * AddQualifierNode(XMP_Node * xmpParent, const XMP_VarString & name, const XMP_VarString & value);

class AddQualifierNodeTest_2122 : public ::testing::Test {
protected:
    void SetUp() override {
        xmpParent = new XMP_Node(nullptr, "testParent", 0);
    }

    void TearDown() override {
        delete xmpParent;
    }

    XMP_Node* xmpParent;
};

// Test that an exception is thrown when the XML_Node has an empty namespace
TEST_F(AddQualifierNodeTest_2122, ThrowsWhenNamespaceIsEmpty_2122) {
    XML_Node attr(nullptr, "attrName", 0);
    // ns is empty by default
    attr.name = "test:attr";
    attr.value = "someValue";
    // attr.ns is empty string by default

    EXPECT_THROW({
        AddQualifierNode(xmpParent, attr);
    }, XMP_Error);
}

// Test that the exception message/code is kXMPErr_BadRDF when namespace is empty
TEST_F(AddQualifierNodeTest_2122, ThrowsBadRDFWhenNamespaceIsEmpty_2122) {
    XML_Node attr(nullptr, "attrName", 0);
    attr.ns = "";
    attr.name = "test:attr";
    attr.value = "someValue";

    try {
        AddQualifierNode(xmpParent, attr);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadRDF);
    } catch (...) {
        FAIL() << "Expected XMP_Error but caught different exception";
    }
}

// Test that no exception is thrown when namespace is non-empty
TEST_F(AddQualifierNodeTest_2122, NoThrowWhenNamespaceIsNonEmpty_2122) {
    XML_Node attr(nullptr, "attrName", 0);
    attr.ns = "http://example.com/ns/";
    attr.name = "ex:qualifier";
    attr.value = "qualValue";

    EXPECT_NO_THROW({
        XMP_Node* result = AddQualifierNode(xmpParent, attr);
        // Result should be a valid node if the internal overload succeeds
        EXPECT_NE(result, nullptr);
    });
}

// Test that the returned qualifier node has the correct name from the attr
TEST_F(AddQualifierNodeTest_2122, ReturnsNodeWithCorrectName_2122) {
    XML_Node attr(nullptr, "attrName", 0);
    attr.ns = "http://example.com/ns/";
    attr.name = "ex:myQualifier";
    attr.value = "myValue";

    XMP_Node* result = AddQualifierNode(xmpParent, attr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->name, "ex:myQualifier");
}

// Test that the returned qualifier node has the correct value from the attr
TEST_F(AddQualifierNodeTest_2122, ReturnsNodeWithCorrectValue_2122) {
    XML_Node attr(nullptr, "attrName", 0);
    attr.ns = "http://example.com/ns/";
    attr.name = "ex:myQualifier";
    attr.value = "expectedValue";

    XMP_Node* result = AddQualifierNode(xmpParent, attr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value, "expectedValue");
}

// Test with an empty name but non-empty namespace
TEST_F(AddQualifierNodeTest_2122, EmptyNameWithNonEmptyNamespace_2122) {
    XML_Node attr(nullptr, "", 0);
    attr.ns = "http://example.com/ns/";
    attr.name = "";
    attr.value = "someValue";

    // Should not throw due to namespace check, but behavior depends on inner overload
    EXPECT_NO_THROW({
        AddQualifierNode(xmpParent, attr);
    });
}

// Test with empty value but non-empty namespace and name
TEST_F(AddQualifierNodeTest_2122, EmptyValueWithValidNameAndNamespace_2122) {
    XML_Node attr(nullptr, "attrName", 0);
    attr.ns = "http://example.com/ns/";
    attr.name = "ex:qualifier";
    attr.value = "";

    XMP_Node* result = AddQualifierNode(xmpParent, attr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value, "");
}

// Test that qualifier is added to parent's qualifiers list
TEST_F(AddQualifierNodeTest_2122, QualifierAddedToParent_2122) {
    XML_Node attr(nullptr, "attrName", 0);
    attr.ns = "http://example.com/ns/";
    attr.name = "ex:qualifier";
    attr.value = "qualValue";

    size_t initialQualCount = xmpParent->qualifiers.size();
    AddQualifierNode(xmpParent, attr);
    EXPECT_GT(xmpParent->qualifiers.size(), initialQualCount);
}
