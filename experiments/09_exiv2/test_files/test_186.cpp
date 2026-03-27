#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/tags_int.hpp"

#include <sstream>

#include <string>



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Invoke;



class MockValue {

public:

    MOCK_METHOD0(toString, std::string());

};



TEST_F(printTagVocabularyTest_186, NormalOperation_186) {

    const TagVocabulary tagArray[] = {{"Key1", "Label1"}, {"Key2", "Label2"}};

    MockValue mockValue;

    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("Key1"));



    std::ostringstream os;

    printTagVocabulary(os, mockValue, nullptr);



    ASSERT_EQ(os.str(), "Label1");

}



TEST_F(printTagVocabularyTest_186, BoundaryCondition_EmptyString_186) {

    const TagVocabulary tagArray[] = {{"Key1", "Label1"}, {"Key2", "Label2"}};

    MockValue mockValue;

    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return(""));



    std::ostringstream os;

    printTagVocabulary(os, mockValue, nullptr);



    ASSERT_EQ(os.str(), "( )");

}



TEST_F(printTagVocabularyTest_186, BoundaryCondition_NoMatch_186) {

    const TagVocabulary tagArray[] = {{"Key1", "Label1"}, {"Key2", "Label2"}};

    MockValue mockValue;

    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("NonExistentKey"));



    std::ostringstream os;

    printTagVocabulary(os, mockValue, nullptr);



    ASSERT_EQ(os.str(), "(NonExistentKey)");

}



TEST_F(printTagVocabularyTest_186, BoundaryCondition_SingleElementMatch_186) {

    const TagVocabulary tagArray[] = {{"Key1", "Label1"}};

    MockValue mockValue;

    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("Key1"));



    std::ostringstream os;

    printTagVocabulary(os, mockValue, nullptr);



    ASSERT_EQ(os.str(), "Label1");

}



TEST_F(printTagVocabularyTest_186, BoundaryCondition_SingleElementNoMatch_186) {

    const TagVocabulary tagArray[] = {{"Key1", "Label1"}};

    MockValue mockValue;

    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return("NonExistentKey"));



    std::ostringstream os;

    printTagVocabulary(os, mockValue, nullptr);



    ASSERT_EQ(os.str(), "(NonExistentKey)");

}
