#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

struct contact{
    char name[50];
    char phone[50];
};

void search();
void insert();
void update();
void delete();

const char *originalFileName="./contact.csv";
const char *newFileName="./2015025732_박지윤.csv";

char choice=0;
char find[100]; //update

int main()
{
     
    while(1)
    {
        printf("2019 주소록 프로그램\n");
        printf("---------------\n");
        printf("(1) 전화번호 검색\n");
        printf("(2) 회원 정보 입력\n");
        printf("(3) 회원 정보 수정\n");
        printf("(4) 회원 정보 삭제\n");
        printf("(5) 종료\n");
        printf("---------------\n");

        choice=getchar();
        fflush(stdin);

        switch(choice)
        {
        case '1': 
            search();
            break;
        case '2':
            insert();
            break;
        case '3':
            update();
            break;
        case '4':
            delete();
            break;
        case '5':
            return 0;
            break;
        }
        break;
    }
    return 0;
}

void search(){

    FILE *rf, *cf;
    struct contact addr[1000];
    char tmpStr[100];
    char find[50];
    int i,sel=0;
    int try, new=0;
    char *tok;


    rf=fopen(originalFileName,"r");
    cf=fopen(newFileName,"r");
    
    printf("검색할 이름을 입력해주세요 :");
    scanf("%s", &find);
    fflush(stdin);

 //-------------------------------------------- contact.csv 에서 1차 검색 
    
    while(!feof(rf))
    {
        fscanf(rf,"%s\t", &tmpStr); //reading csv file...
    
        tok=strtok(tmpStr,",");
        strcpy(addr[i].name, tok);


        if(strcmp(addr[i].name, find)==0) {
            tok=strtok(NULL,",");
            strcpy(addr[i].phone,tok);
            printf("%s님의 핸드폰 번호는 %s 입니다.\n",find, addr[i].phone); 
            try=1;
            break;
        } //전체 일치
        

        if((!strncmp(addr[i].name, find,6))&&(strlen(find)<=6)){       
            printf(addr[i].name);
            printf("\n");
            i++;
            try=1;
        }// 첫 번째, 두 번째 글자 일치

        if((!strncmp(addr[i].name, find,3))&&(strlen(find)<=3)){       
            printf(addr[i].name);
            printf("\n");
            i++;
            try=1;
        }// 첫 번째 글자 일치
        

    }
    
    fclose(rf);

 //-------------------------------------------- 이름_학번.csv 에서 2차 검색 

    while(!feof(cf))
    {
        fscanf(cf,"%s\t", &tmpStr); 
    
        tok=strtok(tmpStr,",");
        strcpy(addr[i].name, tok);


        if(strcmp(addr[i].name, find)==0) {
            tok=strtok(NULL,",");
            strcpy(addr[i].phone,tok);
            printf("%s님의 핸드폰 번호는 %s 입니다.\n",find, addr[i].phone); 
            try=1;
            new=1;
            break;
        } //전체 일치
        

        if((!strncmp(addr[i].name, find,6))&&(strlen(find)<=6)){       
            printf(addr[i].name);
            printf("\n");
            i++;
            try=1;
            new=1;
        }// 첫 번째, 두 번째 글자 일치

        if((!strncmp(addr[i].name, find,3))&&(strlen(find)<=3)){       
            printf(addr[i].name);
            printf("\n");
            i++;
            try=1;
            new=1;
        }// 첫 번째 글자 일치
        

    }
    
    fclose(cf);

    if(try != 1) {
        printf("검색 실패했습니다.\n");
        printf("등록을 진행하시겠습니까? (1 예 | 2 아니오)\n");
            scanf("%d", &sel);

            if(sel !=1 || sel !=2){
                switch(sel){
                    case 1:
                        insert();
                        break;

                    case 2:
                        exit(0);
                        break;
                }
            }
        printf("재검색하시겠습니까? (1 예 | 2 아니오)\n");
            scanf("%d", &sel);

            if(sel !=1 || sel !=2){
                switch(sel){
                    case 1:
                        search();
                        break;

                    case 2:
                        exit(0);
                        break;
                }
            }


    }

    if(new ==1){
        printf("수정 / 삭제 하시겠습니까? (1 수정 | 2 삭제 | 3 종료)\n");
            scanf("%d", &sel);

            if(sel !=1 || sel !=2){
                switch(sel){
                    case 1:
                        update();
                        break;
                    case 2:
                        delete();
                    case 3:
                        exit(0);
                        break;
                }
            }
    }
}
 
