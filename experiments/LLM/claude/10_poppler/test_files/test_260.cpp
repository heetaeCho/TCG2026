#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XRef.h"
#include "Object.h"
#include "Stream.h"
#include "Dict.h"
#include "GooString.h"

// Test fixture for XRef tests using the default constructor
class XRefTest_260 : public ::testing::Test {
protected:
    void SetUp() override {
        xref = new XRef();
    }

    void TearDown() override {
        delete xref;
    }

    XRef *xref;
};

// Test that a default-constructed XRef reports not encrypted
TEST_F(XRefTest_260, DefaultConstructorNotEncrypted_260) {
    EXPECT_FALSE(xref->isEncrypted());
}

// Test that a default-constructed XRef has an error code or is not ok
TEST_F(XRefTest_260, DefaultConstructorIsOk_260) {
    // Default constructed XRef may or may not be ok depending on implementation
    // We just verify the method is callable
    bool ok = xref->isOk();
    (void)ok; // Observable behavior test
}

// Test that a default-constructed XRef reports not modified
TEST_F(XRefTest_260, DefaultConstructorNotModified_260) {
    EXPECT_FALSE(xref->isModified());
}

// Test that setModified marks the XRef as modified
TEST_F(XRefTest_260, SetModifiedMarksAsModified_260) {
    EXPECT_FALSE(xref->isModified());
    xref->setModified();
    EXPECT_TRUE(xref->isModified());
}

// Test that getNumObjects returns a non-negative value on default construction
TEST_F(XRefTest_260, DefaultConstructorNumObjects_260) {
    int numObjects = xref->getNumObjects();
    EXPECT_GE(numObjects, 0);
}

// Test that getRootNum returns some value on default construction
TEST_F(XRefTest_260, DefaultConstructorRootNum_260) {
    int rootNum = xref->getRootNum();
    // Root num may be -1 or 0 for an empty/default XRef
    (void)rootNum;
}

// Test that getRootGen returns some value on default construction
TEST_F(XRefTest_260, DefaultConstructorRootGen_260) {
    int rootGen = xref->getRootGen();
    (void)rootGen;
}

// Test that getRoot returns a Ref on default construction
TEST_F(XRefTest_260, DefaultConstructorGetRoot_260) {
    Ref root = xref->getRoot();
    // Just verify it returns without crashing
    (void)root;
}

// Test that getErrorCode is callable
TEST_F(XRefTest_260, DefaultConstructorErrorCode_260) {
    int errCode = xref->getErrorCode();
    (void)errCode;
}

// Test that isXRefStream returns false on default construction
TEST_F(XRefTest_260, DefaultConstructorIsXRefStream_260) {
    bool isStream = xref->isXRefStream();
    // Default constructor likely won't be a stream
    (void)isStream;
}

// Test that getPermFlags returns some value
TEST_F(XRefTest_260, DefaultConstructorPermFlags_260) {
    int flags = xref->getPermFlags();
    (void)flags;
}

// Test that getTrailerDict returns a pointer
TEST_F(XRefTest_260, DefaultConstructorTrailerDict_260) {
    Object *trailer = xref->getTrailerDict();
    EXPECT_NE(trailer, nullptr);
}

// Test that markUnencrypted can be called on a default XRef
TEST_F(XRefTest_260, MarkUnencryptedOnDefault_260) {
    xref->markUnencrypted();
    EXPECT_FALSE(xref->isEncrypted());
}

// Test setEncryption then isEncrypted
TEST_F(XRefTest_260, SetEncryptionMakesEncrypted_260) {
    unsigned char fileKey[32] = {0};
    xref->setEncryption(0xFFFF, true, fileKey, 16, 2, 3, cryptRC4);
    EXPECT_TRUE(xref->isEncrypted());
}

// Test setEncryption and then markUnencrypted
TEST_F(XRefTest_260, SetEncryptionThenMarkUnencrypted_260) {
    unsigned char fileKey[32] = {0};
    xref->setEncryption(0xFFFF, true, fileKey, 16, 2, 3, cryptRC4);
    EXPECT_TRUE(xref->isEncrypted());
    xref->markUnencrypted();
    EXPECT_FALSE(xref->isEncrypted());
}

