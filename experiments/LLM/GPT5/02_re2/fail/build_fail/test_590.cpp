// File: pcre_constructor_590_test.cc

#include <climits>
#include <string>
#include <vector>
#include "gtest/gtest.h"

#include "TestProjects/re2/util/pcre.h"  // assumes this header exposes re2::PCRE and re2::PCRE_Options

using re2::PCRE;
using re2::PCRE_Options;

class PCRECtorTest_590 : public ::testing::Test {
protected:
  static PCRE_Options MakeOptions(PCRE::Option opt, int match_limit, int stack_limit, bool report_errors) {
    PCRE_Options o;
    o.set_option(opt);
    o.set_match_limit(match_limit);
    o.set_stack_limit(stack_limit);
    o.set_report_errors(report_errors);
    return o;
  }
};

// --- PCRE_Options behavior ---

TEST_F(PCRECtorTest_590, PCREOptions_Defaults_590) {
  PCRE_Options o;
  // Default values should be observable via getters.
  // From the header: option_ defaults to PCRE::None, limits to 0, report_errors to true.
  EXPECT_EQ(o.option(), PCRE::None);
  EXPECT_EQ(o.match_limit(), 0);
  EXPECT_EQ(o.stack_limit(), 0);
  EXPECT_TRUE(o.report_errors());
}

TEST_F(PCRECtorTest_590, PCREOptions_SettersAndGetters_590) {
  PCRE_Options o;
  o.set_option(PCRE::ANCHORED);     // Use any visible enum value from the interface
  o.set_match_limit(123);
  o.set_stack_limit(456);
  o.set_report_errors(false);

  EXPECT_EQ(o.option(), PCRE::ANCHORED);
  EXPECT_EQ(o.match_limit(), 123);
  EXPECT_EQ(o.stack_limit(), 456);
  EXPECT_FALSE(o.report_errors());
}

// --- PCRE(std::string, PCRE_Options) constructor behavior ---

TEST_F(PCRECtorTest_590, Construct_WithDefaultOptions_EmptyPattern_590) {
  PCRE_Options o;  // defaults
  // Construction should succeed and not throw (treating ctor as black box).
  EXPECT_NO_THROW({
    PCRE re(std::string(""), o);
    (void)re;
  });

  // Since options were passed by const&, they must remain unchanged after construction.
  EXPECT_EQ(o.option(), PCRE::None);
  EXPECT_EQ(o.match_limit(), 0);
  EXPECT_EQ(o.stack_limit(), 0);
  EXPECT_TRUE(o.report_errors());
}

TEST_F(PCRECtorTest_590, Construct_WithDefaultOptions_NonEmptyPattern_590) {
  PCRE_Options o;  // defaults
  EXPECT_NO_THROW({
    PCRE re(std::string("abc.*def"), o);
    (void)re;
  });
  // Options object should remain intact (cannot be modified via const&).
  EXPECT_EQ(o.option(), PCRE::None);
  EXPECT_EQ(o.match_limit(), 0);
  EXPECT_EQ(o.stack_limit(), 0);
  EXPECT_TRUE(o.report_errors());
}

TEST_F(PCRECtorTest_590, Construct_WithDisabledReportErrors_590) {
  PCRE_Options o;
  o.set_report_errors(false);
  EXPECT_NO_THROW({
    PCRE re(std::string("a(bc)?"), o);
    (void)re;
  });
  // Verify caller's options are unchanged post-construction.
  EXPECT_FALSE(o.report_errors());
}

TEST_F(PCRECtorTest_590, Construct_WithLargeLimits_590) {
  PCRE_Options o = MakeOptions(PCRE::None, INT_MAX, INT_MAX, true);
  EXPECT_NO_THROW({
    PCRE re(std::string("x+"), o);
    (void)re;
  });
  EXPECT_EQ(o.match_limit(), INT_MAX);
  EXPECT_EQ(o.stack_limit(), INT_MAX);
}

TEST_F(PCRECtorTest_590, Construct_WithZeroLimits_590) {
  PCRE_Options o = MakeOptions(PCRE::None, 0, 0, true);
  EXPECT_NO_THROW({
    PCRE re(std::string("\\d+"), o);
    (void)re;
  });
  EXPECT_EQ(o.match_limit(), 0);
  EXPECT_EQ(o.stack_limit(), 0);
}

TEST_F(PCRECtorTest_590, Construct_WithNegativeLimits_RemainsObservable_590) {
  // If negative values are allowed by the setter interface, they should round-trip
  // in the options object (we don't assume internal validation in PCRE::Init).
  PCRE_Options o = MakeOptions(PCRE::None, -1, -2, true);
  EXPECT_NO_THROW({
    PCRE re(std::string(".*"), o);
    (void)re;
  });
  EXPECT_EQ(o.match_limit(), -1);
  EXPECT_EQ(o.stack_limit(), -2);
}

TEST_F(PCRECtorTest_590, Construct_ManyTimes_DoesNotCrash_590) {
  PCRE_Options o = MakeOptions(PCRE::None, 10, 10, true);
  std::vector<std::unique_ptr<PCRE>> vec;
  vec.reserve(128);
  EXPECT_NO_THROW({
    for (int i = 0; i < 128; ++i) {
      vec.emplace_back(new PCRE(std::string("a*"), o));
    }
  });
  EXPECT_EQ(vec.size(), 128u);
}
