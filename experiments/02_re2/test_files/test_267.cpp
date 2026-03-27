#include <gtest/gtest.h>

#include <string>



namespace re2 {

namespace re2_internal {



template <> bool Parse(const char* str, size_t n, std::string* dest);



}  // namespace re2_internal

}  // namespace re2



using namespace re2::re2_internal;



class ParseTest_267 : public ::testing::Test {};



TEST_F(ParseTest_267, NormalOperationWithValidInput_267) {

    std::string dest;

    const char* str = "Hello";

    size_t n = 5;

    EXPECT_TRUE(Parse(str, n, &dest));

    EXPECT_EQ(dest, "Hello");

}



TEST_F(ParseTest_267, NormalOperationWithEmptyString_267) {

    std::string dest;

    const char* str = "";

    size_t n = 0;

    EXPECT_TRUE(Parse(str, n, &dest));

    EXPECT_EQ(dest, "");

}



TEST_F(ParseTest_267, BoundaryConditionWithNullDestination_267) {

    const char* str = "Hello";

    size_t n = 5;

    EXPECT_TRUE(Parse(str, n, nullptr));

}



TEST_F(ParseTest_267, ExceptionalCaseWithLargeSize_267) {

    std::string dest;

    const char* str = "Hello";

    size_t n = 10;  // Larger than the actual string length

    EXPECT_TRUE(Parse(str, n, &dest));

    EXPECT_EQ(dest, "Hello");

}



TEST_F(ParseTest_267, BoundaryConditionWithExactSize_267) {

    std::string dest;

    const char* str = "World";

    size_t n = 5;  // Exact length of the string

    EXPECT_TRUE(Parse(str, n, &dest));

    EXPECT_EQ(dest, "World");

}
