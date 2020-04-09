#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <brick_file_init.h>

void editorAppendRow(struct brick_win_size *win,char *line, size_t linelen)
{
	int row = win->data_row;
	
	if(linelen > win->col)
	{
		int off = 0;
		int tmp_len = linelen;
		while(tmp_len > win->col)
		{
			win->container = realloc(win->container, sizeof(row_container) * (row+1));
			win->container[row].data = malloc(win->col);
			
			char *str  = win->container[row].data;
			memcpy(str,(line+off),win->col);
			
			off = off + win->col;
			tmp_len -= win->col;
			
			win->container[row].size = win->col;
			row++;
		}
		if(tmp_len > 0)
		{
			win->container = realloc(win->container, sizeof(row_container) * (row+1));
			win->container[row].data = malloc(tmp_len);
			
			char *str  = win->container[row].data;
			memcpy(str,(line+off),tmp_len);
			
			win->container[row].size = tmp_len;
			row++;
		}
	}
	else
	{
		win->container = realloc(win->container, sizeof(row_container) * (row+1));	
		win->container[row].data = malloc(linelen + 1);
		
		char *str  = win->container[row].data;
		memcpy(str,line,linelen);
		str[linelen] = '\0';
		
		win->container[row].size = linelen;
		row++;
	}
	
	win->data_row = row;
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
