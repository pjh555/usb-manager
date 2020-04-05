#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../usr/usb_manager.h"
int main(int argc,char **argv)
{
    if(argc==3){

        if((strcmp("usb-storage",argv[1])==0)||(strcmp("usb-net",argv[1])==0)){

            if(atoi(argv[2])==0||atoi(argv[2])==1){
            //printf("%d,%s,%d\n",argc,argv[1],atoi(argv[2]));
            usb_control(argv[1],atoi(argv[2]));

            }else{
                perror("参数错误\n");
                exit(0);
            }
        }else{
            perror("参数错误\n");
            exit(0);
        }

    }else{

        perror("参数错误\n");
        exit(1);
    }
    return 0;
}

