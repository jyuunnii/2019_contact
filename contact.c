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
    int i,count=0;
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
            count=0;
            break;
        } //전체 일치
        

        if((!strncmp(addr[i].name, find,6))&&(strlen(find)>3)){       
            printf(addr[i].name);
            printf("\n");
            i++;
        }// 첫 번째 글자 일치

        if((!strncmp(addr[i].name, find,3))&&(strlen(find)<=3)){       
            printf(addr[i].name);
            printf("\n");
            i++;
        }// 첫 번째, 두 번째 글자 일치

    }
    
    fclose(rfp);

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
    int i,count,sel=0;
    char *tok;
    char name[100];
    char phone[100];
    int up_line;


    rfp=fopen(newFileName,"r");
    
    printf("수정할 이름을 입력해주세요 :");
    scanf("%s", &find);
    fflush(stdin);
  
    while(!feof(rfp))
    {
        fscanf(rfp,"%s\t", &tmpStr); //reading csv file...
    
        tok=strtok(tmpStr,",");
        strcpy(addr[i].name, tok);


        if(strcmp(addr[i].name, find)==0) { //검색어와 일치할 경우
            up_line=i;
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
                        strcpy(addr[up_line].name, name);
                        break;
                    case 2:
                        printf("변경 후 핸드폰 번호를 입력하세요 : ");
                        scanf("%s",&phone);
                        strcpy(addr[up_line].phone, phone);
                        break;
                }

                wfp=fopen(newFileName,"w");

                for(int j=0; j<count+1; j++){
                    fprintf(wfp, "%s,%s\n", addr[j].name, addr[j].phone);
                }
                fclose(wfp);
            }


            break;
        } 

        tok=strtok(NULL,",");
        strcpy(addr[i].phone,tok);

        i++;
        count++;
    }
    
    fclose(rfp);
}

void delete(){

    FILE *rfp, *wfp;
    struct contact addr[1000];
    char tmpStr[100];
    char *tok;
    int del_line, count=0;
    int i,j,sel=0;
    char find[100];

    rfp = fopen(newFileName,"r");

    printf("삭제할 이름을 입력해주세요. \n");
    scanf("%s", &find);
    fflush(stdin);

    fscanf(rfp,"%s %s", addr[i].name,addr[i].phone);

    if(strcmp(addr[i].name, find)==0) {
        tok=strtok(NULL,",");
        strcpy(addr[i].phone,tok);
        printf("%s님의 핸드폰 번호는 %s 입니다./n",find, addr[i].phone); 
        j=i;
        i++;
    } //전체 일치
    
    fclose(rfp);

    printf("삭제하시겠습니까? (1 예| 2 아니오)\n");
    scanf("%d", &sel);

    if(sel !=1 || sel !=2){
        switch(sel){
            case 1:
                wfp = fopen(newFileName, "w");
                strcpy(addr[j].name,"");
                strcpy(addr[j].phone,"");
                printf("삭제되었습니다.\n");
                break;
            case 2:
                break;
        }
        fclose(wfp);

    
    }











    // for(int i=0; i<100; i++){
    //     if(fscanf(rfp, "%s %s", &addr[i].name, &addr[i].phone) == EOF){
    //         break;
    //     }
    //     if(strcmp(addr[i].name,find)==0){
    //         del_line=i;
    //     }
    //     count++;
    // }

    // fclose(rfp);



    // FILE *rfp, *wfp, *wwfp;
    // struct contact addr[100];
    // char name[50], phone[50];
    // char find[100];
    // int del_line,count, cnt=0;
    
    // char str[100];

    // rfp = fopen(newFileName,"r");

    // if(rfp == NULL){
    //     puts("\n No file\n");
    //     return;
    // }

    // printf("삭제할 이름을 입력해주세요. \n");
    // scanf("%s", &find);

    // for(int i=0; i<sizeof(addr); i++){
    //     if(fscanf(rfp, "%s %s", &addr[i].name, &addr[i].phone) == EOF){
    //         break;
    //     }
    //     if(strcmp(addr[i].name,find)==0){
    //         del_line=i;
    //     }
    // }


    // for(int i=0; i<10;i++){
    //     if(fscanf(rfp, "%s %s",&name,&phone)==EOF) break;

    //     if(i+1 != del_line){
    //         strcpy(addr[i].name, name);
    //         strcpy(addr[i].phone,phone);

    //         count++;
    //     }else{
    //         strcpy(addr[i].name,"");
    //         strcpy(addr[i].phone,"");
    //     }
    // }
    // fclose(rfp);

    // wfp=fopen(newFileName,"w");

    // for(int j=0; j<=count;j++){
    //     if(strcmp(addr[j].name, "")!= 0){
    //         fprintf(wfp, "%s %s\n", addr[j].name, addr[j].phone);
    //     }
    // }
    // fclose(wfp);
        
}

    



