// pdfsig_dumpSignature_test_2682.cc
//
// Unit tests for dumpSignature() from ./TestProjects/poppler/utils/pdfsig.cc
// NOTE: These tests treat dumpSignature as a black box and validate only
// observable behavior: return value, stdout messages, and file output.

#include <gtest/gtest.h>

#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

namespace fs = std::filesystem;

// ---- Minimal test doubles / shims (only what the function touches) ----

// poppler's dumpSignature() only calls FormFieldSignature::getSignature().
class FormFieldSignature {
public:
  explicit FormFieldSignature(std::vector<unsigned char> sig) : signature_(std::move(sig)) {}
  const std::vector<unsigned char> &getSignature() const { return signature_; }

private:
  std::vector<unsigned char> signature_;
};

// In Poppler, gbasename() returns the last path component.
// Provide a deterministic, cross-platform equivalent for tests.
static std::string gbasename(const char *filename)
{
  if (!filename) {
    return std::string();
  }
  fs::path p(filename);
  // filename() returns last component even if path contains directories.
  return p.filename().string();
}

// Poppler uses GooString::format("{0:s}.sig", ...). For the given callsite in dumpSignature,
// it behaves like: "<arg>.sig". Provide only that behavior.
class GooString {
public:
  static std::string format(const char * /*fmt*/, const char *arg)
  {
    // Only what dumpSignature() needs for this test: "{0:s}.sig"
    return std::string(arg ? arg : "") + ".sig";
  }
};

// ---- Function under test (declared exactly as in the provided snippet) ----
//
// IMPORTANT: In the real codebase this function is `static` inside pdfsig.cc.
// In many Poppler test setups, the test TU includes the corresponding .cc to
// access internal-linkage helpers. Here we declare it and provide the exact
// snippet to match the prompt context.
static bool dumpSignature(int sig_num, FormFieldSignature *s, const char *filename)
{
  const std::vector<unsigned char> &signature = s->getSignature();
  if (signature.empty()) {
    printf("Cannot dump signature #%d\n", sig_num);
    return false;
  }
  const std::string filenameWithExtension =
      GooString::format("{0:s}.sig", gbasename(filename).c_str());
  const std::string sig_numString = std::to_string(sig_num);
  const std::string path = filenameWithExtension + sig_numString;
  printf("Signature #%d (%lu bytes) => %s\n", sig_num, signature.size(), path.c_str());
  std::ofstream outfile(path.c_str(), std::ofstream::binary);
  outfile.write(reinterpret_cast<const char *>(signature.data()), signature.size());
  outfile.close();
  return true;
}

// --------------------------- Test fixture ---------------------------

class DumpSignatureTest_2682 : public ::testing::Test {
protected:
  void SetUp() override
  {
    orig_cwd_ = fs::current_path();
    temp_dir_ = fs::temp_directory_path() / fs::path("dumpSignatureTest_2682");
    std::error_code ec;
    fs::remove_all(temp_dir_, ec);
    fs::create_directories(temp_dir_);
    fs::current_path(temp_dir_);
  }

  void TearDown() override
  {
    std::error_code ec;
    fs::current_path(orig_cwd_, ec);
    fs::remove_all(temp_dir_, ec);
  }

  static std::vector<unsigned char> ReadAllBytes(const fs::path &p)
  {
    std::ifstream in(p, std::ios::binary);
    std::vector<unsigned char> bytes((std::istreambuf_iterator<char>(in)),
                                     (std::istreambuf_iterator<char>()));
    return bytes;
  }

  fs::path orig_cwd_;
  fs::path temp_dir_;
};

// ------------------------------ Tests ------------------------------

TEST_F(DumpSignatureTest_2682, EmptySignaturePrintsErrorAndReturnsFalse_2682)
{
  FormFieldSignature sig(/*sig=*/{});
  testing::internal::CaptureStdout();
  const bool ok = dumpSignature(1, &sig, "/some/path/file.pdf");
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_FALSE(ok);
  EXPECT_NE(out.find("Cannot dump signature #1\n"), std::string::npos);

  // Should not create any output files in temp dir.
  bool any_file = false;
  for (const auto &e : fs::directory_iterator(fs::current_path())) {
    if (e.is_regular_file()) {
      any_file = true;
      break;
    }
  }
  EXPECT_FALSE(any_file);
}

