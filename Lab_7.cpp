#include<iostream>

using std::string;
struct Serial {
    Serial *next;
    string name;
    string producer;
    int count_seasons;
    double popularity;
    double rating;
    string date;
    string country;
};

void InitSerial(Serial *serial,
                string name,
                string producer,
                int count_seasons,
                double popularity,
                double rating,
                string date,
                string country) {
    serial->name = name;
    serial->producer = producer;
    serial->count_seasons = count_seasons;
    serial->popularity = popularity;
    serial->rating = rating;
    serial->date = date;
    serial->country = country;
}

struct SerialList {
    Serial *first;
};

void InitList(SerialList *list) {
    list->first = NULL;
}

void remove(SerialList *lst, Serial *serial) {
    Serial *curr = lst->first;
    while (curr != serial) {
        curr = curr->next;
    }
    curr->next = serial->next;
    delete serial;
}

void insert(SerialList *lst, Serial *serial, int order) {
    int n = 0;
    Serial *curr = lst->first;
    while (n++ < order - 1) {
        curr = curr->next;
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

/*
 * param:
 * 1 is >
 * 0 is ==
 * -1 is <
 * */
void filter(SerialList *lst,SerialList *f_lst, double popularity, int param) {
    Serial *curr = lst->first;
    if (param == -1) {
        while (curr != NULL) {
            if (curr->popularity < popularity) {
                add(f_lst, curr);
            }
            curr = curr->next;
        }

    }
    if (param == 0) {
        while (curr != NULL) {
            if (curr->popularity == popularity) {
                add(f_lst, curr);
            }
            curr = curr->next;
        }

    }
    if (param == 1) {
        while (curr != NULL) {
            if (curr->popularity > popularity) {
                add(f_lst, curr);
            }
            curr = curr->next;
        }
    }
}

SerialList find(SerialList *lst, string producer) {
    SerialList f_lst;
    Serial *curr = lst->first;

    while (curr->next != NULL) {
        if (curr->producer == producer) {
            add(&f_lst, curr);
        }
        curr = curr->next;
    }
    return f_lst;
}

int save(char *address, SerialList *lst) {
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

SerialList *load(char *address) {
    FILE *f_in;
    f_in = fopen(address, "r");
    SerialList *lst;
    if (f_in != 0) {

        fclose(f_in);
    }
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
    Serial *serial = (Serial *) malloc(sizeof(Serial));
    Serial *serial1 = (Serial *) malloc(sizeof(Serial));
    Serial *serial3 = (Serial *) malloc(sizeof(Serial));
    Serial *serial4 = (Serial *) malloc(sizeof(Serial));
    InitSerial(serial, "Name", "Producer", 4, 4.6, 5, "07.06.2011", "Ru");
    InitSerial(serial1, "Name", "Producer", 4, 4.6, 5, "07.06.2011", "Ru");
    InitSerial(serial4, "Name", "Producer", 4, 4.2, 5, "07.06.2011", "Ru");
    InitSerial(serial3, "Name", "Producer", 4, 4.8, 5, "07.06.2011", "Ru");
    add(&lst, serial);
    add(&lst, serial1);
    add(&lst, serial3);
    add(&lst, serial4);
    SerialList f_lst;
    InitList(&f_lst);
    filter(&lst,&f_lst,4.8,-1);
    return 0;
}
