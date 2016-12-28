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

  Issue: When alarm is set to 7:00 am the music is casted again at 8:00 am.
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

  if (hour == h)
    h = 23;
  else if (hour > h)
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

int main(int argc, char *argv[])
{
  pid_t child_pid;
  int status;

  time_t tt;
  struct tm *t1;

  child_pid= fork();

  if (child_pid > 0)
  {

    /* sets time to command line args from python script. */
    /* sleep(t(atoi(argv[2]), atoi(argv[3]))); */

    /*
      make while loop that sleeps for a minute and
      the condition checks the current times hour
      and minute.
    */

    tt = time(0);
    t1 = (localtime) (&tt);

    sleep(60);

    while ((t1->tm_hour != atoi(argv[2])) || (t1->tm_min != atoi(argv[3])))
    {
      sleep(60);
      tt = time(0);
      t1 = (localtime) (&tt);
    }

    kill(child_pid, SIGTERM);
    main(argc, argv);
  }
  else

    tt = time(0);
    t1 = (localtime) (&tt);

    if (child_pid == 0)
      printf("Casting now @ %d : %02d : %02d\n", t1->tm_hour, t1->tm_min, t1->tm_sec);
      //execle("/usr/local/bin/castnow", "castnow", argv[1], "&", NULL, environ);
    else
      err(EX_OSERR, "fork error");

  return 0;
}
