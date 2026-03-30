#include <gtest/gtest.h>

#include <QString>



namespace Poppler {

    enum CaretSymbol { None, P };

    static CaretSymbol caretSymbolFromString(const QString &symbol);

}



class CaretAnnotationTest_1411 : public ::testing::Test {};



TEST_F(CaretAnnotationTest_1411, NormalOperation_None_1411) {

    EXPECT_EQ(Poppler::caretSymbolFromString(QLatin1String("None")), Poppler::None);

}



TEST_F(CaretAnnotationTest_1411, NormalOperation_P_1411) {

    EXPECT_EQ(Poppler::caretSymbolFromString(QLatin1String("P")), Poppler::P);

}



TEST_F(CaretAnnotationTest_1411, BoundaryCondition_EmptyString_1411) {

    EXPECT_EQ(Poppler::caretSymbolFromString(QLatin1String("")), Poppler::None);

}



TEST_F(CaretAnnotationTest_1411, ExceptionalCase_UppercaseP_1411) {

    EXPECT_EQ(Poppler::caretSymbolFromString(QLatin1String("p")), Poppler::None);

}



TEST_F(CaretAnnotationTest_1411, ExceptionalCase_DifferentString_1411) {

    EXPECT_EQ(Poppler::caretSymbolFromString(QLatin1String("Other")), Poppler::None);

}
