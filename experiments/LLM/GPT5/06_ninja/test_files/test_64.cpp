// File: ./TestProjects/ninja/tests/implicit_dep_loader_deps_log_test_64.cc

#include "graph.h"
#include "deps_log.h"

#include "gtest/gtest.h"

// Test fixture for ImplicitDepLoader-related tests.
class ImplicitDepLoaderTest_64 : public ::testing::Test {
protected:
  ImplicitDepLoaderTest_64() = default;
};

// Normal operation: when constructed with a valid DepsLog pointer,
// deps_log() should return the same pointer.
TEST_F(ImplicitDepLoaderTest_64, DepsLogReturnsSamePointer_64) {
  DepsLog deps_log;

  // Other collaborators are not relevant for this accessor test; pass nullptr.
  ImplicitDepLoader loader(
      /*state=*/nullptr,
      /*deps_log=*/&deps_log,
      /*disk_interface=*/nullptr,
      /*depfile_parser_options=*/nullptr,
      /*explanations=*/nullptr);

  EXPECT_EQ(&deps_log, loader.deps_log());
}

// Boundary condition: construction with a nullptr DepsLog pointer should be
// observable via deps_log() returning nullptr as well (if allowed by the API).
TEST_F(ImplicitDepLoaderTest_64, DepsLogCanBeNull_64) {
  ImplicitDepLoader loader(
      /*state=*/nullptr,
      /*deps_log=*/nullptr,
      /*disk_interface=*/nullptr,
      /*depfile_parser_options=*/nullptr,
      /*explanations=*/nullptr);

  EXPECT_EQ(nullptr, loader.deps_log());
}

// Const-correctness: deps_log() is declared const, so it should be callable
// on a const ImplicitDepLoader instance and still return the same pointer.
TEST_F(ImplicitDepLoaderTest_64, DepsLogCallableOnConstInstance_64) {
  DepsLog deps_log;

  ImplicitDepLoader loader(
      /*state=*/nullptr,
      /*deps_log=*/&deps_log,
      /*disk_interface=*/nullptr,
      /*depfile_parser_options=*/nullptr,
      /*explanations=*/nullptr);

  const ImplicitDepLoader& const_loader = loader;
  EXPECT_EQ(&deps_log, const_loader.deps_log());
}

// Multiple instances: each ImplicitDepLoader instance should retain and
// return its own DepsLog pointer independently.
TEST_F(ImplicitDepLoaderTest_64, DepsLogIsInstanceSpecific_64) {
  DepsLog deps_log_a;
  DepsLog deps_log_b;

  ImplicitDepLoader loader_a(
      /*state=*/nullptr,
      /*deps_log=*/&deps_log_a,
      /*disk_interface=*/nullptr,
      /*depfile_parser_options=*/nullptr,
      /*explanations=*/nullptr);

  ImplicitDepLoader loader_b(
      /*state=*/nullptr,
      /*deps_log=*/&deps_log_b,
      /*disk_interface=*/nullptr,
      /*depfile_parser_options=*/nullptr,
      /*explanations=*/nullptr);

  EXPECT_EQ(&deps_log_a, loader_a.deps_log());
  EXPECT_EQ(&deps_log_b, loader_b.deps_log());
  EXPECT_NE(loader_a.deps_log(), loader_b.deps_log());
}
