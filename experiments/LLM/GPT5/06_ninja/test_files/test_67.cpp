// File: ./TestProjects/ninja/tests/dependency_scan_deps_log_test_67.cc

#include "gtest/gtest.h"

#include "graph.h"  // Contains DependencyScan (and ImplicitDepLoader, etc.)

// We treat DependencyScan as a black box and only verify observable behavior
// of the public interface: specifically, the deps_log() accessor.

class DependencyScanTest_67 : public ::testing::Test {
protected:
  // Helper to construct DependencyScan with minimal dependencies.
  // We only care about the DepsLog* parameter; others are left as nullptr.
  DependencyScan MakeScan(DepsLog* deps_log, BuildLog* build_log = nullptr) {
    State* state = nullptr;
    DiskInterface* disk = nullptr;
    const DepfileParserOptions* depfile_opts = nullptr;
    Explanations* explanations = nullptr;

    return DependencyScan(state, build_log, deps_log,
                          disk, depfile_opts, explanations);
  }
};

// Normal operation: when constructed with a non-null DepsLog*, deps_log()
// should return the exact same pointer.
TEST_F(DependencyScanTest_67, DepsLogReturnsSamePointer_67) {
  // We don't need a real DepsLog object; only pointer identity matters
  // for this accessor. We rely on DependencyScan not dereferencing it
  // in the constructor or deps_log(), treating it as an opaque handle.
  DepsLog* expected_deps_log =
      reinterpret_cast<DepsLog*>(0x1);  // opaque, never dereferenced

  DependencyScan scan = MakeScan(expected_deps_log);

  EXPECT_EQ(expected_deps_log, scan.deps_log());
}

// Boundary condition: when constructed with a nullptr DepsLog*,
// deps_log() should safely return nullptr as well.
TEST_F(DependencyScanTest_67, DepsLogHandlesNullPointer_67) {
  DepsLog* expected_deps_log = nullptr;

  DependencyScan scan = MakeScan(expected_deps_log);

  EXPECT_EQ(expected_deps_log, scan.deps_log());
}

// Const-correctness: deps_log() is declared const; calling it through
// a const reference should still return the same pointer.
TEST_F(DependencyScanTest_67, DepsLogConstAccessReturnsSamePointer_67) {
  DepsLog* expected_deps_log =
      reinterpret_cast<DepsLog*>(0x2);  // opaque, never dereferenced

  DependencyScan scan = MakeScan(expected_deps_log);

  const DependencyScan& const_scan = scan;
  EXPECT_EQ(expected_deps_log, const_scan.deps_log());
}
