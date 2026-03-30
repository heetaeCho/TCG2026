#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/qt5/src/poppler-link.cc"  // Include the file with the function to be tested
#include "poppler/poppler/Page.h" // Include the header for the Page class

class MockPage : public Poppler::Page {
public:
    MockPage(PDFDoc *doc, int num, Object &&pageDict, Ref pageRefA)
        : Poppler::Page(doc, num, std::move(pageDict), pageRefA) {}

    MOCK_METHOD(void, getDefaultCTM, (double* ctm, double hDPI, double vDPI, int rotate, bool useMediaBox, bool upsideDown), (override));
};

// Test Normal Operation
TEST_F(MockPageTest_1251, CvtUserToDev_NormalOperation_1251) {
    MockPage mockPage(nullptr, 0, Object(), Ref());
    double xu = 100.0;
    double yu = 200.0;
    int xd = 0, yd = 0;
    
    // Mock the behavior of getDefaultCTM
    double mockCTM[6] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};  // Identity matrix
    EXPECT_CALL(mockPage, getDefaultCTM(testing::_ , testing::_ , testing::_ , testing::_ , testing::_ , testing::_))
        .WillOnce(testing::DoAll(testing::SetArrayArgument<0>(mockCTM, mockCTM + 6), testing::Return()));

    Poppler::cvtUserToDev(&mockPage, xu, yu, &xd, &yd);

    // Verifying that the conversion happens correctly based on the identity matrix.
    EXPECT_EQ(xd, 100);  // Expected result based on identity transformation
    EXPECT_EQ(yd, 200);
}

// Test Boundary Conditions
TEST_F(MockPageTest_1252, CvtUserToDev_BoundaryConditions_1252) {
    MockPage mockPage(nullptr, 0, Object(), Ref());
    double xu = 0.0;
    double yu = 0.0;
    int xd = 0, yd = 0;
    
    // Mock the behavior of getDefaultCTM
    double mockCTM[6] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};  // Identity matrix
    EXPECT_CALL(mockPage, getDefaultCTM(testing::_ , testing::_ , testing::_ , testing::_ , testing::_ , testing::_))
        .WillOnce(testing::DoAll(testing::SetArrayArgument<0>(mockCTM, mockCTM + 6), testing::Return()));

    Poppler::cvtUserToDev(&mockPage, xu, yu, &xd, &yd);

    // Verifying that the conversion happens correctly
    EXPECT_EQ(xd, 0);  // Result based on identity transformation
    EXPECT_EQ(yd, 0);
}

// Test Large Values for xu and yu
TEST_F(MockPageTest_1253, CvtUserToDev_LargeValues_1253) {
    MockPage mockPage(nullptr, 0, Object(), Ref());
    double xu = 1e6;
    double yu = 1e6;
    int xd = 0, yd = 0;

    // Mock the behavior of getDefaultCTM
    double mockCTM[6] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};  // Identity matrix
    EXPECT_CALL(mockPage, getDefaultCTM(testing::_ , testing::_ , testing::_ , testing::_ , testing::_ , testing::_))
        .WillOnce(testing::DoAll(testing::SetArrayArgument<0>(mockCTM, mockCTM + 6), testing::Return()));

    Poppler::cvtUserToDev(&mockPage, xu, yu, &xd, &yd);

    // Verifying that the conversion happens correctly
    EXPECT_EQ(xd, 1000000);  // Result based on identity transformation
    EXPECT_EQ(yd, 1000000);
}

// Test External Interaction (Verification of `getDefaultCTM` call)
TEST_F(MockPageTest_1254, CvtUserToDev_ExternalInteraction_1254) {
    MockPage mockPage(nullptr, 0, Object(), Ref());
    double xu = 50.0;
    double yu = 75.0;
    int xd = 0, yd = 0;
    
    // Mock the behavior of getDefaultCTM
    double mockCTM[6] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};  // Identity matrix
    EXPECT_CALL(mockPage, getDefaultCTM(testing::_ , testing::_ , testing::_ , testing::_ , testing::_ , testing::_))
        .WillOnce(testing::DoAll(testing::SetArrayArgument<0>(mockCTM, mockCTM + 6), testing::Return()));

    Poppler::cvtUserToDev(&mockPage, xu, yu, &xd, &yd);

    // Verifying that the getDefaultCTM method was called correctly
    EXPECT_EQ(xd, 50);  // Identity transformation
    EXPECT_EQ(yd, 75);
}