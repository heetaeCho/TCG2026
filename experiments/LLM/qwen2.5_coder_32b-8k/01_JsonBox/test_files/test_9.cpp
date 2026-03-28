#include <gtest/gtest.h>

#include "JsonBox/OutputFilter.h"

#include <sstream>



using namespace JsonBox;



class MockInserter {

public:

    MOCK_METHOD(void, operator<<, (int_type ch), (const));

};



TEST_F(OutputFilterTest_9, GetInserterReturnsValidReference_9) {

    std::stringstream ss;

    MockInserter mockInserter;

    OutputFilter<MockInserter> filter(ss.rdbuf(), mockInserter);

    

    Inserter& inserter = filter.getInserter();

    EXPECT_EQ(&inserter, &mockInserter);

}



TEST_F(OutputFilterTest_9, ConstructorWithInserterSetsDestinationAndInserter_9) {

    std::stringstream ss;

    MockInserter mockInserter;

    OutputFilter<MockInserter> filter(ss.rdbuf(), mockInserter);

    

    EXPECT_EQ(filter.getDestination(), ss.rdbuf());

}



TEST_F(OutputFilterTest_9, ConstructorWithoutInserterSetsDestination_9) {

    std::stringstream ss;

    OutputFilter<MockInserter> filter(ss.rdbuf());

    

    EXPECT_EQ(filter.getDestination(), ss.rdbuf());

}



TEST_F(OutputFilterTest_9, OverflowCallsInserterOperator_9) {

    std::stringstream ss;

    MockInserter mockInserter;

    OutputFilter<MockInserter> filter(ss.rdbuf(), mockInserter);

    

    const int_type testChar = 'A';

    EXPECT_CALL(mockInserter, operator<<(testChar));

    filter.overflow(testChar);

}



TEST_F(OutputFilterTest_9, UnderflowReturnsEOFByDefault_9) {

    std::stringstream ss;

    MockInserter mockInserter;

    OutputFilter<MockInserter> filter(ss.rdbuf(), mockInserter);

    

    EXPECT_EQ(filter.underflow(), traits_type::eof());

}
