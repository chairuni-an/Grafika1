//file: grafika1.c
//versi: chairuni-an

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

int main()
{
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    char *fbp = 0;
    int x = 0, y = 0;
    long int location = 0;

    #define background_red 235
    #define background_green 138
    #define background_blue 163

    void makeBackground(){
        for (y = 0; y < 236; y++)//maks 236
            for (x = 0; x < 800; x++) {//maks 800

                location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                           (y+vinfo.yoffset) * finfo.line_length;

                if (vinfo.bits_per_pixel == 32) { // color information
                    *(fbp + location) = background_blue;        // blue
                    *(fbp + location + 1) = background_green;     // green
                    *(fbp + location + 2) = background_red;    // red
                    *(fbp + location + 3) = 0;      // No transparency
                } else { 
                    printf("can't write\n");
                }
            }
    }

    void drawBlock(int absis, int ordinat, int red, int green, int blue){
        for (y = ordinat; y < ordinat+10; y++)//maks 236
            for (x = absis; x < ordinat+10; x++) {//maks 800

                location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                           (y+vinfo.yoffset) * finfo.line_length;

                if (vinfo.bits_per_pixel == 32) { // color information
                    *(fbp + location) = blue;        // blue
                    *(fbp + location + 1) = green;     // green
                    *(fbp + location + 2) = red;    // red
                    *(fbp + location + 3) = 0;      // No transparency
                } else  { 
                printf("can't write\n");
                }
            }
    }
    void eraseBlock(int absis, int ordinat){
        for (y = ordinat; y < ordinat+10; y++)//maks 236
            for (x = absis; x < ordinat+10; x++) {//maks 800

                location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                           (y+vinfo.yoffset) * finfo.line_length;

                if (vinfo.bits_per_pixel == 32) { // color information
                    *(fbp + location) = background_blue;        // blue
                    *(fbp + location + 1) = background_green;     // green
                    *(fbp + location + 2) = background_red;    // red
                    *(fbp + location + 3) = 0;      // No transparency
                } else { 
                    printf("can't write\n");
                }
            }
    }

    void fly(int red, int green, int blue){
        for(int i = 0; i<10; i++){
            drawBlock(10*i,10*i,red,green,blue);
            printf("Heiho\n");
            sleep(1000);
            eraseBlock(10*i,10*i);
        }
    }
    

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
    printf("Screensize: %d", screensize);

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");

    makeBackground(0, 200, 255);
    drawBlock(0, 0, 200, 100, 0);
    fly(200,100,0);
    munmap(fbp, screensize);
    close(fbfd);
    return 0;
}