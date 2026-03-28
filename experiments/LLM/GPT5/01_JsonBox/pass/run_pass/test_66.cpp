// File: tests/Value_WriteToFile_Test_66.cpp
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

#include "JsonBox/Value.h"  // assumes this provides JsonBox::Value and its public API

namespace fs = std::filesystem;
using JsonBox::Value;

class ValueWriteToFileTest_66 : public ::testing::Test {
protected:
    fs::path tempDir;

    void SetUp() override {
        tempDir = fs::temp_directory_path();
    }

    static std::string ReadFileAll(const fs::path& p) {
        std::ifstream in(p, std::ios::binary);
        std::ostringstream oss;
        oss << in.rdbuf();
        return oss.str();
    }

    static fs::path UniqueTempPath(const std::string& stem = "jsonbox_write_66") {
        // Generate a unique temporary file path (file is not created yet).
        fs::path p = fs::temp_directory_path() / fs::path(stem + "_" + std::to_string(::testing::UnitTest::GetInstance()->random_seed()) + ".json");
        // Ensure uniqueness by appending a counter if needed.
        int counter = 0;
        fs::path candidate = p;
        while (fs::exists(candidate)) {
            candidate = p;
            candidate += ("_" + std::to_string(++counter));
        }
        return candidate;
    }
};

// Normal operation: file is created and its contents match writeToStream output.
TEST_F(ValueWriteToFileTest_66, CreatesFileAndMatchesStream_66) {
    Value v(std::string("Hello \"world\"\nline2")); // a value that exercises escaping/newlines
    const fs::path outPath = UniqueTempPath("creates_match_66");

    // Produce reference output through the public stream API.
    std::ostringstream refNoIndentNoEscape;
    v.writeToStream(refNoIndentNoEscape, /*indent=*/false, /*escapeAll=*/false);

    // Write to file using the same flags.
    v.writeToFile(outPath.string(), /*indent=*/false, /*escapeAll=*/false);

    ASSERT_TRUE(fs::exists(outPath));
    const std::string fileData = ReadFileAll(outPath);
    EXPECT_EQ(refNoIndentNoEscape.str(), fileData);

    // Cleanup
    fs::remove(outPath);
}

// Normal operation: flags are passed through to writeToStream (checked by equivalence).
TEST_F(ValueWriteToFileTest_66, PassesFlagsThrough_66) {
    Value v(std::string("A\tB\nC\u00A9")); // tabs/newline/unicode likely affect formatting/escaping
    const fs::path p1 = UniqueTempPath("flags_noindent_minescape_66");
    const fs::path p2 = UniqueTempPath("flags_indent_escall_66");

    // Reference outputs directly from public writeToStream with different flag combos.
    std::ostringstream refA;
    v.writeToStream(refA, /*indent=*/false, /*escapeAll=*/false);

    std::ostringstream refB;
    v.writeToStream(refB, /*indent=*/true, /*escapeAll=*/true);

    // Write to files with the same flag combos.
    v.writeToFile(p1.string(), /*indent=*/false, /*escapeAll=*/false);
    v.writeToFile(p2.string(), /*indent=*/true, /*escapeAll=*/true);

    // Compare file contents to corresponding reference outputs.
    EXPECT_EQ(refA.str(), ReadFileAll(p1));
    EXPECT_EQ(refB.str(), ReadFileAll(p2));

    fs::remove(p1);
    fs::remove(p2);
}

// Boundary/behavior: writing again should overwrite (truncate) existing file.
TEST_F(ValueWriteToFileTest_66, OverwritesExistingFile_66) {
    Value v1(std::string("first"));
    Value v2(123);  // different value & likely different serialization
    const fs::path p = UniqueTempPath("overwrite_66");

    // First write
    {
        std::ostringstream ref1;
        v1.writeToStream(ref1, /*indent=*/false, /*escapeAll=*/false);
        v1.writeToFile(p.string(), /*indent=*/false, /*escapeAll=*/false);
        ASSERT_TRUE(fs::exists(p));
        EXPECT_EQ(ref1.str(), ReadFileAll(p));
    }

    // Second write should replace content
    {
        std::ostringstream ref2;
        v2.writeToStream(ref2, /*indent=*/false, /*escapeAll=*/false);
        v2.writeToFile(p.string(), /*indent=*/false, /*escapeAll=*/false);
        EXPECT_EQ(ref2.str(), ReadFileAll(p));
    }

    fs::remove(p);
}

// Error case: attempting to write to a path that is a directory should throw.
TEST_F(ValueWriteToFileTest_66, ThrowsWhenPathIsDirectory_66) {
    Value v(true);
    // Use a guaranteed directory path (temp directory itself).
    const std::string directoryPath = fs::temp_directory_path().string();

    // We don't assume the exact exception type beyond being an exception with a message,
    // because we treat implementation as a black box. We verify exception is thrown.
    EXPECT_THROW({
        v.writeToFile(directoryPath, /*indent=*/false, /*escapeAll=*/false);
    }, std::exception);
}

// Error case: empty path should fail to open and throw.
TEST_F(ValueWriteToFileTest_66, ThrowsOnEmptyPath_66) {
    Value v(false);
    EXPECT_THROW({
        v.writeToFile(std::string(), /*indent=*/true, /*escapeAll=*/true);
    }, std::exception);
}
