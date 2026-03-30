#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/yaml-cpp/src/null.cpp"



namespace YAML {



class SameFunctionTest_588 : public ::testing::Test {

protected:

    template<std::size_t N>

    bool same(const char* str, std::size_t size, const char (&literal)[N]) {

        return YAML::same(str, size, literal);

    }

};



TEST_F(SameFunctionTest_588, ExactMatch_588) {

    EXPECT_TRUE(same("test", 4, "test"));

}



TEST_F(SameFunctionTest_588, DifferentContent_588) {

    EXPECT_FALSE(same("test", 4, "tset"));

}



TEST_F(SameFunctionTest_588, LongerInputString_588) {

    EXPECT_FALSE(same("testing", 7, "test"));

}



TEST_F(SameFunctionTest_588, ShorterInputString_588) {

    EXPECT_FALSE(same("tes", 3, "test"));

}



TEST_F(SameFunctionTest_588, EmptyStrings_588) {

    EXPECT_TRUE(same("", 0, ""));

}



TEST_F(SameFunctionTest_588, NullInputString_588) {

    EXPECT_FALSE(same(nullptr, 0, "test"));

}



TEST_F(SameFunctionTest_588, ZeroSizeWithNonEmptyLiteral_588) {

    EXPECT_FALSE(same("test", 0, "test"));

}



} // namespace YAML
