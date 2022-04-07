#ifndef LIGHT_CONTROLLER_H_
#define LIGHT_CONTROLLER_H_

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

enum { MAX_LIGHTS = 32 };

void LightController_Create(void);
void LightController_Destroy(void);
void LightController_On(int id);
void LightController_Off(int id);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* LIGHT_CONTROLLER_H_ */