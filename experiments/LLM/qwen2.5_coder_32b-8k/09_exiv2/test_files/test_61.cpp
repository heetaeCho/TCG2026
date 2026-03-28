#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"

#include <gmock/gmock.h>



using namespace Exiv2;

using namespace testing;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo& src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo& src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(size_t, tell, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(bool, isopen, (), (const, override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

    MOCK_METHOD(const std::string&, path, (), (const, override));

};



class IoCloserTest : public Test {

protected:

    MockBasicIo mockBio;

    IoCloser ioCloser{mockBio};

};



TEST_F(IoCloserTest_61, CloseCallsCloseOnBasicIo_61) {

    EXPECT_CALL(mockBio, close()).Times(1);

    ioCloser.close();

}



TEST_F(IoCloserTest_61, CloseDoesNothingIfAlreadyClosed_61) {

    ON_CALL(mockBio, isopen()).WillByDefault(Return(false));

    EXPECT_CALL(mockBio, close()).Times(0);

    ioCloser.close();

}



TEST_F(IoCloserTest_61, CloseOnlyCallsCloseOnce_61) {

    EXPECT_CALL(mockBio, close()).Times(1);

    ioCloser.close();

    ioCloser.close(); // Subsequent calls should not call close again

}
