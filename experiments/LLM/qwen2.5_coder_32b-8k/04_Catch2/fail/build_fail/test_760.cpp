#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_console.hpp"



using namespace Catch;



// Mocking TablePrinter for testing purposes

class MockTablePrinter : public TablePrinter {

public:

    MOCK_METHOD(std::ostream&, getStream, (), (override));

    MOCK_METHOD(int, getCurrentColumn, (), (const, override));



    MockTablePrinter(std::ostream& os) : TablePrinter(os) {}

};



TEST_F(MockTablePrinterTest_760, RowBreakWithCurrentColumnPositive_760) {

    std::ostringstream oss;

    MockTablePrinter mockTp(oss);



    EXPECT_CALL(mockTp, getCurrentColumn()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockTp, getStream()).Times(1);



    TablePrinter& result = operator<<(mockTp, RowBreak());

    EXPECT_EQ(result.getCurrentColumn(), -1);

}



TEST_F(MockTablePrinterTest_760, RowBreakWithCurrentColumnZero_760) {

    std::ostringstream oss;

    MockTablePrinter mockTp(oss);



    EXPECT_CALL(mockTp, getCurrentColumn()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockTp, getStream()).Times(1);



    TablePrinter& result = operator<<(mockTp, RowBreak());

    EXPECT_EQ(result.getCurrentColumn(), -1);

}



TEST_F(MockTablePrinterTest_760, RowBreakWithCurrentColumnNegative_760) {

    std::ostringstream oss;

    MockTablePrinter mockTp(oss);



    EXPECT_CALL(mockTp, getCurrentColumn()).WillOnce(::testing::Return(-1));

    EXPECT_CALL(mockTp, getStream()).Times(0);



    TablePrinter& result = operator<<(mockTp, RowBreak());

    EXPECT_EQ(result.getCurrentColumn(), -1);

}

```


