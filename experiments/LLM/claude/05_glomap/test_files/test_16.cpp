#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <array>
#include "glomap/estimators/cost_function.h"

namespace glomap {
namespace {

class FetzerDsTest_16 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test with identity matrix
TEST_F(FetzerDsTest_16, IdentityMatrix_16) {
  Eigen::Matrix3d G = Eigen::Matrix3d::Identity();
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(G);
  
  // Just verify it returns 3 Vector4d elements without crashing
  EXPECT_EQ(ds.size(), 3u);
  
  // Each element should be a valid 4D vector (no NaN or Inf)
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_FALSE(std::isnan(ds[i](j))) << "ds[" << i << "](" << j << ") is NaN";
      EXPECT_FALSE(std::isinf(ds[i](j))) << "ds[" << i << "](" << j << ") is Inf";
    }
  }
}

// Test with a diagonal matrix (scaled identity)
TEST_F(FetzerDsTest_16, DiagonalMatrix_16) {
  Eigen::Matrix3d G = Eigen::Matrix3d::Zero();
  G(0, 0) = 3.0;
  G(1, 1) = 2.0;
  G(2, 2) = 1.0;
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(G);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_FALSE(std::isnan(ds[i](j)));
      EXPECT_FALSE(std::isinf(ds[i](j)));
    }
  }
}

// Test with a random general matrix
TEST_F(FetzerDsTest_16, GeneralMatrix_16) {
  Eigen::Matrix3d G;
  G << 1.0, 2.0, 3.0,
       4.0, 5.0, 6.0,
       7.0, 8.0, 10.0;
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(G);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_FALSE(std::isnan(ds[i](j)));
      EXPECT_FALSE(std::isinf(ds[i](j)));
    }
  }
}

// Test with a rotation matrix
TEST_F(FetzerDsTest_16, RotationMatrix_16) {
  double angle = M_PI / 4.0;
  Eigen::Matrix3d G;
  G << std::cos(angle), -std::sin(angle), 0,
       std::sin(angle),  std::cos(angle), 0,
       0,                0,               1;
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(G);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_FALSE(std::isnan(ds[i](j)));
      EXPECT_FALSE(std::isinf(ds[i](j)));
    }
  }
}

// Test with a rank-deficient (singular) matrix
TEST_F(FetzerDsTest_16, SingularMatrix_16) {
  Eigen::Matrix3d G;
  G << 1.0, 2.0, 3.0,
       2.0, 4.0, 6.0,
       3.0, 6.0, 9.0;
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(G);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_FALSE(std::isnan(ds[i](j)));
    }
  }
}

// Test with zero matrix
TEST_F(FetzerDsTest_16, ZeroMatrix_16) {
  Eigen::Matrix3d G = Eigen::Matrix3d::Zero();
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(G);
  
  EXPECT_EQ(ds.size(), 3u);
  // With zero matrix, singular values are all zero
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_FALSE(std::isnan(ds[i](j)));
    }
  }
}

// Test with negative entries
TEST_F(FetzerDsTest_16, NegativeEntries_16) {
  Eigen::Matrix3d G;
  G << -1.0, -2.0, -3.0,
       -4.0, -5.0, -6.0,
       -7.0, -8.0, -9.0;
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(G);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_FALSE(std::isnan(ds[i](j)));
    }
  }
}

// Test with a scaled identity matrix (uniform scaling)
TEST_F(FetzerDsTest_16, ScaledIdentity_16) {
  Eigen::Matrix3d G = 5.0 * Eigen::Matrix3d::Identity();
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(G);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_FALSE(std::isnan(ds[i](j)));
      EXPECT_FALSE(std::isinf(ds[i](j)));
    }
  }
}

// Test deterministic behavior: same input produces same output
TEST_F(FetzerDsTest_16, Deterministic_16) {
  Eigen::Matrix3d G;
  G << 1.5, 0.3, -0.7,
       2.1, -1.4, 0.8,
       0.6, 3.2, -2.1;
  
  std::array<Eigen::Vector4d, 3> ds1 = fetzer_ds(G);
  std::array<Eigen::Vector4d, 3> ds2 = fetzer_ds(G);
  
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_DOUBLE_EQ(ds1[i](j), ds2[i](j))
          << "Mismatch at ds[" << i << "](" << j << ")";
    }
  }
}

// Test with very small values (near-zero matrix)
TEST_F(FetzerDsTest_16, VerySmallValues_16) {
  Eigen::Matrix3d G = 1e-15 * Eigen::Matrix3d::Ones();
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(G);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_FALSE(std::isnan(ds[i](j)));
    }
  }
}

// Test with large values
TEST_F(FetzerDsTest_16, LargeValues_16) {
  Eigen::Matrix3d G;
  G << 1e6, 2e6, 3e6,
       4e6, 5e6, 6e6,
       7e6, 8e6, 1e7;
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(G);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_FALSE(std::isnan(ds[i](j)));
      EXPECT_FALSE(std::isinf(ds[i](j)));
    }
  }
}

// Test with an antisymmetric (skew-symmetric) matrix
TEST_F(FetzerDsTest_16, SkewSymmetricMatrix_16) {
  Eigen::Matrix3d G;
  G <<  0.0,  1.0, -2.0,
       -1.0,  0.0,  3.0,
        2.0, -3.0,  0.0;
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(G);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_FALSE(std::isnan(ds[i](j)));
      EXPECT_FALSE(std::isinf(ds[i](j)));
    }
  }
}

// Test with symmetric positive definite matrix
TEST_F(FetzerDsTest_16, SymmetricPositiveDefinite_16) {
  Eigen::Matrix3d A;
  A << 2.0, 1.0, 0.0,
       1.0, 3.0, 1.0,
       0.0, 1.0, 4.0;
  // A is symmetric positive definite
  
  std::array<Eigen::Vector4d, 3> ds = fetzer_ds(A);
  
  EXPECT_EQ(ds.size(), 3u);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_FALSE(std::isnan(ds[i](j)));
      EXPECT_FALSE(std::isinf(ds[i](j)));
    }
  }
}

}  // namespace
}  // namespace glomap
