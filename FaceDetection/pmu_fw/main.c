#include "pmu_api.h"

//extern volatile int feature_flag;

void pmu_fw_init_user(void)
{
	//feature_flag = 0x8;
}

void pmu_fw_process_loop(void)
{
}

/*called in sleep mode*/
void pmu_fw_process_sleep_loop(void)
{
}

void irq_rtc_callback(void)
{
}

void irq_epir_callback(void)
{
}

void irq_ipir_callback(void)
{
}

void pmu_power_mode_sleep_user_pre(void)
{
}

void pmu_power_mode_sleep_user_post(void)
{
}

