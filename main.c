//
//  main.c
//  rescale
//
//  Created by Hank Lee on 9/19/16.
//  Copyright (c) 2016 Hank Lee. All rights reserved.
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

#include "rescale.h"


typedef struct
{
    char name[256];
} string_t;

static string_t null;


int main(int argc, char *argv[])
{
    int ifd;
    int ofd;
    
    ssize_t rd_sz;
    
    uint32_t w_src;
    uint32_t h_src;
    uint32_t w_dst;
    uint32_t h_dst;
    uint32_t frame_sz_src;
    uint32_t frame_sz_dst;
    
    char *cp;
    string_t output;
    
    if (argc < 6)
    {
        fprintf(stderr, "useage: %s [input_file] [w_src] [h_src] [w_dst] [h_dst]\n", argv[0]);
        
        return -1;
    }


    w_src   = 0;
    h_src   = 0;
    w_dst   = 0;
    h_dst   = 0;
    cp      = NULL;
    output  = null;
    
    // get input file name from comand line
    ifd = open(argv[1], O_RDONLY);
    if (ifd < 0)
    {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }

    // specify output file name
    sprintf(output.name, "%sx%s_to_%sx%s.yuv", argv[2], argv[3], argv[4], argv[5]);
    ofd = open
            (
             output.name,
             O_WRONLY | O_CREAT | O_TRUNC,
             S_IRUSR
            );
            
    w_src = atoi(argv[2]);
    h_src = atoi(argv[3]);
    w_dst = atoi(argv[4]);
    h_dst = atoi(argv[5]);
    
    frame_sz_src = w_src * h_src * 3 / 2;
    frame_sz_dst = w_dst * h_dst * 3 / 2;
    

	uint8_t *src = malloc(frame_sz_src);
	uint8_t *dst = malloc(frame_sz_dst);

    fprintf(stderr, "Processing: ");
    
	while (1)
	{
		memset(dst, 0, frame_sz_dst);
		
		rd_sz = read(ifd, src, frame_sz_src);
        
        if (rd_sz == frame_sz_src)
        {
            #if 0
            int row = 0;
            uint8_t *p = src;
            uint8_t *q = dst;

            // Y
            for (row = 0; row < 1080; row++)
            {
                memcpy(q, p, 1920);
                p += 1920;
                q += 3840;
            }
            
            // Move to U,V buffer address of original frame
            q += 3840 * 1080;
            
            // U,V
            for (row = 0; row < 540; row++)
            {
                memcpy(q, p, 1920);
                p += 1920;
                q += 3840;
            }
            #endif
            
            rescale
            (
                dst,
                src,
                w_dst,
                h_dst,
                w_src,
                h_src
            );
            
            write(ofd, dst, frame_sz_dst);
        }
        else
        {
            break;
        }
        fputc('.', stderr);
        fflush(stderr);
	}

	close(ifd);
	close(ofd);

    fprintf(stderr, "Done\n");
    fprintf(stderr, "Output file: %s\n", output.name);
    
    return 0;
}

