#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10 // 저장가능한 요청서 최대 갯수.

typedef struct request{
    char date[80];
    char name[80];
    int age;
    char phone[80];
    char city[80];
    int space;
}T_request;



//int r_sum_sales 전체구조체배열에서 금액의 합계를 리턴//void delete_all() 모든구조체 포인터 NULL로 만들기


int r_available(); // 추가가능한 공간 있는지 확인
int r_first_available(); // 추가가능한 가장 빠른 인덱스
int r_count(); // 생성된 요청서 갯수
T_request* r_search_by_name(char* name);//이름일치하는 요청서 구조체 반환
T_request* r_search_by_date(char* t_date);//이름일치하는 요청서 구조체 반환(동일한 날짜가 있는지 없는지 확인용)
T_request* r_search_by_city(char* t_city);//지역일치하는 요청서 구조체들 반환
void r_get_all_by_city(T_request* a[], char* city, int *size); // 구조체 배열과 지역을 받아서 지역일치하는 요청서구조체들을 구조체배열에 차곡차곡넣기.
void r_get_all_by_date(T_request* a[], char* date, int *size); // 구조체 배열과 날짜를 받아서 날짜일치하는 요청서구조체들을 구조체배열에 차곡차곡넣기.
void r_create(char* t_date, char* t_name, int t_age, char* t_phone, char* t_city, int t_space); // 요청서 정보받아서 하나 생성
void r_update(T_request* p, char* t_date, char* t_name, int t_age, char* t_phone, char* t_city, int t_space); // 요청서 정보받아서 업데이트, 정보수정
void r_delete(T_request* p); // p과같은 구조체찾아서 삭제.(NULL)
void r_delete_all(); // 요청서 전체삭제
char* r_to_string(T_request* T); // 구조체 하나받아서 해당요청서 정보를 한줄의 문자열로 만들어 반환
char* r_to_string_save(T_request* T); // 저장하기에 편하게 문자열로 반환, 구조체정보를.
void r_get_all(T_request* T[]); //구조체 배열을 받아서 여기서 요청서구조체들 차곡차곡넣기.
void r_rerrange(); // 요청서 배열 최적화
char* r_getname(T_request* p);
char* r_getphone(T_request* p);
char* r_getdate(T_request* p);
int r_getage(T_request* p);
char* r_getaddress(T_request* p);
int r_getspace(T_request* p);
