#include <stdio.h>
#include <libdragon.h>

int main(void) {
    /* Initialize video (320x240, 32-bit color) and controllers */
    display_init(RESOLUTION_320x240, DEPTH_32_BPP, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);
    controller_init();
    
    // Game variables
    int player_y = 100;
    int ball_x = 160;
    int ball_y = 120;
    int ball_dx = 3;
    int ball_dy = 3;

    while(1) {
        /* Read controller input */
        controller_scan();
        struct controller_data keys = get_keys_held();

        /* Move player paddle with D-Pad or Analog Stick */
        if (keys.c[0].up || keys.c[0].y > 20) {
            player_y -= 5;
        }
        if (keys.c[0].down || keys.c[0].y < -20) {
            player_y += 5;
        }

        /* Clamp paddle to screen bounds */
        if (player_y < 0) player_y = 0;
        if (player_y > 240 - 40) player_y = 240 - 40;

        /* Move the ball */
        ball_x += ball_dx;
        ball_y += ball_dy;

        /* Ball collision: Top and Bottom walls */
        if (ball_y <= 0 || ball_y >= 240 - 10) {
            ball_dy = -ball_dy;
        }

        /* Ball collision: Right wall (bounce back) */
        if (ball_x >= 320 - 10) {
            ball_dx = -ball_dx;
        }

        /* Ball collision: Player Paddle */
        if (ball_x <= 30 && ball_x >= 20 && ball_y + 10 >= player_y && ball_y <= player_y + 40) {
            ball_dx = -ball_dx;
            
            /* Speed up the ball slightly to increase difficulty */
            if (ball_dx < 0) ball_dx -= 1; else ball_dx += 1;
        }

        /* Lose condition: Ball passes the left screen edge */
        if (ball_x < 0) {
            ball_x = 160;
            ball_y = 120;
            ball_dx = 3; /* Reset speed */
        }

        /* Grab a render buffer from the N64 */
        display_context_t disp = display_get();
        
        /* Clear screen to black */
        graphics_fill_screen(disp, 0x000000FF);
        
        /* Draw Player Paddle (White) at X=20 */
        graphics_draw_box(disp, 20, player_y, 10, 40, 0xFFFFFFFF);
        
        /* Draw Ball (Red) */
        graphics_draw_box(disp, ball_x, ball_y, 10, 10, 0xFF0000FF);

        /* Push buffer to the screen */
        display_show(disp);
    }
    return 0;
}