#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/SVD>
#include <array>
#include "glomap/estimators/cost_function.h"

namespace glomap {
namespace {

class FetzerDsTest_92 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test with identity matrix
TEST_F(FetzerDsTest_92, IdentityMatrix_92) {
  Eigen::Matrix3d I = Eigen::Matrix3d::Identity();
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(I);
  
  // Should return 3 elements
  EXPECT_EQ(ds.size(), 3u);
  
  // Each element should be a 4D vector (finite values)
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_TRUE(std::isfinite(ds[i](j))) 
          << "ds[" << i << "](" << j << ") is not finite";
    }
  }
}

// Test with a diagonal matrix
TEST_F(FetzerDsTest_92, DiagonalMatrix_92) {
  Eigen::Matrix3d D = Eigen::Matrix3d::Zero();
  D(0, 0) = 3.0;
  D(1, 1) = 2.0;
  D(2, 2) = 1.0;
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(D);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_TRUE(std::isfinite(ds[i](j)));
    }
  }
}

// Test with a rotation matrix
TEST_F(FetzerDsTest_92, RotationMatrix_92) {
  double angle = M_PI / 4.0;
  Eigen::Matrix3d R;
  R << std::cos(angle), -std::sin(angle), 0,
       std::sin(angle),  std::cos(angle), 0,
       0,                0,               1;
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(R);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_TRUE(std::isfinite(ds[i](j)));
    }
  }
}

// Test with a general matrix
TEST_F(FetzerDsTest_92, GeneralMatrix_92) {
  Eigen::Matrix3d M;
  M << 1.0, 2.0, 3.0,
       4.0, 5.0, 6.0,
       7.0, 8.0, 10.0;
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(M);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_TRUE(std::isfinite(ds[i](j)));
    }
  }
}

// Test with a scaled identity matrix
TEST_F(FetzerDsTest_92, ScaledIdentity_92) {
  Eigen::Matrix3d M = 5.0 * Eigen::Matrix3d::Identity();
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(M);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_TRUE(std::isfinite(ds[i](j)));
    }
  }
}

// Test deterministic behavior - same input gives same output
TEST_F(FetzerDsTest_92, Deterministic_92) {
  Eigen::Matrix3d M;
  M << 1.5, -0.3, 0.7,
       0.2,  2.1, -0.4,
       -0.6, 0.8,  1.9;
  
  std::array<Eigen::Vector4d, 3> ds1 = fetzer_ds(M);
  std::array<Eigen::Vector4d, 3> ds2 = fetzer_ds(M);
  
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_DOUBLE_EQ(ds1[i](j), ds2[i](j));
    }
  }
}

// Test with a matrix that has near-zero singular values (rank deficient)
TEST_F(FetzerDsTest_92, RankDeficientMatrix_92) {
  Eigen::Matrix3d M;
  M << 1.0, 2.0, 3.0,
       2.0, 4.0, 6.0,
       3.0, 6.0, 9.0;
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(M);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_TRUE(std::isfinite(ds[i](j)));
    }
  }
}

// Test with zero matrix
TEST_F(FetzerDsTest_92, ZeroMatrix_92) {
  Eigen::Matrix3d M = Eigen::Matrix3d::Zero();
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(M);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_TRUE(std::isfinite(ds[i](j)));
    }
  }
}

// Test with negative entries
TEST_F(FetzerDsTest_92, NegativeEntries_92) {
  Eigen::Matrix3d M;
  M << -1.0, -2.0, -3.0,
       -4.0, -5.0, -6.0,
       -7.0, -8.0, -9.0;
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(M);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_TRUE(std::isfinite(ds[i](j)));
    }
  }
}

// Test with a symmetric positive definite matrix
TEST_F(FetzerDsTest_92, SymmetricPositiveDefinite_92) {
  Eigen::Matrix3d A;
  A << 2.0, 0.5, 0.1,
       0.5, 3.0, 0.3,
       0.1, 0.3, 4.0;
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(A);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_TRUE(std::isfinite(ds[i](j)));
    }
  }
}

// Test with a skew-symmetric matrix
TEST_F(FetzerDsTest_92, SkewSymmetricMatrix_92) {
  Eigen::Matrix3d M;
  M <<  0.0, -3.0,  2.0,
        3.0,  0.0, -1.0,
       -2.0,  1.0,  0.0;
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(M);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_TRUE(std::isfinite(ds[i](j)));
    }
  }
}

// Test that the output size is always 3 elements of Vector4d
TEST_F(FetzerDsTest_92, OutputSizeConsistency_92) {
  Eigen::Matrix3d M = Eigen::Matrix3d::Random();
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(M);
  
  // std::array<..., 3> always has size 3 at compile time, but verify it works
  EXPECT_EQ(ds.size(), 3u);
  
  // Each Vector4d should have 4 components
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(ds[i].size(), 4);
  }
}

// Test with a permutation matrix
TEST_F(FetzerDsTest_92, PermutationMatrix_92) {
  Eigen::Matrix3d P;
  P << 0, 1, 0,
       0, 0, 1,
       1, 0, 0;
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(P);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_TRUE(std::isfinite(ds[i](j)));
    }
  }
}

// Test with very small values
TEST_F(FetzerDsTest_92, SmallValues_92) {
  Eigen::Matrix3d M = 1e-10 * Eigen::Matrix3d::Identity();
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(M);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_TRUE(std::isfinite(ds[i](j)));
    }
  }
}

// Test with large values
TEST_F(FetzerDsTest_92, LargeValues_92) {
  Eigen::Matrix3d M = 1e6 * Eigen::Matrix3d::Identity();
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(M);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_TRUE(std::isfinite(ds[i](j)));
    }
  }
}

}  // namespace
}  // namespace glomap
