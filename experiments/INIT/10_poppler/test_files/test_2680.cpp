// parse_assert_signer_file_test_2680.cc
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

// NOTE:
// parseAssertSignerFile() is declared `static` in pdfsig.cc (internal linkage).
// To test it as a black box via its observable behavior, we include the .cc so the
// function is in the same translation unit as these tests.
#include "TestProjects/poppler/utils/pdfsig.cc"

namespace {

class ParseAssertSignerFileTest_2680 : public ::testing::Test {
protected:
  static std::filesystem::path MakeTempFilePath(std::string_view name) {
    const auto base = std::filesystem::temp_directory_path() /
                      std::filesystem::path("parseAssertSignerFileTest_2680");
    std::error_code ec;
    std::filesystem::create_directories(base, ec);
    return base / std::filesystem::path(std::string(name));
  }

  static void WriteFile(const std::filesystem::path &path,
                        const std::string &content) {
    std::ofstream out(path, std::ios::binary);
    ASSERT_TRUE(out.is_open());
    out << content;
    out.close();
    ASSERT_TRUE(out.good() || out.eof());
  }
};

TEST_F(ParseAssertSignerFileTest_2680, ReturnsEmptyVectorForMissingFile_2680) {
  const auto missing = MakeTempFilePath("missing_does_not_exist.txt");
  std::error_code ec;
  std::filesystem::remove(missing, ec); // ensure it doesn't exist

  const std::vector<std::string> lines =
      parseAssertSignerFile(missing.string());

  EXPECT_TRUE(lines.empty());
}

TEST_F(ParseAssertSignerFileTest_2680, ReturnsEmptyVectorForEmptyFile_2680) {
  const auto path = MakeTempFilePath("empty.txt");
  WriteFile(path, "");

  const std::vector<std::string> lines =
      parseAssertSignerFile(path.string());

  EXPECT_TRUE(lines.empty());
}

TEST_F(ParseAssertSignerFileTest_2680, SkipsEmptyLinesAndHashCommentLines_2680) {
  const auto path = MakeTempFilePath("comments_and_empty.txt");
  WriteFile(path,
            "\n"
            "# comment 1\n"
            "\n"
            "#comment 2\n"
            "\n");

  const std::vector<std::string> lines =
      parseAssertSignerFile(path.string());

  EXPECT_TRUE(lines.empty());
}

TEST_F(ParseAssertSignerFileTest_2680, KeepsTrimmedNonEmptyNonCommentLines_2680) {
  const auto path = MakeTempFilePath("basic_trim.txt");
  WriteFile(path,
            "  Alice  \n"
            "\tBob\t\n"
            "Carol\n");

  const std::vector<std::string> lines =
      parseAssertSignerFile(path.string());

  ASSERT_EQ(lines.size(), 3u);
  EXPECT_EQ(lines[0], "Alice");
  EXPECT_EQ(lines[1], "Bob");
  EXPECT_EQ(lines[2], "Carol");
}

TEST_F(ParseAssertSignerFileTest_2680, SkipsLinesThatBecomeEmptyAfterTrimming_2680) {
  const auto path = MakeTempFilePath("whitespace_only.txt");
  WriteFile(path,
            "   \n"
            "\t\t\n"
            " \t \n");

  const std::vector<std::string> lines =
      parseAssertSignerFile(path.string());

  EXPECT_TRUE(lines.empty());
}

TEST_F(ParseAssertSignerFileTest_2680, DoesNotTreatLeadingWhitespaceHashAsComment_2680) {
  // Observable behavior from the interface: lines that do not start with '#'
  // are not filtered as comments before trimming; trimming may yield "#...".
  const auto path = MakeTempFilePath("leading_space_hash.txt");
  WriteFile(path,
            "   #not_a_comment_after_trim\n"
            "\t#also_not_a_comment_after_trim\n"
            "#real_comment\n");

  const std::vector<std::string> lines =
      parseAssertSignerFile(path.string());

  ASSERT_EQ(lines.size(), 2u);
  EXPECT_EQ(lines[0], "#not_a_comment_after_trim");
  EXPECT_EQ(lines[1], "#also_not_a_comment_after_trim");
}

TEST_F(ParseAssertSignerFileTest_2680, HandlesLastLineWithoutTrailingNewline_2680) {
  const auto path = MakeTempFilePath("no_trailing_newline.txt");
  WriteFile(path,
            "First\n"
            "Second\n"
            "Third"); // no '\n' at end

  const std::vector<std::string> lines =
      parseAssertSignerFile(path.string());

  ASSERT_EQ(lines.size(), 3u);
  EXPECT_EQ(lines[0], "First");
  EXPECT_EQ(lines[1], "Second");
  EXPECT_EQ(lines[2], "Third");
}

TEST_F(ParseAssertSignerFileTest_2680, PreservesInternalSpacesButTrimsEnds_2680) {
  const auto path = MakeTempFilePath("internal_spaces.txt");
  WriteFile(path,
            "  Alice   Bob  \n"
            "  X  Y   Z \n");

  const std::vector<std::string> lines =
      parseAssertSignerFile(path.string());

  ASSERT_EQ(lines.size(), 2u);
  EXPECT_EQ(lines[0], "Alice   Bob");
  EXPECT_EQ(lines[1], "X  Y   Z");
}

} // namespace