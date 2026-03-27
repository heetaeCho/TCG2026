#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/poppler/Function.h"



using ::testing::Return;



class MockFunction : public Function {

public:

    MOCK_CONST_METHOD1(getRangeMin, double(int));

    MOCK_CONST_METHOD1(getDomainMin, double(int));

    MOCK_CONST_METHOD1(getDomainMax, double(int));

    MOCK_CONST_METHOD1(getRangeMax, double(int));

    MOCK_CONST_METHOD0(getInputSize, int());

    MOCK_CONST_METHOD0(getOutputSize, int());

    MOCK_CONST_METHOD0(getHasRange, bool());

};



class FunctionTest_351 : public ::testing::Test {

protected:

    std::unique_ptr<MockFunction> function;



    void SetUp() override {

        function = std::make_unique<MockFunction>();

    }

};



TEST_F(FunctionTest_351, GetRangeMin_NormalOperation_351) {

    EXPECT_CALL(*function, getRangeMin(0)).WillOnce(Return(1.0));

    EXPECT_EQ(function->getRangeMin(0), 1.0);

}



TEST_F(FunctionTest_351, GetDomainMin_NormalOperation_351) {

    EXPECT_CALL(*function, getDomainMin(0)).WillOnce(Return(2.0));

    EXPECT_EQ(function->getDomainMin(0), 2.0);

}



TEST_F(FunctionTest_351, GetDomainMax_NormalOperation_351) {

    EXPECT_CALL(*function, getDomainMax(0)).WillOnce(Return(4.0));

    EXPECT_EQ(function->getDomainMax(0), 4.0);

}



TEST_F(FunctionTest_351, GetRangeMax_NormalOperation_351) {

    EXPECT_CALL(*function, getRangeMax(0)).WillOnce(Return(5.0));

    EXPECT_EQ(function->getRangeMax(0), 5.0);

}



TEST_F(FunctionTest_351, GetInputSize_NormalOperation_351) {

    EXPECT_CALL(*function, getInputSize()).WillOnce(Return(1));

    EXPECT_EQ(function->getInputSize(), 1);

}



TEST_F(FunctionTest_351, GetOutputSize_NormalOperation_351) {

    EXPECT_CALL(*function, getOutputSize()).WillOnce(Return(2));

    EXPECT_EQ(function->getOutputSize(), 2);

}



TEST_F(FunctionTest_351, GetHasRange_NormalOperation_351) {

    EXPECT_CALL(*function, getHasRange()).WillOnce(Return(true));

    EXPECT_TRUE(function->getHasRange());

}



TEST_F(FunctionTest_351, GetRangeMin_BoundaryCondition_351) {

    EXPECT_CALL(*function, getRangeMin(0)).WillOnce(Return(-1.0));

    EXPECT_EQ(function->getRangeMin(0), -1.0);

}



TEST_F(FunctionTest_351, GetDomainMin_BoundaryCondition_351) {

    EXPECT_CALL(*function, getDomainMin(0)).WillOnce(Return(0.0));

    EXPECT_EQ(function->getDomainMin(0), 0.0);

}



TEST_F(FunctionTest_351, GetDomainMax_BoundaryCondition_351) {

    EXPECT_CALL(*function, getDomainMax(0)).WillOnce(Return(0.0));

    EXPECT_EQ(function->getDomainMax(0), 0.0);

}



TEST_F(FunctionTest_351, GetRangeMax_BoundaryCondition_351) {

    EXPECT_CALL(*function, getRangeMax(0)).WillOnce(Return(-2.0));

    EXPECT_EQ(function->getRangeMax(0), -2.0);

}



TEST_F(FunctionTest_351, GetInputSize_BoundaryCondition_351) {

    EXPECT_CALL(*function, getInputSize()).WillOnce(Return(0));

    EXPECT_EQ(function->getInputSize(), 0);

}



TEST_F(FunctionTest_351, GetOutputSize_BoundaryCondition_351) {

    EXPECT_CALL(*function, getOutputSize()).WillOnce(Return(0));

    EXPECT_EQ(function->getOutputSize(), 0);

}
