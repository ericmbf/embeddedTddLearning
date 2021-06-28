#if UNIT_TEST
#include <unity.h>
#include <unity_fixture.h>
#include "Flash.h"
#include "m28w160ect.h"
#include "FakeMicroTime.h"
#include "MockIO.h"

ioAddress address;
ioData data;
int result;

TEST_GROUP(Flash);

TEST_SETUP(Flash)
{
    address = 0x1000;
    data = 0xBEEF;
    result = -1;
    MockIO_Init();
    Flash_Create();
}

TEST_TEAR_DOWN(Flash)
{
    Flash_Destroy();
    MockIO_Verify();
    MockIO_Destroy();
}

TEST(Flash, WriteSucceeds_ReadyImmediately)
{
    IO_Write_CMockExpect(__LINE__, CommandRegister, ProgramCommand);
    IO_Write_CMockExpect(__LINE__, address, data);
    IO_Read_CMockExpectAndReturn(__LINE__, StatusRegister, ReadyBit);
    IO_Read_CMockExpectAndReturn(__LINE__,address, data);
    result = Flash_Write(address, data);
    LONGS_EQUAL(FLASH_SUCCESS, result);
}

TEST(Flash, SucceedsNotImmediatelyReady)
{
    IO_Write_CMockExpect(__LINE__, CommandRegister, ProgramCommand);
    IO_Write_CMockExpect(__LINE__, address, data);
    IO_Read_CMockExpectAndReturn(__LINE__,StatusRegister, 0);
    IO_Read_CMockExpectAndReturn(__LINE__,StatusRegister, 0);
    IO_Read_CMockExpectAndReturn(__LINE__,StatusRegister, 0);
    IO_Read_CMockExpectAndReturn(__LINE__,StatusRegister, ReadyBit);
    IO_Read_CMockExpectAndReturn(__LINE__,address, data);

    result = Flash_Write(address, data);
    LONGS_EQUAL(FLASH_SUCCESS, result);
}

TEST(Flash, WriteFails_VppError)
{
    IO_Write_CMockExpect(__LINE__, CommandRegister, ProgramCommand);
    IO_Write_CMockExpect(__LINE__, address, data);
    IO_Read_CMockExpectAndReturn(__LINE__,StatusRegister, ReadyBit | VppErrorBit);
    IO_Write_CMockExpect(__LINE__, CommandRegister, Reset);

    result = Flash_Write(address, data);
    
    LONGS_EQUAL(FLASH_VPP_ERROR, result);
}

TEST(Flash, WriteFails_ProgramError)
{
    IO_Write_CMockExpect(__LINE__, CommandRegister, ProgramCommand);
    IO_Write_CMockExpect(__LINE__, address, data);
    IO_Read_CMockExpectAndReturn(__LINE__,StatusRegister, ReadyBit | ProgramErrorBit);
    IO_Write_CMockExpect(__LINE__, CommandRegister, Reset);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_PROGRAM_ERROR, result);
}

TEST(Flash, WriteFails_ProtectedBlockError)
{
    IO_Write_CMockExpect(__LINE__, CommandRegister, ProgramCommand);
    IO_Write_CMockExpect(__LINE__, address, data);
    IO_Read_CMockExpectAndReturn(__LINE__,StatusRegister, ReadyBit | BlockProtectionErrorBit);
    IO_Write_CMockExpect(__LINE__, CommandRegister, Reset);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_PROTECTED_BLOCK_ERROR, result);
}

TEST(Flash, WriteFails_FlashUnknownProgramError)
{
    IO_Write_CMockExpect(__LINE__, CommandRegister, ProgramCommand);
    IO_Write_CMockExpect(__LINE__, address, data);
    IO_Read_CMockExpectAndReturn(__LINE__,StatusRegister, ReadyBit |  EraseSuspendBit | EraseErrorBit | ProgramSuspendBit | ReservedBit);
    IO_Write_CMockExpect(__LINE__, CommandRegister, Reset);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_UNKNOWN_PROGRAM_ERROR, result);
}

TEST(Flash, WriteFails_FlashReadBackError)
{
    IO_Write_CMockExpect(__LINE__, CommandRegister, ProgramCommand);
    IO_Write_CMockExpect(__LINE__, address, data);
    IO_Read_CMockExpectAndReturn(__LINE__,StatusRegister, ReadyBit);
    IO_Read_CMockExpectAndReturn(__LINE__,address, data-1);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_READ_BACK_ERROR, result);
}

TEST(Flash, WriteSucceeds_IgnoresOtherBitsUntilReady)
{
    IO_Write_CMockExpect(__LINE__, CommandRegister, ProgramCommand);
    IO_Write_CMockExpect(__LINE__, address, data);
    IO_Read_CMockExpectAndReturn(__LINE__,StatusRegister, ~ReadyBit);
    IO_Read_CMockExpectAndReturn(__LINE__,StatusRegister, ReadyBit);
    IO_Read_CMockExpectAndReturn(__LINE__,address, data);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_SUCCESS, result);
}

TEST(Flash, WriteFails_Timeout)
{
    FakeMicroTime_Init(0, 500);
    Flash_Create();
    IO_Write_CMockExpect(__LINE__, CommandRegister, ProgramCommand);
    IO_Write_CMockExpect(__LINE__, address, data);
    for (int i = 0; i < 10; i++)
    {
        IO_Read_CMockExpectAndReturn(__LINE__,StatusRegister, ~ReadyBit);
    }

    result = Flash_Write(address, data);
    LONGS_EQUAL(FLASH_TIMEOUT_ERROR, result);
}

TEST(Flash, WriteFails_TimeoutAtEndOfTime)
{
    FakeMicroTime_Init(0xffffffff, 500);
    Flash_Create();
    IO_Write_CMockExpect(__LINE__, CommandRegister, ProgramCommand);
    IO_Write_CMockExpect(__LINE__, address, data);
    
    for (int i = 0; i < 10; i++)
    {
        IO_Read_CMockExpectAndReturn(__LINE__,StatusRegister, ~ReadyBit);
    }

    result = Flash_Write(address, data);
    LONGS_EQUAL(FLASH_TIMEOUT_ERROR, result);
}
#endif