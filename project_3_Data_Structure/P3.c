#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct information
{

    char  courseName [30];
    int CrediHours;
    char CourseCode[30];
    char department[30];
    char  topic [1000];


} info;
struct Node
{

    info data;
    struct Node* left;
    struct Node* right;

    //height = 0; the initial state (leaf node)
    int height;//HOW MANY THE MAXIMUM NUMBER OF NODES UNDER THIS NODE
};
typedef struct Node *AVL, *N;//Shortcuts

AVL tree=NULL;
AVL insert(AVL root, info data);//FOR ADD NEW NODE ON TREE




//GLOBAL DATA FIELDS
struct Node** Courses = NULL;//CREATE EMPTY HASHTABLE CALLED "patients" FOR SAVE THE TREE NODES INFORMATION
int CourseSize = 0;//THE CURRENT SIZE OF THE patients HASH TABLE
int CoursesOldSize = 0;//THE SIZE OF THE OLD patients HASH TABLE
int elementsSize = 0;//THE NUMBER OF PATIENTS IN THE patients HASH TABLE
char deleteLine[500];//FOR DELETE LINE WHEN READ FROM CONSOLE



int main()
{
    int flag = 0;


    while (true)
    {

        PrintMenue();
        readFile();
        printf("\n");
        scanf("%d", &flag);
        int s=0;
        if (flag == 8)
            break;

        switch (flag)
        {

        case 1:


            printf("\nQuadratic hash table\n");
            printCourses();
            printf("\nDouble hash table\n");
            printCourses1();
            break;

        case 2:

            printf("\nSize of Quadratic hash table and load factor\n");
            printHashTableSize();
            printf("\nSize of Double hash table and load factor\n");
            printHashTableSize1();
            break;


        case 3:
            printHashMethodName();
            break;

        case 4:
            insertCourse();

            break;
        case 5:
            printf("Enter 1 to search in hash 1\n");
            printf("Enter 2 to search in hash 2\n");
            scanf("%d",&s);


            if(s==1)
                searchAboutCourse();

            else if(s==2)
                searchAboutCourse1();

            break;

        case 6:
            deleteCourse();
            break;
        case 7:
            break;
        case 8:
            saveHashTable();
            return 0;

            break;


        }

    }
}

void PrintMenue()  //only print menue
{

    printf("\n 1. Print hashed tables (including empty spots)");
    printf("\n 2. Print out table size and the load factor");
    printf("\n 3. Print out the used hash functions");
    printf("\n 4. Insert a new record to hash table (insertion will be done on both hash tables)");
    printf("\n 5. Search for a specific word (specify which table to search in)");
    printf("\n 6. Delete a specific record (from both tables)");
    printf("\n 7. Compare between the two methods in terms of number of collisions occurred.");
    printf("\n 8. Save hash table " );

}

int max(int n1, int n2)   //function to return max
{
    return (n1>n2) ? n1 : n2;
}


int getHeight(N node)  //function to return height of tree
{
    if(node == NULL)
        return -1;//WHEN WE CALL RIGHT AND LEFT OF THE  NODE which values it null WE USE THIS CONDITION
    return node->height;
}


int getBalanced(N node)   //function to return the balance of tree
{

    if(node == NULL)
        return 0;//WHEN ANY MISTAKE HAPPENED SO DON'T MAKE ROTATIONS

    return getHeight(node->left) - getHeight(node->right);//BALANCED = HEIGHT OF LEFT SUB TREE - HEIGHT OF RIGHT SUB TREE

}


bool isEmpty(AVL root)   //function to check if the tree is empty
{
    return root == NULL;
}


N newNode(info data)    //function to create node of information
{

    N node = (N) malloc(sizeof (struct Node));
    node->left = node->right = NULL;
    node->height = 0;


    strcpy(node->data.courseName, data.courseName);
    node->data.CrediHours = data.CrediHours;
    strcpy(node->data.CourseCode, data.CourseCode);

    strcpy(node->data.department, data.department);
    strcpy(node->data.topic, data.topic);


    return node;

}


N leftRotate(N node)    //function to work leftRotate
{

    N mid = node->right;
    N leftOfMid = mid->left;

    //Perform rotation
    mid->left = node;
    node->right = leftOfMid;

    //Update heights

    node->height = max(getHeight(node->left), getHeight(node->right)) +1 ;//firstly we should get height of the left sub tree (10)
    mid->height =  max(getHeight(mid->left), getHeight(mid->right)) +1;//secondly the we can get the correct height of the new root (20)

    return mid;
}

