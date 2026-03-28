#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_console.hpp"



using namespace Catch;



class TablePrinterMock : public TablePrinter {

public:

    MOCK_METHOD(std::ostream&, os, (), (override));

    MOCK_METHOD(std::ostringstream&, m_oss, (), (override));

    MOCK_METHOD(int, m_currentColumn, (), (const, override));

    MOCK_METHOD(void, set_m_currentColumn, (int), (override));

    MOCK_METHOD(std::vector<ColumnInfo>, m_columnInfos, (), (const, override));

};



TEST_F(TablePrinterMockTest_759, ColumnBreakOperator_NormalOperation_759) {

    TablePrinterMock mockTablePrinter;

    std::ostringstream oss;

    std::string expectedOutput = "TestString     ";

    

    // Setup mocks

    EXPECT_CALL(mockTablePrinter, m_oss()).WillOnce(testing::ReturnRef(oss));

    EXPECT_CALL(mockTablePrinter, m_currentColumn())

        .WillOnce(testing::Return(0))

        .WillOnce(testing::Return(-1));

    EXPECT_CALL(mockTablePrinter, set_m_currentColumn(testing::_)).Times(2);

    EXPECT_CALL(mockTablePrinter, m_columnInfos()).WillOnce(testing::Return(std::vector<ColumnInfo>{{.width = 14, .justification = Justification::Left}}));



    // Set initial state

    oss << "TestString";



    // Exercise the operator<<

    mockTablePrinter << ColumnBreak{};



    // Verify output

    EXPECT_EQ(oss.str(), expectedOutput);

}



TEST_F(TablePrinterMockTest_759, ColumnBreakOperator_BoundaryCondition_LastColumn_759) {

    TablePrinterMock mockTablePrinter;

    std::ostringstream oss;

    std::string expectedOutput = "TestString\n     ";

    

    // Setup mocks

    EXPECT_CALL(mockTablePrinter, m_oss()).WillOnce(testing::ReturnRef(oss));

    EXPECT_CALL(mockTablePrinter, m_currentColumn())

        .WillOnce(testing::Return(static_cast<int>(mockTablePrinter.m_columnInfos().size() - 1)))

        .WillOnce(testing::Return(-1));

    EXPECT_CALL(mockTablePrinter, set_m_currentColumn(testing::_)).Times(2);

    EXPECT_CALL(mockTablePrinter, m_columnInfos()).WillOnce(testing::Return(std::vector<ColumnInfo>{{.width = 14, .justification = Justification::Left}}));



    // Set initial state

    oss << "TestString";



    // Exercise the operator<<

    mockTablePrinter << ColumnBreak{};



    // Verify output

    EXPECT_EQ(oss.str(), expectedOutput);

}



TEST_F(TablePrinterMockTest_759, ColumnBreakOperator_BoundaryCondition_EmptyString_759) {

    TablePrinterMock mockTablePrinter;

    std::ostringstream oss;

    std::string expectedOutput = "             ";

    

    // Setup mocks

    EXPECT_CALL(mockTablePrinter, m_oss()).WillOnce(testing::ReturnRef(oss));

    EXPECT_CALL(mockTablePrinter, m_currentColumn())

        .WillOnce(testing::Return(0))

        .WillOnce(testing::Return(-1));

    EXPECT_CALL(mockTablePrinter, set_m_currentColumn(testing::_)).Times(2);

    EXPECT_CALL(mockTablePrinter, m_columnInfos()).WillOnce(testing::Return(std::vector<ColumnInfo>{{.width = 14, .justification = Justification::Left}}));



    // Exercise the operator<<

    mockTablePrinter << ColumnBreak{};



    // Verify output

    EXPECT_EQ(oss.str(), expectedOutput);

}



TEST_F(TablePrinterMockTest_759, ColumnBreakOperator_ExceptionalCase_WidthLessThanColumnStringSize_759) {

    TablePrinterMock mockTablePrinter;

    std::ostringstream oss;

    std::string expectedOutput = "TestString    ";

    

    // Setup mocks

    EXPECT_CALL(mockTablePrinter, m_oss()).WillOnce(testing::ReturnRef(oss));

    EXPECT_CALL(mockTablePrinter, m_currentColumn())

        .WillOnce(testing::Return(0))

        .WillOnce(testing::Return(-1));

    EXPECT_CALL(mockTablePrinter, set_m_currentColumn(testing::_)).Times(2);

    EXPECT_CALL(mockTablePrinter, m_columnInfos()).WillOnce(testing::Return(std::vector<ColumnInfo>{{.width = 5, .justification = Justification::Left}}));



    // Set initial state

    oss << "TestString";



    // Exercise the operator<<

    mockTablePrinter << ColumnBreak{};



    // Verify output

    EXPECT_EQ(oss.str(), expectedOutput);

}



TEST_F(TablePrinterMockTest_759, ColumnBreakOperator_VerifyExternalInteractions_759) {

    TablePrinterMock mockTablePrinter;

    std::ostringstream oss;

    std::string expectedOutput = "TestString     ";

    

    // Setup mocks

    EXPECT_CALL(mockTablePrinter, m_oss()).WillOnce(testing::ReturnRef(oss));

    EXPECT_CALL(mockTablePrinter, m_currentColumn())

        .WillOnce(testing::Return(0))

        .WillOnce(testing::Return(-1));

    EXPECT_CALL(mockTablePrinter, set_m_currentColumn(1)).Times(1);

    EXPECT_CALL(mockTablePrinter, set_m_currentColumn(-1)).Times(1);

    EXPECT_CALL(mockTablePrinter, m_columnInfos()).WillOnce(testing::Return(std::vector<ColumnInfo>{{.width = 14, .justification = Justification::Left}}));



    // Set initial state

    oss << "TestString";



    // Exercise the operator<<

    mockTablePrinter << ColumnBreak{};



    // Verify output

    EXPECT_EQ(oss.str(), expectedOutput);

}
