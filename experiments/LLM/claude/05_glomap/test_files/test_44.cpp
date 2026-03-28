#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

namespace glomap {
namespace {

class OptionManagerTest_44 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create OptionManager without project options to keep it simple
    option_manager_ = std::make_unique<OptionManager>(false);
  }

  std::unique_ptr<OptionManager> option_manager_;
};

// Test that AddGlobalPositionerOptions can be called without crashing
TEST_F(OptionManagerTest_44, AddGlobalPositionerOptionsDoesNotCrash_44) {
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test that calling AddGlobalPositionerOptions twice is idempotent (no crash/error)
TEST_F(OptionManagerTest_44, AddGlobalPositionerOptionsIdempotent_44) {
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test that mapper shared_ptr is valid and opt_gp has expected defaults before adding options
TEST_F(OptionManagerTest_44, MapperDefaultsBeforeAddingOptions_44) {
  ASSERT_NE(option_manager_->mapper, nullptr);
  // Check default values from GlobalPositionerOptions
  EXPECT_TRUE(option_manager_->mapper->opt_gp.optimize_positions);
  EXPECT_TRUE(option_manager_->mapper->opt_gp.optimize_scales);
}

// Test that after AddGlobalPositionerOptions, the mapper options still have their defaults
TEST_F(OptionManagerTest_44, GlobalPositionerDefaultsAfterAdding_44) {
  option_manager_->AddGlobalPositionerOptions();
  ASSERT_NE(option_manager_->mapper, nullptr);
  // The default values should still be present
  EXPECT_TRUE(option_manager_->mapper->opt_gp.optimize_positions);
  EXPECT_TRUE(option_manager_->mapper->opt_gp.optimize_scales);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_gp.thres_loss_function, 0.1);
}

// Test that AddAllOptions includes global positioning options without error
TEST_F(OptionManagerTest_44, AddAllOptionsIncludesGlobalPositioner_44) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
  // Calling AddGlobalPositionerOptions again should be a no-op (already added)
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test Reset functionality
TEST_F(OptionManagerTest_44, ResetDoesNotCrash_44) {
  option_manager_->AddGlobalPositionerOptions();
  EXPECT_NO_THROW(option_manager_->Reset());
}

// Test ResetOptions functionality
TEST_F(OptionManagerTest_44, ResetOptionsDoesNotCrash_44) {
  option_manager_->AddGlobalPositionerOptions();
  EXPECT_NO_THROW(option_manager_->ResetOptions(false));
  EXPECT_NO_THROW(option_manager_->ResetOptions(true));
}

// Test that after Reset, we can add global positioning options again
TEST_F(OptionManagerTest_44, AddGlobalPositionerAfterReset_44) {
  option_manager_->AddGlobalPositionerOptions();
  option_manager_->Reset();
  // After reset, the guard flag should be reset, allowing re-addition
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test AddDatabaseOptions doesn't interfere with AddGlobalPositionerOptions
TEST_F(OptionManagerTest_44, AddDatabaseAndGlobalPositionerIndependent_44) {
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test AddImageOptions doesn't interfere with AddGlobalPositionerOptions
TEST_F(OptionManagerTest_44, AddImageAndGlobalPositionerIndependent_44) {
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test adding other mapper-related options alongside global positioning
TEST_F(OptionManagerTest_44, AddMultipleMapperOptionSections_44) {
  EXPECT_NO_THROW(option_manager_->AddRotationEstimatorOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
}

// Test construction with project options enabled
TEST_F(OptionManagerTest_44, ConstructWithProjectOptions_44) {
  auto om = std::make_unique<OptionManager>(true);
  EXPECT_NO_THROW(om->AddGlobalPositionerOptions());
  ASSERT_NE(om->mapper, nullptr);
}

// Test that Parse with no arguments doesn't crash after adding global positioner options
TEST_F(OptionManagerTest_44, ParseNoArgsAfterAddingGlobalPositioner_44) {
  option_manager_->AddGlobalPositionerOptions();
  const char* argv[] = {"test_program"};
  // Parse with argc=1, just the program name
  EXPECT_NO_THROW(option_manager_->Parse(1, const_cast<char**>(argv)));
}

// Test that default thres_loss_function value is approximately 0.1
TEST_F(OptionManagerTest_44, DefaultThresLossFunction_44) {
  option_manager_->AddGlobalPositionerOptions();
  EXPECT_NEAR(option_manager_->mapper->opt_gp.thres_loss_function, 0.1, 1e-9);
}

// Test that AddGlobalMapperFullOptions includes global positioning
TEST_F(OptionManagerTest_44, AddGlobalMapperFullOptionsIncludesGP_44) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperFullOptions());
  // Should be idempotent since full options should add GP
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test adding view graph calibration and global positioning together
TEST_F(OptionManagerTest_44, AddViewGraphCalibrationAndGP_44) {
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test adding track establishment and global positioning together
TEST_F(OptionManagerTest_44, AddTrackEstablishmentAndGP_44) {
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test calling AddGlobalPositionerOptions three times (triple idempotency)
TEST_F(OptionManagerTest_44, AddGlobalPositionerOptionsTripleCall_44) {
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
  // Values should still be default
  EXPECT_TRUE(option_manager_->mapper->opt_gp.optimize_positions);
}

}  // namespace
}  // namespace glomap
