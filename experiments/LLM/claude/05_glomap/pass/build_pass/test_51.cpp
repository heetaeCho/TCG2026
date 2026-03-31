#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

#include "glomap/controllers/option_manager.h"

namespace glomap {
namespace {

// Helper to create argv-style arguments
class ArgvHelper {
public:
    ArgvHelper(std::initializer_list<std::string> args) {
        for (const auto& arg : args) {
            storage_.push_back(arg);
        }
        for (auto& s : storage_) {
            argv_.push_back(const_cast<char*>(s.c_str()));
        }
    }
    int argc() const { return static_cast<int>(argv_.size()); }
    char** argv() { return argv_.data(); }

private:
    std::vector<std::string> storage_;
    std::vector<char*> argv_;
};

class OptionManagerTest_51 : public ::testing::Test {
protected:
    void SetUp() override {
        // Default constructor with add_project_options = false
    }
};

// Test: OptionManager can be constructed with project options disabled
TEST_F(OptionManagerTest_51, ConstructWithoutProjectOptions_51) {
    EXPECT_NO_THROW(OptionManager om(false));
}

// Test: OptionManager can be constructed with project options enabled
TEST_F(OptionManagerTest_51, ConstructWithProjectOptions_51) {
    EXPECT_NO_THROW(OptionManager om(true));
}

// Test: AddDatabaseOptions can be called without crashing
TEST_F(OptionManagerTest_51, AddDatabaseOptions_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddDatabaseOptions());
}

// Test: AddImageOptions can be called without crashing
TEST_F(OptionManagerTest_51, AddImageOptions_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddImageOptions());
}

// Test: AddGlobalMapperOptions can be called without crashing
TEST_F(OptionManagerTest_51, AddGlobalMapperOptions_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddGlobalMapperOptions());
}

// Test: AddGlobalMapperFullOptions can be called without crashing
TEST_F(OptionManagerTest_51, AddGlobalMapperFullOptions_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddGlobalMapperFullOptions());
}

// Test: AddGlobalMapperResumeOptions can be called without crashing
TEST_F(OptionManagerTest_51, AddGlobalMapperResumeOptions_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddGlobalMapperResumeOptions());
}

// Test: AddGlobalMapperResumeFullOptions can be called without crashing
TEST_F(OptionManagerTest_51, AddGlobalMapperResumeFullOptions_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddGlobalMapperResumeFullOptions());
}

// Test: AddViewGraphCalibrationOptions can be called without crashing
TEST_F(OptionManagerTest_51, AddViewGraphCalibrationOptions_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddViewGraphCalibrationOptions());
}

// Test: AddRelativePoseEstimationOptions can be called without crashing
TEST_F(OptionManagerTest_51, AddRelativePoseEstimationOptions_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddRelativePoseEstimationOptions());
}

// Test: AddRotationEstimatorOptions can be called without crashing
TEST_F(OptionManagerTest_51, AddRotationEstimatorOptions_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddRotationEstimatorOptions());
}

// Test: AddTrackEstablishmentOptions can be called without crashing
TEST_F(OptionManagerTest_51, AddTrackEstablishmentOptions_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddTrackEstablishmentOptions());
}

// Test: AddGlobalPositionerOptions can be called without crashing
TEST_F(OptionManagerTest_51, AddGlobalPositionerOptions_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddGlobalPositionerOptions());
}

// Test: AddBundleAdjusterOptions can be called without crashing
TEST_F(OptionManagerTest_51, AddBundleAdjusterOptions_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddBundleAdjusterOptions());
}

// Test: AddTriangulatorOptions can be called without crashing
TEST_F(OptionManagerTest_51, AddTriangulatorOptions_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddTriangulatorOptions());
}

// Test: AddInlierThresholdOptions can be called without crashing
TEST_F(OptionManagerTest_51, AddInlierThresholdOptions_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddInlierThresholdOptions());
}

// Test: AddGravityRefinerOptions can be called without crashing
TEST_F(OptionManagerTest_51, AddGravityRefinerOptions_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddGravityRefinerOptions());
}

// Test: AddAllOptions can be called without crashing
TEST_F(OptionManagerTest_51, AddAllOptions_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddAllOptions());
}

// Test: Calling AddDatabaseOptions twice should not crash (idempotent guard)
TEST_F(OptionManagerTest_51, AddDatabaseOptionsTwice_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddDatabaseOptions());
    EXPECT_NO_THROW(om.AddDatabaseOptions());
}

