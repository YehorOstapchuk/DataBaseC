#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define TITLE_LEN 20
#define ADRESS_LEN 40
#define CODE_LEN 10
#define NAME_LEN 20
#define SURNAME_LEN 20
#define PASSPORT_NUMBER_LEN 20
#define PROFESSION_LEN 20
#define MAX_AMOUNT 30
#define MAX_AMOUNT_SLAVE 60


const char fileNameIndex [] = "index.txt";
const char fileNameMaster [] = "master.txt";
const char fileNameSlave [] = "slave.txt";
long index = 0;
int count = 0;
int count_slave = 0;

typedef struct tag_bank {
    char title [TITLE_LEN];
    char adress [ADRESS_LEN];
    char code [CODE_LEN];
    long slave_adress;
    long slaves_amount;
    int flag;
} tbank;

typedef struct tag_worker {
    char name [NAME_LEN];
    char surname [SURNAME_LEN];
    char passport_number [PASSPORT_NUMBER_LEN];
    char profession [PROFESSION_LEN];
   // int experience;
    //long master_adress;
    long next_slave_adress;
    int flag;
} tworker;

typedef struct tag_index {
    long key;
    long master_adress;
    int flag;
} tindex;



int insert_master (long position) {
    FILE *out_bank;
    tbank b;
    out_bank = fopen(fileNameMaster, "rb+");
    printf("Insert the title of the Bank:\n");
    scanf("%s",b.title );
    printf("Insert the adress of the Bank:\n");
    scanf("%s", b.adress);
    printf("Insert the code of the Bank (KEY):\n");
    scanf("%s", b.code);
    b.flag = 1;
    b.slaves_amount = 0;
    b.slave_adress = -1;
    //printf("%ld", ind.key);
    long distance = position*sizeof(tbank);
    fseek(out_bank, distance + MAX_AMOUNT*sizeof(int), SEEK_SET);
    fwrite(&b, sizeof(tbank), 1, out_bank);
    fclose(out_bank);

   // tindex ind2;
  // out_index = fopen(fileNameIndex, "r");
  // fread(&ind2, sizeof(tindex), 1, out_index);
    //printf("%ld", ind2.key);
        FILE *out_index;
            out_index = fopen(fileNameIndex, "rb+");
        tindex ind;
        ind.key = index;
        fseek(out_index, index*sizeof(tindex), SEEK_SET);
        index++;
        ind.master_adress = position;
        ind.flag = 1;
       // printf("%d%d", ind.key, ind.master_adress);
        fwrite(&ind, sizeof(tindex), 1, out_index);
        fclose(out_index);
    return 0;

}




int add_deleted (int position){
    FILE *out_bank;
    out_bank = fopen(fileNameMaster, "rb+");
    int temp = 0;
    int i = 0;
    while ((temp != -1) && (i<MAX_AMOUNT)){
        fread(&temp, sizeof(int), 1, out_bank);
        if (temp != -1 ) { i++; }
        fseek(out_bank, sizeof(int)*i, SEEK_SET);
    }
    if (i == MAX_AMOUNT) return -1;
    fseek(out_bank, sizeof(int)*i, SEEK_SET);
    fwrite(&position, sizeof(int), 1, out_bank);
    fclose(out_bank);
   // printf("%d", i);
   // printf("----");
    return 1;
}

int pop_deleted (){
    int position;
    int d = -1;
        FILE *out_bank;
    out_bank = fopen(fileNameMaster, "rb+");
    int temp = 0;
    int i = 0;
    while ((temp != -1) && (i<MAX_AMOUNT)){
        fread(&temp, sizeof(int), 1, out_bank);
        if (temp != -1 ) i++;
    }
    if (i == 0) return -1;
    fseek(out_bank, (i-1)*sizeof(int), SEEK_SET);
    fread(&position, sizeof(int), 1, out_bank );
    fseek(out_bank, (i-1)*sizeof(int), SEEK_SET);
    fwrite(&d, sizeof(int), 1, out_bank);
    fclose(out_bank);
    return position;
}

int create_space (){
    FILE *out_bank;
    out_bank = fopen(fileNameMaster, "rb+");
    int i=0;
    int d = -1;
    fseek(out_bank, 0, SEEK_SET);
    while (i<MAX_AMOUNT){
        fwrite(&d, sizeof(int), 1, out_bank);
        i++;
    }
    fclose(out_bank);
    return 1;
}


