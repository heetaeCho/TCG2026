// File: node_iterator_base_eq_test_183.cpp
#include <gtest/gtest.h>

#include <iterator>
#include <type_traits>
#include <vector>

#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/detail/node_iterator.h"

namespace {

// Detection idiom for public nested iterator typedefs (may or may not be accessible).
template <class T, class = void>
struct has_public_seq_iter : std::false_type {};
template <class T>
struct has_public_seq_iter<T, std::void_t<typename T::SeqIter>> : std::true_type {};

template <class T, class = void>
struct has_public_map_iter : std::false_type {};
template <class T>
struct has_public_map_iter<T, std::void_t<typename T::MapIter>> : std::true_type {};

// Helper to create a std::vector for an iterator type like std::vector<X>::iterator,
// without needing to know X ahead of time.
template <class Iter>
using iter_value_t = typename std::iterator_traits<Iter>::value_type;

}  // namespace

class NodeIteratorBaseEqualTest_183 : public ::testing::Test {};

TEST_F(NodeIteratorBaseEqualTest_183, NoneTypeEqualsNoneTypeSameV_183) {
  using Iter = YAML::detail::node_iterator_base<YAML::Node>;
  Iter a;
  Iter b;
  EXPECT_TRUE(a == b);
  EXPECT_TRUE(b == a);
}

TEST_F(NodeIteratorBaseEqualTest_183, NoneTypeEqualsNoneTypeAcrossConvertibleTypes_183) {
  using Iter = YAML::detail::node_iterator_base<YAML::Node>;
  using CIter = YAML::detail::node_iterator_base<const YAML::Node>;

  Iter a;
  CIter b;

  // Templated operator== should be usable for cross-type comparisons.
  EXPECT_TRUE(a == b);
  EXPECT_TRUE(b == a);
}

TEST_F(NodeIteratorBaseEqualTest_183, DifferentIteratorTypesAreNotEqualWhenConstructible_183) {
  using Iter = YAML::detail::node_iterator_base<YAML::Node>;

  // If we can't construct sequence/map iterators from public types, we can’t test
  // cross-type mismatch behavior without touching internals.
  if constexpr (!(has_public_seq_iter<Iter>::value && has_public_map_iter<Iter>::value)) {
    GTEST_SKIP() << "SeqIter/MapIter types not publicly accessible; skipping type-mismatch test.";
  } else {
    using SeqIter = typename Iter::SeqIter;
    using MapIter = typename Iter::MapIter;

    std::vector<iter_value_t<SeqIter>> seq_storage;
    seq_storage.resize(1);
    std::vector<iter_value_t<MapIter>> map_storage;
    map_storage.resize(1);

    Iter seq_it(SeqIter(seq_storage.begin()));
    Iter map_it(MapIter(map_storage.begin()), MapIter(map_storage.end()));

    EXPECT_FALSE(seq_it == map_it);
    EXPECT_FALSE(map_it == seq_it);
  }
}

TEST_F(NodeIteratorBaseEqualTest_183, SequenceEqualitySamePosition_183) {
  using Iter = YAML::detail::node_iterator_base<YAML::Node>;
  if constexpr (!has_public_seq_iter<Iter>::value) {
    GTEST_SKIP() << "SeqIter type not publicly accessible; skipping sequence equality tests.";
  } else {
    using SeqIter = typename Iter::SeqIter;

    std::vector<iter_value_t<SeqIter>> storage;
    storage.resize(2);

    Iter a(SeqIter(storage.begin()));
    Iter b(SeqIter(storage.begin()));
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);
  }
}

TEST_F(NodeIteratorBaseEqualTest_183, SequenceInequalityDifferentPositions_183) {
  using Iter = YAML::detail::node_iterator_base<YAML::Node>;
  if constexpr (!has_public_seq_iter<Iter>::value) {
    GTEST_SKIP() << "SeqIter type not publicly accessible; skipping sequence inequality tests.";
  } else {
    using SeqIter = typename Iter::SeqIter;

    std::vector<iter_value_t<SeqIter>> storage;
    storage.resize(2);

    Iter begin_it(SeqIter(storage.begin()));
    Iter next_it(SeqIter(std::next(storage.begin())));

    EXPECT_FALSE(begin_it == next_it);
    EXPECT_FALSE(next_it == begin_it);
  }
}

