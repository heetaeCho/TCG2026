// File: file_exists_test_2634.cc
//
// Unit tests for static fileExists() in:
//   ./TestProjects/poppler/utils/pdfattach.cc
//
// NOTE: fileExists() is a static function with internal linkage, so we include the
// .cc file directly to test it without touching private/internal state.

#include <cstdio>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Return;
using ::testing::StrEq;

// ---- External dependency seam for openFile (collaborator) ----
struct OpenFileProvider_2634 {
  virtual ~OpenFileProvider_2634() = default;
  virtual FILE *Open(const char *path, const char *mode) = 0;
};

struct MockOpenFileProvider_2634 : OpenFileProvider_2634 {
  MOCK_METHOD(FILE *, Open, (const char *path, const char *mode), (override));
};

static OpenFileProvider_2634 *g_open_file_provider_2634 = nullptr;

// pdfattach.cc calls openFile(). Provide a test-controlled definition.
// This is not re-implementing fileExists; it's mocking an external collaborator.
extern "C" FILE *openFile(const char *path, const char *mode)
{
  if (g_open_file_provider_2634) {
    return g_open_file_provider_2634->Open(path, mode);
  }
  return nullptr;
}

// ---- Include the production implementation to access static fileExists() ----
#include "TestProjects/poppler/utils/pdfattach.cc"

// ---- Tests ----
class FileExistsTest_2634 : public ::testing::Test {
protected:
  void TearDown() override { g_open_file_provider_2634 = nullptr; }
};

TEST_F(FileExistsTest_2634, ReturnsFalseWhenOpenFileReturnsNull_2634)
{
  MockOpenFileProvider_2634 mock;
  g_open_file_provider_2634 = &mock;

  EXPECT_CALL(mock, Open(StrEq("/does/not/matter"), StrEq("r"))).WillOnce(Return(nullptr));

  EXPECT_FALSE(fileExists("/does/not/matter"));
}

TEST_F(FileExistsTest_2634, ReturnsTrueWhenOpenFileReturnsNonNull_2634)
{
  MockOpenFileProvider_2634 mock;
  g_open_file_provider_2634 = &mock;

  // tmpfile() provides a real FILE*; fileExists() should fclose() it and return true.
  FILE *tmp = std::tmpfile();
  ASSERT_NE(tmp, nullptr);

  EXPECT_CALL(mock, Open(StrEq("/any/path"), StrEq("r"))).WillOnce(Return(tmp));

  EXPECT_TRUE(fileExists("/any/path"));
}

TEST_F(FileExistsTest_2634, ForwardsEmptyPathToOpenFileAndReturnsFalse_2634)
{
  MockOpenFileProvider_2634 mock;
  g_open_file_provider_2634 = &mock;

  EXPECT_CALL(mock, Open(StrEq(""), StrEq("r"))).WillOnce(Return(nullptr));

  EXPECT_FALSE(fileExists(""));
}

TEST_F(FileExistsTest_2634, AcceptsNullPathAndReturnsBasedOnOpenFile_2634)
{
  MockOpenFileProvider_2634 mock;
  g_open_file_provider_2634 = &mock;

  // Behavior for nullptr is not specified by the interface; we only verify forwarding
  // and observable return value based on collaborator result.
  EXPECT_CALL(mock, Open(nullptr, StrEq("r"))).WillOnce(Return(nullptr));

  EXPECT_FALSE(fileExists(nullptr));
}