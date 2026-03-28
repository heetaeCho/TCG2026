#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "JsonBox/OutputFilter.h"

#include <sstream>



using namespace JsonBox;

using ::testing::_;

using ::testing::Return;



class MockInserter {

public:

    MOCK_METHOD(void, insert, (int_type ch), ());

};



class OutputFilterTest_8 : public ::testing::Test {

protected:

    std::stringstream ss;

    MockInserter mockInserter;

    OutputFilter<MockInserter> filter{ss.rdbuf(), mockInserter};

};



TEST_F(OutputFilterTest_8, UnderflowReturnsEOFByDefault_8) {

    EXPECT_EQ(filter.underflow(), std::char_traits<char_type>::eof());

}



TEST_F(OutputFilterTest_8, OverflowCallsInsertOnInserter_8) {

    int_type ch = 'A';

    EXPECT_CALL(mockInserter, insert(ch));

    filter.overflow(ch);

}
