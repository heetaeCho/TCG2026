#include <gtest/gtest.h>
#include <cstring>

// Include necessary XMP SDK headers
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"
#include "TXMPMeta.hpp"
#include "TXMPUtils.hpp"
#include "XMPCore_Impl.hpp"
#include "XMPMeta.hpp"
#include "XMPUtils.hpp"

// Declaration of the function under test
extern void WXMPUtils_PackageForJPEG_1(
    XMPMetaRef wxmpObj,
    XMP_StringPtr * stdStr, XMP_StringLen * stdLen,
    XMP_StringPtr * extStr, XMP_StringLen * extLen,
    XMP_StringPtr * digestStr, XMP_StringLen * digestLen,
    WXMP_Result * wResult);

class WXMPUtilsPackageForJPEGTest_1952 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Initialize XMP SDK
        SXMPMeta::Initialize();
    }

    static void TearDownTestSuite() {
        SXMPMeta::Terminate();
    }

    void SetUp() override {
        memset(&wResult, 0, sizeof(wResult));
        wResult.errMessage = nullptr;
    }

    WXMP_Result wResult;
};

// Test with a valid empty XMP object and all output pointers provided
TEST_F(WXMPUtilsPackageForJPEGTest_1952, EmptyXMPObjectAllPointersProvided_1952) {
    SXMPMeta meta;
    XMPMetaRef metaRef = meta.GetInternalRef();

    XMP_StringPtr stdStr = nullptr;
    XMP_StringLen stdLen = 0;
    XMP_StringPtr extStr = nullptr;
    XMP_StringLen extLen = 0;
    XMP_StringPtr digestStr = nullptr;
    XMP_StringLen digestLen = 0;

    WXMPUtils_PackageForJPEG_1(metaRef, &stdStr, &stdLen, &extStr, &extLen, &digestStr, &digestLen, &wResult);

    // Should succeed without error
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test with null stdStr and stdLen pointers (should use void defaults)
TEST_F(WXMPUtilsPackageForJPEGTest_1952, NullStdStrAndStdLen_1952) {
    SXMPMeta meta;
    XMPMetaRef metaRef = meta.GetInternalRef();

    XMP_StringPtr extStr = nullptr;
    XMP_StringLen extLen = 0;
    XMP_StringPtr digestStr = nullptr;
    XMP_StringLen digestLen = 0;

    WXMPUtils_PackageForJPEG_1(metaRef, nullptr, nullptr, &extStr, &extLen, &digestStr, &digestLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test with null extStr and extLen pointers
TEST_F(WXMPUtilsPackageForJPEGTest_1952, NullExtStrAndExtLen_1952) {
    SXMPMeta meta;
    XMPMetaRef metaRef = meta.GetInternalRef();

    XMP_StringPtr stdStr = nullptr;
    XMP_StringLen stdLen = 0;
    XMP_StringPtr digestStr = nullptr;
    XMP_StringLen digestLen = 0;

    WXMPUtils_PackageForJPEG_1(metaRef, &stdStr, &stdLen, nullptr, nullptr, &digestStr, &digestLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test with null digestStr and digestLen pointers
TEST_F(WXMPUtilsPackageForJPEGTest_1952, NullDigestStrAndDigestLen_1952) {
    SXMPMeta meta;
    XMPMetaRef metaRef = meta.GetInternalRef();

    XMP_StringPtr stdStr = nullptr;
    XMP_StringLen stdLen = 0;
    XMP_StringPtr extStr = nullptr;
    XMP_StringLen extLen = 0;

    WXMPUtils_PackageForJPEG_1(metaRef, &stdStr, &stdLen, &extStr, &extLen, nullptr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test with all output pointers null
TEST_F(WXMPUtilsPackageForJPEGTest_1952, AllOutputPointersNull_1952) {
    SXMPMeta meta;
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMPUtils_PackageForJPEG_1(metaRef, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test with XMP object containing some properties
TEST_F(WXMPUtilsPackageForJPEGTest_1952, XMPObjectWithProperties_1952) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "title", "Test Title");
    meta.SetProperty(kXMP_NS_DC, "creator", "Test Creator");
    XMPMetaRef metaRef = meta.GetInternalRef();

    XMP_StringPtr stdStr = nullptr;
    XMP_StringLen stdLen = 0;
    XMP_StringPtr extStr = nullptr;
    XMP_StringLen extLen = 0;
    XMP_StringPtr digestStr = nullptr;
    XMP_StringLen digestLen = 0;

    WXMPUtils_PackageForJPEG_1(metaRef, &stdStr, &stdLen, &extStr, &extLen, &digestStr, &digestLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    // Standard string should contain data for a non-empty XMP object
    EXPECT_NE(stdStr, nullptr);
    EXPECT_GT(stdLen, static_cast<XMP_StringLen>(0));
}

// Test that standard output contains valid XMP for small metadata
TEST_F(WXMPUtilsPackageForJPEGTest_1952, SmallMetadataFitsInStandard_1952) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "subject", "small");
    XMPMetaRef metaRef = meta.GetInternalRef();

    XMP_StringPtr stdStr = nullptr;
    XMP_StringLen stdLen = 0;
    XMP_StringPtr extStr = nullptr;
    XMP_StringLen extLen = 0;
    XMP_StringPtr digestStr = nullptr;
    XMP_StringLen digestLen = 0;

    WXMPUtils_PackageForJPEG_1(metaRef, &stdStr, &stdLen, &extStr, &extLen, &digestStr, &digestLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(stdStr, nullptr);
    EXPECT_GT(stdLen, static_cast<XMP_StringLen>(0));
    // For small metadata, extended portion should be empty
    EXPECT_EQ(extLen, static_cast<XMP_StringLen>(0));
}

// Test with only some null pointer combinations (stdStr null, stdLen provided)
TEST_F(WXMPUtilsPackageForJPEGTest_1952, MixedNullPointers_StdStrNull_1952) {
    SXMPMeta meta;
    XMPMetaRef metaRef = meta.GetInternalRef();

    XMP_StringLen stdLen = 0;
    XMP_StringPtr extStr = nullptr;
    XMP_StringLen extLen = 0;
    XMP_StringPtr digestStr = nullptr;
    XMP_StringLen digestLen = 0;

    WXMPUtils_PackageForJPEG_1(metaRef, nullptr, &stdLen, &extStr, &extLen, &digestStr, &digestLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test with only stdLen null
TEST_F(WXMPUtilsPackageForJPEGTest_1952, MixedNullPointers_StdLenNull_1952) {
    SXMPMeta meta;
    XMPMetaRef metaRef = meta.GetInternalRef();

    XMP_StringPtr stdStr = nullptr;
    XMP_StringPtr extStr = nullptr;
    XMP_StringLen extLen = 0;
    XMP_StringPtr digestStr = nullptr;
    XMP_StringLen digestLen = 0;

    WXMPUtils_PackageForJPEG_1(metaRef, &stdStr, nullptr, &extStr, &extLen, &digestStr, &digestLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test that calling twice on the same object produces consistent results
TEST_F(WXMPUtilsPackageForJPEGTest_1952, ConsistentResults_1952) {
    SXMPMeta meta;
    meta.SetProperty(kXMP_NS_DC, "description", "Consistency test");
    XMPMetaRef metaRef = meta.GetInternalRef();

    XMP_StringPtr stdStr1 = nullptr;
    XMP_StringLen stdLen1 = 0;
    XMP_StringPtr extStr1 = nullptr;
    XMP_StringLen extLen1 = 0;
    XMP_StringPtr digestStr1 = nullptr;
    XMP_StringLen digestLen1 = 0;

    WXMP_Result wResult1;
    memset(&wResult1, 0, sizeof(wResult1));
    WXMPUtils_PackageForJPEG_1(metaRef, &stdStr1, &stdLen1, &extStr1, &extLen1, &digestStr1, &digestLen1, &wResult1);
    EXPECT_EQ(wResult1.errMessage, nullptr);

    XMP_StringPtr stdStr2 = nullptr;
    XMP_StringLen stdLen2 = 0;
    XMP_StringPtr extStr2 = nullptr;
    XMP_StringLen extLen2 = 0;
    XMP_StringPtr digestStr2 = nullptr;
    XMP_StringLen digestLen2 = 0;

    WXMP_Result wResult2;
    memset(&wResult2, 0, sizeof(wResult2));
    WXMPUtils_PackageForJPEG_1(metaRef, &stdStr2, &stdLen2, &extStr2, &extLen2, &digestStr2, &digestLen2, &wResult2);
    EXPECT_EQ(wResult2.errMessage, nullptr);

    EXPECT_EQ(stdLen1, stdLen2);
    EXPECT_EQ(extLen1, extLen2);
    EXPECT_EQ(digestLen1, digestLen2);
}

// Test with a large amount of XMP data to potentially trigger extended portion
TEST_F(WXMPUtilsPackageForJPEGTest_1952, LargeXMPDataMayUseExtended_1952) {
    SXMPMeta meta;
    // Add many properties to potentially exceed standard JPEG XMP limit
    for (int i = 0; i < 500; ++i) {
        std::string propName = "prop" + std::to_string(i);
        std::string value(200, 'A' + (i % 26));
        meta.SetProperty(kXMP_NS_DC, propName.c_str(), value.c_str());
    }
    XMPMetaRef metaRef = meta.GetInternalRef();

    XMP_StringPtr stdStr = nullptr;
    XMP_StringLen stdLen = 0;
    XMP_StringPtr extStr = nullptr;
    XMP_StringLen extLen = 0;
    XMP_StringPtr digestStr = nullptr;
    XMP_StringLen digestLen = 0;

    WXMPUtils_PackageForJPEG_1(metaRef, &stdStr, &stdLen, &extStr, &extLen, &digestStr, &digestLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(stdStr, nullptr);
    EXPECT_GT(stdLen, static_cast<XMP_StringLen>(0));
}

// Test WXMP_Result is properly initialized and remains clean on success
TEST_F(WXMPUtilsPackageForJPEGTest_1952, ResultStructCleanOnSuccess_1952) {
    SXMPMeta meta;
    XMPMetaRef metaRef = meta.GetInternalRef();

    XMP_StringPtr stdStr = nullptr;
    XMP_StringLen stdLen = 0;
    XMP_StringPtr extStr = nullptr;
    XMP_StringLen extLen = 0;
    XMP_StringPtr digestStr = nullptr;
    XMP_StringLen digestLen = 0;

    WXMP_Result result;
    result.errMessage = nullptr;
    result.int32Result = 0;
    result.int64Result = 0;

    WXMPUtils_PackageForJPEG_1(metaRef, &stdStr, &stdLen, &extStr, &extLen, &digestStr, &digestLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
}
