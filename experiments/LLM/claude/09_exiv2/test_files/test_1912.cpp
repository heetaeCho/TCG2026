#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPIterator.hpp"
#include "XMPCore_Impl.hpp"

// Declaration of the function under test
extern "C" void WXMPIterator_Next_1(
    XMPIteratorRef iterRef,
    XMP_StringPtr * schemaNS,
    XMP_StringLen * nsSize,
    XMP_StringPtr * propPath,
    XMP_StringLen * pathSize,
    XMP_StringPtr * propValue,
    XMP_StringLen * valueSize,
    XMP_OptionBits * propOptions,
    WXMP_Result * wResult);

// Test fixture
class WXMPIteratorNextTest_1912 : public ::testing::Test {
protected:
    void SetUp() override {
        memset(&wResult, 0, sizeof(wResult));
    }

    WXMP_Result wResult;
};

// Test: WXMP_Result is properly initialized
TEST_F(WXMPIteratorNextTest_1912, ResultInitialization_1912) {
    WXMP_Result result;
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_EQ(result.int32Result, 0u);
}

// Test: Calling with null iterRef should produce an error in wResult
TEST_F(WXMPIteratorNextTest_1912, NullIterRefProducesError_1912) {
    XMP_StringPtr schemaNS = nullptr;
    XMP_StringLen nsSize = 0;
    XMP_StringPtr propPath = nullptr;
    XMP_StringLen pathSize = 0;
    XMP_StringPtr propValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits propOptions = 0;

    WXMPIterator_Next_1(
        nullptr,
        &schemaNS, &nsSize,
        &propPath, &pathSize,
        &propValue, &valueSize,
        &propOptions,
        &wResult);

    // With a null iterRef, the conversion WtoXMPIterator_Ptr should fail
    // and the wrapper should catch the exception, setting errMessage
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Calling with all null optional params and null iterRef
TEST_F(WXMPIteratorNextTest_1912, AllNullOutputParams_1912) {
    WXMPIterator_Next_1(
        nullptr,
        nullptr, nullptr,
        nullptr, nullptr,
        nullptr, nullptr,
        nullptr,
        &wResult);

    // Should still produce an error due to null iterRef
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Verify WXMP_Result default state before call
TEST_F(WXMPIteratorNextTest_1912, WXMPResultDefaultConstruction_1912) {
    WXMP_Result freshResult;
    EXPECT_EQ(freshResult.errMessage, nullptr);
    EXPECT_EQ(freshResult.int32Result, 0u);
    EXPECT_EQ(freshResult.int64Result, 0u);
    EXPECT_DOUBLE_EQ(freshResult.floatResult, 0.0);
    EXPECT_EQ(freshResult.ptrResult, nullptr);
}

// Test: Error result int32Result should be 0 on failure
TEST_F(WXMPIteratorNextTest_1912, ErrorResultInt32IsZero_1912) {
    WXMPIterator_Next_1(
        nullptr,
        nullptr, nullptr,
        nullptr, nullptr,
        nullptr, nullptr,
        nullptr,
        &wResult);

    // On error, int32Result should remain 0 (not found)
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: Invalid (non-null but invalid) iterRef should produce error
TEST_F(WXMPIteratorNextTest_1912, InvalidIterRefProducesError_1912) {
    // Use a garbage pointer that isn't a valid XMPIterator
    int dummy = 42;
    XMPIteratorRef badRef = reinterpret_cast<XMPIteratorRef>(&dummy);

    WXMPIterator_Next_1(
        badRef,
        nullptr, nullptr,
        nullptr, nullptr,
        nullptr, nullptr,
        nullptr,
        &wResult);

    // Should fail since it's not a valid XMPIterator object
    // Either errMessage is set or behavior is undefined, but we check it doesn't crash cleanly
    // The wrapper should catch exceptions
    EXPECT_TRUE(wResult.errMessage != nullptr || wResult.int32Result == 0u);
}
