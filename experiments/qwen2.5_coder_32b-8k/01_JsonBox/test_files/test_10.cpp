#include <gtest/gtest.h>

#include "JsonBox/OutputFilter.h"

#include <sstream>



namespace JsonBox {

    class MockInserter {

    public:

        MOCK_METHOD1(insert, void(int_type));

    };

}



using namespace JsonBox;



class OutputFilterTest_10 : public ::testing::Test {

protected:

    std::stringstream ss;

    MockInserter mockInserter;

    OutputFilter<MockInserter> filter;



    OutputFilterTest_10() : filter(ss.rdbuf(), mockInserter) {}

};



TEST_F(OutputFilterTest_10, GetDestination_ReturnsCorrectPointer_10) {

    EXPECT_EQ(filter.getDestination(), ss.rdbuf());

}



TEST_F(OutputFilterTest_10, Overflow_CallsInsertWithCharacter_10) {

    int_type testChar = 'A';

    EXPECT_CALL(mockInserter, insert(testChar));

    filter.overflow(testChar);

}



TEST_F(OutputFilterTest_10, Underflow_ReturnsEOF_ByDefault_10) {

    EXPECT_EQ(filter.underflow(), traits_type::eof());

}
