#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FileSpec.h"
#include "Object.h"
#include "Stream.h"
#include "GooString.h"
#include "Dict.h"
#include "PDFDoc.h"

class EmbFileTest_1127 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper to create a minimal embedded file stream Object
static Object createMinimalEmbFileStream() {
    // Create a null/empty object as a minimal stream representation
    return Object(objNull);
}

// Test that constructing EmbFile with a null object doesn't crash
TEST_F(EmbFileTest_1127, ConstructWithNullObject_1127) {
    Object obj(objNull);
    EmbFile embFile(std::move(obj));
    // Should be constructible without crashing
}

// Test that modDate returns nullptr when no mod date is set
TEST_F(EmbFileTest_1127, ModDateReturnsNullWhenNotSet_1127) {
    Object obj(objNull);
    EmbFile embFile(std::move(obj));
    const GooString *modDate = embFile.modDate();
    // With a null/invalid stream, modDate should be nullptr
    EXPECT_EQ(modDate, nullptr);
}

// Test that createDate returns nullptr when no create date is set
TEST_F(EmbFileTest_1127, CreateDateReturnsNullWhenNotSet_1127) {
    Object obj(objNull);
    EmbFile embFile(std::move(obj));
    const GooString *createDate = embFile.createDate();
    EXPECT_EQ(createDate, nullptr);
}

// Test that checksum returns nullptr when no checksum is set
TEST_F(EmbFileTest_1127, ChecksumReturnsNullWhenNotSet_1127) {
    Object obj(objNull);
    EmbFile embFile(std::move(obj));
    const GooString *checksum = embFile.checksum();
    EXPECT_EQ(checksum, nullptr);
}

// Test that mimeType returns nullptr when no mime type is set
TEST_F(EmbFileTest_1127, MimeTypeReturnsNullWhenNotSet_1127) {
    Object obj(objNull);
    EmbFile embFile(std::move(obj));
    const GooString *mimeType = embFile.mimeType();
    EXPECT_EQ(mimeType, nullptr);
}

// Test that size returns a value (likely -1 or 0 for invalid stream)
TEST_F(EmbFileTest_1127, SizeForNullObject_1127) {
    Object obj(objNull);
    EmbFile embFile(std::move(obj));
    int size = embFile.size();
    // For a null/invalid stream, size should be non-positive or -1
    EXPECT_LE(size, 0);
}

// Test that isOk returns false for a null object
TEST_F(EmbFileTest_1127, IsOkReturnsFalseForNullObject_1127) {
    Object obj(objNull);
    EmbFile embFile(std::move(obj));
    EXPECT_FALSE(embFile.isOk());
}

// Test that streamObject returns a non-null pointer (it's always valid as member)
TEST_F(EmbFileTest_1127, StreamObjectReturnsNonNull_1127) {
    Object obj(objNull);
    EmbFile embFile(std::move(obj));
    Object *streamObj = embFile.streamObject();
    EXPECT_NE(streamObj, nullptr);
}

// Test that stream returns nullptr for invalid embedded file
TEST_F(EmbFileTest_1127, StreamReturnsNullForInvalidObject_1127) {
    Object obj(objNull);
    EmbFile embFile(std::move(obj));
    Stream *s = embFile.stream();
    // For a null object, stream should be nullptr
    EXPECT_EQ(s, nullptr);
}

// Test that save returns false for invalid embedded file
TEST_F(EmbFileTest_1127, SaveReturnsFalseForInvalidObject_1127) {
    Object obj(objNull);
    EmbFile embFile(std::move(obj));
    bool result = embFile.save("/tmp/test_embfile_1127_nonexistent.bin");
    EXPECT_FALSE(result);
}

// Test that copy constructor is deleted (compile-time check - we verify class design)
TEST_F(EmbFileTest_1127, CopyConstructorDeleted_1127) {
    // This is a compile-time check; if it compiles, the constraint holds
    EXPECT_FALSE(std::is_copy_constructible<EmbFile>::value);
}

// Test that copy assignment is deleted
TEST_F(EmbFileTest_1127, CopyAssignmentDeleted_1127) {
    EXPECT_FALSE(std::is_copy_assignable<EmbFile>::value);
}

// Test multiple calls to modDate return consistent results
TEST_F(EmbFileTest_1127, ModDateConsistentAcrossCalls_1127) {
    Object obj(objNull);
    EmbFile embFile(std::move(obj));
    const GooString *modDate1 = embFile.modDate();
    const GooString *modDate2 = embFile.modDate();
    EXPECT_EQ(modDate1, modDate2);
}

// Test multiple calls to createDate return consistent results
TEST_F(EmbFileTest_1127, CreateDateConsistentAcrossCalls_1127) {
    Object obj(objNull);
    EmbFile embFile(std::move(obj));
    const GooString *createDate1 = embFile.createDate();
    const GooString *createDate2 = embFile.createDate();
    EXPECT_EQ(createDate1, createDate2);
}

// Test save with empty path
TEST_F(EmbFileTest_1127, SaveWithEmptyPath_1127) {
    Object obj(objNull);
    EmbFile embFile(std::move(obj));
    bool result = embFile.save("");
    EXPECT_FALSE(result);
}
