// File: ./TestProjects/yaml-cpp/util/read_test_675.cpp

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <istream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::StrictMock;

// ---- Link-time seam for dependencies used by read.cpp (external interactions) ----
// These are referenced by read.cpp but not defined there (in the snippet).
// We provide test doubles here and verify calls/parameters.
struct MockDeps_675 {
  MOCK_METHOD(void, Usage, ());
  MOCK_METHOD(void, Run, (std::istream&));
  MOCK_METHOD(std::string, ReadStream, (std::istream&));
};

static MockDeps_675* g_deps_675 = nullptr;

void usage() {
  if (g_deps_675) g_deps_675->Usage();
}

void run(std::istream& in) {
  if (g_deps_675) g_deps_675->Run(in);
}

std::string read_stream(std::istream& in) {
  if (g_deps_675) return g_deps_675->ReadStream(in);
  return {};
}

// ---- Include the program-under-test, but rename main so tests can call it. ----
#define main yaml_cpp_util_read_main_675
#include "./TestProjects/yaml-cpp/util/read.cpp"
#undef main

namespace {

class ReadMainTest_675 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_deps_675 = &deps_;
    old_cin_buf_ = std::cin.rdbuf();
    old_cout_buf_ = std::cout.rdbuf();
    old_cerr_buf_ = std::cerr.rdbuf();

    // Provide harmless buffers for std::cin/cout/cerr so tests don't block/spam output.
    cin_src_.str("");
    std::cin.rdbuf(cin_src_.rdbuf());

    cout_sink_.str("");
    std::cout.rdbuf(cout_sink_.rdbuf());

    cerr_sink_.str("");
    std::cerr.rdbuf(cerr_sink_.rdbuf());
  }

  void TearDown() override {
    std::cin.rdbuf(old_cin_buf_);
    std::cout.rdbuf(old_cout_buf_);
    std::cerr.rdbuf(old_cerr_buf_);
    g_deps_675 = nullptr;
  }

  // Helper to call renamed main with vector<string> args.
  int CallMain(const std::vector<std::string>& args) {
    argv_store_.clear();
    argv_store_.reserve(args.size());
    for (const auto& s : args) argv_store_.push_back(s);

    argv_ptrs_.clear();
    argv_ptrs_.reserve(argv_store_.size());
    for (auto& s : argv_store_) argv_ptrs_.push_back(const_cast<char*>(s.c_str()));

    return yaml_cpp_util_read_main_675(static_cast<int>(argv_ptrs_.size()), argv_ptrs_.data());
  }

  // Helper to create a temp file with contents; returns filename.
  std::string WriteTempFile(const std::string& contents) {
    // Simple, deterministic-ish temp name.
    // (Good enough for unit tests in a sandboxed environment.)
    std::string path = "/tmp/yaml_cpp_util_read_test_675_";
    path += std::to_string(std::rand());
    path += ".txt";

    std::ofstream out(path, std::ios::binary);
    out << contents;
    out.close();
    return path;
  }

  void RemoveFile(const std::string& path) { (void)std::remove(path.c_str()); }

  StrictMock<MockDeps_675> deps_;

  std::streambuf* old_cin_buf_ = nullptr;
  std::streambuf* old_cout_buf_ = nullptr;
  std::streambuf* old_cerr_buf_ = nullptr;

  std::istringstream cin_src_;
  std::ostringstream cout_sink_;
  std::ostringstream cerr_sink_;

  std::vector<std::string> argv_store_;
  std::vector<char*> argv_ptrs_;
};

TEST_F(ReadMainTest_675, DefaultArgsRunsOnceOnStdin_675) {
  cin_src_.str("hello");

  int run_calls = 0;
  EXPECT_CALL(deps_, Usage()).Times(0);
  EXPECT_CALL(deps_, ReadStream(_)).Times(0);
  EXPECT_CALL(deps_, Run(_))
      .Times(1)
      .WillOnce(Invoke([&](std::istream& in) {
        ++run_calls;
        std::string got;
        in >> got;  // should read "hello"
        EXPECT_EQ(got, "hello");
      }));

  const int rc = CallMain({"prog"});
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(run_calls, 1);
}

TEST_F(ReadMainTest_675, MissingNValueCallsUsageAndReturnsMinus1_675) {
  EXPECT_CALL(deps_, Usage()).Times(1);
  EXPECT_CALL(deps_, Run(_)).Times(0);
  EXPECT_CALL(deps_, ReadStream(_)).Times(0);

  const int rc = CallMain({"prog", "-n"});
  EXPECT_EQ(rc, -1);
}

