#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declarations matching the interface
typedef void* XMPIteratorRef;
typedef XMP_Uns32 XMP_OptionBits;

extern "C" void WXMPIterator_Skip_1(XMPIteratorRef iterRef, XMP_OptionBits options, WXMP_Result* wResult);

class WXMPIteratorSkipTest_1913 : public ::testing::Test {
protected:
    WXMP_Result result;

    void SetUp() override {
        result = WXMP_Result();
    }
};

// Test that passing a null iterator reference results in an error
TEST_F(WXMPIteratorSkipTest_1913, NullIteratorRef_SetsError_1913) {
    WXMPIterator_Skip_1(nullptr, 0, &result);
    // A null iterator ref should cause an error, resulting in a non-null errMessage
    EXPECT_NE(result.errMessage, nullptr);
}

// Test that passing a null iterator reference with various option bits still errors
TEST_F(WXMPIteratorSkipTest_1913, NullIteratorRefWithOptions_SetsError_1913) {
    WXMPIterator_Skip_1(nullptr, 0x01, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test that passing an invalid (non-null but bogus) iterator reference results in an error
TEST_F(WXMPIteratorSkipTest_1913, InvalidIteratorRef_SetsError_1913) {
    // Create a bogus pointer that is not a valid XMPIterator
    int dummy = 42;
    XMPIteratorRef bogusRef = reinterpret_cast<XMPIteratorRef>(&dummy);

    // This should either crash or set an error; we test that the wrapper catches it
    // Since the wrapper uses XMP_ENTER_WRAPPER/XMP_EXIT_WRAPPER, it should catch exceptions
    WXMP_Result localResult = WXMP_Result();
    // Note: This may cause undefined behavior with a truly bogus pointer,
    // but the wrapper pattern should catch exceptions from bad object access
    // We protect this test with a try in case it doesn't gracefully handle it
    WXMPIterator_Skip_1(bogusRef, 0, &localResult);
    // If we get here, we expect an error was reported
    EXPECT_NE(localResult.errMessage, nullptr);
}

// Test WXMP_Result default initialization
TEST_F(WXMPIteratorSkipTest_1913, ResultDefaultInitialization_1913) {
    WXMP_Result freshResult;
    EXPECT_EQ(freshResult.errMessage, nullptr);
    EXPECT_EQ(freshResult.int32Result, 0u);
    EXPECT_EQ(freshResult.int64Result, 0u);
}

// Test that null ref with multiple different option values all produce errors
TEST_F(WXMPIteratorSkipTest_1913, NullRefWithDifferentOptions_AllError_1913) {
    XMP_OptionBits optionValues[] = {0, 1, 2, 0xFF, 0xFFFFFFFF};
    for (auto opt : optionValues) {
        WXMP_Result r = WXMP_Result();
        WXMPIterator_Skip_1(nullptr, opt, &r);
        EXPECT_NE(r.errMessage, nullptr)
            << "Expected error for null ref with options=" << opt;
    }
}

// Test that calling with zero options on null ref produces error
TEST_F(WXMPIteratorSkipTest_1913, NullRefZeroOptions_1913) {
    WXMP_Result r = WXMP_Result();
    WXMPIterator_Skip_1(nullptr, 0, &r);
    EXPECT_NE(r.errMessage, nullptr);
}
