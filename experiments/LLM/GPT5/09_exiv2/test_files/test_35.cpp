#include <gtest/gtest.h>
#include <string>
#include <sstream>

namespace Exiv2 {
    template <typename T>
    T stringTo(const std::string& s, bool& ok) {
        std::istringstream is(s);
        T tmp = T();
        ok = static_cast<bool>(is >> tmp);
        std::string rest;
        is >> std::skipws >> rest;
        if (!rest.empty()) ok = false;
        return tmp;
    }
}

TEST_F(Exiv2StringToTest_35, ConvertsStringToInt_35) {
    bool ok;
    int result = Exiv2::stringTo<int>("123", ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 123);
}

TEST_F(Exiv2StringToTest_35, InvalidStringToInt_35) {
    bool ok;
    int result = Exiv2::stringTo<int>("abc", ok);
    EXPECT_FALSE(ok);
    EXPECT_EQ(result, 0);
}

TEST_F(Exiv2StringToTest_35, StringWithExtraCharacters_35) {
    bool ok;
    int result = Exiv2::stringTo<int>("123abc", ok);
    EXPECT_FALSE(ok);
    EXPECT_EQ(result, 0);
}

TEST_F(Exiv2StringToTest_35, ConvertsStringToDouble_35) {
    bool ok;
    double result = Exiv2::stringTo<double>("123.456", ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, 123.456);
}

TEST_F(Exiv2StringToTest_35, InvalidStringToDouble_35) {
    bool ok;
    double result = Exiv2::stringTo<double>("abc", ok);
    EXPECT_FALSE(ok);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(Exiv2StringToTest_35, EmptyStringToInt_35) {
    bool ok;
    int result = Exiv2::stringTo<int>("", ok);
    EXPECT_FALSE(ok);
    EXPECT_EQ(result, 0);
}

TEST_F(Exiv2StringToTest_35, BoundaryStringToIntMax_35) {
    bool ok;
    int result = Exiv2::stringTo<int>("2147483647", ok); // INT_MAX for 32-bit
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, 2147483647);
}

TEST_F(Exiv2StringToTest_35, BoundaryStringToIntMin_35) {
    bool ok;
    int result = Exiv2::stringTo<int>("-2147483648", ok); // INT_MIN for 32-bit
    EXPECT_TRUE(ok);
    EXPECT_EQ(result, -2147483648);
}

TEST_F(Exiv2StringToTest_35, BoundaryStringToDoubleMax_35) {
    bool ok;
    double result = Exiv2::stringTo<double>("1.7976931348623157e308", ok); // DBL_MAX
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, 1.7976931348623157e308);
}

TEST_F(Exiv2StringToTest_35, BoundaryStringToDoubleMin_35) {
    bool ok;
    double result = Exiv2::stringTo<double>("-1.7976931348623157e308", ok); // -DBL_MAX
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, -1.7976931348623157e308);
}

TEST_F(Exiv2StringToTest_35, NonConvertibleString_35) {
    bool ok;
    int result = Exiv2::stringTo<int>("100x", ok);
    EXPECT_FALSE(ok);
    EXPECT_EQ(result, 0);
}