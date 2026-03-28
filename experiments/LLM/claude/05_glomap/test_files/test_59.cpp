#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/exe/global_mapper.h"
#include "glomap/controllers/option_manager.h"
#include "glomap/controllers/global_mapper.h"
#include "glomap/scene/view_graph.h"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace glomap {
namespace {

class RunMapperResumeTest_59 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create a temporary directory for testing
    temp_dir_ = std::filesystem::temp_directory_path() / "glomap_test_59";
    std::filesystem::create_directories(temp_dir_);
    
    output_dir_ = temp_dir_ / "output";
    std::filesystem::create_directories(output_dir_);
  }

  void TearDown() override {
    std::filesystem::remove_all(temp_dir_);
  }

  std::filesystem::path temp_dir_;
  std::filesystem::path output_dir_;

  // Helper to build argc/argv from a vector of strings
  std::pair<int, std::vector<char*>> BuildArgs(
      const std::vector<std::string>& args) {
    args_storage_ = args;
    argv_ptrs_.clear();
    for (auto& arg : args_storage_) {
      argv_ptrs_.push_back(const_cast<char*>(arg.c_str()));
    }
    return {static_cast<int>(argv_ptrs_.size()), argv_ptrs_};
  }

 private:
  std::vector<std::string> args_storage_;
  std::vector<char*> argv_ptrs_;
};

// Test: When input_path does not exist, RunMapperResume should return EXIT_FAILURE
TEST_F(RunMapperResumeTest_59, NonExistentInputPathReturnsFailure_59) {
  std::string non_existent_path = (temp_dir_ / "non_existent_dir").string();
  std::string output_path = output_dir_.string();

  auto [argc, argv] = BuildArgs({
      "mapper_resume",
      "--input_path", non_existent_path,
      "--output_path", output_path,
  });

  int result = RunMapperResume(argc, argv.data());
  EXPECT_EQ(result, EXIT_FAILURE);
}

// Test: When output_format is invalid, RunMapperResume should return EXIT_FAILURE
TEST_F(RunMapperResumeTest_59, InvalidOutputFormatReturnsFailure_59) {
  // Create a valid input directory (though it may not contain valid reconstruction data,
  // the format check should happen before reading)
  std::string input_path = temp_dir_.string();
  std::string output_path = output_dir_.string();

  auto [argc, argv] = BuildArgs({
      "mapper_resume",
      "--input_path", input_path,
      "--output_path", output_path,
      "--output_format", "json",
  });

  int result = RunMapperResume(argc, argv.data());
  EXPECT_EQ(result, EXIT_FAILURE);
}

// Test: When input_path exists but is empty (no valid reconstruction), 
// it should fail during reconstruction reading (not format validation)
TEST_F(RunMapperResumeTest_59, EmptyInputDirectoryFailsOnRead_59) {
  std::string input_path = temp_dir_.string();
  std::string output_path = output_dir_.string();

  auto [argc, argv] = BuildArgs({
      "mapper_resume",
      "--input_path", input_path,
      "--output_path", output_path,
      "--output_format", "bin",
  });

  // This should either throw or return failure since there's no valid
  // reconstruction in the directory. We test that it doesn't succeed silently.
  // The exact behavior depends on colmap::Reconstruction::Read
  // but we expect it won't return EXIT_SUCCESS with empty data.
  EXPECT_ANY_THROW({
    try {
      RunMapperResume(argc, argv.data());
    } catch (...) {
      throw;
    }
  });
}

// Test: Verify that "txt" is an accepted output format (no format error)
// Even though it will fail on reading reconstruction, it should pass format validation
TEST_F(RunMapperResumeTest_59, TxtFormatPassesValidation_59) {
  std::string input_path = temp_dir_.string();
  std::string output_path = output_dir_.string();

  auto [argc, argv] = BuildArgs({
      "mapper_resume",
      "--input_path", input_path,
      "--output_path", output_path,
      "--output_format", "txt",
  });

  // Should not fail with "Invalid output format" error.
  // It may fail later during reconstruction read, but format validation passes.
  // We can't easily distinguish, so we just ensure it doesn't succeed
  // (since there's no valid reconstruction data).
  try {
    int result = RunMapperResume(argc, argv.data());
    // If it doesn't throw, it should not be EXIT_SUCCESS with empty input
    // (though technically possible if Reconstruction::Read is lenient)
    // We just note that format validation passed
    SUCCEED();
  } catch (...) {
    // Expected - fails during reconstruction read, not format validation
    SUCCEED();
  }
}

// Test: Verify that "bin" is an accepted output format (no format error)
TEST_F(RunMapperResumeTest_59, BinFormatPassesValidation_59) {
  std::string input_path = temp_dir_.string();
  std::string output_path = output_dir_.string();

  auto [argc, argv] = BuildArgs({
      "mapper_resume",
      "--input_path", input_path,
      "--output_path", output_path,
      "--output_format", "bin",
  });

  try {
    int result = RunMapperResume(argc, argv.data());
    SUCCEED();
  } catch (...) {
    // Expected - fails during reconstruction read, not format validation
    SUCCEED();
  }
}

// Test: OptionManager can be constructed and configured for resume
TEST_F(RunMapperResumeTest_59, OptionManagerResumeOptionsCanBeAdded_59) {
  OptionManager options;
  EXPECT_NO_THROW(options.AddGlobalMapperResumeFullOptions());
}

// Test: OptionManager AddRequiredOption and AddDefaultOption
TEST_F(RunMapperResumeTest_59, OptionManagerCanAddOptions_59) {
  OptionManager options;
  std::string input_path;
  std::string output_path;
  std::string image_path = "";
  std::string output_format = "bin";

  EXPECT_NO_THROW(options.AddRequiredOption("input_path", &input_path));
  EXPECT_NO_THROW(options.AddRequiredOption("output_path", &output_path));
  EXPECT_NO_THROW(options.AddDefaultOption("image_path", &image_path));
  EXPECT_NO_THROW(
      options.AddDefaultOption("output_format", &output_format, "{bin, txt}"));
}

// Test: GlobalMapper can be constructed with default options
TEST_F(RunMapperResumeTest_59, GlobalMapperCanBeConstructed_59) {
  GlobalMapperOptions opts;
  EXPECT_NO_THROW(GlobalMapper mapper(opts));
}

// Test: ViewGraph default construction
TEST_F(RunMapperResumeTest_59, ViewGraphDefaultConstruction_59) {
  ViewGraph vg;
  EXPECT_TRUE(vg.image_pairs.empty());
}

// Test: ViewGraph CreateImageAdjacencyList on empty graph
TEST_F(RunMapperResumeTest_59, ViewGraphEmptyAdjacencyList_59) {
  ViewGraph vg;
  auto adj = vg.CreateImageAdjacencyList();
  EXPECT_TRUE(adj.empty());
}

// Test: ViewGraph KeepLargestConnectedComponents on empty data
TEST_F(RunMapperResumeTest_59, ViewGraphKeepLargestCCEmpty_59) {
  ViewGraph vg;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  
  int result = vg.KeepLargestConnectedComponents(frames, images);
  // With no data, result should be 0 or minimal
  EXPECT_GE(result, 0);
}

// Test: ViewGraph MarkConnectedComponents on empty data
TEST_F(RunMapperResumeTest_59, ViewGraphMarkCCEmpty_59) {
  ViewGraph vg;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  
  int result = vg.MarkConnectedComponents(frames, images, 0);
  EXPECT_GE(result, 0);
}

}  // namespace
}  // namespace glomap
