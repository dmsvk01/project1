#include "requisition.h"
//#define DEBUG
T_request* request[MAX];
int _count = 0;


int r_available(){
    if(_count  < MAX) return 1;
    else return 0;
}

int r_first_available(){
    int i;
    for(i=0; i<MAX; i++){
        if(request[i]==NULL){
            break;
        }
    }
    return i;
}

int r_count(){
    return _count;
}

T_request* r_search_by_name(char* t_name){
    for(int i=0; i<MAX; i++){
        if(request[i] && strcmp(t_name, request[i]->name)==0){
#ifdef DEBUG
    printf("\n[DEBUF] %s의 요청서를 찾았습니다.\n\n", t_name);
#endif
            return request[i];
        }
    }
    return NULL;
}

T_request* r_search_by_date(char* t_date){
    for(int i=0; i<MAX; i++){
        if(request[i] && strcmp(t_date,request[i]->date)==0){
#ifdef DEBUG
    printf("\n[DEBUF] %s날짜에 해당하는 요청서를 찾았습니다.\n\n", t_date);
#endif
            return request[i];
        }
    }
    return NULL;
}

T_request* r_search_by_city(char* t_city){
    for(int i=0; i<MAX; i++){
        if(request[i] && strcmp(t_city,request[i]->city)==0){
#ifdef DEBUG
    printf("\n[DEBUF] %s에 해당하는 요청서를 찾았습니다.\n\n", t_city);
#endif
            return request[i];
        }
    }
    return NULL;
}
 // 구조체 배열과 날짜를 받아서 날짜일치하는 요청서구조체를 구조체배열에 차곡차곡넣기.
void r_get_all_by_date(T_request* a[], char* date, int *size){
    int c=0;
    for(int i=0; i<MAX; i++){
        if(request[i] && strcmp(date, request[i]->date)==0){
            a[c] = request[i];
            c++;
            *size+=1;
        }
    }
#ifdef DEBUG
    printf("\n[DEBUF] get by date 총 %d개의 구조체발견.\n\n", c);
#endif
}

void r_get_all_by_city(T_request* a[], char* city, int *size){
    int c=0;
    for(int i=0; i<MAX; i++){
        if(request[i] && strcmp(city, request[i]->city)==0){
            a[c] = request[i];
            c++;
            *size+=1;
        }
    }
#ifdef DEBUG
    printf("\n[DEBUF] get by city 총 %d개의 구조체발견.\n\n", c);
#endif
}

void r_create(char* t_date, char* t_name, int t_age, char* t_phone, char* t_city, int t_space){
    int index = r_first_available();
    request[index] = (T_request*)malloc(sizeof(T_request));
    T_request* p=request[index];
    strcpy(p->date, t_date);
    strcpy(p->name, t_name);
    p->age = t_age;
    strcpy(p->phone, t_phone);
    strcpy(p->city, t_city);
    p->space = t_space;
    _count++;
#ifdef DEBUG
    printf("\n[DEBUF] 요청서생성완료.\n\n");
#endif
}

void r_update(T_request* p, char* t_date, char* t_name, int t_age, char* t_phone, char* t_city, int t_space){
    strcpy(p->date, t_date);
    strcpy(p->name, t_name);
    p->age = t_age;
    strcpy(p->phone, t_phone);
    strcpy(p->city, t_city);
    p->space = t_space;
#ifdef DEBUG
    printf("\n[DEBUF] 업데이트 완료.\n\n");
#endif
}

void r_delete(T_request* p){
    int index;
    for(int i=0; i<MAX; i++){
        if(p==request[i]){
            index = i;
#ifdef DEBUG
    printf("\n[DEBUF] delete 해당항목 발견.\n\n");
#endif
            break;
        }
    }
    request[index] = NULL;
    free(p);
    _count--;
}

void r_delete_all(){
    for(int i=0; i<MAX; i++){
        if(request[i]!=NULL){
            free(request[i]);
        }
        request[i]=NULL;
    }
    _count=0;
}

char* r_to_string(T_request* T){
    static char str[200];
    sprintf(str, " [%s]%s, %d세, %s, %s, %d평\n", T->date, T->name, T->age, T->phone, T->city, T->space);
#ifdef DEBUG
    printf("\n[DEBUF] to_string : string생성 완료.\n\n");
#endif
    return str;
}

char* r_to_string_save(T_request* T){
    static char str[200];
    sprintf(str, "%s %s %d %s %s %d\n", T->date, T->name, T->age, T->phone, T->city, T->space);
#ifdef DEBUG
    printf("\n[DEBUF] to_string_save : string생성 완료.\n\n");
#endif
    return str;
}

void r_get_all(T_request* a[]){
    int c=0;
    for(int i=0; i<MAX; i++){
        if(request[i]!=NULL){
            a[c] = request[i];
            c++;
        }
    }
}

void r_rerrange(){ // 중간에 빈 공간 땡겨서 최적화.
    for(int i=0; i<MAX-1; i++){
        if(request[i]==NULL){
            request[i] = request[i+1];
            request[i+1] = NULL;
#ifdef DEBUG
    printf("\n[DEBUF] 최적화 .%d번째칸\n", i);
#endif
        }
    }
}

char* r_getname(T_request* p){
    return p->name;
}

char* r_getphone(T_request* p){
    return p->phone;
}

char* r_getdate(T_request* p){
    return p->date;
}

int r_getage(T_request* p){
    return p->age;
}

char* r_getaddress(T_request* p){
    return p->city;
}

int r_getspace(T_request* p){
    return p->space;
}
