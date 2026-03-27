// TEST_ID: 613
//
// File: yaml-cpp/node/convert_test.cpp
//
// These tests validate YAML::encode(const std::list<T, A>&) from yaml-cpp/node/convert.h
// as a black box via observable Node behavior: type/sequence-ness, size, and element values.
//
// NOTE: We intentionally avoid asserting ordering-dependent iterator behavior since the public
// interface excerpt doesn't show operator++/dereference for const_iterator. We instead verify
// contents using operator[] + as<T>() when available for sequences.

#include <gtest/gtest.h>

#include <list>
#include <string>

#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/convert.h"

namespace {

class EncodeListTest_613 : public ::testing::Test {};

TEST_F(EncodeListTest_613, EmptyListEncodesToEmptySequence_613) {
  std::list<int> input;

  YAML::Node node = YAML::encode(input);

  EXPECT_TRUE(node.IsDefined());
  EXPECT_TRUE(node.IsSequence());
  EXPECT_EQ(node.size(), 0u);
}

TEST_F(EncodeListTest_613, SingleElementListEncodesToSequenceOfSizeOne_613) {
  std::list<int> input;
  input.push_back(42);

  YAML::Node node = YAML::encode(input);

  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), 1u);

  // For sequences, operator[](size_t) is typically supported; we treat it as an observable API.
  EXPECT_EQ(node[0].as<int>(), 42);
}

TEST_F(EncodeListTest_613, MultipleElementsListEncodesToSequencePreservingValues_613) {
  std::list<int> input = {1, 2, 3, 4};

  YAML::Node node = YAML::encode(input);

  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), 4u);

  EXPECT_EQ(node[0].as<int>(), 1);
  EXPECT_EQ(node[1].as<int>(), 2);
  EXPECT_EQ(node[2].as<int>(), 3);
  EXPECT_EQ(node[3].as<int>(), 4);
}

TEST_F(EncodeListTest_613, ListWithDuplicateElementsPreservesDuplicates_613) {
  std::list<int> input = {7, 7, 8, 7};

  YAML::Node node = YAML::encode(input);

  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), 4u);

  EXPECT_EQ(node[0].as<int>(), 7);
  EXPECT_EQ(node[1].as<int>(), 7);
  EXPECT_EQ(node[2].as<int>(), 8);
  EXPECT_EQ(node[3].as<int>(), 7);
}

TEST_F(EncodeListTest_613, ListOfStringsEncodesToSequenceWithSameStrings_613) {
  std::list<std::string> input = {"alpha", "beta", "gamma"};

  YAML::Node node = YAML::encode(input);

  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), 3u);

  EXPECT_EQ(node[0].as<std::string>(), "alpha");
  EXPECT_EQ(node[1].as<std::string>(), "beta");
  EXPECT_EQ(node[2].as<std::string>(), "gamma");
}

TEST_F(EncodeListTest_613, LargeListEncodesToSequenceWithMatchingSize_613) {
  std::list<int> input;
  for (int i = 0; i < 1000; ++i) {
    input.push_back(i);
  }

  YAML::Node node = YAML::encode(input);

  ASSERT_TRUE(node.IsSequence());
  EXPECT_EQ(node.size(), 1000u);

  // Spot-check a few positions (boundary-ish) without assuming any internal optimization.
  EXPECT_EQ(node[0].as<int>(), 0);
  EXPECT_EQ(node[1].as<int>(), 1);
  EXPECT_EQ(node[998].as<int>(), 998);
  EXPECT_EQ(node[999].as<int>(), 999);
}

TEST_F(EncodeListTest_613, EncodedNodeIsIndependentOfSubsequentListMutation_613) {
  std::list<int> input = {10, 20, 30};

  YAML::Node node = YAML::encode(input);

  // Mutate the input after encoding.
  input.push_back(40);
  input.pop_front();

  // Observable expectation: previously produced node remains representing the original input.
  // We don't assume deep/shallow copy mechanism; we only assert the already-produced Node's
  // observable contents stay stable across list mutation (a reasonable API contract expectation).
  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), 3u);
  EXPECT_EQ(node[0].as<int>(), 10);
  EXPECT_EQ(node[1].as<int>(), 20);
  EXPECT_EQ(node[2].as<int>(), 30);
}

TEST_F(EncodeListTest_613, EncodingListOfNodesEmbedsNodesAsSequenceElements_613) {
  YAML::Node a(1);
  YAML::Node b("two");
  YAML::Node c;
  c = 3;

  std::list<YAML::Node> input = {a, b, c};

  YAML::Node node = YAML::encode(input);

  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), 3u);

  EXPECT_EQ(node[0].as<int>(), 1);
  EXPECT_EQ(node[1].as<std::string>(), "two");
  EXPECT_EQ(node[2].as<int>(), 3);
}

// “Exceptional or error cases (if observable)”
// For this encode(list) signature, there is no direct error channel exposed.
// We include a type-mismatch access check using as<T>(fallback) to ensure callers
// can safely read when types don't match (observable behavior through interface).
TEST_F(EncodeListTest_613, TypeMismatchReadCanUseFallback_613) {
  std::list<std::string> input = {"not-an-int"};

  YAML::Node node = YAML::encode(input);

  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), 1u);

  // If conversion fails, fallback should be returned (observable behavior).
  // This does not assume the internal conversion mechanism; it uses the public API.
  EXPECT_EQ(node[0].as<int>(-1), -1);
}

}  // namespace