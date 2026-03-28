// File: tests/Clara_ExeName_Set_667.tests.cpp
#include <gtest/gtest.h>
#include <string>

// Include the real header from your tree
#include "Catch2/src/catch2/internal/catch_clara.hpp"

using namespace Catch::Clara;

class ClaraExeNameTest_667 : public ::testing::Test {
protected:
    // Helper that calls set and returns the updated name()
    static std::string SetAndGet(ExeName& ex, const std::string& path) {
        auto res = ex.set(path);
        // Only assert on observable surface: result indicates success (if bool-convertible)
        // Some Catch2 Clara results support operator bool(); if not, this EXPECT will be compiled out by overload resolution.
        // If operator bool() is not available in your version, you can remove the next line safely.
        EXPECT_TRUE(static_cast<bool>(res)) << "ParserResult should indicate success for a normal set() call";
        return ex.name();
    }
};

// Normal operation: Unix-style path
TEST_F(ClaraExeNameTest_667, SetsNameFromUnixPath_667) {
    ExeName ex;
    std::string updated = SetAndGet(ex, "/usr/local/bin/mytool");
    EXPECT_EQ(updated, "mytool");
    EXPECT_EQ(ex.name(), "mytool");
}

// Normal operation: Windows-style path
TEST_F(ClaraExeNameTest_667, SetsNameFromWindowsPath_667) {
    ExeName ex;
    std::string updated = SetAndGet(ex, "C:\\Tools\\myapp.exe");
    EXPECT_EQ(updated, "myapp.exe");
    EXPECT_EQ(ex.name(), "myapp.exe");
}

// Normal operation: bare filename (no separators)
TEST_F(ClaraExeNameTest_667, SetsNameFromBareFilename_667) {
    ExeName ex;
    std::string updated = SetAndGet(ex, "runner");
    EXPECT_EQ(updated, "runner");
    EXPECT_EQ(ex.name(), "runner");
}

// Boundary: trailing separator -> filename becomes empty string
TEST_F(ClaraExeNameTest_667, TrailingSlashYieldsEmptyFilename_667) {
    ExeName ex;
    std::string updated = SetAndGet(ex, "/opt/bin/");
    EXPECT_EQ(updated, "");
    EXPECT_EQ(ex.name(), "");
}

// Boundary: empty input -> name becomes empty string
TEST_F(ClaraExeNameTest_667, EmptyInputYieldsEmptyFilename_667) {
    ExeName ex;
    std::string updated = SetAndGet(ex, "");
    EXPECT_EQ(updated, "");
    EXPECT_EQ(ex.name(), "");
}

// External interaction (observable effect): ExeName constructed with a referenced string
// should update the referenced string as a side effect of set()
TEST_F(ClaraExeNameTest_667, RefConstructorUpdatesExternalString_667) {
    std::string external = "initial";
    ExeName ex(external);

    // 1st update
    auto r1 = ex.set("/bin/ls");
    EXPECT_TRUE(static_cast<bool>(r1));
    EXPECT_EQ(ex.name(), "ls");
    EXPECT_EQ(external, "ls");  // externally observable interaction

    // 2nd update (overwrite previous)
    auto r2 = ex.set("C:\\Windows\\System32\\whoami.exe");
    EXPECT_TRUE(static_cast<bool>(r2));
    EXPECT_EQ(ex.name(), "whoami.exe");
    EXPECT_EQ(external, "whoami.exe");
}

// Mixed separators edge case (robustness): ensure last separator wins
TEST_F(ClaraExeNameTest_667, MixedSeparators_LastOneWins_667) {
    ExeName ex;
    // Path contains both '/' and '\' — the last one should be used for splitting
    std::string updated = SetAndGet(ex, "C:/Program Files\\App\\bin/tool");
    EXPECT_EQ(updated, "tool");
    EXPECT_EQ(ex.name(), "tool");
}
