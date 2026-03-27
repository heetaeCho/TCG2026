#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Function.h"



class MockFunction : public Function {

public:

    MOCK_CONST_METHOD0(getType, Type());

    MOCK_CONST_METHOD0(isOk, bool());

};



using namespace testing;



class StitchingFunctionTest_377 : public Test {

protected:

    std::vector<std::unique_ptr<Function>> mockFuncs;

    double bounds[2] = {0.0, 1.0};

    double encode[2] = {0.0, 1.0};

    double scale[2] = {1.0, 1.0};



    void SetUp() override {

        for (int i = 0; i < 3; ++i) {

            mockFuncs.emplace_back(std::make_unique<MockFunction>());

        }

    }



    std::unique_ptr<StitchingFunction> createStitchingFunction() {

        return std::make_unique<StitchingFunction>(mockFuncs, bounds, encode, scale);

    }

};



TEST_F(StitchingFunctionTest_377, GetNumFuncs_ReturnsCorrectCount_377) {

    auto stitchingFunction = createStitchingFunction();

    EXPECT_EQ(stitchingFunction->getNumFuncs(), 3);

}



TEST_F(StitchingFunctionTest_377, GetFunc_ReturnsValidPointerForExistingIndex_377) {

    auto stitchingFunction = createStitchingFunction();

    EXPECT_NE(stitchingFunction->getFunc(0), nullptr);

    EXPECT_NE(stitchingFunction->getFunc(1), nullptr);

    EXPECT_NE(stitchingFunction->getFunc(2), nullptr);

}



TEST_F(StitchingFunctionTest_377, GetFunc_ReturnsNullForNonExistentIndex_377) {

    auto stitchingFunction = createStitchingFunction();

    EXPECT_EQ(stitchingFunction->getFunc(-1), nullptr);

    EXPECT_EQ(stitchingFunction->getFunc(3), nullptr);

}



TEST_F(StitchingFunctionTest_377, GetBounds_ReturnsValidPointer_377) {

    auto stitchingFunction = createStitchingFunction();

    EXPECT_NE(stitchingFunction->getBounds(), nullptr);

}



TEST_F(StitchingFunctionTest_377, GetEncode_ReturnsValidPointer_377) {

    auto stitchingFunction = createStitchingFunction();

    EXPECT_NE(stitchingFunction->getEncode(), nullptr);

}



TEST_F(StitchingFunctionTest_377, GetScale_ReturnsValidPointer_377) {

    auto stitchingFunction = createStitchingFunction();

    EXPECT_NE(stitchingFunction->getScale(), nullptr);

}
