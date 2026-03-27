#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"

#include <sstream>



using namespace Catch::TextFlow;



class ColumnTest_49 : public ::testing::Test {

protected:

    void SetUp() override {

        column = std::make_unique<Column>("Sample text");

    }



    std::unique_ptr<Column> column;

};



TEST_F(ColumnTest_49, InitialIndentSetsCorrectly_49) {

    size_t newIndent = 5;

    column->initialIndent(newIndent);

    // Since there's no direct way to check the internal state, we rely on observable behavior.

    // Here, we assume that setting initial indent should not affect the current width or other public methods.

    EXPECT_EQ(column->width(), 79); // Default width is CATCH_CONFIG_CONSOLE_WIDTH - 1

}



TEST_F(ColumnTest_49, WidthSetsCorrectly_49) {

    size_t newWidth = 50;

    column->width(newWidth);

    EXPECT_EQ(column->width(), newWidth);

}



TEST_F(ColumnTest_49, IndentSetsCorrectly_49) {

    size_t newIndent = 10;

    column->indent(newIndent);

    // Similar to initialIndent, we rely on observable behavior.

    EXPECT_EQ(column->width(), 79); // Default width is CATCH_CONFIG_CONSOLE_WIDTH - 1

}



TEST_F(ColumnTest_49, WidthBoundaryCondition_49) {

    size_t zeroWidth = 0;

    column->width(zeroWidth);

    EXPECT_EQ(column->width(), zeroWidth);



    size_t maxWidth = 1000;

    column->width(maxWidth);

    EXPECT_EQ(column->width(), maxWidth);

}



TEST_F(ColumnTest_49, IndentBoundaryCondition_49) {

    size_t zeroIndent = 0;

    column->indent(zeroIndent);

    // Assuming indent does not affect width directly.

    EXPECT_EQ(column->width(), 79); // Default width is CATCH_CONFIG_CONSOLE_WIDTH - 1



    size_t maxIndent = 1000;

    column->indent(maxIndent);

    EXPECT_EQ(column->width(), 79); // Default width is CATCH_CONFIG_CONSOLE_WIDTH - 1

}



TEST_F(ColumnTest_49, InitialIndentBoundaryCondition_49) {

    size_t zeroIndent = 0;

    column->initialIndent(zeroIndent);

    // Assuming initialIndent does not affect width directly.

    EXPECT_EQ(column->width(), 79); // Default width is CATCH_CONFIG_CONSOLE_WIDTH - 1



    size_t maxIndent = 1000;

    column->initialIndent(maxIndent);

    EXPECT_EQ(column->width(), 79); // Default width is CATCH_CONFIG_CONSOLE_WIDTH - 1

}



TEST_F(ColumnTest_49, OutputOperatorWorks_49) {

    std::ostringstream oss;

    oss << *column;

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(ColumnTest_49, OperatorPlusWithConstLhsAndRhs_49) {

    Column column2("Another text");

    Columns columns = (*column + column2);

    EXPECT_TRUE(!columns.empty());

}



TEST_F(ColumnTest_49, OperatorPlusWithMoveLhsAndRhs_49) {

    Columns columns = (std::move(*column) + std::move(*column));

    EXPECT_TRUE(!columns.empty());

}