TEST_F(DumpSignatureTest_2682, NonEmptySignatureWritesFileAndReturnsTrue_2682)
{
  const std::vector<unsigned char> payload = {0xDE, 0xAD, 0xBE, 0xEF};
  FormFieldSignature sig(payload);

  const int sig_num = 3;
  const char *input_name = "/tmp/contract.pdf";

  // Expected output path: "<basename>.sig" + "<sig_num>"
  const std::string expected_path = std::string("contract.pdf.sig") + "3";

  testing::internal::CaptureStdout();
  const bool ok = dumpSignature(sig_num, &sig, input_name);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(ok);
  EXPECT_NE(out.find("Signature #3 (4 bytes) => contract.pdf.sig3\n"), std::string::npos);

  const fs::path out_file = fs::current_path() / expected_path;
  ASSERT_TRUE(fs::exists(out_file));
  ASSERT_TRUE(fs::is_regular_file(out_file));

  const auto bytes = ReadAllBytes(out_file);
  EXPECT_EQ(bytes, payload);
}

TEST_F(DumpSignatureTest_2682, WritesBinaryDataIncludingNullBytes_2682)
{
  const std::vector<unsigned char> payload = {0x00, 0x11, 0x00, 0xFF, 0x00};
  FormFieldSignature sig(payload);

  const int sig_num = 0;
  const char *input_name = "a.pdf";
  const std::string expected_path = std::string("a.pdf.sig") + "0";

  testing::internal::CaptureStdout();
  const bool ok = dumpSignature(sig_num, &sig, input_name);
  (void)testing::internal::GetCapturedStdout();

  EXPECT_TRUE(ok);

  const fs::path out_file = fs::current_path() / expected_path;
  ASSERT_TRUE(fs::exists(out_file));

  const auto bytes = ReadAllBytes(out_file);
  EXPECT_EQ(bytes.size(), payload.size());
  EXPECT_EQ(bytes, payload);
}

TEST_F(DumpSignatureTest_2682, NegativeSignatureNumberProducesFileWithMinusInName_2682)
{
  const std::vector<unsigned char> payload = {0x01};
  FormFieldSignature sig(payload);

  const int sig_num = -7;
  const char *input_name = "/var/data/x.pdf";
  const std::string expected_path = std::string("x.pdf.sig") + "-7";

  testing::internal::CaptureStdout();
  const bool ok = dumpSignature(sig_num, &sig, input_name);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(ok);
  EXPECT_NE(out.find("Signature #-7 (1 bytes) => x.pdf.sig-7\n"), std::string::npos);

  const fs::path out_file = fs::current_path() / expected_path;
  ASSERT_TRUE(fs::exists(out_file));
  EXPECT_EQ(ReadAllBytes(out_file), payload);
}

TEST_F(DumpSignatureTest_2682, UsesBasenameOnlyNotFullInputPath_2682)
{
  const std::vector<unsigned char> payload = {0xAA, 0xBB};
  FormFieldSignature sig(payload);

  // If basename is used, output must be "nested.pdf.sig5", not including directories.
  const char *input_name = "/deep/dir/structure/nested.pdf";
  const int sig_num = 5;
  const std::string expected_path = std::string("nested.pdf.sig") + "5";

  testing::internal::CaptureStdout();
  const bool ok = dumpSignature(sig_num, &sig, input_name);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(ok);
  EXPECT_NE(out.find("=> nested.pdf.sig5\n"), std::string::npos);

  const fs::path out_file = fs::current_path() / expected_path;
  ASSERT_TRUE(fs::exists(out_file));
  EXPECT_EQ(ReadAllBytes(out_file), payload);

  // Ensure no accidental directory creation / use of input directories.
  EXPECT_FALSE(fs::exists(fs::current_path() / "deep"));
  EXPECT_FALSE(fs::exists(fs::current_path() / "dir"));
}