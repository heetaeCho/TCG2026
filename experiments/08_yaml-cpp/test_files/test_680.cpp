#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_iterator.h"



using namespace YAML::detail;



// Mocking external collaborators if needed

class MapIterMock {

public:

    using difference_type = std::ptrdiff_t;

    using value_type = std::pair<std::string, int>;

    using pointer = value_type*;

    using reference = value_type&;

    using iterator_category = std::forward_iterator_tag;



    MapIterMock() : m_it({}) {}

    explicit MapIterMock(const std::map<std::string, int>& map) : m_map(map), m_it(m_map.begin()) {}



    bool operator==(const MapIterMock& other) const {

        return m_it == other.m_it;

    }



    bool operator!=(const MapIterMock& other) const {

        return !(*this == other);

    }



    MapIterMock& operator++() {

        ++m_it;

        return *this;

    }



    value_type operator*() const {

        return *m_it;

    }



private:

    std::map<std::string, int> m_map;

    std::map<std::string, int>::iterator m_it;

};



TEST_F(NodeIteratorBaseTest_680, DefaultConstructorInitializesNoneType_680) {

    node_iterator_base<int> it;

    EXPECT_EQ(it.m_type, iterator_type::NoneType);

}



TEST_F(NodeIteratorBaseTest_680, SeqIterConstructorInitializesSequence_680) {

    MapIterMock seqIt;

    node_iterator_base<int> it(seqIt);

    EXPECT_EQ(it.m_type, iterator_type::Sequence);

}



TEST_F(NodeIteratorBaseTest_680, MapIterConstructorInitializesMap_680) {

    std::map<std::string, int> map = {{"key1", 1}, {"key2", 2}};

    MapIterMock mapIt(map), mapEnd;

    node_iterator_base<int> it(mapIt, mapEnd);

    EXPECT_EQ(it.m_type, iterator_type::Map);

}



TEST_F(NodeIteratorBaseTest_680, CopyConstructorConvertsType_680) {

    std::map<std::string, int> map = {{"key1", 1}, {"key2", 2}};

    MapIterMock mapIt(map), mapEnd;

    node_iterator_base<int> original(mapIt, mapEnd);

    node_iterator_base<double> copy(original);

    EXPECT_EQ(copy.m_type, iterator_type::Map);

}



TEST_F(NodeIteratorBaseTest_680, IncrementOperatorAdvancesIterator_680) {

    std::map<std::string, int> map = {{"key1", 1}, {"key2", 2}};

    MapIterMock mapIt(map), mapEnd;

    node_iterator_base<int> it(mapIt, mapEnd);

    auto originalPosition = *it;

    ++it;

    EXPECT_NE(*it, originalPosition);

}



TEST_F(NodeIteratorBaseTest_680, PostIncrementOperatorAdvancesIterator_680) {

    std::map<std::string, int> map = {{"key1", 1}, {"key2", 2}};

    MapIterMock mapIt(map), mapEnd;

    node_iterator_base<int> it(mapIt, mapEnd);

    auto originalPosition = *it;

    it++;

    EXPECT_NE(*it, originalPosition);

}



TEST_F(NodeIteratorBaseTest_680, DereferenceOperatorReturnsCurrentElement_680) {

    std::map<std::string, int> map = {{"key1", 1}};

    MapIterMock mapIt(map), mapEnd;

    node_iterator_base<int> it(mapIt, mapEnd);

    EXPECT_EQ((*it).first, "key1");

}



TEST_F(NodeIteratorBaseTest_680, ArrowOperatorReturnsCurrentElement_680) {

    std::map<std::string, int> map = {{"key1", 1}};

    MapIterMock mapIt(map), mapEnd;

    node_iterator_base<int> it(mapIt, mapEnd);

    EXPECT_EQ(it->first, "key1");

}



TEST_F(NodeIteratorBaseTest_680, EqualityOperatorComparesPositions_680) {

    std::map<std::string, int> map = {{"key1", 1}};

    MapIterMock mapIt(map), mapEnd;

    node_iterator_base<int> it1(mapIt, mapEnd);

    node_iterator_base<int> it2(mapIt, mapEnd);

    EXPECT_TRUE(it1 == it2);



    ++it1;

    EXPECT_FALSE(it1 == it2);

}



TEST_F(NodeIteratorBaseTest_680, InequalityOperatorComparesPositions_680) {

    std::map<std::string, int> map = {{"key1", 1}};

    MapIterMock mapIt(map), mapEnd;

    node_iterator_base<int> it1(mapIt, mapEnd);

    node_iterator_base<int> it2(mapIt, mapEnd);

    EXPECT_FALSE(it1 != it2);



    ++it1;

    EXPECT_TRUE(it1 != it2);

}