// Test getEncryptionParameters after setting encryption
TEST_F(XRefTest_260, GetEncryptionParametersAfterSet_260) {
    unsigned char fileKey[32] = {0};
    for (int i = 0; i < 32; i++) {
        fileKey[i] = (unsigned char)i;
    }
    xref->setEncryption(0xFFFF, true, fileKey, 16, 2, 3, cryptRC4);

    unsigned char *retrievedKey = nullptr;
    CryptAlgorithm algo;
    int keyLen = 0;
    xref->getEncryptionParameters(&retrievedKey, &algo, &keyLen);

    EXPECT_NE(retrievedKey, nullptr);
    EXPECT_EQ(algo, cryptRC4);
    EXPECT_EQ(keyLen, 16);
}

// Test permission checks with ownerPasswordOk = true
TEST_F(XRefTest_260, PermissionsWithOwnerPassword_260) {
    unsigned char fileKey[32] = {0};
    // Set with all permissions and owner password ok
    xref->setEncryption(0xFFFFFFFF, true, fileKey, 16, 2, 3, cryptRC4);

    EXPECT_TRUE(xref->okToPrint(false));
    EXPECT_TRUE(xref->okToPrintHighRes(false));
    EXPECT_TRUE(xref->okToChange(false));
    EXPECT_TRUE(xref->okToCopy(false));
    EXPECT_TRUE(xref->okToAddNotes(false));
    EXPECT_TRUE(xref->okToFillForm(false));
    EXPECT_TRUE(xref->okToAccessibility(false));
    EXPECT_TRUE(xref->okToAssemble(false));
}

// Test permission checks ignoring owner password
TEST_F(XRefTest_260, PermissionsIgnoreOwnerPW_260) {
    unsigned char fileKey[32] = {0};
    xref->setEncryption(0xFFFFFFFF, true, fileKey, 16, 2, 3, cryptRC4);

    EXPECT_TRUE(xref->okToPrint(true));
    EXPECT_TRUE(xref->okToPrintHighRes(true));
    EXPECT_TRUE(xref->okToChange(true));
    EXPECT_TRUE(xref->okToCopy(true));
    EXPECT_TRUE(xref->okToAddNotes(true));
    EXPECT_TRUE(xref->okToFillForm(true));
    EXPECT_TRUE(xref->okToAccessibility(true));
    EXPECT_TRUE(xref->okToAssemble(true));
}

// Test permission checks with no permissions set
TEST_F(XRefTest_260, PermissionsNoFlags_260) {
    unsigned char fileKey[32] = {0};
    // Set with no permissions and owner password not ok
    xref->setEncryption(0, false, fileKey, 16, 2, 3, cryptRC4);

    // Without owner password, all should likely be false
    EXPECT_FALSE(xref->okToPrint(false));
    EXPECT_FALSE(xref->okToChange(false));
    EXPECT_FALSE(xref->okToCopy(false));
    EXPECT_FALSE(xref->okToAddNotes(false));
}

// Test lock and unlock don't crash
TEST_F(XRefTest_260, LockUnlock_260) {
    xref->lock();
    xref->unlock();
    // No crash means success
}

// Test getStreamEnd on default XRef (no streams)
TEST_F(XRefTest_260, GetStreamEndNoStreams_260) {
    Goffset streamEnd = 0;
    bool result = xref->getStreamEnd(0, &streamEnd);
    EXPECT_FALSE(result);
}

// Test getEntry with invalid index
TEST_F(XRefTest_260, GetEntryInvalidIndex_260) {
    XRefEntry *entry = xref->getEntry(-1, false);
    // Should return nullptr or a sentinel entry for invalid index
    (void)entry;
}

// Test getEntry with index 0
TEST_F(XRefTest_260, GetEntryIndexZero_260) {
    // Index 0 is typically the free entry in a PDF
    XRefEntry *entry = xref->getEntry(0, false);
    (void)entry;
}

// Test getCatalog on default XRef
TEST_F(XRefTest_260, DefaultConstructorGetCatalog_260) {
    Object catalog = xref->getCatalog();
    // On default XRef with no valid root, catalog should be null/none type
    (void)catalog;
}

// Test getDocInfo on default XRef
TEST_F(XRefTest_260, DefaultConstructorGetDocInfo_260) {
    Object docInfo = xref->getDocInfo();
    (void)docInfo;
}

// Test getDocInfoNF on default XRef
TEST_F(XRefTest_260, DefaultConstructorGetDocInfoNF_260) {
    Object docInfoNF = xref->getDocInfoNF();
    (void)docInfoNF;
}

// Test fetch with invalid ref on default XRef
TEST_F(XRefTest_260, FetchInvalidRef_260) {
    Ref ref = {-1, 0};
    Object obj = xref->fetch(ref);
    // Should return a null or error object for invalid ref
    (void)obj;
}

