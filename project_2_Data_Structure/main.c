#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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


FILE* TREE_OUT_FILE = NULL;//OUTPUT TREE FILE NAME
char outputTreePath[200] = "offered_courses.txt";
AVL tree = NULL;//CREATE EMPTY AVL TREE WITH LABEL "tree"
char deleteLine[500];//FOR DELETE LINE WHEN READ FROM CONSOLE
AVL insert(AVL root, info data);//FOR ADD NEW NODE ON TREE


int main()
{


    int flag = 0;


    while (true)
    {

        PrintMenue();
        scanf("%d", &flag);

        if (flag == 10)
            break;

        switch (flag)
        {

        case 1:
            read(); //call function to read file
            break;

        case 2:
            insertNodeByUser(); //call function to insert new node by user
            break;


        case 3:
            updateNode(); //call function to update information of course
            break;

        case 4:
            inLexicographicOrder(); //call function to print information
            break;
        case 5:
            displyTopic(); //call function to print topic
            break;
        case 6:
            printSameDepartment(); //call function to print Same Department
            break;
        case 7:
            deleteNode(); //function to delete node by given course code
            break;
        case 8:
            DeleteCourseByGivenDepartment(); //function to delete node by given department

            break;
        case 9:
            deleteStart();
            break;
        case 10:

            saveTree(outputTreePath); //call function to save tree
            return 0;
            break;

        }

    }
}
void PrintMenue() // only print menue
{

    printf("1. Read the file courses.txt file and create the tree\n");
    printf("2. Insert a new course from the user with all its associated data\n");
    printf("3. Find a course and support updating of its information\n");
    printf("4. List courses in lexicographic order with their associated information (credit hours, IDs, and topics)\n");
    printf("5. List all topics associated with a given course\n");
    printf("6. List all courses in lexicographic order that belong to the same department\n");
    printf("7. Delete a course\n");
    printf("8. Delete all courses that start with a specific letter\n");
    printf("9. Delete all courses belong to a given department\n");
    printf("10. Save all words in file offered_courses.txt\n");


}

int max(int x1, int x2)   //function to return max
{
    return (x1>x2) ? x1 : x2;
}

int getHeight(N node)   //function to return height of tree
{
    if(node == NULL)
        return -1;    //if there is no node we return value -1
    return node->height;
}
int getBalanced(N node)  //function to return the balance of tree
{

    if(node == NULL)
        return 0;

    return getHeight(node->left) - getHeight(node->right); //balance =height of left - height of right

}
bool isEmpty(AVL root)   //function to check if the tree is empty
{
    return root == NULL;
}

N newNode(info data)   //function to create node of information
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




