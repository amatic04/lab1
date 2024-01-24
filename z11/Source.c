#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
10. Napisati program koji èita datoteku drzave.txt u kojoj su zapisani nazivi pojedinih država. Uz
ime države u datoteci se nalazi i ime dodatne datoteke u kojoj se nalaze gradovi pojedine
države. Svaka datoteka koja predstavlja državu sadrži popis gradova u formatu naziv_grada,
broj_stanovnika.

a) Potrebno je formirati sortiranu vezanu listu država po nazivu. Svaki èvor vezane liste
sadrži stablo gradova sortirano po broju stanovnika, zatim po nazivu grada.

b) Potrebno je formirati stablo država sortirano po nazivu. Svaki èvor stabla sadrži vezanu
listu gradova sortiranu po broju stanovnika, zatim po nazivu grada.

Nakon formiranja podataka potrebno je ispisati države i gradove te omoguæiti korisniku putem
tastature pretragu gradova odreðene države koji imaju broj stanovnika veæi od unosa na
tastaturi.

11. Prepraviti zadatak 10 na način da se formira hash tablica država. Tablica ima 11 mjesta, a
funkcija za preslikavanje ključ računa da se zbraja ASCII vrijednost prvih pet slova države zatim
računa ostatak cjelobrojnog dijeljenja te vrijednosti s veličinom tablice. Države s istim ključem se
pohranjuju u vezanu listu sortiranu po nazivu države. Svaki čvor vezane liste sadrži stablo
gradova sortirano po broju stanovnika, zatim po nazivu grada.

*/


// a)
typedef struct tree_element tree_Element;
typedef tree_Element* tree_position;
struct tree_element {
    char name[50];
    int population;
    tree_position L;
    tree_position R;
};

typedef struct list_element list_Element;
typedef list_Element* list_position;
struct list_element {
    char name[50];
    tree_position root;
    list_position next;
};

// b)
typedef struct list_element_b list_Element_b;
typedef list_Element_b* list_position_b;
struct list_element_b {
    char name[50];
    int population;
    list_position_b next;
};

typedef struct tree_element_b tree_Element_b;
typedef tree_Element_b* tree_position_b;
struct tree_element_b {
    char name[50];
    list_position_b head;
    tree_position_b L;
    tree_position_b R;
};
// 11)
typedef struct list_element Hash;
typedef Hash* hash_position;


// a)
int read_file(list_position head, char* fileName);
int country_to_list(list_position head, char* country, char* country_file);
int read_country_file(tree_position root, char* country_file);
tree_position add_to_tree(tree_position root, char* city, int population);
int print_a(list_position head);
int print_inorder(tree_position root);
int find_a(list_position head);
int print_cities(tree_position root, int min);

// b)
int read_file_b(tree_position_b root, char* fileName);
tree_position_b country_to_tree(tree_position_b root, char* coutry, char* country_file);
int read_country_file_b(list_position_b head, char* country_file);
int add_to_list(list_position_b head, char* city, int population);
int print_b(tree_position_b root);
int print_list(list_position_b head);
int find_b(tree_position_b root, char* country);
int print_cities_b(list_position_b head);

int country_to_hash(hash_position* country_hash);
int add_to_hash(hash_position* country_hash, char* country, char* country_file);


int main()
{
    // a)
    /*
    list_Element head = {
        .root = NULL,
        .next = NULL,
    };

    read_file(&head, "drzave.txt");
    print_a(&head);
    find_a(&head);

    // b)
    tree_Element_b root = {
        .head = NULL,
        .L = NULL,
        .R = NULL,
    };

    read_file_b(&root, "drzave.txt");
    print_b(&root);

    printf("Unesite traženu državu: ");

    char country[50];
    scanf(" %[^\n]", country);

    find_b(&root, country);
    */
    hash_position country_hash[11];


    country_to_hash(country_hash);
    print_hash(country_hash);


    return 0;
}

// a)
int read_file(list_position head, char* fileName) {

    FILE* file = NULL;
    file = fopen(fileName, "r");

    if (file == NULL) {
        printf("ERROR opening file");
        return 1;
    }

    char country[50];
    char country_file[50];

    while (fscanf(file, "%[^,], %s\n", country, country_file) == 2) {
        country_to_list(head, country, country_file);
    }

    return 0;
}

