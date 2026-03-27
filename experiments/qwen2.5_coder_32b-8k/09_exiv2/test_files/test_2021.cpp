#include <gtest/gtest.h>

#include "WXMPMeta.cpp"



TEST(WXMPMeta_DoesStructFieldExist_2021, NormalOperation_StructFieldExists_2021) {

    XMPMetaRef xmpRef = nullptr; // Assume this is properly initialized in actual use

    WXMP_Result wResult;

    

    const char* schemaNS = "http://example.com/schema";

    const char* structName = "ExampleStruct";

    const char* fieldNS = "http://example.com/field";

    const char* fieldName = "exampleField";



    // Assuming the XMPMeta object has been set up such that the struct field exists

    WXMPMeta_DoesStructFieldExist_1(xmpRef, schemaNS, structName, fieldNS, fieldName, &wResult);

    

    EXPECT_EQ(wResult.int32Result, 1); // True if field exists

}



TEST(WXMPMeta_DoesStructFieldExist_2021, NormalOperation_StructFieldDoesNotExist_2021) {

    XMPMetaRef xmpRef = nullptr; // Assume this is properly initialized in actual use

    WXMP_Result wResult;

    

    const char* schemaNS = "http://example.com/schema";

    const char* structName = "ExampleStruct";

    const char* fieldNS = "http://example.com/field";

    const char* fieldName = "nonExistentField";



    // Assuming the XMPMeta object has been set up such that the struct field does not exist

    WXMPMeta_DoesStructFieldExist_1(xmpRef, schemaNS, structName, fieldNS, fieldName, &wResult);

    

    EXPECT_EQ(wResult.int32Result, 0); // False if field does not exist

}



TEST(WXMPMeta_DoesStructFieldExist_2021, BoundaryCondition_EmptySchemaNamespaceURI_2021) {

    XMPMetaRef xmpRef = nullptr; // Assume this is properly initialized in actual use

    WXMP_Result wResult;

    

    const char* schemaNS = "";

    const char* structName = "ExampleStruct";

    const char* fieldNS = "http://example.com/field";

    const char* fieldName = "exampleField";



    EXPECT_THROW(WXMPMeta_DoesStructFieldExist_1(xmpRef, schemaNS, structName, fieldNS, fieldName, &wResult), XMP_Error);

}



TEST(WXMPMeta_DoesStructFieldExist_2021, BoundaryCondition_NullSchemaNamespaceURI_2021) {

    XMPMetaRef xmpRef = nullptr; // Assume this is properly initialized in actual use

    WXMP_Result wResult;

    

    const char* schemaNS = nullptr;

    const char* structName = "ExampleStruct";

    const char* fieldNS = "http://example.com/field";

    const char* fieldName = "exampleField";



    EXPECT_THROW(WXMPMeta_DoesStructFieldExist_1(xmpRef, schemaNS, structName, fieldNS, fieldName, &wResult), XMP_Error);

}



TEST(WXMPMeta_DoesStructFieldExist_2021, BoundaryCondition_EmptyStructName_2021) {

    XMPMetaRef xmpRef = nullptr; // Assume this is properly initialized in actual use

    WXMP_Result wResult;

    

    const char* schemaNS = "http://example.com/schema";

    const char* structName = "";

    const char* fieldNS = "http://example.com/field";

    const char* fieldName = "exampleField";



    EXPECT_THROW(WXMPMeta_DoesStructFieldExist_1(xmpRef, schemaNS, structName, fieldNS, fieldName, &wResult), XMP_Error);

}



TEST(WXMPMeta_DoesStructFieldExist_2021, BoundaryCondition_NullStructName_2021) {

    XMPMetaRef xmpRef = nullptr; // Assume this is properly initialized in actual use

    WXMP_Result wResult;

    

    const char* schemaNS = "http://example.com/schema";

    const char* structName = nullptr;

    const char* fieldNS = "http://example.com/field";

    const char* fieldName = "exampleField";



    EXPECT_THROW(WXMPMeta_DoesStructFieldExist_1(xmpRef, schemaNS, structName, fieldNS, fieldName, &wResult), XMP_Error);

}



TEST(WXMPMeta_DoesStructFieldExist_2021, BoundaryCondition_EmptyFieldNamespaceURI_2021) {

    XMPMetaRef xmpRef = nullptr; // Assume this is properly initialized in actual use

    WXMP_Result wResult;

    

    const char* schemaNS = "http://example.com/schema";

    const char* structName = "ExampleStruct";

    const char* fieldNS = "";

    const char* fieldName = "exampleField";



    EXPECT_THROW(WXMPMeta_DoesStructFieldExist_1(xmpRef, schemaNS, structName, fieldNS, fieldName, &wResult), XMP_Error);

}



TEST(WXMPMeta_DoesStructFieldExist_2021, BoundaryCondition_NullFieldNamespaceURI_2021) {

    XMPMetaRef xmpRef = nullptr; // Assume this is properly initialized in actual use

    WXMP_Result wResult;

    

    const char* schemaNS = "http://example.com/schema";

    const char* structName = "ExampleStruct";

    const char* fieldNS = nullptr;

    const char* fieldName = "exampleField";



    EXPECT_THROW(WXMPMeta_DoesStructFieldExist_1(xmpRef, schemaNS, structName, fieldNS, fieldName, &wResult), XMP_Error);

}



TEST(WXMPMeta_DoesStructFieldExist_2021, BoundaryCondition_EmptyFieldName_2021) {

    XMPMetaRef xmpRef = nullptr; // Assume this is properly initialized in actual use

    WXMP_Result wResult;

    

    const char* schemaNS = "http://example.com/schema";

    const char* structName = "ExampleStruct";

    const char* fieldNS = "http://example.com/field";

    const char* fieldName = "";



    EXPECT_THROW(WXMPMeta_DoesStructFieldExist_1(xmpRef, schemaNS, structName, fieldNS, fieldName, &wResult), XMP_Error);

}



TEST(WXMPMeta_DoesStructFieldExist_2021, BoundaryCondition_NullFieldName_2021) {

    XMPMetaRef xmpRef = nullptr; // Assume this is properly initialized in actual use

    WXMP_Result wResult;

    

    const char* schemaNS = "http://example.com/schema";

    const char* structName = "ExampleStruct";

    const char* fieldNS = "http://example.com/field";

    const char* fieldName = nullptr;



    EXPECT_THROW(WXMPMeta_DoesStructFieldExist_1(xmpRef, schemaNS, structName, fieldNS, fieldName, &wResult), XMP_Error);

}
