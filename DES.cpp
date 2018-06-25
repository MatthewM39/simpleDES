/*
Applied Cryptography Project 1 - DES
By Matthew McCrackin
*/

#include <iostream>
#include <cmath>
using namespace std;

int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17,  9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

int IPI[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41,  9, 49, 17, 57, 25
};

int Exp[48] = {
    32,  1,  2,  3,  4,  5,
     4,  5,  6,  7,  8,  9,
     8,  9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32,  1
};

int PC1[56] = {
    57, 49, 41, 33, 25, 17,  9,  1,
    58, 50, 42, 34, 26, 18, 10,  2,
    59, 51, 43, 35, 27, 19, 11,  3,
    60, 52, 44, 36, 63, 55, 47, 39,
    31, 23, 15,  7, 62, 54, 46, 38,
    30, 22, 14,  6, 61, 53, 45, 37,
    29, 21, 13,  5, 28, 20, 12,  4
};

int PC2[48] = {
    14, 17, 11, 24,  1,  5,  3, 28,
    15,  6, 21, 10, 23, 19, 12,  4,
    26,  8, 16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
};

int P[32] = {
    16,  7, 20, 21, 29, 12, 28, 17,
     1, 15, 23, 26,  5, 18, 31, 10,
     2,  8, 24, 14, 32, 27,  3,  9,
    19, 13, 30,  6, 22, 11,  4, 25
};

int S[8][64] = {
    {
        14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
        0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
        4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
        15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
        
    },
    {
        15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
        3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
        0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
        13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9
    },
    {
        10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
        13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
        13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
        1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
    },
    {
        7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
        13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
        10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
        3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
    },
    {
        2, 12, 4, 1, 7, 10, 11, 6, 8 ,5 , 3, 15, 13, 0, 14, 9,
        14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
        4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
        11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
    },
    {
        12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
        10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
        9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
        4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13
    },
    {
        4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
        13, 0 , 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
        1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
        6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
    },
    {
        13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
        1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
        7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
        2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
    }
};

string toText(int input[64]){
    int counter = 0;
    string str = "AAAAAAAA";
    for(int i = 0; i < 8; i++){
        counter = 0;
        for(int j = 0; j < 8; j++){
            counter += (input[i*8 + j] * pow(2, 7 - j));
        }
        str[i] = (char)counter;
    }
    return str;
}

unsigned long long power(int pow){
    unsigned long long l = 1;
    for(int i = 0; i < pow; i++){
        l *= 2;
    }
    return l;
}

unsigned long long binNum(int num[64]){
    unsigned long long n = 0;
    for(int i = 0; i < 64; i++){
        n += (power(i) * num[63 - i]);
    }
    return n;
}

void getS(int input[6], int output[4], int S[64]){
    int x = (2 * input[0]) + (1 * input[5]);            // get x, y coordinates
    int y =  (input[1] * 8) + (input[2] * 4) + (input[3] * 2) + (input[4] * 1);
    bitset<4> temp = bitset<4>(S[x * 16 + y]);          // convert table entry to 4 bits
    for(int i = 0; i < 4; i++){
        output[i] = temp[3 - i];                        // place bits in output
    }    
}

void permuteBlock(int bits[64], int table[64]){
    int bitCopy[64];                         // make a deep copy of the input
    for(int i = 0; i < 64; i++){
        bitCopy[i] = bits[i];
    }
    for(int i = 0; i < 64; i++){
        bits[i] = bitCopy[table[i] - 1];    // populate the original by indexing the copy with the table
    }
}



void expandBlock(int bits[32], int expandedBlock[48], int table[48]){
    for(int i = 0; i < 48; i++){
        expandedBlock[i] = bits[table[i] - 1];      // populate expandedBlock by indexing the 32 bits with the table
    }
}

void generateSubkey(int bits[64], int C[28], int D[28], int table[56]){
    int permuteBits[56];                        // declare a variable to temporarily store our subkey
    for(int i  = 0; i < 56; i++){               // map the subkey from the 64bit input key
        permuteBits[i] = bits[table[i] - 1];
    }
    for(int i = 0; i < 28; i++){                // assign the left half to C, right half to D
        C[i] = permuteBits[i];
        D[i] = permuteBits[i + 28];
    }
}

void shiftArr(int arr[28], bool L){
    if (L){                             // shift the bits left
        int temp = arr[0];
        for(int i = 0; i < 27; i++){
            arr[i] = arr[i + 1];
        }
        arr[27] = temp;
    }
    else{
        int temp = arr[27];             // shift the bits right
        for(int i = 27; i > 0; i--){
            arr[i] = arr[i - 1];
        }
        arr[0] = temp;
    }
}

void generateK(int C[28], int D[28], int k[48], int table[48], int i, bool L){
    int CD[56];
    if(L){
        shiftArr(C, L);
        shiftArr(D, L);
        switch(i){
            case 1:
            case 2:
            case 9:
            case 16:
                break;
            default:
                shiftArr(C, L);
                shiftArr(D, L);
                break;
        }
    }
    else{
        switch(i){
            case 1:
                break;
            case 2:
            case 9:
            case 16:
                shiftArr(C, L);
                shiftArr(D, L);
                break;
            default:
                shiftArr(C, L);
                shiftArr(D, L);
                shiftArr(C, L);
                shiftArr(D, L);
                break;
        }
    }
    for(int i = 0; i < 28; i++){
        CD[i] = C[i];
        CD[i + 28] = D[i];
    }
    for(int i = 0; i < 48; i++){
        k[i] = CD[table[i] - 1];
    }
}



