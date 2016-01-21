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
#define FONT_WIDTH 5
#define FONT_HEIGHT 5

/* Character Font */
//FONT 5X5

int font[][FONT_WIDTH * FONT_HEIGHT] = {
										// 'A'
                                          { 0, 1, 1, 1, 0,
                                            1, 0, 0, 0, 1,
                                            1, 0, 0, 0, 1,
                                            1, 1, 1, 1, 1,
                                            1, 0, 0, 0, 1 },
                                        // 'B'
                                          { 1, 1, 1, 1, 0,
                                            1, 0, 0, 0, 1,
                                            1, 1, 1, 1, 0,
                                            1, 0, 0, 0, 1,
                                            1, 1, 1, 1, 0 },
                                        // 'C'
                                          { 0, 1, 1, 1, 0,
                                            1, 0, 0, 0, 1,
                                            1, 0, 0, 0, 0,
                                            1, 0, 0, 0, 1,
                                            0, 1, 1, 1, 0 },
                                        // 'D'
                                          { 1, 1, 1, 1, 0,
                                            1, 0, 0, 0, 1,
                                            1, 0, 0, 0, 1,
                                            1, 0, 0, 0, 1,
                                            1, 1, 1, 1, 0 },
                                        // 'E'
                                          { 1, 1, 1, 1, 1,
                                            1, 0, 0, 0, 0,
                                            1, 1, 1, 1, 0,
                                            1, 0, 0, 0, 0,
                                            1, 1, 1, 1, 1 },
                                        // 'F'
                                          { 1, 1, 1, 1, 1,
                                            1, 0, 0, 0, 0,
                                            1, 1, 1, 1, 0,
                                            1, 0, 0, 0, 0,
                                            1, 0, 0, 0, 0 },
                                        // 'G'
                                          { 0, 1, 1, 1, 1,
                                            1, 0, 0, 0, 0,
                                            1, 0, 1, 1, 1,
                                            1, 0, 0, 0, 1,
                                            0, 1, 1, 1, 1 },
                                        // 'H'
                                          { 1, 0, 0, 0, 1,
                                            1, 0, 0, 0, 1,
                                            1, 1, 1, 1, 1,
                                            1, 0, 0, 0, 1,
                                            1, 0, 0, 0, 1 },
                                        // 'I'
                                          { 0, 1, 1, 1, 0,
                                            0, 0, 1, 0, 0,
                                            0, 0, 1, 0, 0,
                                            0, 0, 1, 0, 0,
                                            0, 1, 1, 1, 0 },
                                        // 'J'
                                          { 0, 0, 0, 1, 1,
                                            0, 0, 0, 0, 1,
                                            0, 0, 0, 0, 1,
                                            1, 0, 0, 0, 1,
                                            0, 1, 1, 1, 0 },
                                        // 'K'
                                          { 1, 0, 0, 0, 1,
                                            1, 0, 0, 1, 0,
                                            1, 1, 1, 0, 0,
                                            1, 0, 0, 1, 0,
                                            1, 0, 0, 0, 1 },
                                        // 'L'
                                          { 1, 0, 0, 0, 0,
                                            1, 0, 0, 0, 0,
                                            1, 0, 0, 0, 0,
                                            1, 0, 0, 0, 0,
                                            1, 1, 1, 1, 1 },
                                        // 'M'
                                          { 1, 0, 0, 0, 1,
                                            1, 1, 0, 1, 1,
                                            1, 0, 1, 0, 1,
                                            1, 0, 0, 0, 1,
                                            1, 0, 0, 0, 1 },
                                        // 'N'
                                          { 1, 0, 0, 0, 1,
                                            1, 1, 0, 0, 1,
                                            1, 0, 1, 0, 1,
                                            1, 0, 0, 1, 1,
                                            1, 0, 0, 0, 1 },
                                        // 'O'
                                          { 0, 1, 1, 1, 0,
                                            1, 0, 0, 0, 1,
                                            1, 0, 0, 0, 1,
                                            1, 0, 0, 0, 1,
                                            0, 1, 1, 1, 0 },
                                        // 'P'
                                          { 1, 1, 1, 1, 0,
                                            1, 0, 0, 0, 1,
                                            1, 1, 1, 1, 0,
                                            1, 0, 0, 0, 0,
                                            1, 0, 0, 0, 0 },
                                        // 'Q'
                                          { 0, 1, 1, 1, 0,
                                            1, 0, 0, 0, 1,
                                            1, 0, 1, 0, 1,
                                            1, 0, 0, 1, 1,
                                            0, 1, 1, 1, 0 },
                                        // 'R'
                                          { 1, 1, 1, 1, 0,
                                            1, 0, 0, 0, 1,
                                            1, 1, 1, 1, 0,
                                            1, 0, 0, 0, 1,
                                            1, 0, 0, 0, 1 },
                                        // 'S'
                                          { 0, 1, 1, 1, 1,
                                            1, 0, 0, 0, 0,
                                            0, 1, 1, 1, 0,
                                            0, 0, 0, 0, 1,
                                            1, 1, 1, 1, 0 },
                                        // 'T'
                                          { 1, 1, 1, 1, 1,
                                            0, 0, 1, 0, 0,
                                            0, 0, 1, 0, 0,
                                            0, 0, 1, 0, 0,
                                            0, 0, 1, 0, 0 },
                                        // 'U'
                                          { 1, 0, 0, 0, 1,
                                            1, 0, 0, 0, 1,
                                            1, 0, 0, 0, 1,
                                            1, 0, 0, 0, 1,
                                            0, 1, 1, 1, 0 },
                                        // 'V'
                                          { 1, 0, 0, 0, 1,
                                            1, 0, 0, 0, 1,
                                            1, 0, 0, 0, 1,
                                            0, 1, 0, 1, 0,
                                            0, 0, 1, 0, 0 },
                                        // 'W'
                                          { 1, 0, 1, 0, 1,
                                            1, 0, 1, 0, 1,
                                            1, 0, 1, 0, 1,
                                            1, 0, 1, 0, 1,
                                            0, 1, 0, 1, 0 },
                                        // 'X'
                                          { 1, 0, 0, 0, 1,
                                            0, 1, 0, 1, 0,
                                            0, 0, 1, 0, 0,
                                            0, 1, 0, 1, 0,
                                            1, 0, 0, 0, 1 },
                                        // 'Y'
                                          { 1, 0, 0, 0, 1,
                                            1, 0, 0, 0, 1,
                                            0, 1, 0, 1, 0,
                                            0, 0, 1, 0, 0,
                                            0, 0, 1, 0, 0 },
                                        // 'Z'
                                          { 1, 1, 1, 1, 1,
                                            0, 0, 0, 1, 0,
                                            0, 0, 1, 0, 0,
                                            0, 1, 0, 0, 0,
                                            1, 1, 1, 1, 1 },
                                            // TIE Fighter Kiri atas
                                          { 0, 1, 0, 1, 0,
                                            1, 0, 1, 0, 1,
                                            1, 1, 0, 1, 1,
                                            1, 0, 1, 0, 1,
                                            0, 1, 0, 1, 0 },
                                            // TIE Fighter Kanan atas
                                            { 0, 1, 0, 1, 0,
                                            1, 0, 1, 0, 1,
                                            1, 1, 0, 1, 1,
                                            1, 0, 1, 0, 1,
                                            0, 1, 0, 1, 0 },
                                            // TIE Fighter Kiri bawah
                                            { 0, 1, 0, 1, 0,
                                            1, 0, 1, 0, 1,
                                            1, 1, 0, 1, 1,
                                            1, 0, 1, 0, 1,
                                            0, 1, 0, 1, 0 },
                                            // TIE Fighter Kanan bawah
                                            { 0, 1, 0, 1, 0,
                                            1, 0, 1, 0, 1,
                                            1, 1, 0, 1, 1,
                                            1, 0, 1, 0, 1,
                                            0, 1, 0, 1, 0 }
                                        };
