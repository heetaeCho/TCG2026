#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMP_Const.h"

#include "client-glue/WXMP_Common.hpp"

#include "XMPUtils.hpp"



class WXMPUtilsTest_1958 : public ::testing::Test {

protected:

    XMPMetaRef wSource = nullptr;

    XMPMetaRef wDest = nullptr;

    WXMP_Result result;



    void SetUp() override {

        // Initialize the source and destination XMPMetaRef objects

        wSource = new XMPMeta();

        wDest = new XMPMeta();

    }



    void TearDown() override {

        // Clean up the allocated XMPMetaRef objects

        delete WtoXMPMeta_Ptr(wSource);

        delete WtoXMPMeta_Ptr(wDest);

        wSource = nullptr;

        wDest = nullptr;

    }

};



TEST_F(WXMPUtilsTest_1958, DuplicateSubtree_NormalOperation_1958) {

    const XMP_StringPtr sourceNS = "http://example.com/ns";

    const XMP_StringPtr sourceRoot = "rootElement";

    const XMP_StringPtr destNS = "http://example.com/ns";

    const XMP_StringPtr destRoot = "rootElementCopy";

    XMP_OptionBits options = 0;



    WXMPUtils_DuplicateSubtree_1(wSource, wDest, sourceNS, sourceRoot, destNS, destRoot, options, &result);



    EXPECT_STREQ(result.errMessage, nullptr);

}



TEST_F(WXMPUtilsTest_1958, DuplicateSubtree_NullDestination_1958) {

    const XMP_StringPtr sourceNS = "http://example.com/ns";

    const XMP_StringPtr sourceRoot = "rootElement";

    const XMP_StringPtr destNS = "http://example.com/ns";

    const XMP_StringPtr destRoot = "rootElementCopy";

    XMP_OptionBits options = 0;



    WXMPUtils_DuplicateSubtree_1(wSource, nullptr, sourceNS, sourceRoot, destNS, destRoot, options, &result);



    EXPECT_STREQ(result.errMessage, "Output XMP pointer is null");

}



TEST_F(WXMPUtilsTest_1958, DuplicateSubtree_EmptySourceNamespace_1958) {

    const XMP_StringPtr sourceNS = "";

    const XMP_StringPtr sourceRoot = "rootElement";

    const XMP_StringPtr destNS = "http://example.com/ns";

    const XMP_StringPtr destRoot = "rootElementCopy";

    XMP_OptionBits options = 0;



    WXMPUtils_DuplicateSubtree_1(wSource, wDest, sourceNS, sourceRoot, destNS, destRoot, options, &result);



    EXPECT_STREQ(result.errMessage, "Empty source schema URI");

}



TEST_F(WXMPUtilsTest_1958, DuplicateSubtree_EmptySourceRoot_1958) {

    const XMP_StringPtr sourceNS = "http://example.com/ns";

    const XMP_StringPtr sourceRoot = "";

    const XMP_StringPtr destNS = "http://example.com/ns";

    const XMP_StringPtr destRoot = "rootElementCopy";

    XMP_OptionBits options = 0;



    WXMPUtils_DuplicateSubtree_1(wSource, wDest, sourceNS, sourceRoot, destNS, destRoot, options, &result);



    EXPECT_STREQ(result.errMessage, "Empty source root name");

}



TEST_F(WXMPUtilsTest_1958, DuplicateSubtree_DefaultDestinationNamespaceAndRoot_1958) {

    const XMP_StringPtr sourceNS = "http://example.com/ns";

    const XMP_StringPtr sourceRoot = "rootElement";

    XMP_OptionBits options = 0;



    WXMPUtils_DuplicateSubtree_1(wSource, wDest, sourceNS, sourceRoot, nullptr, nullptr, options, &result);



    EXPECT_STREQ(result.errMessage, nullptr);

}