int create_space_slave (){
    FILE *out_worker;
    out_worker = fopen(fileNameSlave, "rb+");
    int i=0;
    int d = -1;
    fseek(out_worker, 0, SEEK_SET);
    while (i<MAX_AMOUNT_SLAVE){
        fwrite(&d, sizeof(int), 1, out_worker);
        i++;
    }
    fclose(out_worker);
    return 1;
}

int add_deleted_slave (int position){
    FILE *out_worker;
    out_worker = fopen(fileNameSlave, "rb+");
    int temp = 0;
    int i = 0;
    while ((temp != -1) && (i<MAX_AMOUNT_SLAVE)){
        fread(&temp, sizeof(int), 1, out_worker);
        if (temp != -1 ) { i++; }
        fseek(out_worker, sizeof(int)*i, SEEK_SET);
    }
    if (i == MAX_AMOUNT_SLAVE) return -1;
    fseek(out_worker, sizeof(int)*i, SEEK_SET);
    fwrite(&position, sizeof(int), 1, out_worker);
    fclose(out_worker);
  //  printf("%d", i);
  //  printf("----");
    return 1;
}

int pop_deleted_slave (){
    int position;
    int d = -1;
        FILE *out_worker;
    out_worker = fopen(fileNameSlave, "rb+");
    int temp = 0;
    int i = 0;
    while ((temp != -1) && (i<MAX_AMOUNT_SLAVE)){
        fread(&temp, sizeof(int), 1, out_worker);
        if (temp != -1 ) i++;
    }
    if (i == 0) return -1;
    fseek(out_worker, (i-1)*sizeof(int), SEEK_SET);
    fread(&position, sizeof(int), 1, out_worker );
    fseek(out_worker, (i-1)*sizeof(int), SEEK_SET);
    fwrite(&d, sizeof(int), 1, out_worker);
    fclose(out_worker);
    return position;
}




int insert_slave (int position){
    FILE *out_worker;
    tworker w;
    out_worker = fopen(fileNameSlave, "rb+");
    printf("Insert the name of the worker:\n");
    scanf("%s", w.name );
    printf("Insert the surname of the worker:\n");
    scanf("%s", w.surname);
    printf("Insert the passport number of the worker(KEY):\n");
    scanf("%s", w.passport_number);
    printf("Insert the profession of the worker:\n");
    scanf("%s", w.profession);
   // printf("Insert the experience:\n");
  //  scanf("%d", w.experience);
    //if (master_adress>=0) w.master_adress = master_adress;
    //else w.master_adress = -1;
    w.next_slave_adress = -1;
    w.flag = 1;
   // printf("Position"); printf("%d", position); printf("\n");
    fseek(out_worker, position*sizeof(tworker) + MAX_AMOUNT_SLAVE*sizeof(int), SEEK_SET);
    fwrite(&w, sizeof(tworker), 1, out_worker);
    fclose(out_worker);
    return 0;
}


int insert_master_full (){
    int deleted = 0;
    deleted = pop_deleted();
    if (deleted != -1) { insert_master(deleted); return deleted; }
      else { if(count < MAX_AMOUNT) {insert_master(count); count++;   return (count - 1);}}
    return -1;
}


int insert_slave_full (){
    int del = -1;
    del = pop_deleted_slave();
  //  printf("delted"); printf("%d", del);
    if (del != -1) { insert_slave(del); return del; }
      else { if(count_slave < MAX_AMOUNT_SLAVE) {insert_slave(count_slave); count_slave++; return (count_slave - 1);}}
    return -1;
}


int rewrite_master (tbank m, long position)
{
    FILE *out_bank;
    out_bank = fopen(fileNameMaster, "rb+");
    fseek(out_bank, position*sizeof(tbank) + MAX_AMOUNT*sizeof(int), SEEK_SET);
    fwrite(&m, sizeof(tbank), 1, out_bank);
    fclose(out_bank);
    return 0;
}

int rewrite_slave (tworker m, long position)
{
    FILE *out_worker;
    out_worker = fopen(fileNameSlave, "rb+");
    fseek(out_worker, position*sizeof(tworker) + MAX_AMOUNT_SLAVE*sizeof(int), SEEK_SET);
    fwrite(&m, sizeof(tworker), 1, out_worker);
    fclose(out_worker);
    return 0;
}

