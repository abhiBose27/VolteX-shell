#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
#include <poll.h>
#include <syslog.h>
#include <ncurses.h>
#include <math.h>
#include <err.h>
#include <regex.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct job
{
	char name[100];
	int pid;
	int is_back;
} job;

extern job back[100];
extern job fore;
extern int back_count;
extern pid_t shellid;
extern pid_t childpid;
extern const char **commands;
extern char color[10];
extern const char **default_commands;

void print_jobs();
void change_color(char *c);
int exec(char **parameters, int *nb_par);
void prompt();
void alias(int nb_par, char **parameters, const char **commands);
void bg(char **tokens, int k);
void calc(int nb_par);
void _cat(int argc, char *argv[]);
void cd(int argc, char *argv[]);
void cmat(int nb_par);
void _echo(char **buff, int k);
void set_env(char **parameters, int nb_par);
void unset_env(char **parameters, int nb_par);
char *pwd(int nb_par);
void create_dir(int nb_par, char **dirname);
void touch(char **filename, int nb_par);
void helppage(int nb_par, char **fns, const char **commands, const char **default_commands);
void mv(int nb_par, char **files);
void remove_dir(int nb_par, char **dirname);
void clean(int nb_par);
void sleep_fun(int nb_par, char **parameters);
int grep(int argc, char **argv);
void compile_pattern(const char *pat);
void process(const char *name, FILE *fp);
void usage(void);
void my_add_history(int index, char *cmd);
int history(int nb_par);
void _ls(int argc, char *argv[]);
void execute_pipe(char *buff);
void redirection(char *buf, int type);
void print_error(char *message, char *filename);
void print_usage();
int isDirExits(const char *path);
void _delete(int argc, char **argv);
void play(int nb_par);
int _tree(int argc, char *argv[]);
void foreground(char **tokens, int nb_par);
int SpaceInvaders(int nb_par);
char **parameterArr();
void get_host_name(int nb_par, char **attributes);

struct player
{
	int r, c;
	char ch;
};

struct alien
{
	int r, c;
	int pr, pc;
	int alive;		/* 1=alive 0=destroyed */
	char direction; /* 'l'=left 'r'=right */
	char ch;
};

struct shoot
{
	int r, c;
	int active; /* 1=active 0=inactive */
	char ch;
};

struct bomb
{
	int r, c;
	int active; /* 1=active 0=inactive */
	int loop;	/* used to prevent alien from flashing when bomb is dropped */
	char ch;
};

struct options
{
	int overall, alien, shots, bombs, bombchance;
};
