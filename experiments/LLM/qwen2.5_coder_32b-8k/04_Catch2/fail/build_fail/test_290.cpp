#include <gtest/gtest.h>

#include "catch2/catch_assertion_result.hpp"

#include "catch2/internal/catch_lazy_expr.hpp"



using namespace Catch;



class AssertionResultDataTest_290 : public ::testing::Test {

protected:

    LazyExpression lazyExpr;

    AssertionResultData data;



    AssertionResultDataTest_290() 

        : lazyExpr(false), 

          data(ResultWas::OfType::Ok, lazyExpr) {}

};



TEST_F(AssertionResultDataTest_290, ReconstructExpression_EmptyInitially_290) {

    EXPECT_EQ(data.reconstructExpression(), "");

}



TEST_F(AssertionResultDataTest_290, ReconstructExpression_CachesReconstructedExpression_290) {

    std::ostringstream oss;

    oss << lazyExpr;

    const std::string expected = oss.str();



    EXPECT_EQ(data.reconstructExpression(), expected);

    EXPECT_EQ(data.reconstructExpression(), expected); // Ensure it's cached

}



TEST_F(AssertionResultDataTest_290, ReconstructExpression_ReturnsLazyExpressionString_290) {

    lazyExpr.get() << "Some expression";

    const std::string expected = "Some expression";



    EXPECT_EQ(data.reconstructExpression(), expected);

}
