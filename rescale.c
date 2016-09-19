//
//  rescale.c
//  rescale
//
//  Created by Hank Lee on 9/19/16.
//  Copyright (c) 2016 Hank Lee. All rights reserved.
//

#include <stdint.h>
#include <string.h>

void rescale
(
    uint8_t *src,
    uint8_t *dst,
    uint32_t w_src,
    uint32_t h_src,
    uint32_t w_dst,
    uint32_t h_dst
)
{
    uint8_t *p = src;
    uint8_t *q = dst;

    // Y
    int i;
    for (i = 0; i < h_src; i++)
    {
        memcpy(q, p, w_src);
        p += w_src;
        q += w_dst;
    }

    // Move to U,V buffer address of original frame
    q = dst + w_dst * h_dst;
    
    // U,V
    for (i = 0; i < h_src / 2; i++)
    {
        memcpy(q, p, w_src);
        p += w_src;
        q += w_dst;
    }
}
