#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class ColumnConstIteratorTest_614 : public ::testing::Test {

protected:

    void SetUp() override {

        m_column = new Column("Sample text for testing.");

        m_iterator = Column::const_iterator(*m_column);

    }



    void TearDown() override {

        delete m_column;

    }



    Column* m_column;

    Column::const_iterator m_iterator;

};



TEST_F(ColumnConstIteratorTest_614, DereferenceOperator_NormalOperation_614) {

    EXPECT_EQ(*m_iterator, "Sample text for testing.");

}



TEST_F(ColumnConstIteratorTest_614, PostIncrementOperator_NormalOperation_614) {

    auto original = m_iterator;

    auto result = m_iterator++;

    EXPECT_EQ(result, original);

    EXPECT_NE(m_iterator, original);

}



TEST_F(ColumnConstIteratorTest_614, PreIncrementOperator_NormalOperation_614) {

    auto& result = ++m_iterator;

    EXPECT_EQ(&result, &m_iterator);

}



TEST_F(ColumnConstIteratorTest_614, EqualityOperator_SameIterator_614) {

    Column::const_iterator sameIterator(*m_column);

    EXPECT_TRUE(m_iterator == sameIterator);

}



TEST_F(ColumnConstIteratorTest_614, InequalityOperator_DifferentIterators_614) {

    Column::const_iterator otherColumn("Different text.");

    Column::const_iterator differentIterator(otherColumn);

    EXPECT_NE(m_iterator, differentIterator);

}



TEST_F(ColumnConstIteratorTest_614, DereferenceOperator_EmptyString_614) {

    Column emptyColumn("");

    Column::const_iterator emptyIterator(emptyColumn);

    EXPECT_EQ(*emptyIterator, "");

}
