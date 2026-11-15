#ifndef BUILTIN_CMNDS_H
#define BUILTIN_CMNDS_H

int snitch_cd(char **args);
int snitch_help(char **args);
int snitch_exit(char **args);
int snitch_cwd(char **args);
int snitch_num_builtins(void);
int snitch_execute(char **args);
int snitch_clear(char **args);

#endif
