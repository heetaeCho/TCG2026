// File: option_manager_add_global_positioner_options_test_44.cc

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

#include "glomap/controllers/option_manager.h"
#include "glomap/controllers/global_mapper.h"
#include "glomap/estimators/global_positioning.h"

namespace {

// ---------------------------------------------------------------------------
// Test-side recording of AddAndRegisterDefaultOption calls
// ---------------------------------------------------------------------------

struct BoolDefaultOptionCall_44 {
  std::string name;
  const bool* option_ptr;
  std::string help_text;
};

struct IntDefaultOptionCall_44 {
  std::string name;
  const int* option_ptr;
  std::string help_text;
};

struct DoubleDefaultOptionCall_44 {
  std::string name;
  const double* option_ptr;
  std::string help_text;
};

std::vector<BoolDefaultOptionCall_44>   g_bool_default_calls_44;
std::vector<IntDefaultOptionCall_44>    g_int_default_calls_44;
std::vector<DoubleDefaultOptionCall_44> g_double_default_calls_44;

void ClearRecordedDefaultOptionCalls_44() {
  g_bool_default_calls_44.clear();
  g_int_default_calls_44.clear();
  g_double_default_calls_44.clear();
}

}  // namespace

// ---------------------------------------------------------------------------
// Test-only specializations of OptionManager::AddAndRegisterDefaultOption
//
// NOTE:
// We are NOT re-implementing the production logic. The original templates are
// only declared in the header but not defined for this test build. These
// specializations simply record which options are registered so we can verify
// that AddGlobalPositionerOptions() interacts with them as expected.
// ---------------------------------------------------------------------------
namespace glomap {

template <>
void OptionManager::AddAndRegisterDefaultOption<bool>(
    const std::string& name, bool* option, const std::string& help_text) {
  g_bool_default_calls_44.push_back(
      BoolDefaultOptionCall_44{name, option, help_text});
}

template <>
void OptionManager::AddAndRegisterDefaultOption<int>(
    const std::string& name, int* option, const std::string& help_text) {
  g_int_default_calls_44.push_back(
      IntDefaultOptionCall_44{name, option, help_text});
}

template <>
void OptionManager::AddAndRegisterDefaultOption<double>(
    const std::string& name, double* option, const std::string& help_text) {
  g_double_default_calls_44.push_back(
      DoubleDefaultOptionCall_44{name, option, help_text});
}

}  // namespace glomap

// ---------------------------------------------------------------------------
// Test fixture
// ---------------------------------------------------------------------------
class OptionManagerTest_44 : public ::testing::Test {
 protected:
  void SetUp() override {
    ClearRecordedDefaultOptionCalls_44();

    mapper_options_ = std::make_shared<glomap::GlobalMapperOptions>();

    // We pass 'false' so that the constructor (if it adds options when 'true')
    // does not pre-populate any options.
    option_manager_ =
        std::make_unique<glomap::OptionManager>(false /*add_project_options*/);

    option_manager_->mapper = mapper_options_;

    // Just in case the constructor added anything, clear recordings again.
    ClearRecordedDefaultOptionCalls_44();
  }

  void TearDown() override {
    option_manager_.reset();
    mapper_options_.reset();
    ClearRecordedDefaultOptionCalls_44();
  }

  std::unique_ptr<glomap::OptionManager> option_manager_;
  std::shared_ptr<glomap::GlobalMapperOptions> mapper_options_;
};

// ---------------------------------------------------------------------------
// Test 1: Normal operation
// ---------------------------------------------------------------------------

