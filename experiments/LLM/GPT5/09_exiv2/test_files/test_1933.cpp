#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "WXMPUtils.hpp" // Include the necessary header files for the test

// Mock the dependencies if needed (none required for this function)
class MockWXMPUtils : public WXMPUtils {
public:
    MOCK_METHOD(bool, Initialize, (), (override));
    MOCK_METHOD(void, Terminate, (), (override));
};

// Unit tests for WXMPUtils_ComposeLangSelector_1
TEST_F(WXMPUtils_ComposeLangSelector_1, ValidInput_1933) {
    // TEST_ID: 1933 - Test normal operation with valid input
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr arrayName = "array";
    XMP_StringPtr langName = "en";
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMP_Result wResult = { nullptr, nullptr, 0.0, 0, 0 };
    WXMPUtils_ComposeLangSelector_1(schemaNS, arrayName, langName, &fullPath, &pathSize, &wResult);

    ASSERT_NE(fullPath, nullptr); // Ensure fullPath is populated
    ASSERT_GT(pathSize, 0);       // Ensure pathSize is set
    ASSERT_EQ(wResult.errMessage, nullptr); // Ensure there are no error messages
}

TEST_F(WXMPUtils_ComposeLangSelector_1, EmptySchemaNS_1934) {
    // TEST_ID: 1934 - Test for empty schema namespace
    XMP_StringPtr schemaNS = "";
    XMP_StringPtr arrayName = "array";
    XMP_StringPtr langName = "en";
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMP_Result wResult = { nullptr, nullptr, 0.0, 0, 0 };

    // Expect the function to throw the appropriate error
    EXPECT_THROW(WXMPUtils_ComposeLangSelector_1(schemaNS, arrayName, langName, &fullPath, &pathSize, &wResult), std::runtime_error);
}

TEST_F(WXMPUtils_ComposeLangSelector_1, EmptyArrayName_1935) {
    // TEST_ID: 1935 - Test for empty array name
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr arrayName = "";
    XMP_StringPtr langName = "en";
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMP_Result wResult = { nullptr, nullptr, 0.0, 0, 0 };

    // Expect the function to throw the appropriate error
    EXPECT_THROW(WXMPUtils_ComposeLangSelector_1(schemaNS, arrayName, langName, &fullPath, &pathSize, &wResult), std::runtime_error);
}

TEST_F(WXMPUtils_ComposeLangSelector_1, EmptyLangName_1936) {
    // TEST_ID: 1936 - Test for empty language name
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr arrayName = "array";
    XMP_StringPtr langName = "";
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMP_Result wResult = { nullptr, nullptr, 0.0, 0, 0 };

    // Expect the function to throw the appropriate error
    EXPECT_THROW(WXMPUtils_ComposeLangSelector_1(schemaNS, arrayName, langName, &fullPath, &pathSize, &wResult), std::runtime_error);
}

TEST_F(WXMPUtils_ComposeLangSelector_1, NullFullPath_1937) {
    // TEST_ID: 1937 - Test for null fullPath parameter
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr arrayName = "array";
    XMP_StringPtr langName = "en";
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMP_Result wResult = { nullptr, nullptr, 0.0, 0, 0 };

    WXMPUtils_ComposeLangSelector_1(schemaNS, arrayName, langName, &fullPath, &pathSize, &wResult);

    // Check that the fullPath gets assigned even though it was passed as null
    ASSERT_NE(fullPath, nullptr);
}

TEST_F(WXMPUtils_ComposeLangSelector_1, NullPathSize_1938) {
    // TEST_ID: 1938 - Test for null pathSize parameter
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr arrayName = "array";
    XMP_StringPtr langName = "en";
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;

    WXMP_Result wResult = { nullptr, nullptr, 0.0, 0, 0 };

    WXMPUtils_ComposeLangSelector_1(schemaNS, arrayName, langName, &fullPath, &pathSize, &wResult);

    // Ensure pathSize is updated
    ASSERT_GT(pathSize, 0);
}