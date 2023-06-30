#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Структура спортсмена
struct athlete
{
    char surname[20];
    char country[20];
    float result;
    float personal_result;
};

// Головна структура
struct sport
{
    char type_sport[30];
    struct athlete first;
    struct athlete second;
    struct athlete third;
    struct sport* next;
};

// Глобальна змінна
struct sport *begin = NULL;
struct sport *end = NULL;
struct sport *temp = NULL;

// прототипи функцій
void LoadFromFile();
void CreateElement();
void inputElement();
void DeleteElement();
void DataCorrection();
void OutputAllData();
void OutputDataEnter();
void OutputImprovedRecord();
void SearchFromCountry();
void OutputTableCountry();
void SortingTypeSport();

int main()
{
    int num;
    // загрузка елементів
    LoadFromFile();

    while (1)
        {

        printf("||Menu:                                    ||\n");
        printf("||_________________________________________||\n");
        printf("|| 1. Create a new element                 ||\n");
        printf("|| 2. Delete an element                    ||\n");
        printf("|| 3. Data correction                      ||\n");
        printf("|| 4. Print all data                       ||\n");
        printf("|| 5. Print table of sports                ||\n");
        printf("|| 6. Print data about sport               ||\n");
        printf("|| 7. Print data about record athlete      ||\n");
        printf("|| 8. Print all athletes from a country    ||\n");
        printf("|| 9. Print of a summary table the country ||\n");
        printf("|| 10. Sort list by sport                  ||\n");
        printf("|| 0. Exit                                 ||\n");
        printf("||=========================================||");
        printf("\n  Enter your num: ");
        scanf("%d", &num);

        switch (num)
        {
            case 1:
                CreateElement();
                break;
            case 2:
                DeleteElement();
                break;
            case 3:
                DataCorrection();
                break;
            case 4:
                OutputAllData();
                break;
            case 5:
                PrintTable();
                break;
            case 6:
                OutputDataEnter();
                break;
            case 7:
                OutputImprovedRecord();
                break;
            case 8:
                SearchFromCountry();
                break;
            case 9:
                OutputTableCountry();
                break;
            case 10:
                SortingTypeSport();
                break;
            case 0:
                return 0;
            default:
                puts("You have entered an invalid number.");
                puts("Program functionality - [0 - 10]");
                break;
        }

        // очищення буферу
        fflush(stdin);
        printf("\nPlease, press any key...");
        getch();
        system("cls");
    }
}

void LoadFromFile()
{
    FILE* file = fopen("file.txt", "r");
    if (file == NULL)
    {
        puts("Error opening file");
        return;
    }

    char type_sport[30];
    while (fscanf(file, "%s", type_sport) == 1)
        {
        struct sport* new_element = (struct sport*)malloc(sizeof(struct sport));
        if (new_element == NULL)
        {
            puts("Error with memory");
            fclose(file);
            return;
        }

        strcpy(new_element->type_sport, type_sport);

        fscanf(file, "%s %s %f %f", new_element->first.surname, new_element->first.country, &new_element->first.result, &new_element->first.personal_result);
        fscanf(file, "%s %s %f %f", new_element->second.surname, new_element->second.country, &new_element->second.result, &new_element->second.personal_result);
        fscanf(file, "%s %s %f %f", new_element->third.surname, new_element->third.country, &new_element->third.result, &new_element->third.personal_result);

        new_element->next = NULL;

        if (begin == NULL)
        {
            begin = new_element;
            end = new_element;
        } else
        {
            end->next = new_element;
            end = new_element;
        }
    }

    fclose(file);
}


