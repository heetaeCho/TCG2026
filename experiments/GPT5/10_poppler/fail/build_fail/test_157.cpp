#include <gtest/gtest.h>
#include <memory>

// Include the header under test
#include "Stream.h"

// ------------------------------------------------------------
// Test Suite for CachedFileStream - TEST_ID 157
// ------------------------------------------------------------

// Since we must treat the implementation as a black box,
// and only rely on observable behavior via the public interface,
// these tests focus on the getKind() override behavior.

class CachedFileStreamTest_157 : public ::testing::Test {
protected:
    // No internal state access allowed.
    // No re-implementation of internal logic.
};

// ------------------------------------------------------------
// Normal Operation Tests
// ------------------------------------------------------------

// Verify that getKind() returns strCachedFile
TEST_F(CachedFileStreamTest_157, GetKindReturnsStrCachedFile_157) {
    CachedFileStream stream;
    EXPECT_EQ(stream.getKind(), strCachedFile);
}

// Verify that the returned value matches the expected enum numeric value
TEST_F(CachedFileStreamTest_157, GetKindReturnsCorrectEnumValue_157) {
    CachedFileStream stream;
    EXPECT_EQ(static_cast<int>(stream.getKind()), static_cast<int>(strCachedFile));
}

// ------------------------------------------------------------
// Boundary / Stability Tests
// ------------------------------------------------------------

// Repeated calls should consistently return the same value
TEST_F(CachedFileStreamTest_157, GetKindIsStableAcrossMultipleCalls_157) {
    CachedFileStream stream;

    StreamKind first = stream.getKind();
    StreamKind second = stream.getKind();
    StreamKind third = stream.getKind();

    EXPECT_EQ(first, strCachedFile);
    EXPECT_EQ(second, strCachedFile);
    EXPECT_EQ(third, strCachedFile);
}

// Verify that getKind() is const-correct and callable on const object
TEST_F(CachedFileStreamTest_157, GetKindCallableOnConstObject_157) {
    const CachedFileStream stream;
    EXPECT_EQ(stream.getKind(), strCachedFile);
}

// ------------------------------------------------------------
// Exceptional / Error Case Tests
// ------------------------------------------------------------

// Since getKind() is a simple const override returning an enum,
// no exceptional behavior is observable via the interface.
// This test verifies that calling getKind() does not throw.
TEST_F(CachedFileStreamTest_157, GetKindDoesNotThrow_157) {
    CachedFileStream stream;
    EXPECT_NO_THROW({
        auto kind = stream.getKind();
        EXPECT_EQ(kind, strCachedFile);
    });
}

// ------------------------------------------------------------
// External Interaction Verification
// ------------------------------------------------------------

// getKind() does not interact with external collaborators.
// This test ensures it behaves independently of external state.
TEST_F(CachedFileStreamTest_157, GetKindIndependentOfExternalState_157) {
    CachedFileStream stream1;
    CachedFileStream stream2;

    EXPECT_EQ(stream1.getKind(), strCachedFile);
    EXPECT_EQ(stream2.getKind(), strCachedFile);
    EXPECT_EQ(stream1.getKind(), stream2.getKind());
}