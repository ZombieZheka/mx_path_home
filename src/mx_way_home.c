#include "../inc/way_home.h"

t_cell **mx_create_map(const char *map, t_point *size) {
	size->x = 0;
	size->y = 0;
	for(int i = 0; map[i] != '\n'; i++) {
		if (map[i] == '#' || map[i] == '.')
			size->x++;
	}

	for (int i = 0; map[i] != '\0'; i++) {
		if (map[i] == '\n') {
			size->y++;
		}
	}

	t_cell **arr = (t_cell**) malloc(sizeof(t_cell*) * size->y);
	for (int i = 0; i < size->y; i++) {
		arr[i] = (t_cell*) malloc(sizeof(t_cell) * size->x);
	}

	for (int i = 0, n = 0; i < size->y; i++) {
		for (int j = 0; j < size->x; j++, n++) {
			if (map[n] == ',' || map[n] == '\n')
				n++;
			arr[i][j].isWall = (map[n] == '#') ? true : false;
			arr[i][j].isPath = false;
			arr[i][j].wave = 0;
		}
	}
	return arr;
}

void mx_wave(t_cell **arr, t_point size, int i, int j, t_point end, int step) {
	if (arr[i][j].isWall || (arr[i][j].wave != 0 && arr[i][j].wave < step))
		return;
	arr[i][j].wave = step++;
	if (j > 0)
		mx_wave(arr, size, i, j - 1, end, step);
	if (i < size.y - 1)
		mx_wave(arr, size, i + 1, j, end, step);
	if (j < size.x - 1)
		mx_wave(arr, size, i, j + 1, end, step);
	if (i > 0)
		mx_wave(arr, size, i - 1, j, end, step);
}

int main(int argc, char *argv[]) {
	mx_find_error(argc, argv);

	char *maze = mx_file_to_str(argv[1]);

	t_point size = {0, 0};
	t_point start = {mx_atoi(argv[2]), mx_atoi(argv[3])};
	t_point finish = {mx_atoi(argv[4]), mx_atoi(argv[5])};
	t_cell **arr = mx_create_map(maze, &size);
    int wall = -1;  // стенка
    if (arr[start.y][start.x].wave == wall) {
        mx_printerr("entry point cannot be an obstacle\n");
        exit(-1);
    }
    if (arr[finish.y][finish.x].wave == wall) {
        mx_printerr("exit point cannot be an obstacle\n");
        exit(-1);
    }
	free(maze);
	maze = NULL;

	mx_wave(arr, size, start.x, start.y, finish, 1);

	for (int i = finish.x, j = finish.y; true;) {
		arr[i][j].isPath = true;
		if (arr[i][j].wave == 1)
			break;
		if (j > 0 && arr[i][j - 1].wave == arr[i][j].wave - 1)
			j--;
		else if (i < size.y - 1 && arr[i + 1][j].wave == arr[i][j].wave - 1)
			i++;
		else if (j < size.x - 1 && arr[i][j + 1].wave == arr[i][j].wave - 1)
			j++;
		else if (i > 0 && arr[i - 1][j].wave == arr[i][j].wave - 1)
			i--;
	}
	int max_length = 1;
	for (int i = 0; i < size.y; i++) {
		for (int j = 0; j < size.x; j++) {
			if (arr[i][j].wave > max_length)
				max_length = arr[i][j].wave;
		}
	}
	int file = open("path.txt", O_RDWR | O_CREAT, 0666);
	mx_printstr("dist=");
	mx_printint(max_length - 1);
	mx_printstr("\nexit=");
	mx_printint(arr[finish.x][finish.y].wave - 1);
	mx_printchar('\n');
	for (int i = 0; i < size.y; i++) {
		for (int j = 0; j < size.x; j++) {
			write(file, (arr[i][j].isWall) ? "#"
			: (arr[i][j].wave == max_length) ? "D"
			: (arr[i][j].isPath) ? "*" : ".", 1);
		}
		write(file, "\n", 1);
	}
	close(file);
	for (int i = 0; i < size.y; i++) {
		free(arr[i]);
	}
	free(arr);
	return 0;
}

