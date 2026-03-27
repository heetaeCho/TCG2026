#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/generators/catch_generators.hpp"



using namespace Catch::Generators;



// Assuming we have a class that uses the table generator from Catch2 for testing purposes.

// Since the actual class is not provided, we will create a mock class to demonstrate how to write tests.



class MockExternalHandler {

public:

    MOCK_METHOD(void, HandleTuple, (const std::tuple<int, std::string>&), ());

};



class ClassUnderTest {

public:

    void ProcessTable(MockExternalHandler& handler) {

        auto gen = table<std::tuple<int, std::string>>({

            std::make_tuple(1, "one"),

            std::make_tuple(2, "two"),

            std::make_tuple(3, "three")

        });



        while (gen.next()) {

            handler.HandleTuple(gen.get());

        }

    }

};



class ClassUnderTestTest : public ::testing::Test {

protected:

    MockExternalHandler mock_handler;

    ClassUnderTest class_under_test;

};



TEST_F(ClassUnderTestTest, ProcessTable_CallsHandleTupleWithCorrectTuples_322) {

    EXPECT_CALL(mock_handler, HandleTuple(std::make_tuple(1, "one")));

    EXPECT_CALL(mock_handler, HandleTuple(std::make_tuple(2, "two")));

    EXPECT_CALL(mock_handler, HandleTuple(std::make_tuple(3, "three")));



    class_under_test.ProcessTable(mock_handler);

}



TEST_F(ClassUnderTestTest, ProcessTable_VerifyCallOrder_322) {

    // Using InSequence to verify the order of calls

    ::testing::InSequence seq;

    EXPECT_CALL(mock_handler, HandleTuple(std::make_tuple(1, "one")));

    EXPECT_CALL(mock_handler, HandleTuple(std::make_tuple(2, "two")));

    EXPECT_CALL(mock_handler, HandleTuple(std::make_tuple(3, "three")));



    class_under_test.ProcessTable(mock_handler);

}



// Assuming there are no exceptional or error cases based on the provided interface.

```


