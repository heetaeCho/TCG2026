#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "WXMPIterator.hpp" // Assuming the relevant headers are included

// Mocking WXMP_Result for interaction verification
class MockWXMPResult : public WXMP_Result {
public:
    MOCK_METHOD(void, SetResult, (void* result), ());
};

// TEST_ID 1908: Test for normal operation of the WXMPIterator_TableCTor_1 function
TEST_F(WXMPIteratorTest_1908, NormalOperation_1908) {
    // Arrange
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr propName = "PropertyName";
    XMP_OptionBits options = 0;
    MockWXMPResult mockResult;

    // Act
    WXMPIterator_TableCTor_1(schemaNS, propName, options, &mockResult);

    // Assert: Check that the result pointer is correctly set
    EXPECT_EQ(mockResult.ptrResult, static_cast<void*>(XMPIteratorRef(new XMPIterator(schemaNS, propName, options))));
}

// TEST_ID 1909: Test for schemaNS and propName being null (edge case handling)
TEST_F(WXMPIteratorTest_1909, NullInputs_1909) {
    // Arrange
    XMP_StringPtr schemaNS = nullptr;
    XMP_StringPtr propName = nullptr;
    XMP_OptionBits options = 0;
    MockWXMPResult mockResult;

    // Act
    WXMPIterator_TableCTor_1(schemaNS, propName, options, &mockResult);

    // Assert: Ensure that null inputs are handled by setting default values
    EXPECT_EQ(mockResult.ptrResult, static_cast<void*>(XMPIteratorRef(new XMPIterator("", "", options))));
}

// TEST_ID 1910: Test for exceptional case when schemaNS is null
TEST_F(WXMPIteratorTest_1910, NullSchemaNS_1910) {
    // Arrange
    XMP_StringPtr schemaNS = nullptr;
    XMP_StringPtr propName = "PropertyName";
    XMP_OptionBits options = 0;
    MockWXMPResult mockResult;

    // Act
    WXMPIterator_TableCTor_1(schemaNS, propName, options, &mockResult);

    // Assert: Check if the default empty schema is applied correctly
    EXPECT_EQ(mockResult.ptrResult, static_cast<void*>(XMPIteratorRef(new XMPIterator("", propName, options))));
}

// TEST_ID 1911: Test for exceptional case when propName is null
TEST_F(WXMPIteratorTest_1911, NullPropName_1911) {
    // Arrange
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr propName = nullptr;
    XMP_OptionBits options = 0;
    MockWXMPResult mockResult;

    // Act
    WXMPIterator_TableCTor_1(schemaNS, propName, options, &mockResult);

    // Assert: Ensure that the null property name is handled as expected
    EXPECT_EQ(mockResult.ptrResult, static_cast<void*>(XMPIteratorRef(new XMPIterator(schemaNS, "", options))));
}

// TEST_ID 1912: Test for exceptional case when both schemaNS and propName are null
TEST_F(WXMPIteratorTest_1912, BothNullInputs_1912) {
    // Arrange
    XMP_StringPtr schemaNS = nullptr;
    XMP_StringPtr propName = nullptr;
    XMP_OptionBits options = 0;
    MockWXMPResult mockResult;

    // Act
    WXMPIterator_TableCTor_1(schemaNS, propName, options, &mockResult);

    // Assert: Ensure that both null inputs are handled and default values are set
    EXPECT_EQ(mockResult.ptrResult, static_cast<void*>(XMPIteratorRef(new XMPIterator("", "", options))));
}

// TEST_ID 1913: Test for checking internal iterator reference count
TEST_F(WXMPIteratorTest_1913, IteratorReferenceCount_1913) {
    // Arrange
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr propName = "PropertyName";
    XMP_OptionBits options = 0;
    MockWXMPResult mockResult;

    // Act
    WXMPIterator_TableCTor_1(schemaNS, propName, options, &mockResult);

    // Assert: Ensure the iterator reference count is set to 1 (after constructor)
    XMPIterator* iter = static_cast<XMPIterator*>(mockResult.ptrResult);
    EXPECT_EQ(iter->clientRefs, 1);
}

// TEST_ID 1914: Test for invalid options passed to the constructor
TEST_F(WXMPIteratorTest_1914, InvalidOptions_1914) {
    // Arrange
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr propName = "PropertyName";
    XMP_OptionBits invalidOptions = 9999; // Invalid option
    MockWXMPResult mockResult;

    // Act
    WXMPIterator_TableCTor_1(schemaNS, propName, invalidOptions, &mockResult);

    // Assert: Verify that the invalid options do not break the function (default behavior is maintained)
    EXPECT_EQ(mockResult.ptrResult, static_cast<void*>(XMPIteratorRef(new XMPIterator(schemaNS, propName, invalidOptions))));
}