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


#define EXIT_SUCC 0;
#define EXIT_FAIL 1;
//extern JSAMPLE * image_buffer;

// int copy_file (const char* srcfile, const char* destfile );

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
 // unsigned char *buffer = malloc(6000000*sizeof(unsigned char));
char ch;
 // int n = 0;


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

  pfile1 = fopen("Receipt.txt", "rt");
 pfile2 = fopen("F1.txt", "wt");
  // pfile1 = fopen("Flower4.jpg", "rb");
    // pfile2 = fopen("DemoDay.jpg", "wb");
   setbuf(stdout, NULL);
   setbuf(stdin, NULL);



//fputs ("This is added to the buffered stream, Do you see this?", pfile1);

   if(wiringPiSetupGpio() == -1)
   {
   fprintf(stdout, "unable to start WiringPi : %s\n", strerror(errno));
       return EXIT_FAIL;
   }


   if((fd = serialOpen("/dev/ttyAMA0", 9600)) < 0)
   {
      fprintf(stderr, "Unable to open serial device : %s\n", strerror(errno));
        return EXIT_FAIL;
    }

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
*/
clock_t start;
clock_t end;
double cpu_time;

unsigned long fileLen;
unsigned long counter;

fseek(pfile1, 0, SEEK_END);
fileLen = ftell(pfile1);
fseek(pfile1, 0, SEEK_SET);

double wall_start = wall_time();
start = clock();
for (counter = 0; counter < fileLen; counter++) {

int z;
// Comment this is you are sending an image file, this only works for TEXT files!!
while ((z = fgetc(pfile1)) != EOF) {
	printf("%c", z);
	serialPrintf(fd, "%c", z);
}

// Uncomment this below if you are sending an image file
/*

unsigned long ch = fgetc(pfile1);
printf("%02x", ch);
serialPrintf(fd,"%x", ch);
unsigned long written = fputc(ch, pfile2);

if (written != EOF)
{
	buffer[counter] =ch;
}
*/

/*
fputc(fgetc(pfile1), pfile2);
ch= fread(buffer, sizeof(char), 6000000, pfile1);
printf("%02x", buffer[counter]);
 serialPrintf(fd,"%x", buffer[counter]);
*/
// THISfputc(fgetc(pfile1), pfile2);
//fputc(fgetc(pfile1), buffer[counter]);
// fputc(buffer[counter], pfile1);
//serialPutchar(fd, buffer[counter]);
//March 17:
//THIS chh = fread(buffer, sizeof(char), 60000, pfile1);
// THIS serialPrintf(fd,"%x", buffer[counter]);
}
end = clock();
double wall_end = wall_time();
cpu_time = ((double) (end-start)) / CLOCKS_PER_SEC;

printf("\nElapsed CPU Time: %fs\n", (float)cpu_time);
printf("Elapsed Wall time: %fs\n", (float) (wall_end - wall_start));
printf("\n");

fclose(pfile1);
fclose(pfile2);
while (1) {
         if((data = fgetc(stdin)) == EOF){
                 printf("EOF\n");
            break;
         }
        if(data == '\n'){
         serialPutchar(fd, '\r');



      }


       serialPutchar(fd, data);

      // data = serialGetchar(fd);
       // printf("%c", data);



}
 return EXIT_SUCC;
}


