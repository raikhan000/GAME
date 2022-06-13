
#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)
#include<string.h>
//float player_pos_x = 0.f;
//float player_pos_y = 0.f;
int final_cnt = 0; 
float player_x = -52.f, player_y = 48.f;
int flag_menu = 0, final_flag = 0, flag_emptiness = 0;
bool current_gamemode= true;
int flag_won = 0;
int round = 1, round2_flag = 0;
internal void
simulate_game(Input* input, float dt) {
	int button_state = 0;
	//round2_flag = draw_maze(-88, 48, 4, 0x00ffff, 0xffffff, round);
	//round2_flag = draw_maze(-88, 48, 4, 0x00ffff, 0xffffff, round);
	
	if (current_gamemode == true) {
		clear_screen(0x362f67);
		round2_flag = draw_maze(-88, 48, 4, 0x00ffff, 0xffffff, round);

		if (pressed(BUTTON_UP)) { player_y += 4.f; button_state = 1; }
		if (pressed(BUTTON_DOWN)) { player_y -= 4.f; button_state = 2; }
		if (pressed(BUTTON_RIGHT)) {
			player_x += 4.f; button_state = 3;
		}
		if (pressed(BUTTON_LEFT)) {
			player_x -= 4.f; button_state = 4;
		}

		int flag = 0;
		if (pressed(BUTTON_UP) || pressed(BUTTON_DOWN) || pressed(BUTTON_LEFT) || pressed(BUTTON_RIGHT))
			flag = check_centers(player_x, player_y);
		if (flag == 0) {
			switch (button_state) {
			case 1:
				player_y -= 4.f;
				break;
			case 2:
				player_y += 4.f;
				break;
			case 3:
				player_x -= 4.f;
				break;
			case 4:
				player_x += 4.f;
				break;
			}

		}

		check_center_points(player_x, player_y);
		draw_rect(player_x, player_y, 2.f, 2.f, 0x00ff22);

		final_flag = final(player_x, player_y);
		flag_emptiness = check_empty(player_x, player_y);
	
		if (final_flag == 1) {
			current_gamemode = false;
			clear_screen(0x362f67);
			draw_rect(-30, 0, 20, 10, 0x00ff22);
			if (flag_won == 1 && round2_flag == 1) {
				draw_text("GAME OVER", -50, 30, 2, 0xffffff);
				draw_text("RETRY", -35, 0, 0.5, 0xffffff);
				round = 1;
				flag_won = 0;
			}
			else {
				draw_text("YOU  WON", -50, 30, 2, 0xffffff);
				raund2_flag = 0;
				round = 2;
				flag_won = 1;
				draw_text("NEXT ROUND", -45, 0, 0.5, 0xffffff);
			}
			draw_rect(30, 0, 20, 10, 0xffffff);
			draw_text("EXIT", 25, 0, 0.5, 0x00ff22);


		}

		if (flag_emptiness == 1) {
			current_gamemode = false;
			clear_screen(0x362f67);
			draw_text("YOU LOST", -40, 30, 2, 0xffffff);
			draw_rect(-30, 0, 20, 10, 0x00ff22);
			draw_text("RETRY", -35, 0, 0.5, 0xffffff);
			draw_rect(30, 0, 20, 10, 0xffffff);
			draw_text("EXIT", 25, 0, 0.5, 0x00ff22);
			flag_won = 0;
			if (round2_flag == 0) round = 1;
			//final_cnt++;
		}
	}
	else{
		if (pressed(BUTTON_RIGHT)) {
			draw_rect(-30, 0, 20, 10, 0xffffff);
			if (flag_won == 0) {
				draw_text("RETRY", -35, 0, 0.5, 0x00ff22);
			}
			else {
				draw_text("NEXT ROUND", -45, 0, 0.5, 0x00ff22);
				//flag_won = 0;
			}

			draw_rect(30, 0, 20, 10, 0x00ff22);
			draw_text("EXIT", 25, 0, 0.5, 0xffffff);

			flag_menu++;
		}
		if (pressed(BUTTON_LEFT)) {
			draw_rect(-30, 0, 20, 10, 0x00ff22);
			if (flag_won == 0) {
				draw_text("RETRY", -35, 0, 0.5, 0xffffff);
			}
			else
				draw_text("NEXT ROUND", -45, 0, 0.5, 0xffffff);
			draw_rect(30, 0, 20, 10, 0xffffff);
			draw_text("EXIT", 25, 0, 0.5, 0x00ff22);
			flag_menu++;
		}
		if (pressed(BUTTON_RETURN)) {
			if (flag_menu % 2 != 0) {
				running = false;
				
				

			}
			else{

				player_x = -52.f;
				player_y = 48.f;
				current_gamemode = true;
				flag_emptiness = 0;
				for (int i = 0; i < 576; i++) {
					maze_points_cnt[i] = 0;
				}
				final_flag = 0;
				flag_menu = 0;
				round2_flag = 0;

			}

		}
	}
	


	//check_cnt();
}
