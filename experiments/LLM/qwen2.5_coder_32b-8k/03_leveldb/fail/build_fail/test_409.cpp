#include <gtest/gtest.h>

#include "table/block.h"



using namespace leveldb;



class BlockIterTest : public ::testing::Test {

protected:

    class MockComparator : public Comparator {

    public:

        MOCK_METHOD2(Compare, int(const Slice&, const Slice&));

        MOCK_CONST_METHOD0(Name, const char*());

        MOCK_METHOD3(FindShortestSeparator, void(std::string*, const Slice&));

        MOCK_METHOD2(FindShortSuccessor, void(std::string*, const Slice&));

    };



    MockComparator mock_comparator;

    const char* data = "dummy_data";

    uint32_t restarts = 0;

    uint32_t num_restarts = 1;



    Block::Iter iter{&mock_comparator, data, restarts, num_restarts};



    void SetUp() override {

        // Setup if necessary

    }



    void TearDown() override {

        // Teardown if necessary

    }

};



TEST_F(BlockIterTest_409, ValidInitiallyFalse_409) {

    EXPECT_FALSE(iter.Valid());

}



TEST_F(BlockIterTest_409, KeyThrowsWhenInvalid_409) {

    EXPECT_DEATH_IF_SUPPORTED({

        iter.key();

    }, "assert");

}



TEST_F(BlockIterTest_409, ValueThrowsWhenInvalid_409) {

    EXPECT_DEATH_IF_SUPPORTED({

        iter.value();

    }, "assert");

}



TEST_F(BlockIterTest_409, SeekToFirstSetsValid_409) {

    iter.SeekToFirst();

    EXPECT_TRUE(iter.Valid());

}



TEST_F(BlockIterTest_409, SeekToLastSetsValid_409) {

    iter.SeekToLast();

    EXPECT_TRUE(iter.Valid());

}



TEST_F(BlockIterTest_409, NextAndPrevToggleValidity_409) {

    iter.SeekToFirst();

    EXPECT_TRUE(iter.Valid());

    iter.Next();

    EXPECT_FALSE(iter.Valid());

    iter.Prev();

    EXPECT_TRUE(iter.Valid());

}



TEST_F(BlockIterTest_409, SeekSetsValid_409) {

    Slice target("dummy_target");

    iter.Seek(target);

    EXPECT_TRUE(iter.Valid());

}



TEST_F(BlockIterTest_409, StatusInitiallyOk_409) {

    EXPECT_EQ(iter.status(), Status::OK());

}
