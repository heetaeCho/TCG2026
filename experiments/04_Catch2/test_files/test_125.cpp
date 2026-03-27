#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace Catch {

    class BinaryExpr {

    public:

        template<typename T>

        auto operator <= (T) const -> BinaryExpr<LhsT, RhsT const&> const {

            static_assert(always_false<T>::value, "chained comparisons are not supported inside assertions, "

                                                  "wrap the expression inside parentheses, or decompose it");

        }

    };

}



// Since the provided class does not have any observable behavior through its interface

// that can be tested with Google Test, we will create a mock scenario to demonstrate

// how you might test interactions if there were external collaborators.



// Mocking an external collaborator for demonstration purposes

class ExternalCollaborator {

public:

    virtual ~ExternalCollaborator() = default;

    virtual void handleComparison(const Catch::BinaryExpr&) = 0;

};



class MockExternalCollaborator : public ExternalCollaborator {

public:

    MOCK_METHOD(void, handleComparison, (const Catch::BinaryExpr&), (override));

};



// Test fixture for testing interactions with external collaborators

class BinaryExprTest_125 : public ::testing::Test {

protected:

    std::unique_ptr<MockExternalCollaborator> mock_collaborator;



    void SetUp() override {

        mock_collaborator = std::make_unique<MockExternalCollaborator>();

    }

};



// Test case to verify that the operator <= does not allow chained comparisons

TEST_F(BinaryExprTest_125, ChainedComparisonsNotAllowed_125) {

    Catch::BinaryExpr expr;

    EXPECT_THROW((expr <= 0) <= 0, int); // static_assert will cause compilation failure if uncommented

}



// Test case to verify interaction with an external collaborator

TEST_F(BinaryExprTest_125, HandleComparisonCalled_125) {

    Catch::BinaryExpr expr;

    EXPECT_CALL(*mock_collaborator, handleComparison(::testing::_)).Times(1);

    mock_collaborator->handleComparison(expr <= 0);

}

```


