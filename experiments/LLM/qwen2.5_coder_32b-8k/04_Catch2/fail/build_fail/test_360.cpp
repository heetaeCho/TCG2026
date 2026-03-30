#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace Catch { namespace Clara { namespace Detail {



// Mock class for testing ResultValueBase

class MockResultValueBase : public ResultValueBase<int> {

public:

    MockResultValueBase(ResultType type) : ResultValueBase(type) {}

    MockResultValueBase(ResultType type, int value) : ResultValueBase(type, value) {}



    MOCK_METHOD(void, enforceOk, (), (const, override));

};



TEST_F(MockResultValueBaseTest_360, ValueAccessWithOkType_360) {

    MockResultValueBase mockResult(ResultType::Ok, 42);

    EXPECT_CALL(mockResult, enforceOk()).Times(1);

    EXPECT_EQ(mockResult.value(), 42);

}



TEST_F(MockResultValueBaseTest_360, ValueAccessWithNonOkType_360) {

    MockResultValueBase mockResult(ResultType::Error);

    EXPECT_THROW({

        EXPECT_CALL(mockResult, enforceOk()).Times(1).WillOnce([]() { throw std::runtime_error("Not Ok"); });

        mockResult.value();

    }, std::runtime_error);

}



TEST_F(MockResultValueBaseTest_360, CopyConstructorWithOkType_360) {

    MockResultValueBase original(ResultType::Ok, 42);

    EXPECT_CALL(original, enforceOk()).Times(1);

    MockResultValueBase copy = original;

    EXPECT_EQ(copy.value(), 42);

}



TEST_F(MockResultValueBaseTest_360, MoveConstructorWithOkType_360) {

    MockResultValueBase original(ResultType::Ok, 42);

    EXPECT_CALL(original, enforceOk()).Times(1);

    MockResultValueBase moved = std::move(original);

    EXPECT_EQ(moved.value(), 42);

}



TEST_F(MockResultValueBaseTest_360, CopyAssignmentWithOkType_360) {

    MockResultValueBase original(ResultType::Ok, 42);

    MockResultValueBase copy(ResultType::Error);

    EXPECT_CALL(original, enforceOk()).Times(1);

    copy = original;

    EXPECT_EQ(copy.value(), 42);

}



TEST_F(MockResultValueBaseTest_360, MoveAssignmentWithOkType_360) {

    MockResultValueBase original(ResultType::Ok, 42);

    MockResultValueBase moved(ResultType::Error);

    EXPECT_CALL(original, enforceOk()).Times(1);

    moved = std::move(original);

    EXPECT_EQ(moved.value(), 42);

}



}}} // namespace Catch::Clara::Detail
