// File: ./TestProjects/re2/re2/testing/repetition_walker_postvisit_test.cc

#include <climits>
#include <gtest/gtest.h>

// The production code declares Regexp and defines RepetitionWalker in parse.cc.
// We include regexp.h for the Regexp forward-declaration and types,
// and include parse.cc to get the RepetitionWalker definition.
#include "re2/regexp.h"
#include "re2/parse.cc"

namespace {

using re2::RepetitionWalker;
using re2::Regexp;

// Test fixture kept minimal; we don't touch any private/internal state.
class RepetitionWalkerTest_497 : public ::testing::Test {
protected:
  RepetitionWalker walker_;
};

TEST_F(RepetitionWalkerTest_497, ReturnsMinOfPreArgAndChildren_497) {
  int pre_arg = 4;
  int children[] = {5, 3, 7};
  int result = walker_.PostVisit(/*re=*/nullptr, /*parent_arg=*/0,
                                 pre_arg, children,
                                 /*nchild_args=*/static_cast<int>(std::size(children)));
  EXPECT_EQ(result, 3);
}

TEST_F(RepetitionWalkerTest_497, NoChildrenReturnsPreArg_497) {
  int pre_arg = 42;
  int* children = nullptr;
  int result = walker_.PostVisit(/*re=*/nullptr, /*parent_arg=*/0,
                                 pre_arg, children, /*nchild_args=*/0);
  EXPECT_EQ(result, 42);
}

TEST_F(RepetitionWalkerTest_497, HandlesNegativeNumbers_497) {
  int pre_arg = -1;
  int children[] = {2, -5, 0};
  int result = walker_.PostVisit(/*re=*/nullptr, /*parent_arg=*/0,
                                 pre_arg, children,
                                 /*nchild_args=*/static_cast<int>(std::size(children)));
  EXPECT_EQ(result, -5);
}

TEST_F(RepetitionWalkerTest_497, ChildrenAllGreaterThanPreArg_497) {
  int pre_arg = 10;
  int children[] = {20, 30, 40};
  int result = walker_.PostVisit(/*re=*/nullptr, /*parent_arg=*/0,
                                 pre_arg, children,
                                 /*nchild_args=*/static_cast<int>(std::size(children)));
  EXPECT_EQ(result, 10);
}

TEST_F(RepetitionWalkerTest_497, ChildrenAllLessThanPreArg_497) {
  int pre_arg = 10;
  int children[] = {9, 8, 8, 9};
  int result = walker_.PostVisit(/*re=*/nullptr, /*parent_arg=*/0,
                                 pre_arg, children,
                                 /*nchild_args=*/static_cast<int>(std::size(children)));
  EXPECT_EQ(result, 8);
}

TEST_F(RepetitionWalkerTest_497, SingleChild_497) {
  int pre_arg = 5;
  int children[] = {7};
  int result = walker_.PostVisit(/*re=*/nullptr, /*parent_arg=*/0,
                                 pre_arg, children, 1);
  EXPECT_EQ(result, 5);
}

TEST_F(RepetitionWalkerTest_497, WithIntExtremes_497) {
  int pre_arg = INT_MAX;
  int children[] = {INT_MAX, 0, INT_MIN};
  int result = walker_.PostVisit(/*re=*/nullptr, /*parent_arg=*/0,
                                 pre_arg, children,
                                 /*nchild_args=*/static_cast<int>(std::size(children)));
  EXPECT_EQ(result, INT_MIN);
}

}  // namespace
