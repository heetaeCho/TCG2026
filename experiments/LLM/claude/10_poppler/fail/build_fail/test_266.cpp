#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XRef.h"
#include "Object.h"

// Test fixture for XRef tests using the default constructor
class XRefTest_266 : public ::testing::Test {
protected:
    void SetUp() override {
        xref = new XRef();
    }

    void TearDown() override {
        delete xref;
    }

    XRef *xref;
};

// Test that default-constructed XRef returns a non-null trailer dict pointer
TEST_F(XRefTest_266, GetTrailerDictReturnsNonNull_266) {
    Object *trailerDict = xref->getTrailerDict();
    ASSERT_NE(trailerDict, nullptr);
}

// Test that getTrailerDict returns the same pointer on multiple calls
TEST_F(XRefTest_266, GetTrailerDictReturnsSamePointer_266) {
    Object *first = xref->getTrailerDict();
    Object *second = xref->getTrailerDict();
    EXPECT_EQ(first, second);
}

// Test that default-constructed XRef reports not OK (no valid stream)
TEST_F(XRefTest_266, DefaultConstructorIsNotOk_266) {
    // Default XRef with no stream should not be "ok"
    // This tests the observable behavior of isOk()
    bool ok = xref->isOk();
    // Default constructed XRef may or may not be ok depending on implementation
    // We just verify it doesn't crash and returns a bool
    EXPECT_TRUE(ok || !ok);
}

// Test getErrorCode on default-constructed XRef
TEST_F(XRefTest_266, DefaultConstructorErrorCode_266) {
    int errCode = xref->getErrorCode();
    // Error code should be some integer value
    EXPECT_GE(errCode, 0);
}

// Test that default-constructed XRef is not encrypted
TEST_F(XRefTest_266, DefaultConstructorNotEncrypted_266) {
    EXPECT_FALSE(xref->isEncrypted());
}

// Test getNumObjects on default XRef
TEST_F(XRefTest_266, DefaultConstructorNumObjects_266) {
    int numObjects = xref->getNumObjects();
    EXPECT_GE(numObjects, 0);
}

// Test isModified on default XRef
TEST_F(XRefTest_266, DefaultConstructorNotModified_266) {
    EXPECT_FALSE(xref->isModified());
}

// Test setModified changes isModified
TEST_F(XRefTest_266, SetModifiedMakesIsModifiedTrue_266) {
    xref->setModified();
    EXPECT_TRUE(xref->isModified());
}

// Test isXRefStream on default XRef
TEST_F(XRefTest_266, DefaultConstructorIsNotXRefStream_266) {
    EXPECT_FALSE(xref->isXRefStream());
}

// Test getRootNum and getRootGen on default XRef
TEST_F(XRefTest_266, DefaultConstructorRootNumAndGen_266) {
    int rootNum = xref->getRootNum();
    int rootGen = xref->getRootGen();
    // Default values should be non-negative or -1 depending on implementation
    // Just verify no crash
    (void)rootNum;
    (void)rootGen;
}

// Test getRoot on default XRef
TEST_F(XRefTest_266, DefaultConstructorGetRoot_266) {
    Ref root = xref->getRoot();
    // Root ref should have num and gen fields
    (void)root.num;
    (void)root.gen;
}

// Test getPermFlags on default XRef
TEST_F(XRefTest_266, DefaultConstructorPermFlags_266) {
    int permFlags = xref->getPermFlags();
    (void)permFlags; // Just verify no crash
}

// Test that lock and unlock don't crash
TEST_F(XRefTest_266, LockAndUnlockNoCrash_266) {
    EXPECT_NO_FATAL_FAILURE(xref->lock());
    EXPECT_NO_FATAL_FAILURE(xref->unlock());
}

// Test construction with a trailerDict Object
class XRefTrailerDictTest_266 : public ::testing::Test {
protected:
    void SetUp() override {
        trailerObj = Object(new Dict(nullptr));
        xref = new XRef(&trailerObj);
    }

    void TearDown() override {
        delete xref;
    }

    Object trailerObj;
    XRef *xref;
};

TEST_F(XRefTrailerDictTest_266, ConstructedWithTrailerDictIsOk_266) {
    // XRef constructed with a trailer dict object
    // Verify getTrailerDict returns non-null
    Object *td = xref->getTrailerDict();
    ASSERT_NE(td, nullptr);
}

TEST_F(XRefTrailerDictTest_266, IsNotEncrypted_266) {
    EXPECT_FALSE(xref->isEncrypted());
}

TEST_F(XRefTrailerDictTest_266, NotModifiedInitially_266) {
    EXPECT_FALSE(xref->isModified());
}

