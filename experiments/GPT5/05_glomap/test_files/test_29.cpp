// File: global_rotation_averaging_solve_l1_regression_test_29.cc

#include <gtest/gtest.h>

#include <unordered_map>
#include <limits>

#include <Eigen/Core>
#include <Eigen/SparseCore>

// Include the headers under test.
#include "glomap/estimators/global_rotation_averaging.h"
#include "glomap/scene/view_graph.h"

//
// Stub for external dependency: colmap::LeastAbsoluteDeviationSolver
// We treat this as an external collaborator and provide a simple
// controllable implementation for testing.
//

namespace colmap {

class LeastAbsoluteDeviationSolver {
 public:
  struct Options {
    enum SolverType {
      SupernodalCholmodLLT
    };

    int max_num_iterations = 0;
    SolverType solver_type = SupernodalCholmodLLT;
  };

  LeastAbsoluteDeviationSolver(const Options& /*options*/,
                               const Eigen::SparseMatrix<double>& /*A*/) {}

  // Static controls for test behavior.
  static bool produce_nan_step;
  static int num_solve_calls;

  void Solve(const Eigen::VectorXd& b, Eigen::VectorXd* x) const {
    ++num_solve_calls;
    if (x == nullptr) {
      return;
    }

    // Ensure the vector has at least one entry so NaN checks work.
    if (x->size() == 0) {
      x->conservativeResize(1);
    }

    if (produce_nan_step) {
      x->setConstant(std::numeric_limits<double>::quiet_NaN());
    } else {
      // Produce a simple finite step (reusing b's size if non-zero).
      if (b.size() > 0) {
        x->conservativeResize(b.size());
      }
      x->setConstant(1.0);
    }
  }
};

// Static member definitions.
bool LeastAbsoluteDeviationSolver::produce_nan_step = false;
int LeastAbsoluteDeviationSolver::num_solve_calls = 0;

}  // namespace colmap

//
// Testable wrapper to access the protected SolveL1Regression method
// without touching internal state directly.
//

class TestableRotationEstimator_29 : public glomap::RotationEstimator {
 public:
  explicit TestableRotationEstimator_29(
      const glomap::RotationEstimatorOptions& options)
      : glomap::RotationEstimator(options) {}

  bool CallSolveL1Regression(const glomap::ViewGraph& view_graph,
                             std::unordered_map<frame_t, Frame>& frames,
                             std::unordered_map<image_t, Image>& images) {
    return SolveL1Regression(view_graph, frames, images);
  }
};

class RotationEstimatorSolveL1RegressionTest_29 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Reset stub solver controls before each test.
    colmap::LeastAbsoluteDeviationSolver::produce_nan_step = false;
    colmap::LeastAbsoluteDeviationSolver::num_solve_calls = 0;
  }
};

//
// Normal operation: solver produces finite step vector,
// method should return true and call the solver at least once.
//

TEST_F(RotationEstimatorSolveL1RegressionTest_29,
       ReturnsTrueWhenSolverProducesFiniteStep_29) {
  glomap::RotationEstimatorOptions options;
  // Allow at least one iteration.
  options.max_num_l1_iterations = 3;

  TestableRotationEstimator_29 estimator(options);
  glomap::ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  colmap::LeastAbsoluteDeviationSolver::produce_nan_step = false;

  const bool result =
      estimator.CallSolveL1Regression(view_graph, frames, images);

  EXPECT_TRUE(result);
  // With a positive max_num_l1_iterations, the solver must be called
  // at least once before any convergence or error check.
  EXPECT_GE(colmap::LeastAbsoluteDeviationSolver::num_solve_calls, 1);
}

//
// Error case: solver writes NaNs into the step vector,
// SolveL1Regression should detect this and return false,
// exiting after the first iteration.
//

TEST_F(RotationEstimatorSolveL1RegressionTest_29,
       ReturnsFalseWhenSolverProducesNaNStep_29) {
  glomap::RotationEstimatorOptions options;
  options.max_num_l1_iterations = 5;

  TestableRotationEstimator_29 estimator(options);
  glomap::ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  colmap::LeastAbsoluteDeviationSolver::produce_nan_step = true;

  const bool result =
      estimator.CallSolveL1Regression(view_graph, frames, images);

  EXPECT_FALSE(result);
  // NaN should cause an early return from the first iteration.
  EXPECT_EQ(colmap::LeastAbsoluteDeviationSolver::num_solve_calls, 1);
}

//
// Boundary condition: max_num_l1_iterations == 0.
// The for-loop body should never execute, so the solver's Solve()
// must not be called, and the method should still return true.
//

TEST_F(RotationEstimatorSolveL1RegressionTest_29,
       ZeroMaxIterationsSkipsSolverAndReturnsTrue_29) {
  glomap::RotationEstimatorOptions options;
  options.max_num_l1_iterations = 0;

  TestableRotationEstimator_29 estimator(options);
  glomap::ViewGraph view_graph;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  const bool result =
      estimator.CallSolveL1Regression(view_graph, frames, images);

  EXPECT_TRUE(result);
  EXPECT_EQ(colmap::LeastAbsoluteDeviationSolver::num_solve_calls, 0);
}
