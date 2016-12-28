#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <err.h>
#include <sysexits.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

/* Compile with -DDEBUG flag after gcc to print and not cast */

extern char **environ;

int main(int argc, char *argv[])
{
  pid_t child_pid;
  int status;

  time_t tt;
  struct tm *t1;

  child_pid= fork();

  if (child_pid > 0)
  {

    tt = time(0);
    t1 = (localtime) (&tt);

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
    {
      #ifdef DEBUG
        printf("Casting now @ %d : %02d : %02d\n", t1->tm_hour, t1->tm_min, t1->tm_sec);
      #else
        execle("/usr/local/bin/castnow", "castnow", argv[1], "&", NULL, environ);
      #endif
    }
    else
      err(EX_OSERR, "fork error");

  return 0;
}