int fbfd = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
long int screensize = 0;
char *fbp = 0;
long int location = 0;

void blockBuilder(int x, int y, int blue, int green, int red) {
    int i, j;
    // Figure out where in memory to put the pixel
    for (j = y; j < y + FONT_SIZE ; j++) {
        for (i = x; i < x + FONT_SIZE; i++) {

            if ( i >= 0 && j >= 0 && i < vinfo.xres - 50 && j < vinfo.yres - 50 ) {
                location = (i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                           (j+vinfo.yoffset) * finfo.line_length;

                if (vinfo.bits_per_pixel == 32) {
                    *(fbp + location) = 255 - blue;        // Blue
                    *(fbp + location + 1) = 255 - green;    // Green
                    *(fbp + location + 2) = 255 - red;    // Red
                    *(fbp + location + 3) = 0;      // Alpha
            //location += 4;
                } else  { //assume 16bpp
                    int b = 255 - blue;
                    int g = 255 - green;     // A little green
                    int r = 255 - red;    // A lot of red
                    unsigned short int t = r<<11 | g << 5 | b;
                    *((unsigned short int*)(fbp + location)) = t;
                }
            }

        }
    }
}

void charBuilder(char c, int startX, int startY) {
    int i, j;
    for (j = 0; j < FONT_HEIGHT; j++) {
        for (i = 0; i < FONT_WIDTH; i++) {
            if ( font[c - 65][j * FONT_WIDTH + i] == 1 ) {
                blockBuilder(startX + i * FONT_SIZE, startY + j * FONT_SIZE, 255, 0, 0); //Ngilangin warna
            }
        }
    }
}

void stringBuilder(char *s, int startX, int startY) {
    int i;
    for (i = 0; i < strlen(s); i++) {
        charBuilder(s[i], startX + i * FONT_SIZE * (FONT_WIDTH + 1), startY);
    }

}

char* receiveInput(char *s){
    scanf("%99s",s);
    return s;
}

void solidBackground() {
    int i, j;
    // Figure out where in memory to put the pixel
    for (j = 0; j < vinfo.yres - 50; j++) {
        for (i = 0; i < vinfo.xres - 50; i++) {

            location = (i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (j+vinfo.yoffset) * finfo.line_length;

            if (vinfo.bits_per_pixel == 32) {
                *(fbp + location) = 0;        // Blue
                *(fbp + location + 1) = 0;    // Green
                *(fbp + location + 2) = 0;    // Red
                *(fbp + location + 3) = 0;      // Alpha
        //location += 4;
            } else  { //assume 16bpp
                int b = 0;
                int g = 0;     // A little green
                int r = 0;    // A lot of red
                unsigned short int t = r<<11 | g << 5 | b;
                *((unsigned short int*)(fbp + location)) = t;
            }

        }
    }
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

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    //printf("The framebuffer device was mapped to memory successfully.\n");

    //char str[100];
    //receiveInput(str);

    int reductor = 0;

    solidBackground();
    while (reductor < vinfo.yres + (FONT_SIZE * (FONT_HEIGHT + 2) * 6)) {

        char adin[] = "ADIN";
        stringBuilder(adin, (vinfo.xres / 2) - (strlen(adin) * (FONT_WIDTH * FONT_SIZE ) + ((strlen(adin)-1) * FONT_SIZE) )/2, vinfo.yres-reductor);

        char fery[] = "FERY";
        stringBuilder(fery, (vinfo.xres / 2) - (strlen(fery) * (FONT_WIDTH * FONT_SIZE ) + ((strlen(fery)-1) * FONT_SIZE) )/2, vinfo.yres + (FONT_SIZE * (FONT_HEIGHT + 2) * 1) - reductor);

        char wawan[] = "WAWAN";
        stringBuilder(wawan, (vinfo.xres / 2) - (strlen(wawan) * (FONT_WIDTH * FONT_SIZE ) + ((strlen(wawan)-1) * FONT_SIZE) )/2, vinfo.yres + (FONT_SIZE * (FONT_HEIGHT + 2) * 2) - reductor);

        char chaer[] = "CHAER";
        stringBuilder(chaer, (vinfo.xres / 2) - (strlen(chaer) * (FONT_WIDTH * FONT_SIZE ) + ((strlen(chaer)-1) * FONT_SIZE) )/2, vinfo.yres + (FONT_SIZE * (FONT_HEIGHT + 2) * 3) - reductor);

        char julio[] = "JULIO";
        stringBuilder(julio, (vinfo.xres / 2) - (strlen(julio) * (FONT_WIDTH * FONT_SIZE ) + ((strlen(julio)-1) * FONT_SIZE) )/2, vinfo.yres + (FONT_SIZE * (FONT_HEIGHT + 2) * 4) - reductor);

        char ibrohim[] = "BOIM[";
        stringBuilder(ibrohim, (vinfo.xres / 2) - (strlen(ibrohim) * (FONT_WIDTH * FONT_SIZE ) + ((strlen(ibrohim)-1) * FONT_SIZE) )/2, vinfo.yres + (FONT_SIZE * (FONT_HEIGHT + 2) * 5) - reductor);

        ++reductor;
        //sleep(1);

        usleep(10000);
        solidBackground();
    }
    munmap(fbp, screensize);

    close(fbfd);
    return 0;
}