int country_to_list(list_position head, char* country, char* country_file) {

    list_position newElement = (list_position)malloc(sizeof(list_Element));

    if (newElement == NULL) {
        printf("ERROR alocating memory");
        return 1;
    }

    strcpy(newElement->name, country);
    newElement->root = NULL;
    newElement->next = NULL;

    list_position temp = head;

    while (temp->next != NULL) {

        if (strcmp(country, temp->next->name) < 0) {
            break;
        }

        temp = temp->next;
    }

    newElement->next = temp->next;
    temp->next = newElement;

    tree_position root = (tree_position)malloc(sizeof(tree_Element));
    if (root == NULL) {
        printf("ERROR alocating memory");
        return 1;
    }
    root->L = NULL;
    root->R = NULL;

    newElement->root = root;

    read_country_file(newElement->root, country_file);

    return 0;
}

int read_country_file(tree_position root, char* country_file) {

    FILE* file = NULL;
    file = fopen(country_file, "r");

    if (file == NULL) {
        printf("ERROR opening file\n");
        return 1;
    }

    char city[50] = "";
    int population = 0;

    if (fscanf(file, " %[^,], %d.\n", city, &population) == 2) {
        strcpy(root->name, city);
        root->population = population;
    }

    while (fscanf(file, " %[^,], %d.\n", city, &population) == 2) {
        add_to_tree(root, city, population);
    }

    return 0;
}

tree_position add_to_tree(tree_position root, char* city, int population) {

    if (root == NULL) {
        root = (tree_position)malloc(sizeof(tree_Element));
        if (root == NULL) {
            printf("ERROR alocating memory");
            return NULL;
        }

        root->L = NULL;
        root->R = NULL;
        root->population = population;
        strcpy(root->name, city);
    }
    else {
        if (population > root->population) {
            root->L = add_to_tree(root->L, city, population);
        }
        else if (population < root->population) {
            root->R = add_to_tree(root->R, city, population);
        }
        else {
            if (strcmp(city, root->name) < 0) {
                root->L = add_to_tree(root->L, city, population);
            }
            else {
                root->R = add_to_tree(root->R, city, population);
            }
        }
    }

    return root;
}

int print_a(list_position head) {

    list_position temp = head->next;

    while (temp != NULL) {
        printf("\n%s\n", temp->name);
        print_inorder(temp->root);

        temp = temp->next;
    }

    return 0;
}

int print_inorder(tree_position root) {

    if (root == NULL) {
        return 0;
    }
    print_inorder(root->L);
    printf("  -%s : %d,\n", root->name, root->population);
    print_inorder(root->R);

    return 0;
}

int find_a(list_position head) {

    printf("Unesite traženu državu: ");

    char country[50];
    scanf("%[^\n]", country);

    list_position temp = head->next;

    while (temp != NULL) {

        if (strcmp(country, temp->name) == 0) {
            break;
        }

        temp = temp->next;
    }
    if (temp == NULL) {
        printf("country not found");
        return 0;
    }
    int min = 0;

    printf("Unesite minimalnu vrijednost stanovnika: ");
    scanf("%d", &min);

    print_cities(temp->root, min);

    return 0;
}

int print_cities(tree_position root, int min) {

    if (root == NULL) {
        return 0;
    }

    print_cities(root->L, min);

    if (root->population <= min) {
        return 0;
    }

    printf("%s : %d\n", root->name, root->population);
    print_cities(root->R, min);

    return 0;
}

// b)

int read_file_b(tree_position_b root, char* fileName) {

    FILE* file = NULL;
    file = fopen(fileName, "r");

    if (file == NULL) {
        printf("ERROR opening file");
        return 1;
    }

    char country[50] = "";
    char country_file[50] = "";

    if (fscanf(file, "%[^,], %s\n", country, country_file) == 2) {
        strcpy(root->name, country);

        root->head = (list_position_b)malloc(sizeof(list_Element_b));

        if (root->head == NULL) {
            printf("ERROR alocating memory");
            return 1;
        }

        read_country_file_b(root->head, country_file);
    }

    while (fscanf(file, "%[^,], %s\n", country, country_file) == 2) {
        country_to_tree(root, country, country_file);
    }

    fclose(file);
    return 0;
}

tree_position_b country_to_tree(tree_position_b root, char* country, char* country_file) {

    if (root == NULL) {
        root = (tree_position_b)malloc(sizeof(tree_Element_b));

        if (root == NULL) {
            printf("ERROR alocating memory");
            return NULL;
        }

        strcpy(root->name, country);
        root->L = NULL;
        root->R = NULL;
        root->head = (list_position_b)malloc(sizeof(list_Element_b));

        if (root->head == NULL) {
            printf("ERROR alocating memory");
            return NULL;
        }

        read_country_file_b(root->head, country_file);

    }
    else if (strcmp(country, root->name) < 0) {
        root->L = country_to_tree(root->L, country, country_file);
    }
    else {
        root->R = country_to_tree(root->R, country, country_file);
    }

    return root;
}

