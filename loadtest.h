#ifndef __LOADTEST_H__
#define __LOADTEST_H__

/* load loop, this schould take about 1 to 2ms to complete */
#define ROUNDS(x) {unsigned int rcnt;			       \
		for (rcnt = 0; rcnt < x*1000; rcnt++) { \
			(void)(((pow(rcnt, rcnt) * \
				      sqrt(rcnt*7230970)) * 7230716) * \
				      atan2(rcnt, rcnt));	       \
		} }							\


#define _DEBUG 0  /* Make _DEBUG to 1 to turn on debug statements */

void startLoadTest(config configParams);

#endif /* __LOADTEST_H__ */

