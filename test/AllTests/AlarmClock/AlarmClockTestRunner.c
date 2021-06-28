#if UNIT_TEST
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(AlarmClock)
{
    RUN_TEST_CASE(AlarmClock, clearAllAlarmOnCreate);
    RUN_TEST_CASE(AlarmClock, addOneAlarm);
    RUN_TEST_CASE(AlarmClock, clearAlarmCntOnCreate);
    RUN_TEST_CASE(AlarmClock, addMoreThanOneAlarm);
    RUN_TEST_CASE(AlarmClock, fullAlarmList);
    RUN_TEST_CASE(AlarmClock, setAlarmIDNotExist);
    RUN_TEST_CASE(AlarmClock, setAlarmIDValidId);
    RUN_TEST_CASE(AlarmClock, isNotTimeYet);
    RUN_TEST_CASE(AlarmClock, createNullPointerCallback);
    RUN_TEST_CASE(AlarmClock, wakeUpBeforeSetAlarm);
    RUN_TEST_CASE(AlarmClock, isTime);
    RUN_TEST_CASE(AlarmClock, timePast);
    RUN_TEST_CASE(AlarmClock, destroyAlarm);
    RUN_TEST_CASE(AlarmClock, useFirstAvailableIdxAlarmAfterDestroyAlarm);
    RUN_TEST_CASE(AlarmClock, disableAlarm);
}
#endif