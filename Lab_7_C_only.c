#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Serial Serial;
typedef struct SerialList SerialList;
const char *file = "/home/njozzer/CLionProjects/untitled15/data.txt";
struct Serial {
    Serial *next;
    char name[32];
    char producer[32];
    int count_seasons;
    double popularity;
    double rating;
    char date[32];
    char country[32];
};

void InitSerial(Serial *serial,
                char name[32],
                char producer[32],
                int count_seasons,
                double popularity,
                double rating,
                char date[32],
                char country[32]) {
    serial->next = NULL;
    strcpy(serial->name, name);
    strcpy(serial->producer, producer);
    serial->count_seasons = count_seasons;
    serial->popularity = popularity;
    serial->rating = rating;
    strcpy(serial->date, date);;
    strcpy(serial->country, country);;
}

struct SerialList {
    Serial *first;
};

void InitList(SerialList *list) {
    list->first = NULL;
}

void remove1(SerialList *lst, Serial *serial) {
    Serial *curr = lst->first;
    if (curr == serial) {
        lst->first = serial->next;
    } else {
        while (curr->next != serial) {
            curr = curr->next;
        }
        curr->next = serial->next;
    }
    free(serial);
}

void print(SerialList *lst) {
    Serial *curr = lst->first;
    while (curr != NULL) {
        printf("%1.2lf %s\n", curr->popularity, curr->producer);
        curr = curr->next;
    }
}

void insert(SerialList *lst, Serial *serial, int order) {
    int n = 0;
    Serial *curr = lst->first;
    if (curr == NULL) {
        lst->first = serial;
        return;
    }
    while (n++ < order - 1) {
        if (curr->next != NULL)
            curr = curr->next;
        else if (curr->next == NULL) {
            curr->next = serial;
            return;
        }
    }
    serial->next = curr->next;
    curr->next = serial;
}

void add(SerialList *lst, Serial *serial) {

    Serial *curr = lst->first;
    if (curr == NULL) {
        lst->first = serial;
    } else {
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = serial;
    }

}

Serial *copy(Serial *target) {
    Serial *serial;
    serial = (Serial *) malloc(sizeof(Serial));
    InitSerial(serial,
               target->name,
               target->producer,
               target->count_seasons,
               target->popularity,
               target->rating,
               target->date,
               target->country);
    return serial;
}

/*
 * param:
 * 1 is >
 * 0 is ==
 * -1 is <
 * */
void filter(SerialList *lst, SerialList *f_lst, double popularity, int param) {
    Serial *curr = lst->first;
    if (param == -1) {
        while (curr != NULL) {
            if (curr->popularity < popularity) {
                add(f_lst, copy(curr));
            }
            curr = curr->next;
        }
    }
    if (param == 0) {
        while (curr != NULL) {
            if (curr->popularity == popularity) {
                add(f_lst, copy(curr));
            }
            curr = curr->next;
        }
    }
    if (param == 1) {
        while (curr != NULL) {
            if (curr->popularity > popularity) {
                add(f_lst, copy(curr));
            }
            curr = curr->next;
        }
    }
}

void find(SerialList *lst, SerialList *f_lst, char producer[32]) {
    Serial *curr = lst->first;
    while (curr != NULL) {
        if (curr->producer == producer) {
            add(f_lst, copy(curr));
        }
        curr = curr->next;
    }
}

int save(const char *address, SerialList *lst) {
    FILE *f_out;
    f_out = fopen(address, "w");
    if (f_out != 0) {
        Serial *current = lst->first;
        while (current != NULL) {
            fprintf(f_out, "%s %s %d %lf %lf %s %s\n",
                    current->name,
                    current->producer,
                    current->count_seasons,
                    current->popularity,
                    current->rating,
                    current->date,
                    current->country
            );
            current = current->next;
        }
        fclose(f_out);
        return 1;
    }
    return 0;
}

SerialList load(const char *address) {
    SerialList list;
    InitList(&list);
    FILE *f_in;
    f_in = fopen(address, "r");
    if (f_in != 0) {

        char name[32];
        char producer[32];
        int count_seasons;
        double popularity;
        double rating;
        char date[32];
        char country[32];
        while (fscanf(f_in, "%s %s %d %lf %lf %s %s",
                      name,
                      producer,
                      &count_seasons,
                      &popularity,
                      &rating,
                      date,
                      country) != EOF) {
            Serial *serial = (Serial *) malloc(sizeof(Serial));
            InitSerial(serial, name, producer, count_seasons, popularity, rating, date, country);
            add(&list, serial);
        }
        fclose(f_in);
    }

    return list;
}

/*
 *string name;
 *string producer;
 *int count_seasons;
 *double popularity;
 *double rating;
 *string date;
 *string country;
*/
int main() {
    SerialList lst;
    InitList(&lst);
    Serial *serial1 = (Serial *) malloc(sizeof(Serial));
    Serial *serial2 = (Serial *) malloc(sizeof(Serial));
    Serial *serial3 = (Serial *) malloc(sizeof(Serial));
    Serial *serial4 = (Serial *) malloc(sizeof(Serial));
    InitSerial(serial1, "Name", "Producer1", 4, 4.6, 5, "07.06.2011", "Ru");
    InitSerial(serial2, "Name", "Producer2", 4, 4.6, 5, "07.06.2011", "Ru");
    InitSerial(serial3, "Name", "Producer3", 4, 4.2, 5, "07.06.2011", "Ru");
    InitSerial(serial4, "Name", "Producer4", 4, 4.8, 5, "07.06.2011", "Ru");
    add(&lst, serial1);
    add(&lst, serial2);
    insert(&lst, serial3, 1);
    add(&lst, serial4);
    SerialList flst;
    InitList(&flst);
    filter(&lst, &flst, 4.7, -1);
    print(&flst);
    return 0;
}
