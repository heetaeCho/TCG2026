#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/qt5/src/poppler-annotation.cc"

#include "./TestProjects/poppler/poppler/GfxState.h"

#include "./TestProjects/poppler/poppler/Page.h"



using namespace Poppler;

using ::testing::NiceMock;



class MockPage : public Page {

public:

    MockPage(PDFDoc* docA, int numA, Object&& pageDict, Ref pageRefA, std::unique_ptr<PageAttrs> attrsA)

        : Page(docA, numA, std::move(pageDict), pageRefA, std::move(attrsA)) {}



    MOCK_METHOD(const PDFRectangle*, getCropBox, (), (const, override));

    MOCK_METHOD(double, getCropWidth, (), (const, override));

    MOCK_METHOD(double, getCropHeight, (), (const, override));

};



class MockGfxState : public GfxState {

public:

    MockGfxState(double hDPIA, double vDPIA, const PDFRectangle* pageBox, int rotateA, bool upsideDown)

        : GfxState(hDPIA, vDPIA, pageBox, rotateA, upsideDown) {}



    MOCK_METHOD(const std::array<double, 6>&, getCTM, (), (const, override));

};



class FillNormalizationMTXTest_1384 : public ::testing::Test {

protected:

    NiceMock<MockPage> mockPage;

    MockGfxState* mockGfxState = nullptr;



    FillNormalizationMTXTest_1384()

        : mockPage(nullptr, 0, Object(), Ref(), std::make_unique<PageAttrs>()) {}



    void SetUp() override {

        mockGfxState = new NiceMock<MockGfxState>(72.0, 72.0, nullptr, 0, true);

    }



    void TearDown() override {

        delete mockGfxState;

    }

};



TEST_F(FillNormalizationMTXTest_1384, NormalOperation_0_Degrees_1384) {

    const std::array<double, 6> expectedCTM = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    double MTX[6] = {0};



    EXPECT_CALL(mockGfxState, getCTM()).WillOnce(::testing::Return(expectedCTM));

    ON_CALL(mockPage, getCropBox()).WillByDefault([]() {

        static const PDFRectangle cropBox(0, 0, 100, 200);

        return &cropBox;

    });

    ON_CALL(mockPage, getCropWidth()).WillByDefault(::testing::Return(100.0));

    ON_CALL(mockPage, getCropHeight()).WillByDefault(::testing::Return(200.0));



    fillNormalizationMTX(&mockPage, MTX, 0);



    EXPECT_DOUBLE_EQ(MTX[0], expectedCTM[0] / 100);

    EXPECT_DOUBLE_EQ(MTX[1], expectedCTM[1] / 200);

    EXPECT_DOUBLE_EQ(MTX[2], expectedCTM[2] / 100);

    EXPECT_DOUBLE_EQ(MTX[3], expectedCTM[3] / 200);

    EXPECT_DOUBLE_EQ(MTX[4], expectedCTM[4] / 100);

    EXPECT_DOUBLE_EQ(MTX[5], expectedCTM[5] / 200);

}



TEST_F(FillNormalizationMTXTest_1384, NormalOperation_90_Degrees_1384) {

    const std::array<double, 6> expectedCTM = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    double MTX[6] = {0};



    EXPECT_CALL(mockGfxState, getCTM()).WillOnce(::testing::Return(expectedCTM));

    ON_CALL(mockPage, getCropBox()).WillByDefault([]() {

        static const PDFRectangle cropBox(0, 0, 100, 200);

        return &cropBox;

    });

    ON_CALL(mockPage, getCropWidth()).WillByDefault(::testing::Return(100.0));

    ON_CALL(mockPage, getCropHeight()).WillByDefault(::testing::Return(200.0));



    fillNormalizationMTX(&mockPage, MTX, 90);



    EXPECT_DOUBLE_EQ(MTX[0], expectedCTM[0] / 200);

    EXPECT_DOUBLE_EQ(MTX[1], expectedCTM[1] / 200);

    EXPECT_DOUBLE_EQ(MTX[2], expectedCTM[2] / 100);

    EXPECT_DOUBLE_EQ(MTX[3], expectedCTM[3] / 100);

    EXPECT_DOUBLE_EQ(MTX[4], expectedCTM[4] / 200);

    EXPECT_DOUBLE_EQ(MTX[5], expectedCTM[5] / 100);

}



TEST_F(FillNormalizationMTXTest_1384, BoundaryCondition_ZeroWidthHeight_1384) {

    const std::array<double, 6> expectedCTM = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    double MTX[6] = {0};



    EXPECT_CALL(mockGfxState, getCTM()).WillOnce(::testing::Return(expectedCTM));

    ON_CALL(mockPage, getCropBox()).WillByDefault([]() {

        static const PDFRectangle cropBox(0, 0, 0, 0);

        return &cropBox;

    });

    ON_CALL(mockPage, getCropWidth()).WillByDefault(::testing::Return(0.0));

    ON_CALL(mockPage, getCropHeight()).WillByDefault(::testing::Return(0.0));



    fillNormalizationMTX(&mockPage, MTX, 0);



    // Assuming division by zero results in undefined behavior or zeros

    EXPECT_DOUBLE_EQ(MTX[0], 0);

    EXPECT_DOUBLE_EQ(MTX[1], 0);

    EXPECT_DOUBLE_EQ(MTX[2], 0);

    EXPECT_DOUBLE_EQ(MTX[3], 0);

    EXPECT_DOUBLE_EQ(MTX[4], 0);

    EXPECT_DOUBLE_EQ(MTX[5], 0);

}



TEST_F(FillNormalizationMTXTest_1384, BoundaryCondition_NegativeRotation_1384) {

    const std::array<double, 6> expectedCTM = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    double MTX[6] = {0};



    EXPECT_CALL(mockGfxState, getCTM()).WillOnce(::testing::Return(expectedCTM));

    ON_CALL(mockPage, getCropBox()).WillByDefault([]() {

        static const PDFRectangle cropBox(0, 0, 100, 200);

        return &cropBox;

    });

    ON_CALL(mockPage, getCropWidth()).WillByDefault(::testing::Return(100.0));

    ON_CALL(mockPage, getCropHeight()).WillByDefault(::testing::Return(200.0));



    fillNormalizationMTX(&mockPage, MTX, -90);



    // Assuming negative rotation is handled as non-90 or 270 degrees

    EXPECT_DOUBLE_EQ(MTX[0], expectedCTM[0] / 100);

    EXPECT_DOUBLE_EQ(MTX[1], expectedCTM[1] / 200);

    EXPECT_DOUBLE_EQ(MTX[2], expectedCTM[2] / 100);

    EXPECT_DOUBLE_EQ(MTX[3], expectedCTM[3] / 200);

    EXPECT_DOUBLE_EQ(MTX[4], expectedCTM[4] / 100);

    EXPECT_DOUBLE_EQ(MTX[5], expectedCTM[5] / 200);

}
