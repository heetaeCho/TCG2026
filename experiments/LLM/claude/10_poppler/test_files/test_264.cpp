#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XRef.h"
#include "Object.h"

// Test fixture for XRef default constructor tests
class XRefTest_264 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor creates an XRef object
TEST_F(XRefTest_264, DefaultConstructor_264) {
    XRef xref;
    // Default constructed XRef should have some initial state
    // We can check observable properties
    EXPECT_EQ(xref.getNumObjects(), 0);
    EXPECT_FALSE(xref.isEncrypted());
    EXPECT_FALSE(xref.isModified());
}

// Test getRootGen returns an integer value
TEST_F(XRefTest_264, GetRootGenDefault_264) {
    XRef xref;
    int rootGen = xref.getRootGen();
    // Default should be some initial value (likely 0 or -1)
    EXPECT_GE(rootGen, -1);
}

// Test getRootNum returns an integer value
TEST_F(XRefTest_264, GetRootNumDefault_264) {
    XRef xref;
    int rootNum = xref.getRootNum();
    EXPECT_GE(rootNum, -1);
}

// Test getRoot returns a Ref
TEST_F(XRefTest_264, GetRootDefault_264) {
    XRef xref;
    Ref root = xref.getRoot();
    EXPECT_EQ(root.num, xref.getRootNum());
    EXPECT_EQ(root.gen, xref.getRootGen());
}

// Test isOk on default constructed XRef
TEST_F(XRefTest_264, IsOkDefault_264) {
    XRef xref;
    // A default constructed XRef without a stream may not be "ok"
    // Just verify it returns a boolean without crashing
    bool ok = xref.isOk();
    (void)ok; // We just verify it doesn't crash
}

// Test getErrorCode on default constructed XRef
TEST_F(XRefTest_264, GetErrorCodeDefault_264) {
    XRef xref;
    int errCode = xref.getErrorCode();
    // Error code should be retrievable
    (void)errCode;
}

// Test isEncrypted on default constructed XRef
TEST_F(XRefTest_264, IsEncryptedDefault_264) {
    XRef xref;
    EXPECT_FALSE(xref.isEncrypted());
}

// Test isModified and setModified
TEST_F(XRefTest_264, SetModifiedChangesState_264) {
    XRef xref;
    EXPECT_FALSE(xref.isModified());
    xref.setModified();
    EXPECT_TRUE(xref.isModified());
}

// Test isXRefStream on default constructed XRef
TEST_F(XRefTest_264, IsXRefStreamDefault_264) {
    XRef xref;
    bool isStream = xref.isXRefStream();
    // Default should not be an xref stream
    EXPECT_FALSE(isStream);
}

// Test getNumObjects on default constructed XRef
TEST_F(XRefTest_264, GetNumObjectsDefault_264) {
    XRef xref;
    int numObjects = xref.getNumObjects();
    EXPECT_GE(numObjects, 0);
}

// Test getPermFlags on default constructed XRef
TEST_F(XRefTest_264, GetPermFlagsDefault_264) {
    XRef xref;
    int permFlags = xref.getPermFlags();
    (void)permFlags;
}

// Test getTrailerDict returns non-null pointer
TEST_F(XRefTest_264, GetTrailerDictDefault_264) {
    XRef xref;
    Object *trailerDict = xref.getTrailerDict();
    EXPECT_NE(trailerDict, nullptr);
}

// Test that setModified can be called multiple times
TEST_F(XRefTest_264, SetModifiedMultipleTimes_264) {
    XRef xref;
    EXPECT_FALSE(xref.isModified());
    xref.setModified();
    EXPECT_TRUE(xref.isModified());
    xref.setModified();
    EXPECT_TRUE(xref.isModified());
}

// Test constructing XRef with a trailerDict object
TEST_F(XRefTest_264, ConstructWithTrailerDict_264) {
    Object trailerDict;
    XRef xref(&trailerDict);
    // Should be constructible without crashing
    EXPECT_NE(xref.getTrailerDict(), nullptr);
}

// Test lock and unlock don't crash
TEST_F(XRefTest_264, LockUnlock_264) {
    XRef xref;
    xref.lock();
    xref.unlock();
    // Just verifying these don't crash or deadlock
}

// Test that copy-constructor is deleted (compile-time check is implicit)
// We verify the class is usable after basic operations
TEST_F(XRefTest_264, BasicOperationsAfterConstruction_264) {
    XRef xref;
    // Perform several operations and ensure consistent state
    int numObj = xref.getNumObjects();
    int rootNum = xref.getRootNum();
    int rootGen = xref.getRootGen();
    bool encrypted = xref.isEncrypted();
    bool modified = xref.isModified();

    EXPECT_GE(numObj, 0);
    EXPECT_FALSE(modified);
    
    // Call again to verify consistency
    EXPECT_EQ(xref.getNumObjects(), numObj);
    EXPECT_EQ(xref.getRootNum(), rootNum);
    EXPECT_EQ(xref.getRootGen(), rootGen);
    EXPECT_EQ(xref.isEncrypted(), encrypted);
}

