//
//  rescale.h
//  rescale
//
//  Created by Hank Lee on 9/19/16.
//  Copyright (c) 2016 Hank Lee. All rights reserved.
//

#ifndef ___RESCALE___
#define ___RESCALE___

void rescale
(
        uint8_t *dst,
  const uint8_t *src,
        uint32_t w_dst,
        uint32_t h_dst,
        uint32_t w_src,
        uint32_t h_src
);

#endif