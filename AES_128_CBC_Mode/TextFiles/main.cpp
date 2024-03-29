#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;



    uint8_t Key[4][44] = {{0x2b,0x28,0xab,0x09},
                         {0x7e,0xae,0xf7,0xcf},
                         {0x15,0xd2,0x15,0x4f},
                         {0x16,0xa6,0x88,0x3c}};


//-------------------Initialization Vector
    uint8_t IniVec[4][4] = {{0xff,0x88,0x44,0x00},
                            {0xee,0x99,0x55,0x11},
                            {0xdd,0xaa,0x66,0x22},
                            {0xcc,0xbb,0x77,0x33}};





    uint8_t SBox[16][16] = {
                        {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
                        {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
                        {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
                        {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
                        {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
                        {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
                        {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
                        {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
                        {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
                        {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
                        {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
                        {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
                        {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
                        {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
                        {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
                        {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}
                        };

     uint8_t InvSBox[16][16] = {
                                {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
                                {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb },
                                {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},
                                {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},
                                {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
                                {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},
                                {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},
                                {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},
                                {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
                                {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
                                { 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
                                { 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},
                                { 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
                                { 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
                                { 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
                                { 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}
                            };

     uint8_t rcon[4][10] = { {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36},
                             {0,0,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0}};

    uint8_t MixCol[4][4] = { {0x02,0x03,0x01,0x01},
                             {0x01,0x02,0x03,0x01},
                             {0x01,0x01,0x02,0x03},
                             {0x03,0x01,0x01,0x02}};

    uint8_t InvMixCol[4][4] = { {0x0e,0x0b,0x0d,0x09},
                                {0x09,0x0e,0x0b,0x0d},
                                {0x0d,0x09,0x0e,0x0b},
                                {0x0b,0x0d,0x09,0x0e} };

       uint8_t temp[4][4] = {{0xff,0x88,0x44,0x00},
                            {0xee,0x99,0x55,0x11},
                            {0xdd,0xaa,0x66,0x22},
                            {0xcc,0xbb,0x77,0x33}};


void Encryption(int index,uint8_t Message[][4]);
void Decryption(int index,uint8_t Cipher[][4],int rows);


int main()
{

 string Text="";
 string r;
 ifstream ReadFile("Input.txt");


  while (getline (ReadFile, r)) {

    Text.append(r);
  }


  ReadFile.close();

  int rows= Text.size()/4;

  uint8_t Message[rows][4];

  int k=0;
  for(int i=0;i<rows;i++)
  {
      for(int j=0;j<4;j++)
      {
          Message[i][j]=Text[k];
          k++;
      }
  }


            printf("\nKey Used: \n\n");
            for (int i=0;i<4;i++)
            {
                   for (int j=0;j<44;j++)
                        {

                            printf("%X  ",Key[i][j]);
                        }

                        printf("\n");
            }


            printf("\nInitialization Vector Used: \n\n");
            for (int i=0;i<4;i++)
            {
                   for (int j=0;j<4;j++)
                        {

                            printf("%X  ",IniVec[i][j]);
                        }

                        printf("\n");
            }



                                //-------------Encryption----------------
        printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>AES 128 Encryption CBC Mode!<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");


        int len=0;

        len = rows/4;

        for(int i=0; i<len; i++)
            {
                Encryption(i,Message);

            }
        printf("\nEncryption Done!\nEncrypted file stored in EncryptedText.txt\n");

        uint8_t Cipher[rows][4];

        //-----------------Store Encrypted Message in Cipher -----------------
        for(int i=0;i<rows;i++)
              {
                  for(int j=0;j<4;j++)
                  {
                      Cipher[i][j]=Message[i][j];

                  }
              }

                                //-------------Decryption----------------
        printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>AES 128 Decryption CBC Mode!<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");


        for(int i=(len-1); i>=0; i--)
            {
                Decryption(i,Cipher,rows);
            }


         printf("\nDecryption Done!\nDecrypted file stored in DecryptedText.txt\n");

    return 0;
}



void Encryption(int index,uint8_t Message[][4])
{
    int BlockRow = index*4;

//-------------Step 0: Add Initialization Vector and Round Key----------------


        if(index !=0)               //Add previous cipher message to Initialization Vector
        {
            for (int i=0;i<4;i++)
            {
                   for (int j=0;j<4;j++)
                        {
                           IniVec[i][j]= Message[BlockRow-4][j];
                        }
                        BlockRow++;
            }
        }

    BlockRow = index*4;

    for (int i=0;i<4;i++)
    {
           for (int j=0;j<4;j++)
                {
                    Message[BlockRow][j]= Message[BlockRow][j] ^ IniVec[i][j];

                }
                BlockRow++;
    }



BlockRow = index*4;

    for (int i=0;i<4;i++)
    {
           for (int j=0;j<4;j++)
                {
                    Message[BlockRow][j]= Message[BlockRow][j] ^ Key[i][j];
                }
                BlockRow++;
    }




//-------------Step 1-10 in the Loop----------------

        for(int a=0; a<10; a++)
        {

            //-------------Generate Key----------------
             int kindex=1+a;
             kindex=kindex*4;

            uint8_t t1=0;
            uint8_t t2=Key[3][kindex-1];

            uint8_t NewKey[4][4] = {{0,0,0,0},
                                     {0,0,0,0},
                                     {0,0,0,0},
                                     {0,0,0,0}};

            //--------------Rotate Up-----------------
                for (int i=2; i>=0; i--)
                {
                        t1 = t2;
                        t2 = Key[i][kindex-1];
                        NewKey[i][0] = t1;


                }
                NewKey[3][0] = t2;


            //--------------Sub Bytes for Key-----------------
                uint8_t t=0;
                int x=0;
                int y=0;
                for (int i=0; i<4; i++)
                {
                        t = NewKey[i][0];
                        y = (t & 0x0F);
                        x = (t & 0xF0) >> 4;
                        NewKey[i][0] = SBox[x][y];
                }

            //--------------XOR with rcon Matrix-----------------
                int k=0;
                for (int i=0;i<4;i++)
                {
                    NewKey[i][0]= rcon[i][a] ^ NewKey[i][0] ^ Key[i][kindex-4];

                }

                for(int i=0;i<4;i++)
                {
                    k=3;
                    for (int j=1;j<4;j++)
                    {
                        NewKey[i][j]= Key[i][kindex-k] ^ NewKey[i][j-1];
                        k--;
                    }
                }

            //--------------Final Key Generated-----------------

                for (int i=0;i<4;i++)
                {
                    k=0;
                       for (int j=kindex; j<(kindex+4); j++)
                            {
                                Key[i][j]=NewKey[i][k];
                                k++;
                            }
                }

            //--------------Step 1: Sub Bytes-----------------

                t=0;
                x=0;
                y=0;

            BlockRow = index*4;

                for (int i=BlockRow; i<(BlockRow+4); i++)
                {
                    for(int j=0; j<4;j++)
                    {

                        t = Message[i][j];
                        y = (t & 0x0F);

                        x = (t & 0xF0) >> 4;

                        Message[i][j] = SBox[x][y];
                    }

                }

            //--------------Step 2: Shift Rows-----------------

            t1=0;

             for (int i=(BlockRow+1); i<(BlockRow+4); i++)
                {

                    if(i==(BlockRow+1))
                    {
                        uint8_t t2=Message[i][3];

                        for (int j=2; j>=0; j--)
                        {
                            t1=t2;
                            t2=Message[i][j];
                            Message[i][j]=t1;
                        }

                        Message[i][3]=t2;
                    }

                    else if(i==(BlockRow+2))
                    {
                       for(int z=0;z<2;z++)
                       {

                        uint8_t t2=Message[i][3];

                        for (int j=2; j>=0; j--)
                        {
                            t1=t2;
                            t2=Message[i][j];
                            Message[i][j]=t1;
                        }

                        Message[i][3]=t2;
                       }
                    }

                    else
                    {

                    for(int z=0; z<3; z++)
                       {

                        uint8_t t2=Message[i][3];

                        for (int j=2; j>=0; j--)
                        {
                            t1=t2;
                            t2=Message[i][j];
                            Message[i][j]=t1;
                        }

                        Message[i][3]=t2;
                       }
                    }

                    }

            //--------------Step 3: MixColumns-----------------

            if(a != 9)
            {

            int fb=0;
            uint8_t temp=0;
            uint8_t m[4];
            uint8_t mx[4][4];
            k=0;
            for(int i=0;i<4;i++)
            {
               for(int j=0;j<4;j++)
               {
                   BlockRow = index*4;

                for(int b=0;b<4;b++)
                    {
                                   if(MixCol[j][b] == 1)
                                   {
                                       m[k]=Message[BlockRow][i];

                                   }

                                   else if (MixCol[j][b] == 2)
                                    {
                                        fb = (Message[BlockRow][i] & 0x80) >> 7;       //Find Leftmost Bit before shift
                                        m[k] = Message[BlockRow][i] << 1;    //Left shift
                                        if(fb == 1)
                                        {
                                             m[k] = m[k] ^ 0x1B;    //XOR with 1B
                                        }

                                    }

                                    else if (MixCol[j][b] == 3)
                                    {

                                        temp = Message[BlockRow][i];
                                        fb = (Message[BlockRow][i] & 0x80) >> 7;       //Find Leftmost Bit before shift
                                        m[k] = Message[BlockRow][i] << 1;    //Left shift
                                        if(fb == 1)
                                        {
                                             m[k] = m[k] ^ 0x1B;    //XOR with 1B
                                        }

                                        m[k]= m[k] ^ temp;

                                    }

                        k++;
                        BlockRow++;

                    }
                    k=0;

                    mx[j][i]= m[0] ^ m[1] ^ m[2] ^ m[3];

               }


            }


            BlockRow = index*4;

                for (int i=0;i<4;i++)
                {
                       for (int j=0;j<4;j++)
                            {
                                Message[BlockRow][j]=mx[i][j];
                            }
                BlockRow++;
                }
            }

                //--------------Step 4: Add Round Key-----------------


                 BlockRow = index*4;

                for (int i=0;i<4;i++)
                {

                    k=kindex;
                       for (int j=0;j<4;j++)
                            {
                                Message[BlockRow][j]= Message[BlockRow][j] ^ Key[i][k];
                                k++;

                            }
                            BlockRow++;

                }



            if (a==9)
                {


            //    printf("\nFinal Encrypted Message for Block# %d\n\n",index+1);


                BlockRow = index*4;

                  ofstream WriteFile("EncryptedText.txt",ios::app);


              for (int i=(BlockRow); i<(BlockRow+4); i++)
                {
                for (int j=0;j<4;j++)
                            {
               //                 printf("%X  ",Message[i][j]);

                                  WriteFile << Message[i][j];
                            }

                 //           printf("\n");
                }
                      WriteFile.close();

                }
        }

}





void Decryption(int index,uint8_t Cipher[][4],int rows)

{
    int kindex=0;
    int k=0;
    //-------------Generate Key----------------
    for(int a=0; a<10; a++)
    {
         kindex=1+a;
         kindex=kindex*4;

        uint8_t t1=0;
        uint8_t t2=Key[3][kindex-1];

        uint8_t NewKey[4][4] = {{0,0,0,0},
                                 {0,0,0,0},
                                 {0,0,0,0},
                                 {0,0,0,0}};

        //--------------Rotate Up-----------------
            for (int i=2; i>=0; i--)
            {
                    t1 = t2;
                    t2 = Key[i][kindex-1];
                    NewKey[i][0] = t1;


            }
            NewKey[3][0] = t2;

            uint8_t t=0;
            int x=0;
            int y=0;

        //--------------Sub Bytes-----------------
            for (int i=0; i<4; i++)
            {
                    t = NewKey[i][0];
                    y = (t & 0x0F);
                    x = (t & 0xF0) >> 4;
                    NewKey[i][0] = SBox[x][y];
            }


        //--------------XOR with rcon Matrix-----------------
            k=0;
            for (int i=0;i<4;i++)
            {
                NewKey[i][0]= rcon[i][a] ^ NewKey[i][0] ^ Key[i][kindex-4];

            }

            for(int i=0;i<4;i++)
            {
                k=3;
                for (int j=1;j<4;j++)
                {
                    NewKey[i][j]= Key[i][kindex-k] ^ NewKey[i][j-1];
                    k--;
                }

            }


        //--------------Final Key Generated-----------------

            for (int i=0;i<4;i++)
            {
                k=0;
                   for (int j=kindex; j<(kindex+4); j++)
                        {
                            Key[i][j]=NewKey[i][k];
                            k++;

                        }


            }

    }




int BlockRow = index*4;
//-------------Step 0: Add Round Key----------------


    for (int i=0;i<4;i++)
    {
        k=40;
           for (int j=0;j<4;j++)
                {
                    Cipher[BlockRow][j]= Cipher[BlockRow][j] ^ Key[i][k];
                    k++;
                }

                BlockRow++;

    }




//-------------Step 1-10 in the Loop----------------

        for(int a=0; a<10; a++)
        {

                //--------------Step 1: Inverse Shift Rows-----------------
                BlockRow = index*4;
                uint8_t t1=0;


                    for (int i=(BlockRow+1); i<(BlockRow+4); i++)
                    {
                        if(i==(BlockRow+1))
                        {
                            uint8_t t2=Cipher[i][0];

                            for (int j=1; j<4; j++)
                            {
                                t1=t2;
                                t2=Cipher[i][j];
                                Cipher[i][j]=t1;
                            }

                            Cipher[i][0]=t2;
                        }

                        else if(i==(BlockRow+2))
                        {
                           for(int z=0;z<2;z++)
                           {

                            uint8_t t2=Cipher[i][0];

                            for (int j=1; j<4; j++)
                            {
                                t1=t2;
                                t2=Cipher[i][j];
                                Cipher[i][j]=t1;
                            }

                            Cipher[i][0]=t2;
                           }
                        }

                        else
                        {

                        for(int z=0; z<3; z++)
                           {

                            uint8_t t2=Cipher[i][0];

                            for (int j=1; j<4; j++)
                            {
                                t1=t2;
                                t2=Cipher[i][j];
                                Cipher[i][j]=t1;
                            }

                            Cipher[i][0]=t2;
                           }
                        }

                        }

                //--------------Step 2: Inverse Sub Bytes-----------------

                    uint8_t t=0;
                    int x=0;
                    int y=0;

                     for (int i=BlockRow; i<(BlockRow+4); i++)
                    {
                        for(int j=0; j<4;j++)
                        {

                            t = Cipher[i][j];
                            y = (t & 0x0F);

                            x = (t & 0xF0) >> 4;

                            Cipher[i][j] = InvSBox[x][y];
                        }
                    }


                    //--------------Step 3: Add Round Key-----------------

                     BlockRow = index*4;
                    kindex=36;

                    for (int i=0;i<4;i++)
                    {
                        k=kindex-(a*4);

                           for (int j=0;j<4;j++)
                                {
                                    Cipher[BlockRow][j]= Cipher[BlockRow][j] ^ Key[i][k];

                                     k++;

                                }
                                BlockRow++;

                    }

                if(a==9)
                {


                    BlockRow = index*4;

            //------------- Add Initialization Vector and Add Round Key----------------


                    if(index !=0)               //Add previous cipher message to Initialization Vector
                    {
                        for (int i=0;i<4;i++)
                        {
                               for (int j=0;j<4;j++)
                                    {
                                       IniVec[i][j]= Cipher[BlockRow-4][j];

                                    }
                                    BlockRow++;
                        }
                    }

                    else
                        {
                        for (int i=0;i<4;i++)
                        {
                               for (int j=0;j<4;j++)
                                    {
                                       IniVec[i][j]= temp[i][j];

                                    }
                        }

                        }

                BlockRow = index*4;

                for (int i=0;i<4;i++)
                {
                       for (int j=0;j<4;j++)
                            {
                                Cipher[BlockRow][j]= Cipher[BlockRow][j] ^ IniVec[i][j];

                            }
                            BlockRow++;
                }


             //        printf("\nFinal Decrypted Message for Block# %d\n\n",index+1);

                     BlockRow = index*4;

                for (int i=BlockRow; i<(BlockRow+4); i++)
                    {
                           for (int j=0;j<4;j++)
                                {

                  //                  printf("%X  ",Cipher[i][j]);

                                }

//                                printf("\n");
                    }


                    if(index==0)            //After the Last Block is Decrypted Arrange Order
                    {

                        ofstream WriteFile("DecryptedText.txt",ios::app);

                        for (int i=0; i<rows; i++)
                            {
                           for (int j=0;j<4;j++)
                                {
                                      WriteFile << Cipher[i][j];
                                }
                            }

                            WriteFile.close();
                    }

                }




                    //--------------Step 4: Inverse MixColumns-----------------

                if(a != 9)
                {
                    //For Inverse Mix Columns we use look ahead tables


                uint8_t m[4];
                uint8_t mx[4][4];
                k=0;

                 uint8_t mul_e[256] =
                    {
                        0x00,0x0e,0x1c,0x12,0x38,0x36,0x24,0x2a,0x70,0x7e,0x6c,0x62,0x48,0x46,0x54,0x5a,
                        0xe0,0xee,0xfc,0xf2,0xd8,0xd6,0xc4,0xca,0x90,0x9e,0x8c,0x82,0xa8,0xa6,0xb4,0xba,
                        0xdb,0xd5,0xc7,0xc9,0xe3,0xed,0xff,0xf1,0xab,0xa5,0xb7,0xb9,0x93,0x9d,0x8f,0x81,
                        0x3b,0x35,0x27,0x29,0x03,0x0d,0x1f,0x11,0x4b,0x45,0x57,0x59,0x73,0x7d,0x6f,0x61,
                        0xad,0xa3,0xb1,0xbf,0x95,0x9b,0x89,0x87,0xdd,0xd3,0xc1,0xcf,0xe5,0xeb,0xf9,0xf7,
                        0x4d,0x43,0x51,0x5f,0x75,0x7b,0x69,0x67,0x3d,0x33,0x21,0x2f,0x05,0x0b,0x19,0x17,
                        0x76,0x78,0x6a,0x64,0x4e,0x40,0x52,0x5c,0x06,0x08,0x1a,0x14,0x3e,0x30,0x22,0x2c,
                        0x96,0x98,0x8a,0x84,0xae,0xa0,0xb2,0xbc,0xe6,0xe8,0xfa,0xf4,0xde,0xd0,0xc2,0xcc,
                        0x41,0x4f,0x5d,0x53,0x79,0x77,0x65,0x6b,0x31,0x3f,0x2d,0x23,0x09,0x07,0x15,0x1b,
                        0xa1,0xaf,0xbd,0xb3,0x99,0x97,0x85,0x8b,0xd1,0xdf,0xcd,0xc3,0xe9,0xe7,0xf5,0xfb,
                        0x9a,0x94,0x86,0x88,0xa2,0xac,0xbe,0xb0,0xea,0xe4,0xf6,0xf8,0xd2,0xdc,0xce,0xc0,
                        0x7a,0x74,0x66,0x68,0x42,0x4c,0x5e,0x50,0x0a,0x04,0x16,0x18,0x32,0x3c,0x2e,0x20,
                        0xec,0xe2,0xf0,0xfe,0xd4,0xda,0xc8,0xc6,0x9c,0x92,0x80,0x8e,0xa4,0xaa,0xb8,0xb6,
                        0x0c,0x02,0x10,0x1e,0x34,0x3a,0x28,0x26,0x7c,0x72,0x60,0x6e,0x44,0x4a,0x58,0x56,
                        0x37,0x39,0x2b,0x25,0x0f,0x01,0x13,0x1d,0x47,0x49,0x5b,0x55,0x7f,0x71,0x63,0x6d,
                        0xd7,0xd9,0xcb,0xc5,0xef,0xe1,0xf3,0xfd,0xa7,0xa9,0xbb,0xb5,0x9f,0x91,0x83,0x8d
                    };

                        uint8_t mul_b[256] =
                    {
                        0x00,0x0b,0x16,0x1d,0x2c,0x27,0x3a,0x31,0x58,0x53,0x4e,0x45,0x74,0x7f,0x62,0x69,
                        0xb0,0xbb,0xa6,0xad,0x9c,0x97,0x8a,0x81,0xe8,0xe3,0xfe,0xf5,0xc4,0xcf,0xd2,0xd9,
                        0x7b,0x70,0x6d,0x66,0x57,0x5c,0x41,0x4a,0x23,0x28,0x35,0x3e,0x0f,0x04,0x19,0x12,
                        0xcb,0xc0,0xdd,0xd6,0xe7,0xec,0xf1,0xfa,0x93,0x98,0x85,0x8e,0xbf,0xb4,0xa9,0xa2,
                        0xf6,0xfd,0xe0,0xeb,0xda,0xd1,0xcc,0xc7,0xae,0xa5,0xb8,0xb3,0x82,0x89,0x94,0x9f,
                        0x46,0x4d,0x50,0x5b,0x6a,0x61,0x7c,0x77,0x1e,0x15,0x08,0x03,0x32,0x39,0x24,0x2f,
                        0x8d,0x86,0x9b,0x90,0xa1,0xaa,0xb7,0xbc,0xd5,0xde,0xc3,0xc8,0xf9,0xf2,0xef,0xe4,
                        0x3d,0x36,0x2b,0x20,0x11,0x1a,0x07,0x0c,0x65,0x6e,0x73,0x78,0x49,0x42,0x5f,0x54,
                        0xf7,0xfc,0xe1,0xea,0xdb,0xd0,0xcd,0xc6,0xaf,0xa4,0xb9,0xb2,0x83,0x88,0x95,0x9e,
                        0x47,0x4c,0x51,0x5a,0x6b,0x60,0x7d,0x76,0x1f,0x14,0x09,0x02,0x33,0x38,0x25,0x2e,
                        0x8c,0x87,0x9a,0x91,0xa0,0xab,0xb6,0xbd,0xd4,0xdf,0xc2,0xc9,0xf8,0xf3,0xee,0xe5,
                        0x3c,0x37,0x2a,0x21,0x10,0x1b,0x06,0x0d,0x64,0x6f,0x72,0x79,0x48,0x43,0x5e,0x55,
                        0x01,0x0a,0x17,0x1c,0x2d,0x26,0x3b,0x30,0x59,0x52,0x4f,0x44,0x75,0x7e,0x63,0x68,
                        0xb1,0xba,0xa7,0xac,0x9d,0x96,0x8b,0x80,0xe9,0xe2,0xff,0xf4,0xc5,0xce,0xd3,0xd8,
                        0x7a,0x71,0x6c,0x67,0x56,0x5d,0x40,0x4b,0x22,0x29,0x34,0x3f,0x0e,0x05,0x18,0x13,
                        0xca,0xc1,0xdc,0xd7,0xe6,0xed,0xf0,0xfb,0x92,0x99,0x84,0x8f,0xbe,0xb5,0xa8,0xa3
                    };

                        uint8_t mul_d[256] =
                    {
                        0x00,0x0d,0x1a,0x17,0x34,0x39,0x2e,0x23,0x68,0x65,0x72,0x7f,0x5c,0x51,0x46,0x4b,
                        0xd0,0xdd,0xca,0xc7,0xe4,0xe9,0xfe,0xf3,0xb8,0xb5,0xa2,0xaf,0x8c,0x81,0x96,0x9b,
                        0xbb,0xb6,0xa1,0xac,0x8f,0x82,0x95,0x98,0xd3,0xde,0xc9,0xc4,0xe7,0xea,0xfd,0xf0,
                        0x6b,0x66,0x71,0x7c,0x5f,0x52,0x45,0x48,0x03,0x0e,0x19,0x14,0x37,0x3a,0x2d,0x20,
                        0x6d,0x60,0x77,0x7a,0x59,0x54,0x43,0x4e,0x05,0x08,0x1f,0x12,0x31,0x3c,0x2b,0x26,
                        0xbd,0xb0,0xa7,0xaa,0x89,0x84,0x93,0x9e,0xd5,0xd8,0xcf,0xc2,0xe1,0xec,0xfb,0xf6,
                        0xd6,0xdb,0xcc,0xc1,0xe2,0xef,0xf8,0xf5,0xbe,0xb3,0xa4,0xa9,0x8a,0x87,0x90,0x9d,
                        0x06,0x0b,0x1c,0x11,0x32,0x3f,0x28,0x25,0x6e,0x63,0x74,0x79,0x5a,0x57,0x40,0x4d,
                        0xda,0xd7,0xc0,0xcd,0xee,0xe3,0xf4,0xf9,0xb2,0xbf,0xa8,0xa5,0x86,0x8b,0x9c,0x91,
                        0x0a,0x07,0x10,0x1d,0x3e,0x33,0x24,0x29,0x62,0x6f,0x78,0x75,0x56,0x5b,0x4c,0x41,
                        0x61,0x6c,0x7b,0x76,0x55,0x58,0x4f,0x42,0x09,0x04,0x13,0x1e,0x3d,0x30,0x27,0x2a,
                        0xb1,0xbc,0xab,0xa6,0x85,0x88,0x9f,0x92,0xd9,0xd4,0xc3,0xce,0xed,0xe0,0xf7,0xfa,
                        0xb7,0xba,0xad,0xa0,0x83,0x8e,0x99,0x94,0xdf,0xd2,0xc5,0xc8,0xeb,0xe6,0xf1,0xfc,
                        0x67,0x6a,0x7d,0x70,0x53,0x5e,0x49,0x44,0x0f,0x02,0x15,0x18,0x3b,0x36,0x21,0x2c,
                        0x0c,0x01,0x16,0x1b,0x38,0x35,0x22,0x2f,0x64,0x69,0x7e,0x73,0x50,0x5d,0x4a,0x47,
                        0xdc,0xd1,0xc6,0xcb,0xe8,0xe5,0xf2,0xff,0xb4,0xb9,0xae,0xa3,0x80,0x8d,0x9a,0x97
                    };


                        uint8_t mul_9[256] =
                    {
                        0x00,0x09,0x12,0x1b,0x24,0x2d,0x36,0x3f,0x48,0x41,0x5a,0x53,0x6c,0x65,0x7e,0x77,
                        0x90,0x99,0x82,0x8b,0xb4,0xbd,0xa6,0xaf,0xd8,0xd1,0xca,0xc3,0xfc,0xf5,0xee,0xe7,
                        0x3b,0x32,0x29,0x20,0x1f,0x16,0x0d,0x04,0x73,0x7a,0x61,0x68,0x57,0x5e,0x45,0x4c,
                        0xab,0xa2,0xb9,0xb0,0x8f,0x86,0x9d,0x94,0xe3,0xea,0xf1,0xf8,0xc7,0xce,0xd5,0xdc,
                        0x76,0x7f,0x64,0x6d,0x52,0x5b,0x40,0x49,0x3e,0x37,0x2c,0x25,0x1a,0x13,0x08,0x01,
                        0xe6,0xef,0xf4,0xfd,0xc2,0xcb,0xd0,0xd9,0xae,0xa7,0xbc,0xb5,0x8a,0x83,0x98,0x91,
                        0x4d,0x44,0x5f,0x56,0x69,0x60,0x7b,0x72,0x05,0x0c,0x17,0x1e,0x21,0x28,0x33,0x3a,
                        0xdd,0xd4,0xcf,0xc6,0xf9,0xf0,0xeb,0xe2,0x95,0x9c,0x87,0x8e,0xb1,0xb8,0xa3,0xaa,
                        0xec,0xe5,0xfe,0xf7,0xc8,0xc1,0xda,0xd3,0xa4,0xad,0xb6,0xbf,0x80,0x89,0x92,0x9b,
                        0x7c,0x75,0x6e,0x67,0x58,0x51,0x4a,0x43,0x34,0x3d,0x26,0x2f,0x10,0x19,0x02,0x0b,
                        0xd7,0xde,0xc5,0xcc,0xf3,0xfa,0xe1,0xe8,0x9f,0x96,0x8d,0x84,0xbb,0xb2,0xa9,0xa0,
                        0x47,0x4e,0x55,0x5c,0x63,0x6a,0x71,0x78,0x0f,0x06,0x1d,0x14,0x2b,0x22,0x39,0x30,
                        0x9a,0x93,0x88,0x81,0xbe,0xb7,0xac,0xa5,0xd2,0xdb,0xc0,0xc9,0xf6,0xff,0xe4,0xed,
                        0x0a,0x03,0x18,0x11,0x2e,0x27,0x3c,0x35,0x42,0x4b,0x50,0x59,0x66,0x6f,0x74,0x7d,
                        0xa1,0xa8,0xb3,0xba,0x85,0x8c,0x97,0x9e,0xe9,0xe0,0xfb,0xf2,0xcd,0xc4,0xdf,0xd6,
                        0x31,0x38,0x23,0x2a,0x15,0x1c,0x07,0x0e,0x79,0x70,0x6b,0x62,0x5d,0x54,0x4f,0x46
                    };


                for(int i=0;i<4;i++)
                {
                   for(int j=0;j<4;j++)
                   {
                       BlockRow = index*4;

                    for(int b=0;b<4;b++)
                        {
                                       if(InvMixCol[j][b] == 0x0e)
                                       {
                                           m[k]=mul_e[Cipher[BlockRow][i]];

                                       }

                                       else if (InvMixCol[j][b] == 0x0b)
                                        {

                                                 m[k]=mul_b[Cipher[BlockRow][i]];
                                        }

                                        else if (InvMixCol[j][b] == 0x0d)
                                        {

                                                m[k]=mul_d[Cipher[BlockRow][i]];

                                        }

                                        else if (InvMixCol[j][b] == 0x09)
                                        {

                                             m[k]=mul_9[Cipher[BlockRow][i]];

                                        }
                            BlockRow++;
                            k++;

                        }
                        k=0;

                        mx[j][i]= m[0] ^ m[1] ^ m[2] ^ m[3];

                   }

                }


                BlockRow = index*4;
                    for (int i=0;i<4;i++)
                    {
                           for (int j=0;j<4;j++)
                                {
                                    Cipher[BlockRow][j]=mx[i][j];
                                }
                                BlockRow++;
                    }

                }
        }
}