int rewrite_index (tindex m, long position)
{
    FILE *out_index;
    out_index = fopen(fileNameIndex, "rb+");
    fseek(out_index, position*sizeof(tindex), SEEK_SET);
    fwrite(&m, sizeof(tindex), 1, out_index);
    fclose(out_index);
    return 0;
}


tbank get_master (long position){
    FILE *in_bank;
    in_bank = fopen(fileNameMaster, "rb");
    fseek(in_bank, position*sizeof(tbank) + MAX_AMOUNT*sizeof(int), SEEK_SET);
    tbank temp;
    fread(&temp, sizeof(tbank), 1, in_bank);
    fclose(in_bank);
    return temp;
}

tworker get_slave (long position){
    FILE *in_worker;
    in_worker = fopen(fileNameSlave, "rb");
    fseek(in_worker, position*sizeof(tworker)+ MAX_AMOUNT_SLAVE*sizeof(int), SEEK_SET);
    tworker temp;
    fread(&temp, sizeof(tworker), 1, in_worker);
    fclose(in_worker);
    return temp;
}


tindex get_index (long position){
    FILE *in_index;
    in_index = fopen(fileNameIndex, "rb");
    fseek(in_index, position*sizeof(tindex), SEEK_SET);
    tindex temp;
    fread(&temp, sizeof(tindex), 1, in_index);
    fclose(in_index);
    return temp;
}


int find_master ( char *code_, tbank *temp2){
    FILE *index_in;
    index_in = fopen(fileNameIndex, "rb");
    tindex temp;
    while(!feof(index_in)){
        fread(&temp, sizeof(tindex), 1, index_in);
        //printf("%d%d", temp.master_adress, temp.key);
        if (temp.flag) { *temp2 = get_master(temp.master_adress);// printf("%d", temp.master_adress);
         if ( strcmp((*temp2).code, code_) == 0 ) { fclose(index_in); return temp.master_adress;}   // Доделать сравнение
        }
    }
    fclose(index_in);
    return -1;
}



int find_master_key ( char *code_, tbank *temp2){
    FILE *index_in;
    index_in = fopen(fileNameIndex, "rb");
    tindex temp;
    while(!feof(index_in)){
        fread(&temp, sizeof(tindex), 1, index_in);
        //printf("%d%d", temp.master_adress, temp.key);
        if (temp.flag) { *temp2 = get_master(temp.master_adress);// printf("%d", temp.master_adress);
         if ( strcmp((*temp2).code, code_) == 0 ) { fclose(index_in); return temp.key;}   // Доделать сравнение
        }
    }
    fclose(index_in);
    return -1;
}

int find_slave (char *code_master, char *pasport_slave, tworker *temp2){
    tbank temp;
    find_master(code_master, &temp);
    int position = temp.slave_adress;
    while(position != -1){
        *temp2 = get_slave(position);
        if (strcmp(pasport_slave, (*temp2).passport_number) == 0) return position;
        position = (*temp2).next_slave_adress;
    }
    return -1;
}


int delete_slave (char *code_master, char *pasport_slave) {
    tbank temp;
    int pos = find_master(code_master, &temp);
    int previous_position;
    int previous_position1;
    int position = temp.slave_adress;
    int i = 0;
    int temp_position;
    tworker temp2;
    tworker temp3;
    //printf("hui0");
        while(position != -1){
        temp2 = get_slave(position);
        previous_position1 = position;
       // printf("%d", position);
        //printf("pass");
        //printf("%s", temp2.passport_number); break;
        if (strcmp(pasport_slave, temp2.passport_number) == 0) { //printf("hui");
            if (i == 0) {temp.slave_adress = temp2.next_slave_adress;  rewrite_master(temp, pos); temp2.flag = 0; rewrite_slave(temp2, position); add_deleted_slave(previous_position1); return 1; }
        else {   temp_position = temp2.next_slave_adress; temp2.flag = 0; rewrite_slave(temp2, position);
        temp3 = get_slave(previous_position);  temp3.next_slave_adress = temp2.next_slave_adress; rewrite_slave(temp3, previous_position); add_deleted_slave(position); return 1;}  }
        i++;
        previous_position = position;
        position = temp2.next_slave_adress;
    }
    return -1;
}

