#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_iterator.h"



using YAML::detail::node_iterator_base;



// Define some mock types for testing

struct SeqIter {};

struct MapIter {};

struct iterator_type {

    enum value { NoneType, Sequence, Map };

};



TEST_F(NodeIteratorBaseTest_183, EqualityOperator_NoneTypeEqual_183) {

    node_iterator_base<SeqIter> it1(iterator_type::NoneType);

    node_iterator_base<MapIter> it2(iterator_type::NoneType);

    EXPECT_TRUE(it1 == it2);

}



TEST_F(NodeIteratorBaseTest_183, EqualityOperator_SequenceEqual_183) {

    SeqIter seqIt1, seqIt2;

    node_iterator_base<SeqIter> it1(seqIt1);

    node_iterator_base<SeqIter> it2(seqIt2);

    EXPECT_FALSE(it1 == it2); // Assuming different instances are not equal

}



TEST_F(NodeIteratorBaseTest_183, EqualityOperator_SequenceSameInstanceEqual_183) {

    SeqIter seqIt;

    node_iterator_base<SeqIter> it1(seqIt);

    node_iterator_base<SeqIter> it2(seqIt);

    EXPECT_TRUE(it1 == it2); // Same instance should be equal

}



TEST_F(NodeIteratorBaseTest_183, EqualityOperator_MapEqual_183) {

    MapIter mapIt1, mapEnd1;

    MapIter mapIt2, mapEnd2;

    node_iterator_base<MapIter> it1(mapIt1, mapEnd1);

    node_iterator_base<MapIter> it2(mapIt2, mapEnd2);

    EXPECT_FALSE(it1 == it2); // Assuming different instances are not equal

}



TEST_F(NodeIteratorBaseTest_183, EqualityOperator_MapSameInstanceEqual_183) {

    MapIter mapIt, mapEnd;

    node_iterator_base<MapIter> it1(mapIt, mapEnd);

    node_iterator_base<MapIter> it2(mapIt, mapEnd);

    EXPECT_TRUE(it1 == it2); // Same instance should be equal

}



TEST_F(NodeIteratorBaseTest_183, EqualityOperator_DifferentTypesNotEqual_183) {

    SeqIter seqIt;

    MapIter mapIt, mapEnd;

    node_iterator_base<SeqIter> it1(seqIt);

    node_iterator_base<MapIter> it2(mapIt, mapEnd);

    EXPECT_FALSE(it1 == it2); // Different types should not be equal

}



TEST_F(NodeIteratorBaseTest_183, EqualityOperator_SequenceAndNoneTypeNotEqual_183) {

    SeqIter seqIt;

    node_iterator_base<SeqIter> it1(seqIt);

    node_iterator_base<MapIter> it2(iterator_type::NoneType);

    EXPECT_FALSE(it1 == it2); // Sequence and NoneType should not be equal

}



TEST_F(NodeIteratorBaseTest_183, EqualityOperator_MapAndNoneTypeNotEqual_183) {

    MapIter mapIt, mapEnd;

    node_iterator_base<MapIter> it1(mapIt, mapEnd);

    node_iterator_base<SeqIter> it2(iterator_type::NoneType);

    EXPECT_FALSE(it1 == it2); // Map and NoneType should not be equal

}
