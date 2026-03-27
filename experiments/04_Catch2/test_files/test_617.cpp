#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_textflow.hpp"

#include <sstream>



using namespace Catch::TextFlow;



TEST_F(ColumnTest_617, DefaultConstructorInitializesWidthAndIndent_617) {

    Column col("test");

    EXPECT_EQ(col.width(), 79);

    EXPECT_EQ(col.indent(), 0);

}



TEST_F(ColumnTest_617, WidthSetterAndGettersWorkCorrectly_617) {

    Column col("test");

    col.width(50);

    EXPECT_EQ(col.width(), 50);

}



TEST_F(ColumnTest_617, IndentSetterAndGettersWorkCorrectly_617) {

    Column col("test");

    col.indent(10);

    EXPECT_EQ(col.indent(), 10);

}



TEST_F(ColumnTest_617, InitialIndentSetterAndGettersWorkCorrectly_617) {

    Column col("test");

    col.initialIndent(5);

    EXPECT_EQ(col.initialIndent(), 5);

}



TEST_F(ColumnTest_617, OperatorStreamOutputsColumnContent_617) {

    Column col("line1\nline2");

    std::ostringstream oss;

    oss << col;

    EXPECT_EQ(oss.str(), "line1\nline2");

}



TEST_F(ColumnTest_617, MultipleLinesAreOutputCorrectly_617) {

    Column col("line1\nline2\nline3");

    std::ostringstream oss;

    oss << col;

    EXPECT_EQ(oss.str(), "line1\nline2\nline3");

}



TEST_F(ColumnTest_617, SingleLineIsOutputCorrectly_617) {

    Column col("singleline");

    std::ostringstream oss;

    oss << col;

    EXPECT_EQ(oss.str(), "singleline");

}



TEST_F(ColumnTest_617, EmptyColumnOutputsNothing_617) {

    Column col("");

    std::ostringstream oss;

    oss << col;

    EXPECT_EQ(oss.str(), "");

}