N rightRotate(N node)      //function to work rightRotate
{

    N mid = node->left;
    N rightOfMid = mid->right;

    // Perform rotation
    mid->right = node;
    node->left = rightOfMid;

    //Update heights
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;//firstly we should get height of the right sub tree (30)
    mid->height =  max(getHeight(mid->left), getHeight(mid->right)) + 1;//secondly the we can get the correct height of the new root (20)

    return mid;
}


AVL insert(AVL root, info data)   //function to insert new node in tree
{


    //if the new node is leaf
    if(root == NULL)
        return newNode(data);
    //if the new node is less than the parent
    else if (strcmp(data.courseName, root->data.courseName) < 0)
        root->left = insert(root->left, data);
    //if the new node is more than the parent
    else if (strcmp(data.courseName, root->data.courseName) > 0)
        root->right = insert(root->right, data);



    //update the height of the  nodes
    root->height = max(getHeight(root->right), getHeight(root->left)) + 1 ;
    int balanced = getBalanced(root);


    // LEFT LEFT Case : RIGHT ROTATION
    if(balanced > 1 && (strcmp(data.courseName, root->left->data.courseName) < 0))
        root = rightRotate(root);

    // RIGHT RIGHT Case : LEFT ROTATION
    if(balanced < -1 && (strcmp(data.courseName, root->right->data.courseName) > 0))
        root = leftRotate(root);



    // RIGHT LEFT Case : RIGHT ROTATION THEN LEFT ROTATION
    if(balanced < -1 && (strcmp(data.courseName, root->right->data.courseName) < 0))
    {
        root->right = rightRotate(root->right); // this for make it like RIGHT RIGHT FORM
        root = leftRotate(root);
    }



    // LEFT RIGHT Case : LEFT ROTATION THEN RIGHT ROTATION
    if(balanced > 1 && (strcmp(data.courseName, root->left->data.courseName) > 0))
    {
        root->left = leftRotate(root->left);// this for make it like LEFT LEFT FORM
        root = rightRotate(root);
    }



    return  root;
}


AVL makeEmpty(AVL root)
{

    if (root != NULL)
    {
        makeEmpty(root->right);
        makeEmpty(root->left);
        free(root);
    }

    return  NULL;
}


N findMin(AVL root)   //function to find the minimum node in tree
{
    if (root != NULL)
    {
        if (root->left != NULL)
            return findMin(root->left);
    }
    return root;
}


N findMax(AVL root)   //function to find the maximum node in tree
{
    if (root != NULL)
    {
        if (root->right != NULL)
            return findMax(root->right) ;
    }
    return root;
}

void readFile()   //function to read information in file
{

    FILE *fp = fopen("offered_courses.txt", "r"); // for open the file

    if(fp == NULL)
        printf("THE FILE NOT FOUNDED"); // print error if the file empty
    else
    {


        char line[500];//the maximum length of each line in file


        //FOR SAVE ALL LINES IN THE INPUT FILE AS NODES IN THE AVL TREE
        while (fgets(line, 500, fp))
        {

            int *splitBy = "[#:/\n]";//divide the line when read "#/:\n"
            char *edge = strtok(line, splitBy);//save the divided edge line
            int flag = 0;//counter for the number of edges at line
            info data;//save the line information at data

            while (edge != NULL)
            {

                if (flag == 0)
                    strcpy(data.courseName, edge);//for save the nameCourse

                else if (flag == 1)//for save the criditHoure
                {
                    data.CrediHours = 0;
                    for (int i = 0; edge[i] != '\0'; ++i)
                        data.CrediHours = (edge[i] - 48) + data.CrediHours * 10;

                }
                else if (flag == 2)   //for save the courseCode
                    strcpy(data.CourseCode, edge);
                else if (flag == 3) //for save the department of course
                    strcpy(data.department, edge);


                else if (flag == 4) //for save the topic of course
                    strcpy(data.topic, edge);

                flag++;
                if (flag == 5) //when finish read the line
                    tree = insert(tree, data);//add new node to tree

                edge = strtok(NULL, splitBy);// for make new edge from the line
            }


        }
    }


    fclose(fp);//close the input file


}





//-----------------------------------------------HASH TABLE -----------------------------------------------------

int hash(char courseName[30],int tableSize)   //quadratic table
{

    int sum = 0;
    for (int i = 0; courseName[i] != '\0'; ++i)
        sum = (courseName[i])% tableSize;

    return sum ;
}
int hash1(char courseName[30], int tableSize)  //double table
{

    int sum=0;

    for(int i=0; courseName[i] != '\0'; ++i)
        sum=((courseName[i]+i*courseName[i])%tableSize);
    return sum;

}


