// File: openFile_test_40.cc
//
// Unit tests for openFile(const char*, const char*)
// From: ./TestProjects/poppler/goo/gfile.cc
//
// Notes / constraints adherence:
// - Treat openFile as a black box: only validate observable behavior (FILE* result,
//   ability to read/write, error/null on invalid cases, and FD_CLOEXEC flag on POSIX).
// - No reliance on internal/private state.
// - No mocking needed (no external collaborators exposed via interface).

#include <gtest/gtest.h>

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#endif

#if !defined(_WIN32)
#include <fcntl.h>
#include <unistd.h>
#endif

// Declaration under test (provided by the codebase).
// If your build exposes it via a header, prefer including that header instead.
extern "C" FILE *openFile(const char *path, const char *mode);

namespace {

#if __has_include(<filesystem>)
static fs::path MakeUniqueTempPath(const std::string& prefix) {
  const fs::path base = fs::temp_directory_path();
  // Use a simple uniqueness source; this is for tests, collisions are highly unlikely.
  // (We avoid relying on internal implementation details of openFile.)
  const auto pid =
#if !defined(_WIN32)
      static_cast<long long>(::getpid());
#else
      0LL;
#endif
  const auto now = static_cast<long long>(std::time(nullptr));
  return base / (prefix + "_" + std::to_string(pid) + "_" + std::to_string(now) + ".tmp");
}
#endif

static bool WriteAll(FILE* f, const std::string& s) {
  if (!f) return false;
  const size_t n = std::fwrite(s.data(), 1, s.size(), f);
  return n == s.size();
}

static std::string ReadAll(FILE* f) {
  if (!f) return {};
  std::vector<char> buf(4096);
  std::string out;
  while (true) {
    const size_t n = std::fread(buf.data(), 1, buf.size(), f);
    if (n > 0) out.append(buf.data(), n);
    if (n < buf.size()) break;  // EOF or error
  }
  return out;
}

#if !defined(_WIN32)
static bool HasCloexec(FILE* f) {
  if (!f) return false;
  const int fd = ::fileno(f);
  if (fd < 0) return false;
  const int flags = ::fcntl(fd, F_GETFD);
  if (flags < 0) return false;
  return (flags & FD_CLOEXEC) != 0;
}
#endif

}  // namespace

class OpenFileTest_40 : public ::testing::Test {};

#if __has_include(<filesystem>)

TEST_F(OpenFileTest_40, OpenExistingFileForRead_ReturnsNonNullAndReadsContent_40) {
  const fs::path p = MakeUniqueTempPath("openFile_read");
  {
    // Create a file with known content using standard facilities (not openFile).
    FILE* f = std::fopen(p.string().c_str(), "wb");
    ASSERT_NE(f, nullptr);
    ASSERT_TRUE(WriteAll(f, "hello\nworld"));
    std::fclose(f);
  }

  FILE* f = openFile(p.string().c_str(), "rb");
  ASSERT_NE(f, nullptr);

  const std::string content = ReadAll(f);
  std::fclose(f);

  EXPECT_EQ(content, "hello\nworld");
}

TEST_F(OpenFileTest_40, OpenForWrite_CreatesOrTruncatesFileAndWritesData_40) {
  const fs::path p = MakeUniqueTempPath("openFile_write");

  FILE* f = openFile(p.string().c_str(), "wb");
  ASSERT_NE(f, nullptr);
  ASSERT_TRUE(WriteAll(f, "abc123"));
  std::fflush(f);
  std::fclose(f);

  // Verify file exists and content matches.
  FILE* r = std::fopen(p.string().c_str(), "rb");
  ASSERT_NE(r, nullptr);
  const std::string content = ReadAll(r);
  std::fclose(r);

  EXPECT_EQ(content, "abc123");
}

TEST_F(OpenFileTest_40, OpenNonexistentFileForRead_ReturnsNull_40) {
  const fs::path p = MakeUniqueTempPath("openFile_missing");
  // Ensure it's not present.
  std::error_code ec;
  fs::remove(p, ec);

  FILE* f = openFile(p.string().c_str(), "rb");
  EXPECT_EQ(f, nullptr);
}

TEST_F(OpenFileTest_40, OpenEmptyPath_ReturnsNull_40) {
  FILE* f = openFile("", "rb");
  EXPECT_EQ(f, nullptr);
}

TEST_F(OpenFileTest_40, OpenDirectoryAsFileForRead_ReturnsNull_40) {
  const fs::path dir = fs::temp_directory_path();  // existing directory
  FILE* f = openFile(dir.string().c_str(), "rb");
  EXPECT_EQ(f, nullptr);
}

#if !defined(_WIN32)
TEST_F(OpenFileTest_40, OpenSetsCloseOnExecFlag_WhenFileOpenedSuccessfully_40) {
  const fs::path p = MakeUniqueTempPath("openFile_cloexec");
  {
    FILE* f = std::fopen(p.string().c_str(), "wb");
    ASSERT_NE(f, nullptr);
    ASSERT_TRUE(WriteAll(f, "x"));
    std::fclose(f);
  }

  FILE* f = openFile(p.string().c_str(), "rb");
  ASSERT_NE(f, nullptr);

  // Observable effect: file descriptor should have FD_CLOEXEC set.
  // If the platform does not support checking this, the test will fail fast above.
  EXPECT_TRUE(HasCloexec(f));

  std::fclose(f);
}
#endif  // !defined(_WIN32)

#else  // no <filesystem>

TEST_F(OpenFileTest_40, OpenExistingFileForRead_BasicSmoke_40) {
  // Fallback smoke test when <filesystem> is unavailable.
  // Uses tmpfile + mode on known path is not possible, so just ensure empty path fails.
  FILE* f = openFile("", "rb");
  EXPECT_EQ(f, nullptr);
}

#endif  // __has_include(<filesystem>)