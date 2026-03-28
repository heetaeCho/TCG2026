#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "JsonBox/OutputFilter.h"



using namespace JsonBox;

using ::testing::_;

using ::testing::Return;



class MockInserter {

public:

    MOCK_METHOD2(insert, int_type(std::streambuf&, int_type));

};



TEST_F(OutputFilterTest_7, OverflowWritesCharacterToDestination_7) {

    std::stringbuf destination;

    MockInserter mockInserter;

    OutputFilter<MockInserter> filter(&destination, mockInserter);



    EXPECT_CALL(mockInserter, insert(_, 'A')).Times(1).WillOnce(Return('A'));



    int_type result = filter.overflow('A');

    EXPECT_EQ(result, 'A');

}



TEST_F(OutputFilterTest_7, OverflowCallsSyncWhenEofReceived_7) {

    std::stringbuf destination;

    MockInserter mockInserter;

    OutputFilter<MockInserter> filter(&destination, mockInserter);



    EXPECT_CALL(mockInserter, insert(_, _)).Times(0);

    EXPECT_CALL(destination, pubsync()).WillOnce(Return(0));



    int_type result = filter.overflow(std::char_traits<char>::eof());

    EXPECT_EQ(result, 0);

}



TEST_F(OutputFilterTest_7, OverflowReturnsEofWhenNoDestination_7) {

    MockInserter mockInserter;

    OutputFilter<MockInserter> filter(nullptr, mockInserter);



    EXPECT_CALL(mockInserter, insert(_, _)).Times(0);



    int_type result = filter.overflow('A');

    EXPECT_EQ(result, std::char_traits<char>::eof());

}



TEST_F(OutputFilterTest_7, OverflowHandlesMaxCharacterValue_7) {

    std::stringbuf destination;

    MockInserter mockInserter;

    OutputFilter<MockInserter> filter(&destination, mockInserter);



    EXPECT_CALL(mockInserter, insert(_, 255)).Times(1).WillOnce(Return(255));



    int_type result = filter.overflow(255);

    EXPECT_EQ(result, 255);

}



TEST_F(OutputFilterTest_7, OverflowHandlesMinCharacterValue_7) {

    std::stringbuf destination;

    MockInserter mockInserter;

    OutputFilter<MockInserter> filter(&destination, mockInserter);



    EXPECT_CALL(mockInserter, insert(_, 0)).Times(1).WillOnce(Return(0));



    int_type result = filter.overflow(0);

    EXPECT_EQ(result, 0);

}



TEST_F(OutputFilterTest_7, OverflowThrowsOnInvalidCharacter_7) {

    std::stringbuf destination;

    MockInserter mockInserter;

    OutputFilter<MockInserter> filter(&destination, mockInserter);



    EXPECT_THROW(filter.overflow(256), std::runtime_error); // Assuming invalid character throws

}
