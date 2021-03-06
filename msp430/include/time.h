/*
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)time.h	8.3 (Berkeley) 1/21/94
 */

/*
 * $FreeBSD$
 */

#ifndef _TIME_H_
#define	_TIME_H_

#include <stddef.h>
#include <sys/cdefs.h>
#include <sys/_types.h>

#if 0
/* Frequency of the clock ticks reported by clock().  */
#define	CLOCKS_PER_SEC	128
#endif

#ifndef _CLOCK_T_DECLARED
typedef	_clock_t	clock_t;
#define	_CLOCK_T_DECLARED
#endif

#ifndef _TIME_T_DECLARED
typedef	_time_t	time_t;
#define	_TIME_T_DECLARED
#endif

/*
 * New in POSIX 1003.1b-1993.
 */
#ifndef _CLOCKID_T_DECLARED
typedef	_clockid_t	clockid_t;
#define	_CLOCKID_T_DECLARED
#endif

struct timespec {
	time_t	tv_sec;		/* seconds */
	long	tv_nsec;	/* and nanoseconds */
};

#define TIMEVAL_TO_TIMESPEC(tv, ts)		\
  do {						\
    (ts)->tv_sec = (tv)->tv_sec;		\
    (ts)->tv_nsec = (tv)->tv_usec * 1000;	\
  } while (0)
#define TIMESPEC_TO_TIMEVAL(tv, ts)		\
  do {						\
    (tv)->tv_sec = (ts)->tv_sec;		\
    (tv)->tv_usec = (ts)->tv_nsec / 1000;	\
  } while (0)

/* These macros are also in sys/time.h. */
#if !defined(CLOCK_REALTIME) /* && __POSIX_VISIBLE >= 200112 */
#define CLOCK_REALTIME	0
/* POSIX only specifies CLOCK_REALTIME.  All other clocks are specific
 * to the application, and are supported or not depending on the
 * provider of clock_gettime() and its ilk.  Standard time-related
 * functions below depend on a functional CLOCK_REALTIME which has as
 * its base the POSIX epoch 1970-01-01T00:00:00Z. */
#define CLOCK_ACLK      1
#define CLOCK_SMCLK     2
#define CLOCK_SECOND    3
#define CLOCK_UPTIME    4
/* If your clock_* infrastructure supports other clocks, define
 * constants for them starting with CLOCK_START_APP_CLOCKS_HERE */
#define CLOCK_START_APP_CLOCKS_HERE 20
#endif /* !defined(CLOCK_REALTIME) && __POSIX_VISIBLE >= 200112 */

#if !defined(TIMER_ABSTIME) && __POSIX_VISIBLE >= 200112
#if __BSD_VISIBLE
#define TIMER_RELTIME	0x0	/* relative timer */
#endif
#define TIMER_ABSTIME	0x1	/* absolute timer */
#endif /* !defined(TIMER_ABSTIME) && __POSIX_VISIBLE >= 200112 */

struct tm {
	int	tm_sec;		/* seconds after the minute [0-60] */
	int	tm_min;		/* minutes after the hour [0-59] */
	int	tm_hour;	/* hours since midnight [0-23] */
	int	tm_mday;	/* day of the month [1-31] */
	int	tm_mon;		/* months since January [0-11] */
	int	tm_year;	/* years since 1900 */
	int	tm_wday;	/* days since Sunday [0-6] */
	int	tm_yday;	/* days since January 1 [0-365] */
	int	tm_isdst;	/* Daylight Savings Time flag */
	long	tm_gmtoff;	/* offset from UTC in seconds */
	char	*tm_zone;	/* timezone abbreviation */
};

char *asctime(const struct tm *);
clock_t clock(void);
char *ctime(const time_t *);
double difftime(time_t, time_t);
/* XXX missing: getdate() */
struct tm *gmtime(const time_t *);
struct tm *localtime(const time_t *);
time_t mktime(struct tm *);
size_t strftime(char * __restrict, size_t, const char * __restrict,
    const struct tm * __restrict);
time_t time(time_t *);
#if 0 /* __POSIX_VISIBLE >= 200112 */
#ifndef _TIMER_T_DECLARED
typedef	__timer_t	timer_t;
#define	_TIMER_T_DECLARED
#endif

struct sigevent;
int timer_create(clockid_t, struct sigevent *__restrict, timer_t *__restrict);
int timer_delete(timer_t);
int timer_gettime(timer_t, struct itimerspec *);
int timer_getoverrun(timer_t);
int timer_settime(timer_t, int, const struct itimerspec *__restrict,
	struct itimerspec *__restrict);
#endif

#if 1 /* __POSIX_VISIBLE >= 199309 */
int clock_getres(clockid_t, struct timespec *);
int clock_gettime(clockid_t, struct timespec *);
int clock_settime(clockid_t, const struct timespec *);
#if 0
/* XXX missing: clock_nanosleep() */
int nanosleep(const struct timespec *, struct timespec *);
#endif
#endif /* __POSIX_VISIBLE >= 199309 */

#if 1 /* __POSIX_VISIBLE >= 199506 */
char *asctime_r(const struct tm *, char *);
char *ctime_r(const time_t *, char *);
struct tm *gmtime_r(const time_t *, struct tm *);
struct tm *localtime_r(const time_t *, struct tm *);
#endif

#if __XSI_VISIBLE
char *strptime(const char * __restrict, const char * __restrict,
    struct tm * __restrict);
#endif

#endif /* !_TIME_H_ */
