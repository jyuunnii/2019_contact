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

void getinfo();
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
            getinfo();
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

void getinfo(){

    FILE *rfp;
    struct contact addr[1000];
    char tmpStr[100];
    char find[50];
    int i,try=0;
    char *tok;


    rfp=fopen(originalFileName,"r");
    
    printf("검색할 이름을 입력해주세요 :");
    scanf("%s", &find);
    fflush(stdin);
  
    while(!feof(rfp))
    {
        fscanf(rfp,"%s\t", &tmpStr); //reading csv file...
    
        tok=strtok(tmpStr,",");
        strcpy(addr[i].name, tok);


        if(strcmp(addr[i].name, find)==0) {
            tok=strtok(NULL,",");
            strcpy(addr[i].phone,tok);
            printf("%s님의 핸드폰 번호는 %s 입니다.",find, addr[i].phone); 
            try=1;
            break;
        } //전체 일치
        

        if((!strncmp(addr[i].name, find,6))&&(strlen(find)>3)){       
            printf(addr[i].name);
            printf("\n");
            i++;
            
            try=1;
        }// 첫 번째 글자 일치

        if((!strncmp(addr[i].name, find,3))&&(strlen(find)<=3)){       
            printf(addr[i].name);
            printf("\n");
            i++;

            try=1;
        }// 첫 번째, 두 번째 글자 일치

    }
    
    fclose(rfp);

    if(try != 1) printf("실패했습니다.\n");

}
 
void insert(){
    
    FILE *wfp;
    struct contact addr ={"" ""};
    char str[100];

    wfp = fopen(newFileName, "a");

    printf("등록할 회원 정보를 입력해주세요.\n 이름 : ");
    scanf("%s", &str);
    strcpy(addr.name, str);

    printf("핸드폰 번호 : ");
    scanf("%s", &str);
    strcpy(addr.phone, str);

    if(!(addr.name == NULL && addr.phone == NULL)){
        fprintf(wfp,"%s,%s\n", addr.name, addr.phone);
        //fprintf(wfp,"%s","\n");
        printf("성공적으로 추가되었습니다.\n");
    }else printf("취소되었습니다.\n");


    fclose(wfp);
}

void update(){

    FILE *rfp, *wfp;
    struct contact addr[1000];
    char tmpStr[100];
    char find[50];
    int i,count,sel,try=0;
    char *tok;
    char name[100], phone[100];
    int up_line;


    rfp=fopen(newFileName,"r");

    if(rfp == NULL){
        perror("\n 파일을 찾을 수 없습니다.\n");
        return;
    }
    
    printf("수정할 이름을 입력해주세요 :");
    scanf("%s", &find);
    fflush(stdin);

  
    while(!feof(rfp))
    {
        fscanf(rfp,"%s\t", &tmpStr); //reading csv file...
    
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
                        
                        i++;
                        count++;
                        break;

                    case 2:
                        printf("변경 후 핸드폰 번호를 입력하세요 : ");
                        scanf("%s",&phone);
                        strcpy(addr[i].phone, phone);

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
    
    fclose(rfp);

    wfp=fopen(newFileName,"w");

    for(int j=0; j<count; j++){
        fprintf(wfp, "%s,%s\n", addr[j].name, addr[j].phone);
    }

    fclose(wfp);
    
    
    if(try != 1) printf("실패했습니다.\n");

}

void delete(){

   
    FILE *rfp, *wfp;
    struct contact addr[1000];
    char tmpStr[100];
    char find[100];
    int i,count,sel,try=0;
    char *tok;
    int del_line;


    rfp = fopen(newFileName,"r");

    if(rfp == NULL){
        perror("\n 파일을 찾을 수 없습니다.\n");
        return;
    }

    printf("삭제할 이름을 입력해주세요 :");
    scanf("%s", &find);
    fflush(stdin);

    while(!feof(rfp))
    {
        fscanf(rfp,"%s\t", &tmpStr); //reading csv file...
    
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

    fclose(rfp);

    wfp=fopen(newFileName,"w");
                
    for(int j=0; j<count+2; j++){
        if(strcmp(addr[j].name, "") != 0){
            fprintf(wfp,"%s,%s\n", addr[j].name, addr[j].phone);
        }
    }
    fclose(wfp);

    if(try != 1) printf("실패했습니다.\n");
        
}

    



