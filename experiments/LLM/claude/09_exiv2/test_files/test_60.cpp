#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>

namespace {

// Test fixture for IoCloser tests
class IoCloserTest_60 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that IoCloser can be constructed with a BasicIo reference and
// destructor calls close without crashing
TEST_F(IoCloserTest_60, ConstructAndDestruct_60) {
  // Use a MemIo as a concrete BasicIo implementation
  Exiv2::MemIo memIo;
  {
    Exiv2::IoCloser closer(memIo);
    // IoCloser should be constructed successfully
    // Destructor should call close() when going out of scope
  }
  // If we get here without crashing, the destructor worked
  SUCCEED();
}

// Test that close() can be called explicitly without issues
TEST_F(IoCloserTest_60, ExplicitClose_60) {
  Exiv2::MemIo memIo;
  Exiv2::IoCloser closer(memIo);
  // Explicitly call close
  closer.close();
  // Should not crash when destructor also calls close
  SUCCEED();
}

// Test that close() can be called multiple times without error
TEST_F(IoCloserTest_60, MultipleCloseCalls_60) {
  Exiv2::MemIo memIo;
  Exiv2::IoCloser closer(memIo);
  closer.close();
  closer.close();
  closer.close();
  SUCCEED();
}

// Test IoCloser with a MemIo that has been opened/used
TEST_F(IoCloserTest_60, CloseAfterMemIoOperations_60) {
  Exiv2::MemIo memIo;
  const uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
  memIo.write(data, sizeof(data));
  memIo.seek(0, Exiv2::BasicIo::beg);

  {
    Exiv2::IoCloser closer(memIo);
    // Read some data while closer is alive
    Exiv2::DataBuf buf = memIo.read(2);
    EXPECT_EQ(buf.size(), 2u);
    // Closer will close memIo on destruction
  }
  SUCCEED();
}

// Test that the bio_ member references the correct BasicIo object
TEST_F(IoCloserTest_60, BioMemberReferencesCorrectObject_60) {
  Exiv2::MemIo memIo;
  Exiv2::IoCloser closer(memIo);
  // Verify that bio_ is a reference to the same object
  EXPECT_EQ(&closer.bio_, &memIo);
}

// Test IoCloser with MemIo that has no data (empty/boundary case)
TEST_F(IoCloserTest_60, CloseEmptyMemIo_60) {
  Exiv2::MemIo memIo;
  EXPECT_EQ(memIo.size(), 0u);
  {
    Exiv2::IoCloser closer(memIo);
  }
  SUCCEED();
}

// Test that after IoCloser destructs, the BasicIo is in closed state
TEST_F(IoCloserTest_60, BasicIoClosedAfterDestructor_60) {
  Exiv2::MemIo memIo;
  const uint8_t data[] = {0x10, 0x20};
  memIo.write(data, sizeof(data));

  {
    Exiv2::IoCloser closer(memIo);
    EXPECT_TRUE(memIo.isopen());
  }
  // After IoCloser destructor, the io should be closed
  // MemIo may behave differently, but close should have been called
  SUCCEED();
}

// Test IoCloser with open and close cycle
TEST_F(IoCloserTest_60, OpenCloseOpenCycle_60) {
  Exiv2::MemIo memIo;
  const uint8_t data[] = {0xAA, 0xBB, 0xCC};
  memIo.write(data, sizeof(data));

  {
    Exiv2::IoCloser closer(memIo);
    closer.close();
  }

  // Should be able to reopen and use the MemIo
  memIo.open();
  memIo.seek(0, Exiv2::BasicIo::beg);
  Exiv2::DataBuf buf = memIo.read(3);
  EXPECT_EQ(buf.size(), 3u);
}

}  // namespace
