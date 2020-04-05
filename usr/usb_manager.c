#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <linux/types.h>
#include <fcntl.h>
#include <linux/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>
#include <sys/mount.h>
#include "../usr/usb_manager.h"
void del_current_usb(){
/*
    FILE *fp;
    char readline[100];
    char *token;
    int num;
    char ch[2];
    char tmp1[20]="usb";
    char tmp2[1024]="/sys/bus/usb/devices/";
    char tmp3[20]="/authorized";
    fp=popen("lsusb","r");
    int fd;
    if(fp==NULL){

        perror("执行命令失败\n");
        exit(0);
    }
    while(fgets(readline,100,fp)!=0){

        if(strstr(readline,"Flash Drive")!=NULL){

               token=strtok(readline," ");
               token=strtok(NULL," ");
               num=atoi(token);
               int fd;
               sprintf(ch,"%d",num);
               strcat(tmp1,ch);
               strcat(tmp2,tmp1);
               strcat(tmp2,tmp3);
               fd=open(tmp2,O_RDWR);
               if(fd<0){

                   printf("%d\n",errno);
               }
                write(fd,"0",1);
                sleep(1);
                write(fd,"1",1);
        }
    }
    
      //struct passwd *pwd=getpwuid(getuid());
*/
    char str[20]="/media/";
    DIR *dir;
    struct dirent *dd;
    dir=opendir(str);
    if(dir!=NULL){
    while((dd=readdir(dir))!=NULL){
    if(strcmp(dd->d_name,".")!=0&&strcmp(dd->d_name,"..")!=0){

     char str2[50]="/media/";
     DIR *dirp;
     struct dirent *dp;
     strcat(str2,dd->d_name);
     //printf("%s\n",str2);
     dirp=opendir(str2); 
     if(dirp!=NULL){
         while((dp=readdir(dirp))!=NULL){

             if(strcmp(dp->d_name,".")!=0&&strcmp(dp->d_name,"..")!=0){
            
             char str1[200]="/media/";
     //        strcat(str1,pwd->pw_name);
             strcat(str1,dd->d_name);
             strcat(str1,"/'");
             strcat(str1,dp->d_name);
             strcat(str1,"'");
             char str5[250]="mountpoint ";
             strcat(str5,str1);
             //printf("%s\n",str5);
             FILE *file;
             char str6[100];
             file=popen(str5,"r");
             while(fgets(str6,100,file)!=NULL){
            if(strstr(str6,"不是")==NULL||strstr(str6,"not")){
             char str4[50]="eject ";
             strcat(str4,str1);
             //printf("%s\n",str4);
             system(str4);
            // umount(str1);
            
     }
     }
     }
     }
     }else {
         printf("%d\n",errno);
     }
     
             }
        }
    }
   // return num;
}
void del_current_net()
{
        DIR *dir;
        struct dirent *ptr;
        if((dir=opendir("/sys/class/net"))==NULL){

            perror(" open dir error...");
            exit(1);
        }

        while((ptr=readdir(dir))!=NULL)
        {
            if(strcmp(ptr->d_name,".")==0||strcmp(ptr->d_name,"..")==0)
            {
                continue;
            }else {

                if(strcmp(ptr->d_name,"lo")!=0&&strcmp(ptr->d_name,"enp2s0")!=0&&strcmp(ptr->d_name,"wlp4s0")!=0){

                       char str1[1024]="/sys/class/net/";
                       char readline[1024];
                       char *str2="/device/uevent";
                       char *str3="/device/authorized";
                       char str4[1024]="/sys/class/net/";
                       int result;
                       strcat(str1,ptr->d_name);
                       strcat(str1,str2);
                       result=access(str1,F_OK);
                        if(result==0){
                       //printf("%s\n",str1);
                       FILE *file;
                       file=fopen(str1,"r");
                       if(file==NULL){
                           perror("open error");
                       }
                       while(fgets(readline,1024,file)!=0){
                            //printf("%s\n",readline);
                           if(strstr(readline,"usb_interface")!=NULL){
                              //  printf("hello wolrd \n");
                                strcat(str4,ptr->d_name);
                                strcat(str4,str3);
                               // printf("%s\n",str4);
                                int fd;
                                //chmod(str4,0660);
                                fd=open(str4,O_RDWR);
                                if(fd<0){
                                    printf("errnonum:%d\n",errno);
                                }

                                write(fd,"0",1);
                           }
                       }
                        }
                }      
                   
            }
}
}

void usb_control(char *type,int flag){


    int fd;
    int rs;
    if(strcmp(type,"usb-storage")!=0&&strcmp(type,"usb-net")!=0){
                    
            perror("parameter error");
            exit(0);
    }
    rs=access("/etc/udev/rules.d/99-myudisks2.rules",F_OK);
    if(rs!=0){
    system("touch /etc/udev/rules.d/99-myudisks2.rules");

    }
  const char *net_rules="echo \"SUBSYSTEM==\\\"net\\\",ACTION==\\\"add|change\\\",SUBSYSTEMS==\\\"usb\\\", RUN+=\\\"/bin/sh -c 'echo 0 >/sys\\\$DEVPATH/device/authorized'\\\"\" >> /etc/udev/rules.d/99-myudisks2.rules";
  const char *storage_rules="echo \"SUBSYSTEM==\\\"block\\\",ACTION==\\\"add|change\\\",DRIVERS==\\\"usb-storage\\\",SUBSYSTEMS==\\\"usb\\\",ENV{UDISKS_IGNORE}=\\\"1\\\", RUN+=\\\"/bin/sh -c 'rm -rf /dev/%k'\\\"\" >> /etc/udev/rules.d/99-myudisks2.rules";
    if(strcmp(type,"usb-storage")==0){
        
        if(flag==0){
            system(storage_rules);
            del_current_usb();
            system("/sbin/udevadm control --reload");
        }else if(flag>0){
            system("sed -i \"/SUBSYSTEM==\\\"block\\\",ACTION==\\\"add|change\\\"/d\" /etc/udev/rules.d/99-myudisks2.rules");
            system("/sbin/udevadm control --reload");
        }            
    }else if(strcmp(type,"usb-net")==0){

        if(flag==0){
            system(net_rules);
            del_current_net();
            system("/sbin/udevadm control --reload");
        }else if(flag>0){
           system("sed -i \"/SUBSYSTEM==\\\"net\\\",ACTION==\\\"add|change\\\"/d\" /etc/udev/rules.d/99-myudisks2.rules");
           system("/sbin/udevadm control --reload");
        }
    }
}


int main(int argc,char **argv){

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
