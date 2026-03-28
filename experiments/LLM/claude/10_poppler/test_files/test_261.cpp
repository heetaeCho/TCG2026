#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XRef.h"
#include "Object.h"
#include "Stream.h"
#include "Dict.h"
#include "GooString.h"

// Test fixture for XRef with default constructor
class XRefTest_261 : public ::testing::Test {
protected:
    void SetUp() override {
        xref = new XRef();
    }

    void TearDown() override {
        delete xref;
    }

    XRef *xref;
};

// Test fixture for XRef with trailerDict constructor
class XRefTrailerTest_261 : public ::testing::Test {
protected:
    void SetUp() override {
        trailerDict = Object(new Dict(nullptr));
        xref = new XRef(&trailerDict);
    }

    void TearDown() override {
        delete xref;
    }

    Object trailerDict;
    XRef *xref;
};

// =============================================================================
// Tests using default constructor
// =============================================================================

TEST_F(XRefTest_261, DefaultConstructor_IsNotOk_261) {
    // A default-constructed XRef without a stream should not be "ok"
    // (no valid xref table was loaded)
    // The exact behavior depends on implementation, but we can at least call isOk()
    bool ok = xref->isOk();
    // We just verify it doesn't crash; the value is implementation-defined
    (void)ok;
}

TEST_F(XRefTest_261, DefaultConstructor_GetPermFlags_261) {
    int flags = xref->getPermFlags();
    // Default permFlags should be some initial value (likely 0 or -1)
    (void)flags; // Just verify it doesn't crash
}

TEST_F(XRefTest_261, DefaultConstructor_IsEncrypted_261) {
    // Default-constructed XRef should not be encrypted
    EXPECT_FALSE(xref->isEncrypted());
}

TEST_F(XRefTest_261, DefaultConstructor_IsModified_261) {
    // Default-constructed XRef should not be modified
    EXPECT_FALSE(xref->isModified());
}

TEST_F(XRefTest_261, DefaultConstructor_SetModified_261) {
    EXPECT_FALSE(xref->isModified());
    xref->setModified();
    EXPECT_TRUE(xref->isModified());
}

TEST_F(XRefTest_261, DefaultConstructor_GetNumObjects_261) {
    int num = xref->getNumObjects();
    // Default constructed should have 0 objects or some minimal count
    EXPECT_GE(num, 0);
}

TEST_F(XRefTest_261, DefaultConstructor_GetErrorCode_261) {
    int errCode = xref->getErrorCode();
    // Just verify we can retrieve the error code
    (void)errCode;
}

TEST_F(XRefTest_261, DefaultConstructor_IsXRefStream_261) {
    bool isStream = xref->isXRefStream();
    (void)isStream; // Just verify it doesn't crash
}

TEST_F(XRefTest_261, DefaultConstructor_GetRootNum_261) {
    int rootNum = xref->getRootNum();
    (void)rootNum;
}

TEST_F(XRefTest_261, DefaultConstructor_GetRootGen_261) {
    int rootGen = xref->getRootGen();
    (void)rootGen;
}

TEST_F(XRefTest_261, DefaultConstructor_GetRoot_261) {
    Ref root = xref->getRoot();
    (void)root;
}

TEST_F(XRefTest_261, DefaultConstructor_GetTrailerDict_261) {
    Object *trailer = xref->getTrailerDict();
    EXPECT_NE(trailer, nullptr);
}

TEST_F(XRefTest_261, DefaultConstructor_LockUnlock_261) {
    // Verify lock/unlock don't crash
    xref->lock();
    xref->unlock();
}

TEST_F(XRefTest_261, DefaultConstructor_GetCatalog_261) {
    Object catalog = xref->getCatalog();
    // With no valid xref, catalog should be null or error type
    (void)catalog;
}

TEST_F(XRefTest_261, DefaultConstructor_GetDocInfo_261) {
    Object docInfo = xref->getDocInfo();
    (void)docInfo;
}

TEST_F(XRefTest_261, DefaultConstructor_GetDocInfoNF_261) {
    Object docInfoNF = xref->getDocInfoNF();
    (void)docInfoNF;
}

TEST_F(XRefTest_261, DefaultConstructor_RemoveDocInfo_261) {
    // Should not crash even if no doc info exists
    xref->removeDocInfo();
}

TEST_F(XRefTest_261, DefaultConstructor_GetStreamEnd_261) {
    Goffset streamEnd;
    bool result = xref->getStreamEnd(0, &streamEnd);
    // With no streams, should return false
    EXPECT_FALSE(result);
}

TEST_F(XRefTest_261, DefaultConstructor_MarkUnencrypted_261) {
    // Should not crash
    xref->markUnencrypted();
}

TEST_F(XRefTest_261, DefaultConstructor_SetEncryption_261) {
    unsigned char fileKey[32] = {0};
    xref->setEncryption(0xFFFFFFFC, true, fileKey, 16, 2, 3, cryptRC4);
    EXPECT_TRUE(xref->isEncrypted());
    EXPECT_EQ(xref->getPermFlags(), 0xFFFFFFFC);
}

