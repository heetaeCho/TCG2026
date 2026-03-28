#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <clocale>

#include <cmath>

#include "gstrtod.cc"



using namespace testing;



TEST(gstrtodTest_31, NormalOperationWithInteger_31) {

    const char *nptr = "123";

    char *endptr;

    double result = gstrtod(nptr, &endptr);

    EXPECT_DOUBLE_EQ(result, 123.0);

    EXPECT_STREQ(endptr, nptr + strlen(nptr));

}



TEST(gstrtodTest_31, NormalOperationWithDecimal_31) {

    const char *nptr = "123.456";

    char *endptr;

    double result = gstrtod(nptr, &endptr);

    EXPECT_DOUBLE_EQ(result, 123.456);

    EXPECT_STREQ(endptr, nptr + strlen(nptr));

}



TEST(gstrtodTest_31, NormalOperationWithScientificNotation_31) {

    const char *nptr = "1.23e2";

    char *endptr;

    double result = gstrtod(nptr, &endptr);

    EXPECT_DOUBLE_EQ(result, 123.0);

    EXPECT_STREQ(endptr, nptr + strlen(nptr));

}



TEST(gstrtodTest_31, NormalOperationWithNegativeNumber_31) {

    const char *nptr = "-456";

    char *endptr;

    double result = gstrtod(nptr, &endptr);

    EXPECT_DOUBLE_EQ(result, -456.0);

    EXPECT_STREQ(endptr, nptr + strlen(nptr));

}



TEST(gstrtodTest_31, BoundaryConditionWithEmptyString_31) {

    const char *nptr = "";

    char *endptr;

    double result = gstrtod(nptr, &endptr);

    EXPECT_DOUBLE_EQ(result, 0.0);

    EXPECT_STREQ(endptr, nptr);

}



TEST(gstrtodTest_31, BoundaryConditionWithSpacesOnly_31) {

    const char *nptr = "   ";

    char *endptr;

    double result = gstrtod(nptr, &endptr);

    EXPECT_DOUBLE_EQ(result, 0.0);

    EXPECT_STREQ(endptr, nptr + strlen(nptr));

}



TEST(gstrtodTest_31, BoundaryConditionWithLeadingSpaces_31) {

    const char *nptr = "   789";

    char *endptr;

    double result = gstrtod(nptr, &endptr);

    EXPECT_DOUBLE_EQ(result, 789.0);

    EXPECT_STREQ(endptr, nptr + strlen(nptr));

}



TEST(gstrtodTest_31, BoundaryConditionWithTrailingCharacters_31) {

    const char *nptr = "42abc";

    char *endptr;

    double result = gstrtod(nptr, &endptr);

    EXPECT_DOUBLE_EQ(result, 42.0);

    EXPECT_STREQ(endptr, nptr + 2);

}



TEST(gstrtodTest_31, ExceptionalCaseWithInvalidInput_31) {

    const char *nptr = "abc";

    char *endptr;

    double result = gstrtod(nptr, &endptr);

    EXPECT_DOUBLE_EQ(result, 0.0);

    EXPECT_STREQ(endptr, nptr);

}



TEST(gstrtodTest_31, ExceptionalCaseWithNegativeDecimalPoint_31) {

    const char *nptr = "12-.34";

    char *endptr;

    double result = gstrtod(nptr, &endptr);

    EXPECT_DOUBLE_EQ(result, 12.0);

    EXPECT_STREQ(endptr, nptr + 2);

}



TEST(gstrtodTest_31, ExceptionalCaseWithDoubleDecimalPoint_31) {

    const char *nptr = "12.34.56";

    char *endptr;

    double result = gstrtod(nptr, &endptr);

    EXPECT_DOUBLE_EQ(result, 12.34);

    EXPECT_STREQ(endptr, nptr + 5);

}



TEST(gstrtodTest_31, LocaleSpecificDecimalPoint_31) {

    struct lconv *locale_data = localeconv();

    const char *original_decimal_point = locale_data->decimal_point;

    std::string custom_decimal_point = ",";

    setlocale(LC_ALL, "de_DE.UTF-8");

    locale_data = localeconv();

    EXPECT_STREQ(locale_data->decimal_point, custom_decimal_point.c_str());



    const char *nptr = "123,456";

    char *endptr;

    double result = gstrtod(nptr, &endptr);

    EXPECT_DOUBLE_EQ(result, 123.456);

    EXPECT_STREQ(endptr, nptr + strlen(nptr));



    setlocale(LC_ALL, "C");

    locale_data = localeconv();

    EXPECT_STREQ(locale_data->decimal_point, original_decimal_point);

}
