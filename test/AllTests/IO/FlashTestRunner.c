#if UNIT_TEST
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Flash)
{
    RUN_TEST_CASE(Flash, WriteSucceeds_ReadyImmediately);
    RUN_TEST_CASE(Flash, SucceedsNotImmediatelyReady);
    RUN_TEST_CASE(Flash, WriteFails_VppError);
    RUN_TEST_CASE(Flash, WriteFails_ProgramError);
    RUN_TEST_CASE(Flash, WriteFails_ProtectedBlockError);
    RUN_TEST_CASE(Flash, WriteFails_FlashUnknownProgramError);
    RUN_TEST_CASE(Flash, WriteFails_FlashReadBackError);
    RUN_TEST_CASE(Flash, WriteSucceeds_IgnoresOtherBitsUntilReady);
    RUN_TEST_CASE(Flash, WriteFails_Timeout);
    RUN_TEST_CASE(Flash, WriteFails_TimeoutAtEndOfTime);
}
#endif