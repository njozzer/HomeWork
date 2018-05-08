#include<iostream>

using std::string;
const char *file = "/home/njozzer/CLionProjects/untitled15/data.txt";
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
    if (curr == serial) {
        lst->first = serial->next;
    } else {
        while (curr->next != serial) {
            curr = curr->next;
        }
        curr->next = serial->next;
    }
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

void find(SerialList *lst, SerialList *f_lst, string producer) {
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
                    current->name.c_str(),
                    current->producer.c_str(),
                    current->count_seasons,
                    current->popularity,
                    current->rating,
                    current->date.c_str(),
                    current->country.c_str()
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

        char name[20];
        char producer[20];
        int count_seasons;
        double popularity;
        double rating;
        char date[20];
        char country[40];
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
    InitSerial(serial1, "Name", "Producer", 4, 4.6, 5, "07.06.2011", "Ru");
    InitSerial(serial2, "Name", "Producer", 4, 4.6, 5, "07.06.2011", "Ru");
    InitSerial(serial3, "Name", "Producer", 4, 4.2, 5, "07.06.2011", "Ru");
    InitSerial(serial4, "Name", "Producer", 4, 4.8, 5, "07.06.2011", "Ru");
    add(&lst, serial1);
    add(&lst, serial2);
    insert(&lst, serial3, 1);
    add(&lst, serial4);

    SerialList f_lst;
    InitList(&f_lst);
    find(&lst, &f_lst, "Producer");


    SerialList list = load(file);
    Serial *curr = list.first;
    while (curr != NULL) {
        std::cout << curr->popularity << " " << curr->producer << std::endl;
        curr = curr->next;
    }
    return 0;
}
