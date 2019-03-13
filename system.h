/*  cpufreq-bench CPUFreq microbenchmark
 */
#ifndef __SYSTEM_H__
#define __SYSTEM_H__

/* initial loop count for the load calibration */
#define GAUGECOUNT	1500

/* default scheduling policy SCHED_OTHER */
#define SCHEDULER	SCHED_OTHER

#define PRIORITY_DEFAULT 0
#define PRIORITY_HIGH	 sched_get_priority_max(SCHEDULER)
#define PRIORITY_LOW	 sched_get_priority_min(SCHEDULER)

#define PATH_TO_CPU "/sys/devices/system/cpu/"
#define SYSFS_PATH_MAX 255

typedef struct _config
{
    long loadTime;        /* load time in µs */
    long sleepTime;       /* sleep time in µs */

    int cycles;  /* calculation cycles with the same sleep/load time */
    int rounds;  /* calculation rounds with iterated sleep/load time */

    int minCpuLoad;
    int maxCpuLoad;
    int nlogLevel;
    int nlogMode;
}config;


long long getTime();

int sysfsModifyFreqPolicyGovernor(unsigned int cpu, char *governor);
int cpufreqModifyPolicyGovernor(unsigned int cpu, char *governor);

int setCpufreqGovernor(char *governor, unsigned int cpu);

void prepareUser(config configParams);
int prepareSystem();

#endif /* __SYSTEM_H__ */

