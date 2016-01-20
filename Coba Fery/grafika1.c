//file: grafika1.c

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#define FONT_SIZE 10
#define FONT_WIDTH 10
#define FONT_HEIGHT 15

/* Character Font */
int font[][FONT_WIDTH * FONT_HEIGHT] = {  // 'A'
                                          { 0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
                                            0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
                                            0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
                                            0, 1, 0, 0, 0, 0, 0, 0, 1, 0,
                                            0, 1, 0, 0, 0, 0, 0, 0, 1, 0,
                                            1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                            1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                            1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                            1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                            1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                            1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                            1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                            1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                            1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                            1, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, 
                                        // 'b'
                                          { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
                                            1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
                                            1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
                                            1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
                                            1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
                                            1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
                                            1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
                                            1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
                                            1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
                                            1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
                                            1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
                                            1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
                                            1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
                                            1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
                                            1, 1, 1, 1, 1, 1, 1, 0, 0, 0 }, 
                                        // 'C'
                                          { 0, 0, 0, 0, 1, 1, 1, 1, 0, 0,
                                            0, 0, 0, 1, 0, 0, 0, 0, 1, 0,
                                            0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
                                            0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
                                            0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
                                            0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
                                            0, 0, 0, 1, 0, 0, 0, 0, 1, 0,
                                            0, 0, 0, 0, 1, 1, 1, 1, 0, 0 } };

int fbfd = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
long int screensize = 0;
char *fbp = 0;
long int location = 0;

void blockBuilder(int x, int y, int clear) {
    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    //printf("The framebuffer device was mapped to memory successfully.\n");

    int i, j;
    // Figure out where in memory to put the pixel
    for (j = y; j < y + FONT_SIZE ; j++) {
        for (i = x; i < x + FONT_SIZE; i++) {

            location = (i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (j+vinfo.yoffset) * finfo.line_length;

            if (vinfo.bits_per_pixel == 32) {
                *(fbp + location) = 255 - clear;        // Blue
                *(fbp + location + 1) = 255 - clear;    // Green
                *(fbp + location + 2) = 255 - clear;    // Red
                *(fbp + location + 3) = 0;      // Alpha
        //location += 4;
            } else  { //assume 16bpp
                int b = 255 - clear;
                int g = 255 - clear;     // A little green
                int r = 255 - clear;    // A lot of red
                unsigned short int t = r<<11 | g << 5 | b;
                *((unsigned short int*)(fbp + location)) = t;
            }

        }
    }
    munmap(fbp, screensize);
}

void charBuilder(char c, int startX, int startY) {
    int i, j;
    for (j = 0; j < FONT_HEIGHT; j++) {
        for (i = 0; i < FONT_WIDTH; i++) {
            if ( font[c - 65][j * FONT_WIDTH + i] == 1 ) {
                blockBuilder(startX + i * FONT_SIZE, startY + j * FONT_SIZE, 0);
            } else {
                blockBuilder(startX + i * FONT_SIZE, startY + j * FONT_SIZE, 255);                
            }
        }
    }
}

void stringBuilder(char *s) {
    int startX = 100;
    int startY = 100;

    int i;
    for (i = 0; i < strlen(s); i++) {
        charBuilder(s[i], startX + i * FONT_SIZE * (FONT_WIDTH + 1), startY);
    }

}

char* receiveInput(char *s){
    scanf("%99s",s);
    return s;
}

int main() {

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;


    char str[100];
    receiveInput(str);

    stringBuilder(str);
    close(fbfd);
    return 0;
}