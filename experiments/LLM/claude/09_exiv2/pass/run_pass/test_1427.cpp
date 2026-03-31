#include <gtest/gtest.h>
#include <string>
#include <cstdlib>

// Forward declare the function we're testing
namespace Exiv2 {
namespace Internal {
std::string getExiv2ConfigPath();
}
}

class GetExiv2ConfigPathTest_1427 : public ::testing::Test {
protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

// Test that getExiv2ConfigPath returns a string (does not crash)
TEST_F(GetExiv2ConfigPathTest_1427, ReturnsString_1427) {
  std::string result;
  ASSERT_NO_THROW(result = Exiv2::Internal::getExiv2ConfigPath());
}

// Test that the returned path is not empty when filesystem support is enabled
// (or empty when it's disabled). We test observable behavior only.
TEST_F(GetExiv2ConfigPathTest_1427, ReturnValueIsConsistent_1427) {
  std::string result = Exiv2::Internal::getExiv2ConfigPath();
#ifdef EXV_ENABLE_FILESYSTEM
  // When filesystem is enabled, the result should contain the config filename
#ifdef _WIN32
  // On Windows, the path should contain "exiv2.ini"
  EXPECT_NE(result.find("exiv2.ini"), std::string::npos)
      << "Expected path to contain 'exiv2.ini', got: " << result;
#else
  // On Unix, the path should contain ".exiv2"
  EXPECT_NE(result.find(".exiv2"), std::string::npos)
      << "Expected path to contain '.exiv2', got: " << result;
#endif
#else
  // When filesystem is disabled, the result should be empty
  EXPECT_TRUE(result.empty()) << "Expected empty string when EXV_ENABLE_FILESYSTEM is not defined";
#endif
}

// Test that calling the function multiple times returns the same result (deterministic)
TEST_F(GetExiv2ConfigPathTest_1427, DeterministicResult_1427) {
  std::string result1 = Exiv2::Internal::getExiv2ConfigPath();
  std::string result2 = Exiv2::Internal::getExiv2ConfigPath();
  EXPECT_EQ(result1, result2);
}

// Test that the returned path is a non-zero-length string when filesystem is enabled
TEST_F(GetExiv2ConfigPathTest_1427, NonEmptyWhenFilesystemEnabled_1427) {
  std::string result = Exiv2::Internal::getExiv2ConfigPath();
#ifdef EXV_ENABLE_FILESYSTEM
  EXPECT_FALSE(result.empty()) << "Path should not be empty when filesystem support is enabled";
  // The path should have a reasonable length
  EXPECT_GT(result.size(), 1u);
#else
  EXPECT_TRUE(result.empty());
#endif
}

// Test that the returned path contains a directory separator when filesystem is enabled
TEST_F(GetExiv2ConfigPathTest_1427, ContainsDirectorySeparator_1427) {
  std::string result = Exiv2::Internal::getExiv2ConfigPath();
#ifdef EXV_ENABLE_FILESYSTEM
#ifdef _WIN32
  // On Windows, path separator could be \ or /
  bool hasBackslash = result.find('\\') != std::string::npos;
  bool hasForwardSlash = result.find('/') != std::string::npos;
  EXPECT_TRUE(hasBackslash || hasForwardSlash)
      << "Expected a directory separator in path: " << result;
#else
  EXPECT_NE(result.find('/'), std::string::npos)
      << "Expected '/' in path: " << result;
#endif
#endif
}

// Test that the function can be called from multiple iterations without side effects
TEST_F(GetExiv2ConfigPathTest_1427, NoSideEffectsOnRepeatedCalls_1427) {
  for (int i = 0; i < 10; ++i) {
    std::string result;
    ASSERT_NO_THROW(result = Exiv2::Internal::getExiv2ConfigPath());
    // Just ensure it doesn't crash or change behavior
  }
  std::string first = Exiv2::Internal::getExiv2ConfigPath();
  std::string last = Exiv2::Internal::getExiv2ConfigPath();
  EXPECT_EQ(first, last);
}

// Test that the config filename at the end of the path is correct
TEST_F(GetExiv2ConfigPathTest_1427, EndsWithCorrectFilename_1427) {
  std::string result = Exiv2::Internal::getExiv2ConfigPath();
#ifdef EXV_ENABLE_FILESYSTEM
#ifdef _WIN32
  std::string expectedSuffix = "exiv2.ini";
#else
  std::string expectedSuffix = ".exiv2";
#endif
  // The result should end with the expected config filename
  if (!result.empty()) {
    ASSERT_GE(result.size(), expectedSuffix.size());
    std::string actualSuffix = result.substr(result.size() - expectedSuffix.size());
    EXPECT_EQ(actualSuffix, expectedSuffix)
        << "Path should end with '" << expectedSuffix << "', got: " << result;
  }
#endif
}
