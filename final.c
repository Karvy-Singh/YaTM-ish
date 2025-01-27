
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <stdbool.h>
#include "parser.h"
#include "resize.h"

//--------------------------------------------------------------------
// Helper function to draw a filled rectangle with a border
//--------------------------------------------------------------------
static void drawStyledRect(SDL_Renderer *rend, SDL_Rect *rect,
                           SDL_Color fillColor, SDL_Color borderColor) 
{
    // Fill
    SDL_SetRenderDrawColor(rend, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    SDL_RenderFillRect(rend, rect);

    // Border
    SDL_SetRenderDrawColor(rend, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(rend, rect);
}

//--------------------------------------------------------------------
// Handle keyboard events
//--------------------------------------------------------------------
void handleKeyboardInput(int c, int id[], SDL_Event *event, int *close, int width, int height) 
{
    switch (c) {
        case 3: {
            switch (event->key.keysym.sym) {
                case SDLK_1:
                    printf("Pressed 1\n");
                    *close = 1;
                    resize(id[0], 0, 0, width/2, height);
                    resize(id[1], width/2, 0, width/2, height);
                    break;
                case SDLK_2:
                    printf("Pressed 2\n");
                    *close = 1;
                    resize(id[1], 0, 0, width/2, height);
                    resize(id[2], width/2, 0, width/2, height);
                    break;
                case SDLK_3:
                    printf("Pressed 3\n");
                    *close = 1;
                    resize(id[0], 0, 0, width/2, height);
                    resize(id[2], width/2, 0, width/2, height);
                    break;
                case SDLK_4:
                    printf("Pressed 4\n");
                    *close = 1;
                    resize(id[0], 0, 0, width/2, height/2);
                    resize(id[2], width/2, 0, width/2, height/2);
                    resize(id[1], 0, height/2, width, height/2);
                    break;
                default:
                    break;
            }
            break; // Important: break out of case c=3
        }
        case 2: {
            switch (event->key.keysym.sym) {
                case SDLK_1:
                    printf("Pressed 1\n");
                    *close = 1;
                    resize(id[0], 0, 0, width/2, height);
                    resize(id[1], width/2, 0, width/2, height);
                    break;
                case SDLK_2:
                    printf("Pressed 2\n");
                    *close = 1;
                    resize(id[0], 0, 0, width, height/2);
                    resize(id[1], 0, height/2, width, height/2);
                    break;
                default:
                    break;
            }
            break; // break out of case c=2
        }
        default:
            break;
    }
}

//--------------------------------------------------------------------
// Insert text with simple word wrapping
// We now pass in an already-opened TTF_Font to avoid repeated opens.
//--------------------------------------------------------------------
int insert_text(int m, TTF_Font *font, const char *text,
                SDL_Rect *rect, SDL_Renderer *rend) 
{
    if (!text || !*text) {
        return 0; // No string to render
    }

    // Choose font color
    SDL_Color textColor = {255, 255, 255, 255};  // White color

    // Maximum width for text wrapping
    int maxWidth = m * rect->w; 
    // Start rendering below the rectangle
    int x = rect->x;           
    int y = rect->y + rect->h + 10; 

    char lineBuffer[1024]; 
    const char *currentPos = text;

    while (*currentPos) {
        int lineLength = 0;
        int lastValidLength = 0;

        // Try to fit as much text as possible within maxWidth
        while (currentPos[lineLength] && lineLength < (int)sizeof(lineBuffer) - 1) {
            lineBuffer[lineLength] = currentPos[lineLength];
            lineBuffer[lineLength + 1] = '\0'; // Null-terminate

            // Check if the current line fits within the maxWidth
            int textWidth;
            TTF_SizeText(font, lineBuffer, &textWidth, NULL);
            if (textWidth <= maxWidth) {
                lastValidLength = lineLength + 1;
            } else {
                break; // Exceeded maxWidth
            }
            lineLength++;
        }

        // If no valid line could fit, forcefully split
        if (lastValidLength == 0) {
            lastValidLength = lineLength;
        }

        // Render the valid portion
        strncpy(lineBuffer, currentPos, (size_t)lastValidLength);
        lineBuffer[lastValidLength] = '\0';

        SDL_Surface *textSurface = TTF_RenderText_Blended(font, lineBuffer, textColor);
        if (!textSurface) {
            printf("TTF_RenderText_Blended failed: %s\n", TTF_GetError());
            return 1;
        }

        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(rend, textSurface);
        if (!textTexture) {
            printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
            SDL_FreeSurface(textSurface);
            return 1;
        }

        SDL_Rect trect = {
            .x = x,
            .y = y,
            .w = textSurface->w,
            .h = textSurface->h
        };
        SDL_RenderCopy(rend, textTexture, NULL, &trect);

        // Clean up
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);

        // Move to the next line
        y += trect.h + 5; 
        currentPos += lastValidLength;

        // Skip leading spaces for the next line
        while (*currentPos == ' ') {
            currentPos++;
        }
    }

    return 0;
}

//--------------------------------------------------------------------
// Main
//--------------------------------------------------------------------
int main() 
{
    // 1) Retrieve top 3 windows
    char *array[3] = {0};
    int ids[3]     = {0};

    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        printf("Unable to open X display\n");
        return 1;
    }

    int screen = DefaultScreen(display);
    int width  = DisplayWidth(display, screen);
    int height = DisplayHeight(display, screen);

    top_used_windows(array, ids);

    // 2) Count how many valid (non-null) entries we have
    int c = 0;
    for (int i = 0; i < 3; i++) {
        if (array[i]) {
            c++;
        }
    }

    // Print for debugging
    printf("Top %d Used Windows:\n", c);
    for (int i = 0; i < c; i++) {
        printf("  %s (ID: %d)\n", array[i], ids[i]);
    }

    // 3) Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    // 3.5) Initialize TTF once (instead of in insert_text)
    if (TTF_Init() == -1) {
        printf("TTF_Init failed: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Open a font once (re-used for all text renderings)
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/TTF/TSCu_Times.ttf", 16);
    if (!font) {
        printf("Error loading font: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // If you want a bigger window when c=3 for "good symmetry"
    int window_w = 640;
    int window_h = 280;
    if (c == 3) {
        window_w = 640;
        window_h = 600;
    }

    SDL_Window *win = SDL_CreateWindow("Tiling Manager",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       window_w,
                                       window_h,
                                       0);
    if (!win) {
        printf("Error creating window: %s\n", SDL_GetError());
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // 4) Load background image
    SDL_Surface* surface = IMG_Load("black-screen_39.png");
    if (!surface) {
        printf("Error loading surface: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if (!tex) {
        printf("Error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // 5) Clear and draw background
    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, tex, NULL, NULL);

    // 6) Define rectangles
    SDL_Rect rect1  = {50,  10, 100, 200};
    SDL_Rect rect2  = {rect1.x + rect1.w + 10,    10, 100, 200};
    SDL_Rect rect3  = {rect2.x + rect2.w + 120,   10, 100, 200};
    SDL_Rect rect4  = {rect3.x + rect3.w + 10,    10, 100, 200};
    SDL_Rect rect5  = {rect2.x + rect2.w + 120,   10, 200, 100};
    SDL_Rect rect6  = {rect5.x, rect5.y + rect5.h + 10, 200, 100};
    SDL_Rect rect7  = {rect1.x, rect1.y + rect1.h + 70, 100, 200};
    SDL_Rect rect8  = {rect7.x + rect7.w + 10, rect7.y, 100, 200};
    SDL_Rect rect9  = {rect8.x + rect8.w + 120, rect8.y, 100, 100};
    SDL_Rect rect10 = {rect9.x + rect9.w + 10,   rect9.y, 100, 100};
    SDL_Rect rect11 = {rect9.x, rect9.y + rect9.h + 10, 210, 100};

    // Pre-fill lines
    char line1[256] = "";
    char line2[256] = "";
    char line3[256] = "";
    char line4[256] = "";

    // 7) Draw rectangles + text if c=3
    if (c == 3) {
        // Fill+Border style: gray fill, white border
        SDL_Color fillColor   = {50,  50,  50,  255};
        SDL_Color borderColor = {255, 255, 255, 255};

        drawStyledRect(rend, &rect1,  fillColor, borderColor);
        drawStyledRect(rend, &rect2,  fillColor, borderColor);
        drawStyledRect(rend, &rect3,  fillColor, borderColor);
        drawStyledRect(rend, &rect4,  fillColor, borderColor);
        drawStyledRect(rend, &rect7,  fillColor, borderColor);
        drawStyledRect(rend, &rect8,  fillColor, borderColor);
        drawStyledRect(rend, &rect9,  fillColor, borderColor);
        drawStyledRect(rend, &rect10, fillColor, borderColor);
        drawStyledRect(rend, &rect11, fillColor, borderColor);

        snprintf(line1, sizeof(line1), "%s & %s", array[0], array[1]);
        snprintf(line2, sizeof(line2), "%s & %s", array[1], array[2]);
        snprintf(line3, sizeof(line3), "%s & %s", array[0], array[2]);
        snprintf(line4, sizeof(line4), "%s & %s & %s", array[0], array[1], array[2]);

        if (line1[0] != '\0' && line2[0] != '\0') {
            insert_text(2, font, line1, &rect1,  rend);
            insert_text(2, font, line2, &rect3,  rend);
            insert_text(2, font, line3, &rect7,  rend);
            insert_text(1, font, line4, &rect11, rend);
        }
    }
    // 8) Draw rectangles + text if c=2
    else if (c == 2) {
        SDL_Color fillColor   = {50,  50,  50,  255};
        SDL_Color borderColor = {255, 255, 255, 255};

        drawStyledRect(rend, &rect1, fillColor, borderColor);
        drawStyledRect(rend, &rect2, fillColor, borderColor);
        drawStyledRect(rend, &rect5, fillColor, borderColor);
        drawStyledRect(rend, &rect6, fillColor, borderColor);

        snprintf(line1, sizeof(line1), "%s & %s", array[0], array[1]);
        snprintf(line2, sizeof(line2), "%s & %s", array[0], array[1]);

        if (line1[0] != '\0' && line2[0] != '\0') {
            insert_text(2, font, line1, &rect1, rend);
            insert_text(1, font, line2, &rect6, rend);
        }
    }

    SDL_RenderPresent(rend);

    // 9) Event loop
    int close = 0;
    while (!close) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                close = 1;
            } else {
                handleKeyboardInput(c, ids, &event, &close, width, height);
            }
        }
    }

    // 10) Cleanup
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    // Close the font and quit TTF
    TTF_CloseFont(font);
    TTF_Quit();

    SDL_Quit();

    // Free your allocated strings
    for (int i = 0; i < 3; i++) {
        if (array[i]) {
            free(array[i]);
        }
    }

    return 0;
}

