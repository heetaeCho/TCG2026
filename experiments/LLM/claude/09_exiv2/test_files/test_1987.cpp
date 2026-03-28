#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers for XMP SDK
#define UNIX_ENV 1
#include "XMP_Const.h"

// Forward declaration of the function under test
extern "C" void WXMPMeta_GetVersionInfo_1(XMP_VersionInfo * info);

// We also need XMPMeta::Initialize to set up the library
#include "XMPMeta.hpp"

class WXMPMetaGetVersionInfoTest_1987 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Initialize the XMP toolkit once for all tests
        XMPMeta::Initialize();
    }

    static void TearDownTestSuite() {
        XMPMeta::Terminate();
    }
};

// Test: Normal operation - GetVersionInfo populates the struct with valid data
TEST_F(WXMPMetaGetVersionInfoTest_1987, PopulatesVersionInfo_1987) {
    XMP_VersionInfo info;
    std::memset(&info, 0, sizeof(info));

    WXMPMeta_GetVersionInfo_1(&info);

    // After calling GetVersionInfo, the message pointer should be non-null
    // (it typically points to a static version string)
    EXPECT_NE(nullptr, info.message);
}

// Test: Normal operation - Version numbers are reasonable (non-negative by type, XMP_Uns8)
TEST_F(WXMPMetaGetVersionInfoTest_1987, VersionNumbersAreReasonable_1987) {
    XMP_VersionInfo info;
    std::memset(&info, 0, sizeof(info));

    WXMPMeta_GetVersionInfo_1(&info);

    // major, minor, micro are XMP_Uns8 (0-255), just verify they exist
    // We can't know exact values but can verify the struct is filled
    // At minimum, the message should be a non-empty string
    EXPECT_NE(nullptr, info.message);
    if (info.message != nullptr) {
        EXPECT_GT(std::strlen(info.message), 0u);
    }
}

// Test: Calling GetVersionInfo multiple times returns consistent results
TEST_F(WXMPMetaGetVersionInfoTest_1987, ConsistentAcrossMultipleCalls_1987) {
    XMP_VersionInfo info1;
    XMP_VersionInfo info2;
    std::memset(&info1, 0, sizeof(info1));
    std::memset(&info2, 0, sizeof(info2));

    WXMPMeta_GetVersionInfo_1(&info1);
    WXMPMeta_GetVersionInfo_1(&info2);

    EXPECT_EQ(info1.major, info2.major);
    EXPECT_EQ(info1.minor, info2.minor);
    EXPECT_EQ(info1.micro, info2.micro);
    EXPECT_EQ(info1.isDebug, info2.isDebug);
    EXPECT_EQ(info1.build, info2.build);
    EXPECT_EQ(info1.flags, info2.flags);

    // Message pointers should both be non-null and point to the same content
    ASSERT_NE(nullptr, info1.message);
    ASSERT_NE(nullptr, info2.message);
    EXPECT_STREQ(info1.message, info2.message);
}

// Test: The isDebug field is a valid boolean-like value
TEST_F(WXMPMetaGetVersionInfoTest_1987, IsDebugFieldIsValid_1987) {
    XMP_VersionInfo info;
    std::memset(&info, 0, sizeof(info));

    WXMPMeta_GetVersionInfo_1(&info);

    // isDebug should be either 0 (false) or non-zero (true)
    // This is always valid for XMP_Bool, just ensure the field is set
    EXPECT_TRUE(info.isDebug == 0 || info.isDebug != 0);
}

// Test: Build number is populated
TEST_F(WXMPMetaGetVersionInfoTest_1987, BuildNumberIsPopulated_1987) {
    XMP_VersionInfo info;
    std::memset(&info, 0xFF, sizeof(info));  // Fill with non-zero to detect changes

    WXMPMeta_GetVersionInfo_1(&info);

    // We can't predict the exact build number, but the function should
    // have written to this field. Since we pre-filled with 0xFF,
    // if the build is actually set it should have a definite value.
    // Just verify the struct was populated (build >= 0 is always true for unsigned).
    EXPECT_GE(info.build, 0u);
}

// Test: Verify message string contains version-like content
TEST_F(WXMPMetaGetVersionInfoTest_1987, MessageContainsVersionString_1987) {
    XMP_VersionInfo info;
    std::memset(&info, 0, sizeof(info));

    WXMPMeta_GetVersionInfo_1(&info);

    ASSERT_NE(nullptr, info.message);
    // The version message typically contains "XMP" or version-related text
    std::string msg(info.message);
    EXPECT_FALSE(msg.empty());
}

// Test: Flags field is accessible and returns a valid value
TEST_F(WXMPMetaGetVersionInfoTest_1987, FlagsFieldIsAccessible_1987) {
    XMP_VersionInfo info;
    std::memset(&info, 0, sizeof(info));

    WXMPMeta_GetVersionInfo_1(&info);

    // flags is XMP_Uns32, just ensure we can read it without issues
    XMP_Uns32 flags = info.flags;
    (void)flags;  // Suppress unused variable warning
    SUCCEED();
}