bool isPrime(int x) //to check if number is prime
{
    // base case
    if (x <= 1)
        return false;

    // Check from 2 to (n-1) / 2
    for (int i = 2; i <= x/2; i++)
        if (x % i == 0)
            return false;

    return true;
}


int reHash(int oldSize)
{

    int newSize = oldSize * 2;

    while (!isPrime(newSize))
        newSize++;

    return newSize;
}


int deHash(int oldSize)
{

    int newSize = oldSize / 2;

    while (!isPrime(newSize))
        newSize--;

    return newSize;
}


bool hashCheck(int function, int i, int size, struct Node** hashTable)
{

    int c = (function + (i*i)) % size;//Quadratic Hashing Function
    if(hashTable[c] == NULL)
        return false;//RETURN FALSE FOR STOP THE LOOP IN addPatient and updateHashTable Methods

    return true;
}

void createHashTable()
{

    CourseSize = reHash(CourseSize);//FOR DEFINE INITIAL SIZE FOR THE HASH TABLE
    Courses = (struct Node**) malloc((sizeof (struct Node*)) * CourseSize);//FOR CREATE THE COURSES  HASH TABLE
    for (int i = 0; i < CourseSize; ++i)
        Courses[i] = NULL;


    addCourse(tree);//FOR ADD THE NODES FROM THE AVL TREE TO THE COURSES HASH TABLE

}


void addCourse(AVL root)  //FUNCTION TO ADD COURSES
{


    if (root != NULL)
    {


        addCourse(root->left);//ADD THE COURSES WHICH EXIST AT LEFT SUBTREE
        addCourse(root->right);//ADD THE COURSES WHICH EXIST AT RIGHT SUBTREE


        if ( (int) (0.75 * CourseSize) <= elementsSize)//WHEN THE TABLE 75% FULL THEN UPDATE IT
            updateHashTable(1);

        info save = root->data;
        N node = newNode(save);
        free(root);


        int i = 0;
        int index = hash(node->data.courseName, CourseSize);//RETURN THE INDEX OF THE COURSE NAME
        bool update = false;//FOR CHECK IF THE HASH TABLE IS FULL OR NOT

        //FOR SEARCH ABOUT THE EMPTY POSITION AT HASH TABLE
        while (hashCheck(index, i, CourseSize, Courses))
        {

            if (i > CourseSize)
            {
                update = true;//WHEN THE VALUE CAN'T FIND ANY PLACE FOR IT IN THE ARRAY
                break;
            }

            i++;
        }


        if (update)
        {
            updateHashTable(1);//FOR UPDATE THE HASH TABLE
            addCourse(node);
        }
        else
        {
            index = (index + (i*i)) % CourseSize;//FOR RETURN THE CORRECT POSITION AT HASH TABLE FOR INSERT THE COURSES
            Courses[index] = node;
            elementsSize++;
        }

    }

}

void updateHashTable(int flag)  //FUNCTION TO UPDATE HASH TABLE
{


    int oldSize = CourseSize;//SAVE THE OLD HASH TABLE SIZE

    if (flag == 1)
        CourseSize = reHash(CourseSize);//UPDATE THE HASH TABLE SIZE (increase)
    else if (flag == 2)
        CourseSize = deHash(CourseSize);//UPDATE THE HASH TABLE SIZE (decrease)

    struct Node** newHashTable = (struct Node**) malloc((sizeof (struct Node*)) * CourseSize);//CREATE NEW PATIENTS HASH TABLE
    for (int i = 0; i < CourseSize; ++i)
        newHashTable[i] = NULL;


    //RE-INSERT COURSES FROM OLD HASH TABLE TO THE NEW HASH TABLE
    for (int i = 0; i < oldSize; ++i)
    {

        if(Courses[i] != NULL)
        {

            int index = hash(Courses[i]->data.courseName, CourseSize);
            int j = 0;

            while (hashCheck(index, j, CourseSize, newHashTable))
                j++;




            index = (index + (j*j)) % CourseSize;
            newHashTable[index] = Courses[i];



        }

    }

    free(Courses);//DELETE THE OLD HASH TABLE : this don't delete the nodes in the old table
    Courses = newHashTable;




    //FOR UPDATE THE SIZE OF THE CoursesOldSize
    if(flag == 1)
        CoursesOldSize = oldSize;
    if(flag == 2)
    {

        if (CourseSize != 2)
            CoursesOldSize = deHash(CourseSize);
        else
            CoursesOldSize = 0;//INITIAL STATE

    }




}

//-------------------------------------Operation  of an Courses Hash Table---------------------------------------------


