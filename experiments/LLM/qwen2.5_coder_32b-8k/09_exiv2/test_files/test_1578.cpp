#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "rw2image.hpp"

#include "basicio.hpp"

#include "error.hpp"

#include <sstream>



using namespace Exiv2;

using ::testing::Return;

using ::testing::_;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo & src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte * buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo & src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string &, path, (), (const override));

    MOCK_METHOD(void, populateFakeData, (), (override));

};



bool mockIsRw2Type(BasicIo& io, [[maybe_unused]] bool /*verbose*/) {

    return true;

}



TEST_F(Rw2ImageTest_1578, PrintStructure_SuccessfulOpenAndValidRw2_1578) {

    auto mockIo = std::make_unique<MockBasicIo>();

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(Return("test_path"));

    EXPECT_CALL(*mockIo, seek(0, BasicIo::beg)).WillOnce(Return(0));



    Rw2Image rw2Image(std::move(mockIo));

    std::ostringstream out;

    rw2Image.printStructure(out, PrintStructureOption::kpsNone, 0);

    

    EXPECT_EQ("RW2 IMAGE\n", out.str());

}



TEST_F(Rw2ImageTest_1578, PrintStructure_OpenFailed_1578) {

    auto mockIo = std::make_unique<MockBasicIo>();

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(-1));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(Return("test_path"));



    Rw2Image rw2Image(std::move(mockIo));

    EXPECT_THROW(rw2Image.printStructure(std::ostringstream(), PrintStructureOption::kpsNone, 0), Error);

}



TEST_F(Rw2ImageTest_1578, PrintStructure_NotRw2Type_ErrorNotAJpeg_1578) {

    auto mockIo = std::make_unique<MockBasicIo>();

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(Return("test_path"));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(false));



    Rw2Image rw2Image(std::move(mockIo));

    auto originalIsRw2Type = Exiv2::isRw2Type;

    Exiv2::isRw2Type = [](BasicIo& io, bool verbose) { return false; };



    EXPECT_THROW(rw2Image.printStructure(std::ostringstream(), PrintStructureOption::kpsNone, 0), Error);



    Exiv2::isRw2Type = originalIsRw2Type;

}



TEST_F(Rw2ImageTest_1578, PrintStructure_ErrorReadingImageData_1578) {

    auto mockIo = std::make_unique<MockBasicIo>();

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(Return("test_path"));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(-1));



    Rw2Image rw2Image(std::move(mockIo));

    EXPECT_THROW(rw2Image.printStructure(std::ostringstream(), PrintStructureOption::kpsNone, 0), Error);

}
