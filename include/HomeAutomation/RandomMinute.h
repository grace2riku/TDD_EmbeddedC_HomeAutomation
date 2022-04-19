#ifndef D_RandomMinute_H
#define D_RandomMinute_H

/**********************************************************
 *
 * RandomMinute is responsible for ...
 *
 **********************************************************/

void RandomMinute_Create(int bound);
void RandomMinute_Destroy(void);

extern int (*RandomMinute_Get)(void);
//int RandomMinute_Get(void);

#endif  /* D_FakeRandomMinute_H */
