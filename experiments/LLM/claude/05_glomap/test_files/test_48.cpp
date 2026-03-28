#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

namespace glomap {
namespace {

class OptionManagerTest_48 : public ::testing::Test {
 protected:
  void SetUp() override {
    option_manager_ = std::make_unique<OptionManager>(false);
  }

  std::unique_ptr<OptionManager> option_manager_;
};

// Test that AddGravityRefinerOptions can be called without crashing
TEST_F(OptionManagerTest_48, AddGravityRefinerOptionsDoesNotCrash_48) {
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
}

// Test that calling AddGravityRefinerOptions twice is idempotent (guard check)
TEST_F(OptionManagerTest_48, AddGravityRefinerOptionsIdempotent_48) {
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
}

// Test that calling AddGravityRefinerOptions multiple times does not crash
TEST_F(OptionManagerTest_48, AddGravityRefinerOptionsMultipleCalls_48) {
  for (int i = 0; i < 10; ++i) {
    EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
  }
}

// Test that gravity_refiner shared_ptr is valid after construction
TEST_F(OptionManagerTest_48, GravityRefinerSharedPtrIsValid_48) {
  EXPECT_NE(option_manager_->gravity_refiner, nullptr);
}

// Test that gravity_refiner default values are set correctly
TEST_F(OptionManagerTest_48, GravityRefinerDefaultValues_48) {
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_outlier_ratio, 0.5);
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_gravity_error, 1.0);
  EXPECT_EQ(option_manager_->gravity_refiner->min_num_neighbors, 7);
}

// Test that default values remain unchanged after AddGravityRefinerOptions
TEST_F(OptionManagerTest_48, DefaultValuesUnchangedAfterAdd_48) {
  option_manager_->AddGravityRefinerOptions();
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_outlier_ratio, 0.5);
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_gravity_error, 1.0);
  EXPECT_EQ(option_manager_->gravity_refiner->min_num_neighbors, 7);
}

// Test that modifying gravity_refiner options before adding still works
TEST_F(OptionManagerTest_48, ModifyBeforeAdd_48) {
  option_manager_->gravity_refiner->max_outlier_ratio = 0.3;
  option_manager_->gravity_refiner->max_gravity_error = 2.0;
  option_manager_->gravity_refiner->min_num_neighbors = 10;
  
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
  
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_outlier_ratio, 0.3);
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_gravity_error, 2.0);
  EXPECT_EQ(option_manager_->gravity_refiner->min_num_neighbors, 10);
}

// Test that modifying gravity_refiner options after adding works
TEST_F(OptionManagerTest_48, ModifyAfterAdd_48) {
  option_manager_->AddGravityRefinerOptions();
  
  option_manager_->gravity_refiner->max_outlier_ratio = 0.8;
  option_manager_->gravity_refiner->max_gravity_error = 5.0;
  option_manager_->gravity_refiner->min_num_neighbors = 3;
  
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_outlier_ratio, 0.8);
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_gravity_error, 5.0);
  EXPECT_EQ(option_manager_->gravity_refiner->min_num_neighbors, 3);
}

// Test AddAllOptions includes gravity refiner options without crashing
TEST_F(OptionManagerTest_48, AddAllOptionsIncludesGravityRefiner_48) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test that AddAllOptions followed by AddGravityRefinerOptions is safe (idempotent)
TEST_F(OptionManagerTest_48, AddAllOptionsThenGravityRefiner_48) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
}

// Test Reset after adding gravity refiner options
TEST_F(OptionManagerTest_48, ResetAfterAddGravityRefiner_48) {
  option_manager_->AddGravityRefinerOptions();
  option_manager_->gravity_refiner->max_outlier_ratio = 0.9;
  
  EXPECT_NO_THROW(option_manager_->Reset());
  
  // After reset, gravity_refiner should still be accessible
  EXPECT_NE(option_manager_->gravity_refiner, nullptr);
}

// Test ResetOptions after adding gravity refiner options
TEST_F(OptionManagerTest_48, ResetOptionsAfterAddGravityRefiner_48) {
  option_manager_->AddGravityRefinerOptions();
  option_manager_->gravity_refiner->max_outlier_ratio = 0.1;
  
  EXPECT_NO_THROW(option_manager_->ResetOptions(false));
  
  // After ResetOptions, default values should be restored
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_outlier_ratio, 0.5);
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_gravity_error, 1.0);
  EXPECT_EQ(option_manager_->gravity_refiner->min_num_neighbors, 7);
}

