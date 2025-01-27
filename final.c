
//   #include <stdio.h>
//   #include <SDL2/SDL.h>
//   #include <SDL2/SDL_timer.h>
//   #include <SDL2/SDL_image.h>
//   #include <SDL2/SDL_ttf.h>
//   #include "parser.h"
//   
//   void handleKeyboardInput(SDL_Event *event, int *close){
//     switch (event->key.keysym.sym) {
//             case SDLK_1:
//                 printf("enetered 1");
//                 *close=1;
//                 break;}
//   }
//   
//   int insert_text(char **arr, SDL_Rect *rect, SDL_Renderer* rend){
//     TTF_Init();
//     SDL_Color textColor = {255, 255, 255, 255};  // White color
//     TTF_Font *font = TTF_OpenFont("/usr/share/fonts/TTF/TSCu_Times.ttf", 24);
//     if (!font) {
//     printf("Error loading font: %s\n", TTF_GetError());
//     return 1;
//     }
//     // Create the text surface
//     printf("%s", arr[0]);
//     SDL_Surface *textSurface = TTF_RenderText_Solid(font, arr[0] , textColor);
//     if (!textSurface) {
//         printf("TTF_RenderText_Blended failed: %s\n", TTF_GetError());
//         return 1;
//     }
//     SDL_Texture *textTexture = SDL_CreateTextureFromSurface(rend, textSurface);
//     SDL_FreeSurface(textSurface);
//   
//     if (!textTexture) {
//         printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
//         return 1;
//     }
//      
//     SDL_Rect trect = {
//           .x = rect->x,
//           .y = rect->y + rect->h + 10, // Position below the rectangle
//           .w = textSurface->w,
//           .h = textSurface->h
//       };
//   
//     SDL_RenderCopy(rend, textTexture, NULL, &trect);
//     SDL_DestroyTexture(textTexture);
//     SDL_RenderPresent(rend);
//     TTF_CloseFont(font);
//   
//   }
//   
//   int main(){
//   
//    char *array[3] = {0}; // Initialize top array
//     int ids[3]={0};
//    top_used_windows(array,ids); 
//   
//    // Print the top 3 used windows
//   int c=0
//    printf("Top 3 Used Windows:\n");
//    for (int i = 0; i < 3; i++) {
//        if (array[i]) {
//             c++;
//            printf("%s  ", array[i]);
//           printf("%d\n",ids[i]);
//            //free(array[i]); // Free allocated memory
//        }
//    }
//        if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
//    {
//        printf("error initializing SDL: %s\n", SDL_GetError());
//        return 1;
//    }
//    
//    SDL_Window* win = SDL_CreateWindow("Hello, CS50!",
//                                       SDL_WINDOWPOS_CENTERED,
//                                       SDL_WINDOWPOS_CENTERED,
//                                       640,480, 0);
//    if (!win)
//    {
//        printf("error creating window: %s\n", SDL_GetError());
//        SDL_Quit();
//      return 1;
//    }
//   
//    Uint32 render_flags= SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
//    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
//   
//     if (!rend)
//     {
//       printf("error creating renderer: %s\n", SDL_GetError());
//       SDL_DestroyWindow(win);
//       SDL_Quit();
//       return 1;
//       }
//   
//     SDL_Surface* surface = IMG_Load("black-screen_39.png");
//     if (!surface)
//     {
//         printf("error creating surface\n");
//         SDL_DestroyRenderer(rend);
//         SDL_DestroyWindow(win);
//         SDL_Quit();
//         return 1;
//     }
//     
//     SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
//     SDL_FreeSurface(surface);
//     if (!tex)
//     {
//         printf("error creating texture: %s\n", SDL_GetError());
//         SDL_DestroyRenderer(rend);
//         SDL_DestroyWindow(win);
//         SDL_Quit();
//         return 1;
//     }
//     
//     
//     SDL_RenderClear(rend);
//     
//     // draw the image to the window
//     SDL_RenderCopy(rend, tex, NULL, NULL);
//     
//     
//     SDL_Rect rect1;
//     rect1.x = 70;
//     rect1.y = 10;
//     rect1.w = 100;
//     rect1.h = 200;
//   
//     SDL_Rect rect2;
//     rect2.x = rect1.x + rect1.w + 10;  // Position rect2 next to rect1
//     rect2.y = 10;
//     rect2.w = 100;
//     rect2.h = 200;
//   
//     SDL_Rect rect3;
//     rect3.x = rect2.x + rect2.w + 70;  // Position rect3 next to rect2
//     rect3.y = 10;
//     rect3.w = 100;
//     rect3.h = 200;
//   
//     SDL_Rect rect4;
//     rect4.x = rect3.x + rect3.w + 10;  // Position rect4 next to rect3
//     rect4.y = 10;
//     rect4.w = 100;
//     rect4.h = 200;
//   
//     
//   
//   
//     SDL_SetRenderDrawColor(rend,255, 255, 255, 255);
//     SDL_RenderDrawRect(rend, &rect1);
//     SDL_RenderDrawRect(rend, &rect2);
//     SDL_RenderDrawRect(rend, &rect3);
//     SDL_RenderDrawRect(rend, &rect4);
//     SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
//   
//    
//     insert_text(array, &rect1, rend );
//     
//   
//     int close=0;
//       while(!close){
//       SDL_Event event;
//       while (SDL_PollEvent(&event)){
//         if(event.type== SDL_QUIT){
//           close=1;
//         }
//         else{
//           handleKeyboardInput(&event, &close);
//         }
//       }
//     }
//     // wait a few seconds
//     //SDL_Delay(5000);
//     SDL_DestroyTexture(tex);
//     // clean up resources before exiting
//     SDL_DestroyWindow(win);
//     TTF_Quit();
//     SDL_Quit();
//   }
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