int read_country_file_b(list_position_b head, char* country_file) {

    FILE* file = NULL;
    file = fopen(country_file, "r");

    if (file == NULL) {
        printf("ERROR opening file");
        return 1;
    }

    char city[50] = "";
    int population = 0;

    while (fscanf(file, "%[^,], %d.\n", city, &population) == 2) {
        add_to_list(head, city, population);
    }

    fclose(file);
    return 0;
}

int add_to_list(list_position_b head, char* city, int population) {

    list_position_b newElement = (list_position_b)malloc(sizeof(list_Element));

    if (newElement == NULL) {
        printf("ERROR alocating memory");
        return 1;
    }

    strcpy(newElement->name, city);
    newElement->population = population;

    list_position_b temp = head;

    while (temp->next != NULL) {

        if (population > temp->next->population) {
            break;
        }
        else if (population == temp->next->population) {
            if (strcmp(city, temp->next->name) < 0) {
                break;
            }
        }

        temp = temp->next;
    }

    newElement->next = temp->next;
    temp->next = newElement;

    return 0;
}

int print_b(tree_position_b root) {

    if (root == NULL) {
        return 1;
    }

    print_b(root->L);
    printf("%s\n", root->name);
    print_list(root->head);
    print_b(root->R);

    return 0;
}

int print_list(list_position_b head) {

    if (head == NULL) {
        return 1;
    }

    list_position_b temp = head->next;

    while (temp != NULL) {
        printf("   -%s : %d,\n", temp->name, temp->population);

        temp = temp->next;
    }

    return 0;
}

int find_b(tree_position_b root, char* country) {

    int compare = strcmp(country, root->name);

    if (compare == 0) {
        print_cities_b(root->head);
    }
    else if (compare < 0) {
        find_b(root->L, country);
    }
    else {
        find_b(root->R, country);
    }

    return 0;
}

int print_cities_b(list_position_b head) {

    int min = 0;

    printf("Unesite minimalnu vrijednost stanovnika: ");
    scanf("%d", &min);

    list_position_b temp = head->next;

    while (temp != NULL) {

        if (temp->population > min) {
            printf("%s : %d\n", temp->name, temp->population);
        }

        temp = temp->next;
    }

    return 0;
}

int country_to_hash(hash_position* country_hash) {


    for (int i = 0; i < 11; i++) {
        country_hash[i] = NULL;
    }

    FILE* file = NULL;
    file = fopen("drzave.txt", "r");

    if (file == NULL) {
        printf("ERROR opening file");
        return 1;
    }

    char country[50];
    char country_file[50];

    while (fscanf(file, "%[^,], %s\n", country, country_file) == 2) {
        add_to_hash(country_hash, country, country_file);
    }

    return 0;
}

int add_to_hash(hash_position* country_hash, char* country, char* country_file) {

    int key = hash_key(country);

    hash_position new_hash = (hash_position)malloc(sizeof(Hash));

    if (new_hash == NULL) {
        printf("ERROR alocating memory");
        return 0;
    }

    strcpy(new_hash->name, country);
    new_hash->root = NULL;
    new_hash->next = NULL;

    hash_position temp = country_hash[key];

    if (temp == NULL) {
        country_hash[key] = new_hash;
    }
    else {
        while (temp->next != NULL) {

            if (strcmp(country, temp->next->name) < 0) {
                break;
            }

            temp = temp->next;
        }

        new_hash->next = temp->next;
        temp->next = new_hash;
    }

    tree_position root = (tree_position)malloc(sizeof(tree_Element));
    if (root == NULL) {
        printf("ERROR alocating memory");
        return 1;
    }
    root->L = NULL;
    root->R = NULL;

    new_hash->root = root;

    read_country_file(new_hash->root, country_file);

    return 0;
}

int hash_key(char* str) {
    int key = 0, i = 0;

    while (i < 5 && str[i] != '\0') {
        key += (int)str[i];
        i++;
    }

    return key % 11;
}

int print_hash(hash_position* country_hash) {

    int i = 0;

    for (i = 0; i < 11; i++) {
        hash_position temp = country_hash[i];

        while (temp != NULL) {
            printf("\n%s\n", temp->name);
            print_inorder(temp->root);

            temp = temp->next;
        }
    }

    return 0;
}