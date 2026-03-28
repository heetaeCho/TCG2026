#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

using namespace glomap;

class OptionManagerResetOptionsTest_50 : public ::testing::Test {
protected:
    OptionManagerResetOptionsTest_50() : opt_mgr(false) {
        opt_mgr.database_path = std::make_shared<std::string>("db_initial");
        opt_mgr.image_path = std::make_shared<std::string>("img_initial");
        opt_mgr.mapper = std::make_shared<GlobalMapperOptions>();
        opt_mgr.gravity_refiner = std::make_shared<GravityRefinerOptions>();
    }

    OptionManager opt_mgr;
};

//
// ─────────────────────────────────────────────────────────────
//   TESTS FOR ResetOptions(reset_paths = true)
// ─────────────────────────────────────────────────────────────
//

TEST_F(OptionManagerResetOptionsTest_50, ResetOptions_ResetsPaths_WhenTrue_50)
{
    ASSERT_EQ(*opt_mgr.database_path, "db_initial");
    ASSERT_EQ(*opt_mgr.image_path, "img_initial");

    opt_mgr.ResetOptions(true);

    EXPECT_EQ(*opt_mgr.database_path, "");
    EXPECT_EQ(*opt_mgr.image_path, "");
}

TEST_F(OptionManagerResetOptionsTest_50, ResetOptions_ReplacesMapper_WhenTrue_50)
{
    auto old_mapper = opt_mgr.mapper;

    opt_mgr.ResetOptions(true);

    EXPECT_NE(opt_mgr.mapper, old_mapper);      // new instance created
    // Nothing else is tested because internal values are not observable
}

TEST_F(OptionManagerResetOptionsTest_50, ResetOptions_ReplacesGravityRefiner_WhenTrue_50)
{
    auto old_refiner = opt_mgr.gravity_refiner;

    opt_mgr.ResetOptions(true);

    EXPECT_NE(opt_mgr.gravity_refiner, old_refiner); // new instance created
}

//
// ─────────────────────────────────────────────────────────────
//   TESTS FOR ResetOptions(reset_paths = false)
// ─────────────────────────────────────────────────────────────
//

TEST_F(OptionManagerResetOptionsTest_50, ResetOptions_DoesNotResetPaths_WhenFalse_50)
{
    std::string expected_db = *opt_mgr.database_path;
    std::string expected_img = *opt_mgr.image_path;

    opt_mgr.ResetOptions(false);

    EXPECT_EQ(*opt_mgr.database_path, expected_db);   // unchanged
    EXPECT_EQ(*opt_mgr.image_path, expected_img);     // unchanged
}

TEST_F(OptionManagerResetOptionsTest_50, ResetOptions_ReplacesMapper_WhenFalse_50)
{
    auto old_mapper = opt_mgr.mapper;

    opt_mgr.ResetOptions(false);

    EXPECT_NE(opt_mgr.mapper, old_mapper);    // still replaced
}

TEST_F(OptionManagerResetOptionsTest_50, ResetOptions_ReplacesGravityRefiner_WhenFalse_50)
{
    auto old_refiner = opt_mgr.gravity_refiner;

    opt_mgr.ResetOptions(false);

    EXPECT_NE(opt_mgr.gravity_refiner, old_refiner);   // still replaced
}

//
// ─────────────────────────────────────────────────────────────
//   Boundary / Special Cases
// ─────────────────────────────────────────────────────────────
//

TEST_F(OptionManagerResetOptionsTest_50, ResetOptions_AllPointersAreValidAfterCall_50)
{
    opt_mgr.ResetOptions(true);

    EXPECT_NE(opt_mgr.database_path, nullptr);
    EXPECT_NE(opt_mgr.image_path, nullptr);
    EXPECT_NE(opt_mgr.mapper, nullptr);
    EXPECT_NE(opt_mgr.gravity_refiner, nullptr);
}

