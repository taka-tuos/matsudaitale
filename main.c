#include <curses.h>
#include <locale.h>
#include <stdlib.h>

WINDOW *fb;

void millisleep(int n)
{
	struct timespec treq, trem;

	treq.tv_sec = (time_t)0;
	treq.tv_nsec = n * 1000 * 1000;
	
	nanosleep(&treq, &trem);
}

void drawbox(WINDOW *win, int x, int y, int w, int h)
{
	mvwvline(win, y        , x        , '|', h);
	mvwvline(win, y        , x + w - 1, '|', h);
	
	mvwhline(win, y        , x        , '-', w);
	mvwhline(win, y + h - 1, x        , '-', w);
	
	mvwaddch(win, y        , x        , '+');
	mvwaddch(win, y + h - 1, x        , '+');
	mvwaddch(win, y        , x + w - 1, '+');
	mvwaddch(win, y + h - 1, x + w - 1, '+');
}

int cursor_button = 0;

void buttoncursor()
{
	move(30-5+2, 5+30*cursor_button+3);
}

char *buttonlist[] = { "FIGHT", "ACT", "ITEM", "MERCY" };

int main()
{
	setlocale(LC_ALL,"");
	
	fb = initscr();
	cbreak();
	noecho();
	nodelay(fb, true);
	keypad(fb, true);
	
	start_color();
	
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);

	for(int i=0;i<4;i++) {
		drawbox(fb, 5+30*i, 30-5+1, 20, 3);
		mvwaddstr(fb, 30-5+2, 5+30*i+6, buttonlist[i]);
	}
	
	//drawbox(fb, 120/2-10, 30/2-5+4, 20, 10); //fight
	
	drawbox(fb, 120/2-55, 30/2-5+4, 110, 10);
	
	mvwaddstr(fb, 30/2-5+4+1, 120/2-55+1, "* おたかんはあなたと添い寝している。");
	attron(COLOR_PAIR(2));
	mvwaddstr(fb, 30/2-5+4+2, 120/2-55+1, "* 今なら楽に殺せそうだ。");
	attroff(COLOR_PAIR(2));
	
	mvwaddstr(fb, 5, 120/2-15, "お　た　か　ん　の　立　ち　絵");
	
	mvwaddstr(fb, 30/2-5+4+10, 120/2-55, "HOTASK LV 19");
	for(int i=0;i<120/2-10-12-5;i++) waddstr(fb, " ");
	attron(COLOR_PAIR(1));
	waddstr(fb, "||||||||||||||");
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(2));
	waddstr(fb, "||||||||");
	attroff(COLOR_PAIR(2));
	
	waddstr(fb, "   ");
	waddstr(fb, "HP 57/94");
	
	wrefresh(fb);
	
	refresh();
	
	buttoncursor();

	while(1) {
		millisleep(20);
		int ch = wgetch(fb);
		
		if(ch != ERR) {
			if(ch == KEY_LEFT || KEY_RIGHT) {
				if(ch == KEY_LEFT) cursor_button--;
				if(ch == KEY_RIGHT) cursor_button++;
				if(cursor_button < 0) cursor_button = 3;
				cursor_button %= 4;
				buttoncursor();
			}
			refresh();
		}
	}

	endwin();
	return 0;
}