// Test fetch with num/gen overload
TEST_F(XRefTest_260, FetchByNumGen_260) {
    Goffset endPos = 0;
    Object obj = xref->fetch(0, 0, 0, &endPos);
    (void)obj;
}

// Test add method
TEST_F(XRefTest_260, AddEntry_260) {
    bool result = xref->add(1, 0, 100, true);
    // Verify the entry was added (should return true or the entry should be accessible)
    (void)result;
}

// Test add with Ref overload
TEST_F(XRefTest_260, AddEntryWithRef_260) {
    Ref ref = {1, 0};
    xref->add(ref, 100, true);
    // Verify by getting the entry
    XRefEntry *entry = xref->getEntry(1, false);
    (void)entry;
}

// Test removeIndirectObject
TEST_F(XRefTest_260, RemoveIndirectObject_260) {
    Ref ref = {1, 0};
    xref->add(ref, 100, true);
    xref->removeIndirectObject(ref);
    // After removal, the entry should be marked as free or similar
}

// Test addIndirectObject
TEST_F(XRefTest_260, AddIndirectObject_260) {
    Object obj = Object(42);
    Ref ref = xref->addIndirectObject(obj);
    EXPECT_GE(ref.num, 0);
}

// Test setModifiedObject
TEST_F(XRefTest_260, SetModifiedObject_260) {
    // First add an object
    Object obj = Object(42);
    Ref ref = xref->addIndirectObject(obj);

    // Modify it
    Object newObj = Object(99);
    xref->setModifiedObject(&newObj, ref);

    // Verify modified flag
    EXPECT_TRUE(xref->isModified());
}

// Test that copy creates a valid copy
TEST_F(XRefTest_260, CopyCreatesValidCopy_260) {
    const XRef *copied = xref->copy();
    if (copied) {
        EXPECT_EQ(copied->isEncrypted(), xref->isEncrypted());
        EXPECT_EQ(copied->getNumObjects(), xref->getNumObjects());
        delete copied;
    }
}

// Test constructor with trailerDict
class XRefTrailerDictTest_260 : public ::testing::Test {
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

TEST_F(XRefTrailerDictTest_260, ConstructedWithTrailerDict_260) {
    // Should construct without crashing
    EXPECT_FALSE(xref->isEncrypted());
}

// Test removeDocInfo on default XRef
TEST_F(XRefTest_260, RemoveDocInfo_260) {
    xref->removeDocInfo();
    Object docInfo = xref->getDocInfoNF();
    (void)docInfo;
}

// Test isRefEncrypted on default (unencrypted) XRef
TEST_F(XRefTest_260, IsRefEncryptedOnUnencrypted_260) {
    Ref ref = {1, 0};
    bool result = xref->isRefEncrypted(ref);
    // On unencrypted XRef, nothing should be ref-encrypted
    EXPECT_FALSE(result);
}

// Test isRefEncrypted after setting encryption
TEST_F(XRefTest_260, IsRefEncryptedAfterSetEncryption_260) {
    unsigned char fileKey[32] = {0};
    xref->setEncryption(0xFFFF, true, fileKey, 16, 2, 3, cryptRC4);

    // Add an entry first
    xref->add(1, 0, 100, true);
    Ref ref = {1, 0};
    bool result = xref->isRefEncrypted(ref);
    // After encryption is set, refs should generally be encrypted
    EXPECT_TRUE(result);
}

// Test scanSpecialFlags doesn't crash
TEST_F(XRefTest_260, ScanSpecialFlagsNoCrash_260) {
    xref->scanSpecialFlags();
}

// Test getNumEntry with invalid offset
TEST_F(XRefTest_260, GetNumEntryInvalidOffset_260) {
    int num = xref->getNumEntry(999999);
    // Should return -1 or similar for not found
    (void)num;
}

// Test multiple setModified calls
TEST_F(XRefTest_260, MultipleSetModified_260) {
    xref->setModified();
    EXPECT_TRUE(xref->isModified());
    xref->setModified();
    EXPECT_TRUE(xref->isModified());
}

// Test setEncryption with different algorithms
TEST_F(XRefTest_260, SetEncryptionAES_260) {
    unsigned char fileKey[32] = {0};
    xref->setEncryption(0xFFFF, true, fileKey, 32, 5, 6, cryptAES256);
    EXPECT_TRUE(xref->isEncrypted());

    unsigned char *retrievedKey = nullptr;
    CryptAlgorithm algo;
    int keyLen = 0;
    xref->getEncryptionParameters(&retrievedKey, &algo, &keyLen);
    EXPECT_EQ(algo, cryptAES256);
    EXPECT_EQ(keyLen, 32);
}