int delete_master (char *code_master){
    tbank temp; tworker temp2;
    int position = find_master(code_master, &temp);
    if (position == -1) return -1;
    while(temp.slave_adress!= -1) {
        temp2 = get_slave(temp.slave_adress);
    //  printf("%s","POehali");  printf("%s", code_master); printf("%s", temp2.passport_number); printf("%s","\n");
        delete_slave(code_master, temp2.passport_number);
        find_master(code_master, &temp);
    }
    temp.flag = 0;
    rewrite_master(temp, position);
    // даудалять в индексе

   // printf("POsition");
    //printf("%d", position);
    tbank temp3;
    int key = find_master_key(code_master, &temp3);
    tindex temp4 = get_index(key);
    temp4.flag = 0;
    rewrite_index(temp4, key);
    add_deleted(position);
    return 1;
}

void index_show () {
    FILE *out_index2;
    out_index2 = fopen(fileNameIndex, "rb");
    tindex temp3;
    int i = 0;
    fseek(out_index2, 0, SEEK_SET );
    while(!feof(out_index2)){ //i++;
        fread(&temp3, sizeof(tindex), 1, out_index2);
        i++;
    }
    fclose(out_index2);


    FILE *out_index;
    out_index = fopen(fileNameIndex, "rb");
    tindex temp;
    //int i = 0;
    printf("-------------INDEX-TABLE---------------\n");
    printf("%5s %8s", "Index", "Position");
    printf("\n");
    fseek(out_index, 0, SEEK_SET );
    int j =0;
    while(j<(i-1)){ //i++;
            j++;
        fread(&temp, sizeof(tindex), 1, out_index);
        if (temp.flag == 0) continue;
        printf("%ld", temp.key);
        printf("       ");
        printf("%ld", temp.master_adress);
        printf("\n");

    }
    printf("---------------------------------------\n");
    fclose(out_index);
}


int insert_slave_full_full(char *master_code){
    tbank temp;
    int position;
    int master = find_master(master_code, &temp);
    if (master == -1) return -1;
    if (temp.slave_adress == -1) {position = insert_slave_full(); temp.slave_adress = position; rewrite_master(temp, master); return position;}
     else
     {
         int slave_pos = temp.slave_adress;
         tworker temp2;
         int before = slave_pos;
         while(slave_pos != -1){
            temp2 = get_slave(slave_pos);
            before = slave_pos;
            slave_pos = temp2.next_slave_adress;
         }
         position = insert_slave_full();
         temp2.next_slave_adress = position;
         rewrite_slave(temp2, before);
         return 1;
     }
}


void master_show () {
    FILE *out_bank;
    out_bank = fopen(fileNameMaster, "rb");
    tbank temp;
    int d;
    //int i = 0;
    /* for(int i=0; i<MAX_AMOUNT; i++){
        fread(&d, sizeof(int), 1, out_bank);
        printf("%d", d);
        printf(" ");
    }
    printf("\n"); */



    FILE *out_index2;
    out_index2 = fopen(fileNameIndex, "rb");
    tindex temp3;
    int i = 0;
    fseek(out_index2, 0, SEEK_SET );
    while(!feof(out_index2)){ //i++;
        fread(&temp3, sizeof(tindex), 1, out_index2);
        i++;
    }
    fclose(out_index2);


    FILE *out_index;
    out_index = fopen(fileNameIndex, "rb");
    tindex temp2;
    //int i = 0;
    fseek(out_index, 0, SEEK_SET );
    printf("----------------------------MASTERS-TABLE--------------------------------\n");
    printf("%20s%40s%10s", "Title", "Adress", "Code");
    printf("\n");
    int j =0;
    while(j<(i-1)){ //i++;
            j++;
        fread(&temp2, sizeof(tindex), 1, out_index);
        if (temp2.flag == 0) continue;
        temp = get_master(temp2.master_adress);
        printf("%20s", temp.title);
        printf("%40s", temp.adress);
        printf("%10s", temp.code);
        printf("\n");
       // fseek(out_bank, i*sizeof(tbank)+MAX_AMOUNT*sizeof(int), SEEK_SET);

    }
    fclose(out_index);





   /*
    -----------------------------------------------------------
    printf("----------------------------MASTERS-TABLE--------------------------------\n");
    printf("%20s%40s%10s", "Title", "Adress", "Code");
    printf("\n");
    fseek(out_bank, MAX_AMOUNT*sizeof(int), SEEK_SET);
        int i = 0;
    int max;
    if (index>=MAX_AMOUNT) max =MAX_AMOUNT;
    else max = index;
    while(i<max){ i++;
        fread(&temp, sizeof(tbank), 1, out_bank);
        if (temp.flag == 0) continue;
        printf("%20s", temp.title);
        printf("%40s", temp.adress);
        printf("%10s", temp.code);
        printf("\n");
        fseek(out_bank, i*sizeof(tbank)+MAX_AMOUNT*sizeof(int), SEEK_SET); //?
    } */
    fclose(out_bank);
    printf("-------------------------------------------------------------------------\n");
}



