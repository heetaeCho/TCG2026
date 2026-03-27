#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.h"

#include <string>



using namespace re2;

using ::testing::ElementsAre;



class RewriteTest_265 : public ::testing::Test {

protected:

    RE2 re2_obj(".*");

};



TEST_F(RewriteTest_265, NormalOperation_NoSubstitutions_265) {

    std::string out;

    absl::string_view rewrite = "hello";

    const absl::string_view vec[] = {};

    int veclen = 0;



    bool result = re2_obj.Rewrite(&out, rewrite, vec, veclen);

    EXPECT_TRUE(result);

    EXPECT_EQ(out, "hello");

}



TEST_F(RewriteTest_265, NormalOperation_Substitutions_265) {

    std::string out;

    absl::string_view rewrite = "prefix \\0 suffix";

    const absl::string_view vec[] = {"world"};

    int veclen = 1;



    bool result = re2_obj.Rewrite(&out, rewrite, vec, veclen);

    EXPECT_TRUE(result);

    EXPECT_EQ(out, "prefix world suffix");

}



TEST_F(RewriteTest_265, BoundaryCondition_EmptyRewrite_265) {

    std::string out;

    absl::string_view rewrite = "";

    const absl::string_view vec[] = {};

    int veclen = 0;



    bool result = re2_obj.Rewrite(&out, rewrite, vec, veclen);

    EXPECT_TRUE(result);

    EXPECT_EQ(out, "");

}



TEST_F(RewriteTest_265, BoundaryCondition_EmptySubstitution_265) {

    std::string out;

    absl::string_view rewrite = "prefix \\0 suffix";

    const absl::string_view vec[] = {""};

    int veclen = 1;



    bool result = re2_obj.Rewrite(&out, rewrite, vec, veclen);

    EXPECT_TRUE(result);

    EXPECT_EQ(out, "prefix  suffix");

}



TEST_F(RewriteTest_265, ExceptionalCase_InvalidSubstitutionIndex_265) {

    std::string out;

    absl::string_view rewrite = "prefix \\1 suffix";

    const absl::string_view vec[] = {"world"};

    int veclen = 1;



    bool result = re2_obj.Rewrite(&out, rewrite, vec, veclen);

    EXPECT_FALSE(result);

}



TEST_F(RewriteTest_265, ExceptionalCase_InvalidRewritePattern_265) {

    std::string out;

    absl::string_view rewrite = "prefix \\x suffix";

    const absl::string_view vec[] = {};

    int veclen = 0;



    bool result = re2_obj.Rewrite(&out, rewrite, vec, veclen);

    EXPECT_FALSE(result);

}



TEST_F(RewriteTest_265, ExceptionalCase_OutOfBoundsSubstitutionIndex_265) {

    std::string out;

    absl::string_view rewrite = "prefix \\1 suffix";

    const absl::string_view vec[] = {"world"};

    int veclen = 0;



    bool result = re2_obj.Rewrite(&out, rewrite, vec, veclen);

    EXPECT_FALSE(result);

}



TEST_F(RewriteTest_265, ExceptionalCase_EmptyVectorWithSubstitution_265) {

    std::string out;

    absl::string_view rewrite = "prefix \\0 suffix";

    const absl::string_view vec[] = {};

    int veclen = 0;



    bool result = re2_obj.Rewrite(&out, rewrite, vec, veclen);

    EXPECT_FALSE(result);

}
