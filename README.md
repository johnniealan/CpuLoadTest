# CpuLoadTest
Loadtest will generate the constant load on CPU from user specified minimum CPU load to maximum cpu load in incremental manner. On starting of loadtest, it displays approximate mins for executing load test case. And test starts with user supplied minimum CPU load as expected CPU load. After calibrating CPU with calculated load and sleep time, It will performs CPU intensive calculation for generating the expected CPU load for given number of cycles. After finishing cycles, loadtest calculates new loadtime and sleeptime as per incremental CPU load. Incremental CPU load has been generated from difference of maximum and minimum CPU load divided by rounds. Now test case will produce the new expected CPU load for given cycles and advances to new CPU load until it reaches to maximum CPU load.

How To:
- Use "config" structure specified in system.h file to control cpu load
- Invoke "startLoadTest" function from your application code
