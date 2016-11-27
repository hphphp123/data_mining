//
//  K_means.cpp
//  leetcode
//
//  Created by Lihaifeng on 2016/11/18.
//  Copyright © 2016年 Lihaifeng. All rights reserved.
//

#include "K_means.hpp"

void LoadData(char filename[]){
    
}

void InitializeCoreNode(){
    //initialize CoreNode
    for (int i = 0; i < sampleNum; i ++) {
        sample[i].Clas = -1;
    }
    for (int i = 0; i < k; i ++) {
        for (int j = 0; j < dimension; j ++) {
            coreNode[i].address[j] = rand() / (RAND_MAX+0.1);  //产生0-1的随机数
        }
    }
    
    
}

//欧氏距离
double distance(NODE t1, NODE t2){
    double ans = 0;
    for (int i = 0; i < dimension; i ++) {
        ans += (t1.address[i] - t2.address[i]) * (t1.address[i] - t2.address[i]);
    }
    ans = pow(ans, 1.0/(double)dimension);
    return ans;
}


int classify(NODE tmp){
    double mini = 9999999;
    double miniClass = 0;
    for (int i = 0; i < k; i ++) {
        double tmpLen = distance(tmp, coreNode[i]);
        if(tmpLen < mini){
            mini = tmpLen;
            miniClass = i;
        }
    }
    return miniClass;
}

void K_Means(){
    int change = 1;
    while(true){
        memset(classLen,0,sizeof(classLen));
        change = 0;
        for (int i = 0; i < sampleNum; i ++) {
            int Cla = classify(sample[i]);
            if(Cla != sample[i].Clas)
                change = 1;
            sample[i].Clas = Cla;   //将其分为第Cla类
            classLen[Cla] ++;
            
        }
        if(change == 0)
            break;
        
        printf("...\n");
        //更新coreNode
        memset(coreNode,0,sizeof(coreNode));
        for (int i = 0; i < sampleNum; i ++) {
            for (int j = 0; j < dimension; j ++) {
                coreNode[sample[i].Clas].address[j] += sample[i].address[j];
            }
        }
        for (int i = 0; i < k; i ++) {
            for (int j = 0; j < dimension; j ++) {
                coreNode[i].address[j] /= classLen[i];
            }
            printf("\n");
            
            
        }
    }
}

void outPut(){
    
}


int main()
{
    char filename[50];
    scanf("%s",filename);
    LoadData(filename);
    
    
    InitializeCoreNode();
    K_Means();
    outPut();
    
    
    return 0;
}
