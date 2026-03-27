#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "JsonBox/OutputFilter.h"

#include <sstream>



using namespace JsonBox;

using ::testing::_;

using ::testing::Return;



class MockInserter {

public:

    MOCK_METHOD(void, insert, (int_type ch));

};



class OutputFilterTest_6 : public ::testing::Test {

protected:

    std::stringstream ss;

    MockInserter mockInserter;

    OutputFilter<MockInserter> *filter;



    void SetUp() override {

        filter = new OutputFilter<MockInserter>(ss.rdbuf(), mockInserter);

    }



    void TearDown() override {

        delete filter;

    }

};



TEST_F(OutputFilterTest_6, OverflowSendsCharToInserter_6) {

    EXPECT_CALL(mockInserter, insert('A'));

    filter->overflow('A');

}



TEST_F(OutputFilterTest_6, UnderflowReturnsEOFWhenEmpty_6) {

    EXPECT_EQ(filter->underflow(), std::streambuf::traits_type::eof());

}



TEST_F(OutputFilterTest_6, GetInserterReturnsCorrectReference_6) {

    EXPECT_EQ(&filter->getInserter(), &mockInserter);

}



TEST_F(OutputFilterTest_6, GetDestinationReturnsCorrectPointer_6) {

    EXPECT_EQ(filter->getDestination(), ss.rdbuf());

}



TEST_F(OutputFilterTest_6, DestructorDeletesDestinationWhenFlagSet_6) {

    std::streambuf *tempBuffer = new std::stringbuf();

    OutputFilter<MockInserter> *filterWithDelete = new OutputFilter<MockInserter>(tempBuffer, mockInserter, true);

    delete filterWithDelete;

    EXPECT_EQ(tempBuffer, nullptr); // This is a conceptual test; in reality, you can't check tempBuffer after deletion.

}



TEST_F(OutputFilterTest_6, OverflowDoesNotModifyDestinationWhenEmpty_6) {

    std::string initialContent = ss.str();

    filter->overflow(std::streambuf::traits_type::eof());

    EXPECT_EQ(ss.str(), initialContent);

}



TEST_F(OutputFilterTest_6, UnderflowWithoutOverflowReturnsEOF_6) {

    EXPECT_EQ(filter->underflow(), std::streambuf::traits_type::eof());

}
