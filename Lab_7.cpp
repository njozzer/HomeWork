#include<iostream>


int *read_file(char *address, size_t *len) {
    FILE *f_in;
    int *arr = 0;
    f_in = fopen(address, "r");
    if (f_in != 0) {
        fscanf(f_in, "%d", len);
        size_t i = 0;
        arr = (int *) calloc(*len, sizeof(int));
        while (i < *len) {
            fscanf(f_in, "%d", &arr[i]);
            i++;
        }
        fclose(f_in);
    }
    return arr;
}

struct Serial {
    Serial *next;
    char *name;
    char *producer;
    int count_seasons;
    double popularity;
    double rating;
    char *date;
    char *country;
};

struct SerialList {
    Serial *first;
public:
    SerialList() {
        this->first = nullptr;
    }

};

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
    while (curr != NULL) {
        curr = curr->next;
    }
    curr->next = serial;
}

Serial *filter(SerialList) {

}
Serial *find(SerialList *lst, char *producer) {
    Serial *curr = lst->first;

    while (curr->next != NULL) {
        if (curr->producer == producer) {
            
        }
        curr = curr->next;
    }
    return curr;
}
/*
 *  Serial *next;
 *   char *name;
 *   char *producer;
 *   int count_seasons;
 *   double popularity;
 *   double rating;
 *   char *date;
 *   char *country;
 */
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

int main() {
    int n = 0;
    while (n++ < 10) {
        std::cout << n;
    }
    return 0;
}