TEST_F(NodeIteratorBaseEqualTest_183, MapEqualitySamePosition_183) {
  using Iter = YAML::detail::node_iterator_base<YAML::Node>;
  if constexpr (!has_public_map_iter<Iter>::value) {
    GTEST_SKIP() << "MapIter type not publicly accessible; skipping map equality tests.";
  } else {
    using MapIter = typename Iter::MapIter;

    std::vector<iter_value_t<MapIter>> storage;
    storage.resize(2);

    Iter a(MapIter(storage.begin()), MapIter(storage.end()));
    Iter b(MapIter(storage.begin()), MapIter(storage.end()));

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);
  }
}

TEST_F(NodeIteratorBaseEqualTest_183, MapInequalityDifferentPositions_183) {
  using Iter = YAML::detail::node_iterator_base<YAML::Node>;
  if constexpr (!has_public_map_iter<Iter>::value) {
    GTEST_SKIP() << "MapIter type not publicly accessible; skipping map inequality tests.";
  } else {
    using MapIter = typename Iter::MapIter;

    std::vector<iter_value_t<MapIter>> storage;
    storage.resize(2);

    Iter begin_it(MapIter(storage.begin()), MapIter(storage.end()));
    Iter next_it(MapIter(std::next(storage.begin())), MapIter(storage.end()));

    EXPECT_FALSE(begin_it == next_it);
    EXPECT_FALSE(next_it == begin_it);
  }
}

TEST_F(NodeIteratorBaseEqualTest_183, NoneTypeNotEqualToSequenceWhenConstructible_183) {
  using Iter = YAML::detail::node_iterator_base<YAML::Node>;
  if constexpr (!has_public_seq_iter<Iter>::value) {
    GTEST_SKIP() << "SeqIter type not publicly accessible; skipping None vs Sequence test.";
  } else {
    using SeqIter = typename Iter::SeqIter;

    std::vector<iter_value_t<SeqIter>> storage;
    storage.resize(1);

    Iter none_it;
    Iter seq_it(SeqIter(storage.begin()));

    EXPECT_FALSE(none_it == seq_it);
    EXPECT_FALSE(seq_it == none_it);
  }
}

TEST_F(NodeIteratorBaseEqualTest_183, NoneTypeNotEqualToMapWhenConstructible_183) {
  using Iter = YAML::detail::node_iterator_base<YAML::Node>;
  if constexpr (!has_public_map_iter<Iter>::value) {
    GTEST_SKIP() << "MapIter type not publicly accessible; skipping None vs Map test.";
  } else {
    using MapIter = typename Iter::MapIter;

    std::vector<iter_value_t<MapIter>> storage;
    storage.resize(1);

    Iter none_it;
    Iter map_it(MapIter(storage.begin()), MapIter(storage.end()));

    EXPECT_FALSE(none_it == map_it);
    EXPECT_FALSE(map_it == none_it);
  }
}

TEST_F(NodeIteratorBaseEqualTest_183, EqualityIsReflexive_183) {
  using Iter = YAML::detail::node_iterator_base<YAML::Node>;

  Iter a;
  EXPECT_TRUE(a == a);

  if constexpr (has_public_seq_iter<Iter>::value) {
    using SeqIter = typename Iter::SeqIter;
    std::vector<iter_value_t<SeqIter>> storage;
    storage.resize(1);
    Iter s(SeqIter(storage.begin()));
    EXPECT_TRUE(s == s);
  }

  if constexpr (has_public_map_iter<Iter>::value) {
    using MapIter = typename Iter::MapIter;
    std::vector<iter_value_t<MapIter>> storage;
    storage.resize(1);
    Iter m(MapIter(storage.begin()), MapIter(storage.end()));
    EXPECT_TRUE(m == m);
  }
}
`