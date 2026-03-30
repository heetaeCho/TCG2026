#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_templated.cpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_stringref.hpp"



using namespace Catch::Matchers::Detail;

using namespace Catch;



TEST(describe_multi_matcher_Test_194, NoDescriptions_194) {

    const std::string combine = "and";

    const std::vector<std::string> descriptions;

    EXPECT_EQ(describe_multi_matcher(combine, descriptions.data(), descriptions.data()), "(  )");

}



TEST(describe_multi_matcher_Test_194, SingleDescription_194) {

    const std::string combine = "and";

    const std::vector<std::string> descriptions = {"description1"};

    EXPECT_EQ(describe_multi_matcher(combine, descriptions.data(), descriptions.data() + 1), "( description1 )");

}



TEST(describe_multi_matcher_Test_194, MultipleDescriptions_194) {

    const std::string combine = "and";

    const std::vector<std::string> descriptions = {"description1", "description2", "description3"};

    EXPECT_EQ(describe_multi_matcher(combine, descriptions.data(), descriptions.data() + 3), "( description1 and description2 and description3 )");

}



TEST(describe_multi_matcher_Test_194, DifferentCombineString_194) {

    const std::string combine = "or";

    const std::vector<std::string> descriptions = {"description1", "description2"};

    EXPECT_EQ(describe_multi_matcher(combine, descriptions.data(), descriptions.data() + 2), "( description1 or description2 )");

}



TEST(describe_multi_matcher_Test_194, EmptyDescriptions_194) {

    const std::string combine = "and";

    const std::vector<std::string> descriptions = {"", ""};

    EXPECT_EQ(describe_multi_matcher(combine, descriptions.data(), descriptions.data() + 2), "(  and  )");

}
