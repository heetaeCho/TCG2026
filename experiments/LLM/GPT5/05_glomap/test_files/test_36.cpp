#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <vector>

#include "glomap/controllers/option_manager.h"
#include "glomap/controllers/global_mapper.h"

using glomap::OptionManager;
using glomap::GlobalMapperOptions;

class OptionManagerTest_36 : public ::testing::Test {
protected:
  // Helper to build argc/argv-style arguments from a list of strings
  static void BuildArgv(const std::vector<std::string>& args,
                        int& argc,
                        std::vector<char*>& argv) {
    argv.clear();
    argv.reserve(args.size());
    for (const auto& s : args) {
      // const_cast is safe here as we do not modify the contents.
      argv.push_back(const_cast<char*>(s.c_str()));
    }
    argc = static_cast<int>(argv.size());
  }
};

// Verifies that after calling AddGlobalMapperOptions, the CLI options
// are correctly parsed into the GlobalMapperOptions fields.
TEST_F(OptionManagerTest_36,
       ParseUpdatesMapperOptionsAfterAddingGlobalMapperOptions_36) {
  OptionManager manager(/*add_project_options=*/false);
  manager.mapper = std::make_shared<GlobalMapperOptions>();

  // Sanity check: initial defaults from GlobalMapperOptions.
  EXPECT_EQ(3, manager.mapper->num_iteration_bundle_adjustment);
  EXPECT_EQ(1, manager.mapper->num_iteration_retriangulation);
  EXPECT_FALSE(manager.mapper->skip_preprocessing);
  EXPECT_FALSE(manager.mapper->skip_view_graph_calibration);
  EXPECT_FALSE(manager.mapper->skip_relative_pose_estimation);
  EXPECT_FALSE(manager.mapper->skip_rotation_averaging);
  EXPECT_FALSE(manager.mapper->skip_global_positioning);
  EXPECT_FALSE(manager.mapper->skip_bundle_adjustment);
  EXPECT_FALSE(manager.mapper->skip_retriangulation);
  EXPECT_TRUE(manager.mapper->skip_pruning);

  manager.AddGlobalMapperOptions();

  std::vector<std::string> args = {
      "program",
      "--ba_iteration_num=10",
      "--retriangulation_iteration_num=5",
      "--skip_preprocessing=1",
      "--skip_view_graph_calibration=1",
      "--skip_relative_pose_estimation=1",
      "--skip_rotation_averaging=1",
      "--skip_global_positioning=1",
      "--skip_bundle_adjustment=1",
      "--skip_retriangulation=1",
      "--skip_pruning=0"
  };

  int argc = 0;
  std::vector<char*> argv;
  BuildArgv(args, argc, argv);

  ASSERT_NO_THROW(manager.Parse(argc, argv.data()));

  // After parsing, mapper options should reflect the CLI values.
  EXPECT_EQ(10, manager.mapper->num_iteration_bundle_adjustment);
  EXPECT_EQ(5, manager.mapper->num_iteration_retriangulation);
  EXPECT_TRUE(manager.mapper->skip_preprocessing);
  EXPECT_TRUE(manager.mapper->skip_view_graph_calibration);
  EXPECT_TRUE(manager.mapper->skip_relative_pose_estimation);
  EXPECT_TRUE(manager.mapper->skip_rotation_averaging);
  EXPECT_TRUE(manager.mapper->skip_global_positioning);
  EXPECT_TRUE(manager.mapper->skip_bundle_adjustment);
  EXPECT_TRUE(manager.mapper->skip_retriangulation);
  EXPECT_FALSE(manager.mapper->skip_pruning);
}