void insert_slave_general (){
  int del = pop_deleted_slave();
  printf("My");
  printf("%d", del);
  printf("\n");
}

void slave_show_2 (char *code_master) {
    FILE *out_worker;
   out_worker = fopen(fileNameSlave, "rb");
   tworker temp;
    int d;
    //int i = 0;








    fseek(out_worker, 0, SEEK_SET);
    for(int i=0; i<MAX_AMOUNT_SLAVE; i++){
        fseek(out_worker, i*sizeof(int), SEEK_SET);
        fread(&d, sizeof(int), 1, out_worker);
        printf("%d", d);
        printf(" ");
    }
    printf("\n");
    //fseek(out_worker, MAX_AMOUNT_SLAVE*sizeof(int), SEEK_SET);
     //   int i = 0;
   // int max;
    //if (index>=MAX_AMOUNT) max =MAX_AMOUNT;
    //else max = index;
    //while(i<max){ i++;
    for(int i=0; i<3; i++){
        fseek(out_worker, i*(sizeof(tworker))+MAX_AMOUNT_SLAVE*sizeof(int), SEEK_SET);
        fread(&temp, sizeof(tworker), 1, out_worker);
        printf("%s", temp.name);
        printf(" ");
        printf("%s", temp.passport_number);
        printf(" ");
        printf("%ld", temp.next_slave_adress);
        printf(" ");
        printf("%d", temp.flag);
        printf("\n"); }
    fclose(out_worker);
    //}
}


int slave_show (char *code_master){


        tbank temp; tworker temp2;
    int flag = find_master(code_master, &temp);
    if (flag == -1) return -1;
       printf("-------------------------------SLAVES-TABLE-----------------------------------------\n");
    printf("%20s%20s%20s%20s","Name","Surname", "PassportN", "Profession");
    printf("\n");
    int position = temp.slave_adress;
    while(position != -1){
        temp2 = get_slave(position);
        position = temp2.next_slave_adress;
        printf("%20s", temp2.name);
        printf("%20s", temp2.surname);
        printf("%20s", temp2.passport_number);
        printf("%20s", temp2.profession);
      //  printf(" ");
        //printf("%ld", temp2.next_slave_adress);
        //printf(" ");
        //printf("%d", temp2.flag);
        printf("\n");

    }
    printf("------------------------------------------------------------------------------------\n");
    return 1;}

void help (){
    printf("Commands: INSERT, GET, DELETE, UPDATE, SHOW, HELP, END.\n");
}


