#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "XMPMeta.hpp"
#include "WXMPMeta.hpp"

// Forward declarations for the C wrapper functions we're testing
extern "C" {
void WXMPMeta_IncrementRefCount_1(XMPMetaRef xmpRef);
}

// We need access to XMP types
#include "XMP_Const.h"

class WXMPMetaIncrementRefCountTest_1991 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit if needed
        XMPMeta::Initialize();
    }

    void TearDown() override {
        XMPMeta::Terminate();
    }
};

// Test that IncrementRefCount increases the clientRefs by 1 from initial state
TEST_F(WXMPMetaIncrementRefCountTest_1991, IncrementFromInitialState_1991) {
    XMPMeta meta;
    XMP_Int32 initialRefs = meta.clientRefs;
    
    WXMPMeta_IncrementRefCount_1((XMPMetaRef)&meta);
    
    EXPECT_EQ(meta.clientRefs, initialRefs + 1);
}

// Test that calling IncrementRefCount multiple times increases clientRefs each time
TEST_F(WXMPMetaIncrementRefCountTest_1991, MultipleIncrements_1991) {
    XMPMeta meta;
    XMP_Int32 initialRefs = meta.clientRefs;
    
    WXMPMeta_IncrementRefCount_1((XMPMetaRef)&meta);
    WXMPMeta_IncrementRefCount_1((XMPMetaRef)&meta);
    WXMPMeta_IncrementRefCount_1((XMPMetaRef)&meta);
    
    EXPECT_EQ(meta.clientRefs, initialRefs + 3);
}

// Test that IncrementRefCount results in a positive clientRefs value
TEST_F(WXMPMetaIncrementRefCountTest_1991, ResultIsPositive_1991) {
    XMPMeta meta;
    
    WXMPMeta_IncrementRefCount_1((XMPMetaRef)&meta);
    
    EXPECT_GT(meta.clientRefs, 0);
}

// Test single increment produces exactly one more than before
TEST_F(WXMPMetaIncrementRefCountTest_1991, SingleIncrementByOne_1991) {
    XMPMeta meta;
    XMP_Int32 before = meta.clientRefs;
    
    WXMPMeta_IncrementRefCount_1((XMPMetaRef)&meta);
    
    XMP_Int32 after = meta.clientRefs;
    EXPECT_EQ(after - before, 1);
}

// Test that two separate XMPMeta objects have independent ref counts
TEST_F(WXMPMetaIncrementRefCountTest_1991, IndependentRefCounts_1991) {
    XMPMeta meta1;
    XMPMeta meta2;
    
    XMP_Int32 initial1 = meta1.clientRefs;
    XMP_Int32 initial2 = meta2.clientRefs;
    
    WXMPMeta_IncrementRefCount_1((XMPMetaRef)&meta1);
    WXMPMeta_IncrementRefCount_1((XMPMetaRef)&meta1);
    WXMPMeta_IncrementRefCount_1((XMPMetaRef)&meta2);
    
    EXPECT_EQ(meta1.clientRefs, initial1 + 2);
    EXPECT_EQ(meta2.clientRefs, initial2 + 1);
}

// Test many increments to verify consistency
TEST_F(WXMPMetaIncrementRefCountTest_1991, ManyIncrements_1991) {
    XMPMeta meta;
    XMP_Int32 initialRefs = meta.clientRefs;
    
    const int numIncrements = 100;
    for (int i = 0; i < numIncrements; ++i) {
        WXMPMeta_IncrementRefCount_1((XMPMetaRef)&meta);
    }
    
    EXPECT_EQ(meta.clientRefs, initialRefs + numIncrements);
}

// Test that the increment is exactly 1 (not 2 or any other value)
TEST_F(WXMPMetaIncrementRefCountTest_1991, IncrementIsExactlyOne_1991) {
    XMPMeta meta;
    XMP_Int32 refsBefore = meta.clientRefs;
    
    WXMPMeta_IncrementRefCount_1((XMPMetaRef)&meta);
    
    XMP_Int32 refsAfter = meta.clientRefs;
    EXPECT_EQ(refsAfter, refsBefore + 1);
    EXPECT_NE(refsAfter, refsBefore + 2);
    EXPECT_NE(refsAfter, refsBefore);
}

// Test that the function doesn't affect other members (object name stays the same)
TEST_F(WXMPMetaIncrementRefCountTest_1991, DoesNotAffectOtherMembers_1991) {
    XMPMeta meta;
    meta.SetObjectName("TestName");
    
    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    meta.GetObjectName(&namePtr, &nameLen);
    std::string nameBefore(namePtr, nameLen);
    
    WXMPMeta_IncrementRefCount_1((XMPMetaRef)&meta);
    
    meta.GetObjectName(&namePtr, &nameLen);
    std::string nameAfter(namePtr, nameLen);
    
    EXPECT_EQ(nameBefore, nameAfter);
}
