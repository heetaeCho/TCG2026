#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Catch2/reporters/catch_reporter_console.hpp>



using namespace Catch;

using ::testing::InSequence;



class TablePrinterTest : public ::testing::Test {

protected:

    std::ostringstream oss;

    std::vector<ColumnInfo> columnInfos;

    TablePrinter tablePrinter;



    TablePrinterTest() : tablePrinter(oss, columnInfos) {}

};



TEST_F(TablePrinterTest_757, CloseWhenNotOpen_757) {

    // Arrange

    // No need to call open()



    // Act

    tablePrinter.close();



    // Assert

    EXPECT_EQ(oss.str(), "");

}



TEST_F(TablePrinterTest_757, CloseAfterOpen_757) {

    // Arrange

    tablePrinter.open();



    // Act

    tablePrinter.close();



    // Assert

    EXPECT_EQ(oss.str(), "\n");

}



TEST_F(TablePrinterTest_757, CloseMultipleTimes_757) {

    // Arrange

    tablePrinter.open();

    tablePrinter.close();



    // Act

    tablePrinter.close();  // Subsequent close calls



    // Assert

    EXPECT_EQ(oss.str(), "\n");  // Only one newline should be produced

}



TEST_F(TablePrinterTest_757, OpenCloseSequence_757) {

    // Arrange

    InSequence s;



    // Act & Assert

    tablePrinter.open();  // First open call

    EXPECT_EQ(oss.str(), "");



    tablePrinter.close();  // First close call

    EXPECT_EQ(oss.str(), "\n");



    tablePrinter.open();  // Second open call

    EXPECT_EQ(oss.str(), "\n");



    tablePrinter.close();  // Second close call

    EXPECT_EQ(oss.str(), "\n\n");

}
