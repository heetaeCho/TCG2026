#include <gtest/gtest.h>

#include "WXMP_Common.hpp"

#include "XMP_Const.h"



// Define a TEST_ID macro for consistency

#define TEST_ID 1999



TEST(WXMPMeta_GetNamespacePrefix_Test_1999, NormalOperation_Found_1999) {

    XMP_StringPtr namespaceURI = "http://example.com/schema";

    XMP_StringPtr namespacePrefix = nullptr;

    XMP_StringLen prefixSize = 0;

    WXMP_Result wResult;



    WXMPMeta_GetNamespacePrefix_1(namespaceURI, &namespacePrefix, &prefixSize, &wResult);



    EXPECT_EQ(wResult.int32Result, 1);

    EXPECT_NE(namespacePrefix, nullptr);

    EXPECT_GT(prefixSize, 0);

}



TEST(WXMPMeta_GetNamespacePrefix_Test_1999, NormalOperation_NotFound_1999) {

    XMP_StringPtr namespaceURI = "http://nonexistent.com/schema";

    XMP_StringPtr namespacePrefix = nullptr;

    XMP_StringLen prefixSize = 0;

    WXMP_Result wResult;



    WXMPMeta_GetNamespacePrefix_1(namespaceURI, &namespacePrefix, &prefixSize, &wResult);



    EXPECT_EQ(wResult.int32Result, 0);

    EXPECT_EQ(namespacePrefix, nullptr);

    EXPECT_EQ(prefixSize, 0);

}



TEST(WXMPMeta_GetNamespacePrefix_Test_1999, NullNamespaceURIFailure_1999) {

    XMP_StringPtr namespaceURI = nullptr;

    XMP_StringPtr namespacePrefix = nullptr;

    XMP_StringLen prefixSize = 0;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_GetNamespacePrefix_1(namespaceURI, &namespacePrefix, &prefixSize, &wResult), std::exception);

}



TEST(WXMPMeta_GetNamespacePrefix_Test_1999, EmptyNamespaceURIFailure_1999) {

    XMP_StringPtr namespaceURI = "";

    XMP_StringPtr namespacePrefix = nullptr;

    XMP_StringLen prefixSize = 0;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_GetNamespacePrefix_1(namespaceURI, &namespacePrefix, &prefixSize, &wResult), std::exception);

}



TEST(WXMPMeta_GetNamespacePrefix_Test_1999, NullNamespacePrefixPointer_1999) {

    XMP_StringPtr namespaceURI = "http://example.com/schema";

    XMP_StringPtr namespacePrefix = nullptr;

    XMP_StringLen prefixSize = 0;

    WXMP_Result wResult;



    WXMPMeta_GetNamespacePrefix_1(namespaceURI, nullptr, &prefixSize, &wResult);



    EXPECT_EQ(wResult.int32Result, 1);

    EXPECT_NE(prefixSize, 0);

}



TEST(WXMPMeta_GetNamespacePrefix_Test_1999, NullPrefixSizePointer_1999) {

    XMP_StringPtr namespaceURI = "http://example.com/schema";

    XMP_StringPtr namespacePrefix = nullptr;

    XMP_StringLen prefixSize = 0;

    WXMP_Result wResult;



    WXMPMeta_GetNamespacePrefix_1(namespaceURI, &namespacePrefix, nullptr, &wResult);



    EXPECT_EQ(wResult.int32Result, 1);

    EXPECT_NE(namespacePrefix, nullptr);

}



TEST(WXMPMeta_GetNamespacePrefix_Test_1999, NullWResultPointer_1999) {

    XMP_StringPtr namespaceURI = "http://example.com/schema";

    XMP_StringPtr namespacePrefix = nullptr;

    XMP_StringLen prefixSize = 0;



    WXMPMeta_GetNamespacePrefix_1(namespaceURI, &namespacePrefix, &prefixSize, nullptr);



    EXPECT_NE(namespacePrefix, nullptr);

    EXPECT_GT(prefixSize, 0);

}
