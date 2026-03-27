#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the necessary headers are included for XMP_StringPtr, XMP_ExpandedXPath, etc.

extern void VerifyXPathRoot(XMP_StringPtr schemaURI, XMP_StringPtr propName, XMP_ExpandedXPath* expandedXPath);



class XMPCoreTest_1884 : public ::testing::Test {

protected:

    XMP_ExpandedXPath expandedXPath;



    virtual void SetUp() override {

        // Ensure the expandedXPath is empty before each test

        expandedXPath.clear();

    }

};



TEST_F(XMPCoreTest_1884, NormalOperationWithPrefix_1884) {

    const char* schemaURI = "http://example.com/schema";

    const char* propName = "prefix:name";



    // Assuming sNamespaceURIToPrefixMap and sNamespacePrefixToURIMap are properly set up

    sNamespaceURIToPrefixMap->insert_or_assign(schemaURI, "prefix");

    sNamespacePrefixToURIMap->insert_or_assign("prefix", schemaURI);



    EXPECT_NO_THROW(VerifyXPathRoot(schemaURI, propName, &expandedXPath));

    ASSERT_EQ(expandedXPath.size(), 2);

    EXPECT_EQ(expandedXPath[kSchemaStep].step, schemaURI);

    EXPECT_EQ(expandedXPath[kRootPropStep].step, "prefix:name");

}



TEST_F(XMPCoreTest_1884, NormalOperationWithoutPrefix_1884) {

    const char* schemaURI = "http://example.com/schema";

    const char* propName = "name";



    sNamespaceURIToPrefixMap->insert_or_assign(schemaURI, "prefix");



    EXPECT_NO_THROW(VerifyXPathRoot(schemaURI, propName, &expandedXPath));

    ASSERT_EQ(expandedXPath.size(), 2);

    EXPECT_EQ(expandedXPath[kSchemaStep].step, schemaURI);

    EXPECT_EQ(expandedXPath[kRootPropStep].step, "name");

}



TEST_F(XMPCoreTest_1884, SchemaURINotProvided_1884) {

    const char* schemaURI = "";

    const char* propName = "name";



    EXPECT_THROW(VerifyXPathRoot(schemaURI, propName, &expandedXPath), XMP_Error);

}



TEST_F(XMPCoreTest_1884, PropNameNotProvided_1884) {

    const char* schemaURI = "http://example.com/schema";

    const char* propName = "";



    EXPECT_THROW(VerifyXPathRoot(schemaURI, propName, &expandedXPath), XMP_Error);

}



TEST_F(XMPCoreTest_1884, PropNameWithQualifier_1884) {

    const char* schemaURI = "http://example.com/schema";

    const char* propName = "?name";



    EXPECT_THROW(VerifyXPathRoot(schemaURI, propName, &expandedXPath), XMP_Error);

}



TEST_F(XMPCoreTest_1884, PropNameWithSimpleXMLCharacters_1884) {

    const char* schemaURI = "http://example.com/schema";

    const char* propName = "name/";



    EXPECT_THROW(VerifyXPathRoot(schemaURI, propName, &expandedXPath), XMP_Error);

}



TEST_F(XMPCoreTest_1884, UnregisteredSchemaURI_1884) {

    const char* schemaURI = "http://unregistered.com/schema";

    const char* propName = "name";



    EXPECT_THROW(VerifyXPathRoot(schemaURI, propName, &expandedXPath), XMP_Error);

}



TEST_F(XMPCoreTest_1884, UnknownSchemaPrefix_1884) {

    const char* schemaURI = "http://example.com/schema";

    const char* propName = "unknown:name";



    sNamespaceURIToPrefixMap->insert_or_assign(schemaURI, "prefix");



    EXPECT_THROW(VerifyXPathRoot(schemaURI, propName, &expandedXPath), XMP_Error);

}



TEST_F(XMPCoreTest_1884, SchemaPrefixMismatch_1884) {

    const char* schemaURI = "http://example.com/schema";

    const char* propName = "prefix:name";



    sNamespaceURIToPrefixMap->insert_or_assign(schemaURI, "prefix");

    sNamespacePrefixToURIMap->insert_or_assign("prefix", "http://mismatched.com/schema");



    EXPECT_THROW(VerifyXPathRoot(schemaURI, propName, &expandedXPath), XMP_Error);

}
