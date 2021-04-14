
#if 1
void RandomMinute_Create(int bound);
extern int (*RandomMinute_Get)(void);
#else
void RandomMinute_Create(int bound);
int RandomMinute_Get(void);
#endif 