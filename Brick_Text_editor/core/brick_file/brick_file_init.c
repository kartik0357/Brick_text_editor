#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <brick_file_init.h>

void editorAppendRow(struct brick_win_size *win,char *line, size_t linelen)
{
	int row = win->data_row;
	win->container = realloc(win->container, sizeof(row_container) * (win->data_row +1));	
	win->container[row].data = malloc(linelen + 1);
	
	char *str  = win->container[row].data;
	memcpy(str,line,linelen);
	str[linelen] = '\0';
	win->container[row].size = linelen;
	
	win->data_row++;
	
}

void brick_open_file(struct brick_win_size *win,char *filename)
{
	  FILE *fp = fopen(filename, "r");
	  if (!fp) 
		  die("fopen");
	  char *line = NULL;
	  size_t linecap = 0;
	  ssize_t linelen;
	  while ((linelen = getline(&line, &linecap, fp)) != -1) {
		while (linelen > 0 && (line[linelen - 1] == '\n' || line[linelen - 1] == '\r'))
			linelen--;
		editorAppendRow(win,line, linelen);
	  }
	  free(line);
	  fclose(fp);
}