void printCourses()
{

    for (int i = 0; i < CourseSize; ++i)
    {
        printf("Index : %d\t Name: %s\n", i, Courses[i]->data.courseName);
    }

}
void printCourses1()
{

    for (int i = 0; i < CourseSize; ++i)
    {
        printf("Index : %d\t Name: %s\n", i, Courses[i]->data.courseName);
    }

}



void printHashTableSize()  //print size and load factor
{

    printf("\nThe Size Of Hash Table is : %d\nThe Number Of Elements In The Table is : %d\nload factor : %f\n", CourseSize,elementsSize,(double)elementsSize/CourseSize);

}

void printHashTableSize1()  //print size and load factor
{

    printf("\nThe Size Of Hash Table is : %d\nThe Number Of Elements In The Table is : %d\nload factor :%f\n", CourseSize,elementsSize,((double)elementsSize/CourseSize));

}

void printHashMethodName()  //print type of hash table
{
    printf("\n Table one -->I USED Quadratic Hashing\n");
    printf("\nTable two -->I USED DOUBLE Hashing \n");

}

void insertCourse()  //insert to courses in hash table
{


    printf("Insert The Course information\n");
    info data;


    printf("Enter the Name of course : ");
    gets(deleteLine);
    gets(data.courseName);
    printf("\n");

    printf("Enter the CriditHoure : ");
    scanf("%d", &data.CrediHours);
    printf("\n");

    printf("Enter the Course Code  : ");
    scanf("%s",data.CourseCode);

    printf("\n");

    printf("Enter the department of course : ");
    scanf("%s",data.department);

    printf("\n");

    printf("Enter the Topic of course : ");
    scanf("%s",data.topic);

    printf("\n");



    printf("Thx For Enter The Course Information\n");

    N node = newNode(data);

    addCourse(node);


}


void searchAboutCourse()   //function to search about Course
{


    printf("\nWrite The Name Of The Course : ");


    char courseName[30];
    gets(deleteLine);
    gets(courseName);



    int function = hash(courseName, CourseSize);
    int i =0;

    int index = (function + (i*i)) % CourseSize;

    while (true)
    {
        if(i > CourseSize)//WHEN WE CHECKED ALL POSSIBILITIES
        {
            printf("\nThere Isn't Course With This Name 1111111 \n");
            break;
        }
        else if (Courses[index] == NULL)//WHEN WE FIND EMPTY AREA WHERE THIS NAME SHOULD BE THERE
        {
            printf("\nThere Isn't Course With This Name \n");
            break;
        }
        else if (strcmp(courseName, Courses[index]->data.courseName) == 0)//IF WE REACH THE RIGHT POSITION THEN WE SHOULD CHECK IF THE NAME SAME AT THE TABLE
        {

            printf("\nCorseName: %s\nCriditHours: %d\nCodeCode: %s\n:Department %s\nTopic:%s\n"
                   , Courses[index]->data.courseName, Courses[index]->data.CrediHours, Courses[index]->data.CourseCode, Courses[index]->data.department, Courses[index]->data.topic);
            break;

        }


        i++;
        index = (function + (i*i)) % CourseSize;
    }




}


void deleteCourse()  //function to delete course from hash table
{


    printf("\nWrite The Name Of The Course : ");
    char courseName [30];
    gets(deleteLine);
    gets(courseName);




    int function = hash(courseName, CourseSize);
    int i =0;

    int index = (function + (i*i)) % CourseSize;

    while (true)
    {
        if(i > CourseSize)//WHEN WE CHECKED ALL POSSIBILITIES
        {
            printf("\nThere Isn't Course With This Name \n");
            break;
        }
        else if (Courses[index] == NULL)//WHEN WE FIND EMPTY AREA WHERE THIS NAME SHOULD BE THERE
        {
            printf("\nThere Isn't Course With This Name \n");
            break;
        }
        else if (strcmp(courseName, Courses[index]->data.courseName) == 0)//IF WE REACH THE RIGHT POSITION THEN WE SHOULD CHECK IF THE NAME SAME AT THE TABLE
        {

            free(Courses[index]);//FOR DELETE THE RECORD
            Courses[index] = NULL;
            elementsSize--;
            printf("THE DELETE OPERATION FOR %s DONE\n", courseName);



            if ( (int) (0.75 * CoursesOldSize) > elementsSize)//WHEN THE TABLE HAS MANY EMPTY PLACES
                updateHashTable(2);

            break;

        }


        i++;
        index = (function + (i*i)) % CourseSize;
    }



}

void saveHashTable()
{

    FILE *f = fopen("saved_courses.txt", "w");//FOR OPEN THE OUTPUT FILE

    for (int i = 0; i < CourseSize; ++i)
        fprintf(f, "Index : %d\t Name: %s\n", i, Courses[i]->data.courseName);

}

