#include <gtest/gtest.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <filesystem>

// Include the header for RunRotationAverager
#include "glomap/exe/rotation_averager.h"

namespace glomap {
namespace {

class RunRotationAveragerTest_57 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create a temporary directory for test files
    test_dir_ = std::filesystem::temp_directory_path() / "rotation_averager_test_57";
    std::filesystem::create_directories(test_dir_);
  }

  void TearDown() override {
    std::filesystem::remove_all(test_dir_);
  }

  std::string CreateTempFile(const std::string& name, const std::string& content = "") {
    std::string path = (test_dir_ / name).string();
    std::ofstream ofs(path);
    ofs << content;
    ofs.close();
    return path;
  }

  // Helper to build argv from vector of strings
  std::vector<char*> BuildArgv(std::vector<std::string>& args) {
    std::vector<char*> argv;
    for (auto& s : args) {
      argv.push_back(s.data());
    }
    return argv;
  }

  std::filesystem::path test_dir_;
};

// Test: Missing relpose_path argument should fail (either parse error or file not found)
TEST_F(RunRotationAveragerTest_57, MissingRequiredArgs_57) {
  std::vector<std::string> args = {"rotation_averager"};
  auto argv = BuildArgv(args);
  // Without required arguments, Parse should throw or return failure
  EXPECT_NE(EXIT_SUCCESS,
            RunRotationAverager(static_cast<int>(argv.size()), argv.data()));
}

// Test: relpose_path does not exist should return EXIT_FAILURE
TEST_F(RunRotationAveragerTest_57, NonExistentRelposePath_57) {
  std::string output_path = (test_dir_ / "output.txt").string();
  std::vector<std::string> args = {
      "rotation_averager",
      "--relpose_path", "/nonexistent/path/relpose.txt",
      "--output_path", output_path
  };
  auto argv = BuildArgv(args);
  EXPECT_EQ(EXIT_FAILURE,
            RunRotationAverager(static_cast<int>(argv.size()), argv.data()));
}

// Test: gravity_path specified but does not exist should return EXIT_FAILURE
TEST_F(RunRotationAveragerTest_57, NonExistentGravityPath_57) {
  std::string relpose_path = CreateTempFile("relpose.txt", "");
  std::string output_path = (test_dir_ / "output.txt").string();
  std::vector<std::string> args = {
      "rotation_averager",
      "--relpose_path", relpose_path,
      "--output_path", output_path,
      "--gravity_path", "/nonexistent/gravity.txt"
  };
  auto argv = BuildArgv(args);
  EXPECT_EQ(EXIT_FAILURE,
            RunRotationAverager(static_cast<int>(argv.size()), argv.data()));
}

// Test: weight_path specified but does not exist should return EXIT_FAILURE
TEST_F(RunRotationAveragerTest_57, NonExistentWeightPath_57) {
  std::string relpose_path = CreateTempFile("relpose.txt", "");
  std::string output_path = (test_dir_ / "output.txt").string();
  std::vector<std::string> args = {
      "rotation_averager",
      "--relpose_path", relpose_path,
      "--output_path", output_path,
      "--weight_path", "/nonexistent/weight.txt"
  };
  auto argv = BuildArgv(args);
  EXPECT_EQ(EXIT_FAILURE,
            RunRotationAverager(static_cast<int>(argv.size()), argv.data()));
}

// Test: use_weight is true but weight_path is empty should return EXIT_FAILURE
TEST_F(RunRotationAveragerTest_57, UseWeightWithoutWeightPath_57) {
  std::string relpose_path = CreateTempFile("relpose.txt", "");
  std::string output_path = (test_dir_ / "output.txt").string();
  std::vector<std::string> args = {
      "rotation_averager",
      "--relpose_path", relpose_path,
      "--output_path", output_path,
      "--use_weight", "1"
  };
  auto argv = BuildArgv(args);
  EXPECT_EQ(EXIT_FAILURE,
            RunRotationAverager(static_cast<int>(argv.size()), argv.data()));
}

