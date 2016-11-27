//
//  K_means.hpp
//  leetcode
//
//  Created by Lihaifeng on 2016/11/18.
//  Copyright © 2016年 Lihaifeng. All rights reserved.
//

#ifndef K_means_hpp
#define K_means_hpp

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#endif /* K_means_hpp */

#define dimension 3
#define sampleNum 10
#define k 3


typedef struct node{
    double address[dimension];
    int Clas;
}NODE;

int classLen[k];
NODE sample[sampleNum];
NODE coreNode[k];
