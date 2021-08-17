/* See LICENSE file for copyright and license details. */
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "../util.h"

#if defined(CLOCK_BOOTTIME)
	#define UPTIME_FLAG CLOCK_BOOTTIME
#elif defined(CLOCK_UPTIME)
	#define UPTIME_FLAG CLOCK_UPTIME
#else
	#define UPTIME_FLAG CLOCK_MONOTONIC
#endif

const char *
uptime(void)
{
	char warn_buf[256];
	uintmax_t d, h, m;
	struct timespec uptime;

	if (clock_gettime(UPTIME_FLAG, &uptime) < 0) {
		snprintf(warn_buf, 256, "clock_gettime %d", UPTIME_FLAG);
		warn(warn_buf);
		return NULL;
	}

	if(uptime.tv_sec / 3600 >= 24) {
		d = floor(uptime.tv_sec / 3600 / 24);
		h = (uptime.tv_sec / 3600) - d * 24;

		return bprintf("%jud %juh", d, h);
	} else {
		h = uptime.tv_sec / 3600;
		m = uptime.tv_sec % 3600 / 60;
	}
	return bprintf("%juh %jum", h, m);
}