// Test getEntry with invalid index
TEST_F(XRefTest_264, GetEntryInvalidIndex_264) {
    XRef xref;
    // Requesting entry with negative index or out-of-range
    XRefEntry *entry = xref.getEntry(-1, false);
    // Should handle gracefully (likely returns nullptr or a special entry)
    (void)entry;
}

// Test getEntry with zero index on empty XRef
TEST_F(XRefTest_264, GetEntryZeroIndex_264) {
    XRef xref;
    if (xref.getNumObjects() > 0) {
        XRefEntry *entry = xref.getEntry(0, false);
        (void)entry;
    }
}

// Test markUnencrypted on default XRef
TEST_F(XRefTest_264, MarkUnencryptedDefault_264) {
    XRef xref;
    xref.markUnencrypted();
    EXPECT_FALSE(xref.isEncrypted());
}

// Test permission checks on default (unencrypted) XRef
TEST_F(XRefTest_264, OkToPrintDefault_264) {
    XRef xref;
    bool canPrint = xref.okToPrint(false);
    EXPECT_TRUE(canPrint);
}

TEST_F(XRefTest_264, OkToPrintHighResDefault_264) {
    XRef xref;
    bool canPrintHighRes = xref.okToPrintHighRes(false);
    EXPECT_TRUE(canPrintHighRes);
}

TEST_F(XRefTest_264, OkToChangeDefault_264) {
    XRef xref;
    bool canChange = xref.okToChange(false);
    EXPECT_TRUE(canChange);
}

TEST_F(XRefTest_264, OkToCopyDefault_264) {
    XRef xref;
    bool canCopy = xref.okToCopy(false);
    EXPECT_TRUE(canCopy);
}

TEST_F(XRefTest_264, OkToAddNotesDefault_264) {
    XRef xref;
    bool canAddNotes = xref.okToAddNotes(false);
    EXPECT_TRUE(canAddNotes);
}

TEST_F(XRefTest_264, OkToFillFormDefault_264) {
    XRef xref;
    bool canFillForm = xref.okToFillForm(false);
    EXPECT_TRUE(canFillForm);
}

TEST_F(XRefTest_264, OkToAccessibilityDefault_264) {
    XRef xref;
    bool canAccess = xref.okToAccessibility(false);
    EXPECT_TRUE(canAccess);
}

TEST_F(XRefTest_264, OkToAssembleDefault_264) {
    XRef xref;
    bool canAssemble = xref.okToAssemble(false);
    EXPECT_TRUE(canAssemble);
}

// Test permission checks with ignoreOwnerPW = true
TEST_F(XRefTest_264, OkToPrintIgnoreOwner_264) {
    XRef xref;
    bool canPrint = xref.okToPrint(true);
    EXPECT_TRUE(canPrint);
}

TEST_F(XRefTest_264, OkToCopyIgnoreOwner_264) {
    XRef xref;
    bool canCopy = xref.okToCopy(true);
    EXPECT_TRUE(canCopy);
}

// Test getStreamEnd with invalid input
TEST_F(XRefTest_264, GetStreamEndInvalid_264) {
    XRef xref;
    Goffset streamEnd;
    bool result = xref.getStreamEnd(0, &streamEnd);
    // On default XRef with no streams, this should return false
    EXPECT_FALSE(result);
}

// Test removeDocInfo doesn't crash on default XRef
TEST_F(XRefTest_264, RemoveDocInfoDefault_264) {
    XRef xref;
    xref.removeDocInfo();
    // Should not crash
}

// Test getCatalog on default XRef
TEST_F(XRefTest_264, GetCatalogDefault_264) {
    XRef xref;
    Object catalog = xref.getCatalog();
    // On a default XRef, catalog may be null/none type
    (void)catalog;
}

// Test getDocInfo on default XRef
TEST_F(XRefTest_264, GetDocInfoDefault_264) {
    XRef xref;
    Object docInfo = xref.getDocInfo();
    (void)docInfo;
}

// Test getDocInfoNF on default XRef
TEST_F(XRefTest_264, GetDocInfoNFDefault_264) {
    XRef xref;
    Object docInfoNF = xref.getDocInfoNF();
    (void)docInfoNF;
}

// Test removeIndirectObject on default XRef  
TEST_F(XRefTest_264, RemoveIndirectObjectDefault_264) {
    XRef xref;
    Ref r;
    r.num = 0;
    r.gen = 0;
    xref.removeIndirectObject(r);
    // Should not crash
}

// Test isRefEncrypted on unencrypted XRef
TEST_F(XRefTest_264, IsRefEncryptedOnUnencrypted_264) {
    XRef xref;
    Ref r;
    r.num = 1;
    r.gen = 0;
    bool encrypted = xref.isRefEncrypted(r);
    EXPECT_FALSE(encrypted);
}
