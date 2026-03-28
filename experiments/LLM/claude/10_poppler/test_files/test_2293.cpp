#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib.h>

// Include necessary headers
#include "poppler-action.h"
#include "Link.h"
#include "GooString.h"

// We need access to build_launch which is static in the .cc file
// For testing purposes, we declare it or include the relevant header
// Since build_launch is static, we may need to include the .cc or use a test wrapper
// For this test, we assume build_launch is accessible (e.g., via a test-only header or linkage)

extern "C" {
// Forward declare if needed - build_launch is a static function in poppler-action.cc
// We need to make it testable. Assuming it's been made accessible for testing.
}

// Since build_launch is static, we include the source to access it in tests
// This is a common pattern for testing static functions
#include "poppler-action.cc"

class MockLinkLaunch : public LinkLaunch {
public:
    MockLinkLaunch() : LinkLaunch(nullptr) {}
    MOCK_CONST_METHOD0(getFileName, const GooString*());
    MOCK_CONST_METHOD0(getParams, const GooString*());
    MOCK_CONST_METHOD0(isOk, bool());
    MOCK_CONST_METHOD0(getKind, LinkActionKind());
};

class BuildLaunchTest_2293 : public ::testing::Test {
protected:
    void SetUp() override {
        memset(&action, 0, sizeof(PopplerAction));
    }

    void TearDown() override {
        g_free(action.launch.file_name);
        g_free(action.launch.params);
    }

    PopplerAction action;
};

// Test: When both fileName and params are non-null, both fields are populated
TEST_F(BuildLaunchTest_2293, BothFileNameAndParamsSet_2293) {
    GooString fileName("test_file.pdf");
    GooString params("--page 5");

    MockLinkLaunch mockLink;
    EXPECT_CALL(mockLink, getFileName())
        .WillRepeatedly(::testing::Return(&fileName));
    EXPECT_CALL(mockLink, getParams())
        .WillRepeatedly(::testing::Return(&params));

    build_launch(&action, &mockLink);

    ASSERT_NE(action.launch.file_name, nullptr);
    EXPECT_STREQ(action.launch.file_name, "test_file.pdf");

    ASSERT_NE(action.launch.params, nullptr);
    EXPECT_STREQ(action.launch.params, "--page 5");
}

// Test: When fileName is null, file_name should remain null/unchanged
TEST_F(BuildLaunchTest_2293, FileNameIsNull_2293) {
    GooString params("some_params");

    MockLinkLaunch mockLink;
    EXPECT_CALL(mockLink, getFileName())
        .WillRepeatedly(::testing::Return(nullptr));
    EXPECT_CALL(mockLink, getParams())
        .WillRepeatedly(::testing::Return(&params));

    build_launch(&action, &mockLink);

    EXPECT_EQ(action.launch.file_name, nullptr);
    ASSERT_NE(action.launch.params, nullptr);
    EXPECT_STREQ(action.launch.params, "some_params");
}

// Test: When params is null, params should remain null/unchanged
TEST_F(BuildLaunchTest_2293, ParamsIsNull_2293) {
    GooString fileName("document.pdf");

    MockLinkLaunch mockLink;
    EXPECT_CALL(mockLink, getFileName())
        .WillRepeatedly(::testing::Return(&fileName));
    EXPECT_CALL(mockLink, getParams())
        .WillRepeatedly(::testing::Return(nullptr));

    build_launch(&action, &mockLink);

    ASSERT_NE(action.launch.file_name, nullptr);
    EXPECT_STREQ(action.launch.file_name, "document.pdf");
    EXPECT_EQ(action.launch.params, nullptr);
}

// Test: When both fileName and params are null
TEST_F(BuildLaunchTest_2293, BothNull_2293) {
    MockLinkLaunch mockLink;
    EXPECT_CALL(mockLink, getFileName())
        .WillRepeatedly(::testing::Return(nullptr));
    EXPECT_CALL(mockLink, getParams())
        .WillRepeatedly(::testing::Return(nullptr));

    build_launch(&action, &mockLink);

    EXPECT_EQ(action.launch.file_name, nullptr);
    EXPECT_EQ(action.launch.params, nullptr);
}

// Test: Empty strings for fileName and params
TEST_F(BuildLaunchTest_2293, EmptyStrings_2293) {
    GooString fileName("");
    GooString params("");

    MockLinkLaunch mockLink;
    EXPECT_CALL(mockLink, getFileName())
        .WillRepeatedly(::testing::Return(&fileName));
    EXPECT_CALL(mockLink, getParams())
        .WillRepeatedly(::testing::Return(&params));

    build_launch(&action, &mockLink);

    ASSERT_NE(action.launch.file_name, nullptr);
    EXPECT_STREQ(action.launch.file_name, "");

    ASSERT_NE(action.launch.params, nullptr);
    EXPECT_STREQ(action.launch.params, "");
}

// Test: Unicode/UTF-8 characters in file name
TEST_F(BuildLaunchTest_2293, UnicodeFileName_2293) {
    GooString fileName("файл.pdf"); // Cyrillic characters
    GooString params("--open");

    MockLinkLaunch mockLink;
    EXPECT_CALL(mockLink, getFileName())
        .WillRepeatedly(::testing::Return(&fileName));
    EXPECT_CALL(mockLink, getParams())
        .WillRepeatedly(::testing::Return(&params));

    build_launch(&action, &mockLink);

    ASSERT_NE(action.launch.file_name, nullptr);
    // The exact output depends on _poppler_goo_string_to_utf8 but it should not be null
    ASSERT_NE(action.launch.params, nullptr);
    EXPECT_STREQ(action.launch.params, "--open");
}

// Test: Long file name and params
TEST_F(BuildLaunchTest_2293, LongStrings_2293) {
    std::string longName(1000, 'a');
    std::string longParams(1000, 'b');
    GooString fileName(longName.c_str());
    GooString params(longParams.c_str());

    MockLinkLaunch mockLink;
    EXPECT_CALL(mockLink, getFileName())
        .WillRepeatedly(::testing::Return(&fileName));
    EXPECT_CALL(mockLink, getParams())
        .WillRepeatedly(::testing::Return(&params));

    build_launch(&action, &mockLink);

    ASSERT_NE(action.launch.file_name, nullptr);
    ASSERT_NE(action.launch.params, nullptr);
    EXPECT_STREQ(action.launch.params, longParams.c_str());
}

// Test: Special characters in params
TEST_F(BuildLaunchTest_2293, SpecialCharactersInParams_2293) {
    GooString fileName("test.pdf");
    GooString params("--flag=\"value with spaces\" & | > <");

    MockLinkLaunch mockLink;
    EXPECT_CALL(mockLink, getFileName())
        .WillRepeatedly(::testing::Return(&fileName));
    EXPECT_CALL(mockLink, getParams())
        .WillRepeatedly(::testing::Return(&params));

    build_launch(&action, &mockLink);

    ASSERT_NE(action.launch.params, nullptr);
    EXPECT_STREQ(action.launch.params, "--flag=\"value with spaces\" & | > <");
}