// Verifies that if AddGlobalMapperOptions is NOT called, parsing the same
// command-line does not change the mapper’s default values (i.e., the
// options are not registered and therefore not applied).
TEST_F(OptionManagerTest_36,
       ParseWithoutAddingGlobalMapperOptionsDoesNotChangeMapper_36) {
  OptionManager manager(/*add_project_options=*/false);
  manager.mapper = std::make_shared<GlobalMapperOptions>();

  // Defaults before parsing.
  const int default_ba_iter = manager.mapper->num_iteration_bundle_adjustment;
  const int default_retriang_iter = manager.mapper->num_iteration_retriangulation;
  const bool default_skip_preprocessing = manager.mapper->skip_preprocessing;
  const bool default_skip_vgcalib = manager.mapper->skip_view_graph_calibration;
  const bool default_skip_relpose = manager.mapper->skip_relative_pose_estimation;
  const bool default_skip_ra = manager.mapper->skip_rotation_averaging;
  const bool default_skip_gp = manager.mapper->skip_global_positioning;
  const bool default_skip_ba = manager.mapper->skip_bundle_adjustment;
  const bool default_skip_retri = manager.mapper->skip_retriangulation;
  const bool default_skip_pruning = manager.mapper->skip_pruning;

  std::vector<std::string> args = {
      "program",
      "--ba_iteration_num=10",
      "--retriangulation_iteration_num=5",
      "--skip_preprocessing=1",
      "--skip_view_graph_calibration=1",
      "--skip_relative_pose_estimation=1",
      "--skip_rotation_averaging=1",
      "--skip_global_positioning=1",
      "--skip_bundle_adjustment=1",
      "--skip_retriangulation=1",
      "--skip_pruning=0"
  };

  int argc = 0;
  std::vector<char*> argv;
  BuildArgv(args, argc, argv);

  // Behavior is defined only via public interface; if the options were not
  // registered, we expect the defaults to remain unchanged.
  ASSERT_NO_THROW(manager.Parse(argc, argv.data()));

  EXPECT_EQ(default_ba_iter, manager.mapper->num_iteration_bundle_adjustment);
  EXPECT_EQ(default_retriang_iter, manager.mapper->num_iteration_retriangulation);
  EXPECT_EQ(default_skip_preprocessing, manager.mapper->skip_preprocessing);
  EXPECT_EQ(default_skip_vgcalib, manager.mapper->skip_view_graph_calibration);
  EXPECT_EQ(default_skip_relpose, manager.mapper->skip_relative_pose_estimation);
  EXPECT_EQ(default_skip_ra, manager.mapper->skip_rotation_averaging);
  EXPECT_EQ(default_skip_gp, manager.mapper->skip_global_positioning);
  EXPECT_EQ(default_skip_ba, manager.mapper->skip_bundle_adjustment);
  EXPECT_EQ(default_skip_retri, manager.mapper->skip_retriangulation);
  EXPECT_EQ(default_skip_pruning, manager.mapper->skip_pruning);
}

// Verifies that calling AddGlobalMapperOptions multiple times is effectively
// idempotent from the caller’s perspective: parsing the same CLI leads to
// the same mapper configuration whether AddGlobalMapperOptions was called
// once or multiple times.
TEST_F(OptionManagerTest_36,
       MultipleCallsToAddGlobalMapperOptionsAreIdempotent_36) {
  // First manager: call AddGlobalMapperOptions once.
  OptionManager manager_single(/*add_project_options=*/false);
  manager_single.mapper = std::make_shared<GlobalMapperOptions>();
  manager_single.AddGlobalMapperOptions();

  std::vector<std::string> args = {
      "program",
      "--ba_iteration_num=7",
      "--retriangulation_iteration_num=4",
      "--skip_preprocessing=1",
      "--skip_view_graph_calibration=0",
      "--skip_relative_pose_estimation=1",
      "--skip_rotation_averaging=0",
      "--skip_global_positioning=1",
      "--skip_bundle_adjustment=0",
      "--skip_retriangulation=1",
      "--skip_pruning=0"
  };

  int argc = 0;
  std::vector<char*> argv;
  BuildArgv(args, argc, argv);

  ASSERT_NO_THROW(manager_single.Parse(argc, argv.data()));

  // Capture results from the single-call case.
  auto mapper_single = manager_single.mapper;

  // Second manager: call AddGlobalMapperOptions twice.
  OptionManager manager_double(/*add_project_options=*/false);
  manager_double.mapper = std::make_shared<GlobalMapperOptions>();
  ASSERT_NO_THROW(manager_double.AddGlobalMapperOptions());
  // Second call should have no observable negative effect.
  ASSERT_NO_THROW(manager_double.AddGlobalMapperOptions());

  BuildArgv(args, argc, argv);
  ASSERT_NO_THROW(manager_double.Parse(argc, argv.data()));

  auto mapper_double = manager_double.mapper;

  // The resulting options should be identical.
  EXPECT_EQ(mapper_single->num_iteration_bundle_adjustment,
            mapper_double->num_iteration_bundle_adjustment);
  EXPECT_EQ(mapper_single->num_iteration_retriangulation,
            mapper_double->num_iteration_retriangulation);
  EXPECT_EQ(mapper_single->skip_preprocessing,
            mapper_double->skip_preprocessing);
  EXPECT_EQ(mapper_single->skip_view_graph_calibration,
            mapper_double->skip_view_graph_calibration);
  EXPECT_EQ(mapper_single->skip_relative_pose_estimation,
            mapper_double->skip_relative_pose_estimation);
  EXPECT_EQ(mapper_single->skip_rotation_averaging,
            mapper_double->skip_rotation_averaging);
  EXPECT_EQ(mapper_single->skip_global_positioning,
            mapper_double->skip_global_positioning);
  EXPECT_EQ(mapper_single->skip_bundle_adjustment,
            mapper_double->skip_bundle_adjustment);
  EXPECT_EQ(mapper_single->skip_retriangulation,
            mapper_double->skip_retriangulation);
  EXPECT_EQ(mapper_single->skip_pruning,
            mapper_double->skip_pruning);
}
