#include <gtest/gtest.h>

#include "leveldb/c.h"

#include "leveldb/comparator.h"



class ComparatorMock : public leveldb::Comparator {

public:

    MOCK_CONST_METHOD2(Compare, int(const leveldb::Slice&, const leveldb::Slice&));

    MOCK_CONST_METHOD0(Name, const char*());

    MOCK_METHOD1(FindShortestSeparator, void(std::string*, const leveldb::Slice&));

    MOCK_METHOD1(FindShortSuccessor, void(std::string*));

};



class OptionsTest_253 : public ::testing::Test {

protected:

    leveldb_options_t options;

    ComparatorMock comparator_mock;



    virtual void SetUp() {

        new (&options) leveldb_options_t();  // Placement new to initialize the struct

    }



    virtual void TearDown() {

        options.~leveldb_options_t();  // Explicitly call destructor for placement new

    }

};



TEST_F(OptionsTest_253, SetComparator_NormalOperation_253) {

    leveldb_comparator_t* comparator = reinterpret_cast<leveldb_comparator_t*>(&comparator_mock);

    leveldb_options_set_comparator(&options, comparator);



    EXPECT_EQ(options.rep.comparator, comparator);

}



TEST_F(OptionsTest_253, SetComparator_BoundaryCondition_NullComparator_253) {

    leveldb_comparator_t* comparator = nullptr;

    leveldb_options_set_comparator(&options, comparator);



    EXPECT_EQ(options.rep.comparator, comparator);

}