// Test ResetOptions with reset_paths=true after adding gravity refiner options
TEST_F(OptionManagerTest_48, ResetOptionsWithPathsAfterAddGravityRefiner_48) {
  option_manager_->AddGravityRefinerOptions();
  option_manager_->gravity_refiner->max_gravity_error = 3.0;
  
  EXPECT_NO_THROW(option_manager_->ResetOptions(true));
  
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_gravity_error, 1.0);
}

// Test boundary: zero values for gravity refiner options
TEST_F(OptionManagerTest_48, BoundaryZeroValues_48) {
  option_manager_->AddGravityRefinerOptions();
  
  option_manager_->gravity_refiner->max_outlier_ratio = 0.0;
  option_manager_->gravity_refiner->max_gravity_error = 0.0;
  option_manager_->gravity_refiner->min_num_neighbors = 0;
  
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_outlier_ratio, 0.0);
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_gravity_error, 0.0);
  EXPECT_EQ(option_manager_->gravity_refiner->min_num_neighbors, 0);
}

// Test boundary: negative values for gravity refiner options
TEST_F(OptionManagerTest_48, BoundaryNegativeValues_48) {
  option_manager_->AddGravityRefinerOptions();
  
  option_manager_->gravity_refiner->max_outlier_ratio = -1.0;
  option_manager_->gravity_refiner->max_gravity_error = -5.0;
  option_manager_->gravity_refiner->min_num_neighbors = -3;
  
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_outlier_ratio, -1.0);
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_gravity_error, -5.0);
  EXPECT_EQ(option_manager_->gravity_refiner->min_num_neighbors, -3);
}

// Test boundary: very large values
TEST_F(OptionManagerTest_48, BoundaryLargeValues_48) {
  option_manager_->AddGravityRefinerOptions();
  
  option_manager_->gravity_refiner->max_outlier_ratio = 1e10;
  option_manager_->gravity_refiner->max_gravity_error = 1e15;
  option_manager_->gravity_refiner->min_num_neighbors = 1000000;
  
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_outlier_ratio, 1e10);
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_gravity_error, 1e15);
  EXPECT_EQ(option_manager_->gravity_refiner->min_num_neighbors, 1000000);
}

// Test construction with add_project_options=true
TEST(OptionManagerConstructionTest_48, ConstructWithProjectOptions_48) {
  EXPECT_NO_THROW(OptionManager om(true));
}

// Test construction with add_project_options=false
TEST(OptionManagerConstructionTest_48, ConstructWithoutProjectOptions_48) {
  EXPECT_NO_THROW(OptionManager om(false));
}

// Test that Parse works with gravity refiner options registered
TEST_F(OptionManagerTest_48, ParseWithGravityRefinerOptions_48) {
  option_manager_->AddGravityRefinerOptions();
  
  const char* argv[] = {"test_program",
                         "--GravityRefiner.max_outlier_ratio", "0.3",
                         "--GravityRefiner.max_gravity_error", "2.5",
                         "--GravityRefiner.min_num_neighbors", "12"};
  int argc = 7;
  
  EXPECT_NO_THROW(option_manager_->Parse(argc, const_cast<char**>(argv)));
  
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_outlier_ratio, 0.3);
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_gravity_error, 2.5);
  EXPECT_EQ(option_manager_->gravity_refiner->min_num_neighbors, 12);
}

// Test that ResetOptions restores modified values after Parse
TEST_F(OptionManagerTest_48, ResetOptionsRestoresAfterParse_48) {
  option_manager_->AddGravityRefinerOptions();
  
  const char* argv[] = {"test_program",
                         "--GravityRefiner.max_outlier_ratio", "0.7"};
  int argc = 3;
  
  option_manager_->Parse(argc, const_cast<char**>(argv));
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_outlier_ratio, 0.7);
  
  option_manager_->ResetOptions(false);
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_outlier_ratio, 0.5);
}

}  // namespace
}  // namespace glomap
