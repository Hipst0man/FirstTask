#include <iostream> //this is only for cout and tolower
#include <stdlib.h>
#include <string.h>


// Initializes list
// void StringListInit(char*** list); 
void StringListInit(char*** list)
{
    if (*list) return;
    *list = nullptr;
    list[0] = nullptr;
}

// Destroy list and set pointer to NULL.
// void StringListDestroy(char*** list);
void StringListDestroy(char*** list)
{
    if (!*list) return;
    char** current(*list), **previous(nullptr);
    
    while(current[1])
    {
        previous = current;
        current = (char**)current[1];
        free(previous[0]);
        free(previous);
    }
    free(current[0]);
    free(current);
    
    *list = nullptr;
    list[0] = nullptr;
}

// Inserts value at the end of the list.
// void StringListAdd(char*** list, String str);
void StringListAdd(char*** head, const char* val)
{
    if (!val[0]) return;

    char** node = (char**)malloc(2 * sizeof(char *));

    node[0] = (char*)malloc(strlen(val)+1);
    strcpy(node[0], val);
    node[1] = NULL;

    if (*head == NULL) *head = node;
    else 
    {
        char** temp;

        temp = *head;
        
        while (temp[1]!=NULL) 
        {
            temp = (char **)temp[1];
        }

        temp[1] = (char *)node;
    }
}

void display(char** head)
{
    char **temp;

    temp = head;
    if(!temp) std::cout<<"List is empty\n";
    else
    {
        std::cout << "display:\n";
        while (temp!=NULL) 
        {
            std::cout<<temp[0]<<std::endl;
            temp = (char **)temp[1];
        }
        std::cout<<std::endl;
    }
}

//Additional
//Removes node from tail
void popBack(char*** head)
{
    if(!*head) return;

    char** current(*head), **previous(nullptr);
    
    if(!current[1])
    {
        free(current[0]);
        free(current);
        *head = nullptr;
        head[0] = nullptr;
    }

    else
    {
        while(current[1]!=nullptr)
        {
            previous = current;
            current = (char**)current[1];
        }
        previous[1] = nullptr;
        free(current[0]);
        free(current);
       
    }
}

// Returns the number of items in the list.
// int StringListSize(char** list);  
int StringListSize (char** list)
{
    if(!list) return 0;

    int counter(0);
    
    while(list!=nullptr)
    {
        counter++;
        list = (char**)list[1];
    }
    return counter;
}

// Returns the index position of the first occurrence of str in the list.     
// int StringListIndexOf(char** list, char* str);        
int StringListIndexOf(char** list, const char* str)
{
    if(!list || !str[0]) return -2;
    
    int counter(0);
    
    while(list!=nullptr)
    {
        if(!strcmp(list[0], str)) return counter;
        counter++;
        list = (char**)list[1];
    }

    return -1;
}

// Removes all occurrences of str in the list.
// void StringListRemove(char*** list, String str);
void StringListRemove(char*** list, const char* str)    
{
    if(!*list || !str[0]) return;

    char** current(*list), **previous(nullptr);
  
    while (current!=nullptr)
    {
        if(current == *list && !strcmp(current[0], str))
        {
            *list = (char**)current[1];
            free(current[0]);
            free(current);
            if(!*list) return;
            current = *list;
            
        }

        else if(!strcmp(current[0], str))
        {
            previous[1] = current[1];
            free(current[0]);
            free(current);
            current = (char**)previous[1];
        }

        else 
        {  
            previous = current;
            current = (char **)current[1];
        }
        
    }

}

// Removes duplicate entries from the list.
// void StringListRemoveDuplicates(char** list);
void StringListRemoveDuplicates(char** list)
{
    if(!list) return;
    char** current(list), **previous(nullptr);

    while(current!=nullptr)
    {
        char** next((char**)current[1]);

        StringListRemove(&next, current[0]);
        previous = current;
        previous[1] = (char*) next;
        current = next;
    }
}

// Replaces every occurrence of the before, in each of the string lists's strings, with after.
// void StringListReplaceInStrings(char** list, char* before, char* after);
void StringListReplaceInStrings(char** list, const char* before, const char* after)
{
    if(!list || !before[0] || !after[0]) return;

    char** current(list);

    while (current!=nullptr)
    {
        if (!strcmp(current[0], before))
        {
            if (strlen(after) != strlen(current[0]))
            {
                current[0] = (char*)realloc(current[0], strlen(after)+1);
            }
            
            strcpy(current[0], after);
        }
        
        current = (char **)current[1];
    }

}

// Sorts the list of strings in ascending order
// void StringListSort(char** list);
void StringListSort(char** list)
{
    if(!list) return;

    char** left(list), **right((char**)list[1]);

    while(left[1])
    {   
        while(right)
        {
            char rightLower [strlen(right[0]) + 1];
            char leftLower [strlen(left[0]) + 1];

            for (int i = 0; i <= strlen(left[0]); i++)
            {
                leftLower[i] = tolower(left[0][i]);
            }

            for (int i = 0; i <= strlen(right[0]); i++)
            {
                rightLower[i] = tolower(right[0][i]);
            }

            if(strcmp(leftLower, rightLower) > 0 )
            {
                char tmp [strlen(leftLower)+1];
                strcpy(tmp, left[0]);
                strcpy(left[0], right[0]);
                strcpy(right[0], tmp);
            }
            
            right = (char**)right[1];
        }
        
        left = (char**)left[1];
        right = (char**)left[1];
    } 
}

int main()
{

    char **list {nullptr};
    
    StringListInit(&list);
    
    
    StringListAdd(&list, "city");
    StringListAdd(&list, "friend");
    StringListAdd(&list, "book");
    StringListAdd(&list, "apple");
    StringListAdd(&list, "Cat");
    
    display(list);

    StringListSort(list);

    display(list);

    StringListAdd(&list, "Cat");
    StringListAdd(&list, "friend");
    StringListAdd(&list, "apple");


    display(list);

    StringListRemoveDuplicates(list);

    display(list);


    return 0;

}

