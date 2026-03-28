#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMP_Const.h"
#include "WXMP_Common.hpp"
#include "WXMPMeta.hpp"

// Mock function for the XMP_TextOutputProc
class MockXMPTextOutputProc {
public:
    MOCK_METHOD(void, operator(), (const char* text), ());
};

// Unit test for WXMPMeta_DumpNamespaces_1
TEST_F(WXMPMeta_DumpNamespaces_1, NullOutProc_1995) {
    WXMP_Result wResult;

    // Verify that the function throws an exception when the outProc is null
    EXPECT_THROW(WXMPMeta_DumpNamespaces_1(nullptr, nullptr, &wResult), std::runtime_error);
}

TEST_F(WXMPMeta_DumpNamespaces_1, ValidOutProc_1995) {
    // Arrange
    MockXMPTextOutputProc mockOutProc;
    WXMP_Result wResult;
    EXPECT_CALL(mockOutProc, operator()(testing::_)).Times(testing::AtLeast(1));  // Expect the output function to be called at least once

    // Act
    WXMPMeta_DumpNamespaces_1(mockOutProc, nullptr, &wResult);

    // Assert
    EXPECT_EQ(wResult.int32Result, kXMPErr_Unknown);  // Check the status code, adjust according to your expectations
}

TEST_F(WXMPMeta_DumpNamespaces_1, BadParam_1995) {
    // Arrange
    WXMP_Result wResult;

    // Act
    EXPECT_THROW(WXMPMeta_DumpNamespaces_1(nullptr, nullptr, &wResult), std::runtime_error);

    // Assert
    EXPECT_EQ(wResult.int32Result, kXMPErr_BadParam);  // Check that the error code is correct
}

// You can add more tests for additional behaviors, boundary cases, etc.