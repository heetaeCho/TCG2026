#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_iterator.h"

#include <vector>

#include <map>



using namespace YAML::detail;



class NodeIteratorBaseTest_184 : public ::testing::Test {

protected:

    using SeqIter = std::vector<int>::iterator;

    using MapIter = std::map<std::string, int>::iterator;

    using iterator_type = struct {

        enum Type { NoneType, Sequence, Map };

        Type value;

    };



    node_iterator_base<SeqIter> seqIterator;

    node_iterator_base<MapIter> mapIterator;



    NodeIteratorBaseTest_184()

        : seqIterator(SeqIter()),

          mapIterator(MapIter(), MapIter()) {}

};



TEST_F(NodeIteratorBaseTest_184, Constructor_Default_184) {

    node_iterator_base<SeqIter> defaultIt;

    EXPECT_EQ(defaultIt.m_type.value, iterator_type::NoneType);

}



TEST_F(NodeIteratorBaseTest_184, Constructor_Sequence_184) {

    std::vector<int> vec = {1, 2, 3};

    node_iterator_base<SeqIter> seqIt(vec.begin());

    EXPECT_EQ(seqIt.m_type.value, iterator_type::Sequence);

}



TEST_F(NodeIteratorBaseTest_184, Constructor_Map_184) {

    std::map<std::string, int> map = {{"a", 1}, {"b", 2}};

    node_iterator_base<MapIter> mapIt(map.begin(), map.end());

    EXPECT_EQ(mapIt.m_type.value, iterator_type::Map);

}



TEST_F(NodeIteratorBaseTest_184, OperatorEqual_SameType_184) {

    std::vector<int> vec = {1, 2, 3};

    node_iterator_base<SeqIter> seqIt1(vec.begin());

    node_iterator_base<SeqIter> seqIt2(vec.begin());



    EXPECT_TRUE(seqIt1 == seqIt2);

}



TEST_F(NodeIteratorBaseTest_184, OperatorEqual_DifferentType_184) {

    std::vector<int> vec = {1, 2, 3};

    node_iterator_base<SeqIter> seqIt(vec.begin());

    std::map<std::string, int> map;

    node_iterator_base<MapIter> mapIt(map.begin(), map.end());



    EXPECT_FALSE(seqIt == mapIt);

}



TEST_F(NodeIteratorBaseTest_184, OperatorNotEqual_SameType_184) {

    std::vector<int> vec = {1, 2, 3};

    node_iterator_base<SeqIter> seqIt1(vec.begin());

    node_iterator_base<SeqIter> seqIt2(vec.end());



    EXPECT_TRUE(seqIt1 != seqIt2);

}



TEST_F(NodeIteratorBaseTest_184, OperatorNotEqual_DifferentType_184) {

    std::vector<int> vec = {1, 2, 3};

    node_iterator_base<SeqIter> seqIt(vec.begin());

    std::map<std::string, int> map;

    node_iterator_base<MapIter> mapIt(map.begin(), map.end());



    EXPECT_TRUE(seqIt != mapIt);

}



TEST_F(NodeIteratorBaseTest_184, CopyConstructor_CompatibleTypes_184) {

    std::vector<int> vec = {1, 2, 3};

    node_iterator_base<SeqIter> seqIt(vec.begin());

    node_iterator_base<const SeqIter> constSeqIt(seqIt);



    EXPECT_EQ(constSeqIt.m_type.value, iterator_type::Sequence);

}



TEST_F(NodeIteratorBaseTest_184, CopyConstructor_IncompatibleTypes_184) {

    std::vector<int> vec = {1, 2, 3};

    node_iterator_base<SeqIter> seqIt(vec.begin());

    // This will not compile if types are incompatible

    // node_iterator_base<MapIter> mapIt(seqIt);

}