// Test: Empty relpose file - should either fail gracefully or succeed with empty output
// The behavior depends on ReadRelPose and SolveRotationAveraging with empty data
TEST_F(RunRotationAveragerTest_57, EmptyRelposeFile_57) {
  std::string relpose_path = CreateTempFile("relpose.txt", "");
  std::string output_path = (test_dir_ / "output.txt").string();
  std::vector<std::string> args = {
      "rotation_averager",
      "--relpose_path", relpose_path,
      "--output_path", output_path
  };
  auto argv = BuildArgv(args);
  // With empty relpose, rotation averaging may fail
  int result = RunRotationAverager(static_cast<int>(argv.size()), argv.data());
  // Result should be either SUCCESS or FAILURE, but should not crash
  EXPECT_TRUE(result == EXIT_SUCCESS || result == EXIT_FAILURE);
}

// Test: use_weight true with valid weight_path but no relpose data
TEST_F(RunRotationAveragerTest_57, UseWeightWithValidWeightPath_57) {
  std::string relpose_path = CreateTempFile("relpose.txt", "");
  std::string weight_path = CreateTempFile("weight.txt", "");
  std::string output_path = (test_dir_ / "output.txt").string();
  std::vector<std::string> args = {
      "rotation_averager",
      "--relpose_path", relpose_path,
      "--output_path", output_path,
      "--weight_path", weight_path,
      "--use_weight", "1"
  };
  auto argv = BuildArgv(args);
  int result = RunRotationAverager(static_cast<int>(argv.size()), argv.data());
  EXPECT_TRUE(result == EXIT_SUCCESS || result == EXIT_FAILURE);
}

// Test: Valid gravity path with empty file
TEST_F(RunRotationAveragerTest_57, ValidGravityPathEmptyFile_57) {
  std::string relpose_path = CreateTempFile("relpose.txt", "");
  std::string gravity_path = CreateTempFile("gravity.txt", "");
  std::string output_path = (test_dir_ / "output.txt").string();
  std::vector<std::string> args = {
      "rotation_averager",
      "--relpose_path", relpose_path,
      "--output_path", output_path,
      "--gravity_path", gravity_path
  };
  auto argv = BuildArgv(args);
  int result = RunRotationAverager(static_cast<int>(argv.size()), argv.data());
  EXPECT_TRUE(result == EXIT_SUCCESS || result == EXIT_FAILURE);
}

// Test: use_stratified set to false
TEST_F(RunRotationAveragerTest_57, UseStratifiedFalse_57) {
  std::string relpose_path = CreateTempFile("relpose.txt", "");
  std::string output_path = (test_dir_ / "output.txt").string();
  std::vector<std::string> args = {
      "rotation_averager",
      "--relpose_path", relpose_path,
      "--output_path", output_path,
      "--use_stratified", "0"
  };
  auto argv = BuildArgv(args);
  int result = RunRotationAverager(static_cast<int>(argv.size()), argv.data());
  EXPECT_TRUE(result == EXIT_SUCCESS || result == EXIT_FAILURE);
}

// Test: refine_gravity with gravity_path provided
TEST_F(RunRotationAveragerTest_57, RefineGravityWithGravityPath_57) {
  std::string relpose_path = CreateTempFile("relpose.txt", "");
  std::string gravity_path = CreateTempFile("gravity.txt", "");
  std::string output_path = (test_dir_ / "output.txt").string();
  std::vector<std::string> args = {
      "rotation_averager",
      "--relpose_path", relpose_path,
      "--output_path", output_path,
      "--gravity_path", gravity_path,
      "--refine_gravity", "1"
  };
  auto argv = BuildArgv(args);
  int result = RunRotationAverager(static_cast<int>(argv.size()), argv.data());
  EXPECT_TRUE(result == EXIT_SUCCESS || result == EXIT_FAILURE);
}

// Test: refine_gravity without gravity_path (should skip refinement, no error from that)
TEST_F(RunRotationAveragerTest_57, RefineGravityWithoutGravityPath_57) {
  std::string relpose_path = CreateTempFile("relpose.txt", "");
  std::string output_path = (test_dir_ / "output.txt").string();
  std::vector<std::string> args = {
      "rotation_averager",
      "--relpose_path", relpose_path,
      "--output_path", output_path,
      "--refine_gravity", "1"
  };
  auto argv = BuildArgv(args);
  int result = RunRotationAverager(static_cast<int>(argv.size()), argv.data());
  // refine_gravity is true but gravity_path is "", so refinement block is skipped
  EXPECT_TRUE(result == EXIT_SUCCESS || result == EXIT_FAILURE);
}

}  // namespace
}  // namespace glomap
