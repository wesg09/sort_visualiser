#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<GL\glut.h>
#define SORT_NO 3	
#define MAX 70		
int a[MAX];
int swapflag = 0;
int delay = 10;
int flag = 0;
int dirflag = 0;
int count = 1;
int k = 0;
int sorting = 0;
char* sort_string[] = { (char*)"Bubble Sort",(char*)"Selection Sort",(char*)"Insertion Sort" };
int sort_count = 0;

// Function to display text on screen char by char
int i = 0, j = 0;
void bitmap_output(int x, int y, char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(font, string[i]);
    }
}

// Function to convert integer to string
void int_str(int rad, char r[])
{
    itoa(rad, r, 10);
}

void display_text()
{
    glColor3f(1, 1, 1);
    bitmap_output(220, 665, (char*)"SORTING ALGORITHM VISUALIZER", GLUT_BITMAP_TIMES_ROMAN_24);
    glEnd();
    if (sorting == 0)	// if not sorting display menu
    {
        bitmap_output(10, 575, (char*)"Selected sort: ", GLUT_BITMAP_9_BY_15);
        bitmap_output(150, 575, *(sort_string + sort_count), GLUT_BITMAP_9_BY_15);
    }
    else if (sorting == 1)	// while sorting
    {
        glColor3f(0, 1, 0);
        bitmap_output(10, 555, (char*)"Sorting in progress...", GLUT_BITMAP_9_BY_15);
        bitmap_output(10, 535, (char*)"Press p to PAUSE", GLUT_BITMAP_9_BY_15);
        bitmap_output(10, 575, (char*)"Selected sort: ", GLUT_BITMAP_9_BY_15);
        bitmap_output(150, 575, *(sort_string + sort_count), GLUT_BITMAP_9_BY_15);
        glColor3f(0.0, 0.0, 0.0);
    }
}

void front()
{
    glColor3f(.0, 1.0, 1.0);
    bitmap_output(300, 565 - 30, (char*)"WELCOME!", GLUT_BITMAP_TIMES_ROMAN_24);
    bitmap_output(330, 525 - 30, (char*)"TO", GLUT_BITMAP_TIMES_ROMAN_24);
    bitmap_output(200, 475 - 30, (char*)"SORTING ALGORITHM VISUALIZER", GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.0, 1.0, 0.0);
    bitmap_output(530, 125, (char*)"Press Enter to continue", GLUT_BITMAP_HELVETICA_18);
}

void Initialize() {
    int temp1;

    // Reset the array
    for (temp1 = 0;temp1 < MAX;temp1++) {
        a[temp1] = rand() % 100 + 1;
        printf("%d ", a[temp1]);
    }

    // Reset all values
    i = j = 0;
    dirflag = 0;
    count = 1;
    flag = 0;

    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 699, 0, 799);
}

// Return 1 if not sorted
int notsorted() {
    int q;
    for (q = 0;q < MAX - 1;q++)
    {
        if (a[q] > a[q + 1])
            return 1;
    }
    return 0;
}

// Main function for display
void display()
{
    int ix, temp;
    glClearColor(0.1, 0.1, 0.1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    if (k == 0)
        front();
    else {
        display_text();
        char text[10];

        for (ix = 0;ix < MAX;ix++)
        {
            glColor3f(1, 0, 0);
            glBegin(GL_POLYGON);
            glVertex2f(30 + (700 / (MAX + 1)) * ix, 50);
            glVertex2f(30 + (700 / (MAX + 1)) * (ix + 1), 50);
            glVertex2f(30 + (700 / (MAX + 1)) * (ix + 1), 50 + a[ix] * 4);
            glVertex2f(30 + (700 / (MAX + 1)) * ix, 50 + a[ix] * 4);
            glEnd();

            glColor3f(1, 1, 1); // Black

            // Drawing polygon border
            glBegin(GL_LINE_LOOP);
            glVertex2f(30 + (700 / (MAX + 1)) * ix, 50);
            glVertex2f(30 + (700 / (MAX + 1)) * (ix + 1), 50);
            glVertex2f(30 + (700 / (MAX + 1)) * (ix + 1), 50 + a[ix] * 4);
            glVertex2f(30 + (700 / (MAX + 1)) * ix, 50 + a[ix] * 4);
            glEnd();

            int_str(a[ix], text);
            glColor3f(0, 1, 0);
            bitmap_output(32 + (700 / (MAX + 1)) * ix, 35, text, GLUT_BITMAP_TIMES_ROMAN_10);
        }
    }
    glFlush();
}

// Insertion Sort
void insertionsort()
{
    int temp;

    while (i < MAX)
    {
        if (flag == 0) { j = i; flag = 1; }
        while (j < MAX - 1)
        {
            if (a[j] > a[j + 1])
            {
                swapflag = 1;
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;

                goto A;
            }
            j++;
            if (j == MAX - 1) { flag = 0; }
        }
        i++;
    }
    sorting = 0;
A:
    i = j = 0;
}

// Selection Sort
void selectionsort()
{
    int temp, j, min, pos;

    while (notsorted())
    {

        while (i < MAX - 1)
        {
            min = a[i + 1];
            pos = i + 1;
            if (i != MAX - 1)
            {
                for (j = i + 2;j < MAX;j++)
                {
                    if (min > a[j])
                    {
                        min = a[j];
                        pos = j;
                    }
                }
            }
            if (min < a[i])
            {
                temp = a[pos];
                a[pos] = a[i];
                a[i] = temp;
                goto A;
            }
            i++;
        }
    }
    sorting = 0;
    i = j = 0;
A:  printf("");
}

//Bubble Sort
void bubblesort()
{
    int temp;
    while (notsorted())
    {
        while (j < MAX - 1)
        {
            if (a[j] > a[j + 1])
            {
                swapflag = 1;
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;

                goto A;
            }
            j++;
            if (j == MAX - 1) j = 0;
        }
    }
    sorting = 0;
A: printf("");
}
void makedelay(int)
{
    if (sorting)
    {
        switch (sort_count)
        {
        case 0:
            bubblesort();
            break;
        case 1:
            selectionsort();
            break;
        case 2:
            insertionsort();
            break;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(delay, makedelay, 1);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 13) // enter key
        k = 1;
    if (k == 1 && sorting == 1)
        if (key == 'p')	sorting = 0;
}

void menuSelection(int option)
{
    switch (option)
    {
    case 1:
        sorting = 1;
        break;
    case 2:
        Initialize();
        break;
    case 3:
        sort_count = (sort_count + 1) % SORT_NO;
        break;
    case 4:
        exit(0);
    case 5:
        sorting = 0;
    }
}

void submenucallback(int op)
{
    switch (op)
    {
    case 1:
        /* code */
        delay = 100;
        break;
    case 2:
        delay = 50;
        break;
    case 3:
        delay = 10;
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("Sorting Visualizer");
    Initialize();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    int submenu = glutCreateMenu(submenucallback);
    glutAddMenuEntry("level 1", 1);
    glutAddMenuEntry("level 2", 2);
    glutAddMenuEntry("level 3", 3);

    int menu = glutCreateMenu(menuSelection);
    glutAddMenuEntry("Sort", 1);
    glutAddMenuEntry("Randomize", 2);
    glutAddMenuEntry("Change Sorting Algorithm", 3);
    glutAddSubMenu("speed level", submenu);
    glutAddMenuEntry("Exit", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutTimerFunc(1000, makedelay, 1);
    glutMainLoop();
    return 0;
}