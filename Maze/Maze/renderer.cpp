internal void
clear_screen(u32 color) {
	unsigned int* pixel = (unsigned int*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = color;
		}
	}
}

internal void
draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 color) {
	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);
	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}
}

global_variable float render_scale = 0.01f;


internal void
draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color) {

	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	half_size_x *= render_state.height * render_scale;
	half_size_y *= render_state.height * render_scale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	// Change to pixels
	int x0 = x - half_size_x;
	int x1 = x + half_size_x;
	int y0 = y - half_size_y;
	int y1 = y + half_size_y;

	draw_rect_in_pixels(x0, y0, x1, y1, color);
}


const char* maze[][26] = {
	"######### ###################################",
	"#                                           #",
	"### ############################## ##########",
	"#             .          #                  #",
	"##### ######## ########### ################ #",
	"#       ##      . ##              .         #",
	"##########.##### ### ########################",
	"#                            .              #",
	"#### ################## ############ ########",
	"#                  #         #              #",
	"####.#################### ###################",
	"#                  #                        #",
	"####### ############## ############# ########",
	"#                #         #                #",
	"################## ################### ######",
	"#                                           #",
	"######### ################## ################",
	"#                  ###                      #",
	"###### ####### ####################### ######",
	"#          #       .                        #",
	"######### ##################### #############",
	"#                  #   .                    #",
	"######## ############## ############## ######",
	"#           #        .    #                 #",
	"##################### ######## ##############",
	"#                                           #",
};


const char* maze1[][26] = {
	"######### ###################################",
	"#                                           #",
	"### ############### ############## ##########",
	"#           #            #                  #",
	"##### ######## ############# ############## #",
	"#       ##        ##              .         #",
	"##########.##### ###.########################",
	"#          #               ##.              #",
	"#### ################## ############ ########",
	"#                  #         ####        ####",
	"###### ################## ###################",
	"#        #                     #            #",
	"#######    ################### ##### ########",
	"#       ##                     #            #",
	"####### ############################## ######",
	"#                                           #",
	"######### ################## ################",
	"#                  ###                      #",
	"###### ####### ####################### ######",
	"#          #       .        #     .         #",
	"######### ##################### #############",
	"#                  #   .#           #       #",
	"######## ############## ############## ######",
	"#           #        .    #                 #",
	"###### ############## ########.##############",
	"#                                           #",
};
#define	NUM_EMPTY 9
#define COL 567+NUM_EMPTY

float maze_center_points[2][COL], maze_points_cnt[COL] = { 0 }, emptiness[2][NUM_EMPTY];
int raund2_flag = 0;
int
draw_maze(float x, float y, float size, u32 color1, u32 color2, int round) {

	int cnt1 = 0, cnt2 = 0;
	float half_size = size * .5f;
	const char** a_letters = maze[0];
	if (round == 2) {
		raund2_flag = 1;
		a_letters = maze1[0];
	}
	float original_x = x;


	for (int i = 0; i < 26; i++) {
		const char* row;
		row = a_letters[i];
		while (*row) {
			if (*row == ' ' || *row == '.') {
				draw_rect(x, y, half_size, half_size, color1);
				maze_center_points[0][cnt1] = x;
				maze_center_points[1][cnt1] = y;
				if (*row == '.') {
					draw_rect(x, y, half_size, half_size, color2);
					emptiness[0][cnt2] = x;
					emptiness[1][cnt2] = y;
					cnt2++;
				}
				cnt1++;
			}
			x += size;
			row++;
		}
		y -= size;
		x = original_x;
	}
	return raund2_flag;
}


const char* letters[][7] = {
	" 00",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"000",

	" 000",
	"0",
	"0",
	"0",
	"0",
	"0",
	" 000",

	"000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0",

	" 000",
	"0",
	"0",
	"0 00",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	"000",

	" 000",
	"   0",
	"   0",
	"   0",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0 0",
	"00",
	"0 0",
	"0  0",
	"0  0",

	"0",
	"0",
	"0",
	"0",
	"0",
	"0",
	"0000",

	"00 00",
	"0 0 0",
	"0 0 0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",

	"00  0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0  00",

	"0000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0000",

	" 000",
	"0  0",
	"0  0",
	"000",
	"0",
	"0",
	"0",

	" 000 ",
	"0   0",
	"0   0",
	"0   0",
	"0 0 0",
	"0  0 ",
	" 00 0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"0  0",

	" 000",
	"0",
	"0 ",
	" 00",
	"   0",
	"   0",
	"000 ",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",

	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	" 00",

	"0   0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",
	" 0 0",
	"  0",

	"0   0 ",
	"0   0",
	"0   0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	" 0 0 ",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	" 0 0",
	"0   0",
	"0   0",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	"  0",
	"  0",
	"  0",

	"0000",
	"   0",
	"  0",
	" 0",
	"0",
	"0",
	"0000",

	"",
	"",
	"",
	"",
	"",
	"",
	"0",

	"   0",
	"  0",
	"  0",
	" 0",
	" 0",
	"0",
	"0",
};

internal void
draw_text(const char* text, float x, float y, float size, u32 color) {
	float half_size = size * .5f;
	float original_y = y;

	while (*text) {
		if (*text != 32) {
			const char** letter;
			if (*text == 47) letter = letters[27];
			else if (*text == 46) letter = letters[26];
			else letter = letters[*text - 'A'];
			float original_x = x;

			for (int i = 0; i < 7; i++) {
				const char* row = letter[i];
				while (*row) {
					if (*row == '0') {
						draw_rect(x, y, half_size, half_size, color);
					}
					x += size;
					row++;
				}
				y -= size;
				x = original_x;
			}
		}
		text++;
		x += size * 6.f;
		y = original_y;
	}
}


int
check_centers(float player_x, float player_y) {
	int flag = 0;
	for (int i = 0; i < COL; i++) {
		if (player_x == maze_center_points[0][i] && player_y == maze_center_points[1][i] && maze_points_cnt[i] < 3) {
			maze_points_cnt[i]++;
			flag = 1;
			break;
		}
	}
	return flag;
}

void
check_center_points(float p_x, float p_y) {
	for (int i = 0; i < COL; i++) {
		if (maze_points_cnt[i] == 3)
			draw_rect(maze_center_points[0][i], maze_center_points[1][i], 2.f, 2.f, 0x6495ED);

	}
}

int check_empty(float p_x, float p_y) {
	int flag = 0;
	for (int i = 0; i < NUM_EMPTY; i++) {
		if (p_x == emptiness[0][i] && p_y == emptiness[1][i]) {
			flag = 1;
			break;
		}
	}
	return flag;

}

int final(float player_x, float player_y) {
	int flag = 0;

	if (/*player_x == maze_center_points[0][COL-7] &&*/ player_y == -48/*maze_center_points[1][COL-7]*/) {
		flag = 1;
	}
	return flag;

}



