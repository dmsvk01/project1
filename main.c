#include <stdio.h>
#include "requisition.h"

/*
필수구현내용 #1
메인:전체 메뉴 중 파일을 읽고 쓰는 내용이 포함된 모든 메뉴의 기능 구현
라이브러리 : 위 메뉴와 관련된 모든 라이브러리함수 구현

필수구현내용 #2
1단계, 2단계에 구현된 라이브러리함수 내에 디버그 매크로 삽입(최소 10군데이상)
최종 실행파일을 2개의 버전으로 만들도록 Makefile을 변경하여 빌드할 것.
-기존 실행 파일
-디버그 매크로 포함된 실행파일 (target명에_debug를붙임)

*/
void create_card(); //1.요청서입력
void read_card(); //2.요청서 검색(개별, 날짜, 지역별)
void list_card(); // 3.전체 요청서 읽기
void rerrange(); // 4.최적화
void update_card(); // 5.요청서 업데이트
void delete_card(); // 6.요청서삭제
void load_card(); // 7.요청서 불러오기
void save_card(); // 8.요청서 저장.
void delete_card_all(); // 9.요청서 전체삭제

int main(){
    int n;
    while(1){
        printf("menu : 1.요청서 입력 2.요청서 검색(개별, 날짜, 지역별) 3.전체 요청서 읽기 4.최적화 5.요청서업데이트 6.요청서삭제 7.요청서 불러오기 8.요청서 저장 9.요청서 전체삭제 0.종료\n");
        scanf("%d", &n);
        switch(n){
            case 1:
                create_card();
                break;
            
            case 2: 
                read_card();
                break;

            case 3:  
                list_card();
                break;
            case 4: 
                rerrange();
                break;
            case 5: 
                update_card();
                break;
            case 6: 
                delete_card();
                break;
            case 7: 
                load_card();
                break;
            case 8: 
                save_card();
                break;
            case 9: 
                delete_card_all();
                break;
            case 0:
                printf("exit ...\n");
                return 0;
        }
    }
}

void create_card(){
    int age, space;
    char name[80], city[80], date[80], phone[80];
    if(!r_available()){
        printf("요청서를 저장할 공간이 부족합니다.\n\n");
        return ;
    }else{
        printf("날짜는? ");
        scanf("%s", date);
        printf("이름은? ");
        scanf("%s", name);
        printf("나이는? ");
        scanf("%d", &age);
        printf("전화번호는? ");
        scanf("%s", phone);
        printf("주소는? ");
        scanf("%s", city);
        printf("평수는? ");
        scanf("%d", &space);
        r_create(date, name, age, phone, city, space);
    }
}


void read_card(){
    int n;
    char name[40];
    char date[40];
    char city[40];
    T_request* p[MAX];
    int size=0;
    printf("1. 이름으로 검색 2. 날짜별 검색 3. 지역별 검색>> ");
    scanf("%d", &n);
    if(n==1){
        printf("이름을 입력하세요. >> ");
        scanf("%s", name);
        if(r_search_by_name(name)==NULL){
            printf("동일한 이름을 찾지 못했습니다.\n\n");
            return ;
        }else{
            p[0]=r_search_by_name(name);
            printf("--------------------\n");
            printf("%s",r_to_string(p[0]));
            printf("--------------------\n");
            return ;
        }
    }else if(n==2){
        printf("날짜를 입력하세요. >> ");
        scanf("%s", date);
        if(r_search_by_date(date)==NULL){
            printf("%s에 해당하는 요청서를 찾지 못했습니다.\n\n", date);
            return ;
        }else{
            r_get_all_by_date(p, date, &size);
            printf("%s날짜의 요청서 리스트입니다.\n", date);
            for(int i=0; i<size; i++){
                printf("[%d]. %s", i+1, r_to_string(p[i]));
            }
        }
    }else if(n==3){
        printf("지역를 입력하세요. >> ");
        scanf("%s", city);
        if(r_search_by_city(city)==NULL){
            printf("%s지역에 해당하는 요청서를 찾지 못했습니다.\n\n", city);
            return ;
        }else{
            r_get_all_by_city(p, city, &size);
            printf("%s지역의 요청서 리스트입니다.\n", city);
            for(int i=0; i<size; i++){
                printf("[%d]. %s", i+1, r_to_string(p[i]));
            }
        }
    }else{
        printf("잘못입력하셨습니다.\n\n");
        return ;
    }
}

void list_card(){
   int size=r_count();
   T_request* p[MAX];
   r_get_all(p);
   printf("\n모든요청서\n");
   printf("----------------------\n");
   for(int i=0; i<size; i++){
       T_request* t = p[i];
       printf("%d. %s", i+1, r_to_string(t));
   }
   printf("----------------------\n\n");
}

void rerrange(){
    r_rerrange();
    printf("최적화가 완료되었습니다.\n\n");
}

void update_card(){
    int age, space;
    char name[80], city[80], date[80], phone[80];
    T_request* p;
    printf("이름을 입력하세요 > ");
    scanf("%s", name);
    if(r_search_by_name(name)==NULL){
        printf("해당하는 이름이 없습니다.\n");
        return ;
    }else{
        p = r_search_by_name(name);
        printf("날짜는? ");
        scanf("%s", date);
        printf("나이는? ");
        scanf("%d", &age);
        printf("전화번호는? ");
        scanf("%s", phone);
        printf("주소는? ");
        scanf("%s", city);
        printf("평수는? ");
        scanf("%d", &space);
        r_update(p, date, name, age, phone, city, space);
        printf("정보수정이 완료되었습니다\n\n");
   }
}

void delete_card(){
    char name[30];
    T_request* p;
    printf("삭제할 요청서의 이름을 입력하세요 > ");
    scanf("%s", name);
    if(r_search_by_name(name)==NULL){
        printf("%s의 요청서를 찾을 수 없습니다.\n", name);
        return ;
    }else{
        p=r_search_by_name(name);
        r_delete(p);
        printf("삭제되었습니다.\n");
    }

}

void load_card(){
    FILE* f = fopen("request.txt", "r");
    int age, space;
    char name[80], city[80], date[80], phone[80];
    int i=0;
    printf("읽어들인 정보.\n");
    while(!feof(f)){
        if(!r_available()){
            printf("저장공간이 부족합니다.\n");
            break;
        }
        int n = fscanf(f, "%s %s %d %s %s %d\n", date, name, &age, phone, city, &space);
        if(n<6) break;
        r_create(date, name, age, phone, city, space);
        printf("%s의 요청서를 읽었습니다\n", name);
        i++;
    }
    printf(" 총 %d개의 요청서를 불러왔습니다.\n", i);
    printf(" 현제 요청서 갯수는 %d개 입니다.\n\n", r_count());

}

void save_card(){
    /*
    파일열고
    모든구조체 모아서
    파일에 쓱삭.
    */
    FILE* f = fopen("request.txt", "a+");
    T_request* p[MAX];
    r_get_all(p);
    int size = r_count();
    for(int i=0; i<size; i++){
        fprintf(f, "%s", r_to_string_save(p[i]));
    }
    printf("\n\n%d개의 요청서가 저장되었습니다.\n\n", size);
    fclose(f);
}

void delete_card_all(){
    r_delete_all();
    printf("전체삭제 되었습니다\n\n");
}
