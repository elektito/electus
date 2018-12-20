#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

static void
handle_sigchld(int sig) {
  int saved_errno = errno;

  /* reap orphaned children. rip. */
  while (waitpid((pid_t)(-1), 0, WNOHANG) > 0) {}

  errno = saved_errno;
}

static int
run_program(const char *path)
{
  pid_t child;
  int ret;
  siginfo_t info;

  child = fork();
  if (child) {
    waitid(P_PID, child, &info, WEXITED);
    return info.si_status;
  } else {
    execl(path, path, NULL);
    printf("Could not run: %s\n", path);
    printf("    %s\n", strerror(errno));
    exit(255);
  }
}

static void
launch_login(void)
{
  if (!fork()) {
    execl("/bin/bash", "/bin/bash", NULL);
  }
}

int
main(int argc, char *argv[])
{
  struct sigaction sa;

  /* register sigchld handler */
  sa.sa_handler = &handle_sigchld;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
  if (sigaction(SIGCHLD, &sa, 0) == -1) {
    printf("Could not install signal handler. Aborting.\n");
    return 1;
  }

  printf("Hello, World!\n");
  printf("This is hello, your friendly init system!\n");

  printf("Attempting to run your rc.local...\n");
  run_program("/etc/rc.local");

  printf("Launching your shell...\n");
  launch_login();

  for (;;) {
    usleep(600 * 1000000);
  }

  return 0;
}
