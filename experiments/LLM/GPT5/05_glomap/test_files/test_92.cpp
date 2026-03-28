// File: fetzer_ds_test_92.cc

#include <array>
#include <cmath>

#include <gtest/gtest.h>
#include <Eigen/Core>

#include "glomap/estimators/cost_function.h"

namespace glomap {

class FetzerDsTest_92 : public ::testing::Test {};

// Basic sanity: identity matrix should be processed deterministically and consistently.
TEST_F(FetzerDsTest_92, DeterministicForIdentity_92) {
  Eigen::Matrix3d i1_G_i0 = Eigen::Matrix3d::Identity();

  auto ds1 = fetzer_ds(i1_G_i0);
  auto ds2 = fetzer_ds(i1_G_i0);

  // std::array should always have size 3, but we still check observable interface.
  EXPECT_EQ(static_cast<std::size_t>(3), ds1.size());
  EXPECT_EQ(static_cast<std::size_t>(3), ds2.size());

  for (std::size_t k = 0; k < 3; ++k) {
    EXPECT_TRUE(ds1[k].isApprox(ds2[k]))
        << "Output at index " << k << " is not deterministic for identity input.";
  }
}

// Boundary-like input: zero matrix should not throw and should yield finite outputs.
TEST_F(FetzerDsTest_92, HandlesZeroMatrixWithoutNaNOrInf_92) {
  Eigen::Matrix3d i1_G_i0 = Eigen::Matrix3d::Zero();

  std::array<Eigen::Vector4d, 3> ds;

  ASSERT_NO_THROW({
    ds = fetzer_ds(i1_G_i0);
  });

  EXPECT_EQ(static_cast<std::size_t>(3), ds.size());

  // Check all components are finite numbers.
  for (std::size_t k = 0; k < 3; ++k) {
    for (int i = 0; i < ds[k].size(); ++i) {
      double value = ds[k](i);
      EXPECT_TRUE(std::isfinite(value))
          << "Non-finite value in output for zero matrix at vector " << k
          << ", component " << i << ": " << value;
    }
  }
}

// Normal operation on a generic, non-trivial matrix: no throw and all outputs finite.
TEST_F(FetzerDsTest_92, GenericMatrixProducesFiniteOutputs_92) {
  Eigen::Matrix3d i1_G_i0;
  // A generic, non-symmetric, non-diagonal matrix to exercise SVD.
  i1_G_i0 << 1.2, -0.7, 2.3,
             0.5,  3.1, -1.4,
             -2.0, 0.8, 0.9;

  std::array<Eigen::Vector4d, 3> ds;

  ASSERT_NO_THROW({
    ds = fetzer_ds(i1_G_i0);
  });

  EXPECT_EQ(static_cast<std::size_t>(3), ds.size());

  for (std::size_t k = 0; k < 3; ++k) {
    for (int i = 0; i < ds[k].size(); ++i) {
      double value = ds[k](i);
      EXPECT_TRUE(std::isfinite(value))
          << "Non-finite value in output for generic matrix at vector " << k
          << ", component " << i << ": " << value;
    }
  }
}

// Sensitivity test: a small change in the input matrix should lead to a (detectably)
// different output, exercising that the function actually uses the input.
TEST_F(FetzerDsTest_92, SmallPerturbationChangesOutput_92) {
  Eigen::Matrix3d base;
  base << 0.9,  0.3, -1.1,
          -0.4, 2.5,  0.7,
          1.8, -0.6,  0.2;

  Eigen::Matrix3d perturbed = base;
  // Apply a small, but not too tiny, perturbation.
  perturbed(0, 0) += 1e-2;

  auto ds_base      = fetzer_ds(base);
  auto ds_perturbed = fetzer_ds(perturbed);

  ASSERT_EQ(static_cast<std::size_t>(3), ds_base.size());
  ASSERT_EQ(static_cast<std::size_t>(3), ds_perturbed.size());

  bool any_diff = false;
  const double tol = 1e-8;

  for (std::size_t k = 0; k < 3 && !any_diff; ++k) {
    for (int i = 0; i < ds_base[k].size(); ++i) {
      double diff = std::abs(ds_base[k](i) - ds_perturbed[k](i));
      if (diff > tol) {
        any_diff = true;
        break;
      }
    }
  }

  EXPECT_TRUE(any_diff)
      << "A small perturbation in the input matrix did not lead to any detectable "
         "change in the output.";
}

}  // namespace glomap
