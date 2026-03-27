#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPCore_Impl.hpp"

#include "XMPMeta.hpp"

#include "XMPIterator.hpp"



using namespace ::testing;



class AddSchemaAliasesTest : public Test {

protected:

    IterInfo info;

    IterNode iterSchema;

    XMP_StringPtr schemaURI;



    void SetUp() override {

        // Initialize necessary objects and data

        info.xmpObj = new XMPMeta();

        sRegisteredAliasMap = new XMP_AliasMap();

    }



    void TearDown() override {

        delete info.xmpObj;

        delete sRegisteredAliasMap;

    }

};



TEST_F(AddSchemaAliasesTest_NormalOperation_2098, AddsAliasesForKnownNamespace_2098) {

    // Arrange

    schemaURI = "http://example.com/schema";

    XMPMeta::RegisterNamespace(schemaURI, "ex");



    sRegisteredAliasMap->insert(std::make_pair("ex:alias", "ex:actual"));

    

    XMP_StringPtr nsPrefix;

    XMP_StringLen nsLen;

    XMPMeta::GetNamespacePrefix(schemaURI, &nsPrefix, &nsLen);



    const XMP_Node actualProp(&info.xmpObj->tree, "ex:actual", kXMP_PropIsAlias);

    info.xmpObj->tree.children.push_back(actualProp);



    // Act

    AddSchemaAliases(info, iterSchema, schemaURI);



    // Assert

    EXPECT_EQ(iterSchema.children.size(), 1u);

    EXPECT_EQ(iterSchema.children[0].fullPath, "ex:alias");

    EXPECT_EQ(iterSchema.children[0].options & kXMP_PropIsAlias, kXMP_PropIsAlias);

}



TEST_F(AddSchemaAliasesTest_BoundaryConditions_2098, NoAliasesRegisteredForNamespace_2098) {

    // Arrange

    schemaURI = "http://example.com/schema";

    XMPMeta::RegisterNamespace(schemaURI, "ex");



    XMP_StringPtr nsPrefix;

    XMP_StringLen nsLen;

    XMPMeta::GetNamespacePrefix(schemaURI, &nsPrefix, &nsLen);



    // Act

    AddSchemaAliases(info, iterSchema, schemaURI);



    // Assert

    EXPECT_EQ(iterSchema.children.size(), 0u);

}



TEST_F(AddSchemaAliasesTest_ExceptionalCases_2098, ThrowsForUnknownNamespace_2098) {

    // Arrange

    schemaURI = "http://unknown.com/schema";



    // Act & Assert

    EXPECT_THROW(AddSchemaAliases(info, iterSchema, schemaURI), XMP_Error);

}



TEST_F(AddSchemaAliasesTest_VerificationOfExternalInteractions_2098, CallsGetNamespacePrefixCorrectly_2098) {

    // Arrange

    schemaURI = "http://example.com/schema";

    XMPMeta::RegisterNamespace(schemaURI, "ex");



    EXPECT_CALL(*MockXMPMeta(), GetNamespacePrefix(Eq(schemaURI), _, _))

        .WillOnce(Return(true));



    // Act

    AddSchemaAliases(info, iterSchema, schemaURI);



    // Assert is handled by the mock call expectation

}

```


