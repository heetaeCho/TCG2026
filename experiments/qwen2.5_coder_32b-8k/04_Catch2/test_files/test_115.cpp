#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>



namespace Catch {

    class ITransientExpression { 

    private: 

        bool m_isBinaryExpression; 

        bool m_result; 



    public: 

        constexpr ITransientExpression( bool isBinaryExpression, bool result ) : m_isBinaryExpression( isBinaryExpression ), m_result( result ) {}

        constexpr ITransientExpression( const ITransientExpression& ) = default;

        virtual ~ITransientExpression() = default;



        constexpr auto isBinaryExpression() const -> bool { return m_isBinaryExpression; }

        constexpr auto getResult() const -> bool { return m_result; }



        void streamReconstructedExpression( std::ostream & os ) const;

    };

}



using namespace Catch;

using ::testing::HasSubstr;



class ITransientExpressionTest : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}



    ITransientExpression binaryTrueExpr = ITransientExpression(true, true);

    ITransientExpression unaryFalseExpr = ITransientExpression(false, false);

};



TEST_F(ITransientExpressionTest_115, IsBinaryExpression_ReturnsTrueForBinary_115) {

    EXPECT_TRUE(binaryTrueExpr.isBinaryExpression());

}



TEST_F(ITransientExpressionTest_115, IsBinaryExpression_ReturnsFalseForUnary_115) {

    EXPECT_FALSE(unaryFalseExpr.isBinaryExpression());

}



TEST_F(ITransientExpressionTest_115, GetResult_ReturnsTrueForTrueResult_115) {

    EXPECT_TRUE(binaryTrueExpr.getResult());

}



TEST_F(ITransientExpressionTest_115, GetResult_ReturnsFalseForFalseResult_115) {

    EXPECT_FALSE(unaryFalseExpr.getResult());

}



TEST_F(ITransientExpressionTest_115, StreamReconstructedExpression_OutputsCorrectStringForBinary_115) {

    std::ostringstream oss;

    binaryTrueExpr.streamReconstructedExpression(oss);

    EXPECT_THAT(oss.str(), HasSubstr("expression"));

}



TEST_F(ITransientExpressionTest_115, StreamReconstructedExpression_OutputsCorrectStringForUnary_115) {

    std::ostringstream oss;

    unaryFalseExpr.streamReconstructedExpression(oss);

    EXPECT_THAT(oss.str(), HasSubstr("expression"));

}
