#include <gtest/gtest.h>

#include <QString>



namespace Poppler {

    enum class CaretSymbol { None, P };

    static QString caretSymbolToString(CaretSymbol symbol);

}



class CaretAnnotationTest_1410 : public ::testing::Test {};



TEST_F(CaretAnnotationTest_1410, ConvertNoneSymbolToQString_1410) {

    EXPECT_EQ(Poppler::caretSymbolToString(Poppler::CaretSymbol::None), QStringLiteral("None"));

}



TEST_F(CaretAnnotationTest_1410, ConvertPSymbolToQString_1410) {

    EXPECT_EQ(Poppler::caretSymbolToString(Poppler::CaretSymbol::P), QStringLiteral("P"));

}



TEST_F(CaretAnnotationTest_1410, ConvertUnknownSymbolToEmptyQString_1410) {

    EXPECT_EQ(Poppler::caretSymbolToString(static_cast<Poppler::CaretSymbol>(99)), QString());

}