//----------------------------------------------------------------------------------------------------------------------//

void addCourse1(AVL root)
{


    if (root != NULL)
    {


        addCourse1(root->left);//ADD THE PATIENTS WHICH EXIST AT LEFT SUBTREE
        addCourse1(root->right);//ADD THE PATIENTS WHICH EXIST AT RIGHT SUBTREE


        if ( (int) (0.75 * CourseSize) <= elementsSize)//WHEN THE TABLE 75% FULL THEN UPDATE IT
            updateHashTable1(1);

        info save = root->data;
        N node = newNode(save);
        free(root);


        int i = 0;
        int index = hash1(node->data.courseName, CourseSize);//RETURN THE INDEX OF THE PATIENT NAME
        bool update = false;//FOR CHECK IF THE HASH TABLE IS FULL OR NOT

        //FOR SEARCH ABOUT THE EMPTY POSITION AT HASH TABLE
        while (hashCheck(index, i, CourseSize, Courses))
        {

            if (i > CourseSize)
            {
                update = true;//WHEN THE VALUE CAN'T FIND ANY PLACE FOR IT IN THE ARRAY
                break;
            }

            i++;
        }


        if (update)
        {
            updateHashTable1(1);//FOR UPDATE THE HASH TABLE
            addCourse1(node);
        }
        else
        {
            index = (index + (i*i)) % CourseSize;//FOR RETURN THE CORRECT POSITION AT HASH TABLE FOR INSERT THE PATIENT
            Courses[index] = node;
            elementsSize++;
        }

    }

}

void updateHashTable1(int flag)
{


    int oldSize = CourseSize;//SAVE THE OLD HASH TABLE SIZE

    if (flag == 1)
        CourseSize = reHash(CourseSize);//UPDATE THE HASH TABLE SIZE (increase)
    else if (flag == 2)
        CourseSize = deHash(CourseSize);//UPDATE THE HASH TABLE SIZE (decrease)

    struct Node** newHashTable = (struct Node**) malloc((sizeof (struct Node*)) * CourseSize);//CREATE NEW PATIENTS HASH TABLE
    for (int i = 0; i < CourseSize; ++i)
        newHashTable[i] = NULL;


    //RE-INSERT THE PATIENTS FROM OLD HASH TABLE TO THE NEW HASH TABLE
    for (int i = 0; i < oldSize; ++i)
    {

        if(Courses[i] != NULL)
        {

            int index = hash1(Courses[i]->data.courseName, CourseSize);
            int j = 0;

            while (hashCheck(index, j, CourseSize, newHashTable))
                j++;




            index = (index + (j*j)) % CourseSize;
            newHashTable[index] = Courses[i];



        }

    }

    free(Courses);//DELETE THE OLD HASH TABLE : this don't delete the nodes in the old table
    Courses = newHashTable;




    //FOR UPDATE THE SIZE OF THE patientsOldSize
    if(flag == 1)
        CoursesOldSize = oldSize;
    if(flag == 2)
    {

        if (CourseSize != 2)
            CoursesOldSize = deHash(CourseSize);
        else
            CoursesOldSize = 0;//INITIAL STATE

    }


}

void searchAboutCourse1()
{


    printf("\nWrite The Name Of The Course : ");


    char courseName[30];
    gets(deleteLine);
    gets(courseName);



    int function = hash1(courseName, CourseSize);
    int i =0;

    int index = (function + (i*i)) % CourseSize;//FOR RETURN THE FIRST POSITION AT HASH TABLE FOR THE REQUIRED NAME

    while (true)
    {
        if(i > CourseSize)//WHEN WE CHECKED ALL POSSIBILITIES
        {
            printf("\nThere Isn't Course With This Name 1111111 \n");
            break;
        }
        else if (Courses[index] == NULL)//WHEN WE FIND EMPTY AREA WHERE THIS NAME SHOULD BE THERE
        {
            printf("\nThere Isn't Course With This Name \n");
            break;
        }
        else if (strcmp(courseName, Courses[index]->data.courseName) == 0)//IF WE REACH THE RIGHT POSITION THEN WE SHOULD CHECK IF THE NAME SAME AT THE TABLE
        {

            printf("\nCorseName: %s\nCriditHours: %d\nCodeCode: %s\n:Department %s\nTopic:%s\n"
                   , Courses[index]->data.courseName, Courses[index]->data.CrediHours, Courses[index]->data.CourseCode, Courses[index]->data.department, Courses[index]->data.topic);
            break;

        }


        i++;
        index = (function + (i*i)) % CourseSize;
    }




}