void CreateElement()
{
    if (begin == NULL)
        {
        begin = (struct sport*)malloc(sizeof(struct sport));
        if (begin == NULL)
        {
            puts("Error with memory");
            return;
        }

        end = begin;
        end->next = NULL;

        inputElement(begin);

        // файл
        FILE *file = fopen("file.txt", "a");
        if (file == NULL)
        {
            puts("Error opening file");
            return;
        }
        fprintf(file, "%s\n", begin->type_sport);
        fprintf(file, "%s %s %.2f %.2f\n", begin->first.surname, begin->first.country, begin->first.result, begin->first.personal_result);
        fprintf(file, "%s %s %.2f %.2f\n", begin->second.surname, begin->second.country, begin->second.result, begin->second.personal_result);
        fprintf(file, "%s %s %.2f %.2f\n", begin->third.surname, begin->third.country, begin->third.result, begin->third.personal_result);
        fclose(file);

        return;
    }

    if (begin != NULL)
        {
        temp = begin;
        begin = (struct sport*)malloc(sizeof(struct sport));
        if (begin == NULL)
        {
            puts("Error with memory");
            return;
        }

        begin->next = temp;

        inputElement(begin);

        // файл
        FILE *file = fopen("file.txt", "a");
        if (file == NULL)
        {
            puts("Error opening file");
            return;
        }
        fprintf(file, "%s\n", begin->type_sport);
        fprintf(file, "%s %s %.2f %.2f\n", begin->first.surname, begin->first.country, begin->first.result, begin->first.personal_result);
        fprintf(file, "%s %s %.2f %.2f\n", begin->second.surname, begin->second.country, begin->second.result, begin->second.personal_result);
        fprintf(file, "%s %s %.2f %.2f\n", begin->third.surname, begin->third.country, begin->third.result, begin->third.personal_result);
        fclose(file);

        return;
    }
}

