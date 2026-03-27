// File: beginDocument_test_2692.cc
#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <string>

#include "goo/GooString.h"

// pdftocairo.cc is a utility and typically defines a main(); rename it to avoid clashes.
#define main pdftocairo_main_2692
// Include the implementation file so we can test the internal-linkage (static) beginDocument().
#include "utils/pdftocairo.cc"
#undef main

namespace {

class BeginDocumentTest_2692 : public ::testing::Test {
protected:
  void SetUp() override
  {
    // Save globals
    saved_ps_ = ps;
    saved_eps_ = eps;
    saved_pdf_ = pdf;
    saved_svg_ = svg;
    saved_printToWin32_ = printToWin32;
    saved_printing_ = printing;
    saved_output_file_ = output_file;

    // Default to a "safe" state: no cairo-surface branches required.
    ps = false;
    eps = false;
    pdf = false;
    svg = false;
    printToWin32 = false;
    printing = false;
    output_file = nullptr;
  }

  void TearDown() override
  {
    // Close any file we might have opened (but don't close stdout).
    if (output_file && output_file != stdout && output_file != saved_output_file_) {
      fclose(output_file);
    }

    // Restore globals
    ps = saved_ps_;
    eps = saved_eps_;
    pdf = saved_pdf_;
    svg = saved_svg_;
    printToWin32 = saved_printToWin32_;
    printing = saved_printing_;
    output_file = saved_output_file_;
  }

  static std::string MakeTempPath()
  {
    namespace fs = std::filesystem;
    const fs::path dir = fs::temp_directory_path();
    // Create a reasonably unique name.
    const std::string name =
        "pdftocairo_beginDocument_2692_" + std::to_string(::getpid()) + "_" + std::to_string(std::rand()) + ".bin";
    return (dir / name).string();
  }

private:
  bool saved_ps_{false};
  bool saved_eps_{false};
  bool saved_pdf_{false};
  bool saved_svg_{false};
  bool saved_printToWin32_{false};
  bool saved_printing_{false};
  FILE *saved_output_file_{nullptr};
};

TEST_F(BeginDocumentTest_2692, PrintingFalse_DoesNotChangeOutputFile_2692)
{
  printing = false;

  // Sentinel value (stdout) to detect unexpected changes.
  output_file = stdout;

  GooString in("in.pdf");
  GooString out("fd://0");

  beginDocument(&in, &out, 10.0, 20.0);

  EXPECT_EQ(output_file, stdout);
}

TEST_F(BeginDocumentTest_2692, PrintingTrue_PrintToWin32True_SetsOutputFileNull_2692)
{
  printing = true;
  printToWin32 = true;

  // Sentinel to ensure it gets overwritten.
  output_file = stdout;

  GooString in("in.pdf");
  GooString out("some-output");

  beginDocument(&in, &out, 10.0, 20.0);

  EXPECT_EQ(output_file, nullptr);
}

TEST_F(BeginDocumentTest_2692, PrintingTrue_OutputFd0_SetsOutputFileToStdout_2692)
{
  printing = true;
  printToWin32 = false;

  output_file = nullptr;

  GooString in("in.pdf");
  GooString out("fd://0");

  beginDocument(&in, &out, 10.0, 20.0);

  EXPECT_EQ(output_file, stdout);
}

TEST_F(BeginDocumentTest_2692, PrintingTrue_OutputPath_OpensFileForWriting_2692)
{
  printing = true;
  printToWin32 = false;

  const std::string path = MakeTempPath();
  // Ensure it doesn't already exist; beginDocument uses fopen("wb").
  std::error_code ec;
  std::filesystem::remove(path, ec);

  GooString in("in.pdf");
  GooString out(path);

  beginDocument(&in, &out, 10.0, 20.0);

  ASSERT_NE(output_file, nullptr);
  ASSERT_NE(output_file, stdout);

  // Observable behavior: should be writable.
  const unsigned char bytes[4] = {0xDE, 0xAD, 0xBE, 0xEF};
  size_t written = fwrite(bytes, 1, sizeof(bytes), output_file);
  EXPECT_EQ(written, sizeof(bytes));
  EXPECT_EQ(fflush(output_file), 0);

  // File should exist and have at least the bytes we wrote.
  EXPECT_TRUE(std::filesystem::exists(path));
  auto sz = std::filesystem::file_size(path, ec);
  if (!ec) {
    EXPECT_GE(static_cast<uintmax_t>(sz), static_cast<uintmax_t>(sizeof(bytes)));
  }
}

TEST_F(BeginDocumentTest_2692, PrintingTrue_InvalidOutputPath_ExitsWithCode2_2692)
{
  printing = true;
  printToWin32 = false;

  // An invalid path (rooted into a non-existent directory).
  // Using a very unlikely directory name to avoid accidental existence.
  const std::string badPath =
      (std::filesystem::temp_directory_path() / "does_not_exist_dir_2692" / "out.bin").string();

  ASSERT_EXIT(
      {
        GooString in("in.pdf");
        GooString out(badPath);
        beginDocument(&in, &out, 10.0, 20.0);
        std::exit(0); // Should not reach here.
      },
      ::testing::ExitedWithCode(2),
      "Error opening output file");
}

TEST_F(BeginDocumentTest_2692, PrintingTrue_EmptyOutputPath_ExitsWithCode2_2692)
{
  printing = true;
  printToWin32 = false;

  ASSERT_EXIT(
      {
        GooString in("in.pdf");
        GooString out("");
        beginDocument(&in, &out, 10.0, 20.0);
        std::exit(0); // Should not reach here.
      },
      ::testing::ExitedWithCode(2),
      "Error opening output file");
}

} // namespace