TEST_F(OptionManagerTest_44, RegistersGlobalPositionerOptions_44) {
  ASSERT_NE(option_manager_, nullptr);
  ASSERT_NE(mapper_options_, nullptr);

  option_manager_->AddGlobalPositionerOptions();

  // We expect the following options to be registered as default options:
  //
  //  - "GlobalPositioning.use_gpu"                 (bool)
  //  - "GlobalPositioning.gpu_index"               (int)
  //  - "GlobalPositioning.optimize_positions"      (bool)
  //  - "GlobalPositioning.optimize_points"         (bool)
  //  - "GlobalPositioning.optimize_scales"         (bool)
  //  - "GlobalPositioning.thres_loss_function"     (double)
  //  - "GlobalPositioning.max_num_iterations"      (int)
  //
  // We only verify the observable interactions: that the correct option
  // names are registered and that the pointers reference the corresponding
  // fields in GlobalMapperOptions::opt_gp.

  // --- Check bool options ---
  EXPECT_EQ(g_bool_default_calls_44.size(), 4u);

  // Collect names for easier checks.
  std::vector<std::string> bool_names_44;
  for (const auto& c : g_bool_default_calls_44) {
    bool_names_44.push_back(c.name);
  }

  // Each expected name should be present exactly once.
  auto has_name_once = [&](const std::string& n) {
    return std::count(bool_names_44.begin(), bool_names_44.end(), n) == 1;
  };

  EXPECT_TRUE(has_name_once("GlobalPositioning.use_gpu"));
  EXPECT_TRUE(has_name_once("GlobalPositioning.optimize_positions"));
  EXPECT_TRUE(has_name_once("GlobalPositioning.optimize_points"));
  EXPECT_TRUE(has_name_once("GlobalPositioning.optimize_scales"));

  // Also verify that the recorded pointers correspond to the fields in opt_gp.
  for (const auto& call : g_bool_default_calls_44) {
    if (call.name == "GlobalPositioning.use_gpu") {
      EXPECT_EQ(call.option_ptr, &option_manager_->mapper->opt_gp.use_gpu);
    } else if (call.name == "GlobalPositioning.optimize_positions") {
      EXPECT_EQ(call.option_ptr,
                &option_manager_->mapper->opt_gp.optimize_positions);
    } else if (call.name == "GlobalPositioning.optimize_points") {
      EXPECT_EQ(call.option_ptr,
                &option_manager_->mapper->opt_gp.optimize_points);
    } else if (call.name == "GlobalPositioning.optimize_scales") {
      EXPECT_EQ(call.option_ptr,
                &option_manager_->mapper->opt_gp.optimize_scales);
    }
  }

  // --- Check int options ---
  EXPECT_EQ(g_int_default_calls_44.size(), 2u);

  std::vector<std::string> int_names_44;
  for (const auto& c : g_int_default_calls_44) {
    int_names_44.push_back(c.name);
  }

  EXPECT_EQ(std::count(int_names_44.begin(), int_names_44.end(),
                       "GlobalPositioning.gpu_index"),
            1);
  EXPECT_EQ(std::count(int_names_44.begin(), int_names_44.end(),
                       "GlobalPositioning.max_num_iterations"),
            1);

  // We can at least verify gpu_index pointer; max_num_iterations is a field
  // inside the solver options, whose exact type we treat as opaque.
  for (const auto& call : g_int_default_calls_44) {
    if (call.name == "GlobalPositioning.gpu_index") {
      EXPECT_EQ(call.option_ptr, &option_manager_->mapper->opt_gp.gpu_index);
    }
  }

  // --- Check double options ---
  ASSERT_EQ(g_double_default_calls_44.size(), 1u);
  EXPECT_EQ(g_double_default_calls_44[0].name,
            "GlobalPositioning.thres_loss_function");
  EXPECT_EQ(g_double_default_calls_44[0].option_ptr,
            &option_manager_->mapper->opt_gp.thres_loss_function);
}

// ---------------------------------------------------------------------------
// Test 2: Boundary case – calling twice should not re-register options
// ---------------------------------------------------------------------------

TEST_F(OptionManagerTest_44, CallingTwiceDoesNotDuplicateOptions_44) {
  ASSERT_NE(option_manager_, nullptr);

  option_manager_->AddGlobalPositionerOptions();

  const auto bool_size_first_44   = g_bool_default_calls_44.size();
  const auto int_size_first_44    = g_int_default_calls_44.size();
  const auto double_size_first_44 = g_double_default_calls_44.size();

  // Call a second time; according to the implementation, this should return
  // early without registering the options again.
  option_manager_->AddGlobalPositionerOptions();

  EXPECT_EQ(g_bool_default_calls_44.size(), bool_size_first_44);
  EXPECT_EQ(g_int_default_calls_44.size(), int_size_first_44);
  EXPECT_EQ(g_double_default_calls_44.size(), double_size_first_44);
}
