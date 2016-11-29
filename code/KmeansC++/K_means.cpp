//
//  K_means.cpp
//  leetcode
//
//  Created by Lihaifeng on 2016/11/18.
//  Copyright © 2016年 Lihaifeng. All rights reserved.
//

#include "K_means.hpp"




void LoadData(char filename[]){
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        return ;
    }
    char line[1044];
    const char *d = ",\r\n";
    char *p;
    int nnn = -1;
    while(fgets(line, sizeof(line), fp)) {
        
        if( nnn == -1){
            nnn ++;
            continue;
        }
//        printf("%s",line);
        p = strtok(line, d);
        int index = 0;
        while(p)
        {
//            printf("%s to ",p);
//            printf("%lf\n",atof(p)); //读出的小数
            sample[nnn].address[index ++] = atof(p);
            p=strtok(NULL,d);
        }
        nnn ++;
    }
    fclose(fp);
}

void InitializeCoreNode(){
    //initialize CoreNode
    for (int i = 0; i < sampleNum; i ++) {
        sample[i].Clas = 0;
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
            
        }
    }
}

void outPut(char outfile[]){
    FILE *fp = fopen(outfile, "w");
    if(fp == NULL) {
        return ;
    }
    char temp[100];
    memset(temp, 0, sizeof(temp));
    temp[1] = '\r';
    temp[2] = '\n';
    for (int i = 0; i < sampleNum; i ++) {
        temp[0] = sample[i].Clas + '0';
        fputs(temp,fp);
    }
    
    fclose(fp);
}


int main()
{
    char filename[1000] = "/Users/haifeng/Documents/国科大/课程/数据挖掘/project/data_mining/OutLRFMCData.csv";
    char outfile[] = "/Users/haifeng/Documents/国科大/课程/数据挖掘/project/data_mining/K_MeansOutFile.csv";
//    scanf("%s",filename);
    LoadData(filename);
    InitializeCoreNode();
    K_Means();
    outPut(outfile);
    printf("success!\n");
    
    return 0;
}