// Handle keyboard events
void handleKeyboardInput(int c,int id[],SDL_Event *event, int *close, int width, int height) {
  switch(c){
    case 3:
      switch (event->key.keysym.sym) {
          case SDLK_1:
              printf("Pressed 1\n");
              *close = 1;
              resize(id[0],0,0,width/2,height);
              resize(id[1],width/2,0,width/2,height);
              break;
          case SDLK_2:
              printf("Pressed 2\n");
              *close = 1;
              resize(id[1],0,0,width/2,height);
              resize(id[2],width/2,0,width/2,height);
              break;
          case SDLK_3:
              printf("Pressed 3\n");
              *close = 1;
              resize(id[0],0,0,width/2,height);
              resize(id[2],width/2,0,width/2,height);
              break;
          case SDLK_4:
              printf("Pressed 3\n");
              *close = 1;
              resize(id[0],0,0,width/2,height/2);
              resize(id[2],width/2,0,width/2,height/2);
               resize(id[1],0,height/2,width,height/2);
              break;


          default:
              break;}
    case 2:
      switch (event->key.keysym.sym) {
                case SDLK_1:
                    printf("Pressed 1\n");
                    *close = 1;
                    resize(id[0],0,0,width/2,height);
                    resize(id[1],width/2,0,width/2,height);
                    break;
                case SDLK_2:
                    printf("Pressed 2\n");
                    *close = 1;
                    resize(id[0],0,0,width,height/2);
                    resize(id[1],0,height/2,width,height/2);
                    break;
                default:
                    break;
    }}
}

