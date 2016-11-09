#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <err.h>
#include <sysexits.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

extern char **environ;

int t(int hour, int min);

/*
  Returns an integer representing the amount of time (in seconds) until
  hour:min. Input must be in military time: hour (0-23).
*/
int t(int hour, int min)
{
  int h, m, s;
  time_t tt;
  struct tm *t1;

  tt = time(0);
  t1 = (localtime) (&tt);

  h = t1->tm_hour;
  m = t1->tm_min;
  s = t1->tm_sec;

  if (hour >= h)
    h = hour - h;
  else
    h = (24 - h) + hour - 1;

  if (min > m)
    m = min - m - 1;
  else
    m = abs((60 - min) - m) - 1;

  s = 60 - s;

  return ((h*3600) + (m*60) + s);

}

int main(void)
{
  pid_t child_pid;
  int status;

  child_pid= fork();

  if (child_pid > 0)
  {

    /* Sleeps until 10:30 AM. */
    sleep(t(10,30));

    kill(child_pid, SIGTERM);
    main();
  }
  else
    if (child_pid == 0)
    {
      /* Insert directory where 'alarm' files are located for /Users/zach/Documents/Music. */
      execle("/usr/local/bin/castnow", "castnow", "/Users/zach/Documents/Music",
      "&", NULL, environ);
    }
    else
      err(EX_OSERR, "fork error");

  return 0;
}
