#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>

namespace {

// Mock class for BasicIo to test IoCloser behavior
class MockBasicIo : public Exiv2::BasicIo {
 public:
  MOCK_METHOD(int, open, (), (override));
  MOCK_METHOD(int, close, (), (override));
  MOCK_METHOD(size_t, write, (const Exiv2::byte* data, size_t wcount), (override));
  MOCK_METHOD(size_t, write, (Exiv2::BasicIo& src), (override));
  MOCK_METHOD(int, putb, (Exiv2::byte data), (override));
  MOCK_METHOD(Exiv2::DataBuf, read, (size_t rcount), (override));
  MOCK_METHOD(size_t, read, (Exiv2::byte* buf, size_t rcount), (override));
  MOCK_METHOD(int, getb, (), (override));
  MOCK_METHOD(void, transfer, (Exiv2::BasicIo& src), (override));
  MOCK_METHOD(int, seek, (int64_t offset, Exiv2::BasicIo::Position pos), (override));
  MOCK_METHOD(Exiv2::byte*, mmap, (bool isWriteable), (override));
  MOCK_METHOD(int, munmap, (), (override));
  MOCK_METHOD(size_t, tell, (), (const, override));
  MOCK_METHOD(size_t, size, (), (const, override));
  MOCK_METHOD(bool, isopen, (), (const, override));
  MOCK_METHOD(int, error, (), (const, override));
  MOCK_METHOD(bool, eof, (), (const, override));
  MOCK_METHOD(const std::string&, path, (), (const, override));
  MOCK_METHOD(void, populateFakeData, (), (override));
};

class IoCloserTest_61 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that IoCloser::close() calls bio_.close() when bio_ is open
TEST_F(IoCloserTest_61, CloseCallsCloseWhenOpen_61) {
  MockBasicIo mockIo;
  Exiv2::IoCloser closer(mockIo);

  EXPECT_CALL(mockIo, isopen())
      .WillOnce(::testing::Return(true));
  EXPECT_CALL(mockIo, close())
      .Times(1);

  closer.close();
}

// Test that IoCloser::close() does NOT call bio_.close() when bio_ is not open
TEST_F(IoCloserTest_61, CloseDoesNotCallCloseWhenNotOpen_61) {
  MockBasicIo mockIo;
  Exiv2::IoCloser closer(mockIo);

  EXPECT_CALL(mockIo, isopen())
      .WillOnce(::testing::Return(false));
  EXPECT_CALL(mockIo, close())
      .Times(0);

  closer.close();
}

// Test that IoCloser can be constructed with a BasicIo reference
TEST_F(IoCloserTest_61, ConstructionWithBasicIo_61) {
  MockBasicIo mockIo;
  // Should not throw or crash
  Exiv2::IoCloser closer(mockIo);
}

// Test that calling close() multiple times works correctly
// First call: io is open -> close called
// Second call: io is no longer open -> close not called
TEST_F(IoCloserTest_61, MultipleCloseCallsHandledCorrectly_61) {
  MockBasicIo mockIo;
  Exiv2::IoCloser closer(mockIo);

  {
    ::testing::InSequence seq;
    // First close call: io is open
    EXPECT_CALL(mockIo, isopen())
        .WillOnce(::testing::Return(true));
    EXPECT_CALL(mockIo, close())
        .Times(1)
        .WillOnce(::testing::Return(0));
    // Second close call: io is no longer open
    EXPECT_CALL(mockIo, isopen())
        .WillOnce(::testing::Return(false));
  }

  closer.close();
  closer.close();
}

// Test that the destructor exists and can be called (IoCloser goes out of scope)
TEST_F(IoCloserTest_61, DestructorDoesNotCrash_61) {
  MockBasicIo mockIo;
  // Allow any calls to isopen and close during destruction
  EXPECT_CALL(mockIo, isopen())
      .WillRepeatedly(::testing::Return(false));
  EXPECT_CALL(mockIo, close())
      .Times(::testing::AnyNumber());

  {
    Exiv2::IoCloser closer(mockIo);
    // closer goes out of scope here
  }
}

// Test close() when isopen returns true multiple consecutive times
TEST_F(IoCloserTest_61, CloseCalledWhenAlwaysOpen_61) {
  MockBasicIo mockIo;
  Exiv2::IoCloser closer(mockIo);

  EXPECT_CALL(mockIo, isopen())
      .Times(3)
      .WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(mockIo, close())
      .Times(3)
      .WillRepeatedly(::testing::Return(0));

  closer.close();
  closer.close();
  closer.close();
}

}  // namespace