void read()   //function to read information in file
{

    FILE *fp = fopen("courses.txt", "r"); // for open the file

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


N leftRotate(N node)   //function to work leftRotate
{

    N mid = node->right;//mid = 20
    N leftOfMid = mid->left;//leftOfMid = ?

    //Perform rotation
    mid->left = node;//let 10 left of 20
    node->right = leftOfMid;//left of mid  ? will be right of 10

    //Update heights

    node->height = max(getHeight(node->left), getHeight(node->right)) +1 ;//firstly we should get height of the left sub tree (10)
    mid->height =  max(getHeight(mid->left), getHeight(mid->right)) +1;//secondly the we can get the correct height of the new root (20)

    return mid;
}

N rightRotate(N node)    //function to work rightRotate
{

    N mid = node->left;//mid = 20
    N rightOfMid = mid->right;//rightOfMid = ?

    // Perform rotation
    mid->right = node;//let 30 left of 20
    node->left = rightOfMid;//right of mid  ? will be left of 30

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
    else if (strcmp(data.CourseCode, root->data.CourseCode) < 0)
        root->left = insert(root->left, data);
    //if the new node is more than the parent
    else if (strcmp(data.CourseCode, root->data.CourseCode) > 0)
        root->right = insert(root->right, data);



    //update the height of the  nodes
    root->height = max(getHeight(root->right), getHeight(root->left)) + 1 ;
    int balanced = getBalanced(root);


    // LEFT LEFT Case : RIGHT ROTATION
    if(balanced > 1 && (strcmp(data.CourseCode, root->left->data.CourseCode) < 0))
        root = rightRotate(root);

    // RIGHT RIGHT Case : LEFT ROTATION
    if(balanced < -1 && (strcmp(data.CourseCode, root->right->data.CourseCode) > 0))
        root = leftRotate(root);




    // RIGHT LEFT Case : RIGHT ROTATION THEN LEFT ROTATION
    if(balanced < -1 && (strcmp(data.CourseCode, root->right->data.CourseCode) < 0))
    {
        root->right = rightRotate(root->right); // this for make it like RIGHT RIGHT FORM
        root = leftRotate(root);
    }



    // LEFT RIGHT Case : LEFT ROTATION THEN RIGHT ROTATION
    if(balanced > 1 && (strcmp(data.CourseCode, root->left->data.CourseCode) > 0))
    {
        root->left = leftRotate(root->left);// this for make it like LEFT LEFT FORM
        root = rightRotate(root);
    }



    return  root;
}
void insertNodeByUser()  //function to insert new node from user
{

    printf("Insert The course information\n");
    info data;
    printf("\n");


    printf("Enter the Name of course : ");
    scanf("%s",data.courseName);
    printf("\n");

    printf("Enter the criditHours : ");
    scanf("%d", &data.CrediHours);
    printf("\n");

    printf("Enter the courseCode : ");
    scanf("%s",data.CourseCode);
    printf("\n");

    printf("Enter the department of course : ");
    scanf("%s",data.department);
    printf("\n");


    printf("Enter the Topic of course : ");

    scanf("%s",data.topic);
    printf("\n");


    printf("Thanks For Enter The course Information\n");
    tree = insert(tree, data);

}

void inOrderDisplay (AVL root) //to print the information of course in order
{

    if (root != NULL)
    {

        inOrderDisplay(root->left);//FOR PRINT THE NODES INFORMATION AT LEFT SUB TREE

        printf("____________________________________________________________________________________________________\n");
        printf("\nCoursName: %s\nCreditHours: %d\nCourseCode: %s\nDepartment: %s\nTopic:%s\n"
               , root->data.courseName, root->data.CrediHours, root->data.CourseCode,root->data.department, root->data.topic);
        printf("____________________________________________________________________________________________________\n");

        inOrderDisplay(root->right);//FOR PRINT THE NODES INFORMATION AT RIGHT SUB TREE


    }

}


void saveTree(char path[500])
{



    TREE_OUT_FILE = fopen(path, "w");//FOR OPEN THE OUTPUT FILE

    if(isEmpty(tree))
        fprintf(TREE_OUT_FILE, "\nTHE TREE IS EMPTY\n");
    else
        inOrderDisplayOnFile(tree);

    // fclose(TREE_OUT_FILE );//FOR CLOSE THE OUTPUT FILE

}

void inLexicographicOrder ()  //to print information inLexicographicOrder
{

    if(isEmpty(tree)) //if tree is null
        printf("\nTHE TREE IS EMPTY\n");
    else
        inOrderDisplay(tree);

}
N delete(AVL root, char CourseCode[30])  //function to delete the node from tree Based on course code
{



    if(root == NULL)
    {
        printf("THE NODE NOT FOUNDED\n");
        return root;
    }

    else if (strcmp(CourseCode, root->data.CourseCode) > 0)
        root->right = delete(root->right, CourseCode);//if the  node is more than the parent
    else if (strcmp(CourseCode, root->data.CourseCode) < 0)
        root->left = delete(root->left, CourseCode);//if the  node is less than the parent
    else //when found the node
    {


        if (root->right != NULL && root->left != NULL) //WHEN THE NODE HAVE 2 CHILDREN
        {

            N minRight = findMin(root->right);
            N temp = minRight;

            //replace the deleted node with the Successor  node
            root->data = minRight->data;

            //free the Successor node
            root->right = delete(root->right, minRight->data.CourseCode);

        }
        else if (root->right == NULL && root->left != NULL)   //WHEN THE NODE HAVE LEFT CHILDREN
        {

            N temp = root;
            root = root->left;
            free(temp);

        }
        else if (root->right != NULL && root->left == NULL)   //WHEN THE NODE HAVE RIGHT CHILDREN
        {

            N temp = root;
            root = root->right;
            free(temp);

        }
        else   //WHEN THE NODE DON'T HAVE CHILDRENS
        {

            N temp = root;
            root = NULL;
            free(temp);
            return root;//FOR DON'T CHECK THE BALANCED CUZ IT'S LEAF NODE

        }


        //update the height of the  node after delete it
        root->height = max(getHeight(root->right), getHeight(root->left)) + 1 ;
        int balanced = getBalanced(root);


        // LEFT LEFT Case : RIGHT ROTATION
        if(balanced > 1 && (strcmp(CourseCode, root->left->data.CourseCode) < 0))
            root = rightRotate(root);

        // RIGHT RIGHT Case : LEFT ROTATION
        if(balanced < -1 && (strcmp(CourseCode, root->right->data.CourseCode) > 0))
            root = leftRotate(root);

        // RIGHT LEFT Case : RIGHT ROTATION THEN LEFT ROTATION
        if(balanced < -1 && (strcmp(CourseCode, root->right->data.CourseCode) < 0))
        {
            root->right = rightRotate(root->right); // this for make it like RIGHT RIGHT FORM
            root = leftRotate(root);
        }

        // LEFT RIGHT Case : LEFT ROTATION THEN RIGHT ROTATION
        if(balanced > 1 && (strcmp(CourseCode, root->left->data.CourseCode) > 0))
        {
            root->left = leftRotate(root->left);// this for make it like LEFT LEFT FORM
            root = rightRotate(root);
        }


    }


    return root;
}
void inOrderDisplayOnFile (AVL root)  //to print information to file output
{


    if (root != NULL)
    {

        inOrderDisplayOnFile(root->left);//FOR PRINT THE NODES INFORMATION AT LEFT SUB TREE

        fprintf(TREE_OUT_FILE,"____________________________________________________________________________________________________\n");
        fprintf(TREE_OUT_FILE,"\nCourseName: %s\nCriditHoures: %d\nCourseCode: %s\nDepartment: %s\nTopic: %s\n"
                , root->data.courseName, root->data.CrediHours, root->data.CourseCode, root->data.department, root->data.topic);
        fprintf(TREE_OUT_FILE,"____________________________________________________________________________________________________\n");

        inOrderDisplayOnFile(root->right);//FOR PRINT THE NODES INFORMATION AT RIGHT SUB TREE

    }



}

N find(AVL root, char CourseCode[30])  //function to find course based on courseCode
{

    if(root == NULL)
        printf("THE VALUE NOT EXIST\n");
    else if (strcmp(CourseCode, root->data.CourseCode) == 0)
        return root;//WHEN FOUND THE NEEDED NODE
    else if(strcmp(CourseCode, root->data.CourseCode) > 0)
        return find(root->right, CourseCode);//if the  node is more than the parent
    else if(strcmp(CourseCode, root->data.CourseCode) < 0)
        return find(root->left, CourseCode);//if the  node is less than the parent


    return NULL;//WHEN THE NODE NOT EXIST IN THE TREE
}
void deleteNode()
{


    printf("\nWrite The code Of The Course : ");
    char courseCode[30];
    scanf("%s",courseCode);

    N Course = find(tree, courseCode);

    if(Course == NULL)
        printf("\nThere Isn't Course With This Name \n");
    else
    {
        delete(tree, courseCode);
        printf("THE DELETE OPERATION DONE\n");
    }


}
void updateNode()  //function to update information of course
{

    printf("\nWrite The CourseCode : ");
    char CourseCode[30];
    scanf("%s",CourseCode);

    N Course = find(tree, CourseCode);
    info data = Course->data;

    if(Course == NULL)
        printf("\nThere Isn't Course With This CourseCode \n");
    else
    {

        int flag = 0;
        while (true)
        {

            printf("1 : For Update the Name of Course \n"
                   "2 : For Update the criditHoures of Course \n"
                   "3 : Update the CourseCode Date of Course \n"
                   "4 : Update the Department of Course \n"
                   "5 : Update the Topic of Course \n"
                  );
            printf("\nWrtie '0' For Finish The Update Date Of The Course\n");
            scanf("%d", &flag);

            if(flag == 0)
                break;
            else if(flag == 1)//WHEN UPDATE THE NAME THEN WE SHOULD INSERT THE NODE AGAIN ON TREE AFTER DELETE THE OLD ONE
            {
                char courseName[30];
                printf("Enter The New CourseName : ");
                scanf("%s",courseName);
                strcpy(Course->data.courseName, courseName);
            }
            else if(flag == 2)
            {
                int CriditHours;
                printf("Enter The New CriditHours : ");
                scanf("%d",&CriditHours);
                Course->data.CrediHours = CriditHours;

            }
            else if(flag == 3)
            {
                char CourseCode[30];
                printf("Enter The New CourseCode : ");
                scanf("%s",CourseCode);
                strcpy(Course->data.CourseCode, CourseCode);

            }
            else if(flag == 4)
            {
                char Department[30];
                printf("Enter The New Department : ");
                scanf("%s",Department);
                strcpy(Course->data.department, Department);

            }
            else if(flag == 5)
            {
                char Topic[500];
                printf("Enter The New Topic : ");
                scanf("%s",Topic);
                strcpy(Course->data.topic, Topic);

            }

            else
                printf("\nYou Should Enter Number Between 1-5\n");

            printf("\n");

        }
        printf("\n");

    }


}

void displyTopic() //function to displyTopic
{

    char CourseCode[30];
    printf("Enter the course code");
    scanf("%s",CourseCode);
    N Course = find(tree, CourseCode);
    info data = Course->data;

    if(Course == NULL)
        printf("\nThere Isn't Course With This CourseCode \n");
    else
    {

        printf("\nTopic :%s\n",Course->data.topic);
    }
}

N delete1(AVL root, char department[30])  //function to delete course based on department
{



    if(root == NULL)
    {
        printf("THE NODE NOT FOUNDED\n");
        return root;
    }

    else if (strcmp(department, root->data.department) > 0)
        root->right = delete1(root->right, department);//if the  node is more than the parent
    else if (strcmp(department, root->data.department) < 0)
        root->left = delete1(root->left, department);//if the  node is less than the parent
    else //when found the node
    {


        if (root->right != NULL && root->left != NULL) //WHEN THE NODE HAVE 2 CHILDREN
        {

            N minRight = findMin(root->right);
            N temp = minRight;

            //replace the deleted node with the Successor  node
            root->data = minRight->data;

            //free the Successor node
            root->right = delete1(root->right, minRight->data.department);

        }
        else if (root->right == NULL && root->left != NULL)   //WHEN THE NODE HAVE LEFT CHILDREN
        {

            N temp = root;
            root = root->left;
            free(temp);

        }
        else if (root->right != NULL && root->left == NULL)   //WHEN THE NODE HAVE RIGHT CHILDREN
        {

            N temp = root;
            root = root->right;
            free(temp);

        }
        else   //WHEN THE NODE DON'T HAVE CHILDRENS
        {

            N temp = root;
            root = NULL;
            free(temp);
            return root;//FOR DON'T CHECK THE BALANCED CUZ IT'S LEAF NODE

        }


        //update the height of the  node after delete it
        root->height = max(getHeight(root->right), getHeight(root->left)) + 1 ;
        int balanced = getBalanced(root);


        // LEFT LEFT Case : RIGHT ROTATION
        if(balanced > 1 && (strcmp(department, root->left->data.department) < 0))
            root = rightRotate(root);

        // RIGHT RIGHT Case : LEFT ROTATION
        if(balanced < -1 && (strcmp(department, root->right->data.department) > 0))
            root = leftRotate(root);

        // RIGHT LEFT Case : RIGHT ROTATION THEN LEFT ROTATION
        if(balanced < -1 && (strcmp(department, root->right->data.department) < 0))
        {
            root->right = rightRotate(root->right); // this for make it like RIGHT RIGHT FORM
            root = leftRotate(root);
        }

        // LEFT RIGHT Case : LEFT ROTATION THEN RIGHT ROTATION
        if(balanced > 1 && (strcmp(department, root->left->data.department) > 0))
        {
            root->left = leftRotate(root->left);// this for make it like LEFT LEFT FORM
            root = rightRotate(root);
        }


    }


    return root;
}

N find1(AVL root, char department[30]) //function to find course based on department
{

    if(root == NULL)
        printf("THE VALUE NOT EXIST\n");
    else if (strcmp(department, root->data.department) == 0)
        return root;//WHEN FOUND THE NEEDED NODE
    else if(strcmp(department, root->data.department) > 0)
        return find1(root->right, department);//if the  node is more than the parent
    else if(strcmp(department, root->data.department) < 0)
        return find1(root->left, department);//if the  node is less than the parent


    return NULL;//WHEN THE NODE NOT EXIST IN THE TREE
}
void DeleteCourseByGivenDepartment()  //function to delete node based on given department
{

    char department[30];
    printf("Enter the Department of course");
    gets(deleteLine);
    gets(department);

    N Course = find1(tree, department);

    if(Course == NULL)
        printf("\nThere Isn't Course With This Department \n");
    else
    {
        delete1(tree, department);
        printf("THE DELETE OPERATION DONE\n");
    }

}


bool checksamedepartment(AVL root, char department[30], bool save)  //to check if same department
{

    if (root != NULL)
    {



        if(strcmp(department, root->data.department) == 0)
        {
            printf("____________________________________________________________________________________________________\n");
            printf("\nCourseName: %s\nCriditHoures: %d\nCourseCode: %s\nDepartment: %s\nTopic: %s\n"
                   , root->data.courseName, root->data.CrediHours, root->data.CourseCode, root->data.department, root->data.topic);
            printf("____________________________________________________________________________________________________\n");

            save = false;
        }



        if(checksamedepartment(root->left, department, save) == false)
            save = false;
        if(checksamedepartment(root->right, department, save) == false)
            save = false;


    }

    if (save == false)
        return false;

    return true;

}
void printSameDepartment()  //function to print the course whith same department
{

    char department[100];
    printf("\nEnter the department : ");
    gets(deleteLine);
    gets(department);
    printf("\n");

    bool checkEmpty =  true; //to check if null
    checkEmpty = checksamedepartment(tree, department, checkEmpty);

    if(checkEmpty)
        printf("\nWe Don't have Course with %s department\n", department);

}
N find2(AVL root, char CourseCode[2]) //function to find course based on CourseCode
{


    if(root == NULL)
        printf("THE VALUE NOT EXIST\n");
    else if (strchr(CourseCode, root->data.CourseCode) == 0)
        return root;//WHEN FOUND THE NEEDED NODE
    else if(strchr(CourseCode, root->data.CourseCode) > 0)
        return find2(root->right, CourseCode);//if the  node is more than the parent
    else if(strchr(CourseCode, root->data.CourseCode) < 0)
        return find2(root->left, CourseCode);//if the  node is less than the parent


    return NULL;//WHEN THE NODE NOT EXIST IN THE TREE
}


N delete2(AVL root, char CourseCode[2])  //function to delete course based on CourseCode
{



    if(root == NULL)
    {
        printf("THE NODE NOT FOUNDED\n");
        return root;
    }

    else if (strchr(CourseCode, root->data.CourseCode) > 0)
        root->right = delete2(root->right, CourseCode);//if the  node is more than the parent
    else if (strchr(CourseCode, root->data.CourseCode) < 0)
        root->left = delete2(root->left, CourseCode);//if the  node is less than the parent
    else //when found the node
    {


        if (root->right != NULL && root->left != NULL) //WHEN THE NODE HAVE 2 CHILDREN
        {

            N minRight = findMin(root->right);
            N temp = minRight;

            //replace the deleted node with the Successor  node
            root->data = minRight->data;

            //free the Successor node
            root->right = delete2(root->right, minRight->data.CourseCode);

        }
        else if (root->right == NULL && root->left != NULL)   //WHEN THE NODE HAVE LEFT CHILDREN
        {

            N temp = root;
            root = root->left;
            free(temp);

        }
        else if (root->right != NULL && root->left == NULL)   //WHEN THE NODE HAVE RIGHT CHILDREN
        {

            N temp = root;
            root = root->right;
            free(temp);

        }
        else   //WHEN THE NODE DON'T HAVE CHILDRENS
        {

            N temp = root;
            root = NULL;
            free(temp);
            return root;//FOR DON'T CHECK THE BALANCED CUZ IT'S LEAF NODE

        }


        //update the height of the  node after delete it
        root->height = max(getHeight(root->right), getHeight(root->left)) + 1 ;
        int balanced = getBalanced(root);


        // LEFT LEFT Case : RIGHT ROTATION
        if(balanced > 1 && (strchr(CourseCode, root->left->data.CourseCode) < 0))
            root = rightRotate(root);

        // RIGHT RIGHT Case : LEFT ROTATION
        if(balanced < -1 && (strcmp(CourseCode, root->right->data.CourseCode) > 0))
            root = leftRotate(root);

        // RIGHT LEFT Case : RIGHT ROTATION THEN LEFT ROTATION
        if(balanced < -1 && (strcmp(CourseCode, root->right->data.CourseCode) < 0))
        {
            root->right = rightRotate(root->right); // this for make it like RIGHT RIGHT FORM
            root = leftRotate(root);
        }

        // LEFT RIGHT Case : LEFT ROTATION THEN RIGHT ROTATION
        if(balanced > 1 && (strcmp(CourseCode, root->left->data.CourseCode) > 0))
        {
            root->left = leftRotate(root->left);// this for make it like LEFT LEFT FORM
            root = rightRotate(root);
        }


    }


    return root;
}
void deleteStart()  //function to delete node based on given CourseCode
{

    char CourseCode[2];
    printf("Enter the CourseCode of course");
    scanf("%s",CourseCode);

    N Course = find2(tree, CourseCode);

    if(Course == NULL)
        printf("\nThere Isn't Course With This Department \n");
    else
    {
        delete2(tree, CourseCode);
        printf("THE DELETE OPERATION DONE\n");
    }

}



