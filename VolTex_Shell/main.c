/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
#include <poll.h>
#include <syslog.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "functions.h"
#include "rm.h"
#include "cat.h"
#include "ls.h"
#include "cd.h"
#include "tree.h"
#include "job_struct.h"
//#include "bg.h"
#include "calc.h"
#include "grep.h"
#include "hostname.h"
#include "alias.h"
#include "echo.h"
#include "redirection.h"
#include "pipe.h"
#include "env.h"
#include "tic_tac_toe.h"
#include "invader.h"
#include "history.h"*/

#include "headers.h"

struct utsname uinfo;
job back[100];
int back_count = 0, shellid = 0, childpid = 0;
job fore;
char color[10];
const char **commands = NULL;
const char **default_commands = NULL;
/////////////////////////////////////////////////
void populateMenu()
{
  static const char *items[] = {"pwd", "help", "mkdir", "touch", "mv", "rmdir",
                                "color", "clear", "tree", "rm", "cat", "ls",
                                "cd", "echo", "bg", "sleep", "job", "grep",
                                "calc", "hostname", "alias", "exit", "setenv", "unsetenv",
                                "tictactoe", "invader", "history"};

  static const char *def_items[] = {"pwd", "help", "mkdir", "touch", "mv", "rmdir",
                                    "color", "clear", "tree", "rm", "cat", "ls",
                                    "cd", "echo", "bg", "sleep", "job", "grep",
                                    "calc", "hostname", "alias", "exit", "setenv", "unsetenv",
                                    "tictactoe", "invader", "history"};

  commands = items;
  default_commands = def_items;
}

int check_redirection(char *token)
{
  int i;
  int l = strlen(token);

  for (i = 0; i < l; i++)
  {
    if (token[i] == '<' || (token[i] == '>' && token[i + 1] != '>'))
      return 2;
    if (token[i] == '>' && token[i + 1] == '>')
      return 3;
  }
  return 0;
}

int check_pipe(char *token)
{
  int i;
  int l = strlen(token);
  for (i = 0; i < l; i++)
  {
    if (token[i] == '|')
      return 1;
  }
  return 0;
}

/////////////////////////
void child_sig()
{
  pid_t pid;
  int x;
  pid = waitpid(WAIT_ANY, &x, WNOHANG);
  int i;
  for (i = 1; i <= back_count; i++)
  {
    if (back[i].pid == pid)
    {
      int exit_status = WEXITSTATUS(x);
      if (exit_status == 0)
        printf("\n%s with pid %d exited normally\n", back[i].name, back[i].pid);
      else
        printf("\n%s with pid %d exited with exit status %d\n", back[i].name, back[i].pid, exit_status);

      fflush(stdout);
      break;
    }
  }
  signal(SIGCHLD, child_sig);
}

void ctrl_c()
{
  pid_t p = getpid();
  if (p != shellid)
    return;
  if (childpid != -1)
    kill(childpid, SIGINT);
  signal(SIGINT, ctrl_c);
}

void ctrl_z()
{
  pid_t p = getpid();
  if (p != shellid)
    return;

  if (childpid != -1)
  {
    kill(childpid, SIGTTIN);
    kill(childpid, SIGTSTP);
    back_count++;
    back[back_count].pid = childpid;
    back[back_count].is_back = 1;
    strcpy(back[back_count].name, fore.name);
  }
  signal(SIGTSTP, ctrl_z);
}

void red()
{
  // printf("\033[0;31m");
  printf("\033[0;31m");
}
void yellow()
{
  printf("\033[0;33m");
}

void blue()
{
  printf("\033[0;34m");
}

void purple()
{
  printf("\033[0;35m");
}

void cyan()
{
  printf("\033[0;36m");
}

void green()
{
  printf("\033[0;32m");
}

void change_color(char *c)
{
  strcpy(color, c);
}
void reset()
{
  printf("\033[0m");
}

void prompt()
{
  static int f_time = 1;
  if (f_time)
  {
    const char *screen_clear = " \e[1;1H\e[2J";
    if (write(STDOUT_FILENO, screen_clear, 12) == -1)
    {
      fprintf(stderr, "Error while clearing the screen");
      return;
    }
    f_time = 0;
  }
  yellow();
  printf("<Vol-Tex-Sh:>~ ");
  if (strcmp(color, "yellow") == 0)
  {
    yellow();
  }
  else if (strcmp(color, "purple") == 0)
  {
    purple();
  }
  else if (strcmp(color, "blue") == 0)
  {
    blue();
  }
  else if (strcmp(color, "red") == 0)
  {
    red();
  }
  else if (strcmp(color, "green") == 0)
  {
    green();
  }
  else
  {
    cyan();
  }

  char *path = pwd(1);
  printf("%s", path);
  reset();
}

char **create_tokens(int *index, char *command, int *nb_par)
{
  char *token = strtok(command, " \n\t\r");
  char **parameters = parameterArr();
  int i = 0;
  while (token != NULL)
  {
    strcpy(parameters[i++], token);
    token = strtok(NULL, " \n\t\r");
  }
  *nb_par = i;
  my_add_history(*index, command);
  (*index)++;
  return parameters;
}

char **parameterArr()
{
  char **parameters = malloc(200 * sizeof(char *));
  for (size_t i = 0; i < 200; i++)
    parameters[i] = calloc(100, sizeof(char));
  return parameters;
}

void freeParameters(char **parameters)
{
  for (size_t i = 0; i < 200; i++)
    free(parameters[i]);
  free(parameters);
}

int main()
{
  // int errno = 0;
  if (uname(&uinfo) != 0)
  {
    perror("uname");
    exit(EXIT_FAILURE);
  }

  shellid = getpid();
  populateMenu();
  signal(SIGCHLD, SIG_IGN);
  signal(SIGCHLD, child_sig);
  signal(SIGINT, ctrl_c);
  signal(SIGTSTP, ctrl_z);
  prompt(color);

  int index = 0;

  while (1)
  {
    childpid = -1;
    char *token_arr[200];
    char *line = readline("$~ ");
    if (strcmp(line, "\n") == 0)
    {
      prompt();
      continue;
    }
    int i = 0, j = 0;
    token_arr[j] = strtok(line, ";");
    while (token_arr[j] != NULL)
    {
      j++;
      token_arr[j] = strtok(NULL, ";");
    }

    for (i = 0; i < j; i++)
    {
      char **tokens;
      int nb_par = 0;

      int c = check_pipe(token_arr[i]);
      if (c == 1)
      {
        execute_pipe(token_arr[i]);
        continue;
      }
      c = check_redirection(token_arr[i]);
      if (c == 2 || c == 3)
      {
        redirection(token_arr[i], c - 2);
        continue;
      }
      tokens = create_tokens(&index, token_arr[i], &nb_par);
      if (tokens == NULL)
        continue;
      int execVal = exec(tokens, &nb_par);
      if (execVal == 1)
        foreground(tokens, nb_par);
      freeParameters(tokens);
    }
    prompt();
  }
  return 0;
}
