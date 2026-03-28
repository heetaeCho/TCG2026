// File: graph_is_implicit_test_60.cc

#include "graph.h"

#include <gtest/gtest.h>

class EdgeIsImplicitTest_60 : public ::testing::Test {
protected:
  Edge edge_;

  void ConfigureEdge(size_t total_inputs,
                     int implicit_deps,
                     int order_only_deps) {
    ASSERT_LE(implicit_deps + order_only_deps,
              static_cast<int>(total_inputs));
    edge_.inputs_.assign(total_inputs, nullptr);
    edge_.implicit_deps_ = implicit_deps;
    edge_.order_only_deps_ = order_only_deps;
  }
};

// No implicit deps at all: is_implicit must be false for all indices.
TEST_F(EdgeIsImplicitTest_60, NoImplicitDepsReturnsFalseForAllInputs_60) {
  ConfigureEdge(/*total_inputs=*/4,
                /*implicit_deps=*/0,
                /*order_only_deps=*/0);

  for (size_t i = 0; i < edge_.inputs_.size(); ++i) {
    EXPECT_FALSE(edge_.is_implicit(i)) << "Index " << i << " should not be implicit";
  }
}

// Only implicit deps (no explicit, no order-only): all inputs are implicit.
TEST_F(EdgeIsImplicitTest_60, AllInputsAreImplicitWhenOnlyImplicitDeps_60) {
  ConfigureEdge(/*total_inputs=*/3,
                /*implicit_deps=*/3,
                /*order_only_deps=*/0);

  for (size_t i = 0; i < edge_.inputs_.size(); ++i) {
    EXPECT_TRUE(edge_.is_implicit(i)) << "Index " << i << " should be implicit";
  }
}

// Mixture of explicit and implicit deps, no order-only: check boundary.
TEST_F(EdgeIsImplicitTest_60, MixedExplicitAndImplicitWithoutOrderOnly_60) {
  // Layout by semantics: [explicit0, explicit1][implicit2, implicit3]
  ConfigureEdge(/*total_inputs=*/4,
                /*implicit_deps=*/2,
                /*order_only_deps=*/0);

  // Indices before implicit range.
  EXPECT_FALSE(edge_.is_implicit(0));
  EXPECT_FALSE(edge_.is_implicit(1));

  // Implicit range.
  EXPECT_TRUE(edge_.is_implicit(2));
  EXPECT_TRUE(edge_.is_implicit(3));
}

// Mixture of explicit, implicit, and order-only deps: check each region.
TEST_F(EdgeIsImplicitTest_60, ExplicitImplicitAndOrderOnlyRegions_60) {
  // By common Edge semantics:
  // total_inputs = 5, implicit_deps = 2, order_only_deps = 1
  // inputs_: [explicit0, explicit1][implicit2, implicit3][order-only4]
  ConfigureEdge(/*total_inputs=*/5,
                /*implicit_deps=*/2,
                /*order_only_deps=*/1);

  // Explicit part.
  EXPECT_FALSE(edge_.is_implicit(0));
  EXPECT_FALSE(edge_.is_implicit(1));

  // Implicit part.
  EXPECT_TRUE(edge_.is_implicit(2));
  EXPECT_TRUE(edge_.is_implicit(3));

  // Order-only part should not be implicit.
  EXPECT_TRUE(edge_.is_order_only(4));  // From Edge’s public interface.
  EXPECT_FALSE(edge_.is_implicit(4));
}

// Boundary: index just before the implicit+order-only tail should not be implicit.
TEST_F(EdgeIsImplicitTest_60, IndexBeforeTailRegionIsNotImplicit_60) {
  // Choose a configuration where there is at least one explicit
  // before any implicit/order-only.
  // total_inputs = 6, implicit_deps = 2, order_only_deps = 2
  // Expected layout: [explicit0, explicit1][implicit2, implicit3][order-only4, order-only5]
  ConfigureEdge(/*total_inputs=*/6,
                /*implicit_deps=*/2,
                /*order_only_deps=*/2);

  // This is the last explicit index.
  size_t explicit_last =
      edge_.inputs_.size() - edge_.implicit_deps_ - edge_.order_only_deps_ - 1;
  ASSERT_LT(explicit_last, edge_.inputs_.size());

  EXPECT_FALSE(edge_.is_implicit(explicit_last));
}

// Consistency: an input cannot be both implicit and order-only.
TEST_F(EdgeIsImplicitTest_60, ImplicitAndOrderOnlyAreMutuallyExclusive_60) {
  ConfigureEdge(/*total_inputs=*/5,
                /*implicit_deps=*/2,
                /*order_only_deps=*/2);

  for (size_t i = 0; i < edge_.inputs_.size(); ++i) {
    bool implicit = edge_.is_implicit(i);
    bool order_only = edge_.is_order_only(i);
    EXPECT_FALSE(implicit && order_only)
        << "Index " << i << " cannot be both implicit and order-only";
  }
}
