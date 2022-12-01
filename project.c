#include <stdio.h>

void retrieveData(int data[], int size, FILE *pF);
void getRange(int list[], int size, int range[2]);
int checkRange(int data[], int size);
int checkStartStopChar(int data[]);
void decodeChar(int data[], int decoding[]);
int checkCK(int decoding[]);

void printArr (int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", i, arr[i]);
    }
    printf("\n");
}

int main () {
    FILE *pF = fopen("input.txt", "r");
    int size, cases, i;

    if (pF == NULL) {
        printf("File cannot be opened.\n");
    } else {
        fscanf(pF, "%d", &size);
        for (cases = 0; size != 0; cases++) {
            int data[size];
            int decodingLen = (size - 11) / 6;
            int decoding[decodingLen];
            // int range[2][2];

            retrieveData(data, size, pF);
            // printArr(data, size);
            // printf("\n");

            if (!checkRange(data, size)) {
                printf("Case %d: bad code\n", cases + 1);
            } 
            
            // checkStartStopChar(data);
            // decodeChar(data, decoding);
            // checkCK(decoding);

            fscanf(pF, "%d", &size);
        }
    }

    fclose(pF);

    return 0;
}


void retrieveData(int data[], int size, FILE *pF) {
    int i;

    for (i = 0; i < size; i++) {
        fscanf(pF, "%d", &data[i]);
    }
}


void getRange(int list[], int size, int range[2]) {
    // * GET THE MODE FROM NARROW AND WIDE LIST
     int mode = 0, maxCount = 0, count, i, j;

    for (i = 0; i < size; ++i) {
        count = 0;
        
        for (j = 0; j < size; ++j) {
            if (list[j] == list[i]) {
                ++count;
            }
        }
        
        if (count > maxCount) {
            maxCount = count;
            mode = list[i];
        }
    }

    // * FIND ERROR RANGE BASED ON THE MODE
    range[0] = mode - (mode * 5/100);
    range[1] = mode + (mode * 5/100);
}

int checkRange(int data[], int size) {
    int i, j, min = 200, max = 0, avg = 0, flag = 1;
    int wideRange[2], narrowRange[2];
    int wideIndex = 0, narrowIndex = 0;
    int wideList[size];
    int narrowList[size];


    // * FIND MIN AND MAX TO GET THE AVERAGE

    for (i = 0; i < size; i++) {
        if (data[i] < min) {
            min = data[i];
        }

        if (data[i] > max) {
            max = data[i];
        }
    }

    avg = (min + max) / 2;

    // printf("min: %d | max: %d | avg: %d\n", min, max, avg);


    // * CALL GETRANGE() FUNCTION

    for (i = 0; i < size; i++) {
        wideList[i] = 0;
        narrowList[i] = 0;
    }

    for (i = 0; i < size; i++) {
        if (data[i] > avg) {
            wideList[wideIndex] = data[i];
            // printf("Inputed: %d\n", wideList[wideIndex]);
            wideIndex++;
        } else {
            narrowList[narrowIndex] = data[i];
            // printf("Inputed: %d\n", narrowList[narrowIndex]);
            narrowIndex++;
        }
    }

    // printf("%d %d\n", wideList[0], narrowList[0]);
    // for (i = 0; i < wideIndex; i++) {
    //     printf("%d ", wideList[i]);
    // }
    // printf("\n");

    getRange(wideList, wideIndex, wideRange);
    getRange(narrowList, narrowIndex, narrowRange);

    // printf("%d - %d\n", wideRange[0], wideRange[1]);
    // printf("%d - %d\n", narrowRange[0], narrowRange[1]);

    // * CHECK WHETHER ALL OF THE ELEMENTS IS ON RANGE
    for (i = 0; i < size; i++) {
        if (data[i] > avg) {
            if (data[i] < wideRange[0] || data[i] > wideRange[1]) {
                flag = 0;
                break;
            }
        } else {
            if (data[i] < narrowRange[0] || data[i] > narrowRange[1]) {
                flag = 0;
                break;
            }
        }
    }

    return flag;
}

int checkStartStopChar(int data[]) {
    // * TAKE THE FIRST AND LAST 5 ELEMENTS AND TURN THEM FROM INT TO STRING, TO CHECK SS CHAR
    // * IF SS IS DETECTED BACKWARDS, REVERSE THE DATA

}

void decodeChar(int data[], int decoding[]) {
    // * TAKE FIVE ELEMENTS AND CONVERT THEM TO ENCODING STRING, GET RESULT BASED ON THE ENCODING
    // * STORES EACH ENCODING RESULT IN THE DECODING ARRAY

}

int checkCK(int decoding[]) {
    // * SET UP C AND K VARIABLE, BUILD THE C AND K CHECKER FUNCTION
    // * RETURNS 1 IF C AND K CORRECT, RETURNS 0 IF C IS INCORRECT, RETURNS -1 IF K IS INCORRECT

}