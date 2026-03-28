// File: ImageOutputDevTest_2643.cpp
#include <gtest/gtest.h>

#include <cstring>
#include <filesystem>
#include <string>

#include "TestProjects/poppler/utils/ImageOutputDev.h"

namespace {

class ImageOutputDevTest_2643 : public ::testing::Test {
protected:
  void SetUp() override {
    // Create a unique, writable root path (prefix) for outputs, but avoid actually
    // forcing the class to write files in these tests.
    const auto base = std::filesystem::temp_directory_path();
    const auto uniq =
        "poppler_ImageOutputDevTest_2643_" + std::to_string(::getpid()) + "_" + std::to_string(counter_++);
    out_dir_ = (base / uniq);

    std::error_code ec;
    std::filesystem::create_directories(out_dir_, ec);

    // fileRootA is a char* (likely copied/owned internally). Provide a stable C-string.
    root_path_ = (out_dir_ / "image_output").string();
    file_root_ = ::strdup(root_path_.c_str());
    ASSERT_NE(file_root_, nullptr);

    // Constructor: ImageOutputDev(char *fileRootA, bool pageNamesA, bool listImagesA)
    // Use conservative defaults; tests do not assume internal behavior beyond "does not crash".
    dev_ = new ImageOutputDev(file_root_, /*pageNamesA=*/false, /*listImagesA=*/false);
    ASSERT_NE(dev_, nullptr);
  }

  void TearDown() override {
    delete dev_;
    dev_ = nullptr;

    if (file_root_) {
      std::free(file_root_);
      file_root_ = nullptr;
    }

    // Best-effort cleanup; ignore errors.
    std::error_code ec;
    std::filesystem::remove_all(out_dir_, ec);
  }

  // A very light-touch helper to exercise a public virtual method that advertises
  // unused params in the signature.
  static void CallStartPageNoDeps(ImageOutputDev* dev, int page_num) {
    ASSERT_NE(dev, nullptr);
    dev->startPage(page_num, /*state=*/nullptr, /*xref=*/nullptr);
  }

  inline static int counter_ = 0;

  std::filesystem::path out_dir_;
  std::string root_path_;
  char* file_root_ = nullptr;
  ImageOutputDev* dev_ = nullptr;
};

} // namespace

TEST_F(ImageOutputDevTest_2643, EnablePrintFilenamesTrueDoesNotCrash_2643) {
  ASSERT_NE(dev_, nullptr);

  // Should be safe to call with a normal value.
  dev_->enablePrintFilenames(true);

  // Exercise another public method afterward to ensure object remains usable.
  CallStartPageNoDeps(dev_, /*page_num=*/1);
}

TEST_F(ImageOutputDevTest_2643, EnablePrintFilenamesFalseDoesNotCrash_2643) {
  ASSERT_NE(dev_, nullptr);

  dev_->enablePrintFilenames(false);
  CallStartPageNoDeps(dev_, /*page_num=*/1);
}

TEST_F(ImageOutputDevTest_2643, EnablePrintFilenamesToggleMultipleTimesDoesNotCrash_2643) {
  ASSERT_NE(dev_, nullptr);

  // Boundary-ish: repeated toggles should not destabilize the instance.
  dev_->enablePrintFilenames(true);
  dev_->enablePrintFilenames(false);
  dev_->enablePrintFilenames(true);
  dev_->enablePrintFilenames(false);

  CallStartPageNoDeps(dev_, /*page_num=*/1);
  CallStartPageNoDeps(dev_, /*page_num=*/2);
}

TEST_F(ImageOutputDevTest_2643, EnablePrintFilenamesDoesNotPreventIsOkQuery_2643) {
  ASSERT_NE(dev_, nullptr);

  // The interface exposes isOk(); we only verify it remains callable around the toggle,
  // without asserting any specific return value.
  const bool before = dev_->isOk();

  dev_->enablePrintFilenames(true);
  const bool after_true = dev_->isOk();

  dev_->enablePrintFilenames(false);
  const bool after_false = dev_->isOk();

  // No behavioral assumption about the value; just ensure calls are valid and consistent types.
  (void)before;
  (void)after_true;
  (void)after_false;
}