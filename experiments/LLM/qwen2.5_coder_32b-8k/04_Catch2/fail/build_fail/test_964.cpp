#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <vector>



// Assuming the interface to test is part of a class named MyClass

class MyClass {

public:

    virtual ~MyClass() = default;

    virtual void addElement(int element) = 0;

    virtual bool containsElement(int element) const = 0;

    virtual std::vector<int> getElements() const = 0;

};



using ::testing::NiceMock;

using ::testing::Return;



class MockMyClass : public MyClass {

public:

    MOCK_METHOD(void, addElement, (int element), (override));

    MOCK_METHOD(bool, containsElement, (int element) const, (override));

    MOCK_METHOD(std::vector<int>, getElements, (), (const, override));

};



TEST_F(MockMyClassTest_964, AddElement_IncreasesCount_964) {

    NiceMock<MockMyClass> mock;

    std::vector<int> elements = {1, 2, 3};

    EXPECT_CALL(mock, getElements()).WillOnce(Return(elements));



    mock.addElement(4);

    elements.push_back(4);



    EXPECT_CALL(mock, getElements()).WillOnce(Return(elements));

    EXPECT_EQ(mock.getElements(), elements);

}



TEST_F(MockMyClassTest_964, ContainsElement_ReturnsTrueForExistingElement_964) {

    NiceMock<MockMyClass> mock;

    std::vector<int> elements = {1, 2, 3};

    EXPECT_CALL(mock, getElements()).WillOnce(Return(elements));



    EXPECT_TRUE(mock.containsElement(2));

}



TEST_F(MockMyClassTest_964, ContainsElement_ReturnsFalseForNonExistingElement_964) {

    NiceMock<MockMyClass> mock;

    std::vector<int> elements = {1, 2, 3};

    EXPECT_CALL(mock, getElements()).WillOnce(Return(elements));



    EXPECT_FALSE(mock.containsElement(4));

}



TEST_F(MockMyClassTest_964, GetElements_ReturnsCorrectVector_964) {

    NiceMock<MockMyClass> mock;

    std::vector<int> elements = {1, 2, 3};

    EXPECT_CALL(mock, getElements()).WillOnce(Return(elements));



    EXPECT_EQ(mock.getElements(), elements);

}



TEST_F(MockMyClassTest_964, AddElement_HandlesBoundaryConditions_964) {

    NiceMock<MockMyClass> mock;

    std::vector<int> elements = {};

    EXPECT_CALL(mock, getElements()).WillOnce(Return(elements));



    mock.addElement(0);

    elements.push_back(0);



    EXPECT_CALL(mock, getElements()).WillOnce(Return(elements));

    EXPECT_EQ(mock.getElements(), elements);

}



TEST_F(MockMyClassTest_964, ContainsElement_HandlesBoundaryConditions_964) {

    NiceMock<MockMyClass> mock;

    std::vector<int> elements = {};

    EXPECT_CALL(mock, getElements()).WillOnce(Return(elements));



    EXPECT_FALSE(mock.containsElement(0));

}
