#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "tiffvisitor_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::InSequence;



class MockTiffVisitor : public TiffVisitor {

public:

    MOCK_METHOD(void, visitDirectory, (TiffDirectory* object), (override));

    MOCK_METHOD(void, visitDirectoryNext, (TiffDirectory* object), (override));

    MOCK_METHOD(void, visitDirectoryEnd, (TiffDirectory* object), (override));

};



class TiffDirectoryTest_342 : public ::testing::Test {

protected:

    void SetUp() override {

        directory = std::make_unique<TiffDirectory>(1, IfdId::rootIFD, false);

        visitor = std::make_unique<MockTiffVisitor>();

    }



    std::unique_ptr<TiffDirectory> directory;

    std::unique_ptr<MockTiffVisitor> visitor;

};



TEST_F(TiffDirectoryTest_342, DoAccept_VisitsDirectory_342) {

    EXPECT_CALL(*visitor, visitDirectory(_)).Times(1);

    EXPECT_CALL(*visitor, visitDirectoryNext(_)).Times(0);

    EXPECT_CALL(*visitor, visitDirectoryEnd(_)).Times(1);



    directory->doAccept(*visitor);

}



TEST_F(TiffDirectoryTest_342, DoAccept_VisitsComponents_342) {

    auto component = std::make_unique<TiffComponent>(2, IfdId::rootIFD);

    component->setStart(nullptr);

    directory->addChild(std::shared_ptr<TiffComponent>(component.release()));



    EXPECT_CALL(*visitor, visitDirectory(_)).Times(1);

    EXPECT_CALL(*visitor, visitDirectoryNext(_)).Times(0);

    EXPECT_CALL(*visitor, visitDirectoryEnd(_)).Times(1);



    directory->doAccept(*visitor);

}



TEST_F(TiffDirectoryTest_342, DoAccept_VisitsDirectoryNext_342) {

    auto nextDir = std::make_unique<TiffDirectory>(2, IfdId::rootIFD, false);

    directory->addNext(std::move(nextDir));



    EXPECT_CALL(*visitor, visitDirectory(_)).Times(1);

    EXPECT_CALL(*visitor, visitDirectoryNext(_)).Times(1);

    EXPECT_CALL(*visitor, visitDirectoryEnd(_)).Times(2);



    directory->doAccept(*visitor);

}



TEST_F(TiffDirectoryTest_342, DoAccept_StopsTraversalOnFalseGo_342) {

    visitor->setGo(GoEvent::geTraverse, false);



    EXPECT_CALL(*visitor, visitDirectory(_)).Times(1);

    EXPECT_CALL(*visitor, visitDirectoryNext(_)).Times(0);

    EXPECT_CALL(*visitor, visitDirectoryEnd(_)).Times(0);



    directory->doAccept(*visitor);

}



TEST_F(TiffDirectoryTest_342, DoAccept_VisitsAllComponentsAndDirectories_342) {

    auto component1 = std::make_unique<TiffComponent>(2, IfdId::rootIFD);

    component1->setStart(nullptr);

    directory->addChild(std::shared_ptr<TiffComponent>(component1.release()));



    auto nextDir = std::make_unique<TiffDirectory>(3, IfdId::rootIFD, false);

    directory->addNext(std::move(nextDir));



    EXPECT_CALL(*visitor, visitDirectory(_)).Times(2);

    EXPECT_CALL(*visitor, visitDirectoryNext(_)).Times(1);

    EXPECT_CALL(*visitor, visitDirectoryEnd(_)).Times(2);



    directory->doAccept(*visitor);

}