// Renders text below the given rectangle.
// 'text' is the string to display, 'rect' is the rectangle reference for positioning,
// 'rend' is the SDL_Renderer we draw on.
//   int insert_text(const char *text, SDL_Rect *rect, SDL_Renderer* rend) {
//       if (!text || !*text) {
//           return 0; // no string to render
//       }
//   
//       // Make sure TTF is initialized (calling TTF_Init multiple times is safe, but typically do it once)
//       if (TTF_Init() == -1) {
//           printf("TTF_Init failed: %s\n", TTF_GetError());
//           return 1;
//       }
//   
//       // Choose font and color
//       SDL_Color textColor = {255, 255, 255, 255};  // White color
//       TTF_Font *font = TTF_OpenFont("/usr/share/fonts/TTF/TSCu_Times.ttf", 24);
//       if (!font) {
//           printf("Error loading font: %s\n", TTF_GetError());
//           return 1;
//       }
//   
//       // Create the text surface
//       SDL_Surface *textSurface = TTF_RenderText_Blended(font, text, textColor);
//       if (!textSurface) {
//           printf("TTF_RenderText_Blended failed: %s\n", TTF_GetError());
//           TTF_CloseFont(font);
//           return 1;
//       }
//   
//       SDL_Texture *textTexture = SDL_CreateTextureFromSurface(rend, textSurface);
//       if (!textTexture) {
//           printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
//           SDL_FreeSurface(textSurface);
//           TTF_CloseFont(font);
//           return 1;
//       }
//   
//       // Determine where to draw the text. We'll put it just below the rectangle.
//       SDL_Rect trect = {
//           .x = rect->x,
//           .y = rect->y + rect->h + 10, // 10 px below the rectangle
//           .w = 2*(rect->w),
//           .h = textSurface->h
//       };
//   
//       SDL_FreeSurface(textSurface); // No longer needed once we have a texture
//   
//       // Render the text
//       SDL_RenderCopy(rend, textTexture, NULL, &trect);
//   
//       // Cleanup
//       SDL_DestroyTexture(textTexture);
//       TTF_CloseFont(font);
//   
//       return 0;
//   }
//  
int insert_text(int m,const char *text, SDL_Rect *rect, SDL_Renderer* rend) {
    if (!text || !*text) {
        return 0; // No string to render
    }

    // Initialize TTF if not already done
    if (TTF_Init() == -1) {
        printf("TTF_Init failed: %s\n", TTF_GetError());
        return 1;
    }

    // Choose font and color
    SDL_Color textColor = {255, 255, 255, 255};  // White color
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/TTF/TSCu_Times.ttf",16);
    if (!font) {
        printf("Error loading font: %s\n", TTF_GetError());
        return 1;
    }

    int maxWidth = m*rect->w; // Maximum width for text wrapping
    int x = rect->x;           // Starting x-coordinate
    int y = rect->y + rect->h + 10; // Starting y-coordinate (below the rectangle)

    char lineBuffer[1024]; // Buffer to hold a single line of text
    const char *currentPos = text; // Pointer to the current position in the input text
    while (*currentPos) {
        int lineLength = 0; // Length of the current line
        int lastValidLength = 0; // Length of the last valid line (doesn't exceed maxWidth)

        // Try to fit as much text as possible within the maxWidth
        while (currentPos[lineLength] && lineLength < sizeof(lineBuffer) - 1) {
            lineBuffer[lineLength] = currentPos[lineLength];
            lineBuffer[lineLength + 1] = '\0'; // Null-terminate

            // Check if the current line fits within the maxWidth
            int textWidth;
            TTF_SizeText(font, lineBuffer, &textWidth, NULL);
            if (textWidth <= maxWidth) {
                lastValidLength = lineLength + 1; // Update the last valid length
            } else {
                break; // Text exceeded maxWidth
            }
            lineLength++;
        }

        // If no valid line could fit, forcefully split the text
        if (lastValidLength == 0) {
            lastValidLength = lineLength;
        }

        // Render the valid portion of the text
        strncpy(lineBuffer, currentPos, lastValidLength);
        lineBuffer[lastValidLength] = '\0'; // Null-terminate the current line

        SDL_Surface *textSurface = TTF_RenderText_Blended(font, lineBuffer, textColor);
        if (!textSurface) {
            printf("TTF_RenderText_Blended failed: %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return 1;
        }

        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(rend, textSurface);
        if (!textTexture) {
            printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
            SDL_FreeSurface(textSurface);
            TTF_CloseFont(font);
            return 1;
        }

        SDL_Rect trect = {
            .x = x,
            .y = y,
            .w = textSurface->w,
            .h = textSurface->h
        };
        SDL_RenderCopy(rend, textTexture, NULL, &trect);

        // Clean up the current texture and surface
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);

        // Move to the next line
        y += trect.h + 5; // Add line height and spacing
        currentPos += lastValidLength; // Advance the pointer to the next part of the text

        // Skip leading spaces for the next line
        while (*currentPos == ' ') {
            currentPos++;
        }
    }

    TTF_CloseFont(font);
    return 0;
}