// Test: Calling AddImageOptions twice should not crash (idempotent guard)
TEST_F(OptionManagerTest_51, AddImageOptionsTwice_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddImageOptions());
    EXPECT_NO_THROW(om.AddImageOptions());
}

// Test: Shared pointers are initialized after construction
TEST_F(OptionManagerTest_51, SharedPointersInitialized_51) {
    OptionManager om(false);
    EXPECT_NE(om.database_path, nullptr);
    EXPECT_NE(om.image_path, nullptr);
    EXPECT_NE(om.mapper, nullptr);
    EXPECT_NE(om.gravity_refiner, nullptr);
}

// Test: Parse with no arguments (just program name) should succeed
TEST_F(OptionManagerTest_51, ParseNoArguments_51) {
    OptionManager om(false);
    ArgvHelper args({"test_program"});
    EXPECT_NO_THROW(om.Parse(args.argc(), args.argv()));
}

// Test: Parse with database path option after adding database options
TEST_F(OptionManagerTest_51, ParseDatabasePath_51) {
    OptionManager om(false);
    om.AddDatabaseOptions();
    ArgvHelper args({"test_program", "--database_path", "/tmp/test.db"});
    EXPECT_NO_THROW(om.Parse(args.argc(), args.argv()));
    EXPECT_EQ(*om.database_path, "/tmp/test.db");
}

// Test: Parse with image path option after adding image options
TEST_F(OptionManagerTest_51, ParseImagePath_51) {
    OptionManager om(false);
    om.AddImageOptions();
    ArgvHelper args({"test_program", "--image_path", "/tmp/images"});
    EXPECT_NO_THROW(om.Parse(args.argc(), args.argv()));
    EXPECT_EQ(*om.image_path, "/tmp/images");
}

// Test: Reset should not crash
TEST_F(OptionManagerTest_51, Reset_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.Reset());
}

// Test: ResetOptions with reset_paths=true should not crash
TEST_F(OptionManagerTest_51, ResetOptionsWithPaths_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.ResetOptions(true));
}

// Test: ResetOptions with reset_paths=false should not crash
TEST_F(OptionManagerTest_51, ResetOptionsWithoutPaths_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.ResetOptions(false));
}

// Test: AddRequiredOption with a string option
TEST_F(OptionManagerTest_51, AddRequiredOptionString_51) {
    OptionManager om(false);
    std::string value;
    EXPECT_NO_THROW(om.AddRequiredOption("test_option", &value, "A test option"));
}

// Test: AddDefaultOption with an int option
TEST_F(OptionManagerTest_51, AddDefaultOptionInt_51) {
    OptionManager om(false);
    int value = 42;
    EXPECT_NO_THROW(om.AddDefaultOption("test_int_option", &value, "A test int option"));
}

// Test: AddDefaultOption with a double option
TEST_F(OptionManagerTest_51, AddDefaultOptionDouble_51) {
    OptionManager om(false);
    double value = 3.14;
    EXPECT_NO_THROW(om.AddDefaultOption("test_double_option", &value, "A test double option"));
}

// Test: AddDefaultOption with a bool option
TEST_F(OptionManagerTest_51, AddDefaultOptionBool_51) {
    OptionManager om(false);
    bool value = true;
    EXPECT_NO_THROW(om.AddDefaultOption("test_bool_option", &value, "A test bool option"));
}

// Test: Parse a custom default option and verify it is set
TEST_F(OptionManagerTest_51, ParseCustomDefaultOption_51) {
    OptionManager om(false);
    int value = 42;
    om.AddDefaultOption("my_int", &value, "My integer option");
    ArgvHelper args({"test_program", "--my_int", "100"});
    EXPECT_NO_THROW(om.Parse(args.argc(), args.argv()));
    EXPECT_EQ(value, 100);
}

// Test: Parse a custom default option that is not provided keeps default
TEST_F(OptionManagerTest_51, ParseCustomDefaultOptionKeepsDefault_51) {
    OptionManager om(false);
    int value = 42;
    om.AddDefaultOption("my_int", &value, "My integer option");
    ArgvHelper args({"test_program"});
    EXPECT_NO_THROW(om.Parse(args.argc(), args.argv()));
    EXPECT_EQ(value, 42);
}

// Test: Parse a custom string default option
TEST_F(OptionManagerTest_51, ParseCustomStringDefaultOption_51) {
    OptionManager om(false);
    std::string value = "default_val";
    om.AddDefaultOption("my_str", &value, "My string option");
    ArgvHelper args({"test_program", "--my_str", "new_val"});
    EXPECT_NO_THROW(om.Parse(args.argc(), args.argv()));
    EXPECT_EQ(value, "new_val");
}

