#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_iterator.h"

#include <vector>

#include <map>



using namespace YAML::detail;



// Mock classes for SeqIter and MapIter

class MockSeqIter {

public:

    MockSeqIter() {}

    MockSeqIter& operator++();

};



class MockMapIter {

public:

    MockMapIter() {}

    MockMapIter& operator++();

    bool operator!=(const MockMapIter&) const;

    void* operator*() const;

};



MockSeqIter& MockSeqIter::operator++() {

    // Mock implementation

    return *this;

}



MockMapIter& MockMapIter::operator++() {

    // Mock implementation

    static bool first = true;

    if (first) {

        first = false;

        return *this;

    }

    throw std::out_of_range("End of range");

}



bool MockMapIter::operator!=(const MockMapIter&) const {

    // Mock comparison logic

    return true;

}



void* MockMapIter::operator*() const {

    // Mock dereference

    return nullptr;

}



TEST_F(node_iterator_baseTest_185, IncrementSequenceIterator_NormalOperation_185) {

    MockSeqIter seqIt;

    node_iterator_base<MockSeqIter> it(seqIt);

    auto& result = ++it;

    EXPECT_EQ(&result, &it);

}



TEST_F(node_iterator_baseTest_185, IncrementMapIterator_NormalOperation_185) {

    MockMapIter mapIt, mapEnd;

    node_iterator_base<MockMapIter> it(mapIt, mapEnd);

    auto& result = ++it;

    EXPECT_EQ(&result, &it);

}



TEST_F(node_iterator_baseTest_185, IncrementNoneTypeIterator_NoChange_185) {

    node_iterator_base<MockSeqIter> it;

    auto& result = ++it;

    EXPECT_EQ(&result, &it);

}



TEST_F(node_iterator_baseTest_185, IncrementMapIterator_AtEnd_NoThrow_185) {

    MockMapIter mapIt, mapEnd;

    node_iterator_base<MockMapIter> it(mapIt, mapEnd);

    try {

        ++it; // First increment

        ++it; // Second increment should throw but is handled internally

    } catch (...) {

        FAIL() << "Incrementing at end of range should not throw";

    }

}



TEST_F(node_iterator_baseTest_185, IncrementSequenceIterator_Postfix_ReturnsOldValue_185) {

    MockSeqIter seqIt;

    node_iterator_base<MockSeqIter> it(seqIt);

    auto old_it = it++;

    EXPECT_NE(&old_it, &it);

}



TEST_F(node_iterator_baseTest_185, IncrementMapIterator_Postfix_ReturnsOldValue_185) {

    MockMapIter mapIt, mapEnd;

    node_iterator_base<MockMapIter> it(mapIt, mapEnd);

    auto old_it = it++;

    EXPECT_NE(&old_it, &it);

}
