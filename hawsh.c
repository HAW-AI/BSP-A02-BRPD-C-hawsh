#include <stdio.h>
#include <sys/wait.h> // waitpid
#include <unistd.h> // execve
#include <string.h>

#ifndef FALSE
#define FALSE (0)
#define TRUE (!(FALSE))
#endif

void type_prompt()
{
  char buffer[200];
  getcwd(buffer, 200);
  printf("%s", buffer);
  printf(":$ ");
}

int read_command(char *command, char *params)
{
  /* printf("%s", command[0]);*/

  int string_max_laenge = 100;
  char input_string[string_max_laenge + 1];

  if (fgets(input_string, sizeof input_string, stdin) != NULL) {
    // remove trailing newline
    int i;
    int new_length = 0;
    for (i = 0; i < string_max_laenge+1; i++) {
      if (input_string[i] == '\n') {
        input_string[i] = '\0';
        new_length = i;
        break;
      }
    }

    // split on first space into command and params
    char command_from_input[100];
    char params_from_input[100];
    int new_string_index = 0;
    int middle_reached = FALSE;
    for (i = 0; i <= new_length; i++) {
      if (input_string[0] == ' ') {
        printf("Please dont start your command with a space");
        return -1;
      }
      if (input_string[i] == ' ' && !middle_reached)
      {
        middle_reached = TRUE;
        command_from_input[i] = '\0';
        new_string_index = 0;
      }
      if (middle_reached)
      {
        params_from_input[new_string_index] = input_string[i];
        new_string_index++;
      } else {
        command_from_input[new_string_index] = input_string[i];
        new_string_index++;
      }
    }
    // copy the command and params to the command and params
    // field in the main function
    stpcpy(command,command_from_input);
    stpcpy(params,params_from_input);
    return 0;
  } else {
    printf("\nmissing command");
    return -1;
  }
}

void changedir(char *path)
{
  if(path != NULL)
  {
    if(chdir(path) == 0)
    {
      printf("changed directory to %s\n", path);
    }
    else
    {
      printf("an error occured. couldn\'t change directories\n");
    }
  }
  else
  {
    printf("no path provided\n");
  }
}

void get_version()
{
  printf("Version: 0.0.1\n");
}

void quit_shell(int *run)
{
  *run = FALSE;
}

void print_help()
{
  printf("this is the help output\n");
}

int main(int argc, const char *argv[])
{
  int RUN = TRUE;
  char command[100] = "";
  char params[100] = "";

  int PIDstatus = 0;

  while (RUN) {/* Endlosschleife */
    type_prompt(); /* Prompt ausgeben */

    read_command(command, params);  /* Eingabezeile von Tastatur lesen */

    if(!strcmp(command, "quit")) {
      quit_shell(&RUN);
    } else if (!strcmp(command, "version")) {
      get_version();
    } else if (!strcmp(command, "/")) {
      changedir(params);
    } else if (!strcmp(command, "help")) {
      print_help();
    } else {
      /* PIDstatus = fork(); [> Kind erzeugen <]*/
      /* if (PIDstatus < 0) {*/
      /*   printf("Unable to fork"); [> Fehlerbedingung <]*/
      /*   continue; [> Schleife wiederholen <]*/
      /* }*/
      /* if (PIDstatus > 0) {*/
      /*   waitpid (PIDstatus, &status, 0);   [> Elternprozess wartet auf Kind <]*/
      /* } else {*/
      /*   execve(command, params, 0);   [> Das Kind-Programm ausführen <]*/
      /* }*/
      printf("external command\n");
    }
  }
  return 0;
}

