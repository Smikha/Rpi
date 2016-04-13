#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/time.h>
#include <float.h>


/*
Capstone Project
S. Mikha (200 300 xxx)
Winter 2016
This program outputs text and images to the serial line using the Raspberry Pi and RN-42 Bluetooth module
It can also be used to simply write text to the serial line
*/



#define EXIT_SUCC 0;
#define EXIT_FAIL 1;


// C defined wall time caculation
// Get the time of the PC, then start and end when specified
double wall_time () {
struct timeval time;
if (gettimeofday(&time,NULL)) {
	return 0;
}
return (double)time.tv_sec + (double)time.tv_usec * .000001;
}



int main(int argc, char **argv) {
   int fd;
   int data;
FILE *pfile2;
  FILE *pfile1;
 // unsigned char buffer[60000] = {0};
 //allocating size of buffer for image transfer
 unsigned char *buffer = malloc(6000000*sizeof(unsigned char));
char ch;



  /*
   // Here I try the new method to compress the file (March 7)
   const int charsize = 1000;
   char file [charsize];

   FILE *fm = NULL;

   fm = fopen("testimg.jpg", "w+b");

    fseek(fm, 0L, SEEK_END);
    unsigned long size = ftell(fm);

    if (fm != NULL)
    {
	fseek(fm, 0L, SEEK_END);
	unsigned long size = ftell(fm);
	fseek(fm, 0L, SEEK_SET);

	fread(file, 1, size, fm);
	fclose(fm);

}

if ( fm != NULL)
{
	// fwrite(file, 1, size, fm);
	fputs(file, fm);
	fclose(fm);
}

     */
     /*
     fp = fopen("testimg.jpg", "rb");
     fseek (fp, 0, SEEK_END);
     len = ftell(fp);
     fseek (fp, 0, SEEK_SET);
     buffer[] = (char *)malloc(len);
     fread(buffer,len,1,fp);
     close(fp);
     */
     
     
/*
Here we open the files, you must specify whether you would like a Text file
or Image file as the formats are different

*/
  pfile1 = fopen("Receipt.txt", "rt");
 pfile2 = fopen("F1.txt", "wt");
  // pfile1 = fopen("Flower4.jpg", "rb");
    // pfile2 = fopen("DemoDay.jpg", "wb");
    
    //Set the buffer to point towards the input and output streams of the connection
   setbuf(stdout, NULL);
   setbuf(stdin, NULL);



// If we cannot initialize the wiringpi system, than exit
   if(wiringPiSetupGpio() == -1)
   {
   fprintf(stdout, "unable to start WiringPi : %s\n", strerror(errno));
       return EXIT_FAIL;
   }

//Specify the baud rate at which the device operates at and allow the user to know if there 
//cannot be a connection. Currently this is set for 9600 baud rate on the UART pins
   if((fd = serialOpen("/dev/ttyAMA0", 9600)) < 0)
   {
      fprintf(stderr, "Unable to open serial device : %s\n", strerror(errno));
        return EXIT_FAIL;
    }


clock_t start;
clock_t end;
double cpu_time;

unsigned long fileLen;
unsigned long counter;

//Find the size of the file we have opened
fseek(pfile1, 0, SEEK_END);
fileLen = ftell(pfile1);
fseek(pfile1, 0, SEEK_SET);

//Start the clocks we are using to time the transmission
double wall_start = wall_time();
start = clock();
for (counter = 0; counter < fileLen; counter++) {

int z;
//*****************
// Comment this is you are sending an image file, this only works for TEXT files!!
//Here we open the file, retrieve the characters bit by bit until we reach the end of the file
//Once we hit the end quit, otherwise print the characters to the screen and send them on the serial line
while ((z = fgetc(pfile1)) != EOF) {
	printf("%c", z);
	serialPrintf(fd, "%c", z);
}


//*****************
// Uncomment this below if you are sending an image file
/*

Get the file as character bits and print them as hex values to the screen
Then print them to the serial line
Keep track of what you have taken in and place it into the second file now (to duplicate)
One we have hit the end of the file, stop allocating bits to the second file and printing. 
unsigned long ch = fgetc(pfile1);
printf("%02x", ch);
serialPrintf(fd,"%x", ch);
unsigned long written = fputc(ch, pfile2);

if (written != EOF)
{
	buffer[counter] =ch;
}
*/


}
end = clock();
double wall_end = wall_time();
cpu_time = ((double) (end-start)) / CLOCKS_PER_SEC;


// Using the predefined functions for timing in C, print these measurements to the screen
// Essentially, I took T2 - T1 and devidied it by the clock frequency for CPU time
// For wall time, I used the internal functions of C and just started when the loop started and ended when it exited
printf("\nElapsed CPU Time: %fs\n", (float)cpu_time);
printf("Elapsed Wall time: %fs\n", (float) (wall_end - wall_start));
printf("\n");



fclose(pfile1);
fclose(pfile2);
while (1) {
	//this allows for the user to write to anothers screen
	//As the user types in the terminal window, keep sending bits until we hit the end
         if((data = fgetc(stdin)) == EOF){
                 printf("EOF\n");
            break;
         }
         //If we hit a end line character, then send them a new line character as well
        if(data == '\n'){
         serialPutchar(fd, '\r');



      }


       serialPutchar(fd, data);

      // data = serialGetchar(fd);
       // printf("%c", data);



}
 return EXIT_SUCC;
}

/*
More Testing:

//fgets(line, 80, fr);
//sscanf (line, "%ld", &elapsed);
//printf ("%ld\n", elapsed);

// serialPuts(fd, "From the raspberry pi, here is the JPEG INFO:\r\n");
  //  serialPuts(fd, "\r\n");

    /*
   while(1) {
    setbuf (pfile1, buffer);
   	fgets(buffer, 632, pfile1);

     serialPrintf(fd, buffer);
     fputs(buffer, pfile2);

 }
   	 fclose (pfile1);
   	 */
   	/*
   	 if (pfile1 == NULL)
   	 perror ("Error opening file");
   	 else
   	 {
	 while (fgetc(pfile1) != EOF) {
		 ++n;
		 setbuf(pfile1, buffer);
		 fgets(buffer, 2000, pfile1);
		 serialPrintf(fd, buffer);
		 fputs(buffer, pfile2);
	 }

	 if (feof(pfile1)) {
		 puts("end of file reached.");
		 printf("Total number of bytes read: %d\n", n);
	 }
	 else puts ("End of file was not reached.");
	// fclose(pfile1);
 }
 
 
 
 /*
fputc(fgetc(pfile1), pfile2);
ch= fread(buffer, sizeof(char), 6000000, pfile1);
printf("%02x", buffer[counter]);
 serialPrintf(fd,"%x", buffer[counter]);
*/
// fputc(fgetc(pfile1), pfile2);
//fputc(fgetc(pfile1), buffer[counter]);
// fputc(buffer[counter], pfile1);
//serialPutchar(fd, buffer[counter]);
//March 17:
//chh = fread(buffer, sizeof(char), 60000, pfile1);
//  serialPrintf(fd,"%x", buffer[counter]);
*/
