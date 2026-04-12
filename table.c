#include <stdio.h>
#include <string.h>

#define MAX_STATES 50
#define MAX_TERMINALS 20
#define MAX_NONTERMINALS 20

char terminals[MAX_TERMINALS][20];
char nonterminals[MAX_NONTERMINALS][20];
char action[MAX_STATES][MAX_TERMINALS][20];
char goTo[MAX_STATES][MAX_NONTERMINALS][20];

int state_count = 0;
int t_count = 0;
int nt_count = 0;

int get_terminal_index(char *sym) {
 for(int i=0;i<t_count;i++)
  if(strcmp(terminals[i], sym)==0)
   return i;

 strcpy(terminals[t_count], sym);
 return t_count++;
}

int get_nonterminal_index(char *sym) {
 for(int i=0;i<nt_count;i++)
  if(strcmp(nonterminals[i], sym)==0)
   return i;

 strcpy(nonterminals[nt_count], sym);
 return nt_count++;
}

void initialize_tables() {
 for(int i=0;i<MAX_STATES;i++) {
  for(int j=0;j<MAX_TERMINALS;j++)
   strcpy(action[i][j], "-");
  for(int j=0;j<MAX_NONTERMINALS;j++)
   strcpy(goTo[i][j], "-");
 }
}

int main() {
 FILE *fp = fopen("lalr.output","r");

 if(fp == NULL) {
  printf("Cannot open lalr.output\n");
  return 1;
 }

 initialize_tables();

 char line[256];
 int current_state = -1;

 while(fgets(line,sizeof(line),fp)) {

  if(strncmp(line,"State",5)==0) {
   sscanf(line,"State %d",&current_state);
   if(current_state >= state_count)
    state_count = current_state + 1;
  }

  if(strstr(line,"shift, and go to state")) {
   char sym[50];
   int next_state;
   sscanf(line," %s shift, and go to state %d",sym,&next_state);
   int index = get_terminal_index(sym);
   sprintf(action[current_state][index],"S%d",next_state);
  }

  else if(strstr(line,"go to state")) {
   char sym[50];
   int next_state;
   sscanf(line," %s go to state %d",sym,&next_state);
   int index = get_nonterminal_index(sym);
   sprintf(goTo[current_state][index],"%d",next_state);
  }

  if(strstr(line,"reduce using rule")) {
   int rule;
   sscanf(line," %*s reduce using rule %d",&rule);
   for(int i=0;i<t_count;i++)
    sprintf(action[current_state][i],"R%d",rule);
  }

  if(strstr(line,"accept")) {
   int index = get_terminal_index("$");
   strcpy(action[current_state][index],"ACC");
  }
 }

 fclose(fp);

 printf("\n===== LALR PARSE TABLE =====\n\n");

 printf("State ");
 for(int i=0;i<t_count;i++)
  printf("%-10s",terminals[i]);

 printf("| ");
 for(int i=0;i<nt_count;i++)
  printf("%-6s",nonterminals[i]);

 printf("\n");

 for(int i=0;i<state_count;i++) {
  printf("%-6d",i);

  for(int j=0;j<t_count;j++)
   printf("%-10s",action[i][j]);

  printf("| ");

  for(int j=0;j<nt_count;j++)
   printf("%-6s",goTo[i][j]);

  printf("\n");
 }

 return 0;
}
