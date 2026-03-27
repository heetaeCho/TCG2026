// File: rotation_estimator_solve_irls_test_30.cc

#include <gtest/gtest.h>

#include <Eigen/Dense>
#include <Eigen/SparseCore>

#include "glomap/estimators/global_rotation_averaging.h"
#include "glomap/scene/view_graph.h"

namespace glomap {

// Minimal stand-in in case the concrete definition is not visible in this TU.
// Only the fields used by SolveIRLS are modeled here.
struct ImagePairTempInfo {
  image_pair_t index = 0;
  bool has_gravity = false;
  double xz_error = 0.0;
};

// Testable subclass that exposes the protected SolveIRLS and allows
// controlled initialization of internal state without re-implementing logic.
class TestableRotationEstimator_30 : public RotationEstimator {
public:
  explicit TestableRotationEstimator_30(const RotationEstimatorOptions& options)
      : RotationEstimator(options) {}

  // Expose the protected SolveIRLS so tests can call it.
  bool CallSolveIRLS(const ViewGraph& view_graph,
                     std::unordered_map<frame_t, Frame>& frames,
                     std::unordered_map<image_t, Image>& images) {
    return SolveIRLS(view_graph, frames, images);
  }

  // Helpers to prepare a minimal, consistent state for SolveIRLS.
  void SetSparseMatrix(const Eigen::SparseMatrix<double>& A) { sparse_matrix_ = A; }

  void SetWeights(const Eigen::ArrayXd& w) { weights_ = w; }

  void SetTangentSpaceResidual(const Eigen::VectorXd& r) {
    tangent_space_residual_ = r;
  }

  std::unordered_map<image_pair_t, ImagePairTempInfo>& MutableRelTempInfo() {
    return rel_temp_info_;
  }
};

}  // namespace glomap

// ---------------------------------------------------------------------------
// Test fixture
// ---------------------------------------------------------------------------

class RotationEstimatorSolveIRLSTest_30 : public ::testing::Test {
protected:
  glomap::RotationEstimatorOptions options_;
  glomap::ViewGraph view_graph_;
  std::unordered_map<glomap::frame_t, glomap::Frame> frames_;
  std::unordered_map<glomap::image_t, glomap::Image> images_;

  // Utility: create a small identity sparse matrix.
  static Eigen::SparseMatrix<double> MakeIdentitySparse(int n) {
    Eigen::SparseMatrix<double> A(n, n);
    A.setIdentity();  // Eigen provides this for SparseMatrix
    return A;
  }
};

// ---------------------------------------------------------------------------
// Normal operation: well-formed system, positive iterations, no NaN weights.
// Expect SolveIRLS to succeed and return true.
// ---------------------------------------------------------------------------

TEST_F(RotationEstimatorSolveIRLSTest_30,
       SolveIRLSReturnsTrueWithSimpleSystem_30) {
  options_.max_num_irls_iterations = 1;
  // Keep default weight_type (e.g., GEMAN_MCCLURE) so NaN is unlikely.

  glomap::TestableRotationEstimator_30 estimator(options_);

  const int m = 3;
  // Prepare a minimal consistent linear system.
  Eigen::SparseMatrix<double> A = MakeIdentitySparse(m);
  Eigen::ArrayXd weights = Eigen::ArrayXd::Ones(m);
  Eigen::VectorXd residual = Eigen::VectorXd::Zero(m);

  estimator.SetSparseMatrix(A);
  estimator.SetWeights(weights);
  estimator.SetTangentSpaceResidual(residual);

  const bool success = estimator.CallSolveIRLS(view_graph_, frames_, images_);
  EXPECT_TRUE(success);
}

// ---------------------------------------------------------------------------
// Boundary condition: max_num_irls_iterations == 0.
// Even if no IRLS iterations are performed, the method should handle this
// configuration gracefully and still succeed (no crash, returns true).
// ---------------------------------------------------------------------------

TEST_F(RotationEstimatorSolveIRLSTest_30,
       SolveIRLSHandlesZeroIterationsGracefully_30) {
  options_.max_num_irls_iterations = 0;

  glomap::TestableRotationEstimator_30 estimator(options_);

  const int m = 3;
  Eigen::SparseMatrix<double> A = MakeIdentitySparse(m);
  Eigen::ArrayXd weights = Eigen::ArrayXd::Ones(m);
  Eigen::VectorXd residual = Eigen::VectorXd::Zero(m);

  estimator.SetSparseMatrix(A);
  estimator.SetWeights(weights);
  estimator.SetTangentSpaceResidual(residual);

  const bool success = estimator.CallSolveIRLS(view_graph_, frames_, images_);
  EXPECT_TRUE(success);
}

// ---------------------------------------------------------------------------
// Error / exceptional behavior:
// If the internally computed weight becomes NaN, SolveIRLS is expected to
// detect this and return false. We drive the branch that computes a NaN
// weight by configuring:
//  - weight_type = HALF_NORM
//  - a rel_temp_info_ entry with has_gravity = true
//  - a negative err_squared (via xz_error), which makes pow(err_squared, ..)
//    produce NaN for HALF_NORM.
// This uses only observable behavior (return value) of SolveIRLS.
// ---------------------------------------------------------------------------

TEST_F(RotationEstimatorSolveIRLSTest_30,
       SolveIRLSReturnsFalseOnNaNWeight_30) {
  // Configure options to use HALF_NORM so we can create a NaN weight.
  options_.max_num_irls_iterations = 1;
  options_.weight_type = glomap::RotationEstimatorOptions::HALF_NORM;

  glomap::TestableRotationEstimator_30 estimator(options_);

  const int m = 3;
  Eigen::SparseMatrix<double> A = MakeIdentitySparse(m);
  Eigen::ArrayXd weights = Eigen::ArrayXd::Ones(m);

  // residual[0]^2 + xz_error < 0 -> negative base for pow with non-integer exponent
  // in HALF_NORM, which yields NaN.
  Eigen::VectorXd residual = Eigen::VectorXd::Zero(m);
  estimator.SetSparseMatrix(A);
  estimator.SetWeights(weights);
  estimator.SetTangentSpaceResidual(residual);

  // Create one image pair entry that will be processed in the IRLS loop.
  auto& rel_temp_info = estimator.MutableRelTempInfo();
  glomap::ImagePairTempInfo info;
  info.index = 0;          // image_pair_pos = 0
  info.has_gravity = true; // drive "has_gravity" branch
  info.xz_error = -1.0;    // makes err_squared negative
  rel_temp_info.emplace(0, info);

  const bool success = estimator.CallSolveIRLS(view_graph_, frames_, images_);
  EXPECT_FALSE(success);
}
