#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the class we are testing is named MyClass and has some functions like setValue, getValue etc.

// Since no actual interface is provided, I'll create a mock example based on common practices.



class ExternalCollaborator {

public:

    virtual ~ExternalCollaborator() = default;

    virtual void notify(int value) = 0;

};



class MyClass {

public:

    MyClass(ExternalCollaborator* collaborator) : collaborator_(collaborator) {}



    void setValue(int value) {

        // Some internal logic to set the value

        if (collaborator_) {

            collaborator_->notify(value);

        }

    }



    int getValue() const {

        // Some internal logic to get the value

        return value_;

    }



private:

    ExternalCollaborator* collaborator_ = nullptr;

    int value_ = 0;

};



class MockExternalCollaborator : public ExternalCollaborator {

public:

    MOCK_METHOD(void, notify, (int), (override));

};



class MyClassTest : public ::testing::Test {

protected:

    std::unique_ptr<MockExternalCollaborator> mock_collaborator_;

    std::unique_ptr<MyClass> my_class_;



    void SetUp() override {

        mock_collaborator_ = std::make_unique<MockExternalCollaborator>();

        my_class_ = std::make_unique<MyClass>(mock_collaborator_.get());

    }

};



TEST_F(MyClassTest_SetValueAndGetNormalOperation_960, SetValueAndGetReturnsTheSameValue_960) {

    int test_value = 42;

    my_class_->setValue(test_value);

    EXPECT_EQ(my_class_->getValue(), test_value);

}



TEST_F(MyClassTest_BoundaryConditions_960, BoundaryConditionMinimumIntValue_960) {

    int min_int = std::numeric_limits<int>::min();

    my_class_->setValue(min_int);

    EXPECT_EQ(my_class_->getValue(), min_int);

}



TEST_F(MyClassTest_BoundaryConditions_960, BoundaryConditionMaximumIntValue_960) {

    int max_int = std::numeric_limits<int>::max();

    my_class_->setValue(max_int);

    EXPECT_EQ(my_class_->getValue(), max_int);

}



TEST_F(MyClassTest_VerifyExternalInteractions_960, SetValueCallsNotifyOnCollaborator_960) {

    int test_value = 123;

    EXPECT_CALL(*mock_collaborator_, notify(test_value));

    my_class_->setValue(test_value);

}
