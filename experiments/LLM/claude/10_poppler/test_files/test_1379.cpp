#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QString>

// We need to test the Poppler::setNSSDir function
// Include the necessary headers
#include "poppler-form.h"

// If the header doesn't directly expose setNSSDir, we declare it
namespace Poppler {
    void setNSSDir(const QString &path);
}

class SetNSSDirTest_1379 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that calling setNSSDir with an empty string does not crash
// and effectively is a no-op (the function returns early for empty paths)
TEST_F(SetNSSDirTest_1379, EmptyStringDoesNotCrash_1379) {
    EXPECT_NO_THROW(Poppler::setNSSDir(QString()));
}

// Test that calling setNSSDir with an empty QString("") does not crash
TEST_F(SetNSSDirTest_1379, EmptyQStringLiteralDoesNotCrash_1379) {
    EXPECT_NO_THROW(Poppler::setNSSDir(QString("")));
}

// Test that calling setNSSDir with a valid path does not crash
TEST_F(SetNSSDirTest_1379, ValidPathDoesNotCrash_1379) {
    EXPECT_NO_THROW(Poppler::setNSSDir(QString("/tmp/nss_test_dir")));
}

// Test that calling setNSSDir with a path containing special characters does not crash
TEST_F(SetNSSDirTest_1379, SpecialCharactersPathDoesNotCrash_1379) {
    EXPECT_NO_THROW(Poppler::setNSSDir(QString("/tmp/nss dir with spaces/and-dashes")));
}

// Test that calling setNSSDir with a unicode path does not crash
TEST_F(SetNSSDirTest_1379, UnicodePathDoesNotCrash_1379) {
    EXPECT_NO_THROW(Poppler::setNSSDir(QString::fromUtf8("/tmp/nss_ünîcödé_dir")));
}

// Test that calling setNSSDir with a very long path does not crash
TEST_F(SetNSSDirTest_1379, VeryLongPathDoesNotCrash_1379) {
    QString longPath = QString("/tmp/") + QString(4096, QChar('a'));
    EXPECT_NO_THROW(Poppler::setNSSDir(longPath));
}

// Test that calling setNSSDir multiple times does not crash
TEST_F(SetNSSDirTest_1379, MultipleCallsDoNotCrash_1379) {
    EXPECT_NO_THROW(Poppler::setNSSDir(QString("/tmp/dir1")));
    EXPECT_NO_THROW(Poppler::setNSSDir(QString("/tmp/dir2")));
    EXPECT_NO_THROW(Poppler::setNSSDir(QString("/tmp/dir3")));
}

// Test calling setNSSDir with a null QString
TEST_F(SetNSSDirTest_1379, NullQStringDoesNotCrash_1379) {
    QString nullStr;
    ASSERT_TRUE(nullStr.isEmpty());
    EXPECT_NO_THROW(Poppler::setNSSDir(nullStr));
}

// Test that calling setNSSDir with path containing only whitespace does not crash
// Note: whitespace-only string is NOT empty, so it should attempt to set the dir
TEST_F(SetNSSDirTest_1379, WhitespaceOnlyPathDoesNotCrash_1379) {
    EXPECT_NO_THROW(Poppler::setNSSDir(QString("   ")));
}

// Test with a relative path
TEST_F(SetNSSDirTest_1379, RelativePathDoesNotCrash_1379) {
    EXPECT_NO_THROW(Poppler::setNSSDir(QString("relative/path/to/nss")));
}

// Test with path containing backslashes (Windows-style)
TEST_F(SetNSSDirTest_1379, WindowsStylePathDoesNotCrash_1379) {
    EXPECT_NO_THROW(Poppler::setNSSDir(QString("C:\\Users\\test\\nss_dir")));
}
