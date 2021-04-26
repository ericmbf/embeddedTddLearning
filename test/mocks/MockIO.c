/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "MockIO.h"

static const char* CMockString_IO_Read = "IO_Read";
static const char* CMockString_IO_Write = "IO_Write";
static const char* CMockString_data = "data";
static const char* CMockString_offset = "offset";

typedef struct _CMOCK_IO_Read_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  ioData ReturnVal;
  ioAddress Expected_offset;

} CMOCK_IO_Read_CALL_INSTANCE;

typedef struct _CMOCK_IO_Write_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  ioAddress Expected_offset;
  ioData Expected_data;

} CMOCK_IO_Write_CALL_INSTANCE;

static struct MockIOInstance
{
  CMOCK_MEM_INDEX_TYPE IO_Read_CallInstance;
  CMOCK_MEM_INDEX_TYPE IO_Write_CallInstance;
} Mock;

extern jmp_buf AbortFrame;

void MockIO_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_MEM_INDEX_TYPE call_instance;
  call_instance = Mock.IO_Read_CallInstance;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_IO_Read);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  call_instance = Mock.IO_Write_CallInstance;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_IO_Write);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
}

void MockIO_Init(void)
{
  MockIO_Destroy();
}

void MockIO_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
}

ioData IO_Read(ioAddress offset)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_IO_Read_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_IO_Read);
  cmock_call_instance = (CMOCK_IO_Read_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.IO_Read_CallInstance);
  Mock.IO_Read_CallInstance = CMock_Guts_MemNext(Mock.IO_Read_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_IO_Read,CMockString_offset);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_offset), (void*)(&offset), sizeof(ioAddress), cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_IO_Read(CMOCK_IO_Read_CALL_INSTANCE* cmock_call_instance, ioAddress offset);
void CMockExpectParameters_IO_Read(CMOCK_IO_Read_CALL_INSTANCE* cmock_call_instance, ioAddress offset)
{
  memcpy((void*)(&cmock_call_instance->Expected_offset), (void*)(&offset),
         sizeof(ioAddress[sizeof(offset) == sizeof(ioAddress) ? 1 : -1])); /* add ioAddress to :treat_as_array if this causes an error */
}

void IO_Read_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, ioAddress offset, ioData cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_IO_Read_CALL_INSTANCE));
  CMOCK_IO_Read_CALL_INSTANCE* cmock_call_instance = (CMOCK_IO_Read_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.IO_Read_CallInstance = CMock_Guts_MemChain(Mock.IO_Read_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_IO_Read(cmock_call_instance, offset);
  memcpy((void*)(&cmock_call_instance->ReturnVal), (void*)(&cmock_to_return),
         sizeof(ioData[sizeof(cmock_to_return) == sizeof(ioData) ? 1 : -1])); /* add ioData to :treat_as_array if this causes an error */
}

void IO_Write(ioAddress offset, ioData data)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_IO_Write_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_IO_Write);
  cmock_call_instance = (CMOCK_IO_Write_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.IO_Write_CallInstance);
  Mock.IO_Write_CallInstance = CMock_Guts_MemNext(Mock.IO_Write_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_IO_Write,CMockString_offset);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_offset), (void*)(&offset), sizeof(ioAddress), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_IO_Write,CMockString_data);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_data), (void*)(&data), sizeof(ioData), cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
}

void CMockExpectParameters_IO_Write(CMOCK_IO_Write_CALL_INSTANCE* cmock_call_instance, ioAddress offset, ioData data);
void CMockExpectParameters_IO_Write(CMOCK_IO_Write_CALL_INSTANCE* cmock_call_instance, ioAddress offset, ioData data)
{
  memcpy((void*)(&cmock_call_instance->Expected_offset), (void*)(&offset),
         sizeof(ioAddress[sizeof(offset) == sizeof(ioAddress) ? 1 : -1])); /* add ioAddress to :treat_as_array if this causes an error */
  memcpy((void*)(&cmock_call_instance->Expected_data), (void*)(&data),
         sizeof(ioData[sizeof(data) == sizeof(ioData) ? 1 : -1])); /* add ioData to :treat_as_array if this causes an error */
}

void IO_Write_CMockExpect(UNITY_LINE_TYPE cmock_line, ioAddress offset, ioData data)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_IO_Write_CALL_INSTANCE));
  CMOCK_IO_Write_CALL_INSTANCE* cmock_call_instance = (CMOCK_IO_Write_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.IO_Write_CallInstance = CMock_Guts_MemChain(Mock.IO_Write_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_IO_Write(cmock_call_instance, offset, data);
}

