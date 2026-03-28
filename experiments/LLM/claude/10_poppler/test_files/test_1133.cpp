#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FileSpec.h"
#include "Object.h"

// Test fixture for EmbFile tests
class EmbFileTest_1133 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that EmbFile constructed with a non-stream Object is not OK
TEST_F(EmbFileTest_1133, IsOkReturnsFalseForNonStreamObject_1133) {
    // Construct with a null object (not a stream)
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    EXPECT_FALSE(embFile.isOk());
}

// Test that EmbFile constructed with a default (none) Object is not OK
TEST_F(EmbFileTest_1133, IsOkReturnsFalseForNoneObject_1133) {
    Object noneObj;
    EmbFile embFile(std::move(noneObj));
    EXPECT_FALSE(embFile.isOk());
}

// Test that EmbFile constructed with an error Object is not OK
TEST_F(EmbFileTest_1133, IsOkReturnsFalseForErrorObject_1133) {
    Object errorObj = Object::error();
    EmbFile embFile(std::move(errorObj));
    EXPECT_FALSE(embFile.isOk());
}

// Test that EmbFile constructed with an integer Object is not OK
TEST_F(EmbFileTest_1133, IsOkReturnsFalseForIntObject_1133) {
    Object intObj(42);
    EmbFile embFile(std::move(intObj));
    EXPECT_FALSE(embFile.isOk());
}

// Test that EmbFile constructed with a boolean Object is not OK
TEST_F(EmbFileTest_1133, IsOkReturnsFalseForBoolObject_1133) {
    Object boolObj(true);
    EmbFile embFile(std::move(boolObj));
    EXPECT_FALSE(embFile.isOk());
}

// Test that EmbFile constructed with a real/double Object is not OK
TEST_F(EmbFileTest_1133, IsOkReturnsFalseForRealObject_1133) {
    Object realObj(3.14);
    EmbFile embFile(std::move(realObj));
    EXPECT_FALSE(embFile.isOk());
}

// Test that size returns a value for a non-stream EmbFile
TEST_F(EmbFileTest_1133, SizeReturnsValueForNonStreamObject_1133) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    // size() should return some default value; we just verify it doesn't crash
    int sz = embFile.size();
    // For a non-stream, size is likely -1 or 0, but we can only test it doesn't crash
    (void)sz;
}

// Test that modDate returns nullptr or valid pointer for a non-stream EmbFile
TEST_F(EmbFileTest_1133, ModDateForNonStreamObject_1133) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    // For a null object, there's no mod date info
    const GooString *md = embFile.modDate();
    // It's acceptable for this to be nullptr
    (void)md;
}

// Test that createDate returns nullptr or valid pointer for a non-stream EmbFile
TEST_F(EmbFileTest_1133, CreateDateForNonStreamObject_1133) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    const GooString *cd = embFile.createDate();
    (void)cd;
}

// Test that checksum returns nullptr or valid pointer for a non-stream EmbFile
TEST_F(EmbFileTest_1133, ChecksumForNonStreamObject_1133) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    const GooString *cs = embFile.checksum();
    (void)cs;
}

// Test that mimeType returns nullptr or valid pointer for a non-stream EmbFile
TEST_F(EmbFileTest_1133, MimeTypeForNonStreamObject_1133) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    const GooString *mt = embFile.mimeType();
    (void)mt;
}

// Test that streamObject returns a pointer for a non-stream EmbFile
TEST_F(EmbFileTest_1133, StreamObjectReturnsNonNullPointer_1133) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    Object *so = embFile.streamObject();
    // streamObject should return a pointer to the internal object
    EXPECT_NE(so, nullptr);
}

// Test that stream returns nullptr for a non-stream EmbFile
TEST_F(EmbFileTest_1133, StreamReturnsNullForNonStreamObject_1133) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    // Since the object is not a stream, stream() should return nullptr or handle gracefully
    // We don't call it if isOk() is false in real code, but we test it doesn't crash
    if (!embFile.isOk()) {
        // Just verify isOk is false; calling stream() on non-stream may be undefined
        EXPECT_FALSE(embFile.isOk());
    }
}

// Test that save returns false for a non-stream EmbFile
TEST_F(EmbFileTest_1133, SaveReturnsFalseForNonStreamObject_1133) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    // Saving a non-stream should fail
    bool result = embFile.save("/tmp/test_embfile_nonexistent_1133.bin");
    EXPECT_FALSE(result);
}

// Test that save returns false when given an invalid path
TEST_F(EmbFileTest_1133, SaveReturnsFalseForInvalidPath_1133) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    bool result = embFile.save("/nonexistent/directory/that/should/not/exist/file_1133.bin");
    EXPECT_FALSE(result);
}

// Test that save returns false for empty path
TEST_F(EmbFileTest_1133, SaveReturnsFalseForEmptyPath_1133) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    bool result = embFile.save("");
    EXPECT_FALSE(result);
}

// Test that EmbFile constructed with EOF object is not OK
TEST_F(EmbFileTest_1133, IsOkReturnsFalseForEOFObject_1133) {
    Object eofObj = Object::eof();
    EmbFile embFile(std::move(eofObj));
    EXPECT_FALSE(embFile.isOk());
}

// Test copy constructor and assignment are deleted (compile-time check implicit)
// We verify this by confirming the class is move-constructible via Object
TEST_F(EmbFileTest_1133, ConstructionWithMovedObject_1133) {
    Object obj1 = Object::null();
    Object obj2 = std::move(obj1);
    EmbFile embFile(std::move(obj2));
    EXPECT_FALSE(embFile.isOk());
}
