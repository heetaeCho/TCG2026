#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GooString.h"  // Assuming GooString is defined in this header

// Mock class for external dependencies if needed
class MockGooString : public GooString {
public:
    MOCK_METHOD(const char*, c_str, (), (const, override));
    MOCK_METHOD(void, erase, (size_t pos, size_t len), (override));
    MOCK_METHOD(void, append, (const char* str), (override));
    MOCK_METHOD(size_t, size, (), (const, override));
};

TEST_F(ReplaceSuffixTest_1984, ReplaceSuffixWithSuffixA_1984) {
    GooString path("example.txt");
    const char* suffixA = ".txt";
    const char* suffixB = ".pdf";

    // Call the replaceSuffix function
    replaceSuffix(&path, suffixA, suffixB);

    // Test the result
    EXPECT_EQ(path.toStr(), "example.pdf");
}

TEST_F(ReplaceSuffixTest_1984, ReplaceSuffixWithSuffixB_1984) {
    GooString path("example.pdf");
    const char* suffixA = ".txt";
    const char* suffixB = ".pdf";

    // Call the replaceSuffix function
    replaceSuffix(&path, suffixA, suffixB);

    // Test the result
    EXPECT_EQ(path.toStr(), "example.txt");
}

TEST_F(ReplaceSuffixTest_1984, NoChangeWhenSuffixDoesNotMatch_1984) {
    GooString path("example.doc");
    const char* suffixA = ".txt";
    const char* suffixB = ".pdf";

    // Call the replaceSuffix function
    replaceSuffix(&path, suffixA, suffixB);

    // Test that the path remains unchanged
    EXPECT_EQ(path.toStr(), "example.doc");
}

TEST_F(ReplaceSuffixTest_1984, CaseInsensitiveSuffixReplacement_1984) {
    GooString path("example.TXT");
    const char* suffixA = ".txt";
    const char* suffixB = ".pdf";

    // Call the replaceSuffix function
    replaceSuffix(&path, suffixA, suffixB);

    // Test the result
    EXPECT_EQ(path.toStr(), "example.pdf");
}

TEST_F(ReplaceSuffixTest_1984, BoundaryCondition_EmptyPath_1984) {
    GooString path("");
    const char* suffixA = ".txt";
    const char* suffixB = ".pdf";

    // Call the replaceSuffix function
    replaceSuffix(&path, suffixA, suffixB);

    // Test that the path remains empty
    EXPECT_EQ(path.toStr(), "");
}

TEST_F(ReplaceSuffixTest_1984, BoundaryCondition_OnlySuffixA_1984) {
    GooString path(".txt");
    const char* suffixA = ".txt";
    const char* suffixB = ".pdf";

    // Call the replaceSuffix function
    replaceSuffix(&path, suffixA, suffixB);

    // Test that the path gets replaced correctly
    EXPECT_EQ(path.toStr(), ".pdf");
}

TEST_F(ReplaceSuffixTest_1984, BoundaryCondition_OnlySuffixB_1984) {
    GooString path(".pdf");
    const char* suffixA = ".txt";
    const char* suffixB = ".pdf";

    // Call the replaceSuffix function
    replaceSuffix(&path, suffixA, suffixB);

    // Test that the path remains unchanged
    EXPECT_EQ(path.toStr(), ".txt");
}

TEST_F(ReplaceSuffixTest_1984, ExceptionalCase_NullPath_1984) {
    GooString* path = nullptr;
    const char* suffixA = ".txt";
    const char* suffixB = ".pdf";

    // Call the replaceSuffix function and expect no crash (Nullptr handling)
    EXPECT_NO_THROW(replaceSuffix(path, suffixA, suffixB));
}