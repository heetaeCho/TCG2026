#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Assuming necessary includes for the Poppler class and associated dependencies

// Mock class to simulate the AnnotMarkup behavior
class MockAnnotMarkup : public AnnotMarkup {
public:
    MOCK_METHOD(AnnotExternalDataType, getExData, (), (const, override));
};

// Test case for the poppler_annot_markup_get_external_data function
TEST_F(PopplerAnnotTest_2088, GetExternalDataMarkup3D_2088) {
    // Arrange
    MockAnnotMarkup mockAnnot;
    EXPECT_CALL(mockAnnot, getExData())
        .WillOnce(testing::Return(annotExternalDataMarkup3D));

    PopplerAnnotMarkup popplerAnnot;
    popplerAnnot.annot = std::make_shared<MockAnnotMarkup>(mockAnnot);

    // Act
    PopplerAnnotExternalDataType result = poppler_annot_markup_get_external_data(&popplerAnnot);

    // Assert
    EXPECT_EQ(result, POPPLER_ANNOT_EXTERNAL_DATA_MARKUP_3D);
}

TEST_F(PopplerAnnotTest_2088, GetExternalDataMarkupUnknown_2088) {
    // Arrange
    MockAnnotMarkup mockAnnot;
    EXPECT_CALL(mockAnnot, getExData())
        .WillOnce(testing::Return(annotExternalDataMarkupUnknown));

    PopplerAnnotMarkup popplerAnnot;
    popplerAnnot.annot = std::make_shared<MockAnnotMarkup>(mockAnnot);

    // Act
    PopplerAnnotExternalDataType result = poppler_annot_markup_get_external_data(&popplerAnnot);

    // Assert
    EXPECT_EQ(result, POPPLER_ANNOT_EXTERNAL_DATA_MARKUP_UNKNOWN);
}

TEST_F(PopplerAnnotTest_2088, GetExternalDataUnsupported_2088) {
    // Arrange
    MockAnnotMarkup mockAnnot;
    EXPECT_CALL(mockAnnot, getExData())
        .WillOnce(testing::Return(static_cast<AnnotExternalDataType>(99))); // Unsupported type

    PopplerAnnotMarkup popplerAnnot;
    popplerAnnot.annot = std::make_shared<MockAnnotMarkup>(mockAnnot);

    // Act
    PopplerAnnotExternalDataType result = poppler_annot_markup_get_external_data(&popplerAnnot);

    // Assert
    EXPECT_EQ(result, POPPLER_ANNOT_EXTERNAL_DATA_MARKUP_UNKNOWN);
}

TEST_F(PopplerAnnotTest_2088, InvalidPopplerAnnot_2088) {
    // Arrange
    PopplerAnnotMarkup popplerAnnot;

    // Act
    PopplerAnnotExternalDataType result = poppler_annot_markup_get_external_data(&popplerAnnot);

    // Assert
    EXPECT_EQ(result, POPPLER_ANNOT_EXTERNAL_DATA_MARKUP_UNKNOWN);
}