// File: builder_set_build_log_test_91.cc

#include "gtest/gtest.h"

#include "build.h"
#include "build_log.h"
#include "deps_log.h"
#include "disk_interface.h"
#include "graph.h"
#include "state.h"

#include <memory>

using namespace std;

// NOTE:
// - We treat Builder and DependencyScan as black boxes.
// - We only use the public interfaces and avoid accessing any private members
//   (such as Builder::scan_).
// - SetBuildLog is documented as "Used for tests", so here we only verify that
//   it is safely callable with various arguments and does not cause observable
//   errors through the public interface we have access to.

class BuilderSetBuildLogTest_91 : public ::testing::Test {
protected:
  void SetUp() override {
    // Minimal configuration for constructing Builder.
    // We use real ninja types where possible and nullptr for optional
    // collaborators for which we don't have/need concrete implementations.

    // Default BuildConfig is fine for tests.
    config_ = BuildConfig{};

    // State / logs / disk interface are required to build a DependencyScan.
    // These are real implementations from the codebase.
    // We don't depend on their internal behavior in these tests.
    builder_ = std::unique_ptr<Builder>(
        new Builder(&state_, config_, &build_log_, &deps_log_,
                    &disk_interface_, /*status=*/nullptr,
                    /*start_time_millis=*/0));
  }

  State state_;
  BuildConfig config_;
  BuildLog build_log_;
  DepsLog deps_log_;
  RealDiskInterface disk_interface_;
  std::unique_ptr<Builder> builder_;
};

//------------------------------------------------------------------------------
// 1) Normal operation: SetBuildLog with a valid BuildLog pointer.
//------------------------------------------------------------------------------

TEST_F(BuilderSetBuildLogTest_91, SetBuildLog_WithValidLog_DoesNotCrash_91) {
  BuildLog new_log;

  // This should be safe to call and should not throw or crash.
  // We don't assert on internal state because scan_ is private and must
  // be treated as an implementation detail.
  ASSERT_NO_THROW(builder_->SetBuildLog(&new_log));
}

//------------------------------------------------------------------------------
// 2) Boundary condition: SetBuildLog with nullptr.
//   (Only checks that the call itself is accepted as part of the public API.)
//------------------------------------------------------------------------------

TEST_F(BuilderSetBuildLogTest_91, SetBuildLog_WithNullptr_DoesNotCrash_91) {
  BuildLog* null_log = nullptr;

  // Even if the implementation may or may not handle nullptr specially,
  // from the caller's perspective passing nullptr is allowed by the type
  // system. We verify that the call itself is safe.
  ASSERT_NO_THROW(builder_->SetBuildLog(null_log));
}

//------------------------------------------------------------------------------
// 3) Repeated calls: calling SetBuildLog multiple times with different logs.
//------------------------------------------------------------------------------

TEST_F(BuilderSetBuildLogTest_91,
       SetBuildLog_CalledMultipleTimes_DoesNotCrash_91) {
  BuildLog log1;
  BuildLog log2;

  ASSERT_NO_THROW(builder_->SetBuildLog(&log1));
  ASSERT_NO_THROW(builder_->SetBuildLog(&log2));
  ASSERT_NO_THROW(builder_->SetBuildLog(&log1));
}