TEST_F(ReadMainTest_675, NonPositiveNCallsUsageAndReturnsMinus1_675) {
  EXPECT_CALL(deps_, Usage()).Times(1);
  EXPECT_CALL(deps_, Run(_)).Times(0);
  EXPECT_CALL(deps_, ReadStream(_)).Times(0);

  const int rc = CallMain({"prog", "-n", "0"});
  EXPECT_EQ(rc, -1);
}

TEST_F(ReadMainTest_675, ExtraArgsAfterFilenameCallsUsageAndReturnsMinus1_675) {
  EXPECT_CALL(deps_, Usage()).Times(1);
  EXPECT_CALL(deps_, Run(_)).Times(0);
  EXPECT_CALL(deps_, ReadStream(_)).Times(0);

  const int rc = CallMain({"prog", "file.yaml", "extra"});
  EXPECT_EQ(rc, -1);
}

TEST_F(ReadMainTest_675, NGreaterThanOneWithoutCacheAndWithoutFilenameErrors_675) {
  EXPECT_CALL(deps_, Usage()).Times(1);
  EXPECT_CALL(deps_, Run(_)).Times(0);
  EXPECT_CALL(deps_, ReadStream(_)).Times(0);

  const int rc = CallMain({"prog", "-n", "2"});
  EXPECT_EQ(rc, -1);
}

TEST_F(ReadMainTest_675, CacheModeReadsOnceThenRunsNReseekingEachTime_675) {
  cin_src_.str("ignored-by-read_stream");

  EXPECT_CALL(deps_, Usage()).Times(0);

  // Cache path should read once from stdin, then call run() N times on an internal istringstream.
  EXPECT_CALL(deps_, ReadStream(_)).Times(1).WillOnce(Return("abc"));

  std::vector<std::string> seen;
  EXPECT_CALL(deps_, Run(_))
      .Times(3)
      .WillRepeatedly(Invoke([&](std::istream& in) {
        std::string got;
        // If seekg(beg) happened each iteration, we should read full "abc" every time.
        got.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
        seen.push_back(got);
      }));

  const int rc = CallMain({"prog", "-c", "-n", "3"});
  EXPECT_EQ(rc, 0);
  ASSERT_EQ(seen.size(), 3u);
  EXPECT_EQ(seen[0], "abc");
  EXPECT_EQ(seen[1], "abc");
  EXPECT_EQ(seen[2], "abc");
}

TEST_F(ReadMainTest_675, NoCacheWithFilenameRunsNAndReseeksInputFile_675) {
  const std::string path = WriteTempFile("FILEDATA");

  EXPECT_CALL(deps_, Usage()).Times(0);
  EXPECT_CALL(deps_, ReadStream(_)).Times(0);

  std::vector<std::string> seen;
  EXPECT_CALL(deps_, Run(_))
      .Times(2)
      .WillRepeatedly(Invoke([&](std::istream& in) {
        std::string got(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
        seen.push_back(got);
      }));

  const int rc = CallMain({"prog", "-n", "2", path});
  EXPECT_EQ(rc, 0);
  ASSERT_EQ(seen.size(), 2u);
  // Verifies observable effect of seekg(beg) between iterations: same content each call.
  EXPECT_EQ(seen[0], "FILEDATA");
  EXPECT_EQ(seen[1], "FILEDATA");

  RemoveFile(path);
}

TEST_F(ReadMainTest_675, CacheWithFilenameReadsOnceThenRunsNFromCachedString_675) {
  const std::string path = WriteTempFile("ONDISK");
  EXPECT_CALL(deps_, Usage()).Times(0);

  // In cache mode with filename, it should read_stream(ifstream) once.
  EXPECT_CALL(deps_, ReadStream(_))
      .Times(1)
      .WillOnce(Invoke([&](std::istream& in) {
        // The file stream should be in a good state when passed in.
        EXPECT_TRUE(in.good());
        // We still return a specific cache string to drive deterministic run() behavior.
        return std::string("CACHED");
      }));

  std::vector<std::string> seen;
  EXPECT_CALL(deps_, Run(_))
      .Times(2)
      .WillRepeatedly(Invoke([&](std::istream& in) {
        std::string got(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
        seen.push_back(got);
      }));

  const int rc = CallMain({"prog", "--cache", "-n", "2", path});
  EXPECT_EQ(rc, 0);
  ASSERT_EQ(seen.size(), 2u);
  EXPECT_EQ(seen[0], "CACHED");
  EXPECT_EQ(seen[1], "CACHED");

  RemoveFile(path);
}

}  // namespace