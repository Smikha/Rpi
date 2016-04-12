//
//  main.c
//  rpi
//
//  Created by Stevan Mikha on 2016-03-12.
//  Copyright © 2016 Stevan Mikha. All rights reserved.
//
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <float.h>
#include <sys/time.h>


double get_wall_time(){
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        //  Handle error
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

int main(int argc, const char * argv[]) {
    // insert code here...
/*
    FILE *pfile2;
    FILE *pfile1;
    
    char buffer[7000];
    
    pfile1 = fopen("d", "rb");
    pfile2 = fopen("d1", "wb");
    setbuf (stdin, NULL);
    setbuf(stdout, NULL);
    
    while (1) {
        setbuf(pfile1, buffer);
        fgets(buffer, 7000, pfile1);
        
        fputs(buffer, pfile2);
    }
  //  fclose(pfile1);
    */

    
    
   
    
   //  **********************
   //  THIS WORKS FOR IMAGES, but it loses at least 50 bytes somehow??
    /*
   unsigned char buffer1[6000];

    FILE *pFile;
    FILE *pFile2;
    int n = 0;
    int i =0;
    pFile = fopen ("myfile.txt","rb");
    pFile2 = fopen("mar17.txt", "wb");
  //  int len = 0;
  //  fseek(pFile, 0, SEEK_END);
   // len = (int)ftell(pFile);
     // printf("This is the size of the file: %d\n", len);
   // fclose(pFile);
   // pFile = fopen ("myfile.txt","rb");
    if (pFile==NULL) perror ("Error opening file");
    else
    {
   
      
        do {
            ++n;
            //setbuf(pFile, buffer1);
           fgets(buffer1, 6000, pFile);
            printf("This is  the buffer content: %s",buffer1);
           fputs(buffer1, pFile2);
            
           
            
         } while (fgetc(pFile) !=  EOF);
        if (feof(pFile)) {
            puts ("End-of-File reached.");
            printf ("Total number of bytes read: %d\n", n);

        }
        else puts ("End-of-File was not reached.");
        fclose (pFile);
    }
    
    */
    FILE * pFile1 = fopen("mar17.txt", "rb");  // open existing binary picture
    unsigned char *buffer= malloc(6000000*sizeof(unsigned char)); // the pic is 6kb or so, so 10k bytes will hold it
    FILE * pFile2 = fopen("newtry.txt", "wb"); // open a new binary file
    // for our copy of the pic
   // char (*ptr)[6000];
    
   char ch;
    unsigned long fileLen;
    unsigned long counter;
 
  
    clock_t start, end;
    double cpu_time_used;
    
    
    fseek(pFile1, 0, SEEK_END);
    fileLen=ftell(pFile1);      // get the exact size of the pic
    fseek(pFile1, 0, SEEK_SET);
    double wall_time_start = get_wall_time();
     start = clock();
   // time_t Wallstart = time(NULL);
    //CHANGE To ++counter
    for(counter=0; counter<fileLen; counter++) {
        
        while ((ch = fgetc(pFile1))!= EOF) {
            printf("%c", ch);
        }
        
        /*
        
        int ch = fgetc(pFile1);
        printf("%02X", ch );
        int written = fputc(ch,pFile2);
        if (written != EOF)
        {
            buffer[counter]=ch;
        }
        */
        
        //fputc(fgetc(pFile1),pFile2);  // read each byte of the small_pic.jpg and make
                                        // a new pic from it
        
        // ch = fread(buffer, sizeof(char), 6000000, pFile1);
       
        // printf("%02x", buffer[counter]);
        
        
        //Needed to use unsigned char for the buffer because it kept adding extra FF's to the line

        
       
   }
    
    /*
    counter =0;
    do {
       
        fputc(fgetc(pFile1),pFile2);
        ch = fread(buffer, sizeof(char), 6000000, pFile1);
        printf("%02x", buffer[counter]);
        counter++;
        
    }while(counter <fileLen);
     */
    end = clock();
    double wall_time_end = get_wall_time();
   // time_t Wallend = time(NULL);
    cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
 //   wall_time_used = ((double) (Wallend - Wallstart));
    printf("\n\nElapsed CPU Time: %fs\n", (float)cpu_time_used);
    printf("Elapsed Wall Time: %fs\n", (float) (wall_time_end - wall_time_start));
    printf("\n");
    
    fclose(pFile1);
    fclose(pFile2);
    
    
    
    
    
//
//    int counter;
//    double *ptr_d;
//    FILE *ptr_fp;
//    
//    /* Part A
//     Allocate some memory for the next steps
//     
//     */
//    ptr_d = (double *)malloc(10 * sizeof(double));
//    if(!ptr_d)
//    {
//        printf("Memory allocation error!\n");
//        exit(1);
//    }else printf("Memory allocation successful.\n");
//    
//    /* Part B
//     Create some random numbers and place them in our allocated memory
//     
//     */
//    for(counter = 0; counter < 10; counter++)
//        ptr_d[counter] = (double) rand();
//    
//    /* Part C
//     
//     Creates an empty file for the binary data to go into
//     */
//    if((ptr_fp = fopen("test.txt", "wb")) == NULL)
//    {
//        printf("Unable to open file!\n");
//        exit(1);
//    }else printf("Opened file successfully for writing.\n");
//    
//    /* Part D
//     Content of the array is written to the file just opened and the allocated memory is freed
//     */
//    if( fwrite(ptr_d, 10*sizeof(double), 1, ptr_fp) != 1)
//    {
//        printf("Write error!\n");
//        exit(1);
//    }else printf("Write was successful.\n");
//    fclose(ptr_fp);
//    free(ptr_d);
//    
//    /* Part E
//     Allocate some memory to read the file
//     */
//    ptr_d = (double *)malloc(10 * sizeof(double));
//    if(!ptr_d)
//    {
//        printf("Memory allocation error!\n");
//        exit(1);
//    }else printf("Memory allocation successful.\n");
//    
//    /* Part F
//     Now open the file so we can read it
//     */
//    if((ptr_fp = fopen("test.txt", "rb"))==NULL)
//    {
//        printf("Unable to open the file!\n");
//        exit(1);
//    }else printf("Opened file successfully for reading.\n");
//    
//    /* Part G
//     Read the content of the file now
//     */
//    if(fread(ptr_d, 10 * sizeof( double ), 1, ptr_fp) != 1)
//    {
//        printf( "Read error!\n" );
//        exit( 1 );
//    }else printf( "Read was successful.\n" );
//    fclose(ptr_fp);
//    
//    /* Part H
//     Print each member of the array to the screen now
//     */
//    printf("The numbers read from file are:\n");
//    for(counter = 0; counter < 10; counter++)
//        printf("%f ", ptr_d[counter]);
//    
//    /* Part I
//     Free memory that was allocated
//     */
//    free(ptr_d);
  
   /*
    char errorBuffer[50];
    
    //Prepare read file
    FILE *pReadFile;
    long bufferReadSize;
    char *bufferReadFile; //This variable is going to be returned as file content
    size_t readFileSize;
    
    pReadFile = fopen ("cbc.jpg", "rb");
    
    if (pReadFile != NULL)
    {
        // Get file size.
        fseek (pReadFile , 0 , SEEK_END);
        bufferReadSize = ftell (pReadFile);
        rewind (pReadFile);
        
        // Allocate RAM to contain the whole file:
        bufferReadFile = (char*) malloc (sizeof(char) * bufferReadSize);
        
        if (bufferReadFile != NULL)
        {
            // Copy the file into the buffer:
            readFileSize = fread (bufferReadFile, sizeof(char), bufferReadSize, pReadFile);
            
            if (readFileSize == bufferReadSize)
            {
                return bufferReadFile;
                
                fclose (pReadFile);
                free (bufferReadFile);
            } else {
                //fread failed
                sprintf (errorBuffer, "File reading failed for file:\n%s", fileName);
                MessageBox (NULL, errorBuffer, "Error file reading", MB_ICONERROR | MB_OK);
            }
        } else {
            //malloc failed
            sprintf (errorBuffer, "Memory allocation failed for file:\n%s", fileName);
            MessageBox (NULL, errorBuffer, "Error memory allocation", MB_ICONERROR | MB_OK);
        }
    } else {
        //fopen failed
        sprintf (errorBuffer, "File opening failed for file:\n%s", fileName);
        MessageBox (NULL, errorBuffer, "Error file opening", MB_ICONERROR | MB_OK);
    }
    
    */
    
    
    return 0;
}
