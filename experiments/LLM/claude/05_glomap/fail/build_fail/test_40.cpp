#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

namespace glomap {
namespace {

class OptionManagerTest_40 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create OptionManager with add_project_options = false to avoid
    // unnecessary initialization side effects
    option_manager_ = std::make_unique<OptionManager>(false);
  }

  std::unique_ptr<OptionManager> option_manager_;
};

// Test that AddViewGraphCalibrationOptions can be called without crashing
TEST_F(OptionManagerTest_40, AddViewGraphCalibrationOptionsDoesNotCrash_40) {
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
}

// Test that calling AddViewGraphCalibrationOptions twice (idempotency) does not crash
TEST_F(OptionManagerTest_40, AddViewGraphCalibrationOptionsIdempotent_40) {
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
}

// Test that calling AddViewGraphCalibrationOptions multiple times is safe
TEST_F(OptionManagerTest_40, AddViewGraphCalibrationOptionsMultipleCalls_40) {
  for (int i = 0; i < 10; ++i) {
    EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
  }
}

// Test that mapper is valid and has expected default values for ViewGraphCalibrator options
TEST_F(OptionManagerTest_40, DefaultViewGraphCalibrationValues_40) {
  ASSERT_NE(option_manager_->mapper, nullptr);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_lower_ratio,
                   0.10000000000000001);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_higher_ratio,
                   10.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_two_view_error,
                   2.0);
}

// Test that default values remain the same after adding view graph calibration options
TEST_F(OptionManagerTest_40, DefaultValuesPreservedAfterAdd_40) {
  double original_lower = option_manager_->mapper->opt_vgcalib.thres_lower_ratio;
  double original_higher = option_manager_->mapper->opt_vgcalib.thres_higher_ratio;
  double original_two_view = option_manager_->mapper->opt_vgcalib.thres_two_view_error;

  option_manager_->AddViewGraphCalibrationOptions();

  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_lower_ratio,
                   original_lower);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_higher_ratio,
                   original_higher);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_two_view_error,
                   original_two_view);
}

// Test AddAllOptions includes view graph calibration options without crashing
TEST_F(OptionManagerTest_40, AddAllOptionsIncludesViewGraphCalibration_40) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
  // After AddAllOptions, calling AddViewGraphCalibrationOptions again should be no-op
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
}

// Test Reset functionality
TEST_F(OptionManagerTest_40, ResetAfterAddViewGraphCalibrationOptions_40) {
  option_manager_->AddViewGraphCalibrationOptions();
  EXPECT_NO_THROW(option_manager_->Reset());
}

// Test ResetOptions functionality
TEST_F(OptionManagerTest_40, ResetOptionsAfterAddViewGraphCalibrationOptions_40) {
  option_manager_->AddViewGraphCalibrationOptions();
  EXPECT_NO_THROW(option_manager_->ResetOptions(false));
  EXPECT_NO_THROW(option_manager_->ResetOptions(true));
}

// Test that after Reset, values are restored to defaults
TEST_F(OptionManagerTest_40, ResetRestoresDefaults_40) {
  option_manager_->AddViewGraphCalibrationOptions();

  // Modify values
  option_manager_->mapper->opt_vgcalib.thres_lower_ratio = 99.0;
  option_manager_->mapper->opt_vgcalib.thres_higher_ratio = 99.0;
  option_manager_->mapper->opt_vgcalib.thres_two_view_error = 99.0;

  option_manager_->ResetOptions(false);

  // After reset, defaults should be restored
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_lower_ratio,
                   0.10000000000000001);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_higher_ratio,
                   10.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_two_view_error,
                   2.0);
}

// Test that AddViewGraphCalibrationOptions registers options that can be parsed
TEST_F(OptionManagerTest_40, ParseViewGraphCalibrationOptions_40) {
  option_manager_->AddViewGraphCalibrationOptions();

  const char* argv[] = {
      "test_program",
      "--ViewGraphCalib.thres_lower_ratio=0.5",
      "--ViewGraphCalib.thres_higher_ratio=20.0",
      "--ViewGraphCalib.thres_two_view_error=5.0"};
  int argc = 4;

  EXPECT_NO_THROW(
      option_manager_->Parse(argc, const_cast<char**>(argv)));

  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_lower_ratio,
                   0.5);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_higher_ratio,
                   20.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_two_view_error,
                   5.0);
}

// Test parsing with boundary values (zero)
TEST_F(OptionManagerTest_40, ParseViewGraphCalibrationZeroValues_40) {
  option_manager_->AddViewGraphCalibrationOptions();

  const char* argv[] = {
      "test_program",
      "--ViewGraphCalib.thres_lower_ratio=0.0",
      "--ViewGraphCalib.thres_higher_ratio=0.0",
      "--ViewGraphCalib.thres_two_view_error=0.0"};
  int argc = 4;

  EXPECT_NO_THROW(
      option_manager_->Parse(argc, const_cast<char**>(argv)));

  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_lower_ratio,
                   0.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_higher_ratio,
                   0.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_two_view_error,
                   0.0);
}

// Test parsing with negative values
TEST_F(OptionManagerTest_40, ParseViewGraphCalibrationNegativeValues_40) {
  option_manager_->AddViewGraphCalibrationOptions();

  const char* argv[] = {
      "test_program",
      "--ViewGraphCalib.thres_lower_ratio=-1.0",
      "--ViewGraphCalib.thres_higher_ratio=-5.0",
      "--ViewGraphCalib.thres_two_view_error=-0.5"};
  int argc = 4;

  EXPECT_NO_THROW(
      option_manager_->Parse(argc, const_cast<char**>(argv)));

  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_lower_ratio,
                   -1.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_higher_ratio,
                   -5.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_two_view_error,
                   -0.5);
}

// Test parsing with very large values
TEST_F(OptionManagerTest_40, ParseViewGraphCalibrationLargeValues_40) {
  option_manager_->AddViewGraphCalibrationOptions();

  const char* argv[] = {
      "test_program",
      "--ViewGraphCalib.thres_lower_ratio=1e10",
      "--ViewGraphCalib.thres_higher_ratio=1e15",
      "--ViewGraphCalib.thres_two_view_error=1e8"};
  int argc = 4;

  EXPECT_NO_THROW(
      option_manager_->Parse(argc, const_cast<char**>(argv)));

  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_lower_ratio,
                   1e10);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_higher_ratio,
                   1e15);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_two_view_error,
                   1e8);
}

// Test construction with project options enabled
TEST_F(OptionManagerTest_40, ConstructWithProjectOptions_40) {
  EXPECT_NO_THROW({
    OptionManager om(true);
    om.AddViewGraphCalibrationOptions();
  });
}

// Test that mapper shared pointer is not null by default
TEST_F(OptionManagerTest_40, MapperNotNull_40) {
  ASSERT_NE(option_manager_->mapper, nullptr);
}

// Test partial parsing (only some view graph calibration options)
TEST_F(OptionManagerTest_40, ParsePartialViewGraphCalibrationOptions_40) {
  option_manager_->AddViewGraphCalibrationOptions();

  const char* argv[] = {
      "test_program",
      "--ViewGraphCalib.thres_lower_ratio=0.25"};
  int argc = 2;

  EXPECT_NO_THROW(
      option_manager_->Parse(argc, const_cast<char**>(argv)));

  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_lower_ratio,
                   0.25);
  // Other values should remain at defaults
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_higher_ratio,
                   10.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_vgcalib.thres_two_view_error,
                   2.0);
}

}  // namespace
}  // namespace glomap
