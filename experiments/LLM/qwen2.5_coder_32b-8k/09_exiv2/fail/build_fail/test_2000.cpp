#include <gtest/gtest.h>

#include "WXMP_Common.hpp"

#include "XMP_Const.h"



TEST(WXMPMeta_GetNamespaceURI_1_Test_2000, NormalOperation_2000) {

    XMP_StringPtr namespacePrefix = "testPrefix";

    XMP_StringPtr namespaceURI;

    XMP_StringLen uriSize;

    WXMP_Result wResult;



    WXMPMeta_GetNamespaceURI_1(namespacePrefix, &namespaceURI, &uriSize, &wResult);



    EXPECT_EQ(wResult.int32Result, 0); // Assuming the prefix is not registered, it should return false

}



TEST(WXMPMeta_GetNamespaceURI_1_Test_2000, EmptyNamespacePrefix_2000) {

    XMP_StringPtr namespacePrefix = "";

    XMP_StringPtr namespaceURI;

    XMP_StringLen uriSize;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_GetNamespaceURI_1(namespacePrefix, &namespaceURI, &uriSize, &wResult), std::exception);

}



TEST(WXMPMeta_GetNamespaceURI_1_Test_2000, NullNamespacePrefix_2000) {

    XMP_StringPtr namespacePrefix = nullptr;

    XMP_StringPtr namespaceURI;

    XMP_StringLen uriSize;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_GetNamespaceURI_1(namespacePrefix, &namespaceURI, &uriSize, &wResult), std::exception);

}



TEST(WXMPMeta_GetNamespaceURI_1_Test_2000, NullNamespaceURIPointer_2000) {

    XMP_StringPtr namespacePrefix = "testPrefix";

    XMP_StringPtr *namespaceURI = nullptr;

    XMP_StringLen uriSize;

    WXMP_Result wResult;



    WXMPMeta_GetNamespaceURI_1(namespacePrefix, namespaceURI, &uriSize, &wResult);



    EXPECT_EQ(wResult.int32Result, 0); // Assuming the prefix is not registered, it should return false

}



TEST(WXMPMeta_GetNamespaceURI_1_Test_2000, NullUriSizePointer_2000) {

    XMP_StringPtr namespacePrefix = "testPrefix";

    XMP_StringPtr namespaceURI;

    XMP_StringLen *uriSize = nullptr;

    WXMP_Result wResult;



    WXMPMeta_GetNamespaceURI_1(namespacePrefix, &namespaceURI, uriSize, &wResult);



    EXPECT_EQ(wResult.int32Result, 0); // Assuming the prefix is not registered, it should return false

}



TEST(WXMPMeta_GetNamespaceURI_1_Test_2000, NullWXMP_ResultPointer_2000) {

    XMP_StringPtr namespacePrefix = "testPrefix";

    XMP_StringPtr namespaceURI;

    XMP_StringLen uriSize;

    WXMP_Result *wResult = nullptr;



    EXPECT_NO_THROW(WXMPMeta_GetNamespaceURI_1(namespacePrefix, &namespaceURI, &uriSize, wResult));

}