void F(int R[32], int k[48], int output[32]){
    int RX[48];                         // expanded key
    int *rx;                            // subset of expanded key
    int *r;                             // subset of reduced key
    int copy[32];                       // for permuting the output
    
    expandBlock(R, RX, Exp);            // expand R from 32 to 48 bits using Expansion table
    
    for(int i = 0; i < 8; i++){
        rx = RX + (i * 6);              // grab a 6 bit subset of RX
        for(int j = 0; j < 6; j++){     // XOR the subset with the key
            if(rx[j] == 1 && k[i*6 + j] == 1){
                rx[j] = 0;
            }
            else if(rx[j] == 1 || k[i*6 + j] == 1){
                rx[j] = 1;
            }
            else{
                rx[j] = 0;
            }
        }
        r = output + (i * 4);           // grab a 4 bit subset of the XOR
        getS(rx, r, S[i]);              // perform Sbox operation on the subset
    }

    for(int i = 0; i < 32; i++){        // copy the output array
        copy[i] = output[i];
    }
    for(int i = 0; i < 32; i++){        // permute the output
        output[i] = copy[P[i] - 1];
    }
 
}

void XOR(int a[32], int b[32], int output[32]){
    for(int i = 0; i < 32; i++){
        if(a[i] == 1 && b [i] == 1){
            output[i] = 0;
        }
        else if(a[i] == 1 || b[i] == 1){
            output[i] = 1;
        }
        else{
            output[i] = 0;
        }
    }
}

void encrypt(int input[64], int key[64], bool E){
    
    int L[17][32], R[17][32];   // halves of text
    int C[28], D[28];           // halves of key once expanded
    int fOut[32];               // output of F
    int subkey[48];             // declare a variable for our subkey
    
    generateSubkey(key, C, D, PC1); //initial key permutation into C and D
    
    permuteBlock(input, IP);        // perform initial permutation of bits
    for(int i = 0; i < 32; i++){    // split permuted input in half
        L[0][i] = input[i];
        R[0][i] = input[i + 32];
    }

    for(int i = 0; i < 16; i++){                // perform 16 rounds
        generateK(C, D, subkey, PC2, i + 1, E); // generate the subkey for the current round
        F(R[i], subkey, fOut);                  // XOR Ri with the Subkey and permute
        XOR(fOut, L[i], R[(i+1)]);              // perform XOR on fOut and Li, store result in Ri+1
        for(int j = 0; j < 32; j++){            // Set Li+1 from Ri
            L[(i+1)][j] = R[i][j];
        }
    }
    
    for(int i = 0; i < 32; i++){                // perform final swap after round 16
        input[i] = R[16][i];                    // R goes to first half
        input[i + 32] = L[16][i];               // L goes to second half
    }
    
    permuteBlock(input, IPI);                    // perform inverse permutation on the result
}

int main() {
    while(true){
        string str;
        unsigned long long result;
        bitset<8> block;
        bitset<64> encrypted;
        int input[64];
        int key[64];

        cout << "Enter 1 to encrypt, any other number to decrypt: ";
        int num;
        cin >> num;
        
        if(num == 1){
            cout << "Enter a string: ";
            cin >> str;
            for(int i  = 0; i < 8; i++){
                block = bitset<8>(str[i]);
                for(int j = 0; j < 8; j++){
                    input[i * 8 + j] = block[7 - j];
                }
            }
            cout << endl << "Enter a key: ";
            cin >> str;
            for(int i  = 0; i < 8; i++){
                block = bitset<8>(str[i]);
                for(int j = 0; j < 8; j++){
                    key[i * 8 + j] = block[7 - j];
                }
            }
            encrypt(input, key, true);
            result = binNum(input);
            cout << "\nResult in binary: \n";
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    cout << input[i*8 + j];
                }
                cout << endl;
            }
            cout << endl;
            cout << "Encrypted text: " << result << endl << endl;
        }
        
        else{
            cout << "Enter encrypted text: ";
            cin >> result;
            cout << "\nEnter key: ";
            cin >> str;
            for(int i  = 0; i < 8; i++){
                block = bitset<8>(str[i]);
                for(int j = 0; j < 8; j++){
                    key[i * 8 + j] = block[7 - j];
                }
            }
            encrypted = bitset<64>(result);
            for(int i = 0; i < 64; i++){
                input[i] = encrypted[63 - i];
            }
            encrypt(input, key, false);
            cout << "\nResult in binary:\n";
			for(int i = 0; i < 8; i++){
				for(int j = 0; j < 8; j++){
					cout << input[i*8 + j];
				}
				cout << endl;
			}
			cout << endl;
            str = toText(input);
            cout << "Decrypted: " << str << endl << endl;
        }

    }
    
    return 0;
}