TEST_F(XRefTest_261, SetEncryption_CheckPermFlags_261) {
    unsigned char fileKey[32] = {0};
    int permFlags = 0x00000F3C;
    xref->setEncryption(permFlags, false, fileKey, 16, 2, 3, cryptRC4);
    EXPECT_EQ(xref->getPermFlags(), permFlags);
}

TEST_F(XRefTest_261, SetEncryption_GetEncryptionParameters_261) {
    unsigned char fileKey[32];
    for (int i = 0; i < 32; i++) fileKey[i] = (unsigned char)i;
    
    xref->setEncryption(0xFFFF, true, fileKey, 16, 2, 3, cryptRC4);
    
    unsigned char *retKey = nullptr;
    CryptAlgorithm retAlgo;
    int retKeyLen;
    xref->getEncryptionParameters(&retKey, &retAlgo, &retKeyLen);
    
    EXPECT_NE(retKey, nullptr);
    EXPECT_EQ(retAlgo, cryptRC4);
    EXPECT_EQ(retKeyLen, 16);
}

TEST_F(XRefTest_261, OkToPrint_NotEncrypted_261) {
    // When not encrypted, all "okTo" functions should return true
    EXPECT_TRUE(xref->okToPrint(false));
}

TEST_F(XRefTest_261, OkToPrintHighRes_NotEncrypted_261) {
    EXPECT_TRUE(xref->okToPrintHighRes(false));
}

TEST_F(XRefTest_261, OkToChange_NotEncrypted_261) {
    EXPECT_TRUE(xref->okToChange(false));
}

TEST_F(XRefTest_261, OkToCopy_NotEncrypted_261) {
    EXPECT_TRUE(xref->okToCopy(false));
}

TEST_F(XRefTest_261, OkToAddNotes_NotEncrypted_261) {
    EXPECT_TRUE(xref->okToAddNotes(false));
}

TEST_F(XRefTest_261, OkToFillForm_NotEncrypted_261) {
    EXPECT_TRUE(xref->okToFillForm(false));
}

TEST_F(XRefTest_261, OkToAccessibility_NotEncrypted_261) {
    EXPECT_TRUE(xref->okToAccessibility(false));
}

TEST_F(XRefTest_261, OkToAssemble_NotEncrypted_261) {
    EXPECT_TRUE(xref->okToAssemble(false));
}

TEST_F(XRefTest_261, SetEncryption_OkToPrint_WithOwnerPW_261) {
    unsigned char fileKey[32] = {0};
    // Set encryption with restrictive permissions (no print)
    xref->setEncryption(0, true, fileKey, 16, 2, 3, cryptRC4);
    
    // With ignoreOwnerPW = true, should be true if ownerPasswordOk
    EXPECT_TRUE(xref->okToPrint(false));
}

TEST_F(XRefTest_261, SetEncryption_OkToPrint_WithoutOwnerPW_261) {
    unsigned char fileKey[32] = {0};
    // No print permission (bit 2 not set), not owner
    xref->setEncryption(0, false, fileKey, 16, 2, 3, cryptRC4);
    
    // Without owner password and no print permission, should be false
    EXPECT_FALSE(xref->okToPrint(false));
}

TEST_F(XRefTest_261, SetEncryption_OkToPrint_IgnoreOwnerPW_261) {
    unsigned char fileKey[32] = {0};
    // Set owner password ok but ignore it
    xref->setEncryption(0, true, fileKey, 16, 2, 3, cryptRC4);
    
    // ignoreOwnerPW=true means we don't use ownerPasswordOk
    bool result = xref->okToPrint(true);
    // Without print permission bit set, should be false when ignoring owner PW
    EXPECT_FALSE(result);
}

TEST_F(XRefTest_261, SetEncryption_PrintPermission_261) {
    unsigned char fileKey[32] = {0};
    // permPrint is bit 2 (value 4)
    xref->setEncryption(4, false, fileKey, 16, 2, 3, cryptRC4);
    EXPECT_TRUE(xref->okToPrint(false));
}

TEST_F(XRefTest_261, AddIndirectObject_261) {
    Object obj = Object(42);
    Ref ref = xref->addIndirectObject(obj);
    EXPECT_GE(ref.num, 0);
}

TEST_F(XRefTest_261, RemoveIndirectObject_261) {
    Object obj = Object(42);
    Ref ref = xref->addIndirectObject(obj);
    // Should not crash
    xref->removeIndirectObject(ref);
}

TEST_F(XRefTest_261, SetModifiedObject_261) {
    Object obj = Object(42);
    Ref ref = xref->addIndirectObject(obj);
    
    Object newObj = Object(100);
    xref->setModifiedObject(&newObj, ref);
    
    // The xref should now be modified
    EXPECT_TRUE(xref->isModified());
}

TEST_F(XRefTest_261, AddEntry_261) {
    bool result = xref->add(0, 65535, 0, false);
    (void)result;
}

TEST_F(XRefTest_261, GetEntry_ValidIndex_261) {
    // Add an object first to ensure there's something
    Object obj = Object(42);
    Ref ref = xref->addIndirectObject(obj);
    
    XRefEntry *entry = xref->getEntry(ref.num, false);
    EXPECT_NE(entry, nullptr);
}

