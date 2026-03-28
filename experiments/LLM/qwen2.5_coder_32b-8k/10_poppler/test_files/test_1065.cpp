#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock classes and dependencies if needed



class MockPage : public Page {

    // If necessary, mock any required methods of Page class

};



class MockAnnot : public Annot {

    // If necessary, mock any required methods of Annot class

};



using ::testing::Return;

using ::testing::MockFunction;



// Test fixture for OutputDev

class OutputDevTest_1065 : public ::testing::Test {

protected:

    OutputDev outputDev;

    MockPage mockPage;

    MockAnnot mockAnnot;



    // Define any necessary mock functions or setup here

};



TEST_F(OutputDevTest_1065, CheckPageSlice_NormalOperation_1065) {

    bool result = outputDev.checkPageSlice(&mockPage, 300.0, 300.0, 0, true, false, 0, 0, 100, 100, false);

    EXPECT_TRUE(result);

}



TEST_F(OutputDevTest_1065, CheckPageSlice_BoundaryConditions_1065) {

    bool result = outputDev.checkPageSlice(&mockPage, 0.0, 0.0, 0, true, false, 0, 0, 0, 0, false);

    EXPECT_TRUE(result);



    result = outputDev.checkPageSlice(&mockPage, std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), 360, false, true, -1, -1, std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), true);

    EXPECT_TRUE(result);

}



TEST_F(OutputDevTest_1065, CheckPageSlice_AbortCheckCallback_ReturnsTrue_1065) {

    MockFunction<bool(void*)> mockAbortCheckCbk;

    EXPECT_CALL(mockAbortCheckCbk, Call(::testing::_)).WillOnce(Return(true));



    bool result = outputDev.checkPageSlice(&mockPage, 300.0, 300.0, 0, true, false, 0, 0, 100, 100, false, mockAbortCheckCbk.AsStdFunction(), nullptr);

    EXPECT_FALSE(result);

}



TEST_F(OutputDevTest_1065, CheckPageSlice_AbortCheckCallback_ReturnsFalse_1065) {

    MockFunction<bool(void*)> mockAbortCheckCbk;

    EXPECT_CALL(mockAbortCheckCbk, Call(::testing::_)).WillOnce(Return(false));



    bool result = outputDev.checkPageSlice(&mockPage, 300.0, 300.0, 0, true, false, 0, 0, 100, 100, false, mockAbortCheckCbk.AsStdFunction(), nullptr);

    EXPECT_TRUE(result);

}



TEST_F(OutputDevTest_1065, CheckPageSlice_AnnotDisplayDecideCallback_ReturnsTrue_1065) {

    MockFunction<bool(Annot*, void*)> mockAnnotDisplayDecideCbk;

    EXPECT_CALL(mockAnnotDisplayDecideCbk, Call(&mockAnnot, ::testing::_)).WillOnce(Return(true));



    bool result = outputDev.checkPageSlice(&mockPage, 300.0, 300.0, 0, true, false, 0, 0, 100, 100, false, nullptr, nullptr, mockAnnotDisplayDecideCbk.AsStdFunction(), nullptr);

    EXPECT_TRUE(result);

}



TEST_F(OutputDevTest_1065, CheckPageSlice_AnnotDisplayDecideCallback_ReturnsFalse_1065) {

    MockFunction<bool(Annot*, void*)> mockAnnotDisplayDecideCbk;

    EXPECT_CALL(mockAnnotDisplayDecideCbk, Call(&mockAnnot, ::testing::_)).WillOnce(Return(false));



    bool result = outputDev.checkPageSlice(&mockPage, 300.0, 300.0, 0, true, false, 0, 0, 100, 100, false, nullptr, nullptr, mockAnnotDisplayDecideCbk.AsStdFunction(), nullptr);

    EXPECT_TRUE(result); // Assuming the return value is not affected by annotDisplayDecideCbk

}
