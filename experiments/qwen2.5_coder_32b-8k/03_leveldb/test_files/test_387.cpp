#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/iterator.h"

#include "leveldb/comparator.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockComparator : public Comparator {

public:

    MOCK_METHOD2(Compare, int(const Slice& a, const Slice& b));

    MOCK_CONST_METHOD0(Name, const char*());

    MOCK_METHOD2(FindShortestSeparator, void(std::string* start, const Slice& limit));

    MOCK_METHOD1(FindShortSuccessor, void(std::string* key));

};



class MockIterator : public Iterator {

public:

    MOCK_METHOD0(Valid, bool());

    MOCK_METHOD0(SeekToFirst, void());

    MOCK_METHOD0(SeekToLast, void());

    MOCK_METHOD1(Seek, void(const Slice& target));

    MOCK_METHOD0(Next, void());

    MOCK_METHOD0(Prev, void());

    MOCK_METHOD0(key, const Slice());

    MOCK_METHOD0(value, const Slice());

    MOCK_METHOD0(status, const Status());

};



class MergingIteratorTest_387 : public ::testing::Test {

protected:

    MockComparator comparator_;

};



TEST_F(MergingIteratorTest_387, NewMergingIteratorWithZeroChildren_ReturnsEmptyIterator_387) {

    Iterator* iter = NewMergingIterator(&comparator_, nullptr, 0);

    EXPECT_TRUE(iter->Valid() == false); // Assuming empty iterator is invalid

    delete iter;

}



TEST_F(MergingIteratorTest_387, NewMergingIteratorWithOneChild_ReturnsThatIterator_387) {

    MockIterator mock_iter;

    Iterator* children[] = { &mock_iter };

    Iterator* iter = NewMergingIterator(&comparator_, children, 1);

    EXPECT_EQ(iter, &mock_iter);

}



TEST_F(MergingIteratorTest_387, NewMergingIteratorWithMultipleChildren_ReturnsMergingIterator_387) {

    MockIterator mock_iters[3];

    Iterator* children[] = { &mock_iters[0], &mock_iters[1], &mock_iters[2] };

    Iterator* iter = NewMergingIterator(&comparator_, children, 3);

    EXPECT_NE(iter, &mock_iters[0]);

    EXPECT_NE(iter, &mock_iters[1]);

    EXPECT_NE(iter, &mock_iters[2]);

    delete iter;

}
