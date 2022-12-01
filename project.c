#include <stdio.h>
#include <string.h>
#include <ctype.h>

void retrieveData(int data[], int size, FILE *pF);
void getRange(int list[], int size, int range[2]);
int checkRange(int data[], int size);
int checkStartStopChar(int data[], int size);
void decodeChar(int data[], int size, int decoding[]);
int checkCK(int decoding[], int length);

void printArr (int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
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
            int length = (size - 11) / 6;
            int decoding[length];
            int finalResult;

            retrieveData(data, size, pF);

            if (!checkRange(data, size)) {
                printf("Case %d: bad code\n", cases + 1);
                fscanf(pF, "%d", &size);
                continue;
            } 

            if (!checkStartStopChar(data, size)) {
                printf("Case %d: bad code\n", cases + 1);
                fscanf(pF, "%d", &size);
                continue;
            } 

            // printArr(data, size);
            decodeChar(data, size, decoding);

            // length = sizeof(decoding)/sizeof(decoding[0]);
            
            // printArr(decoding, sizeof(decoding)/sizeof(decoding[0]));
            finalResult = checkCK(decoding, length);
            // printf("result: %d\n", finalResult);

            if (finalResult > 0) {
                int index = 0, msgLen = length - 2;
                char msg[msgLen + 1];

                for (i = 0; i < msgLen; i++) {
                    if (decoding[i] == 10) {
                        // printf("spotted - at %d\n", i);
                        msg[i] = '-';
                        index += sprintf(&msg[index], "%c", '-');
                    } else {
                        msg[i] = decoding[i];
                        index += sprintf(&msg[index], "%d", decoding[i]); 
                    }
                }
                msg[msgLen] = '\0';

                printf("Case %d: %s\n", cases + 1, msg);
            } else {
                if (!finalResult) {
                    printf("Case %d: bad C\n", cases + 1);
                } else {
                    printf("Case %d: bad K\n", cases + 1);
                }
            }

            fscanf(pF, "%d", &size);
        }
    }

    fclose(pF);

    return 0;
}


void retrieveData(int data[], int size, FILE *pF) {
    for (int i = 0; i < size; i++) {
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


    // * CALL GETRANGE() FUNCTION
    for (i = 0; i < size; i++) {
        wideList[i] = 0;
        narrowList[i] = 0;
    }

    for (i = 0; i < size; i++) {
        if (data[i] > avg) {
            wideList[wideIndex] = data[i];
            wideIndex++;
        } else {
            narrowList[narrowIndex] = data[i];
            narrowIndex++;
        }
    }

    getRange(wideList, wideIndex, wideRange);
    getRange(narrowList, narrowIndex, narrowRange);


    // * CHECK WHETHER ALL OF THE ELEMENTS IS ON RANGE; IF YES, THEN TURN THE ELEMENTS INTO 1 AND 0
    for (i = 0; i < size; i++) {
        if (data[i] > avg) {
            if (data[i] < wideRange[0] || data[i] > wideRange[1]) {
                flag = 0;
                break;
            } else {
                data[i] = 1;
            }
        } else {
            if (data[i] < narrowRange[0] || data[i] > narrowRange[1]) {
                flag = 0;
                break;
            } else {
                data[i] = 0;
            }
        }
    }

    return flag;
}

int checkStartStopChar(int data[], int size) {
    int i, j, startIndex = 0, endIndex = 0, flag = 0;
    char start[6];
    char end[6];

    // * TAKE THE FIRST AND LAST 5 ELEMENTS AND TURN THEM FROM INT TO STRING, TO CHECK SS CHAR
    for (i = 0; i < 5; i++) {
        start[i] = data[i];
        startIndex += sprintf(&start[startIndex], "%d", data[i]);   

        end[i] = data[size - i - 1];
        endIndex += sprintf(&end[endIndex], "%d", data[i]);  
    }
    // printf("%s %s\n", start, end);

    // * IF SS IS DETECTED BACKWARDS, REVERSE THE DATA
    if (strcmp(start, "00110") == 0 && strcmp(end, "00110") == 0) {
        flag = 1;
    } else if (strcmp(start, "01100") == 0 && strcmp(end, "01100") == 0) {
        // reverse data
        for (i = 0; i < size / 2; i++){
            int temp = data[i];
            data[i] = data[size - i - 1];
            data[size - i - 1] = temp;
        }

        flag = 1;
    } 

    return flag;
}

void decodeChar(int data[], int size, int decoding[]) {
    int i, j, len = 0;
    char lists[11][6] = {"10001", "11000", "00101", "01001", "01100", "10010", "00011", "10100", "10000", "00001", "00100"};

    // * TAKE FIVE ELEMENTS AND CONVERT THEM TO ENCODING STRING, GET RESULT BASED ON THE ENCODING
    for (i = 6; i < size - 5; i+=6) {
        char encodingChar[6];
        int index = 0, result;
        
        for (j = 0; j < 5; j++) {
            encodingChar[j] = data[i + j];
            index += sprintf(&encodingChar[index], "%d", data[i + j]);   
            // printf("data[%d]: %d\n", i + j, data[i + j]);
        }
        encodingChar[5] = '\0';

        // printf("%s\n", encodingChar);
        
        // * STORES EACH ENCODING RESULT IN THE DECODING ARRAY
        for (j = 0; j < 11; j++) {
            if (strcmp(encodingChar, lists[j]) == 0) {
                decoding[len] = j;
                len++;
                break;
            }
        }
    }

    // printArr(decoding, len);

}

int checkCK(int decoding[], int length) {
    int i, j, n = length - 2;
    int charC = decoding[n];
    int charK = decoding[n + 1];
    int sumC = 0, sumK = 0;
    int flag = 1;

    // * SET UP C AND K VARIABLE, BUILD THE C AND K CHECKER FUNCTION
    for (i = 1; i <= n; i++) {
        sumC += ((n - i) % 10 + 1) * decoding[i - 1];
    }
    // printf("Current C : %d | Correct C : %d\n", charC, sumC % 11);
    
    // * RETURNS 1 IF C AND K CORRECT, RETURNS 0 IF C IS INCORRECT, RETURNS -1 IF K IS INCORRECT
    if (charC != sumC % 11) {
        // printf("Wrong C\n");
        flag = 0;
    } else {
        for (i = 1; i <= n + 1; i++) {
            sumK += ((n - i + 1) % 9 + 1) * decoding[i - 1];
        }
        // printf("Current K : %d | Correct K : %d\n", charK, sumK % 11);

        if (charK != sumK % 11) {
            // printf("Wrong K\n");
            flag = -1;
        }
    }

    return flag;
}