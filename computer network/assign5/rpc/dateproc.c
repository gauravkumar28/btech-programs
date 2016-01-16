#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include "date.h"
/* return the binary date and time */
/* In Linux: long * bindate_1_svc(void* arg1, struct svc_req *arg2) {
*/ 

/* In Dec Unix: long * bindate_1() {
*/

long * bindate_1_svc(char **msg, struct svc_req *req) {
static long timeval; /* must be static */
timeval = time((long *) 0);
return (&timeval);
}
