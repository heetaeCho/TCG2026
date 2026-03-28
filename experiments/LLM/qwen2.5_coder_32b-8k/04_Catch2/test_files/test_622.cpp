#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_textflow.hpp"

#include <sstream>



using namespace Catch::TextFlow;



// Mock Column for testing purposes

class MockColumn {

public:

    MockColumn(const std::string& content) : m_content(content) {}



    friend std::ostream& operator<<(std::ostream& os, const MockColumn& col) {

        os << col.m_content;

        return os;

    }



private:

    std::string m_content;

};



TEST(ColumnsTest_622, SingleColumnOutput_622) {

    Columns cols;

    cols += MockColumn("Hello");



    std::ostringstream oss;

    oss << cols;



    EXPECT_EQ(oss.str(), "Hello");

}



TEST(ColumnsTest_622, MultipleColumnsOutput_622) {

    Columns cols;

    cols += MockColumn("Hello");

    cols += MockColumn("World");



    std::ostringstream oss;

    oss << cols;



    EXPECT_EQ(oss.str(), "Hello\nWorld");

}



TEST(ColumnsTest_622, EmptyColumnsOutput_622) {

    Columns cols;



    std::ostringstream oss;

    oss << cols;



    EXPECT_EQ(oss.str(), "");

}



TEST(ColumnsTest_622, SingleColumnMoveSemantics_622) {

    Columns cols;

    cols += MockColumn("Hello");



    Columns newCols = std::move(cols);



    std::ostringstream oss;

    oss << newCols;



    EXPECT_EQ(oss.str(), "Hello");

}



TEST(ColumnsTest_622, MultipleColumnsMoveSemantics_622) {

    Columns cols;

    cols += MockColumn("Hello");

    cols += MockColumn("World");



    Columns newCols = std::move(cols);



    std::ostringstream oss;

    oss << newCols;



    EXPECT_EQ(oss.str(), "Hello\nWorld");

}
