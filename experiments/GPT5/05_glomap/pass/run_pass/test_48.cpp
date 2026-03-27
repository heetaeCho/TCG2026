// File: option_manager_add_gravity_refiner_options_test_48.cc

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

#include "glomap/controllers/option_manager.h"
#include "glomap/estimators/gravity_refinement.h"

namespace glomap {

class OptionManagerGravityRefinerTest_48 : public ::testing::Test {
 protected:
  OptionManagerGravityRefinerTest_48()
      : option_manager_(false) {  // Do not add project options automatically.
  }

  void SetUp() override {
    gravity_refiner_ = std::make_shared<GravityRefinerOptions>();
    option_manager_.gravity_refiner = gravity_refiner_;
  }

  // Helper to build argc/argv from an argument vector.
  void BuildArgcArgv(const std::vector<std::string>& args,
                     int* argc,
                     std::vector<char*>* argv) {
    argv->clear();
    argv->reserve(args.size());
    for (const auto& s : args) {
      // std::string::data() is non-const char* in C++17 and later.
      argv->push_back(const_cast<char*>(s.data()));
    }
    *argc = static_cast<int>(argv->size());
  }

  OptionManager option_manager_;
  std::shared_ptr<GravityRefinerOptions> gravity_refiner_;
};

// Normal operation: options are registered so that Parse() can update the
// GravityRefinerOptions fields from command-line flags.
TEST_F(OptionManagerGravityRefinerTest_48,
       ParsesGravityRefinerOptionsFromCommandLine_48) {
  // Arrange
  ASSERT_NE(gravity_refiner_, nullptr);
  const double default_outlier_ratio = gravity_refiner_->max_outlier_ratio;
  const double default_gravity_error = gravity_refiner_->max_gravity_error;
  const int default_min_neighbors = gravity_refiner_->min_num_neighbors;

  option_manager_.AddGravityRefinerOptions();

  // Build command-line arguments with the expected option names.
  std::vector<std::string> args = {
      "test_binary",
      "--GravityRefiner.max_outlier_ratio=0.7",
      "--GravityRefiner.max_gravity_error=2.5",
      "--GravityRefiner.min_num_neighbors=10"};
  int argc = 0;
  std::vector<char*> argv;
  BuildArgcArgv(args, &argc, &argv);

  // Act
  option_manager_.Parse(argc, argv.data());

  // Assert: values should be updated from defaults to the parsed values.
  EXPECT_DOUBLE_EQ(gravity_refiner_->max_outlier_ratio, 0.7);
  EXPECT_DOUBLE_EQ(gravity_refiner_->max_gravity_error, 2.5);
  EXPECT_EQ(gravity_refiner_->min_num_neighbors, 10);

  // Sanity: ensure they actually changed from the original defaults.
  EXPECT_NE(gravity_refiner_->max_outlier_ratio, default_outlier_ratio);
  EXPECT_NE(gravity_refiner_->max_gravity_error, default_gravity_error);
  EXPECT_NE(gravity_refiner_->min_num_neighbors, default_min_neighbors);
}

// Boundary/normal case: when no corresponding command-line flags are provided,
// the GravityRefinerOptions values should remain at their defaults.
TEST_F(OptionManagerGravityRefinerTest_48,
       KeepsDefaultValuesWhenNoFlagsProvided_48) {
  // Arrange
  ASSERT_NE(gravity_refiner_, nullptr);
  const double default_outlier_ratio = gravity_refiner_->max_outlier_ratio;
  const double default_gravity_error = gravity_refiner_->max_gravity_error;
  const int default_min_neighbors = gravity_refiner_->min_num_neighbors;

  option_manager_.AddGravityRefinerOptions();

  // Only program name, no options for the gravity refiner.
  std::vector<std::string> args = {"test_binary"};
  int argc = 0;
  std::vector<char*> argv;
  BuildArgcArgv(args, &argc, &argv);

  // Act
  option_manager_.Parse(argc, argv.data());

  // Assert: values should remain as defaults.
  EXPECT_DOUBLE_EQ(gravity_refiner_->max_outlier_ratio, default_outlier_ratio);
  EXPECT_DOUBLE_EQ(gravity_refiner_->max_gravity_error, default_gravity_error);
  EXPECT_EQ(gravity_refiner_->min_num_neighbors, default_min_neighbors);
}

// Idempotence / error case: calling AddGravityRefinerOptions() multiple times
// should not cause errors or change observable behavior (e.g., Parse still
// works correctly and sets the options as expected).
TEST_F(OptionManagerGravityRefinerTest_48,
       MultipleCallsAreIdempotentAndDoNotDuplicateOptions_48) {
  // Arrange
  ASSERT_NE(gravity_refiner_, nullptr);

  // Call AddGravityRefinerOptions twice.
  option_manager_.AddGravityRefinerOptions();
  option_manager_.AddGravityRefinerOptions();  // Should be a no-op externally.

  std::vector<std::string> args = {
      "test_binary",
      "--GravityRefiner.max_outlier_ratio=0.9",
      "--GravityRefiner.max_gravity_error=3.0",
      "--GravityRefiner.min_num_neighbors=15"};
  int argc = 0;
  std::vector<char*> argv;
  BuildArgcArgv(args, &argc, &argv);

  // Act & Assert: Parse should not throw and should set values as requested.
  EXPECT_NO_THROW(option_manager_.Parse(argc, argv.data()));

  EXPECT_DOUBLE_EQ(gravity_refiner_->max_outlier_ratio, 0.9);
  EXPECT_DOUBLE_EQ(gravity_refiner_->max_gravity_error, 3.0);
  EXPECT_EQ(gravity_refiner_->min_num_neighbors, 15);
}

}  // namespace glomap