int out () {
    printf("Enter the command:");
    char comand[10];
    char* object[10];
    scanf("%s10", comand);
   // printf("%s", comand);
    if (strcmp(comand, "INSERT") == 0) {
        printf("%s", "Print SLAVE or MASTER:\n");
        scanf("%s", object);
        if (strcmp(object, "END") == 0) { return -1;}
        if (strcmp(object, "MASTER") == 0) { insert_master_full(); return 0;}
        if (strcmp(object, "SLAVE") == 0) { char *key[CODE_LEN];
            printf("%s", "Enter the key(code) of the master:\n");
            scanf("%s", key);
           int flag = insert_slave_full_full(key);
           if (flag == -1) return 1;
           return 0;
        }
        return 1;
    }
    if (strcmp(comand, "HELP") == 0) {help(); return 0;}
    if (strcmp(comand, "GET") == 0) {
        printf("%s", "Print SLAVE or MASTER:\n");
        scanf("%s", object);
        if (strcmp(object, "END") == 0) { return -1;}
        if (strcmp(object, "MASTER") == 0) {
                char *key[CODE_LEN];
                printf("%s", "Enter the key of the MASTER:\n");
                scanf("%s",key);
                tbank temp;
                int flag = find_master(key,&temp);
                if (flag == -1) return 1;
                                    printf("%20s%40s%10s", "Title", "Adress", "Code");
    printf("\n");
        printf("%20s", temp.title);
        printf("%40s", temp.adress);
        printf("%10s", temp.code);
        printf("\n");

        return 0;
        }
        if (strcmp(object, "SLAVE") == 0) {
                char *key[CODE_LEN];
                char *key2[PASSPORT_NUMBER_LEN];
                printf("%s", "Enter the key of the MASTER:\n");
                scanf("%s",key);
                printf("%s", "Enter the key of the SLAVE:\n");
                scanf("%s",key2);
                tworker temp;
                int flag = find_slave(key, key2, &temp);
                if (flag == -1) return 1;
                                    printf("%20s%20s%20s%20s","Name","Surname", "PassportN", "Profession");
    printf("\n");
        printf("%20s", temp.name);
        printf("%20s", temp.surname);
        printf("%20s", temp.passport_number);
        printf("%20s", temp.profession);
        printf("\n");

        return 0;
    }
    return 1;}
    if (strcmp(comand, "DELETE") == 0) {
            printf("%s", "Print SLAVE or MASTER:\n");
        scanf("%s", object);
        if (strcmp(object, "END") == 0) { return -1;}
        if (strcmp(object, "MASTER") == 0) {
                char *key[CODE_LEN];
                printf("%s", "Enter the key of the MASTER:\n");
                scanf("%s",key);
                int flag = delete_master(key);
                if (flag == -1) return 1;
        return 0;
        }
        if (strcmp(object, "SLAVE") == 0) {
                char *key[CODE_LEN];
                char *key2[PASSPORT_NUMBER_LEN];
                printf("%s", "Enter the key of the MASTER:\n");
                scanf("%s",key);
                printf("%s", "Enter the key of the SLAVE:\n");
                scanf("%s",key2);
                int flag = delete_slave(key, key2);
                if (flag == -1) return 1;
        return 0;

    }return 1;}
    if(strcmp(comand,"SHOW") == 0){
        printf("%s", "Enter  INDEX, MASTER or SLAVE:\n");
        scanf("%s", object);
        if (strcmp(object, "INDEX") == 0) {index_show(); return 0;}
        if (strcmp(object, "MASTER") == 0) {master_show(); return 0;}
        if (strcmp(object, "SLAVE") == 0){
                char *key[CODE_LEN];
                printf("%s", "Enter the key of the MASTER:\n");
                scanf("%s",key);
                int flag = slave_show(key);
                if (flag == -1) return 1;
                return 0;
        }

        return 1;
    }
    if (strcmp(comand, "UPDATE") == 0){
            printf("%s", "Print SLAVE or MASTER:\n");
        scanf("%s", object);
        if (strcmp(object, "END") == 0) { return -1;}
        if (strcmp(object, "MASTER") == 0) {
                char *key[CODE_LEN];
                printf("%s", "Enter the key of the MASTER:\n");
                scanf("%s",key);
                tbank temp;

                int position = find_master(key, &temp);
                if (position == -1) return 1;
                printf("Enter the title:");
                scanf("%s", temp.title);
                printf("\n");
                printf("Enter the adress:");
                scanf("%s", temp.adress);
                printf("\n");
                rewrite_master(temp, position);
        return 0;
        }
        if (strcmp(object, "SLAVE") == 0) {
                char *key[CODE_LEN];
                char *key2[PASSPORT_NUMBER_LEN];
                printf("%s", "Enter the key of the MASTER:\n");
                scanf("%s",key);
                printf("%s", "Enter the key of the SLAVE:\n");
                scanf("%s",key2);
                tworker temp;
                int position = find_slave(key, key2, &temp);
                if (position == -1) return 1;
                printf("Enter the Name:");
                scanf("%s", temp.name);
                printf("\n");
                printf("Enter the Surname:");
                scanf("%s", temp.surname);
                printf("\n");
                printf("Enter the Profession:");
                scanf("%s", temp.profession);
                printf("\n");
                rewrite_slave(temp, position);
        return 0;
        }
        return 1;
    }

        if (strcmp(comand, "END") == 0) { return -1;}
    return 1;
}

int main()
{

    create_space_slave();
    create_space();
    help();
        int flag = 0;
    while(flag != -1) { flag = out(); if (flag == 1) printf("Wrong input!\n"); if (flag == 0) printf("Successes!\n");}
    /*insert_master_full();
    insert_master_full();
    insert_master_full();
   insert_slave_full_full("b");
   insert_slave_full_full("d");
   insert_slave_full_full("b");
   delete_master("d");
   delete_slave("b", "b");
   slave_show();
    index_show();
    master_show();*/

    return 0;
}
