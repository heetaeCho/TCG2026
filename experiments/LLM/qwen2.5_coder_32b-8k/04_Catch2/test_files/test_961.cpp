#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the class under test is named MyClass and has some methods like:

// void Put(const std::string& key, const std::string& value);

// std::string Get(const std::string& key) const;

// size_t Count() const;



class MyClass {

public:

    virtual ~MyClass() = default;

    virtual void Put(const std::string& key, const std::string& value) = 0;

    virtual std::string Get(const std::string& key) const = 0;

    virtual size_t Count() const = 0;

};



class MockMyClass : public MyClass {

public:

    MOCK_METHOD(void, Put, (const std::string& key, const std::string& value), (override));

    MOCK_METHOD(std::string, Get, (const std::string& key) const, (override));

    MOCK_METHOD(size_t, Count, (), (const, override));

};



class MyClassTest : public ::testing::Test {

protected:

    std::unique_ptr<MockMyClass> mock_my_class;



    void SetUp() override {

        mock_my_class = std::make_unique<MockMyClass>();

    }

};



TEST_F(MyClassTest_961, PutAndGet_NormalOperation_961) {

    EXPECT_CALL(*mock_my_class, Put("key1", "value1")).Times(1);

    EXPECT_CALL(*mock_my_class, Get("key1")).WillOnce(::testing::Return("value1"));



    mock_my_class->Put("key1", "value1");

    EXPECT_EQ(mock_my_class->Get("key1"), "value1");

}



TEST_F(MyClassTest_961, Count_IncreasesAfterPut_961) {

    EXPECT_CALL(*mock_my_class, Put("key1", "value1")).Times(1);

    EXPECT_CALL(*mock_my_class, Count()).WillOnce(::testing::Return(0)).WillOnce(::testing::Return(1));



    EXPECT_EQ(mock_my_class->Count(), 0);

    mock_my_class->Put("key1", "value1");

    EXPECT_EQ(mock_my_class->Count(), 1);

}



TEST_F(MyClassTest_961, Get_ReturnsEmptyStringForNonExistentKey_961) {

    EXPECT_CALL(*mock_my_class, Get("non_existent_key")).WillOnce(::testing::Return(""));



    EXPECT_EQ(mock_my_class->Get("non_existent_key"), "");

}



TEST_F(MyClassTest_961, Count_ReturnsZeroInitially_961) {

    EXPECT_CALL(*mock_my_class, Count()).WillOnce(::testing::Return(0));



    EXPECT_EQ(mock_my_class->Count(), 0);

}
