// TEST_ID: 585
//
// Unit tests for YAML::LoadAllFromFile
//
// Partial implementation under test (black-box from test perspective):
// namespace YAML {
//   std::vector<Node> LoadAllFromFile(const std::string& filename) {
//     std::ifstream fin(filename);
//     if (!fin) { throw BadFile(filename); }
//     return LoadAll(fin);
//   }
// }

#include <gtest/gtest.h>

#include <yaml-cpp/yaml.h>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace {

class LoadAllFromFileTest_585 : public ::testing::Test {
 protected:
  static std::filesystem::path MakeUniquePath(const std::string& stem) {
    const auto base = std::filesystem::temp_directory_path();
    // Use an incrementing suffix until we find a non-existing path.
    for (int i = 0; i < 10000; ++i) {
      std::filesystem::path p = base / (stem + "_" + std::to_string(i) + ".yaml");
      if (!std::filesystem::exists(p)) {
        return p;
      }
    }
    // Extremely unlikely; fall back to a fixed name.
    return base / (stem + "_fallback.yaml");
  }

  static void WriteFileOrFail(const std::filesystem::path& path, const std::string& content) {
    std::ofstream out(path, std::ios::binary);
    ASSERT_TRUE(out.is_open()) << "Failed to open temp file for writing: " << path.string();
    out.write(content.data(), static_cast<std::streamsize>(content.size()));
    out.close();
    ASSERT_TRUE(std::filesystem::exists(path)) << "Temp file not created: " << path.string();
  }

  // Compare result of LoadAllFromFile with LoadAll(std::istream&) on the same file content.
  // This only relies on public API behavior.
  static void ExpectSameAsLoadAllStream(const std::filesystem::path& path) {
    std::ifstream fin(path, std::ios::binary);
    ASSERT_TRUE(fin.is_open()) << "Failed to open file for reading: " << path.string();

    const std::vector<YAML::Node> expected = YAML::LoadAll(fin);
    fin.close();

    const std::vector<YAML::Node> actual = YAML::LoadAllFromFile(path.string());

    ASSERT_EQ(actual.size(), expected.size());
    for (size_t i = 0; i < actual.size(); ++i) {
      EXPECT_TRUE(actual[i] == expected[i]) << "Mismatch at document index " << i;
    }
  }
};

TEST_F(LoadAllFromFileTest_585, ThrowsBadFileWhenFileDoesNotExist_585) {
  const auto missing = (std::filesystem::temp_directory_path() / "yaml_cpp_missing_file_585_does_not_exist.yaml");
  // Ensure it truly doesn't exist.
  std::error_code ec;
  std::filesystem::remove(missing, ec);

  EXPECT_THROW((void)YAML::LoadAllFromFile(missing.string()), YAML::BadFile);
}

TEST_F(LoadAllFromFileTest_585, ThrowsBadFileWhenPathIsDirectory_585) {
  const auto dir = std::filesystem::temp_directory_path() / "yaml_cpp_dir_585";
  std::error_code ec;
  std::filesystem::remove_all(dir, ec);
  ASSERT_TRUE(std::filesystem::create_directory(dir));

  EXPECT_THROW((void)YAML::LoadAllFromFile(dir.string()), YAML::BadFile);

  std::filesystem::remove_all(dir, ec);
}

TEST_F(LoadAllFromFileTest_585, ReturnsSameAsLoadAllOnStreamForSingleDocument_585) {
  const auto path = MakeUniquePath("yaml_cpp_single_doc_585");
  WriteFileOrFail(path, "a: 1\nb: test\n");
  ExpectSameAsLoadAllStream(path);

  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(LoadAllFromFileTest_585, ReturnsSameAsLoadAllOnStreamForMultipleDocuments_585) {
  const auto path = MakeUniquePath("yaml_cpp_multi_doc_585");
  // Multiple YAML documents separated by '---'
  WriteFileOrFail(path,
                  "---\n"
                  "name: alpha\n"
                  "value: 10\n"
                  "---\n"
                  "- 1\n"
                  "- 2\n"
                  "- 3\n");
  ExpectSameAsLoadAllStream(path);

  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(LoadAllFromFileTest_585, ReturnsSameAsLoadAllOnStreamForEmptyFile_585) {
  const auto path = MakeUniquePath("yaml_cpp_empty_585");
  WriteFileOrFail(path, "");  // Empty file boundary case
  ExpectSameAsLoadAllStream(path);

  std::error_code ec;
  std::filesystem::remove(path, ec);
}

}  // namespace