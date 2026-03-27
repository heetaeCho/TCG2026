// parseAssertSigner_test_2681.cc
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

// pdfsig.cc is a utility program and may define its own main(). To avoid
// conflicting with gtest's main, rename it when including the .cc.
#define main pdfsig_utility_main_2681
#include "TestProjects/poppler/utils/pdfsig.cc"
#undef main

namespace {

class ParseAssertSignerTest_2681 : public ::testing::Test {
protected:
  static std::filesystem::path MakeUniqueTempPath(const std::string &suffix) {
    const auto base = std::filesystem::temp_directory_path();
    const auto name =
        std::string("parseAssertSigner_2681_") + std::to_string(::getpid()) + "_" + suffix;
    return base / name;
  }

  static std::filesystem::path CreateTempFileWithContent(const std::string &content) {
    auto p = MakeUniqueTempPath("file.txt");
    // Ensure uniqueness if the unlikely collision happens.
    for (int i = 0; std::filesystem::exists(p) && i < 100; ++i) {
      p = MakeUniqueTempPath("file_" + std::to_string(i) + ".txt");
    }

    std::ofstream ofs(p, std::ios::binary);
    ofs << content;
    ofs.close();
    return p;
  }

  static void RemoveIfExists(const std::filesystem::path &p) {
    std::error_code ec;
    std::filesystem::remove(p, ec);
  }
};

TEST_F(ParseAssertSignerTest_2681, NonexistentPathReturnsSingleElementVector_2681) {
  const std::string input = "this_path_should_not_exist_2681___definitely";
  ASSERT_FALSE(std::filesystem::exists(input));

  const std::vector<std::string> out = parseAssertSigner(std::string_view{input});

  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], input);
}

TEST_F(ParseAssertSignerTest_2681, EmptyInputReturnsVectorWithEmptyString_2681) {
  const std::string input = "";
  // On typical platforms, filesystem::exists("") is false; regardless, we only
  // assert what is observable from this function for the common/expected case.
  if (!std::filesystem::exists(input)) {
    const std::vector<std::string> out = parseAssertSigner(std::string_view{input});
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], input);
  } else {
    // If a platform treats "" as existing, at least ensure no crash.
    EXPECT_NO_THROW((void)parseAssertSigner(std::string_view{input}));
  }
}

TEST_F(ParseAssertSignerTest_2681, PreservesWhitespaceInNonexistentInput_2681) {
  const std::string input = " signer name with spaces \t";
  ASSERT_FALSE(std::filesystem::exists(input));

  const std::vector<std::string> out = parseAssertSigner(std::string_view{input});

  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], input);
}

TEST_F(ParseAssertSignerTest_2681, HandlesVeryLongNonexistentInput_2681) {
  std::string input(4096, 'A');
  input.replace(0, 20, "nonexistent_2681_");
  ASSERT_FALSE(std::filesystem::exists(input));

  const std::vector<std::string> out = parseAssertSigner(std::string_view{input});

  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], input);
}

TEST_F(ParseAssertSignerTest_2681, ExistingFileDoesNotThrow_2681) {
  // We do NOT assume what parseAssertSignerFile() returns; we only verify the
  // observable behavior that parseAssertSigner() can be called with an existing
  // path without throwing.
  const auto filePath = CreateTempFileWithContent("Alice\nBob\n");
  ASSERT_TRUE(std::filesystem::exists(filePath));

  EXPECT_NO_THROW({
    const std::vector<std::string> out = parseAssertSigner(filePath.string());
    (void)out;  // result shape/content is intentionally not asserted here
  });

  RemoveIfExists(filePath);
}

}  // namespace