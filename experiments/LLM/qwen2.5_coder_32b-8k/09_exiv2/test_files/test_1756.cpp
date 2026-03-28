#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(size_t, read, (size_t rcount), (override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(size_t, tell, (), (const, override));

};



TEST_F(MockBasicIoTest_1756, NormalOperationMatchDosEpsSignature_1756) {

    MockBasicIo mockIo;

    const std::string dosEpsSignature = "\305\320\323\306";

    EXPECT_CALL(mockIo, read(dosEpsSignature.size())).WillOnce(Return(DataBuf(dosEpsSignature.c_str(), dosEpsSignature.size())));

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mockIo, tell()).Times(1).WillOnce(Return(0));

    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).Times(2);



    bool result = isEpsType(mockIo, true);

    EXPECT_TRUE(result);

}



TEST_F(MockBasicIoTest_1756, NormalOperationMatchEpsFirstLine_1756) {

    MockBasicIo mockIo;

    const std::string epsFirstLine = "%!PS-Adobe-3.0 EPSF-3.0";

    EXPECT_CALL(mockIo, read(epsFirstLine.size())).WillOnce(Return(DataBuf(epsFirstLine.c_str(), epsFirstLine.size())));

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mockIo, tell()).Times(1).WillOnce(Return(0));

    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).Times(2);



    bool result = isEpsType(mockIo, true);

    EXPECT_TRUE(result);

}



TEST_F(MockBasicIoTest_1756, BoundaryConditionReadLessThanBufSize_1756) {

    MockBasicIo mockIo;

    const std::string partialSignature = "\305\320";

    EXPECT_CALL(mockIo, read(partialSignature.size())).WillOnce(Return(DataBuf(partialSignature.c_str(), partialSignature.size())));

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockIo, tell()).Times(1).WillOnce(Return(0));

    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).Times(2);



    bool result = isEpsType(mockIo, true);

    EXPECT_FALSE(result);

}



TEST_F(MockBasicIoTest_1756, ErrorDuringRead_1756) {

    MockBasicIo mockIo;

    EXPECT_CALL(mockIo, read(::testing::_)).WillOnce(Return(DataBuf()));

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockIo, tell()).Times(1).WillOnce(Return(0));

    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).Times(2);



    bool result = isEpsType(mockIo, true);

    EXPECT_FALSE(result);

}



TEST_F(MockBasicIoTest_1756, AdvanceFalseDoesNotSeekBack_1756) {

    MockBasicIo mockIo;

    const std::string dosEpsSignature = "\305\320\323\306";

    EXPECT_CALL(mockIo, read(dosEpsSignature.size())).WillOnce(Return(DataBuf(dosEpsSignature.c_str(), dosEpsSignature.size())));

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mockIo, tell()).Times(1).WillOnce(Return(0));

    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).Times(1);



    bool result = isEpsType(mockIo, false);

    EXPECT_TRUE(result);

}



TEST_F(MockBasicIoTest_1756, NoMatchOnAdvanceFalseDoesNotSeekBack_1756) {

    MockBasicIo mockIo;

    const std::string invalidSignature = "INVALID";

    EXPECT_CALL(mockIo, read(invalidSignature.size())).WillOnce(Return(DataBuf(invalidSignature.c_str(), invalidSignature.size())));

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mockIo, tell()).Times(1).WillOnce(Return(0));

    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).Times(2);



    bool result = isEpsType(mockIo, false);

    EXPECT_FALSE(result);

}



TEST_F(MockBasicIoTest_1756, NoMatchOnAdvanceTrueSeeksBack_1756) {

    MockBasicIo mockIo;

    const std::string invalidSignature = "INVALID";

    EXPECT_CALL(mockIo, read(invalidSignature.size())).WillOnce(Return(DataBuf(invalidSignature.c_str(), invalidSignature.size())));

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(mockIo, tell()).Times(1).WillOnce(Return(0));

    EXPECT_CALL(mockIo, seek(0, BasicIo::beg)).Times(2);



    bool result = isEpsType(mockIo, true);

    EXPECT_FALSE(result);

}
