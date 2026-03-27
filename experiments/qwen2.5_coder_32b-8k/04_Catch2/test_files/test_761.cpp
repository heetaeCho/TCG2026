#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_console.cpp"



using namespace Catch;



class TablePrinterMock : public TablePrinter {

public:

    MOCK_METHOD(std::ostream&, m_os, (), (override));

};



TEST(TablePrinterOperator_761, FlushOutput_761) {

    TablePrinterMock tablePrinterMock;

    OutputFlush flush;

    

    std::ostringstream oss;

    EXPECT_CALL(tablePrinterMock, m_os()).WillOnce(testing::ReturnRef(oss));



    tablePrinterMock << flush;



    EXPECT_EQ(oss.str(), "");

}



TEST(TablePrinterOperator_761, FlushOutputTwice_761) {

    TablePrinterMock tablePrinterMock;

    OutputFlush flush;

    

    std::ostringstream oss;

    EXPECT_CALL(tablePrinterMock, m_os())

        .WillOnce(testing::ReturnRef(oss))

        .WillRepeatedly(testing::ReturnRef(oss));



    tablePrinterMock << flush;

    tablePrinterMock << flush;



    EXPECT_EQ(oss.str(), "");

}