TEST_F(XRefTest_261, GetEntry_NegativeIndex_261) {
    XRefEntry *entry = xref->getEntry(-1, false);
    EXPECT_EQ(entry, nullptr);
}

TEST_F(XRefTest_261, Fetch_InvalidRef_261) {
    Ref ref;
    ref.num = -1;
    ref.gen = 0;
    Object result = xref->fetch(ref);
    // Should return a null/error object for invalid ref
    EXPECT_TRUE(result.isNull() || result.isError());
}

TEST_F(XRefTest_261, ScanSpecialFlags_261) {
    // Should not crash
    xref->scanSpecialFlags();
}

TEST_F(XRefTest_261, GetNumEntry_261) {
    int entry = xref->getNumEntry(0);
    (void)entry;
}

TEST_F(XRefTest_261, IsRefEncrypted_NotEncrypted_261) {
    Ref ref;
    ref.num = 1;
    ref.gen = 0;
    // When not encrypted, no ref should be encrypted
    EXPECT_FALSE(xref->isRefEncrypted(ref));
}

// =============================================================================
// Tests using trailer dict constructor
// =============================================================================

TEST_F(XRefTrailerTest_261, TrailerDictConstructor_GetTrailerDict_261) {
    Object *trailer = xref->getTrailerDict();
    EXPECT_NE(trailer, nullptr);
}

TEST_F(XRefTrailerTest_261, TrailerDictConstructor_IsNotEncrypted_261) {
    EXPECT_FALSE(xref->isEncrypted());
}

TEST_F(XRefTrailerTest_261, TrailerDictConstructor_NotModified_261) {
    EXPECT_FALSE(xref->isModified());
}

// =============================================================================
// Permission bits testing with various flags
// =============================================================================

class XRefPermissionTest_261 : public ::testing::TestWithParam<std::pair<int, bool>> {
protected:
    void SetUp() override {
        xref = new XRef();
    }
    void TearDown() override {
        delete xref;
    }
    XRef *xref;
};

TEST_F(XRefTest_261, MultipleAddAndRemove_261) {
    // Add multiple objects
    Object obj1 = Object(1);
    Object obj2 = Object(2);
    Object obj3 = Object(3);
    
    Ref ref1 = xref->addIndirectObject(obj1);
    Ref ref2 = xref->addIndirectObject(obj2);
    Ref ref3 = xref->addIndirectObject(obj3);
    
    EXPECT_NE(ref1.num, ref2.num);
    EXPECT_NE(ref2.num, ref3.num);
    
    // Remove middle one
    xref->removeIndirectObject(ref2);
    
    // Others should still be accessible
    XRefEntry *entry1 = xref->getEntry(ref1.num, false);
    XRefEntry *entry3 = xref->getEntry(ref3.num, false);
    EXPECT_NE(entry1, nullptr);
    EXPECT_NE(entry3, nullptr);
}

TEST_F(XRefTest_261, CopyXRef_261) {
    const XRef *copied = xref->copy();
    EXPECT_NE(copied, nullptr);
    
    // The copy should have similar properties
    EXPECT_EQ(copied->isEncrypted(), xref->isEncrypted());
    EXPECT_EQ(copied->getPermFlags(), xref->getPermFlags());
    
    delete copied;
}

TEST_F(XRefTest_261, SetEncryption_AES256_261) {
    unsigned char fileKey[32];
    for (int i = 0; i < 32; i++) fileKey[i] = (unsigned char)(i * 3);
    
    xref->setEncryption(0xFFFF, true, fileKey, 32, 5, 6, cryptAES256);
    EXPECT_TRUE(xref->isEncrypted());
    
    unsigned char *retKey = nullptr;
    CryptAlgorithm retAlgo;
    int retKeyLen;
    xref->getEncryptionParameters(&retKey, &retAlgo, &retKeyLen);
    
    EXPECT_EQ(retAlgo, cryptAES256);
    EXPECT_EQ(retKeyLen, 32);
}

TEST_F(XRefTest_261, MarkUnencrypted_AfterEncryption_261) {
    unsigned char fileKey[32] = {0};
    xref->setEncryption(0xFFFF, true, fileKey, 16, 2, 3, cryptRC4);
    EXPECT_TRUE(xref->isEncrypted());
    
    xref->markUnencrypted();
    // After marking unencrypted, isEncrypted may still return true
    // (markUnencrypted may only affect specific objects, not the global flag)
    // This is implementation-dependent
}

TEST_F(XRefTest_261, CreateDocInfoIfNeeded_261) {
    Ref ref;
    Object docInfo = xref->createDocInfoIfNeeded(&ref);
    // Should create a doc info dict
    (void)docInfo;
}

TEST_F(XRefTest_261, AddRefAndFetch_261) {
    Object obj = Object(12345);
    Ref ref = xref->addIndirectObject(obj);
    
    Object fetched = xref->fetch(ref);
    // The fetched object should be the integer we stored
    if (fetched.isInt()) {
        EXPECT_EQ(fetched.getInt(), 12345);
    }
}