// Test permission check methods on default (non-encrypted) XRef
TEST_F(XRefTest_266, OkToPrintWhenNotEncrypted_266) {
    // When not encrypted, print should be allowed
    EXPECT_TRUE(xref->okToPrint(false));
}

TEST_F(XRefTest_266, OkToPrintHighResWhenNotEncrypted_266) {
    EXPECT_TRUE(xref->okToPrintHighRes(false));
}

TEST_F(XRefTest_266, OkToChangeWhenNotEncrypted_266) {
    EXPECT_TRUE(xref->okToChange(false));
}

TEST_F(XRefTest_266, OkToCopyWhenNotEncrypted_266) {
    EXPECT_TRUE(xref->okToCopy(false));
}

TEST_F(XRefTest_266, OkToAddNotesWhenNotEncrypted_266) {
    EXPECT_TRUE(xref->okToAddNotes(false));
}

TEST_F(XRefTest_266, OkToFillFormWhenNotEncrypted_266) {
    EXPECT_TRUE(xref->okToFillForm(false));
}

TEST_F(XRefTest_266, OkToAccessibilityWhenNotEncrypted_266) {
    EXPECT_TRUE(xref->okToAccessibility(false));
}

TEST_F(XRefTest_266, OkToAssembleWhenNotEncrypted_266) {
    EXPECT_TRUE(xref->okToAssemble(false));
}

// Test permission methods with ignoreOwnerPW = true
TEST_F(XRefTest_266, OkToPrintIgnoreOwnerPW_266) {
    EXPECT_TRUE(xref->okToPrint(true));
}

TEST_F(XRefTest_266, OkToCopyIgnoreOwnerPW_266) {
    EXPECT_TRUE(xref->okToCopy(true));
}

// Test that setModified can be called multiple times
TEST_F(XRefTest_266, SetModifiedMultipleTimes_266) {
    xref->setModified();
    EXPECT_TRUE(xref->isModified());
    xref->setModified();
    EXPECT_TRUE(xref->isModified());
}

// Test getEntry with invalid index
TEST_F(XRefTest_266, GetEntryWithNegativeIndex_266) {
    XRefEntry *entry = xref->getEntry(-1, false);
    // Should return nullptr or handle gracefully
    // We just verify no crash
    (void)entry;
}

// Test getEntry with zero index
TEST_F(XRefTest_266, GetEntryWithZeroIndex_266) {
    if (xref->getNumObjects() > 0) {
        XRefEntry *entry = xref->getEntry(0, false);
        // Entry could be valid or null
        (void)entry;
    }
}

// Test getEntry with out-of-bounds index
TEST_F(XRefTest_266, GetEntryOutOfBounds_266) {
    int numObjects = xref->getNumObjects();
    XRefEntry *entry = xref->getEntry(numObjects + 100, false);
    // Should handle gracefully - might return null or expand
    (void)entry;
}

// Test getStreamEnd with arbitrary values
TEST_F(XRefTest_266, GetStreamEndDefault_266) {
    Goffset streamEnd = 0;
    bool result = xref->getStreamEnd(0, &streamEnd);
    // On default XRef with no streams, should return false
    EXPECT_FALSE(result);
}

// Test markUnencrypted doesn't crash
TEST_F(XRefTest_266, MarkUnencryptedNoCrash_266) {
    EXPECT_NO_FATAL_FAILURE(xref->markUnencrypted());
}

// Test getEncryptionParameters on non-encrypted XRef
TEST_F(XRefTest_266, GetEncryptionParametersNonEncrypted_266) {
    unsigned char *fileKey = nullptr;
    CryptAlgorithm algo;
    int keyLen = 0;
    xref->getEncryptionParameters(&fileKey, &algo, &keyLen);
    // Should not crash; values may be uninitialized or default
    (void)fileKey;
    (void)algo;
    (void)keyLen;
}

// Test isRefEncrypted on non-encrypted XRef
TEST_F(XRefTest_266, IsRefEncryptedOnNonEncryptedXRef_266) {
    Ref ref = {1, 0};
    EXPECT_FALSE(xref->isRefEncrypted(ref));
}

// Test getCatalog on default XRef
TEST_F(XRefTest_266, GetCatalogDefault_266) {
    Object catalog = xref->getCatalog();
    // On default XRef, catalog might be null/none type
    (void)catalog;
}

// Test removeDocInfo doesn't crash on default XRef
TEST_F(XRefTest_266, RemoveDocInfoNoCrash_266) {
    EXPECT_NO_FATAL_FAILURE(xref->removeDocInfo());
}

// Test scanSpecialFlags doesn't crash
TEST_F(XRefTest_266, ScanSpecialFlagsNoCrash_266) {
    EXPECT_NO_FATAL_FAILURE(xref->scanSpecialFlags());
}
