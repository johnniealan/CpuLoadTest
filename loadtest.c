/*
***************************************************************************
*---------------------------------- REVISIONS -----------------------------
* Date        Name        		      Description
* --------    --------------------        ------------------------------
* 05/Jan/15   Johnnie Alan	          Initial Version
***************************************************************************
*/

/*--------------------------- HEADER FILE INCLUDES ----------------------*/
#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include "system.h"
#include "loadtest.h"

/**
 * compute how many rounds of calculation we should do
 * to get the given load time
 *
 * @param load aimed load time in µs
 *
 * @retval rounds of calculation
 **/

unsigned int calculateTimespace(long load, config configParams)
{
    int i;
    long long now, then;
    unsigned int estimated = GAUGECOUNT;
    unsigned int rounds = 0;
    unsigned int timed = 0;
    fprintf(stderr,"calibrating load of %lius, please wait...", load);
    /* get the initial calculation time for a specific number of rounds */
    now = getTime();
    ROUNDS(estimated);
    then = getTime();

    timed = (unsigned int)(then - now);

    /* approximation of the wanted load time by comparing with the
     * initial calculation time */
    for (i = 0; i < 4; i++)
    {
        rounds = (unsigned int)(load * estimated / timed);
        fprintf(stderr,"calibrating with %u rounds", rounds);
        now = getTime();
        ROUNDS(rounds);
        then = getTime();

        timed = (unsigned int)(then - now);
        estimated = rounds;
    }
    fprintf(stderr,"calibration done");
    return estimated;
}

/**
 * loadTest generates a specific load with the performance
 * governor
 *
 * @param config config values for the loadTest
 *
 **/

void startLoadTest(config configParams)
{
    int _round, cycle;
    long long now, then;
    long sleepTime = 0, loadTime = 0;
    long performanceTime = 0;
    unsigned int calculations;
    double cpuLoad = 0;

    sleepTime = configParams.sleepTime;
    loadTime = configParams.loadTime;

    if (configParams.rounds != 0)
    {
        if ((configParams.minCpuLoad >= 0) && (configParams.maxCpuLoad >= 0))
        {
            cpuLoad = (double)(configParams.maxCpuLoad - configParams.minCpuLoad)/(configParams.rounds);
        }
    }

    for (_round = 0; _round <= configParams.rounds ; _round++)
    {
        performanceTime = 0LL;

        sleepTime = (((double)100/((configParams.minCpuLoad +_round * cpuLoad))) -1) * loadTime;
        fprintf(stderr,"Calculated sleepTime is %lu ",sleepTime);
        printf("Expected CPU load is %lf\n",(double)(100 *loadTime)/(loadTime+sleepTime));
        /* set the cpufreq governor to "performance" which disables
         * P-State switching. */
        if (setCpufreqGovernor("performance", 0) != 0)
            return;

        /* calibrate the calculation time. the resulting calculation
         * _rounds should produce a load which matches the configured
         * load time */
        calculations = calculateTimespace(loadTime, configParams);
        fprintf(stderr,"_round %i: doing %u cycles with %u calculations"
                   " for %lius", _round+1, configParams.cycles,
                   calculations, loadTime);

        fprintf(stderr,"avarage: %lius, rps:%li",
                loadTime / calculations,
                1000000 * calculations / loadTime);
        /* do some sleep/load cycles with the performance governor */
        for (cycle = 0; cycle < configParams.cycles; cycle++) {
            now = getTime();
            usleep(sleepTime);
            ROUNDS(calculations);
            then = getTime();
            performanceTime += then - now - sleepTime;
            fprintf(stderr,"performance cycle took %lius, "
                    "sleep: %lius, "
                    "load: %lius, rounds: %u\n",
                    (long)(then - now), sleepTime,
                    loadTime, calculations);
        }
    }
}