void insert(){
    
    FILE *wf;
    struct contact addr ={"" ""};
    char str[100];

    wf = fopen(newFileName, "a");

    printf("등록할 회원 정보를 입력해주세요.\n 이름 : ");
    scanf("%s", &str);
    strcpy(addr.name, str);

    printf("핸드폰 번호 : ");
    scanf("%s", &str);
    strcpy(addr.phone, str);

    if(!(addr.name == NULL && addr.phone == NULL)){
        fprintf(wf,"%s,%s\n", addr.name, addr.phone);
        printf("성공적으로 추가되었습니다.\n");
    }else printf("취소되었습니다.\n");


    fclose(wf);
}

void update(){

    FILE *rf, *wf;
    struct contact addr[1000];
    char tmpStr[100];
    char find[50];
    int i,count,sel,try=0;
    char *tok;
    char name[100], phone[100];
    int up_line;


    rf=fopen(newFileName,"r");

    if(rf == NULL){
        perror("\n 파일을 찾을 수 없습니다.\n");
        return;
    }
    
    printf("수정할 이름을 입력해주세요 :");
    scanf("%s", &find);
    fflush(stdin);

  
    while(!feof(rf))
    {
        fscanf(rf,"%s\t", &tmpStr); //reading csv file...
    
        tok=strtok(tmpStr,",");
        strcpy(addr[i].name, tok);


        if(strcmp(addr[i].name, find)==0) 
        { //검색어와 일치할 경우
            tok=strtok(NULL,",");
            strcpy(addr[i].phone,tok);
            printf("%s님의 핸드폰 번호는 %s 입니다.\n",find, addr[i].phone); 

            printf("변경할 내용을 선택하세요. (1 이름 | 2 핸드폰번호)\n");
            scanf("%d", &sel);

            if(sel !=1 || sel !=2){
                switch(sel){
                    case 1:
                        printf("변경 후 이름을 입력하세요 : ");
                        scanf("%s", &name);
                        strcpy(addr[i].name, name); //해당 값을 수정
                        printf("변경되었습니다.\n");
                        
                        i++;
                        count++;
                        break;

                    case 2:
                        printf("변경 후 핸드폰 번호를 입력하세요 : ");
                        scanf("%s",&phone);
                        strcpy(addr[i].phone, phone);
                        printf("변경되었습니다.\n");

                        i++;
                        count++;
                        break;
                }
            }
            
            try=1;
            continue;
        } 

        tok=strtok(NULL,",");
        strcpy(addr[i].phone,tok);

        i++; //구조체 배열 ++
        count++; //입력횟수 ++
    }
    
    fclose(rf);

    wf=fopen(newFileName,"w");

    for(int j=0; j<count; j++){
        fprintf(wf, "%s,%s\n", addr[j].name, addr[j].phone);
    }

    fclose(wf);
    
    
    if(try != 1) printf("실패했습니다.\n");

}

void delete(){

   
    FILE *rf, *wf;
    struct contact addr[1000];
    char tmpStr[100];
    char find[100];
    int i,count,sel,try=0;
    char *tok;
    int del_line;


    rf = fopen(newFileName,"r");

    if(rf == NULL){
        perror("\n 파일을 찾을 수 없습니다.\n");
        return;
    }

    printf("삭제할 이름을 입력해주세요 :");
    scanf("%s", &find);
    fflush(stdin);

    while(!feof(rf))
    {
        fscanf(rf,"%s\t", &tmpStr); //reading csv file...
    
        tok=strtok(tmpStr,",");
        strcpy(addr[i].name, tok);

        if(strcmp(addr[i].name, find)==0) 
        {
            tok=strtok(NULL,",");
            strcpy(addr[i].phone,tok);
            printf("%s님의 핸드폰 번호는 %s 입니다.\n",find, addr[i].phone); 

            printf("삭제하시겠습니까? (1 예| 2 아니오)\n");
            scanf("%d", &sel);

            if(sel !=1 || sel !=2){
                switch(sel){
                    case 1:
                        strcpy(addr[i].name,"");
                        strcpy(addr[i].phone,"");
                  
                        printf("삭제되었습니다.\n");

                        i++;
                        count++;
                        break;
                    case 2:
                        exit(0);
                        break;
                }   
            } 
            
            try=1;
            continue;
        }

        tok= strtok(NULL,",");
        strcpy(addr[i].phone,tok);

        i++;
        count++;
    }

    fclose(rf);

    wf=fopen(newFileName,"w");
                
    for(int j=0; j<count+2; j++){
        if(strcmp(addr[j].name, "") != 0){
            fprintf(wf,"%s,%s\n", addr[j].name, addr[j].phone);
        }
    }
    fclose(wf);

    if(try != 1) printf("실패했습니다.\n");
        
}

    



