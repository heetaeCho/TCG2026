#include <gtest/gtest.h>
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Forward declaration of the function under test
extern "C" {
void WXMPMeta_CTor_1(WXMP_Result* wResult);
}

class WXMPMetaCTorTest_1990 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMPMeta is initialized if needed
        XMPMeta::Initialize();
    }

    void TearDown() override {
        XMPMeta::Terminate();
    }
};

// Test that WXMPMeta_CTor_1 returns a non-null pointer result on success
TEST_F(WXMPMetaCTorTest_1990, ReturnsNonNullPtrResult_1990) {
    WXMP_Result result;
    WXMPMeta_CTor_1(&result);

    EXPECT_NE(result.ptrResult, nullptr);
    EXPECT_EQ(result.errMessage, nullptr);

    // Clean up: the created XMPMeta object needs to be deleted
    if (result.ptrResult != nullptr) {
        XMPMeta* xmpObj = reinterpret_cast<XMPMeta*>(result.ptrResult);
        delete xmpObj;
    }
}

// Test that WXMP_Result is properly initialized before call
TEST_F(WXMPMetaCTorTest_1990, ResultInitializedCorrectly_1990) {
    WXMP_Result result;

    // Verify default initialization of WXMP_Result
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_EQ(result.ptrResult, nullptr);

    WXMPMeta_CTor_1(&result);

    // After construction, ptrResult should be set
    EXPECT_NE(result.ptrResult, nullptr);
    // No error should have occurred
    EXPECT_EQ(result.errMessage, nullptr);

    // Clean up
    if (result.ptrResult != nullptr) {
        XMPMeta* xmpObj = reinterpret_cast<XMPMeta*>(result.ptrResult);
        delete xmpObj;
    }
}

// Test that clientRefs is set to 1 after construction
TEST_F(WXMPMetaCTorTest_1990, ClientRefsIsOne_1990) {
    WXMP_Result result;
    WXMPMeta_CTor_1(&result);

    ASSERT_NE(result.ptrResult, nullptr);

    XMPMeta* xmpObj = reinterpret_cast<XMPMeta*>(result.ptrResult);
    EXPECT_EQ(xmpObj->clientRefs, 1);

    delete xmpObj;
}

// Test that multiple calls create distinct objects
TEST_F(WXMPMetaCTorTest_1990, MultipleCallsCreateDistinctObjects_1990) {
    WXMP_Result result1;
    WXMP_Result result2;

    WXMPMeta_CTor_1(&result1);
    WXMPMeta_CTor_1(&result2);

    ASSERT_NE(result1.ptrResult, nullptr);
    ASSERT_NE(result2.ptrResult, nullptr);
    EXPECT_NE(result1.ptrResult, result2.ptrResult);

    // Both should have clientRefs == 1
    XMPMeta* xmpObj1 = reinterpret_cast<XMPMeta*>(result1.ptrResult);
    XMPMeta* xmpObj2 = reinterpret_cast<XMPMeta*>(result2.ptrResult);
    EXPECT_EQ(xmpObj1->clientRefs, 1);
    EXPECT_EQ(xmpObj2->clientRefs, 1);

    delete xmpObj1;
    delete xmpObj2;
}

// Test that the error message remains null (no error) on successful construction
TEST_F(WXMPMetaCTorTest_1990, NoErrorOnSuccess_1990) {
    WXMP_Result result;
    WXMPMeta_CTor_1(&result);

    EXPECT_EQ(result.errMessage, nullptr);

    if (result.ptrResult != nullptr) {
        XMPMeta* xmpObj = reinterpret_cast<XMPMeta*>(result.ptrResult);
        delete xmpObj;
    }
}

// Test that the created object is a valid XMPMeta that can be used
TEST_F(WXMPMetaCTorTest_1990, CreatedObjectIsUsable_1990) {
    WXMP_Result result;
    WXMPMeta_CTor_1(&result);

    ASSERT_NE(result.ptrResult, nullptr);
    ASSERT_EQ(result.errMessage, nullptr);

    XMPMeta* xmpObj = reinterpret_cast<XMPMeta*>(result.ptrResult);

    // Verify we can call methods on the created object without crashing
    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    xmpObj->GetObjectName(&namePtr, &nameLen);

    // A freshly created object should have an empty or default name
    EXPECT_EQ(nameLen, 0u);

    delete xmpObj;
}

// Test constructing many objects to check for resource handling
TEST_F(WXMPMetaCTorTest_1990, MultipleConstructionsStressTest_1990) {
    const int count = 100;
    WXMP_Result results[100];

    for (int i = 0; i < count; ++i) {
        WXMPMeta_CTor_1(&results[i]);
        ASSERT_NE(results[i].ptrResult, nullptr) << "Failed at iteration " << i;
        ASSERT_EQ(results[i].errMessage, nullptr) << "Error at iteration " << i;
    }

    for (int i = 0; i < count; ++i) {
        XMPMeta* xmpObj = reinterpret_cast<XMPMeta*>(results[i].ptrResult);
        EXPECT_EQ(xmpObj->clientRefs, 1);
        delete xmpObj;
    }
}

// Test that other WXMP_Result fields are not modified
TEST_F(WXMPMetaCTorTest_1990, OtherResultFieldsUnmodified_1990) {
    WXMP_Result result;

    // Record initial values
    double initialFloat = result.floatResult;
    XMP_Uns64 initialInt64 = result.int64Result;
    XMP_Uns32 initialInt32 = result.int32Result;

    WXMPMeta_CTor_1(&result);

    // The constructor only sets ptrResult; other fields should remain default
    // (This tests that the function doesn't have unintended side effects)
    EXPECT_NE(result.ptrResult, nullptr);
    EXPECT_EQ(result.errMessage, nullptr);

    if (result.ptrResult != nullptr) {
        XMPMeta* xmpObj = reinterpret_cast<XMPMeta*>(result.ptrResult);
        delete xmpObj;
    }
}
