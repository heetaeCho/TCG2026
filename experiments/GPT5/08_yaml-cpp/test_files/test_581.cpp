// File: ./TestProjects/yaml-cpp/test/loadfile_tests_581.cpp

#include <gtest/gtest.h>

#include <yaml-cpp/yaml.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <typeinfo>

namespace {

class TempFile {
public:
  TempFile(std::string contents, std::string suffix = ".yml")
      : path_(std::filesystem::temp_directory_path() /
              std::filesystem::path("yamlcpp_loadfile_581_" + UniqueToken() + suffix)) {
    std::ofstream out(path_, std::ios::binary);
    out << contents;
    out.close();
  }

  explicit TempFile(std::string suffix = ".yml")
      : path_(std::filesystem::temp_directory_path() /
              std::filesystem::path("yamlcpp_loadfile_581_" + UniqueToken() + suffix)) {
    // Create an empty file.
    std::ofstream out(path_, std::ios::binary);
    out.close();
  }

  ~TempFile() {
    std::error_code ec;
    std::filesystem::remove(path_, ec);
  }

  const std::filesystem::path& path() const { return path_; }
  std::string string() const { return path_.string(); }

private:
  static std::string UniqueToken() {
    // Good enough uniqueness for unit tests: pid + monotonic counter.
    static int counter = 0;
    return std::to_string(::getpid()) + "_" + std::to_string(++counter);
  }

  std::filesystem::path path_;
};

// Runs YAML::LoadFile(filename) and YAML::Load(contents) and verifies they behave the same:
// - Either both throw (same dynamic exception type), or both succeed (nodes compare equal).
static void ExpectLoadFileMatchesLoadString(const std::string& filename,
                                           const std::string& contents) {
  bool file_threw = false;
  bool str_threw = false;
  std::string file_exc_type;
  std::string str_exc_type;

  YAML::Node file_node;
  YAML::Node str_node;

  try {
    file_node = YAML::LoadFile(filename);
  } catch (const std::exception& e) {
    file_threw = true;
    file_exc_type = typeid(e).name();
  }

  try {
    str_node = YAML::Load(contents);
  } catch (const std::exception& e) {
    str_threw = true;
    str_exc_type = typeid(e).name();
  }

  ASSERT_EQ(file_threw, str_threw) << "LoadFile and Load(string) should either both throw or both succeed.";
  if (file_threw) {
    EXPECT_EQ(file_exc_type, str_exc_type)
        << "LoadFile and Load(string) should throw the same dynamic exception type.";
    return;
  }

  // If both succeeded, their parsed results should match.
  EXPECT_TRUE(file_node == str_node);
}

}  // namespace

class LoadFileTest_581 : public ::testing::Test {};

TEST_F(LoadFileTest_581, NonexistentFileThrowsBadFile_581) {
  const std::filesystem::path missing =
      std::filesystem::temp_directory_path() / "yamlcpp_loadfile_581_definitely_missing_file.yml";

  try {
    (void)YAML::LoadFile(missing.string());
    FAIL() << "Expected YAML::BadFile to be thrown for a missing file.";
  } catch (const YAML::BadFile& e) {
    // Verify observable info: exception type and that the filename is mentioned (best-effort).
    const std::string what = e.what();
    EXPECT_NE(what.find(missing.string()), std::string::npos)
        << "BadFile::what() should mention the filename (if provided by implementation).";
  } catch (...) {
    FAIL() << "Expected YAML::BadFile, but caught a different exception type.";
  }
}

TEST_F(LoadFileTest_581, EmptyFilenameThrowsBadFile_581) {
  // Opening an empty path is expected to fail and surface as BadFile per interface contract.
  EXPECT_THROW((void)YAML::LoadFile(std::string{}), YAML::BadFile);
}

TEST_F(LoadFileTest_581, ValidYamlFileParsesSuccessfully_581) {
  const std::string yaml_text =
      "a: 1\n"
      "b: [2, 3]\n"
      "c:\n"
      "  nested: true\n";

  TempFile f(yaml_text);
  YAML::Node n = YAML::LoadFile(f.string());

  // Compare to parsing the same content via YAML::Load(string) without assuming internals.
  YAML::Node expected = YAML::Load(yaml_text);
  EXPECT_TRUE(n == expected);
}

TEST_F(LoadFileTest_581, EmptyFileBehaviorMatchesLoadEmptyString_581) {
  TempFile empty_file;  // empty contents
  ExpectLoadFileMatchesLoadString(empty_file.string(), std::string{});
}

TEST_F(LoadFileTest_581, InvalidYamlBehaviorMatchesLoadInvalidString_581) {
  // Intentionally malformed YAML. We don't assume exact exception class—just parity with YAML::Load(string).
  const std::string invalid_yaml = "key: [1, 2\n";  // missing closing bracket

  TempFile f(invalid_yaml);
  ExpectLoadFileMatchesLoadString(f.string(), invalid_yaml);
}