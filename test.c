#include <stdio.h>
#include <stdlib.h>

#define WIDTH 40
#define HEIGHT 20

void plot(int x, int y, char canvas[HEIGHT][WIDTH]) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        canvas[y][x] = '#';  // Mark the point with a character
    }
}

void draw_line(int x0, int y0, int x1, int y1, char canvas[HEIGHT][WIDTH]) {
    int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (1) {
		plot(x0, y0, canvas);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}

void print_canvas(char canvas[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", canvas[y][x]);
        }
        printf("\n");
    }
}

void clear_canvas(char canvas[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            canvas[y][x] = '.';
        }
    }
}

int main() {
    char canvas[HEIGHT][WIDTH];
    
    clear_canvas(canvas);  // Initialize the canvas with empty characters
    
    // Define two points (x0, y0) and (x1, y1)
    int x0 = 20, y0 = 5;
    int x1 = 20, y1 = 15;
    
    // Draw the line
    draw_line(x0, y0, x1, y1, canvas);
    
    // Print the result
    print_canvas(canvas);
    
    return 0;
}
