#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_container_properties.hpp"



// Assuming there's a class or interface that uses SizeIs matcher

// For the sake of this example, let's assume we have a Container class that uses SizeIs



class Container {

public:

    void addElement(const std::string& element) {

        elements_.push_back(element);

    }



    size_t getSize() const {

        return elements_.size();

    }



private:

    std::vector<std::string> elements_;

};



// Mock class for any potential external collaborators

class MockHandler {

public:

    MOCK_METHOD(void, handleSize, (size_t), ());

};



TEST_F(ContainerTest_235, AddElementIncreasesSize_235) {

    Container container;

    EXPECT_EQ(container.getSize(), 0);

    container.addElement("test");

    EXPECT_EQ(container.getSize(), 1);

}



TEST_F(ContainerTest_235, MultipleAddElementsIncreaseSizeCorrectly_235) {

    Container container;

    container.addElement("test1");

    container.addElement("test2");

    container.addElement("test3");

    EXPECT_EQ(container.getSize(), 3);

}



TEST_F(ContainerTest_235, BoundaryConditionEmptyContainer_235) {

    Container container;

    EXPECT_EQ(container.getSize(), 0);

}



TEST_F(ContainerTest_235, BoundaryConditionSingleElement_235) {

    Container container;

    container.addElement("single");

    EXPECT_EQ(container.getSize(), 1);

}



// Assuming there's a function that uses SizeIs matcher to check the size

bool checkSizeUsingMatcher(const Container& container, size_t expectedSize) {

    return Catch::Matchers::SizeIs(expectedSize).match(container.elements_);

}



TEST_F(ContainerTest_235, CheckSizeUsingMatcher_NormalOperation_235) {

    Container container;

    container.addElement("test1");

    container.addElement("test2");

    EXPECT_TRUE(checkSizeUsingMatcher(container, 2));

}



TEST_F(ContainerTest_235, CheckSizeUsingMatcher_WrongSize_235) {

    Container container;

    container.addElement("test1");

    EXPECT_FALSE(checkSizeUsingMatcher(container, 2));

}



// Assuming there's a function that takes a handler and calls it with the size

void reportSize(const Container& container, MockHandler& handler) {

    handler.handleSize(container.getSize());

}



TEST_F(ContainerTest_235, ReportSize_CallsHandlerWithCorrectSize_235) {

    Container container;

    container.addElement("test1");

    container.addElement("test2");



    MockHandler mockHandler;

    EXPECT_CALL(mockHandler, handleSize(2));



    reportSize(container, mockHandler);

}