int main() {
    // 1) Retrieve top 3 windows
    char *array[3] = {0}; // Initialize top array
    int ids[3] = {0};
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        printf("Unable to open X display\n");
        return 1;
    }
    
    int screen = DefaultScreen(display);
    int width = DisplayWidth(display, screen);
    int height = DisplayHeight(display, screen);

    top_used_windows(array, ids);

    // 2) Count how many valid (non-null) entries we have
    int c = 0;
    for (int i = 0; i < 3; i++) {
        if (array[i]) {
            c++;
        }
    }

    // Print them for debugging
    printf("Top %d Used Windows:\n", c);
    for (int i = 0; i < c; i++) {
        printf("  %s (ID: %d)\n", array[i], ids[i]);
    }

    // 3) Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    // If you want a bigger window when c=3 for "good symmetry"
    int window_w = 640;
    int window_h = 480;
     if (c == 3) {
         window_w = 640;
         window_h = 600;
     }

    SDL_Window* win = SDL_CreateWindow("Hello, CS50!",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       window_w,
                                       window_h,
                                       0);
    if (!win) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // 4) Load background image
    SDL_Surface* surface = IMG_Load("black-screen_39.png");
    if (!surface) {
        printf("Error loading surface: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if (!tex) {
        printf("Error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // 5) Clear and draw background
    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, tex, NULL, NULL);

    // 6) Define your 4 rectangles (two sets: rect1&rect2 and rect3&rect4)
    SDL_Rect rect1;
    rect1.x = 50;
    rect1.y = 10;
    rect1.w = 100;
    rect1.h = 200;

    SDL_Rect rect2;
    rect2.x = rect1.x + rect1.w + 10;  // next to rect1
    rect2.y = 10;
    rect2.w = 100;
    rect2.h = 200;

    SDL_Rect rect3;
    rect3.x = rect2.x + rect2.w + 120;  // next to rect2
    rect3.y = 10;
    rect3.w = 100;
    rect3.h = 200;

    SDL_Rect rect4;
    rect4.x = rect3.x + rect3.w + 10;  // next to rect3
    rect4.y = 10;
    rect4.w = 100;
    rect4.h = 200;

    SDL_Rect rect5;
    rect5.x = rect2.x + rect2.w + 120;  // next to rect3
    rect5.y = 10;
    rect5.w = 200;
    rect5.h = 100;   

    SDL_Rect rect6;
    rect6.x = rect5.x;  // next to rect3
    rect6.y = rect5.y+ rect5.h+10;
    rect6.w = 200;
    rect6.h = 100;

    SDL_Rect rect7;
    rect7.x = rect1.x;  // next to rect3
    rect7.y = rect1.y+rect1.h+70;
    rect7.w = 100;
    rect7.h = 200;

    SDL_Rect rect8;
    rect8.x=rect7.x+rect7.w+10;
    rect8.y=rect7.y;
    rect8.w=100;
    rect8.h=200;

    SDL_Rect rect9;
      rect9.x = rect8.x + rect8.w + 120;  // next to rect3
      rect9.y = rect8.y;
      rect9.w = 100;
      rect9.h = 100;

    SDL_Rect rect10;
    rect10.x=rect9.x+rect9.w+10;
    rect10.y=rect9.y;
    rect10.w=100;
    rect10.h=100;

    SDL_Rect rect11;
    rect11.x = rect9.x;  // next to rect3
    rect11.y = rect9.y+ rect9.h+10;
    rect11.w = 210;
    rect11.h = 100;





    
    // 7) Build the text lines you want displayed
    //    - line1 = array[0] & array[1] (if c >= 2)
    //    - line2 = array[1] & array[2] (if c >= 3)
    char line1[256] = "";
    char line2[256] = "";
    char line3[256] = "";
    char line4[256] = "";

    if (c == 3) {
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

        SDL_RenderDrawRect(rend, &rect1);
        SDL_RenderDrawRect(rend, &rect2);
        SDL_RenderDrawRect(rend, &rect3);
        SDL_RenderDrawRect(rend, &rect4);
        SDL_RenderDrawRect(rend, &rect7);
        SDL_RenderDrawRect(rend, &rect8);
        SDL_RenderDrawRect(rend, &rect9);
        SDL_RenderDrawRect(rend, &rect10);
        SDL_RenderDrawRect(rend, &rect11);

        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);

        snprintf(line1, sizeof(line1), "%s & %s", array[0], array[1]);
        snprintf(line2, sizeof(line2), "%s & %s", array[1], array[2]);
        snprintf(line3, sizeof(line3), "%s & %s", array[0], array[2]);
        snprintf(line4, sizeof(line4), "%s & %s & %s", array[0], array[1], array[2]);


        if (line1[0] != '\0' && line2[0] != '\0' ) {  
        insert_text(2,line1, &rect1, rend);
        insert_text(2,line2, &rect3, rend);
        insert_text(2,line3, &rect7, rend);
        insert_text(1,line4, &rect11, rend);

    }
    }
    
    //   if (c >= 3) {
    //       snprintf(line2, sizeof(line2), "%s & %s", array[1], array[2]);
    //   }

    // 8) Render the text strings:
    //    - line1 below rect1 AND rect2 (your "first set")
    //    - line2 below rect3 AND rect4 (your "second set")
    //   if (line2[0] != '\0') {
    //       insert_text(line2, &rect3, rend);
    //       insert_text(line2, &rect4, rend);
    //   }
  //
  if(c==2){
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    SDL_RenderDrawRect(rend, &rect1);
    SDL_RenderDrawRect(rend, &rect2);
    SDL_RenderDrawRect(rend, &rect5);
    SDL_RenderDrawRect(rend, &rect6);
    snprintf(line1, sizeof(line1), "%s & %s", array[0], array[1]);
    snprintf(line2, sizeof(line2), "%s & %s", array[0], array[1]);
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    if (line1[0] != '\0' && line2[0] != '\0' ) {  
        insert_text(2,line1, &rect1, rend);
        insert_text(1,line2, &rect6, rend);
    }
  }

    

    // Present everything on screen
    SDL_RenderPresent(rend);

    // 9) Event loop
    int close = 0;
    while (!close) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                close = 1;
            } else{
                handleKeyboardInput(c,ids,&event, &close,width,height);
            }
        }
        // If you want continuous updates, you could re-render, etc.
        // For now, we just wait for quit/keypress.
    }

    // 10) Cleanup
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

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