void inputElement(struct sport *element)
{
    printf("Enter type of sport: ");
    while (scanf("%29s", element->type_sport) != 1)
    {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    // first

    puts("\nFirst:");
    printf("Enter surname: ");
    while (scanf("%19s", element->first.surname) != 1)
    {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    printf("Enter country: ");
    while (scanf("%19s", element->first.country) != 1)
    {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    printf("Enter result: ");
    while (scanf("%f", &(element->first.result)) != 1)
    {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    printf("Enter personal result: ");
    while (scanf("%f", &(element->first.personal_result)) != 1)
    {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }
    // second
    puts("\nSecond:");
    printf("Enter surname: ");
    while (scanf("%19s", element->second.surname) != 1)
    {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    printf("Enter country: ");
    while (scanf("%19s", element->second.country) != 1)
    {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    printf("Enter result: ");
    while (scanf("%f", &(element->second.result)) != 1)
    {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    printf("Enter personal result: ");
    while (scanf("%f", &(element->second.personal_result)) != 1)
    {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    // third

    puts("\nThird:");
    printf("Enter surname: ");
    while (scanf("%19s", element->third.surname) != 1)
    {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    printf("Enter country: ");
    while (scanf("%19s", element->third.country) != 1)
    {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    printf("Enter result: ");
    while (scanf("%f", &(element->third.result)) != 1)
    {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    printf("Enter personal result: ");
    while (scanf("%f", &(element->third.personal_result)) != 1)
    {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }
}

void DeleteElement()
{
    if (begin == NULL)
    {
        printf("List is empty\n");
        return;
    }

    char type_sport[30];
    printf("Enter the type of sport to delete: ");
    scanf("%s", type_sport);

    struct sport* current = begin;
    struct sport* previous = NULL;

    // Пошук елемента за типом спорту
    while (current != NULL)
    {
        if (strcmp(current->type_sport, type_sport) == 0)
        {
            break;  // найшли елемент
        }
        previous = current;
        current = current->next;
    }

    // Перевірка, чи було знайдено елемент
    if (current == NULL)
    {
        printf("Sport of type %s not found\n", type_sport);
        return;
    }

    // видалення
    if (current == begin)
    {
        begin = begin->next;
    } else
    {
        previous->next = current->next;
    }

    // видалення пам'яті
    free(current);

    printf("Sport of type %s has been deleted\n", type_sport);

    // оновлення файлу
    FILE *file = fopen("file.txt", "w");
    if (file == NULL)
    {
        puts("Error opening file");
        return;
    }

    // запис оновленних данних до файлу
    struct sport* current_element = begin;
    while (current_element != NULL)
    {
        fprintf(file, "%s\n", current_element->type_sport);
        fprintf(file, "%s %s %.2f %.2f\n", current_element->first.surname, current_element->first.country, current_element->first.result, current_element->first.personal_result);
        fprintf(file, "%s %s %.2f %.2f\n", current_element->second.surname, current_element->second.country, current_element->second.result, current_element->second.personal_result);
        fprintf(file, "%s %s %.2f %.2f\n", current_element->third.surname, current_element->third.country, current_element->third.result, current_element->third.personal_result);
        current_element = current_element->next;
    }

    fclose(file);
}

void DataCorrection()
{
    if (begin == NULL)
    {
        printf("List is empty\n");
        return;
    }

    char type_sport[30];
    printf("Enter the type of sport to edit: ");
    scanf("%s", type_sport);

    struct sport* current = begin;

    // Пошук елемента за типом спорту
    while (current != NULL)
    {
        if (strcmp(current->type_sport, type_sport) == 0)
        {
            break;  // найшли елемент
        }
        current = current->next;
    }

    // перевирка
    if (current == NULL)
    {
        printf("Sport of type %s not found\n", type_sport);
        return;
    }

    // редагування данних
    inputElementForCorrection(current);

    printf("Sport of type %s has been corrected\n", type_sport);

    // оновлення файлу
    FILE* file = fopen("data.txt", "w");
    if (file == NULL)
    {
        puts("Error opening file!");
        return;
    }

    // запис до файла
    struct sport* current_element = begin;
    while (current_element != NULL)
    {
        fprintf(file, "%s\n", current_element->type_sport);
        fprintf(file, "%s %s %.2f %.2f\n", current_element->first.surname, current_element->first.country, current_element->first.result, current_element->first.personal_result);
        fprintf(file, "%s %s %.2f %.2f\n", current_element->second.surname, current_element->second.country, current_element->second.result, current_element->second.personal_result);
        fprintf(file, "%s %s %.2f %.2f\n", current_element->third.surname, current_element->third.country, current_element->third.result, current_element->third.personal_result);
        current_element = current_element->next;
    }

    fclose(file);
}

void inputElementForCorrection(struct sport* element)
{
    printf("Enter new type of sport: ");
    while (scanf("%29s", element->type_sport) != 1)
    {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    // first

    puts("\nFirst:");
    printf("Enter new surname: ");
    while (scanf("%19s", element->first.surname) != 1) {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    printf("Enter new country: ");
    while (scanf("%19s", element->first.country) != 1) {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    printf("Enter new result: ");
    while (scanf("%f", &(element->first.result)) != 1) {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    printf("Enter new personal result: ");
    while (scanf("%f", &(element->first.personal_result)) != 1) {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    // second

    puts("\nSecond:");
    printf("Enter new surname: ");
    while (scanf("%19s", element->second.surname) != 1) {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    printf("Enter new country: ");
    while (scanf("%19s", element->second.country) != 1) {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    printf("Enter new result: ");
    while (scanf("%f", &(element->second.result)) != 1) {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    printf("Enter new personal result: ");
    while (scanf("%f", &(element->second.personal_result)) != 1) {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    // third

    puts("\nThird:");
    printf("Enter new surname: ");
    while (scanf("%19s", element->third.surname) != 1) {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    printf("Enter new country: ");
    while (scanf("%19s", element->third.country) != 1) {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    printf("Enter new result: ");
    while (scanf("%f", &(element->third.result)) != 1) {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }

    printf("Enter new personal result: ");
    while (scanf("%f", &(element->third.personal_result)) != 1) {
        puts("Invalid input. Please try again.");
        fflush(stdin);
    }
}

void OutputAllData()
{
    FILE* file = fopen("file.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    struct sport sport_data;
    while (fscanf(file, "%s", sport_data.type_sport) == 1) {
        fscanf(file, "%s %s %f %f", sport_data.first.surname, sport_data.first.country, &sport_data.first.result, &sport_data.first.personal_result);
        fscanf(file, "%s %s %f %f", sport_data.second.surname, sport_data.second.country, &sport_data.second.result, &sport_data.second.personal_result);
        fscanf(file, "%s %s %f %f", sport_data.third.surname, sport_data.third.country, &sport_data.third.result, &sport_data.third.personal_result);
        printf("==============================================================\n");
        printf("|| Type of sport: %s\n", sport_data.type_sport);
        printf("|| First athlete: %s, %s, %.2f, %.2f\n", sport_data.first.surname, sport_data.first.country, sport_data.first.result, sport_data.first.personal_result);
        printf("|| Second athlete: %s, %s, %.2f, %.2f\n", sport_data.second.surname, sport_data.second.country, sport_data.second.result, sport_data.second.personal_result);
        printf("|| Third athlete: %s, %s, %.2f, %.2f\n", sport_data.third.surname, sport_data.third.country, sport_data.third.result, sport_data.third.personal_result);
        printf("==============================================================\n");
    }

    fclose(file);
}


void PrintTable()
{
    FILE* file = fopen("file.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("=====================================================================================\n");
    printf("|| %-20s || %-20s || %-10s || %-16s ||\n", "Surname", "Country", "Result", "Personal Result");
    printf("=====================================================================================\n");

    struct sport sport_data;
    while (fscanf(file, "%s", sport_data.type_sport) == 1) {
        fscanf(file, "%s %s %f %f", sport_data.first.surname, sport_data.first.country, &sport_data.first.result, &sport_data.first.personal_result);
        fscanf(file, "%s %s %f %f", sport_data.second.surname, sport_data.second.country, &sport_data.second.result, &sport_data.second.personal_result);
        fscanf(file, "%s %s %f %f", sport_data.third.surname, sport_data.third.country, &sport_data.third.result, &sport_data.third.personal_result);

        printf("|| %-20s || %-20s || %-10.2f || %-16.2f ||\n", sport_data.first.surname, sport_data.first.country, sport_data.first.result, sport_data.first.personal_result);
        printf("|| %-20s || %-20s || %-10.2f || %-16.2f ||\n", sport_data.second.surname, sport_data.second.country, sport_data.second.result, sport_data.second.personal_result);
        printf("|| %-20s || %-20s || %-10.2f || %-16.2f ||\n", sport_data.third.surname, sport_data.third.country, sport_data.third.result, sport_data.third.personal_result);
        printf("=====================================================================================\n");
    }

    fclose(file);
}

void OutputDataEnter() {
    if (begin == NULL) {
        printf("List is empty\n");
        return;
    }

    char type_sport[30];
    printf("Enter the type of sport: ");
    scanf("%s", type_sport);

    struct sport* current = begin;

    // Пошук елемента за типом спорту
    while (current != NULL) {
        if (strcmp(current->type_sport, type_sport) == 0) {
            break;  // нашли елемент
        }
        current = current->next;
    }

    // перевірка
    if (current == NULL) {
        printf("Sport of type %s not found\n", type_sport);
        return;
    }
    printf("==============================================================\n");
    printf("|| Type of sport: %s\n", current->type_sport);
    printf("|| First athlete: %s, %s, %.2f, %.2f\n", current->first.surname, current->first.country, current->first.result, current->first.personal_result);
    printf("|| Second athlete: %s, %s, %.2f, %.2f\n", current->second.surname, current->second.country, current->second.result, current->second.personal_result);
    printf("|| Third athlete: %s, %s, %.2f, %.2f\n", current->third.surname, current->third.country, current->third.result, current->third.personal_result);
    printf("==============================================================\n");
}

void OutputImprovedRecord()
{
    if (begin == NULL) {
        printf("List is empty\n");
        return;
    }
    FILE* file = fopen("file.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    struct sport sport_data;
    while (fscanf(file, "%s", sport_data.type_sport) == 1)
{
        fscanf(file, "%s %s %f %f", sport_data.first.surname, sport_data.first.country, &sport_data.first.result, &sport_data.first.personal_result);
        fscanf(file, "%s %s %f %f", sport_data.second.surname, sport_data.second.country, &sport_data.second.result, &sport_data.second.personal_result);
        fscanf(file, "%s %s %f %f", sport_data.third.surname, sport_data.third.country, &sport_data.third.result, &sport_data.third.personal_result);

        if (sport_data.first.personal_result < sport_data.first.result || sport_data.second.personal_result < sport_data.second.result || sport_data.third.personal_result < sport_data.third.result)
        {
            printf("==============================================================\n");
            printf("|| Type of sport: %s\n", sport_data.type_sport);
            if (sport_data.first.personal_result < sport_data.first.result)
            {
                printf("|| Athlete %s: %.2f --> %.2f\n", sport_data.first.surname,sport_data.first.personal_result, sport_data.first.result);
            }
            if (sport_data.second.personal_result < sport_data.second.result)
            {
                printf("|| Athlete %s: %.2f --> %.2f\n", sport_data.second.surname, sport_data.second.personal_result, sport_data.second.result);
            }
            if (sport_data.third.personal_result < sport_data.third.result)
            {
                printf("|| Athlete %s: %.2f --> %.2f\n", sport_data.third.surname, sport_data.third.personal_result, sport_data.third.result);
            }
            printf("==============================================================\n");
            printf("\n");
        }
    }

    fclose(file);
}


void SearchFromCountry()
{
    if (begin == NULL) {
        printf("List is empty\n");
        return;
    }
        FILE* file = fopen("file.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    char country[20];
    printf("Enter the country to search: ");
    scanf("%20s", country);

    struct sport* current = begin;
    printf("========================================================\n");
    while (current != NULL) {
        if (strcmp(current->first.country, country) == 0) {
            printf("|| Type of sport: %s\n", current->type_sport);
            printf("|| Athlete: %s, %s\n", current->first.surname, current->first.country);
            printf("|| Result: %.2f\n", current->first.result);
            printf("\n");
        }

        if (strcmp(current->second.country, country) == 0) {
            printf("|| Type of sport: %s\n", current->type_sport);
            printf("|| Athlete: %s, %s\n", current->second.surname, current->second.country);
            printf("|| Result: %.2f\n", current->second.result);
            printf("\n");
        }

        if (strcmp(current->third.country, country) == 0) {
            printf("|| Type of sport: %s\n", current->type_sport);
            printf("|| Athlete: %s, %s\n", current->third.surname, current->third.country);
            printf("|| Result: %.2f\n", current->third.result);
            printf("\n");
        }
        current = current->next;
    }
    printf("========================================================\n");
}

void OutputTableCountry()
{
    if (begin == NULL) {
        printf("List is empty\n");
        return;
    }
    FILE* file = fopen("file.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    char country[20];
    printf("Enter the country to display: ");
    scanf("%19s", country);

    struct sport* current = begin;
    int first_place = 0;
    int second_place = 0;
    int third_place = 0;

    while (current != NULL) {
        if (strcmp(current->first.country, country) == 0) {
            first_place++;
        }
        if (strcmp(current->second.country, country) == 0) {
            second_place++;
        }
        if (strcmp(current->third.country, country) == 0) {
            third_place++;
        }
        current = current->next;
    }
    printf("==============================================================\n");
    printf("|| Country: %s\n", country);
    printf("|| (*) First places: %d\n", first_place);
    printf("|| (**) Second places: %d\n", second_place);
    printf("|| (***) Third places: %d\n", third_place);
    printf("|| All prize places are occupied: %d\n", first_place+second_place+third_place);
    printf("==============================================================\n");
}

void SortingTypeSport()
{
    // перевірка
    if (begin == NULL) {
        printf("List is empty\n");
        return;
    }

    // тимчасовий список для сортирування
    struct sport* sortedList = NULL;

    // перебір кожного елемента в основному списку
    struct sport* current = begin;
    while (current != NULL) {
        // новий елемент для нового списку
        struct sport* newElement = (struct sport*)malloc(sizeof(struct sport));
        if (newElement == NULL) {
            printf("Memory allocation failed\n");
            return;
        }

        // копиюємо данні
        strcpy(newElement->type_sport, current->type_sport);
        memcpy(&newElement->first, &current->first, sizeof(struct athlete));
        memcpy(&newElement->second, &current->second, sizeof(struct athlete));
        memcpy(&newElement->third, &current->third, sizeof(struct athlete));

        // вставляємо новий елемент у відсортований список
        if (sortedList == NULL)
        {
            sortedList = newElement;
            sortedList->next = NULL;
        } else {
            struct sport* temp = sortedList;
            struct sport* prev = NULL;

            // дивимось куда вставляємо
            while (temp != NULL && strcmp(newElement->type_sport, temp->type_sport) > 0) {
                prev = temp;
                temp = temp->next;
            }

            if (prev == NULL)
            {
                newElement->next = sortedList;
                sortedList = newElement;
            } else
            {
                prev->next = newElement;
                newElement->next = temp;
            }
        }

        current = current->next;
    }

    // виведення відсортованого списку
    printf("Sorted file:\n");
    printf("==============================================================\n");
    struct sport* temp = sortedList;
    while (temp != NULL)
    {
        printf("|| Type of sport: %s\n", temp->type_sport);
        printf("|| First: %s %s %.2f %.2f\n", temp->first.surname, temp->first.country, temp->first.result, temp->first.personal_result);
        printf("|| Second: %s %s %.2f %.2f\n", temp->second.surname, temp->second.country, temp->second.result, temp->second.personal_result);
        printf("|| Third: %s %s %.2f %.2f\n", temp->third.surname, temp->third.country, temp->third.result, temp->third.personal_result);
        printf("\n");
        temp = temp->next;
    }
    printf("==============================================================\n");
    // звільнення пам'яті
    while (sortedList != NULL)
    {
        struct sport* temp = sortedList;
        sortedList = sortedList->next;
        free(temp);
    }
}



