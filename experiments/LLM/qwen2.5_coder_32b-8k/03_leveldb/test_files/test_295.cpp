#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "table/block.h"



using namespace leveldb;

using ::testing::Eq;



class BlockTest_295 : public ::testing::Test {

protected:

    class MockComparator : public Comparator {

    public:

        MOCK_METHOD(int, Compare, (const Slice& a, const Slice& b) const, (override));

        MOCK_METHOD(const char*, Name, (), (const override));

        MOCK_METHOD(void, FindShortestSeparator, (std::string* start, const Slice& limit) const, (override));

        MOCK_METHOD(void, FindShortSuccessor, (std::string* key) const, (override));

    };



    BlockContents contents;

    MockComparator comparator;



    void SetUp() override {

        contents.data = "dummy data";

        contents.heap_allocated = false;

        block = new Block(contents);

    }



    void TearDown() override {

        delete block;

    }



    Block* block;

};



TEST_F(BlockTest_295, SizeReturnsCorrectValue_295) {

    EXPECT_EQ(block->size(), contents.data.size());

}



TEST_F(BlockTest_295, NewIteratorCreatesValidIterator_295) {

    Iterator* iterator = block->NewIterator(&comparator);

    EXPECT_NE(iterator, nullptr);

    delete iterator;

}



TEST_F(BlockTest_295, NewIteratorUsesProvidedComparator_295) {

    EXPECT_CALL(comparator, Compare(::testing::_, ::testing::_)).Times(0); // No comparison expected in construction

    Iterator* iterator = block->NewIterator(&comparator);

    delete iterator;

}



TEST_F(BlockTest_295, SizeHandlesEmptyData_295) {

    contents.data = "";

    Block empty_block(contents);

    EXPECT_EQ(empty_block.size(), 0U);

}
