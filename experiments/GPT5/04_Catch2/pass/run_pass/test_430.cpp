// File: test_testinvokerfixture_430.cpp
#include <gtest/gtest.h>

// Use the real header from your codebase.
#include "catch2/internal/catch_test_registry.hpp"

namespace {

// A simple probe fixture type whose observable side-effects are:
//  - Increment a global counter when the const test method is invoked
//  - Increment a global counter when the instance is destroyed
struct ProbeFixture {
  static int s_calls;
  static int s_destructions;

  void Test() const { ++s_calls; }
  ~ProbeFixture() { ++s_destructions; }

  // Utility to reset global counters between tests
  static void Reset() { s_calls = 0; s_destructions = 0; }
};

// Define static members
int ProbeFixture::s_calls = 0;
int ProbeFixture::s_destructions = 0;

}  // namespace

// -------------------- Tests --------------------

TEST(TestInvokerFixtureTest_430, PrepareThenInvoke_CallsMethodOnce_430) {
  ProbeFixture::Reset();

  // Construct invoker with pointer to const member function
  Catch::TestInvokerFixture<ProbeFixture> invoker(&ProbeFixture::Test);

  invoker.prepareTestCase();
  invoker.invoke();

  EXPECT_EQ(ProbeFixture::s_calls, 1) << "invoke() should call the test method exactly once";
  EXPECT_EQ(ProbeFixture::s_destructions, 0)
      << "Fixture should not be destroyed before tearDownTestCase()";
}

TEST(TestInvokerFixtureTest_430, MultipleInvoke_AfterSinglePrepare_CallsMethodEachTime_430) {
  ProbeFixture::Reset();

  Catch::TestInvokerFixture<ProbeFixture> invoker(&ProbeFixture::Test);

  invoker.prepareTestCase();
  invoker.invoke();
  invoker.invoke();

  EXPECT_EQ(ProbeFixture::s_calls, 2)
      << "Multiple invoke() calls after a single prepareTestCase() should call the method each time";
  EXPECT_EQ(ProbeFixture::s_destructions, 0)
      << "Fixture should still be alive until tearDownTestCase()";
}

TEST(TestInvokerFixtureTest_430, TearDown_DestroysFixture_430) {
  ProbeFixture::Reset();

  Catch::TestInvokerFixture<ProbeFixture> invoker(&ProbeFixture::Test);

  invoker.prepareTestCase();

  // Before tearDown, no destructions should have happened.
  EXPECT_EQ(ProbeFixture::s_destructions, 0);

  invoker.tearDownTestCase();

  // After tearDown, the fixture should be destroyed exactly once.
  EXPECT_EQ(ProbeFixture::s_destructions, 1)
      << "tearDownTestCase() should release the fixture instance";
}

TEST(TestInvokerFixtureTest_430, RePrepareAfterTearDown_AllowsNewInvocation_430) {
  ProbeFixture::Reset();

  Catch::TestInvokerFixture<ProbeFixture> invoker(&ProbeFixture::Test);

  // First lifecycle
  invoker.prepareTestCase();
  invoker.invoke();
  invoker.tearDownTestCase();

  // At this point, one call and one destruction should have happened.
  ASSERT_EQ(ProbeFixture::s_calls, 1);
  ASSERT_EQ(ProbeFixture::s_destructions, 1);

  // Second lifecycle (ensure the invoker can be reused)
  invoker.prepareTestCase();
  invoker.invoke();
  invoker.tearDownTestCase();

  EXPECT_EQ(ProbeFixture::s_calls, 2)
      << "Second lifecycle should successfully call the method again";
  EXPECT_EQ(ProbeFixture::s_destructions, 2)
      << "Second tearDown should destroy the second fixture instance";
}