// Test: Parse a custom double default option
TEST_F(OptionManagerTest_51, ParseCustomDoubleDefaultOption_51) {
    OptionManager om(false);
    double value = 1.5;
    om.AddDefaultOption("my_double", &value, "My double option");
    ArgvHelper args({"test_program", "--my_double", "2.718"});
    EXPECT_NO_THROW(om.Parse(args.argc(), args.argv()));
    EXPECT_DOUBLE_EQ(value, 2.718);
}

// Test: Parse with invalid option should cause exit (test with death test)
TEST_F(OptionManagerTest_51, ParseInvalidOptionCausesExit_51) {
    OptionManager om(false);
    ArgvHelper args({"test_program", "--nonexistent_option", "value"});
    EXPECT_EXIT(om.Parse(args.argc(), args.argv()),
                ::testing::ExitedWithCode(EXIT_FAILURE), ".*");
}

// Test: Parse with --help should cause exit with success
TEST_F(OptionManagerTest_51, ParseHelpCausesExitSuccess_51) {
    OptionManager om(false);
    ArgvHelper args({"test_program", "--help"});
    EXPECT_EXIT(om.Parse(args.argc(), args.argv()),
                ::testing::ExitedWithCode(EXIT_SUCCESS), ".*");
}

// Test: Reset and then add options again should work
TEST_F(OptionManagerTest_51, ResetThenAddOptions_51) {
    OptionManager om(false);
    om.AddDatabaseOptions();
    om.Reset();
    EXPECT_NO_THROW(om.AddDatabaseOptions());
}

// Test: ResetOptions with reset_paths=true then parse database path
TEST_F(OptionManagerTest_51, ResetOptionsThenParseDatabasePath_51) {
    OptionManager om(false);
    om.AddDatabaseOptions();
    ArgvHelper args1({"test_program", "--database_path", "/tmp/first.db"});
    om.Parse(args1.argc(), args1.argv());
    EXPECT_EQ(*om.database_path, "/tmp/first.db");

    om.ResetOptions(true);
    // After reset with paths, database_path should be reset
    // The exact behavior depends on implementation, but it should not crash
    EXPECT_NE(om.database_path, nullptr);
}

// Test: Construct with project options and verify shared pointers
TEST_F(OptionManagerTest_51, ConstructWithProjectOptionsSharedPtrs_51) {
    OptionManager om(true);
    EXPECT_NE(om.database_path, nullptr);
    EXPECT_NE(om.image_path, nullptr);
    EXPECT_NE(om.mapper, nullptr);
    EXPECT_NE(om.gravity_refiner, nullptr);
}

// Test: AddAllOptions then parse with no extra args
TEST_F(OptionManagerTest_51, AddAllOptionsThenParseNoArgs_51) {
    OptionManager om(false);
    om.AddAllOptions();
    ArgvHelper args({"test_program"});
    EXPECT_NO_THROW(om.Parse(args.argc(), args.argv()));
}

// Test: Multiple custom options can be added and parsed
TEST_F(OptionManagerTest_51, MultipleCustomOptionsParsed_51) {
    OptionManager om(false);
    int int_val = 0;
    double dbl_val = 0.0;
    std::string str_val = "";
    om.AddDefaultOption("opt_int", &int_val, "Int option");
    om.AddDefaultOption("opt_dbl", &dbl_val, "Double option");
    om.AddDefaultOption("opt_str", &str_val, "String option");

    ArgvHelper args({"test_program",
                     "--opt_int", "7",
                     "--opt_dbl", "3.14",
                     "--opt_str", "hello"});
    EXPECT_NO_THROW(om.Parse(args.argc(), args.argv()));
    EXPECT_EQ(int_val, 7);
    EXPECT_DOUBLE_EQ(dbl_val, 3.14);
    EXPECT_EQ(str_val, "hello");
}

// Test: AddGlobalMapperOptions twice (idempotent guard)
TEST_F(OptionManagerTest_51, AddGlobalMapperOptionsTwice_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddGlobalMapperOptions());
    EXPECT_NO_THROW(om.AddGlobalMapperOptions());
}

// Test: AddGravityRefinerOptions twice (idempotent guard)
TEST_F(OptionManagerTest_51, AddGravityRefinerOptionsTwice_51) {
    OptionManager om(false);
    EXPECT_NO_THROW(om.AddGravityRefinerOptions());
    EXPECT_NO_THROW(om.AddGravityRefinerOptions());
}

}  // namespace
}  // namespace glomap
