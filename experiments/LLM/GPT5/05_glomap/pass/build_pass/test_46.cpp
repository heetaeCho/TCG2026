#include <gtest/gtest.h>
#include <memory>

#include "glomap/controllers/option_manager.h"
#include "glomap/controllers/global_mapper.h"

namespace {

// Test fixture for OptionManager::AddTriangulatorOptions.
class OptionManagerTriangulatorTest_46 : public ::testing::Test {
protected:
    glomap::OptionManager option_manager_{false};
    std::shared_ptr<glomap::GlobalMapperOptions> mapper_;

    void SetUp() override {
        mapper_ = std::make_shared<glomap::GlobalMapperOptions>();
        // Wire the mapper into the option manager via the public interface.
        option_manager_.mapper = mapper_;
    }
};

}  // namespace

// Verifies that AddTriangulatorOptions can be called and does not modify
// preconfigured triangulator option values.
// This treats the function as a black box and checks only the observable
// state of the public dependency (GlobalMapperOptions).
TEST_F(OptionManagerTriangulatorTest_46,
       AddTriangulatorOptions_DoesNotChangePreconfiguredValues_46) {
    ASSERT_NE(mapper_, nullptr);

    // Set non-default values before registering options.
    mapper_->opt_triangulator.tri_complete_max_reproj_error = 31.0;
    mapper_->opt_triangulator.tri_merge_max_reproj_error = 32.0;
    mapper_->opt_triangulator.tri_min_angle = 33.0;
    mapper_->opt_triangulator.min_num_matches = 34;

    // Call the method under test. We only assume it registers options.
    EXPECT_NO_THROW(option_manager_.AddTriangulatorOptions());

    // Check that the observable state on the mapper has not been altered.
    EXPECT_DOUBLE_EQ(31.0,
                     mapper_->opt_triangulator.tri_complete_max_reproj_error);
    EXPECT_DOUBLE_EQ(32.0,
                     mapper_->opt_triangulator.tri_merge_max_reproj_error);
    EXPECT_DOUBLE_EQ(33.0, mapper_->opt_triangulator.tri_min_angle);
    EXPECT_EQ(34, mapper_->opt_triangulator.min_num_matches);
}

// Verifies that AddTriangulatorOptions is safe to call multiple times and
// does not override already adjusted triangulator values on subsequent calls.
// This indirectly tests the "added_triangulation_options_" guarding behavior
// through observable state only.
TEST_F(OptionManagerTriangulatorTest_46,
       AddTriangulatorOptions_IdempotentOnSubsequentCalls_46) {
    ASSERT_NE(mapper_, nullptr);

    // Initial values before first registration.
    mapper_->opt_triangulator.tri_complete_max_reproj_error = 10.0;
    mapper_->opt_triangulator.tri_merge_max_reproj_error = 11.0;
    mapper_->opt_triangulator.tri_min_angle = 12.0;
    mapper_->opt_triangulator.min_num_matches = 13;

    // First call: should succeed without side effects beyond registration.
    option_manager_.AddTriangulatorOptions();

    // Simulate user / application code changing the values after options
    // have been registered.
    mapper_->opt_triangulator.tri_complete_max_reproj_error = 1.0;
    mapper_->opt_triangulator.tri_merge_max_reproj_error = 2.0;
    mapper_->opt_triangulator.tri_min_angle = 3.0;
    mapper_->opt_triangulator.min_num_matches = 4;

    // Second call: should not override or disturb the changed values.
    EXPECT_NO_THROW(option_manager_.AddTriangulatorOptions());

    EXPECT_DOUBLE_EQ(1.0,
                     mapper_->opt_triangulator.tri_complete_max_reproj_error);
    EXPECT_DOUBLE_EQ(2.0,
                     mapper_->opt_triangulator.tri_merge_max_reproj_error);
    EXPECT_DOUBLE_EQ(3.0, mapper_->opt_triangulator.tri_min_angle);
    EXPECT_EQ(4, mapper_->opt_triangulator.min_num_matches);
}
