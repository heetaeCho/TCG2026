

Let's assume we have the following interface (class definition) for which we need to write unit tests:



```cpp

// ExampleClass.hpp

#include <string>



class ExternalDependency {

public:

    virtual ~ExternalDependency() = default;

    virtual void notify(const std::string& message) = 0;

};



class ExampleClass {

public:

    explicit ExampleClass(ExternalDependency* dependency);

    bool setValue(int value);

    int getValue() const;

    void processValue();

private:

    ExternalDependency* m_dependency;

    int m_value;

};

```



And here are the unit tests for this class following your constraints:



```cpp

// ExampleClassTests.cpp



#include "ExampleClass.hpp"

#include <gmock/gmock.h>

#include <gtest/gtest.h>



using namespace ::testing;



class MockExternalDependency : public ExternalDependency {

public:

    MOCK_METHOD(void, notify, (const std::string& message), (override));

};



class ExampleClassTest_925 : public Test {

protected:

    MockExternalDependency mock_dependency;

    ExampleClass example_class{ &mock_dependency };

};



TEST_F(ExampleClassTest_925, SetValue_ReturnsTrueForValidInput_925) {

    EXPECT_TRUE(example_class.setValue(42));

}



TEST_F(ExampleClassTest_925, GetValue_ReturnsSetValue_925) {

    example_class.setValue(10);

    EXPECT_EQ(example_class.getValue(), 10);

}



TEST_F(ExampleClassTest_925, ProcessValue_NotifiesDependencyWithCorrectMessage_925) {

    example_class.setValue(5);

    EXPECT_CALL(mock_dependency, notify("Processed value: 5"));

    example_class.processValue();

}



TEST_F(ExampleClassTest_925, ProcessValue_DoesNotNotifyIfValueIsZero_925) {

    example_class.setValue(0);

    EXPECT_CALL(mock_dependency, notify(_)).Times(0);

    example_class.processValue();

}



TEST_F(ExampleClassTest_925, SetValue_HandlesNegativeValues_925) {

    EXPECT_TRUE(example_class.setValue(-1));

}



TEST_F(ExampleClassTest_925, GetValue_ReturnsZeroInitially_925) {

    EXPECT_EQ(example_class.getValue(), 0);

}

```


