#include <stdint.h>
#include <stdbool.h>

#if UNIT_TEST
#define ALARM_CLOCK_OVERFLOW                                0xFFFFFFFFFFFFFFFF
#define ALARM_CLOCK_LEN                                     10
#endif

typedef void (*fp_alarm_clock_cb_t) (void);

#if UNIT_TEST
typedef enum E_ALARM_STATE
{
    E_ALARM_STATE_AVAILABLE = 0,
    E_ALARM_STATE_CREATED,
    E_ALARM_STATE_DISABLED,
    E_ALARM_STATE_ENABLED,
} E_ALARM_STATE_t;

typedef struct AlarmClockStruct
{
    uint8_t uc_id;
    fp_alarm_clock_cb_t cb;
    uint64_t ull_tick;
    E_ALARM_STATE_t e_state;
    bool b_timeOverFlow;
} s_alarm_clock_t;
#endif


enum{
    ALARM_UNKNOWN_ID                = 0xFF,
    ALARM_CALLBACK_NULL_POINTER     = 0xFE,
    ALARM_INVALID_TICK              = 0xFFFFFFFFFFFFFFFF
};

void AlarmClock_create();
void AlarmClock_destroy();
uint8_t AlarmClock_createAlarm(fp_alarm_clock_cb_t cb);
bool AlarmClock_setAlarm(uint8_t uc_alarmId, uint64_t ull_ms);
void AlarmClock_wakeUp();
void AlarmClock_destroyAlarm(uint8_t uc_alarmId);
void AlarmClock_disableAlarm(uint8_t uc_alarmId);

#if UNIT_TEST
uint8_t * AlarmClockSpy_getList();
uint8_t AlarmClockSpy_getAlarmCnt(void);
#endif