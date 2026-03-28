// File: set_move_constructor_test_594.cc

#include <gtest/gtest.h>
#include <re2/re2.h>
#include <re2/set.h>

using ::testing::UnorderedElementsAre;
using ::testing::IsEmpty;

namespace {

class RE2SetMoveTest_594 : public ::testing::Test {
protected:
  re2::RE2::Options DefaultOpts() { return re2::RE2::Options(); }
};

// Transfers compiled patterns and match behavior.
TEST_F(RE2SetMoveTest_594, MoveConstruct_TransfersPatternsAndMatches_594) {
  re2::RE2::Options opts = DefaultOpts();
  re2::RE2::Set original(opts, re2::RE2::UNANCHORED);

  std::string err;
  int i0 = original.Add("foo", &err);
  ASSERT_GE(i0, 0);
  int i1 = original.Add("bar", &err);
  ASSERT_GE(i1, 0);
  ASSERT_NE(i0, i1);

  ASSERT_TRUE(original.Compile());

  std::vector<int> before_indices;
  EXPECT_TRUE(original.Match("xx foobar yy", &before_indices));
  EXPECT_THAT(before_indices, UnorderedElementsAre(i0, i1));

  // Move-construct.
  re2::RE2::Set moved(std::move(original));

  // The moved-to set preserves match results.
  std::vector<int> after_indices;
  EXPECT_TRUE(moved.Match("xx foobar yy", &after_indices));
  EXPECT_THAT(after_indices, UnorderedElementsAre(i0, i1));
}

// Moved-from set is left valid, empty, and reusable via the public API.
TEST_F(RE2SetMoveTest_594, MoveConstruct_LeavesSourceReusableAndEmpty_594) {
  re2::RE2::Options opts = DefaultOpts();
  re2::RE2::Set src(opts, re2::RE2::UNANCHORED);

  std::string err;
  ASSERT_GE(src.Add("foo", &err), 0);
  ASSERT_TRUE(src.Compile());

  // Move away contents.
  re2::RE2::Set dst(std::move(src));

  // Moved-from set should be usable again and behave like a fresh/empty set:
  // - first Add() should return index 0
  int idx0 = src.Add("baz", &err);
  EXPECT_EQ(idx0, 0);

  // Compiles successfully and matches only the new pattern.
  ASSERT_TRUE(src.Compile());

  std::vector<int> v_has;
  EXPECT_TRUE(src.Match("..baz..", &v_has));
  EXPECT_THAT(v_has, UnorderedElementsAre(0));

  std::vector<int> v_not;
  // "foo" was moved away; the reset set should not match it.
  EXPECT_FALSE(src.Match("foo", &v_not));
  EXPECT_THAT(v_not, IsEmpty());
}

// Both destination and source remain safe to operate on even if the source was empty.
TEST_F(RE2SetMoveTest_594, MoveConstruct_SourceAndDestSafeWhenEmpty_594) {
  re2::RE2::Options opts = DefaultOpts();
  re2::RE2::Set empty_src(opts, re2::RE2::UNANCHORED);

  re2::RE2::Set dst(std::move(empty_src));

  // Compiling and matching an empty set should be safe and produce no matches.
  ASSERT_TRUE(dst.Compile());
  std::vector<int> v;
  EXPECT_FALSE(dst.Match("anything", &v));
  EXPECT_THAT(v, IsEmpty());

  // The moved-from object should also remain usable as an empty set.
  ASSERT_TRUE(empty_src.Compile());
  std::vector<int> v2;
  EXPECT_FALSE(empty_src.Match("anything", &v2));
  EXPECT_THAT(v2, IsEmpty());
}

// Options/anchor semantics are preserved across move construction (observable via matching).
TEST_F(RE2SetMoveTest_594, MoveConstruct_PreservesAnchorBehavior_594) {
  re2::RE2::Options opts = DefaultOpts();
  re2::RE2::Set anchored(opts, re2::RE2::ANCHOR_START);

  std::string err;
  ASSERT_GE(anchored.Add("foo", &err), 0);
  ASSERT_TRUE(anchored.Compile());

  // Move it.
  re2::RE2::Set moved(std::move(anchored));

  // With ANCHOR_START, "foo" must match only at the start.
  std::vector<int> v1, v2;

  EXPECT_TRUE(moved.Match("foo", &v1));
  EXPECT_FALSE(moved.Match("xxfoo", &v2));
  EXPECT_THAT(v2, IsEmpty());
}

}  // namespace
